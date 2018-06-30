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

#include <soil.h>

#include <stdlib.h>
#include <stdio.h>

#include "Camera.h"
#include "SceneHelper.h"
#include "SceneObject.h"
#include "Navigation.h"
#include "NavigationFly.h"
#include "NavigationOrbit.h"

SceneHelper _sceneHelper;
Camera _camera;
Navigation* _navigation;
NavigationFly* _navigationFly = new NavigationFly();
NavigationOrbit* _navigationOrbit = new NavigationOrbit();

std::vector<SceneObject> _sceneObjects;
std::vector<FILE*> _files;

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

int wid = 800;
int hei = 600;
double T = 0, t1 = 0, t2 = 0;

#pragma region Funcoes de Desenho

/* GLUT callback Handlers */
static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);

	gluPerspective(60, ar, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void printtext(int x, int y, int w, int h, char *str)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	int len = (int)strlen(str);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void TurnLight(bool On)
{
	if (On)
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_LIGHTING);
	}
}

static void selectionMode()
{
	TurnLight(false);

	GLfloat resposta[4];
	GLint viewportCores[4];

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(_camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z,
		_camera.GetCenter().x, _camera.GetCenter().y, _camera.GetCenter().z,
		_camera.GetUp().x, _camera.GetUp().y, _camera.GetUp().z);

	for (int i = 0; i < _sceneObjects.size(); i++)
	{
		_sceneObjects.at(i).Draw(_camera.GetMadeSelection());
	}

	glGetIntegerv(GL_VIEWPORT, viewportCores);

	glReadPixels(_navigation->GetMousePosition().x, viewportCores[3] - _navigation->GetMousePosition().y, 1, 1, GL_RGBA, GL_FLOAT, &resposta);

	glm::vec3 cores = glm::vec3(resposta[0], resposta[1], resposta[2]);

	for (int i = 0; i < _sceneObjects.size(); i++) {
		SceneObject so = _sceneObjects.at(i);

		for (int j = 0; j < so.GetQuantidadeMeshItem(); j++) {
			MeshItem mi = so.GetMeshItem(j);

			if (mi.CompareColor(cores)) {
				_camera.SetPivot(mi.GetCenter());
				_camera.SetSelectionMode(false);
				_camera.UpdateDirectionByPivot();
				break;
			}

		}
	}

	TurnLight(true);
}

static void display(void)
{
	char fpsLabel[30];
	char showing[30] = "FPS: ";
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	char line[255];

	t1 = t2;
	t2 = t;
	T = t2 - t1;
	double fps = 1 / T;

	if (_camera.GetSelectionMode() && _camera.GetMadeSelection())
	{
		selectionMode();
		_camera.SetMadeSelection(false);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(_camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z,
		_camera.GetCenter().x, _camera.GetCenter().y, _camera.GetCenter().z,
		_camera.GetUp().x, _camera.GetUp().y, _camera.GetUp().z);

	for (int i = 0; i < _sceneObjects.size(); i++)
	{
		_sceneObjects.at(i).Draw(_camera.GetMadeSelection());
	}

	sprintf(fpsLabel, "%.1f", fps);
	strcat(showing, fpsLabel);
	printtext(10, 10, wid, hei, showing);

	char angularSpeedMouse[100] = "Angular Speed: ";
	char asmValue[50];

	sprintf(asmValue, "%.3f", _camera.GetAngularSpeed());
	strcat(angularSpeedMouse, asmValue);
	printtext(10, 580, wid, hei, angularSpeedMouse);

	glutSwapBuffers();
	glutPostRedisplay();
}

#pragma endregion

#pragma region Funções de carregamento

static void StartCamera()
{
	_camera.SetPosition(glm::vec3(0, 1, 0));
	_camera.SetDirection(glm::vec3(0, 0, 1));
	_camera.SetUp(glm::vec3(0, 1, 0));
	_camera.SetSpeed(1);
	_camera.SetAngularSpeed(0.005);
	_camera.SetPivot(_sceneObjects.at(0).GetMeshItem(0).GetCenter());
	_camera.SetMadeSelection(false);

	_navigationFly->SetCamera(&_camera);
	_navigationOrbit->SetCamera(&_camera);

	_navigation = _navigationFly;
}

FILE* AddFile(const char* path, const char* model) {
	char result[255];
	strcpy_s(result, path);

	FILE* file = fopen(strcat(result, model), "r");

	if (file == NULL)
	{
		printf("Erro ao ler arquivo %s!", strcat(result, model));
		exit(1);
	}

	return file;
}

void preencherVec3(FILE* file, glm::vec3 &vetor) {
	char var[255];
	char val[3][255];

	float x, y, z;

	fscanf(file, "%f %f %f", &x, &y, &z);

	vetor.x = x;
	vetor.y = y;
	vetor.z = z;
}

GLuint LoadTexture(const char* path, const char* fileName) {
	char texture[255];
	strcpy_s(texture, path);
	strcat(texture, fileName);

	GLuint textureID = SOIL_load_OGL_texture(texture, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

void LoadVerticeNormalTextura(FILE* file, int quantidadeVertices, MeshItem &meshItem) {
	GLfloat* vertices = (GLfloat*)malloc(quantidadeVertices * 3 * sizeof(GLfloat));
	GLfloat* normais = (GLfloat*)malloc(quantidadeVertices * 3 * sizeof(GLfloat));
	GLfloat* textCord = (GLfloat*)malloc(quantidadeVertices * 3 * sizeof(GLfloat));
	glm::vec3 maiorCoordenada = glm::vec3(-1000, -1000, -1000);
	glm::vec3 menorCoordenada = glm::vec3(1000, 1000, 1000);
	int indiceLinha = 0;
	float values[3];

	for (int i = 0; i < quantidadeVertices; i++)
	{
		fscanf(file, "%d %f %f %f", &indiceLinha, &values[0], &values[1], &values[2]);
		vertices[(i * 3)] = values[0]; vertices[(i * 3) + 1] = values[1]; vertices[(i * 3) + 2] = values[2];

		if (values[0] > maiorCoordenada.x) maiorCoordenada.x = values[0];
		if (values[1] > maiorCoordenada.y) maiorCoordenada.y = values[1];
		if (values[2] > maiorCoordenada.z) maiorCoordenada.z = values[2];

		if (values[0] < menorCoordenada.x)
			menorCoordenada.x = values[0];
		if (values[1] < menorCoordenada.y)
			menorCoordenada.y = values[1];
		if (values[2] < menorCoordenada.z)
			menorCoordenada.z = values[2];

		fscanf(file, "%f %f %f", &values[0], &values[1], &values[2]);
		normais[(i * 3)] = values[0]; normais[(i * 3) + 1] = values[1]; normais[(i * 3) + 2] = values[2];

		fscanf(file, "%f %f", &values[0], &values[1]);
		textCord[(i * 2)] = values[0]; textCord[(i * 2) + 1] = values[1];
	}

	meshItem.SetVertices(vertices);
	meshItem.SetNormais(normais);
	meshItem.SetTextureCoordenate(textCord);
	meshItem.SetCenter(((maiorCoordenada + menorCoordenada) * 0.5f));
}

void LoadIndices(FILE* file, int quantidadeIndices, MeshItem &meshItem) {
	GLuint* indices = (GLuint*)malloc(quantidadeIndices * 3 * sizeof(GLuint)); // allocate memory for array
	int indiceLinha = 0;
	int val[3];

	for (int i = 0; i < quantidadeIndices; i++)
	{
		fscanf(file, "%d %d %d %d", &indiceLinha, &val[0], &val[1], &val[2]);
		indices[(i * 3)] = val[0]; indices[(i * 3) + 1] = val[1]; indices[(i * 3) + 2] = val[2];
	}

	meshItem.SetIndices(indices);
}

MeshItem LoadMeshItem(FILE* file, const char* path) {
	char line[255];
	MeshItem meshItem;
	glm::vec3 ambiente;
	glm::vec3 difusa;
	glm::vec3 componenteEspecular;
	float coeficienteEspecular = 0;
	int quantidadeVertices;
	int quantidadeIndices;
	glm::vec3 cor;
	glm::vec3 corSelect;

	preencherVec3(file, ambiente);
	preencherVec3(file, difusa);
	preencherVec3(file, componenteEspecular);

	fscanf(file, "%f", &coeficienteEspecular);

	fscanf(file, "%s", line); //Pegou nome do arquivo de textura
	meshItem.SetIdTextura(LoadTexture(path, line));

	//Carrega a quantidade de vertices e indices
	fscanf(file, "%d %d", &quantidadeVertices, &quantidadeIndices);

	LoadVerticeNormalTextura(file, quantidadeVertices, meshItem);
	LoadIndices(file, quantidadeIndices, meshItem);

	meshItem.SetAmbiente(ambiente);
	meshItem.SetDifusa(difusa);
	meshItem.SetComponenteEspecular(componenteEspecular);
	meshItem.SetCoeficienteEspecular(coeficienteEspecular);
	meshItem.SetColor(_sceneHelper.GetNewColor());
	meshItem.SetSelectColor(_sceneHelper.GetNewSelectColor());
	meshItem.SetQuantidadeVertices(quantidadeVertices);
	meshItem.SetQuantidadeIndices(quantidadeIndices);

	return meshItem;
}

std::vector<SceneObject> LoadSceneObjects(std::vector<FILE*> files, std::vector<const char*> paths) {
	char line[255];
	std::vector<SceneObject> sceneObjects;
	FILE* file;
	int qtdMeshItem;

	for (int i = 0; i < files.size(); i++) {
		SceneObject sceneObject;
		glm::vec3 position = _sceneHelper.GetRandomPosition();

		file = files.at(i);
		fscanf(file, "%d", &qtdMeshItem);

		sceneObject.SetQuantidadeMeshItem(qtdMeshItem);

		for (int j = 0; j < qtdMeshItem; j++) {
			MeshItem meshItem = LoadMeshItem(file, paths.at(i));
			meshItem.SetPosition(position);
			sceneObject.PushToMeshGroup(meshItem);
		}

		sceneObjects.push_back(sceneObject);
	}

	return sceneObjects;
}

#pragma endregion

#pragma region Funções de eventos
static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case '1':
		_navigation = _navigationOrbit;
		_navigation->KeyPress(key, x, y);
		break;
	case '2':
		_navigation = _navigationOrbit;
		_navigation->KeyPress(key, x, y);
		break;
	case '3':
		_navigation = _navigationFly;
		break;
	case 'c':
		_camera.UpdateDirectionByPivot();
		break;
	case 'v':
		_camera.UpdatePositionByPivot();
		break;
	default:
		_navigation->KeyPress(key, x, y);
	}
}

void special(int key, int x, int y)
{
	_navigation->SpecialKeyPress(key, x, y);
}

void mouseButton(int button, int state, int x, int y)
{
	_navigation->MouseButton(button, state, x, y);
}

void mouseMove(int x, int y)
{
	_navigation->MouseMove(x, y);
}

static void idle(void)
{
	glutPostRedisplay();
}
#pragma endregion

int main(int argc, char *argv[])
{
	std::vector<const char*> path;
	std::vector<const char*> model;

	path.push_back("Models/starwars/");
	//path.push_back("Models/House/");
	//path.push_back("Models/Bladesong.Missile.Boat/");
	
	model.push_back("starwars.msh");
	//model.push_back("houseA_obj.msh");
	//model.push_back("Bladesong Missile Boat.msh");
	
	for (int i = 0; i < path.size(); i++) {
		_files.push_back(AddFile(path.at(i), model.at(i)));
	}

	glutInit(&argc, argv);
	glutInitWindowSize(wid, hei);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Little Bunny");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutIdleFunc(idle);

	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	TurnLight(true);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	_sceneObjects = LoadSceneObjects(_files, path);
	StartCamera();

	glutMainLoop();

	return EXIT_SUCCESS;
}
