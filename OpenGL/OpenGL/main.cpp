#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: error handling

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "error glew init" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    //DLECLARER LES POSITIONS
    float positions[6]{
        -0.5f, -0.5f,  // X et Y d'un vertx
         0.0f, 0.5f,
         0.5f, -0.5f
    };

    //DECLARER UN UNSAGNED INT
    unsigned int buffer;

    // GENERER UN BUFFER
    glGenBuffers(1, &buffer);

    //ASSIGNERR LE BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    //AJOUTER DATA AU BUFFER
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    //ACTIVER LE VERTEX ATTRIBUS
    glEnableVertexAttribArray(0);

    //ATTRUBUS DU VERTEX (POSITION, TEXTURE ETC...)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    // 0 = l'index du bit ou se trouve les positions
    // 2 = combien de float par vertex
    // sizeof = nb de bit entre chaque vertex

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}