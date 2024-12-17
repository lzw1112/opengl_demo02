/* ������Ӧ�Ŀ� */
#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include"Shader.hpp"
#include"Camera.hpp"
#include "Point_Light.hpp"
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"
#include"glm/gtx/rotate_vector.hpp"

/* ��д������λ�� */
float vertices_1[] = {
	// x��y��z ����				// color				// normal
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// red ��ɫ��
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// green ��ɫ��
	 0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f, 	// blue ��ɫ��(����ͼ��������)
	-0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// yellow ��ɫ��
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f, 	// purple ��ɫ��
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// cyan ����ɫ��
	 0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f
};

const GLint WIDTH = 600, HEIGHT = 600;

bool keys[1024];				// ר�Ŵ洢�����ļ�
Camera camera(glm::vec3(1.0f, 1.0f, -5.0f), glm::vec3(-1.0f, -1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void Key_Movement();
void square_Movement(GLfloat&, GLfloat&, GLfloat&);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);
const double Shift_pix = 0.0005;					// �������ƶ��ٶ�
int main()
{
	/* ��ʼ�� glfw */
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);		// ���Źر�

	/* ���ڲ����봦�� */
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Light Test", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	glfwMakeContextCurrent(window_1);
	glfwSetKeyCallback(window_1, KeyCallback);

	/* ��ʼ�� glew + �������� */
	glewInit();
	Point_Light my_light = Point_Light();

	/* ��Ȳ��Կ��� */
	glEnable(GL_DEPTH_TEST);

	/* �������Լ����õ���ɫ���ı������� */
	Shader ourShader = Shader("shader_v.txt", "shader_f.txt");		// ���·��
	Shader lightShader = Shader("light_v.txt", "light_f.txt");		// ���·��

	/* ���ö��㻺�����(VBO) + ���ö����������(VAO) */
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

	/* �������Ӷ������� */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);		// ͨ�� 0 ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);		// ͨ�� 1 ��
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);		// ͨ�� 2 ��

	GLfloat up_down_move = 0.0f;		// �����ƶ��ı���
	GLfloat left_right_move = 0.0f;		// �����ƶ��ı���
	GLfloat front_back_move = 0.0f;	// ǰ���ƶ��ı���

	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window_1))
	{
		/* ʱ���ȡ */
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = (float)currentTime;

		/* �ӿ� +  ���󲶻� */
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();		// ��ȡ�������
		Key_Movement();			// ��ȡ����
		square_Movement(up_down_move, left_right_move, front_back_move);		// �������ƶ�

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* ���ջ��� */
		lightShader.Use();
		glm::mat4 my_transform = glm::mat4(1.0f);
		lightPos = glm::rotate(lightPos, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));		// ��ת
		my_transform = glm::translate(my_transform, lightPos);									// ƽ��
		my_transform = glm::scale(my_transform, glm::vec3(0.1f, 0.1f, 0.1f));					// ����
		glm::mat4 my_projection = glm::perspective(glm::radians(45.0f), (float)screenWidth_1 / (float)screenHeight_1, 0.1f, 100.0f);
		glm::mat4 my_view = camera.GetViewMatrix();	// ��ù۲����
		int my_transform_Location = glGetUniformLocation(lightShader.Program, "transform_2");
		glUniformMatrix4fv(my_transform_Location, 1, GL_FALSE, glm::value_ptr(my_transform));
		int my_projection_Location = glGetUniformLocation(lightShader.Program, "projection_2");
		glUniformMatrix4fv(my_projection_Location, 1, GL_FALSE, glm::value_ptr(my_projection));
		int my_view_Location = glGetUniformLocation(lightShader.Program, "view_2");
		glUniformMatrix4fv(my_view_Location, 1, GL_FALSE, glm::value_ptr(my_view));
		my_light.Draw(lightShader);

		/* ��������� */
		my_transform = glm::mat4(1.0f);		// ��ʼ���Ǳ�Ҫ��
		ourShader.Use();					// ������ɫ������
		glBindVertexArray(VAO);				// �� VAO
		my_transform = glm::translate(my_transform, glm::vec3(left_right_move, up_down_move, front_back_move));
		my_transform = glm::scale(my_transform, glm::vec3(0.5, 0.5, 0.5));
		my_projection = glm::perspective(glm::radians(45.0f), (float)screenWidth_1 / (float)screenHeight_1, 0.1f, 100.0f);
		my_view = camera.GetViewMatrix();
		my_transform_Location = glGetUniformLocation(ourShader.Program, "transform_1");
		glUniformMatrix4fv(my_transform_Location, 1, GL_FALSE, glm::value_ptr(my_transform));
		my_projection_Location = glGetUniformLocation(ourShader.Program, "projection_1");
		glUniformMatrix4fv(my_projection_Location, 1, GL_FALSE, glm::value_ptr(my_projection));
		my_view_Location = glGetUniformLocation(ourShader.Program, "view_1");
		glUniformMatrix4fv(my_view_Location, 1, GL_FALSE, glm::value_ptr(my_view));
		int LightPos_Location = glGetUniformLocation(ourShader.Program, "LightPos");
		glUniform3f(LightPos_Location, lightPos.x, lightPos.y, lightPos.z);
		int CameraPos_Location = glGetUniformLocation(ourShader.Program, "CameraPos");
		glUniform3f(CameraPos_Location, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		glDrawArrays(GL_TRIANGLES, 0, 36);	// ���� 36 ����(������)
		glBindVertexArray(0);				// ��� VAO
		glfwSwapBuffers(window_1);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)	// ��������(�̶�������ʽ)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void Key_Movement()		// Camera 
{
	if (keys[GLFW_KEY_Q])		// ��ǰ
		camera.ProcessKeyboard(FORWARD, deltaTime);

	if (keys[GLFW_KEY_E])		// ���
		camera.ProcessKeyboard(BACKWARD, deltaTime);

	if (keys[GLFW_KEY_A])		// ����
		camera.ProcessKeyboard(LEFT, deltaTime);

	if (keys[GLFW_KEY_D])		// ����
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (keys[GLFW_KEY_W])		// ����
		camera.ProcessKeyboard(UPWARD, deltaTime);

	if (keys[GLFW_KEY_S])		// ����
		camera.ProcessKeyboard(DOWNWARD, deltaTime);
}

void square_Movement(GLfloat& up_down_move, GLfloat& left_right_move, GLfloat& front_back_move)	 // Square
{

	if (keys[GLFW_KEY_UP])		// ����
	{
		up_down_move += Shift_pix;
	}

	if (keys[GLFW_KEY_DOWN])	// ����
	{
		up_down_move -= Shift_pix;
	}

	if (keys[GLFW_KEY_LEFT])	// ����
	{
		left_right_move += Shift_pix;
	}

	if (keys[GLFW_KEY_RIGHT])	// ����
	{
		left_right_move -= Shift_pix;
	}

	if (keys[GLFW_KEY_F])		// ��ǰ(�� F ��)
	{
		front_back_move += Shift_pix;
	}

	if (keys[GLFW_KEY_B])		// ���(�� B ��)
	{
		front_back_move -= Shift_pix;
	}
}
/* ������Ӧ�Ŀ� */
