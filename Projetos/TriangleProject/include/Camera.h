#ifndef CAMERA_H
#define CAMERA_H
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SceneObject.h>


class Camera
{
    public:
        Camera();
        virtual ~Camera();

        glm::vec3 Getpos() { return pos; }
        void Setpos(glm::vec3 val) { pos = val; }
        glm::vec3 Getdir() { return dir; }
        void Setdir(glm::vec3 val) { dir = val; }
        glm::vec3 Getup() { return up; }
        void Setup(glm::vec3 val) { up = val; }

        glm::vec3 GetSide() { return glm::cross(dir, up); }

        float GetangularSpeed() { return angularSpeed; }
        void SetangularSpeed(float val) { angularSpeed = val; }

        void IncrementAngularSpeed() { angularSpeed += 0.001; }
        void DecrementAngularSpeed() { if(angularSpeed - 0.001 > 0 ) angularSpeed -= 0.001; }

        float Getspeed() { return speed; }
        void Setspeed(float val) { speed = val; }

        glm::vec3 GetCenter() { return pos + dir; }

        void UpdatePosition(glm::vec3 pivotPos);
        void UpdateDirection(glm::vec3 pivotPos);

        void MoveFoward();
        void MoveBackward();
        void MoveRight();
        void MoveLeft();
        void MoveUp();
        void MoveDown();

        void TurnLeft();
        void TurnRight();

        void TurnMouseX(int diferenca);
        void TurnMouseY(int diferenca);

        void ZoomOut(SceneObject* pivot);
        void ZoomIn(SceneObject* pivot);
    protected:

    private:
        glm::vec3 pos;
        glm::vec3 dir;
        glm::vec3 up;
        glm::vec3 side;
        float angularSpeed;
        float speed;
};

#endif // CAMERA_H


