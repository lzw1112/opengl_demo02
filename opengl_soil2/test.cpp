/* ������Ӧ�Ŀ� */
#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include"Shader.hpp"
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include"SOIL2\stb_image.h"
#include"SOIL2\SOIL2.h"

int width, height;

//* (����һ��ľ��) ��д������λ��  + ��ȡ���� */
//GLfloat vertices_1[] =
//{
//	//position				// color				// texture coords(��������)
//	0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		// ���϶���		���0
//	0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		// ���¶���		���1
//	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// ���¶���		���2
//	-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f		// ���϶���		���3
//};
//unsigned char* image = SOIL_load_image("��Ļ��ͼ 2024-12-13 161814.png", &width, &height, 0, SOIL_LOAD_RGBA);			// ��ȡͼƬ


GLfloat vertices_1[] =
{
	//position				// color				// texture coords(��������)
	1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 2.0f,		// ���϶���		���0
	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 0.0f,		// ���¶���		���1
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// ���¶���		���2
	-1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f		// ���϶���		���3
};
unsigned char* image = SOIL_load_image("���ܷ��ֽ������-è��.png", &width, &height, 0, SOIL_LOAD_RGBA);			// ��ȡͼƬ
/*(��������4ֻè)��д������λ�� + ��ȡ���� * /

GLfloat vertices_1[] =
{
	//position				// color				// texture coords(��������)
	1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 2.0f,		// ���϶���		���0
	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 0.0f,		// ���¶���		���1
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// ���¶���		���2
	-1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f		// ���϶���		���3
};
unsigned char* image = SOIL_load_image("T_image3.png", &width, &height, 0, SOIL_LOAD_RGBA);			// ��ȡͼƬ


/* �ĸ������������Ϣ������ */
GLuint indices_1[] =
{
	0, 1, 3,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
	1, 2, 3			// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
};

const GLint WIDTH = 600, HEIGHT = 600;

int main()
{
	glfwInit();
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Texture test", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	cout << "screenWidth_1 = " << screenWidth_1 << ", screenHeight = " << screenHeight_1 << endl;
	glfwMakeContextCurrent(window_1);
	glewInit();

	/* �������Լ����õ���ɫ���ı������� */
	Shader ourShader = Shader("shader_v.txt", "shader_f.txt");		// ���·��

	/* ���ö��㻺�����(VBO) + ���ö����������(VAO) + �����������(EBO)  */
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);

	/* �������Ӷ������� */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	// ͨ�� 0 ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);	// ͨ�� 1 ��
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);	// ͨ�� 2 ��


	/* �������� */
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);			// ��ȡͼƬ��Ϣ
	glGenerateMipmap(GL_TEXTURE_2D);	// ��㽥������
	SOIL_free_image_data(image);

	/* �����Ʒ�ʽ */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// S ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);	// T ����

	/* ������� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* ����Ԫ����һ���ص�ʹ�� */
	ourShader.Use();	// don't forget to activate/use the shader before setting uniforms!
	int textureLocation = glGetUniformLocation(ourShader.Program, "ourTexture");	// �ҵ���ɫ���� uniform ���Ե���Ϊ"ourTexture"�����������
	glUniform1i(textureLocation, 0);		// ���� OpenGL ����ɫ�������������ĸ�����Ԫ	

	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window_1))
	{
		/* �ӿ� + ʱ�� */
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* �������� */
		glActiveTexture(GL_TEXTURE0);			// ���� 0 ������Ԫ����� 16 ��ͨ��
		glBindTexture(GL_TEXTURE_2D, texture);	// �����������ǰ���������Ŀ��			

		/* ����ͼ�� */
		ourShader.Use();
		glBindVertexArray(VAO);									// �� VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// �� EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// ������������ �ӵ�0�����㿪ʼ һ����6��
		glBindVertexArray(0);									// ��� VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// ��� EBO
		glBindTexture(GL_TEXTURE_2D, 0);						// ��� ����

		/* �������� */
		glfwSwapBuffers(window_1);
	}

	/* �ͷ���Դ */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteBuffers(1, &EBO);

	glfwTerminate();	// ����
	return 0;
}
