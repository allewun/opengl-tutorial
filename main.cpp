#include <SFML/Window.hpp>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>



// Shaders
const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;"
    "void main() {"
    "   gl_Position = vec4(position, 0.0, 1.0);"
    "}";

const GLchar* fragmentSource =
    "#version 150 core\n"
    "out vec4 outColor;"
    "void main() {"
    "   outColor = vec4(1.0, 1.0, 1.0, 1.0);"
    "}";


int main() {
    // setup the window & OpenGL context (implicitly created by SFML)
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Close|sf::Style::Resize);

    // use GLEW to check for available OpenGL version
    glewExperimental = GL_TRUE;
    glewInit();

    printf("[OpenGL : v%s]\n[GLSL   : %s]\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));



    // define vertices of triangle
    GLfloat vertices[] = {
         0.0f,  0.5f, // vertex 1 (X,Y)
         0.5f, -0.5f, // vertex 2 (X,Y)
        -0.5f, -0.5f  // vertex 3 (X,Y)
    };

    // create vertex array object (stores links betweens attributs and VBOs)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create vertex buffer object and copy vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // create vertex shader and compile it
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // create fragment shader and compile it
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Combine shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // "Since a fragment shader is allowed to write to multiple buffers,
    // you need to explicitly specify which output is writing to which buffer.
    // This needs to happen before linking the program. However, since this is
    // 0 by default and there's only one output right now, the following line
    // of code is not necessary"
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram); // only 1 program can be active at a time

    // specify how attributes are formatted and ordered (vertex data layout)
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);


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
                default: running = true;
            }

        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers
        window.display();


    }

    // clean-up
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    return 0;
}
