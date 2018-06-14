#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <glut.h>
#endif
#include <glm/vec3.hpp>
#include <stdio.h>

class SceneObject
{
    public:
        SceneObject();
        SceneObject(glm::vec3 Position, glm::vec3 Color, glm::vec3 SelectColor,
                    GLfloat* Vertices,  GLfloat* Normais, GLuint* Indices, int Incidencia, int QuantidadeVertices, glm::vec3 Center);
        virtual ~SceneObject();



        glm::vec3 GetPosition() { return Position; }
        void SetPosition(glm::vec3 val) { Position = val; }

        glm::vec3 GetColor() { return Color; }
        void SetColor(glm::vec3 val) { Color = val; }

        glm::vec3 GetCenter() { return Center; }
        void SetCenter(glm::vec3 val) { Center = val; }

        glm::vec3 GetSelectColor() { return SelectColor; }
        void SetSelectColor(glm::vec3 val) { SelectColor = val; }

        GLfloat* GetVertices() { return Vertices; }
        void SetVertices(GLfloat* val) { Vertices = val; }

        GLfloat* GetNormais() { return Normais; }
        void SetNormais(GLfloat* val) { Normais = val; }

        GLuint* GetIndices() { return Indices; }
        void SetIndices(GLuint* val) { Indices = val; }

        int GetIncidencia() { return Incidencia * 3; }
        void SetIndices(int val) { Incidencia = val; }

        int GetQuantidadeVertices() { return QuantidadeVertices; }
        void SetQuantidadeVertices(int val) { QuantidadeVertices = val; }

        void draw(bool isSelection);
        void printObject();

        bool compareColor(glm::vec3 cores);
    protected:

    private:
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec3 SelectColor;
        glm::vec3 Center;
        GLfloat* Vertices;
        GLfloat* Normais;
        GLuint* Indices;
        int Incidencia;
        int QuantidadeVertices;
};

#endif // SCENEOBJECT_H
