#include "Camera.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma once
class Navigation
{
public:
	virtual ~Navigation() {}

	virtual void MoveFoward() = 0;
	virtual void MoveBackward() = 0;
	virtual void MoveRight() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveUp() = 0;
	virtual void MoveDown() = 0;

	virtual void TurnLeft() = 0;
	virtual void TurnRight() = 0;

	virtual void TurnMouseX(int diferenca) = 0;
	virtual void TurnMouseY(int diferenca) = 0;
	
	virtual void ZoomOut() = 0;
	virtual void ZoomIn() = 0;

	virtual void KeyPress(unsigned char key, int x, int y) = 0;
	virtual void SpecialKeyPress(int key, int x, int y) = 0;
	virtual void MouseButton(int button, int state, int x, int y) = 0;
	virtual void MouseMove(int x, int y) = 0;


	Camera* GetCamera() { return Camera; }
	void SetCamera(Camera* camera) { Camera = camera; }

	glm::vec3 GetMousePosition() { return MousePosition; }
	void SetMousePosition(glm::vec3 val) { MousePosition = val; }

private:
	Camera* Camera;
	glm::vec3 MousePosition;
};

