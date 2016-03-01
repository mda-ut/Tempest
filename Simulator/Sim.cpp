#include "Sim.h"


Sim::Sim()
{
    /**
     * Setup Irrlicht stuff
     */
    device = createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
            false, true, false, &ih);
    if (!device){
        Logger::Log("FATAL- Could not create device");
        return;
    }
    device->setWindowCaption(L"MDA Simulator 0.1");

    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    /**
     * Load textures into the map
     */
    DataStorage::setup(driver);

    /**
     * Loads the nodes into the scene
     */
    ISceneNode *b = smgr->addSphereSceneNode();
    if (!b){
        Logger::Log("Could not create sphere node");
    }else{
        Buoy *ball = new Buoy("ball", b);
        objs.push_back(ball);
    }
}

Sim::~Sim(){

}

int Sim::start(){
    //if the device cannot be created, just exit the program
    if (!device)
        return 1;    

    guienv->addStaticText(L"Hello World!",
        rect<s32>(10,10,260,22), true);

    //Add camera node to a static position. Need to change later to have this on the sub
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    // In order to do framerate independent movement, we have to know
    // how long it was since the last frame
    u32 then = device->getTimer()->getTime();
    while(device->run())
    {
        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        //temp stuff for testing
        SimObject *b = objs.at(0);
        vector3df acc = b->getAcc();
        std::string msg = std::to_string(acc.X) + ' ' + std::to_string(acc.Y)
                + ' ' + std::to_string(acc.Z) + " Sim";
        Logger::Log(msg);

        //input processing
        if(ih.IsKeyDown(irr::KEY_KEY_W)){
            acc.Y += 5 * frameDeltaTime;
        }
        else if(ih.IsKeyDown(irr::KEY_KEY_S))
            acc.Y -= 5 * frameDeltaTime;
        if(ih.IsKeyDown(irr::KEY_KEY_A))
            acc.X -= 5 * frameDeltaTime;
        else if(ih.IsKeyDown(irr::KEY_KEY_D))
            acc.X += 5 * frameDeltaTime;

        //std::string msg = "SIM " + std::to_string(acc.X) + ' ' + std::to_string(acc.Y) + ' ' + std::to_string(acc.Z);
        //Logger::Log(msg);
        b->setAcc(acc);

        for (SimObject *so: objs){
            //so->setAcc(acc);
            so->act();
        }

        driver->beginScene(true, true, SColor(255,100,101,140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->closeDevice();
    return 0;
}
