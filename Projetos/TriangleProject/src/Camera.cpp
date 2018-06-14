#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::~Camera()
{
    //dtor
}

void Camera::MoveFoward()
{
    pos  = pos + speed * dir;
}

void Camera::MoveBackward()
{
    pos  = pos - speed * dir;
}

void Camera::MoveLeft()
{
    glm::vec3 side = GetSide();
    pos  = pos - speed * side;
}

void Camera::MoveRight()
{
    glm::vec3 side = GetSide();
    pos  = pos + speed * side;
}

void Camera::MoveDown()
{
    pos  = pos - speed * up;
}

void Camera::MoveUp()
{
    pos  = pos + speed * up;
}

void Camera::TurnLeft()
{
    glm::mat4 rotUp;
    glm::vec4 newDir;
    rotUp = glm::rotate(glm::mat4(1.0), angularSpeed, up);
    dir = rotUp * glm::vec4(dir, 1.0);
}

void Camera::TurnRight()
{
    glm::mat4 rotUp;
    rotUp = glm::rotate(glm::mat4(1.0), - angularSpeed, up);
    dir = rotUp * glm::vec4(dir, 1.0);
}

void Camera::TurnMouseX(int diferenca)
{
    glm::mat4 rotUp;
    glm::vec4 newDir;
    rotUp = glm::rotate(glm::mat4(1.0), angularSpeed * diferenca, up);
    dir = rotUp * glm::vec4(dir, 1.0);
}

void Camera::TurnMouseY(int diferenca)
{
    glm::mat4 rotUp;
    rotUp = glm::rotate(glm::mat4(1.0), diferenca * angularSpeed, this->GetSide());
    dir = rotUp * glm::vec4(dir, 1.0);
}

void Camera::ZoomIn(SceneObject* pivot)
{
    if(glm::distance(pos, (pos - speed/2 * dir)) > 2) pos  = pos + speed/2 * dir;
    this->UpdateDirection(pivot->GetPosition());
    this->UpdatePosition(pivot->GetPosition());

    printf("%.6f\n", glm::distance(pos, (pos - speed/2 * dir)));
}

void Camera::ZoomOut(SceneObject* pivot)
{
    printf("%.6f\n", glm::distance(pos, (pos - speed/2 * dir)));
    this->UpdateDirection(pivot->GetPosition());
    this->UpdatePosition(pivot->GetPosition());

    pos  = pos - speed/2 * dir;
}

void Camera::UpdatePosition(glm::vec3 pivotPos)
{
    this->Setpos(pivotPos - this->Getdir());
}

void Camera::UpdateDirection(glm::vec3 pivotPos)
{
    this->Setdir(pivotPos - this->Getpos());
}
