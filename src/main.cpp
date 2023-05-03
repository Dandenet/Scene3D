#include <GL/glew.h>

#include <SFML/Window.hpp>

#include "graphics/Shader.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Vertex.hpp"

#include <iostream>

void TestFunction()
{
    switch (glGetError())
    {
    case GL_NO_ERROR:
        std::cout << "ok!" << std::endl;
        break;

    case GL_INVALID_ENUM:
        std::cout << "GL_INVALID_ENUM!" << std::endl;
        break;

    case GL_INVALID_VALUE:
        std::cout << "GL_INVALID_VALUE!" << std::endl;
        break;

    case GL_INVALID_OPERATION:
        std::cout << "GL_INVALID_OPERATION!" << std::endl;
        break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION!" << std::endl;
        break;

    case GL_OUT_OF_MEMORY:
        std::cout << "GL_OUT_OF_MEMORY!" << std::endl;
        break;

    case GL_STACK_UNDERFLOW:
        std::cout << "GL_STACK_UNDERFLOW!" << std::endl;
        break;


    default:
        std::cout << "UNDEFINED ERROR!" << std::endl;
        break;
    }
}

int main()
{
    sf::Window window(sf::VideoMode(1280, 720), "Scene3D");
    glewInit();

    graphics::Shader shader;
    bool success = shader.loadFromFile("res/shader.vert", "res/shader.frag");
    if (!success)
        return -1;

    graphics::Vertex vertices[3] = {
        graphics::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f),    glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f)),
        graphics::Vertex(glm::vec3(0.0f, 0.5f, 0.0f),      glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f)),
        graphics::Vertex(glm::vec3(0.5f, -0.5f, 0.0f),     glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f)),
    };

    unsigned int indices[3] = { 0, 1, 2 };


    graphics::Mesh mesh;
    mesh.create(3, 3);
    mesh.update(vertices, indices);

    shader.bind();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.setActive();

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.drawElements(GL_TRIANGLES);
        window.display();
    }

    return 0;
}
