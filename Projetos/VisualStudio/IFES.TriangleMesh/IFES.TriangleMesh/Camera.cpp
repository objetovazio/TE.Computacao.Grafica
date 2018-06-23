#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::MoveFoward()
{
	Position = Position + Speed * Direction;
}

void Camera::MoveBackward()
{
	Position = Position - Speed * Direction;
}

void Camera::MoveLeft()
{
	glm::vec3 side = GetSide();
	Position = Position - Speed * side;
}

void Camera::MoveRight()
{
	glm::vec3 side = GetSide();
	Position = Position + Speed * side;
}

void Camera::MoveDown()
{
	Position = Position - Speed * Up;
}

void Camera::MoveUp()
{
	Position = Position + Speed * Up;
}

void Camera::TurnLeft()
{
	glm::mat4 rotUp;
	glm::vec4 newDirection;
	rotUp = glm::rotate(glm::mat4(1.0), AngularSpeed, Up);
	Direction = rotUp * glm::vec4(Direction, 1.0);
}

void Camera::TurnRight()
{
	glm::mat4 rotUp;
	rotUp = glm::rotate(glm::mat4(1.0), -AngularSpeed, Up);
	Direction = rotUp * glm::vec4(Direction, 1.0);
}

void Camera::TurnMouseX(int diferenca)
{
	glm::mat4 rotUp;
	glm::vec4 newDirection;
	rotUp = glm::rotate(glm::mat4(1.0), AngularSpeed * diferenca, Up);
	Direction = rotUp * glm::vec4(Direction, 1.0);
}

void Camera::TurnMouseY(int diferenca)
{
	glm::mat4 rotUp;
	rotUp = glm::rotate(glm::mat4(1.0), diferenca * AngularSpeed, this->GetSide());
	Direction = rotUp * glm::vec4(Direction, 1.0);
}

void Camera::UpdatePosition(glm::vec3 pivotPosition)
{
	this->SetPosition(pivotPosition - Direction);
}

void Camera::UpdateDirection(glm::vec3 pivotPosition)
{
	this->SetDirection(pivotPosition - Direction);
}

void Camera::ZoomIn()
{
	Position = Position + 0.1f * Direction;
	this->UpdateDirection(Pivot);
}

void Camera::ZoomOut()
{
	Position = Position - 0.1f * Direction;
	this->UpdateDirection(Pivot);
}

