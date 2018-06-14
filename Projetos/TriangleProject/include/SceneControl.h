#ifndef SCENECONTROL_H
#define SCENECONTROL_H
#include <glm/vec3.hpp>
#include "SceneObject.h"


class SceneControl
{
    public:
        SceneControl();
        virtual ~SceneControl();

        unsigned int Getr() { return r; }
        void Setr(unsigned int val) { r = val; }
        unsigned int Getg() { return g; }
        void Setg(unsigned int val) { g = val; }
        unsigned int Getb() { return b; }
        void Setb(unsigned int val) { b = val; }

        void IncrementR() { r++; }
        void IncrementG() { g++; }
        void IncrementB() { b++; }
        glm::vec3 GetNewSelectColor();

        unsigned int GetSceneMode() { return SceneMode; }
        void SetSceneMode(int val) { SceneMode = val; }

        glm::vec3 GetMousePosition() { return MousePosition; }
        void SetMousePosition(glm::vec3 val) { MousePosition = val; }

        SceneObject* GetPivot() { return Pivot; }
        void SetPivot(SceneObject* val) { Pivot = val; }

    protected:

    private:
        unsigned int r;
        unsigned int g;
        unsigned int b;
        int SceneMode;
        glm::vec3 MousePosition;
        SceneObject* Pivot;
};

#endif // SCENECONTROL_H
