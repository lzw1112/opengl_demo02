/* ������Ӧ�Ŀ� */
#include <iostream>
#define GLEW_STATIC	
#include"Shader.hpp"
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include"SOIL2\stb_image.h"
#include"SOIL2\SOIL2.h"
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"

// ��Ȳ���

/* ��д������λ�� */
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

int main()
{
	/* ��ʼ�� */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// ����ϵͳ �汾��Ϊ��opengl��ͼ׼����  ֧��3.0�Ժ�İ汾 ���µ�  3.3
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// must for Mac(Windows�ɲ���) ��������
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						// ���Źر�

	/* ���ڲ����봦�� */
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "NJUPT_Learn OpenGL Earth-moon System", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	std::cout << "screenWidth_1 = " << screenWidth_1 << ", screenHeight = " << screenHeight_1 << std::endl;
	glewExperimental = GL_TRUE;
	glfwMakeContextCurrent(window_1);
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

	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window_1))
	{
		/* �ӿ� + ʱ�� */
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* ����ͼ�� */
		ourShader.Use();
		glBindVertexArray(VAO);
		for (int i = 0; i < 2; i++)
		{
			GLfloat time = glfwGetTime();	// ��ȡʱ��
			glm::mat4 transform_1;
			if (i == 0)					// ��������
			{
				transform_1 = glm::scale(transform_1, glm::vec3(0.6f, 0.6f, 0.6f));
				transform_1 = glm::rotate(transform_1, time, glm::vec3(0.2f, 1.0f, 0.0f));
			}
			else							// С������
			{
				transform_1 = glm::translate(transform_1, glm::vec3(0.8f * cos(time), 0.8f * sin(time), 0.0f));
				transform_1 = glm::scale(transform_1, glm::vec3(0.15f, 0.15f, 0.15f));
				transform_1 = glm::rotate(transform_1, time, glm::vec3(0.5f, 0.5f, 0.0f));
			}

			int transform_1_Location = glGetUniformLocation(ourShader.Program, "transform_1");
			glUniformMatrix4fv(transform_1_Location, 1, GL_FALSE, glm::value_ptr(transform_1));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);				// ��� VAO
		/* �������� */
		glfwSwapBuffers(window_1);
	}

	/* �ͷ���Դ */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();	// ����
	return 0;
}
