#include "SceneObject.h"

SceneObject::SceneObject()
{

}


SceneObject::~SceneObject()
{
}

void SceneObject::Draw(bool isSelection) {
	for (int i = 0; i < QuantidadeMeshItem; i++) {
		MeshGroup.at(i).Draw(isSelection);
	}
}