#include "SceneObject.h"

SceneObject::SceneObject()
{

}


SceneObject::~SceneObject()
{
}

void SceneObject::Draw(bool isSelection, glm::vec3 CenterBoundingBox, bool drawBox) {
	for (int i = 0; i < QuantidadeMeshItem; i++) {
		MeshItem mi = MeshGroup.at(i);
		MeshGroup.at(i).Draw(isSelection, mi.GetCenter() == CenterBoundingBox && drawBox);
	}
}

bool SceneObject::CompareMeshItem(MeshItem mi)
{
	return false;
}