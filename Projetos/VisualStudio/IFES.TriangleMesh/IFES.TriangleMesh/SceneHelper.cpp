#include "SceneHelper.h"



SceneHelper::SceneHelper()
{
}


SceneHelper::~SceneHelper()
{
}


glm::vec3 SceneHelper::GetNewSelectColor()
{
	if (ColorPicker.r <= 255) {
		ColorPicker.r++;
	}
	else if (ColorPicker.g <= 255)
	{
		ColorPicker.r = 0;
		ColorPicker.g++;
	}
	else
	{
		ColorPicker.r = 0;
		ColorPicker.g = 0;
		ColorPicker.b++;
	}

	float r = ColorPicker.r / 255.0;
	float g = ColorPicker.g / 255.0;
	float b = ColorPicker.b / 255.0;

	glm::vec3 color = glm::vec3(r, g, b); // Testar ColorPicket / 255.0;

	return color;
}