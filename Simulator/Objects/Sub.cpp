#include "Sub.h"

Sub::Sub(std::string name, irr::scene::ISceneNode* n, InputHandler* ih):SimObject(name, n)
{
    this->ih = ih;
}

void Sub::setCam(irr::scene::ICameraSceneNode *c){
    cam = c;
}

void Sub::update()
{
    acc = ih->getAcc();
    node->setRotation(ih->getRot());
    //SimObject::update();
    //cam->setPosition(node->getPosition());
    //ih->setAcc(acc);
    //ih->setRot(node->getRotation());
}
