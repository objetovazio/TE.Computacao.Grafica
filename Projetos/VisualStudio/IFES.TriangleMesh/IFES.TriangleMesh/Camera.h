#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	glm::vec3 GetPosition() { return Position; }
	void SetPosition(glm::vec3 val) { Position = val; }

	glm::vec3 GetDirection() { return Direction; }
	void SetDirection(glm::vec3 val) { Direction = val; }

	glm::vec3 GetUp() { return Up; }
	void SetUp(glm::vec3 val) { Up = val; }

	glm::vec3 GetSide() { return glm::cross(Direction, Up); }

	glm::vec3 GetPivot() { return Pivot; }
	void SetPivot(glm::vec3 val) { Pivot = val; }

	float GetAngularSpeed() { return AngularSpeed; }
	void SetAngularSpeed(float val) { AngularSpeed = val; }

	float GetSpeed() { return Speed; }
	void SetSpeed(float val) { Speed = val; }

	bool GetMadeSelection() { return MadeSelection; }
	void SetMadeSelection(bool val) { MadeSelection = val; }

	bool GetSelectionMode() { return SelectionMode; }
	void SetSelectionMode(bool val) { SelectionMode = val; }

	void UpdateDirectionByPivot();
	void UpdatePositionByPivot();

	void IncrementAngularSpeed() { AngularSpeed += 0.001; }
	void DecrementAngularSpeed() { if (AngularSpeed - 0.001 > 0) AngularSpeed -= 0.001; }

	glm::vec3 GetCenter() { return Position + Direction; }

private:
	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 Up;
	glm::vec3 Pivot;
	float AngularSpeed;
	float Speed;
	bool SelectionMode;
	bool MadeSelection;
};

