#pragma once	// Ϊ�˱���ͬһ��ͷ�ļ���������include�����
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"

// �����Լ�����ɫ��
class Shader
{
private:
	GLuint vertex, fragment;	// ������ɫ�� �� ƬԪ��ɫ�� 
public:
	GLuint Program;				// ��ɫ�������ID
	// Constructor(��ɫ�����캯��)
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// Deconstructor(��������)
	~Shader();
	void Use();
	
};
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// �ļ���ȡϵ�еı�������
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// �쳣���ƴ�����֤ifstream��������׳��쳣��
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		// ���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		// ��ȡ�ļ��Ļ������ݵ���������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// �ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();

		// ת����������string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e) {	// �����쳣ʱ���
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	/* �� string ���͵��ַ���ת��Ϊ char���� ���� */
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	/* ������ɫ�� */
	vertex = glCreateShader(GL_VERTEX_SHADER);				// ����������ɫ������
	glShaderSource(vertex, 1, &vShaderCode, NULL);			// ��������ɫ�������ݴ�����
	glCompileShader(vertex);								// ���붥����ɫ��
	GLint flag;												// �����жϱ����Ƿ�ɹ�
	GLchar infoLog[512];
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &flag); // ��ȡ����״̬
	if (!flag)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* ƬԪ��ɫ�� */
	fragment = glCreateShader(GL_FRAGMENT_SHADER);			// ����ƬԪ��ɫ������
	glShaderSource(fragment, 1, &fShaderCode, NULL);		// ��ƬԪ��ɫ�������ݴ�����
	glCompileShader(fragment);								// ���붥����ɫ��
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &flag);		// ��ȡ����״̬
	if (!flag)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* ��ɫ������ */
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	if (!flag)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
Shader::~Shader()
{
	glDetachShader(this->Program, vertex);
	glDetachShader(this->Program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteProgram(this->Program);
}
void Shader::Use()
{
	glUseProgram(this->Program);
}