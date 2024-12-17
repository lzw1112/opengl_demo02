/* ������Ӧ�Ŀ� */
#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include"Shader.hpp"
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include"SOIL2\stb_image.h"
#include"SOIL2\SOIL2.h"
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"

/* ��д������λ�� */
GLfloat vertices_1[] =
{
	//position				// color				// texture_1 coords(��������)
	1.0f, 3.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 2.0f,			// ���϶���		���0
	1.0f, -3.0, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, -1.0f,		// ���¶���		���1
	-1.0f, -3.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, -1.0f,		// ���¶���		���2
	-1.0f, 3.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f			// ���϶���		���3
	// ������������ķ�Χ���� (0, 0) �� (1, 1) �Ĳ��ֻᱻ���� �������ơ� ��������
};

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
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Transform test", nullptr, nullptr);
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

	/* ��ȡ���� */
	int width, height;
	unsigned char* image_1 = SOIL_load_image("539c12973a64ffa9b3072e7e3a13c22c.png", &width, &height, 0, SOIL_LOAD_RGBA);			// ��ȡͼƬ
	cout << "width = " << width << ", height = " << height << endl;
	unsigned char* image_2 = SOIL_load_image("f28ff346a208fb23732a3126dd3e1c63.png", &width, &height, 0, SOIL_LOAD_RGBA);
	cout << "width = " << width << ", height = " << height << endl;

	/* ����������ѩ��ͼ1 */
	GLuint texture_1;
	glGenTextures(1, &texture_1);				// �������������Ϊ 1
	glBindTexture(GL_TEXTURE_2D, texture_1);	// ���� GL_TEXTURE_2D ��
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_1);
	glGenerateMipmap(GL_TEXTURE_2D);	// ��㽥������

	/* ����������ѩ��ͼ2 */
	GLuint texture_2;
	glGenTextures(1, &texture_2);
	glBindTexture(GL_TEXTURE_2D, texture_2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_2);
	glGenerateMipmap(GL_TEXTURE_2D);	// ��㽥������

	/* �ͷ�ͼ���ڴ� */
	SOIL_free_image_data(image_1);
	SOIL_free_image_data(image_2);

	/* �����Ʒ�ʽ */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// S ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// T ����

	/* ������� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* ���� uniform ���� */
	ourShader.Use(); // don't forget to activate/use the shader before setting uniforms!
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture_1"), 0);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture_2"), 1);

	int cnt = 0;				// ������
	int flag = 1;				// �����л���־
	int N = 2000;				// N Խ��λ��/������ٶȶ������
	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window_1))
	{
		/* �ӿ� + ʱ�� */
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* ���� + ������ */
		glActiveTexture(GL_TEXTURE0);				// ���� 0 ������Ԫ����� 16 ��ͨ��
		glBindTexture(GL_TEXTURE_2D, texture_1);	// �����������ǰ���������Ŀ��
		glActiveTexture(GL_TEXTURE1);				// ���� 1 ������Ԫ����� 16 ��ͨ��
		glBindTexture(GL_TEXTURE_2D, texture_2);	// �����������ǰ���������Ŀ��

		/* ÿһ��ѭ������ķ�Ӧ */
		cnt = cnt + 1;		// ��������1
		if (cnt >= 2 * N)
			cnt = 0;		// �����ظ�ѭ��
		if (cnt == 0 || cnt == N)
			flag = -flag;	// ��������ѭ�������־

		/* ƽ�Ʊ任��ʵ�� */
		glm::mat4 firsrMatrix_1 = glm::mat4(1.0f); // ��ʼ��Ϊ��λ����
		glm::mat4 transform_1 = glm::translate(firsrMatrix_1, glm::vec3(0.0f, 1.0f - cnt * 1.0 / N, 0.0f));

		/* ����任��ʵ�� */
		int vertexColorLocation = glGetUniformLocation(ourShader.Program, "time");	// �ҵ� ��time�� ������
		if (flag == 1)
			glUniform1f(vertexColorLocation, cnt * 1.0 / N);			// ������1 �𽥽��浽 ����2
		else
			glUniform1f(vertexColorLocation, 2.0 - cnt * 1.0 / N);		// ������2 �𽥽��浽 ����1

		// get matrix's uniform location and set matrix
		unsigned int transformLoc = glGetUniformLocation(ourShader.Program, "transform_1");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_1));

		/* ����ͼ�� */
		//ourShader.Use();
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
