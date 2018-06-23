#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <glm/vec3.hpp>
#include <stdio.h>

class MeshItem
{
public:
	MeshItem();
	~MeshItem();

	glm::vec3 GetPosition() { return Position; }
	void SetPosition(glm::vec3 val) { Position = val; }

	glm::vec3 GetColor() { return Color; }
	void SetColor(glm::vec3 val) { Color = val; }

	glm::vec3 GetCenter() { return Center; }
	void SetCenter(glm::vec3 val) { Center = val; }

	glm::vec3 GetSelectColor() { return SelectColor; }
	void SetSelectColor(glm::vec3 val) { SelectColor = val; }

	glm::vec3 GetAmbiente() { return Ambiente; }
	void SetAmbiente(glm::vec3 val) { Ambiente = val; }

	glm::vec3 GetDifusa() { return Difusa; }
	void SetDifusa(glm::vec3 val) { Difusa = val; }

	glm::vec3 GetComponenteEspecular() { return ComponenteEspecular; }
	void SetComponenteEspecular(glm::vec3 val) { ComponenteEspecular = val; }

	float GetCoeficienteEspecular() { return CoeficienteEspecular; }
	void SetCoeficienteEspecular(float val) { CoeficienteEspecular = val; }

	GLfloat* GetVertices() { return Vertices; }
	void SetVertices(GLfloat* val) { Vertices = val; }

	GLfloat* GetNormais() { return Normais; }
	void SetNormais(GLfloat* val) { Normais = val; }

	GLuint* GetIndices() { return Indices; }
	void SetIndices(GLuint* val) { Indices = val; }

	GLfloat* GetTextureCoordenate() { return TextureCoordenate; }
	void SetTextureCoordenate(GLfloat* val) { TextureCoordenate = val; }

	int GetIncidencia() { return Incidencia * 3; }
	void SetIndices(int val) { Incidencia = val; }

	int GetQuantidadeVertices() { return QuantidadeVertices; }
	void SetQuantidadeVertices(int val) { QuantidadeVertices = val; }

	void draw(bool isSelection);
	void printObject();

	bool compareColor(glm::vec3 color);

private:
	glm::vec3 Position;
	glm::vec3 Center;
	glm::vec3 Color;
	glm::vec3 SelectColor;
	glm::vec3 Ambiente;
	glm::vec3 Difusa;
	glm::vec3 ComponenteEspecular;
	float CoeficienteEspecular;
	GLfloat* Vertices;
	GLfloat* Normais;
	GLuint* Indices;
	GLfloat* TextureCoordenate;
	int Incidencia;
	int QuantidadeVertices;
	int IdTextura;
};

