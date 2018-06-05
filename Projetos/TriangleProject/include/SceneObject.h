#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

class SceneObject
{
    public:
        SceneObject();
        virtual ~SceneObject();

        glm::vec3 Getpos() { return pos; }
        void Setpos(glm::vec3 val) { pos = val; }
        glm::vec3 Getdir() { return dir; }
        void Setdir(glm::vec3 val) { dir = val; }
        glm::vec3 Getup() { return up; }
        void Setup(glm::vec3 val) { up = val; }
        float GetangularSpeed() { return angularSpeed; }
        void SetangularSpeed(float val) { angularSpeed = val; }
        float Getspeed() { return speed; }
        void Setspeed(float val) { speed = val; }

        void MoveFoward() {}
        void MoveBackward() {}
        void MoveRight() {}
        void MoveLeft() {}
        void MoveUp() {}
        void MoveDown() {}

    protected:

    private:
        glm::vec3 pos;
        glm::vec3 dir;
        glm::vec3 up;
        float angularSpeed;
        float speed;
};

#endif // SCENEOBJECT_H
