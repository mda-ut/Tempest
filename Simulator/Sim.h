#ifndef SIM_H
#define SIM_H

#include "irrlicht.h"
#include "Objects/SimObject.h"
#include "Objects/Buoy.h"
#include "Logger.h"
#include "InputHandler.h"
#include "DataStorage.h"
#include <vector>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
 * The main class of the Simulator
 */
class Sim
{
public:
    Sim();

    /*
     * Starts running the simulator
     */
    int start();

private:
    //Irrlicht stuff
    IrrlichtDevice *device = 0;
    IVideoDriver* driver = 0;
    ISceneManager* smgr = 0;
    IGUIEnvironment* guienv = 0;
    ISceneNodeAnimatorCollisionResponse* anim = 0;

    InputHandler ih;                //handles input from user
    std::vector<SimObject*> objs;   //list of simulated objects
};

#endif // SIM_H
