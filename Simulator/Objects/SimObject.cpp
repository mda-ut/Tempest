#include "SimObject.h"

SimObject::SimObject(std::string name, irr::scene::ISceneNode *n)
{
    this->name = name;
    node = n;
    n->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    fri.X = -1;
    fri.Y = -1;
    fri.Z = -1;
}

void SimObject::act(){
    irr::core::vector3df pos = node->getPosition();

    if (acc.getLength() > 0){
        vel += acc;
        //acc += fri;
        std::string msg = std::to_string(acc.X) + ' ' + std::to_string(acc.Y) + ' ' + std::to_string(acc.Z) + " Act";
        Logger::Log(msg);
        msg = std::to_string(vel.X) + ' ' + std::to_string(vel.Y) + ' ' + std::to_string(vel.Z) + " Act";
        Logger::Log(msg);
        if (fabs(acc.X)-friction < 0)
            acc.X = 0;
        else
            acc.X -= friction;
        if (fabs(acc.Y)-friction < 0)
            acc.Y = 0;
        else
            acc.Y -= friction;
        if (fabs(acc.Z)-friction < 0)
            acc.Z = 0;
        else
            acc.Z -= friction;
    }
    if (vel.getLength() > 0){
        pos += vel;

        if (fabs(vel.X)-0.01f < 0){
            vel.X = 0;
        }else{
            vel.X += std::copysign(0.01f, -vel.X);
        }
        if (fabs(vel.Y)-0.01f < 0){
            vel.Y = 0;
        }else{
            vel.Y += std::copysign(0.01f, -vel.Y);
        }

        node->setPosition(pos);
    }
    //std::string msg = std::to_string(acc.X) + ' ' + std::to_string(acc.Y) + ' ' + std::to_string(acc.Z) + " Act";
    //Logger::Log(msg);
}

void SimObject::setAcc(irr::core::vector3df a){
    this->acc.X = a.X;
    this->acc.Y = a.Y;
    this->acc.Z = a.Z;
    std::string msg = std::to_string(acc.X) + ' ' + std::to_string(acc.Y) + ' ' + std::to_string(acc.Z);
    Logger::Log(msg);
}
irr::core::vector3df SimObject::getAcc(){
    return acc;
}
