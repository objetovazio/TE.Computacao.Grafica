#include "SceneControl.h"

SceneControl::SceneControl()
{
    this->Setr(0);
    this->Setg(0);
    this->Setb(0);
}

SceneControl::~SceneControl()
{
    //dtor
}

glm::vec3 SceneControl::GetNewSelectColor()
{
    unsigned int r, g, b;
    if(this->Getr() <= 255){
        this->IncrementR();
    }
    else if(this->Getg() <= 255)
    {
        this->Setr(0);
        this->IncrementG();
    }
    else
    {
        this->Setr(0);
        this->Setg(0);
        this->IncrementB();
    }

    r = this->Getr();
    g = this->Getg();
    b = this->Getb();

    glm::vec3 color = glm::vec3(r, g, b);

    return color;
}
