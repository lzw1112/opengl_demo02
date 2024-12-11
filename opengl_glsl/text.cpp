/* ������Ӧ�Ŀ� */
#include <iostream>
#define GLEW_STATIC	
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include "Shader.hpp"

/* ��д������λ������ɫ */
GLfloat vertices_1[] =
{	// position				// color
	0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		// �϶���(��ɫ)
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		// �󶥵�(��ɫ)
	0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f		// �Ҷ���(��ɫ)
};



int main()
{
	/* ��ʼ�� */
	glfwInit();
	GLFWwindow* window_1 = glfwCreateWindow(800,600, "A Beautiful Triangle", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	glfwMakeContextCurrent(window_1);
	glewInit();

	/* ��ɫ���ı������� */
	const GLchar *file_1 = "shader_v.txt";
	const GLchar* file_2 = "shader_f.txt";
	Shader ourShader = Shader(file_1, file_2);
	std::ifstream ifstr_1(file_1);
	std::ifstream ifstr_2(file_2);
	
	if (!ifstr_1.is_open() || !ifstr_2.is_open())
	{
		std::string error = "�ļ���ʧ��";
		throw(error);
	}
	/* ���ö��㻺�����(VBO) + ���ö����������(VAO)  */
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

	// draw loop ��ͼѭ��
	while (!glfwWindowShouldClose(window_1))
	{
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*  �ھŲ������������� */
		ourShader.Use();					// ͼ����Ⱦ
		glBindVertexArray(VAO);				// �� VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);	// ��������  �ӵ�0�����㿪ʼ һ����3��
		glBindVertexArray(0);				// ���

		glfwSwapBuffers(window_1);
	}

	glDeleteVertexArrays(1, &VAO);			// �ͷ���Դ	
	glDeleteBuffers(1, &VBO);
	glfwTerminate();						// ����
	return 0;
}
