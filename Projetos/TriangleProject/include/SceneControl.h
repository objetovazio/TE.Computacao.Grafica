#ifndef SCENECONTROL_H
#define SCENECONTROL_H
#include <glm/vec3.hpp>
#include "SceneObject.h"


class SceneControl
{
    public:
        SceneControl();
        virtual ~SceneControl();

        int Getr() { return r; }
        void Setr(int val) { r = val; }
        int Getg() { return g; }
        void Setg(int val) { g = val; }
        int Getb() { return b; }
        void Setb(int val) { b = val; }

        void IncrementR() { r+=5; }
        void IncrementG() { g+=5; }
        void IncrementB() { b+=5; }
        glm::vec3 GetNewSelectColor();

        int GetSceneMode() { return SceneMode; }
        void SetSceneMode(int val) { SceneMode = val; }

        glm::vec3 GetMousePosition() { return MousePosition; }
        void SetMousePosition(glm::vec3 val) { MousePosition = val; }

        SceneObject* GetPivot() { return Pivot; }
        void SetPivot(SceneObject* val) { Pivot = val; }
    protected:

    private:
        int r;
        int g;
        int b;
        int SceneMode;
        glm::vec3 MousePosition;
        SceneObject* Pivot;
};

#endif // SCENECONTROL_H
