#include "terrainGenerator.cpp"



int main()
{    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow*  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Terrain generator", NULL, NULL);


    Cube ourcube(window);
     while (!glfwWindowShouldClose(window))
    {

    ourcube.run();

    }
    ourcube.terminate();
    return 0;
}