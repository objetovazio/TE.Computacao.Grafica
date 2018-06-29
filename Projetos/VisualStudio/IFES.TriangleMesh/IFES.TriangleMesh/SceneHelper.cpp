#include "SceneHelper.h"



SceneHelper::SceneHelper()
{
	ColorPicker.r = 0.0;
}


SceneHelper::~SceneHelper()
{
}


glm::vec3 SceneHelper::GetNewSelectColor()
{
	if (ColorPicker.r <= 1) {
		ColorPicker.r += 0.0025;
	}
	else if (ColorPicker.g <= 1)
	{
		ColorPicker.r = 0;
		ColorPicker.g += 0.0025;
	}
	else
	{
		ColorPicker.r = 0;
		ColorPicker.g = 0;
		ColorPicker.b += 0.0025;
	}

	float r = ColorPicker.r;
	float g = ColorPicker.g;
	float b = ColorPicker.b;

	glm::vec3 color = glm::vec3(r, g, b); // Testar ColorPicket / 255.0;

	return color;
}

glm::vec3 SceneHelper::GetRandomPosition() {
	return glm::vec3(rand() % 300 + (-100), 0, rand() % 300 + 1);
}