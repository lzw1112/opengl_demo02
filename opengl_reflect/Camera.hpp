#include <iostream>
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

enum Camera_Movement
{
	FORWARD,		// ��ǰ
	BACKWARD,		// ���
	LEFT,			// ����
	RIGHT,			// ����
	UPWARD,			// ����
	DOWNWARD		// ����
};
const GLfloat SPEED = 6.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : movementSpeed(SPEED)
	{
		this->position = position;
		this->camera_Z_axis = target;
		this->camera_Y_axis = up;
		this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));
		this->updatecameravectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, this->position + this->camera_Z_axis, this->camera_Y_axis);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltatime)
	{
		float velocity = this->movementSpeed * deltatime;
		if (direction == FORWARD)
			this->position += this->camera_Z_axis * velocity;

		if (direction == BACKWARD)
			this->position -= this->camera_Z_axis * velocity;

		if (direction == LEFT)
			this->position -= this->camera_X_axis * velocity;

		if (direction == RIGHT)
			this->position += this->camera_X_axis * velocity;

		if (direction == UPWARD)
			this->position += this->camera_Y_axis * velocity;

		if (direction == DOWNWARD)
			this->position -= this->camera_Y_axis * velocity;
	}

	glm::vec3 GetPosition()
	{
		return this->position;
	}
private:
	glm::vec3 position;				 // �����ǰλ�� 
	glm::vec3 camera_Z_axis;
	glm::vec3 camera_X_axis;		// ��Ӱ���� X ������
	glm::vec3 camera_Y_axis;		// ��Ӱ���� Y ������
	GLfloat movementSpeed;			// ��ͷ�ƶ��ٶ�
	void updatecameravectors()
	{
		this->camera_Z_axis = glm::normalize(this->camera_Z_axis);
		this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));
		this->camera_Y_axis = glm::normalize(glm::cross(this->camera_X_axis, this->camera_Z_axis));

	}
};