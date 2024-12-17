#include <iostream>
#include"GL\glew.h"					// 注：这一部分要根据个人情况进行设定
#include"GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

enum Camera_Movement
{
	FORWARD,		// 向前
	BACKWARD,		// 向后
	LEFT,			// 向左
	RIGHT,			// 向右
	UPWARD,			// 向上
	DOWNWARD		// 向下
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
	glm::vec3 position;				 // 相机当前位置 
	glm::vec3 camera_Z_axis;
	glm::vec3 camera_X_axis;		// 摄影机的 X 轴向量
	glm::vec3 camera_Y_axis;		// 摄影机的 Y 轴向量
	GLfloat movementSpeed;			// 镜头移动速度
	void updatecameravectors()
	{
		this->camera_Z_axis = glm::normalize(this->camera_Z_axis);
		this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));
		this->camera_Y_axis = glm::normalize(glm::cross(this->camera_X_axis, this->camera_Z_axis));

	}
};