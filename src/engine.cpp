#include "terrainGenerator.cpp"

class Engine
{
    public:
    GLFWwindow*  window;
    Cube ourcube;
    Cube ourcube2;
    int init()
    {    
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Terrain generator", NULL, NULL);

        ourcube.init(window);
        ourcube2.init(window);
        return 0;
    }

    int run()
    { 
        while (!glfwWindowShouldClose(window))
        {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        processInput(window);
        glfwGetCursorPos(window, &xpos, &ypos);
        // render
        glClearColor(0.594f, 0.8078f, 0.9216f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!



        ourcube.run();
        ourcube2.run();

        glfwSwapBuffers(window);
        glfwPollEvents();
        }

        return 0;
    }
    
    int terminate()
    {
        
        ourcube.terminate();
        ourcube2.terminate();
        
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }
};