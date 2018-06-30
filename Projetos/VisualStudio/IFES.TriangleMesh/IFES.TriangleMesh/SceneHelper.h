#pragma once
#include <glm/vec3.hpp>
#include <time.h>

class SceneHelper
{
public:
	SceneHelper();
	virtual ~SceneHelper();

	glm::vec3 GetNewSelectColor();
	glm::vec3 GetNewColor();
	glm::vec3 GetRandomPosition();

	glm::vec3 GetMousePosition() { return MousePosition; }
	void SetMousePosition(glm::vec3 val) { MousePosition = val; }

protected:

private:
	glm::vec3 ColorPicker;
	glm::vec3 ColorPickerSelection;
	glm::vec3 MousePosition;
};

