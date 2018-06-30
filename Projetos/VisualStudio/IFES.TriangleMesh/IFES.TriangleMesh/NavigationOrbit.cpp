#include "NavigationOrbit.h"

NavigationOrbit::NavigationOrbit() {}

NavigationOrbit::~NavigationOrbit(){}

void NavigationOrbit::TurnMouseX(int diferenca)
{
	glm::mat4 rotUp;
	glm::vec4 newDirection;
	rotUp = glm::rotate(glm::mat4(1.0), GetCamera()->GetAngularSpeed() * diferenca, GetCamera()->GetUp());
	GetCamera()->SetDirection(rotUp * glm::vec4(GetCamera()->GetDirection(), 1.0));
}

void NavigationOrbit::TurnMouseY(int diferenca)
{
	glm::mat4 rotUp;
	rotUp = glm::rotate(glm::mat4(1.0), diferenca * GetCamera()->GetAngularSpeed(), GetCamera()->GetSide());
	GetCamera()->SetDirection(rotUp * glm::vec4(GetCamera()->GetDirection(), 1.0));
}

void NavigationOrbit::ZoomIn()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() + 0.07f * GetCamera()->GetDirection());
	GetCamera()->UpdateDirectionByPivot();
}

void NavigationOrbit::ZoomOut()
{
	GetCamera()->SetPosition(GetCamera()->GetPosition() - 0.07f * GetCamera()->GetDirection());
	GetCamera()->UpdateDirectionByPivot();
}

void NavigationOrbit::KeyPress(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		ZoomIn();
		break;
	case 'z':
		ZoomOut();
		break;
	case '+':
		GetCamera()->IncrementAngularSpeed();
		break;
	case '-':
		GetCamera()->DecrementAngularSpeed();
		break;
	case '1':
		GetCamera()->SetSelectionMode(true);
		break;
	case '2':
		GetCamera()->SetSelectionMode(false);
		break;
	}
}

void NavigationOrbit::SpecialKeyPress(int key, int x, int y) {}

void NavigationOrbit::MouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			glm::vec3 mousePosition = glm::vec3(x, y, 0);
			SetMousePosition(mousePosition);

			if (GetCamera()->GetSelectionMode()) {
				GetCamera()->SetMadeSelection(true); 
			}
		}
	}
}

void NavigationOrbit::MouseMove(int x, int y) {
	if (!GetCamera()->GetSelectionMode())
	{
		int diferencaX, diferencaY;

		diferencaX = x - GetMousePosition().x;
		diferencaY = y - GetMousePosition().y;

		GetCamera()->UpdateDirectionByPivot();

		TurnMouseX(diferencaX);
		TurnMouseY(diferencaY);

		GetCamera()->UpdatePositionByPivot();

		glm::vec3 mouseP = glm::vec3(x, y, 0);
		SetMousePosition(mouseP);
	}
}