/* 引入相应的库 */
#include <iostream>
#define GLEW_STATIC	
#include"GL\glew.h"					// 注：这一部分要根据个人情况进行设定
#include"GLFW\glfw3.h"
#include "Shader.hpp"

/* 编写各顶点位置与颜色 */
GLfloat vertices_1[] =
{	// position				// color
	0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		// 上顶点(红色)
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		// 左顶点(绿色)
	0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f		// 右顶点(蓝色)
};



int main()
{
	/* 初始化 */
	glfwInit();
	GLFWwindow* window_1 = glfwCreateWindow(800,600, "A Beautiful Triangle", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	glfwMakeContextCurrent(window_1);
	glewInit();

	/* 着色器文本传进来 */
	const GLchar *file_1 = "shader_v.txt";
	const GLchar* file_2 = "shader_f.txt";
	Shader ourShader = Shader(file_1, file_2);
	std::ifstream ifstr_1(file_1);
	std::ifstream ifstr_2(file_2);
	
	if (!ifstr_1.is_open() || !ifstr_2.is_open())
	{
		std::string error = "文件打开失败";
		throw(error);
	}
	/* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO)  */
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

	/* 设置链接顶点属性 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	// 通道 0 打开
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);	// 通道 1 打开

	// draw loop 画图循环
	while (!glfwWindowShouldClose(window_1))
	{
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*  第九步：绘制三角形 */
		ourShader.Use();					// 图形渲染
		glBindVertexArray(VAO);				// 绑定 VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);	// 画三角形  从第0个顶点开始 一共画3次
		glBindVertexArray(0);				// 解绑定

		glfwSwapBuffers(window_1);
	}

	glDeleteVertexArrays(1, &VAO);			// 释放资源	
	glDeleteBuffers(1, &VBO);
	glfwTerminate();						// 结束
	return 0;
}
