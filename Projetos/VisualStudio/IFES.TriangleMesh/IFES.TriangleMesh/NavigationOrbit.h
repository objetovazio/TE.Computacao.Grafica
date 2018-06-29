#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/freeglut.h>
#endif

#include "Navigation.h"
class NavigationOrbit : public Navigation
{
public:
	NavigationOrbit();
	~NavigationOrbit();

	void MoveFoward() {}
	void MoveBackward() {}
	void MoveRight() {}
	void MoveLeft() {}
	void MoveUp() {}
	void MoveDown() {}

	void TurnLeft() {}
	void TurnRight() {}

	void TurnMouseX(int diferenca);
	void TurnMouseY(int diferenca);

	void ZoomOut();
	void ZoomIn();

	void KeyPress(unsigned char key, int x, int y);
	void SpecialKeyPress(int key, int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void MouseMove(int x, int y);
};

