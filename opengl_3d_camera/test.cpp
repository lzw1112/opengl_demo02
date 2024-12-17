#include <iostream>

#define GLEW_STATIC	
#include"Shader.hpp"
#include"Camera.hpp"
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include"SOIL2\stb_image.h"
#include"SOIL2\SOIL2.h"
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"

float vertices_1[] = {
    // x��y��z ����				// color
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	// red ��ɫ��
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	// green ��ɫ��
     0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,	// blue ��ɫ��
    -0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,	// yellow ��ɫ��
     0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	// purple ��ɫ��
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,	// cyan ��ɫ��
     0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
};

const GLint WIDTH = 600, HEIGHT = 600;

bool keys[1024];				// ר�Ŵ洢�����ļ�
Camera camera(glm::vec3(1.0f, 1.0f, -5.0f), glm::vec3(-1.0f, -1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);		// �Լ��̵���Ӧ����
void Key_Movement();			// �� Camera �໥���ĺ���
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

int main()
{
    std::cout << "opengl_3d_camera"<<"\n";
    /* ��ʼ�� glfw */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						// ���Źر�

    /* ���ڲ����봦�� */
    GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "NJUPT_Learn OpenGL Key Test", nullptr, nullptr);
    int screenWidth_1, screenHeight_1;
    glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
    std::cout << "screenWidth_1 = " << screenWidth_1 << ", screenHeight = " << screenHeight_1 << std::endl;
    glfwMakeContextCurrent(window_1);
    glfwSetKeyCallback(window_1, KeyCallback);		// ע�ᵽ glfw ���棬�����������Ӧ

    /* ��ʼ�� glew */
    glewInit();

    /* ������Ȳ��� */
    glEnable(GL_DEPTH_TEST);

    /* �������Լ����õ���ɫ���ı������� */
    Shader ourShader = Shader("shader_v.txt", "shader_f.txt");		// ���·��

    /* ���ö��㻺�����(VBO) + ���ö����������(VAO) */
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

    /* �������Ӷ������� */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);	// ͨ�� 0 ��
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);	// ͨ�� 1 ��

    while (!glfwWindowShouldClose(window_1))
    {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        /* �ӿ� + ʱ�� */
        glViewport(0, 0, screenWidth_1, screenHeight_1);
        glfwPollEvents();		// ��ȡ�������
        Key_Movement();			// ��ȡ���̵�С����

        /* ��Ⱦ + �����ɫ���� */
        glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ����ͼ�� */
        ourShader.Use();					// ������ɫ������
        glBindVertexArray(VAO);				// �� VAO

        for (int i = 0; i < 2; i++)
        {
            glm::mat4 transform_1;
            glm::mat4 view_1 = camera.Getviewmatrix();
            if (i == 0)
            {
                transform_1 = glm::translate(transform_1, glm::vec3(0.0f, 0.0f, 0.0f));
                float new_size = cos(currentTime) * 0.2f + 0.8f;
                transform_1 = glm::scale(transform_1, glm::vec3(new_size, new_size, new_size));
            }
            else				// С������
            {
                transform_1 = glm::translate(transform_1, glm::vec3(0.0f, 1.0f, 0.0f));
                transform_1 = glm::rotate(transform_1, currentTime, glm::vec3(0.2f, 1.0f, 0.0f));
                transform_1 = glm::scale(transform_1, glm::vec3(0.15f, 0.15f, 0.15f));
            }

            glm::mat4 projection_1 = glm::perspective(glm::radians(45.0f), (float)screenWidth_1 / (float)screenHeight_1, 0.1f, 100.0f);

            int transform_1_Location = glGetUniformLocation(ourShader.Program, "transform_1");
            glUniformMatrix4fv(transform_1_Location, 1, GL_FALSE, glm::value_ptr(transform_1));

            int projection_1_Location = glGetUniformLocation(ourShader.Program, "projection_1");
            glUniformMatrix4fv(projection_1_Location, 1, GL_FALSE, glm::value_ptr(projection_1));

            int view_1_Location = glGetUniformLocation(ourShader.Program, "view_1");
            glUniformMatrix4fv(view_1_Location, 1, GL_FALSE, glm::value_ptr(view_1));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);				// ��� VAO

        /* �������� */
        glfwSwapBuffers(window_1);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();	// ����
    return 0;
}
    void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
            std::cout << "�����˹رռ� esc = " << key << std::endl;
        }
        if (key >= 0 && key <= 1024)
        {
            if (action == GLFW_PRESS)
                keys[key] = true;	// true �������˼�
            else if (action == GLFW_RELEASE)
                keys[key] = false;
        }
    }

    void Key_Movement()
    {
        if (keys[GLFW_KEY_Q])		// ��ǰ
            camera.Processkeyboard(FORWARD, deltaTime);

        if (keys[GLFW_KEY_E])		// ���
            camera.Processkeyboard(BACKWARD, deltaTime);

        if (keys[GLFW_KEY_A])		// ����
            camera.Processkeyboard(LEFT, deltaTime);

        if (keys[GLFW_KEY_D])		// ����
            camera.Processkeyboard(RIGHT, deltaTime);

        if (keys[GLFW_KEY_W])		// ����
            camera.Processkeyboard(UPWARD, deltaTime);

        if (keys[GLFW_KEY_S])		// ����
            camera.Processkeyboard(DOWNWARD, deltaTime);
    }
 
