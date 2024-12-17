#include <iostream>
using namespace std;
#include"GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include"GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
};

const GLfloat SPEED = 6.0f;

class Camera
{
public:
    /* ���캯�� */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) :movementSpeed(SPEED)
    {
        this->position = position;
        this->camera_Z_axis = target;
        this->camera_Y_axis = up;
        this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));

        this->Zoom = 45.0f;
        this->Yaw = 90.0f;
        this->Pitch = 0.0f;
        this->MouseSensitivity = 0.2f;
        this->updateCameraVectors();
    }

    /* �۲���� */
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(this->position, this->position + this->camera_Z_axis, this->camera_Y_axis);
    }

    /* ��ȡ��ǰ���������Ұ(���۲�ռ�Ĵ�С) */
    GLfloat GetZoom()
    {
        return this->Zoom;
    }

    /* ��ȡ��ǰ�������λ�� */
    glm::vec3 GetPosition()
    {
        return this->position;
    }

    /* ���̿��Ƶ��ӽǱ仯 */
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = this->movementSpeed * deltaTime;
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

    /* ����ƶ����ӽǱ仯 */
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        /* ��ֹ���� ����������ء� ����� */
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        this->updateCameraVectors();
    }

    /* ���������� */
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }


private:
    glm::vec3 position;
    glm::vec3 camera_Z_axis;
    glm::vec3 camera_X_axis;
    glm::vec3 camera_Y_axis;
    GLfloat movementSpeed;

    float Yaw;              // ������
    float Pitch;            // ƫ�ƽ�
    float MouseSensitivity; // ���������
    float Zoom;             // ͶӰ���

    void updateCameraVectors()
    {
        /* ����ƶ� */
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        this->camera_Z_axis = front;

        /* �����������ϵ */
        this->camera_Z_axis = glm::normalize(this->camera_Z_axis);
        this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));
        this->camera_Y_axis = glm::normalize(glm::cross(this->camera_X_axis, this->camera_Z_axis));
    }
};
