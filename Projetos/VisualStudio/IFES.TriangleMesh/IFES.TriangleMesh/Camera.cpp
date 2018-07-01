#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::UpdateDirectionByPivot()
{
	if (glm::distance(Pivot, Position) > 4)
		this->SetDirection(Pivot - Position);
}

void Camera::UpdatePositionByPivot()
{
	this->SetPosition(Pivot - Direction);
}