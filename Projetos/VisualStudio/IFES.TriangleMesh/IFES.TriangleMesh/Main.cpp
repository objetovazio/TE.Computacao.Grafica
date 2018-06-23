/*
* Trabalho de Computação Gráfica V3
* # André Martins
*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "Camera.h"
#include "SceneHelper.h"
#include "SceneObject.h"

SceneHelper _sh;
Camera _camera;
std::vector<SceneObject> _sceneObjects;
std::vector<FILE*> _files;

FILE* AddFile(char* path, char* model) {
	char result[255];
	strcpy(result, path);

	FILE* file = fopen(strcat(result, model), "r");

	if (file == NULL)
	{
		printf("Erro ao ler arquivo %s!", strcat(path, model));
		exit(1);
	}

	return file;
}

void preencherVec3(FILE* file, glm::vec3 &vetor) {
	char var[255];
	char val[3][255];
	
	for (int i = 0; i < 3; i++) {
		fscanf(file, "%s", val[i]);
	}

	vetor.x = atof(val[0]);
	vetor.y = atof(val[1]);
	vetor.z = atof(val[2]);
}

MeshItem LoadMeshItem(FILE* file) {
	char line[255];
	MeshItem meshItem;
	glm::vec3 ambiente;
	glm::vec3 difusa;
	glm::vec3 componenteEspecular;
	float coeficienteEspecular = 0;

	preencherVec3(file, ambiente);
	preencherVec3(file, difusa);
	preencherVec3(file, componenteEspecular);

	fscanf(file, "%s", line);
	coeficienteEspecular = atof(line);

	meshItem.SetAmbiente(ambiente);
	meshItem.SetDifusa(difusa);
	meshItem.SetComponenteEspecular(componenteEspecular);
	meshItem.SetCoeficienteEspecular(coeficienteEspecular);

	return meshItem;
}

std::vector<SceneObject> LoadSceneObjects(std::vector<FILE*> files, char paths[3][255]){
	char line[255];
	std::vector<SceneObject> sceneObjects;
	FILE* file;
	int qtdMeshItem;

	for (int i = 0; i < files.size(); i++) {
		SceneObject sceneObject;

		file = files.at(i);
		fscanf(file, "%s", line);
		qtdMeshItem = atoi(line);

		sceneObject.SetQuantidadeMeshItem(qtdMeshItem);

		for (int j = 0; j < qtdMeshItem; j++) {
			MeshItem meshItem = LoadMeshItem(file);
			sceneObject.PushToMeshGroup(meshItem);
		}

		sceneObject.SetPath(paths[i]);
		sceneObjects.push_back(sceneObject);
	}

	return sceneObjects;
}

int main(int argc, char *argv[])
{
	char path[3][255] = { "Models/House/" , "Models/Bladesong.Missile.Boat/", "Models/starwars/" };
	char model[3][255] = { "houseA_obj.msh", "Bladesong Missile Boat.msh","starwars.msh" };

	for (int i = 0; i < 3; i++) {
		_files.push_back(AddFile(path[i], model[i]));
	}

	_sceneObjects = LoadSceneObjects(_files, path);

	printf("sucesso!");

	return EXIT_SUCCESS;
}
