#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Temp hard coded vertex shader
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Temp hard coded fragment shader
const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor; \n"
"void main() \n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\0"; 

float vertices[] =
{
     -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

int main()
{
   
    //Initialize the window using OpenGL 4.6 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create OpenGL window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Select created window
    glfwMakeContextCurrent(window);

    //On resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Load OpenGL function pointers through GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //OpenGL hello triangle

    //Set up VAO
    unsigned int VAO; 
    glGenVertexArrays(1, &VAO); 

    glBindVertexArray(VAO); 

    //Set up VBO
    unsigned int VBO; 
    glGenBuffers(1, &VBO); 

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    //Set up vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0); 

    //Set up vertex shader
    unsigned int vertexShader; 
    vertexShader = glCreateShader(GL_VERTEX_SHADER); 

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
    glCompileShader(vertexShader); 

    //Set up fragment shader
    unsigned int fragmentShader; 
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
    glCompileShader(fragmentShader); 

    //Create shader program
    unsigned int shaderProgram; 
    shaderProgram = glCreateProgram(); 

    //Set up shader program
    glAttachShader(shaderProgram, vertexShader); 
    glAttachShader(shaderProgram, fragmentShader); 

    glLinkProgram(shaderProgram); 

    glUseProgram(shaderProgram); 

    //Delete shaders after linking
    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader); 

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
    
        processInput(window);

        //Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Draw triangle
        glUseProgram(shaderProgram); 
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3); 

        //Swap buffer and poll input output
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Remove all resources
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}