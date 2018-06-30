#include "SceneHelper.h"



SceneHelper::SceneHelper()
{
	srand(time(NULL));
	ColorPicker.r = 0.0;
}


SceneHelper::~SceneHelper()
{
}

glm::vec3 SceneHelper::GetNewColor()
{
	float value = 6.0f;
	float divider = 255.0f;


	if (ColorPicker.r <= divider) {
		ColorPicker.r += value;
	}
	else if (ColorPicker.g <= divider)
	{
		ColorPicker.r = 0;
		ColorPicker.g += value;
	}
	else if (ColorPicker.b <= divider)
	{
		ColorPicker.r = 0;
		ColorPicker.g = 0;
		ColorPicker.b += value;
	}
	else {
		exit(0);
	}

	float r = ColorPicker.r;
	float g = ColorPicker.g;
	float b = ColorPicker.b;

	glm::vec3 color = glm::vec3(r, g, b) / divider;

	return color;
}

glm::vec3 SceneHelper::GetNewSelectColor()
{
	float value = 6.0f;
	float divider = 255.0f;

	if (ColorPickerSelection.r <= divider) {
		ColorPickerSelection.r += value;
	}
	else if (ColorPickerSelection.g <= 1)
	{
		ColorPickerSelection.r = 0;
		ColorPickerSelection.g += value;
	}
	else if(ColorPickerSelection.b <= divider)
	{
		ColorPickerSelection.r = 0;
		ColorPickerSelection.g = 0;
		ColorPickerSelection.b += value;
	}
	else {
		exit(0);
	}

	float r = ColorPickerSelection.r;
	float g = ColorPickerSelection.g;
	float b = ColorPickerSelection.b;

	glm::vec3 color = glm::vec3(r, g, b) / divider;

	return color;
}

glm::vec3 SceneHelper::GetRandomPosition() {
	return glm::vec3(rand() % 1000 + (-1000), 0, rand() % 1000 + (-100));
}