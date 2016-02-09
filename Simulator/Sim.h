#ifndef SIM_H
#define SIM_H

#include "irrlicht/irrlicht.h"
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


class Sim
{
public:
    Sim();
    ~Sim();
    int start();

private:
    IrrlichtDevice *device = 0;
    IVideoDriver* driver = 0;
    ISceneManager* smgr = 0;
    IGUIEnvironment* guienv = 0;

    InputHandler ih;
    std::vector<SimObject*> objs;
};

#endif // SIM_H
