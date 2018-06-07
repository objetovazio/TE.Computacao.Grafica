#ifndef CAMERA_H
#define CAMERA_H
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>


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
        float GetangularSpeed() { return angularSpeed; }
        void SetangularSpeed(float val) { angularSpeed = val; }
        float Getspeed() { return speed; }
        void Setspeed(float val) { speed = val; }

        glm::vec3 GetCenter() { return pos + dir;; }

        void MoveFoward();
        void MoveBackward();
        void MoveRight();
        void MoveLeft();
        void MoveUp();
        void MoveDown();

        void TurnLeft();
        void TurnRight();

    protected:

    private:
        glm::vec3 pos;
        glm::vec3 dir;
        glm::vec3 up;
        float angularSpeed;
        float speed;
};

#endif // CAMERA_H


