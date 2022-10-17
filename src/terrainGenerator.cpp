
#include"includes.cpp"
class Cube
{
public:
    // settings
    float speed = 1;
    int scale=10;
    int indices_size=0;

    GLFWwindow* window;
    unsigned int texture1, texture2;
    Shader ourShader;
    unsigned int VBO, VAO, EBO;
int numX = 512,
    numY = 512,
    numOctaves = 7;
double persistence = 0.55;
int chunk_size2 = 100;
#define maxPrimeIndex 10
int primeIndex = 0;

int primes[maxPrimeIndex][3] = {
  { 995615039, 600173719, 701464987 },
  { 831731269, 162318869, 136250887 },
  { 174329291, 946737083, 245679977 },
  { 362489573, 795918041, 350777237 },
  { 457025711, 880830799, 909678923 },
  { 787070341, 177340217, 593320781 },
  { 405493717, 291031019, 391950901 },
  { 458904767, 676625681, 424452397 },
  { 531736441, 939683957, 810651871 },
  { 997169939, 842027887, 423882825 }
};
    
int init(GLFWwindow *window1, int chunk_x, int chunk_y, int chunk_size)
{
    // chunk_size = chunk_size/scale;
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
    std::vector<unsigned int> indices;
    std::vector<float>  vertices;

    for(int i=0;i<chunk_size;i++)
    {
        for(int j=0;j<chunk_size;j++)
        {
            
                vertices.push_back((1.0f*i*scale)+(chunk_x*chunk_size));
                float h = 20.0f * ValueNoise_2D((i*scale)+(chunk_x*chunk_size), (j*scale)+(chunk_y*chunk_size));
                if((h)>0)
                {
                    vertices.push_back(10+h*scale);
                    // std::cout<<h*scale<<std::endl;

                    // vertices.push_back(2);
                }
                else
                {
                    vertices.push_back(20+(h*scale/2));
                }
                vertices.push_back((-1.0f*j*scale)+(chunk_y*chunk_size));
                //norma
                vertices.push_back(1.0f*((   (i*i)+(j*j)   )));
        }
    }

// int poly_skip = 1;
    for( int i=0;i<(chunk_size*chunk_size)-chunk_size;i++)
    {
        if(i%chunk_size!=chunk_size-1)
        {
            indices.push_back(i);
            indices.push_back(i+1);
            indices.push_back(i+chunk_size);

            indices.push_back(i+1);
            indices.push_back(i+chunk_size);
            indices.push_back(i+chunk_size+1);

        }
    }


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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    ourShader.Shader_init("7.4.camera.vs", "7.4.camera.fs", "7.4.camera.gs");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); 
    // ourShader.setInt("texture1", 0);
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
    camera.Position.y = 100;
    // + scale *20.0f * ValueNoise_2D(camera.Position.x,camera.Position.z);

    // std::cout<<camera.Position.x<<" " <<" "<< camera.Position.y<<" "<<camera.Position.z<<"\n ";
         // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1400.0f*scale);
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


double Noise(int i, int x, int y) {
  int n = x + y * 57;
  n = (n << 13) ^ n;
  int a = primes[i][0], b = primes[i][1], c = primes[i][2];
  int t = (n * (n * n * a + b) + c) & 0x7fffffff;
  return 1.0 - (double)(t)/1073741824.0;
}

double SmoothedNoise(int i, int x, int y) {
  double corners = (Noise(i, x-1, y-1) + Noise(i, x+1, y-1) +
                    Noise(i, x-1, y+1) + Noise(i, x+1, y+1)) / 16,
         sides = (Noise(i, x-1, y) + Noise(i, x+1, y) + Noise(i, x, y-1) +
                  Noise(i, x, y+1)) / 8,
         center = Noise(i, x, y) / 4;
  return corners + sides + center;
}

double Interpolate(double a, double b, double x) {  // cosine interpolation
  double ft = x * 3.1415927,
         f = (1 - cos(ft)) * 0.5;
  return  a*(1-f) + b*f;
}

double InterpolatedNoise(int i, double x, double y) {
  int integer_X = x;
  double fractional_X = x - integer_X;
  int integer_Y = y;
  double fractional_Y = y - integer_Y;

  double v1 = SmoothedNoise(i, integer_X, integer_Y),
         v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
         v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
         v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
         i1 = Interpolate(v1, v2, fractional_X),
         i2 = Interpolate(v3, v4, fractional_X);
  return Interpolate(i1, i2, fractional_Y);
}

double ValueNoise_2D(double x, double y) {
  double total = 0,
         frequency = pow(2, numOctaves),
         amplitude = 1;
  for (int i = 0; i < numOctaves; ++i) {
    frequency /= 2;
    amplitude *= persistence;
    total += InterpolatedNoise((primeIndex + i) % maxPrimeIndex,
        x / frequency, y / frequency) * amplitude;
  }
  return total / frequency;
}
};