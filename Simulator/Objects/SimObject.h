#ifndef SIMOBJECT_H
#define SIMOBJECT_H
#include "irrlicht/vector3d.h"
#include "irrlicht.h"
#include "Logger.h"
#include "DataStorage.h"
#include <string>
#include <math.h>
#include <cmath>

class SimObject
{
public:
    SimObject(std::string, irr::scene::ISceneNode*);
    void act();

    void setAcc(irr::core::vector3df);
    irr::core::vector3df getAcc();

protected:
    std::string name;
    irr::scene::ISceneNode *node = 0;

    irr::core::vector3df vel;
    irr::core::vector3df acc;
    irr::core::vector3df fri;
    float friction = 0.1f;

};

#endif // SIMOBJECT_H
