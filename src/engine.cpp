#include "terrainGenerator.cpp"

class Engine
{
    public:
    GLFWwindow*  window;
    std::vector<Cube> chunk_memory;
    Cube ourcube;
    // Cube ourcube2;
    int chunk_size = 800;

    int init()
    {    
        glfwInit();
        // chunk_memory.pushback
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Terrain generator", NULL, NULL);
        // chunk_memory.push_back(ourcube);
        ourcube.init(window,0,0,chunk_size);
        // ourcube2.init(window,-1,-1,chunk_size);
        return 0;
    }

    int run()
    { 
        while (!glfwWindowShouldClose(window))
        {
        glClearColor(0.594f, 0.8078f, 0.9216f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        // if(camera.Position.x/ourcube.chunk_size>1)
        // {
        //     std::cout<<"out of bounds";
        //     ourcube.terminate();
        //     ourcube.init(window,1,0);
        // }
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        processInput(window);
        glfwGetCursorPos(window, &xpos, &ypos);
        // render


        // ourcube2.run();

        ourcube.run();
        // std::cout<<camera.Position.x<<" "<<camera.Position.y<<" "<<camera.Position.z<<" \n";

        glfwSwapBuffers(window);
        glfwPollEvents();
        }

        return 0;
    }
    
    int terminate()
    {
        
        ourcube.terminate();
        // ourcube2.terminate();

        
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }
};