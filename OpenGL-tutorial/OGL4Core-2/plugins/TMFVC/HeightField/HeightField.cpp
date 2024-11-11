#include "HeightField.h"

#include <fstream>
#include <iostream>
#include <limits>

#include <glm/gtc/matrix_transform.hpp>
#include <imGuIZMOquat.h>
#include <imgui.h>

#include "core/Core.h"

using namespace OGL4Core2;
using namespace OGL4Core2::Plugins::TMFVC::HeightField;

HeightField::HeightField(const Core::Core& c)
    : Core::RenderPlugin(c),
      currentFileLoaded(0),
      currentFileSelection(0),
      filterId(0),
      hfSizeX(0),
      hfSizeY(0),
      hfMinHeight(0.0f),
      hfMaxHeight(1000.0f),
      hfLengthScale(10.0f),
      hfLightDir(glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f))),
      shader(nullptr),
      vaQuad(nullptr),
      texHF(0) {
    c.setWindowSize(800, 800);

    // Load list of data files.
    datFiles = getResourceDirFilePaths("terrain", "^.*\\.dat$");
    if (datFiles.empty()) {
        std::cerr << "No data files found!" << std::endl;
    }
    datFilesGuiString.clear();
    for (const auto& file : datFiles) {
        datFilesGuiString += file.stem().string() + '\0';
    }
    datFilesGuiString += '\0';

    initShaders();

    const std::vector<float> quadVertices{
        // clang-format off
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        // clang-format on
    };
    const std::vector<GLuint> quadIndices{0, 1, 2, 3};
    glowl::Mesh::VertexDataList<float> vertexDataQuad{{quadVertices, {8, {{2, GL_FLOAT, GL_FALSE, 0}}}}};
    vaQuad = std::make_unique<glowl::Mesh>(vertexDataQuad, quadIndices, GL_UNSIGNED_INT, GL_TRIANGLE_STRIP);

    loadDataFile(0);

    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

HeightField::~HeightField() {
    if (texHF > 0) {
        glDeleteTextures(1, &texHF);
        texHF = 0;
    }
}

void HeightField::renderGUI() {
    bool lightChanged = false;
    if (ImGui::CollapsingHeader("HeightField", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Combo("HF File", &currentFileSelection, datFilesGuiString.c_str());
        ImGui::Combo("Filter", &filterId, "GrayValue\0Normal\0Relief\0GaussCurv\0");
        ImGui::SliderFloat("LengthScale", &hfLengthScale, 1.0f, 1000.0f);
        lightChanged |= ImGui::InputFloat3("LightDir", glm::value_ptr(hfLightDir));
        lightChanged |= ImGui::gizmo3D("##LightDir1", hfLightDir);
        ImGui::Text("HF File information:");
        ImGui::Text("size X:      %i", hfSizeX);
        ImGui::Text("size Y:      %i", hfSizeY);
        ImGui::Text("min. height: %f", hfMinHeight);
        ImGui::Text("max. height: %f", hfMaxHeight);
    }
    // ImGui::Combo also returns true if the same entry is selected again. Only load data if value really changed.
    if (currentFileSelection != currentFileLoaded) {
        loadDataFile(currentFileSelection);
    }
    if (lightChanged) {
        hfLightDir = glm::normalize(hfLightDir);
    }
}

void HeightField::render() {
    renderGUI();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (shader == nullptr || vaQuad == nullptr || texHF == 0) {
        return;
    }

    glm::mat4 projMx = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);

    shader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texHF);
    shader->setUniform("tex", 0);
    shader->setUniform("texSize", hfSizeX, hfSizeY);
    shader->setUniform("hMin", hfMinHeight);
    shader->setUniform("hMax", hfMaxHeight);
    shader->setUniform("lengthScale", hfLengthScale);
    shader->setUniform("filterId", filterId);
    shader->setUniform("lightDir", glm::normalize(hfLightDir));
    shader->setUniform("projMx", projMx);

    vaQuad->draw();

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

void HeightField::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void HeightField::keyboard(Core::Key key, Core::KeyAction action, [[maybe_unused]] Core::Mods mods) {
    if (action != Core::KeyAction::Press && key == Core::Key::R) {
        std::cout << "Reload shaders!" << std::endl;
        initShaders();
    }
}

void HeightField::initShaders() {
    try {
        shader = std::make_unique<glowl::GLSLProgram>(glowl::GLSLProgram::ShaderSourceList{
            {glowl::GLSLProgram::ShaderType::Vertex, getStringResource("shader.vert")},
            {glowl::GLSLProgram::ShaderType::Fragment, getStringResource("shader.frag")}});
    } catch (glowl::GLSLProgramException& e) {
        shader = nullptr;
        std::cerr << "Error compiling shader:" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

void HeightField::loadDataFile(int idx) {
    currentFileLoaded = idx;

    if (texHF > 0) {
        glDeleteTextures(1, &texHF);
        texHF = 0;
    }

    if (idx < 0 || idx >= static_cast<int>(datFiles.size())) {
        std::cerr << "Invalid file index!" << std::endl;
        return;
    }

    auto size = std::filesystem::file_size(datFiles[idx]);
    if (size < 12) {
        std::cerr << "Bad file format!" << std::endl;
        return;
    }

    std::ifstream file(datFiles[idx], std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Cannot open file!" << std::endl;
        return;
    }

    int32_t w = 0;
    int32_t h = 0;
    int32_t c = 0;
    file.read(reinterpret_cast<char*>(&w), sizeof(w));
    file.read(reinterpret_cast<char*>(&h), sizeof(h));
    file.read(reinterpret_cast<char*>(&c), sizeof(c));

    if (w * h * sizeof(float) + 3 * sizeof(int32_t) != size || c != 1) {
        std::cerr << "Bad file format!" << std::endl;
        return;
    }

    std::vector<float> data(w * h);
    file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(w * h * sizeof(float)));

    hfMinHeight = std::numeric_limits<float>::max();
    hfMaxHeight = std::numeric_limits<float>::lowest();
    for (const auto& v : data) {
        if (v > hfMaxHeight) {
            hfMaxHeight = v;
        }
        if (v < hfMinHeight) {
            hfMinHeight = v;
        }
    }

    glGenTextures(1, &texHF);
    glBindTexture(GL_TEXTURE_2D, texHF);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, w, h, 0, GL_RED, GL_FLOAT, data.data());
    glBindTexture(GL_TEXTURE_2D, 0);
    hfSizeX = w;
    hfSizeY = h;
}
