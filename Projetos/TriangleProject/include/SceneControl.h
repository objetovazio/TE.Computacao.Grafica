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

        void IncrementR() { r+=100; }
        void IncrementG() { g+=100; }
        void IncrementB() { b+=100; }
        glm::vec3 GetNewSelectColor();

        int GetSceneMode() { return SceneMode; }
        void SetSceneMode(int val) { SceneMode = val; }

        glm::vec3 GetMousePosition() { return MousePosition; }
        void SetMousePosition(glm::vec3 val) { MousePosition = val; }
        bool GetMadeSelection() { return madeSelection; }
        bool SetMadeSelection(bool val) { madeSelection = val; }

        SceneObject* GetPivot() { return Pivot; }
        void SetPivot(SceneObject* val) { Pivot = val; }
    protected:

    private:
        float r;
        float g;
        float b;
        int SceneMode;
        glm::vec3 MousePosition;
        SceneObject* Pivot;
        bool madeSelection;
};

#endif // SCENECONTROL_H
