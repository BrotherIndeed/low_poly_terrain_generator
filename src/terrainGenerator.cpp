
#include"includes.cpp"

class Cube
{
public:
    // settings
    float speed = 5;
    int chunk_size = 6;
    int indices_size=0;

    GLFWwindow* window;
    unsigned int texture1, texture2;
    Shader ourShader;
    unsigned int VBO, VAO, EBO;
    glm::vec3 cubePositions[sizeof(glm::vec3)*10] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
int init(GLFWwindow *window1)
{
    window = window1;

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // build and compile our shader program
    // ------------------------------------

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // std::vector<float>  vertices = {
        //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        //     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        //     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        //     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        //     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        //     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        //     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    // };

    std::vector<float>  vertices = {
        0.5f,  0.0f,0.5f, 
        0.5f, 0.0f,-0.5f, 
        -0.5f, 0.0f,-0.5f, 
        -0.5f,  0.0f,0.5f, 
    };
    
    std::vector<unsigned int> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // std::vector<float>  vertices;

    // for(int i=0;i<chunk_size*chunk_size;i++)
    // {
        // vertices.push_back(1.0f*i);
        // vertices.push_back(1.0f*i*i);
        // vertices.push_back(2.0f*i*i*i);
        // vertices.push_back(1.0f*i*i);
        // vertices.push_back(0.5f*i*i*i);
    // }


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int) , indices.data(), GL_STATIC_DRAW);
    indices_size = indices.size();

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    ourShader.Shader_init("7.4.camera.vs", "7.4.camera.fs");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); 
    ourShader.setInt("texture1", 0);
    // ourShader.setInt("texture2", 1);


glm::mat4 view;
view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
  		   glm::vec3(0.0f, 0.0f, 0.0f), 
  		   glm::vec3(0.0f, 1.0f, 0.0f));
glEnable(GL_DEPTH_TEST);
return 0;
}

int run()
{

         // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            // model = glm::translate(model, cubePositions[i]);
            
            // float angle = 20.0f * i;

            // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  

            ourShader.setMat4("model", model);

            // glDrawArrays(GL_TRIANGLES, 0, 36);
             glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------

    

    // optional: de-allocate all resources once they've outlived their purpose:
    return 0;
}

int terminate()
{
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    return 0;
}
};