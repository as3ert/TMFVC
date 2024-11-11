#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glowl/glowl.h>

#include "core/PluginRegister.h"
#include "core/RenderPlugin.h"

namespace OGL4Core2::Plugins::TMFVC::HeightField {

    class HeightField : public Core::RenderPlugin {
        REGISTERPLUGIN(HeightField, 202) // NOLINT

    public:
        static std::string name() {
            return "TMFVC/HeightField";
        }

        explicit HeightField(const Core::Core& c);
        ~HeightField() override;

        void render() override;
        void resize(int width, int height) override;
        void keyboard(Core::Key key, Core::KeyAction action, Core::Mods mods) override;

    private:
        void renderGUI();

        void initShaders();

        void loadDataFile(int idx);

        std::vector<std::filesystem::path> datFiles;
        std::string datFilesGuiString;
        int currentFileLoaded;
        int currentFileSelection;

        int filterId;         // filter for different visualizations
        int hfSizeX;          // horizontal data resolution
        int hfSizeY;          // vertical data resolution
        float hfMinHeight;    // minimum value
        float hfMaxHeight;    // maximum value
        float hfLengthScale;  // length scale for grid
        glm::vec3 hfLightDir; // light source direction

        std::unique_ptr<glowl::GLSLProgram> shader;
        std::unique_ptr<glowl::Mesh> vaQuad;

        GLuint texHF; // texture handle for height data.
    };
} // namespace OGL4Core2::Plugins::TMFVC::HeightField
