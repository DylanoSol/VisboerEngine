#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rendering/ShaderContainer.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
     0.5f,  0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f,  
    -0.5f,  0.5f, 0.0f   
};
unsigned int indices[] = {  
    0, 1, 3,  
    1, 2, 3   
};

ShaderContainer* shader = nullptr; 

int main()
{
   
    //Initialize the window using OpenGL 4.6 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create OpenGL window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Visboer", NULL, NULL);
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
  
    //Set up shader
    shader = new ShaderContainer("Shaders/testShader.vert", "Shaders/testShader.frag"); 

    //Set up VAO
    unsigned int VAO; 
    glGenVertexArrays(1, &VAO); 

    glBindVertexArray(VAO); 

    //Set up VBO
    unsigned int VBO; 
    glGenBuffers(1, &VBO); 

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    //Set up indices
    unsigned int EBO; 
    glGenBuffers(1, &EBO); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    //Set up vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    //Initialize ImGui
    ImGui::CreateContext(); 
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGui_ImplGlfw_InitForOther(window, true); 
    ImGui_ImplOpenGL3_Init("#version 460"); 

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
    
        processInput(window);

        //Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //ImGui start frame
        ImGui_ImplOpenGL3_NewFrame(); 
        ImGui_ImplGlfw_NewFrame(); 
        ImGui::NewFrame(); 
        
        //Draw triangle
        shader->UseShader(); 
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

        //ImGui update
        ImGui::Begin("Hello ImGui"); 
        ImGui::End(); 
        
        ImGui::ShowDemoWindow();

        //Deselect vertex array
        glBindVertexArray(0);

        //ImGui Render
        ImGui::Render(); 
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 

        //Swap buffer and poll input output
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Shut down ImGui
    ImGui_ImplOpenGL3_Shutdown(); 
    ImGui_ImplGlfw_Shutdown(); 
    ImGui::DestroyContext(); 

    //Deallocate resources
    glDeleteVertexArrays(1, &VAO); 
    glDeleteBuffers(1, &VBO); 
    glDeleteBuffers(1, &EBO); 

    //Remove all resources
    delete shader; 

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_APOSTROPHE) == GLFW_PRESS)
        shader->RecompileShader(); 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}