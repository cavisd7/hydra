#include <iostream>
// GLAD must be before GLFW 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

int main(void) {
    if (!glfwInit()) { 
	    std::cout << "[ERROR] Failed to initialize GLFW!" << std::endl;

        return -1;
    };

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Sol", NULL, NULL);
    if (!window)
    {
        glfwTerminate();

        return -1;
    }

    glfwSetWindowTitle(window, "Sol");

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    std::cout << "[ERROR] Failed to initialize GLAD" << std::endl;

	    return -1;
    };

    std::cout << glGetString(GL_VERSION) << std::endl;

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float positions[] = {
	    -0.5f, -0.5f,
         0.5f, -0.5f,
	     0.5f,  0.5f,
	    -0.5f,  0.5f  
    };

    VertexBuffer vb(8 * sizeof(float), positions);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    IndexBuffer ib(6, indicies);

    Shader shader("../res/shaders/basic");
    shader.Bind();

    float r = 0.0f;
    float inc = 0.02f;  
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.1f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        shader.SetUniform4f("u_Color", r, 0.3f, 0.1f, 1.0f);
        
        glBindVertexArray(vao);
        ib.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1.0f) {
            inc = -0.02f;
        } else if(r < 0.0f) {
            inc = 0.02f;
        }

        r += inc;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

