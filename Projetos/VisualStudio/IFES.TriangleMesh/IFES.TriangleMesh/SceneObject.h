#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <glm/vec3.hpp>
#include <stdio.h>
#include <vector>
#include "MeshItem.h"


class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();

	std::vector<MeshItem> GetMeshGroup() { return MeshGroup; };
	void SetMeshGroup(std::vector<MeshItem> meshGroup) { MeshGroup = meshGroup; }

	void PushToMeshGroup(MeshItem val) { MeshGroup.push_back(val); }
	void PopFromMeshGroup() { MeshGroup.pop_back(); }
	MeshItem GetMeshItem(int index) { return MeshGroup.at(index); }

	bool CompareMeshItem(MeshItem mi);

	int GetQuantidadeMeshItem() { return QuantidadeMeshItem; }
	void SetQuantidadeMeshItem(int val) { QuantidadeMeshItem = val; }

	char* GetPath() { return Path; }
	void SetPath(char* val) { Path = val; }

	void Draw(bool isSelection, glm::vec3 CenterBoundingBox, bool drawBox);

private:
	std::vector<MeshItem> MeshGroup;
	int QuantidadeMeshItem;
	char* Path;
	int* IdBoundingBox;
};