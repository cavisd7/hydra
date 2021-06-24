#include <iostream>
// GLAD must be before GLFW 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"


int main(void) {
    if (!glfwInit()) { 
	    std::cout << "[ERROR] Failed to initialize GLFW!" << std::endl;

        return -1;
    };

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

    //Data
    float positions[6] = {
	    -0.5f, -0.5f, //vertex
	     0.0f,  0.5f, //vertex
	     0.5f, -0.5f //vertex 
    };

    //ID of generated buffer 
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    //select buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //Add data to buffer 
    //Also allocates buffer on GPU that will hold data
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    
    Shader shader("../res/shaders/basic");
    shader.Bind();
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Draw call 
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}

