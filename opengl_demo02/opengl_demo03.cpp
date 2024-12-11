/* ��һ����������Ӧ�Ŀ� */
#include <iostream>
#define GLEW_STATIC	
#include <GL/glew.h>	
#include <GLFW/glfw3.h> 


/* �ڶ�������д����λ�� */
GLfloat vertices_1[] =
{
	0.0f, 0.5f, 0.0f,		// �϶���
	-0.5f, -0.5f, 0.0f,		// �󶥵�
	0.5f, -0.5f, 0.0f,		// �Ҷ���

};


/* ����������д������ɫ�� */
const GLchar* vertexCode_1 = "#version 330 core\n"		// 3.30�汾
"layout(location = 0) in vec3 position_1;\n"			// ����������vector������ʾλ�� position������
"void main()\n"
"{\n"
"gl_Position = vec4(position_1, 1.0f);\n"				// ���ĺ���(λ����Ϣ��ֵ)
"}\n";


/* ���Ĳ�����дƬԪ��ɫ��(Ҳ��Ƭ����ɫ��) */
const GLchar* fragmentCode_1 = "#version 330 core\n"	// �汾��Ϣ
"out vec4 FragColor_1;\n"								//������ĸ����������ɵ�һ������ RGB+aerfa
"void main()\n"
"{\n"
"FragColor_1 = vec4(0.5f, 0.75f, 0.25f, 1.0f);\n"
"}\n";

const GLint WIDTH = 800, HEIGHT = 600;

// DrawArray �� VAO ������Ҫ�ص���⣬����ֻҪ֪������ģ�鹦�ܾ����ˡ�

int main()
{
	glfwInit();
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Triangle test", nullptr, nullptr);

	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	glfwMakeContextCurrent(window_1);
	glewInit();


	/* ����������д������ɫ�� */
	GLuint vertexShader_1 = glCreateShader(GL_VERTEX_SHADER);		// ����������ɫ������
	glShaderSource(vertexShader_1, 1, &vertexCode_1, NULL);			// ��������ɫ�������ݴ�����
	glCompileShader(vertexShader_1);	// ���붥����ɫ��
	GLint flag;							// �����жϱ����Ƿ�ɹ�
	GLchar infoLog[512];				// 512���ַ�
	glGetShaderiv(vertexShader_1, GL_COMPILE_STATUS, &flag); // ��ȡ����״̬
	if (!flag)
	{
		glGetShaderInfoLog(vertexShader_1, 512, NULL, infoLog);   // �����  
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	/* ���Ĳ�����дƬԪ��ɫ��(Ҳ��Ƭ����ɫ��) */
	GLuint fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);		// ����ƬԪ��ɫ������
	glShaderSource(fragmentShader_1, 1, &fragmentCode_1, NULL);			// ��������ɫ�������ݴ�����
	glCompileShader(fragmentShader_1);									// ���붥����ɫ��
	glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &flag);			// ��ȡ����״̬
	if (!flag)
	{
		glGetShaderInfoLog(fragmentShader_1, 512, NULL, infoLog);		// �����  
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	/* ���岽��������ɫ������ */
	GLuint shaderProgram_1 = glCreateProgram();
	glAttachShader(shaderProgram_1, vertexShader_1);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	glLinkProgram(shaderProgram_1);
	glGetProgramiv(shaderProgram_1, GL_LINK_STATUS, &flag);
	if (!flag)
	{
		glGetProgramInfoLog(shaderProgram_1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader_1);
	glDeleteShader(fragmentShader_1);


	/* ���߲������ö��㻺�����(VBO) + �ڰ˲������ö����������(VAO)  */
	GLuint VAO, VBO;				// �����ǳɶԳ��ֵ�
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// ���Կ��л���һ���ռ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);	// GL_STATIC_DRAW����̬�Ļ�ͼ(Ƶ���ض�)


	/* ���������������Ӷ������� */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	// draw loop ��ͼѭ��
	while (!glfwWindowShouldClose(window_1))
	{
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*  �ھŲ������������� */
		glUseProgram(shaderProgram_1);		// ��Ⱦ������ɫ������
		glBindVertexArray(VAO);				// �� VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);	// ��������  �ӵ�0�����㿪ʼ һ����3��
		glBindVertexArray(0);				// ���

		glfwSwapBuffers(window_1);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram_1);

	glfwTerminate();
	return 0;
}
