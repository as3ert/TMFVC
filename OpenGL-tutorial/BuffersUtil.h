
#include <glad/glad.h>

class VertexBuffer
{
public:
    GLuint ID;
    VertexBuffer(GLfloat *vertices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    // Bind the VertexBuffer
    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }
    // Unbind the VertexBuffer
    void unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    // Delete the VertexBuffer
    void deleteVBO()
    {
        glDeleteBuffers(1, &ID);
    }
};

class ElementBuffer
{
public:
    GLuint ID;
    ElementBuffer(GLuint *indices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    // Bind the ElementBuffer
    void bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    // Unbind the ElementBuffer
    void unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // Delete the ElementBuffer
    void deleteEBO()
    {
        glDeleteBuffers(1, &ID);
    }
};

class VertexArray
{
public:
    GLuint ID;
    VertexArray()
    {
        glGenVertexArrays(1, &ID);
    }

    // Link a VertexBuffer Attribute
    void linkAttrib(VertexBuffer &VertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
    {
        VertexBuffer.bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        VertexBuffer.unbind();
    }
    // Bind the VertexArray
    void bind()
    {
        glBindVertexArray(ID);
    }
    // Unbind the VertexArray
    void unbind()
    {
        glBindVertexArray(0);
    }
    // Delete the VertexArray
    void deleteVAO()
    {
        glDeleteVertexArrays(1, &ID);
    }
};
