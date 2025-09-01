#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int initGlfw() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    return 0;
}

GLFWwindow* createWindow(int width, int height, const char* title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    );
    
    return window;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void getShaderCompilationInfo(unsigned int shaderId) {
    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void getProgramLinkingInfo(unsigned int programId) {
    int success;
    char infoLog[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

unsigned int createProgram() {
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    unsigned int vertexShderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShderId);
    getShaderCompilationInfo(vertexShderId);

    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderId);
    getShaderCompilationInfo(fragmentShaderId);

    unsigned int shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);
    getProgramLinkingInfo(shaderProgramId);
    glUseProgram(shaderProgramId);
    glDeleteShader(vertexShderId);
    glDeleteShader(fragmentShaderId);

    return shaderProgramId;
}

void loadTriangle(float vertices[]) {
}

int main() {
    int glfwInitResult = initGlfw();

    GLFWwindow* window = createWindow(800, 600, "3D Playground");

    GLuint shaderProgramId = createProgram();

    /*
    // float vertices[] = {
    //    -0.5f, -0.0f, 0.0f,
    //    -0.1f, 0.5f, 0.0f,
    //    -0.1f, -0.5f, 0.0f,

    //    0.5f, 0.0f, 0.0f,
    //    0.1f, 0.5f, 0.0f,
    //    0.1f, -0.5f, 0.0f,
    // };
    // unsigned int indices[] = {
    //     0, 1, 2,
    //     3, 4, 5
    // };

    // GLuint VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // // 2) VBO: bind & upload, then define attrib format
    // GLuint VBO;
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // // 3) EBO: bind & upload **while VAO is still bound**
    // GLuint EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glUseProgram(shaderProgramId);
    // glBindVertexArray(VAO);
    // glEnableVertexAttribArray(0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    */

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // loadTriangle([
        //     0.0f, 0.0f, 0.0f,
        //     -0.5f, -0.5f, 0.0f,
        //     0.5f, -0.5f, 0.0f
        // ]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
