#include <iostream>		
#define GLEW_STATIC     
#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
const GLint WIDTH = 800, HEIGHT = 600;		// �����ô����Լ����С								
int main()
{
	glfwInit();								//��ʼ����ʹ��glfw����һ������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						// ���Ŵ��ڵĹر�
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Hello, friend! I'm a openGL window!", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window_1, &screenWidth, &screenHeight);  // ���ʵ��ռ�õ�֡�����С
	if (nullptr == window_1)			//�жϴ�������Ƿ�ɹ�
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window_1);   // ����ǰ���ڣ�׼���Ե�ǰ���ڽ��л�ͼ
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)			// �ж�glew��ʼ���Ƿ�ɹ�
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, screenWidth, screenHeight);	// �����ӿڵĴ�С
	while (!glfwWindowShouldClose(window_1))
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.8f, 0.7f, 1.0f);		// �ֱ��Ǻ졢�̡�����͸���ȵ��ĸ�������RGB��ԭɫ+͸����
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window_1);					// ˫����ģʽ
	}
	glfwTerminate();								// ���ѭ��������glfw�ر�
	return 0;
}

