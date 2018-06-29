#include "NavigationFly.h"

NavigationFly::NavigationFly()
{
}


NavigationFly::~NavigationFly()
{
}


void NavigationFly::MoveFoward()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() + GetCamera()->GetSpeed() * GetCamera()->GetDirection());
}

void NavigationFly::MoveBackward()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() - GetCamera()->GetSpeed() * GetCamera()->GetDirection());
}

void NavigationFly::MoveLeft()
{
	glm::vec3 side = GetCamera()->GetSide();
	GetCamera()->SetPosition(GetCamera()->GetPosition() - GetCamera()->GetSpeed() * side);
}

void NavigationFly::MoveRight()
{
	glm::vec3 side = GetCamera()->GetSide();
	GetCamera()->SetPosition(GetCamera()->GetPosition() + GetCamera()->GetSpeed() * side);
}

void NavigationFly::MoveDown()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() - GetCamera()->GetSpeed() * GetCamera()->GetUp());
}

void NavigationFly::MoveUp()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() + GetCamera()->GetSpeed() * GetCamera()->GetUp());
}

void NavigationFly::TurnLeft()
{
	glm::mat4 rotUp;
	glm::vec4 newDirection;
	rotUp = glm::rotate(glm::mat4(1.0), GetCamera()->GetAngularSpeed(), GetCamera()->GetUp());
	GetCamera()->SetDirection(rotUp * glm::vec4(GetCamera()->GetDirection(), 1.0));
}

void NavigationFly::TurnRight()
{
	glm::mat4 rotUp;
	rotUp = glm::rotate(glm::mat4(1.0), -GetCamera()->GetAngularSpeed(), GetCamera()->GetUp());
	GetCamera()->SetDirection(rotUp * glm::vec4(GetCamera()->GetDirection(), 1.0));
}

void NavigationFly::TurnMouseX(int diferenca)
{
	glm::mat4 rotUp;
	glm::vec4 newDirection;
	rotUp = glm::rotate(glm::mat4(1.0), GetCamera()->GetAngularSpeed() * diferenca, GetCamera()->GetUp());
	GetCamera()->SetDirection(rotUp * glm::vec4(GetCamera()->GetDirection(), 1.0));
}

void NavigationFly::TurnMouseY(int diferenca)
{
	glm::mat4 rotUp;
	rotUp = glm::rotate(glm::mat4(1.0), diferenca * GetCamera()->GetAngularSpeed(), GetCamera()->GetSide());
	GetCamera()->SetDirection(rotUp * glm::vec4(GetCamera()->GetDirection(), 1.0));
}

void NavigationFly::ZoomIn()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() + 0.1f * GetCamera()->GetDirection());
}

void NavigationFly::ZoomOut()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() - 0.1f * GetCamera()->GetDirection());
}

void NavigationFly::KeyPress(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		MoveUp();
		break;
	case 'z':
		MoveDown();
		break;
	case '+':
		GetCamera()->IncrementAngularSpeed();
		break;
	case '-':
		GetCamera()->DecrementAngularSpeed();
		break;
	}
}

void NavigationFly::SpecialKeyPress(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		MoveFoward();
		break;
	case GLUT_KEY_DOWN:
		MoveBackward();
		break;
	case GLUT_KEY_LEFT:
		MoveLeft();
		break;
	case GLUT_KEY_RIGHT:
		MoveRight();
		break;
	}
}

void NavigationFly::MouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			glm::vec3 mousePosition = glm::vec3(x, y, 0);
			SetMousePosition(mousePosition);
		}
	}
}

void NavigationFly::MouseMove(int x, int y) {

	int diferencaX, diferencaY;

	diferencaX = x - GetMousePosition().x;
	diferencaY = y - GetMousePosition().y;

	TurnMouseX(diferencaX);
	TurnMouseY(diferencaY);

	glm::vec3 mouseP = glm::vec3(x, y, 0);
	SetMousePosition(mouseP);
}