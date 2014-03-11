#include <SFML/Window.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

int main() {
    // setup the window & OpenGL context (implicitly created by SFML)
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Close|sf::Style::Resize);

    // use GLEW to check for available OpenGL version
    glewExperimental = GL_TRUE;
    glewInit();

    // test correct setup
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    printf("%u\n", vertexBuffer); // should print "1"

    // event loop
    bool running = true;
    while (running) {
        sf::Event windowEvent;

        while (window.pollEvent(windowEvent)) {
            switch (windowEvent.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed:
                    if (windowEvent.key.code == sf::Keyboard::Escape)
                        running = false;
                    break;
            }

        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers
        window.display();
    }

    return 0;
}
