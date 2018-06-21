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

#include "Camera.h"
#include "SceneHelper.h"
#include "SceneObject.h"

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

SceneHelper _sh;
Camera _camera;
std::vector<SceneObject> _sceneObjects;
std::vector<FILE*> _files;

FILE* AddFile(char* path, char* model) {
	FILE* file = fopen(strcat(path, model), "r");

	if (file == NULL)
	{
		printf("Erro ao ler arquivo %s!", strcat(path, model));
		exit(1);
	}

	return file;
}

int main(int argc, char *argv[])
{
	char path[255] = "Models/House/"; 
	char model[255] = "houseA_obj.msh";

	_files.push_back(AddFile(path, model));

	printf("sucesso!");

	return EXIT_SUCCESS;
}
