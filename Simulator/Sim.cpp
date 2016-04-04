#include "Sim.h"


Sim::Sim(cv::Mat* frame, InputHandler* in)
{
    this->frame = frame;
    this->ih = in;
    /**
     * Setup Irrlicht stuff
     */
    //device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1280, 960), 16,
      //      false, true, false, &ih);
    SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
    //params.AntiAlias = 8;
    params.DriverType = video::EDT_OPENGL;
    params.WindowSize = core::dimension2d<u32>(640, 480);
    params.EventReceiver = ih;
    device = createDeviceEx(params);
    if (!device){
        Logger::Log("FATAL- Could not create device");
        return;
    }
    device->setWindowCaption(L"MDA Simulator 1.0");

    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    /**
     * Load textures into the map
     */
    DataStorage::loadTextures(driver);

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

    ISceneNode *s = smgr->addCubeSceneNode();
    Sub *sub = new Sub("Sub", s, ih);
    objs.push_back(sub);

    //Light and Fog
    ILightSceneNode* light1 = smgr->addLightSceneNode( 0, core::vector3df(0,500,0), video::SColorf(0.3f,0.3f,0.3f), 50000.0f, 1 );
    driver->setFog(video::SColor(0, 120,140,160), video::EFT_FOG_LINEAR, 20, 250, .001f, false, false);
    ISceneNode * scenenode = smgr->getRootSceneNode();
    scenenode->setMaterialFlag(EMF_FOG_ENABLE, true);
    light1->setMaterialFlag(EMF_FOG_ENABLE, true);

    //Load obstacles (need to be separated so that buoys can move)
    IAnimatedMesh* mesh = smgr->getMesh("assets/obstacles.3ds");
    IMeshSceneNode * node = 0;
    if (mesh)
        node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0);

    if (node)
    {
        node->setMaterialFlag(EMF_FOG_ENABLE, true);
        node->setMaterialFlag(EMF_LIGHTING, true);
        node->setScale(core::vector3df(20,20,20));
    }

    IAnimatedMesh* roomMesh = smgr->getMesh("assets/stadium.3ds");
    IMeshSceneNode * roomNode = 0;
    if (roomMesh)
        roomNode = smgr->addOctreeSceneNode(roomMesh->getMesh(0), 0);


    if (roomNode)
    {
        roomNode->setMaterialFlag(EMF_FOG_ENABLE, true);
        roomNode->setMaterialFlag(EMF_LIGHTING, true);
        roomNode->setScale(core::vector3df(20,20,20));
    }

    scene::ITriangleSelector* selector = 0;

    if (node)
    {
        node->setPosition(core::vector3df(0,0,0));

        selector = smgr->createOctreeTriangleSelector(
                node->getMesh(), node, 128);
        node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }

    //ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.05f);
    //ICameraSceneNode* camera = smgr->addCameraSceneNode(s, vector3df(0,10,0), vector3df(0,0,0));
    Logger::Log(s->getPosition());
    cameras[0] = smgr->addCameraSceneNode(s, s->getPosition());
    cameras[0]-> bindTargetAndRotation(true);
    cameras[1] = smgr->addCameraSceneNode(s);
    cameras[2] = smgr->addCameraSceneNode(s, s->getPosition(), vector3df(0,0,0));
    camChilds[1] = smgr->addEmptySceneNode(cameras[1]);
    camChilds[1]->setPosition(vector3df(0,-1,0));
    cameras[1]->setUpVector(vector3df(-1,0,0));
    s->setPosition(vector3df(-200, 212, 443));

    //First vector input is the radius of the collidable object
    anim = smgr->createCollisionResponseAnimator(
    selector, s, vector3df(7.5f,7.5f,7.5f),
    vector3df(0,0,0), vector3df(0,0,0));

    if (selector)
    {
        selector->drop(); // As soon as we're done with the selector, drop it.
        s->addAnimator(anim);
        //camera->addAnimator(anim);
        //anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }
    //node->drop();

}

//Sim::~Sim(){

//}

int Sim::start(){
    //if the device cannot be created, just exit the program
    if (!device)
        return 1;    

    guienv->addStaticText(L"Hello World!",
        rect<s32>(10,10,260,22), true);

    //Add camera node to a static position. Need to change later to have this on the sub
    cameras[3] = smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    bool collision;

    // In order to do framerate independent movement, we have to know
    // how long it was since the last frame
    u32 then = device->getTimer()->getTime();

    while(device->run())
    {
        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        ih->update(frameDeltaTime);
        Logger::Log("FDT");
        Logger::Log(frameDeltaTime);
        for (SimObject *so: objs){
            if (so->getName() == "Sub"){

                so->setRot(ih->getRot());
                Logger::Log(so->getRot());
                so->setAcc(ih->getAcc());

                if (ih->IsKeyDown(irr::KEY_KEY_R)){
                   so->reset();
                }

                ///offsets for camera stuff
                //vector3df temp = so->getPos();
                vector3df temp;
                temp.X = -cos(so->getRot().Y*3.141589f/180.0f);
                if (fabs(so->getRot().Y) > 0){
                    float dZ = sin(so->getRot().Y*3.141589f/180.0f);
                    temp.Z = dZ;
                    Logger::Log(dZ);
                }
                temp.normalize();
                temp *= 20;
                Logger::Log("temp look:");
                Logger::Log(temp);
                cameras[0]->setTarget(so->getPos() + temp);
                //cameras[0]->setRotation(so->getRot());
                //cameras[0]->setRotation(vector3df(0,0,0));

                temp = so->getPos();
                temp.Y -= 10;

                cameras[1]->setTarget(temp);
                //Logger::Log(cameras[1]->getScale());
                //cameras[1]->setTarget(camChilds[1]->getAbsolutePosition());
                //cameras[1]->setRotation(so->getRot());
                //cameras[1]->setRotation(vector3df(0,0,0));
                //cameras[1]->setRotation(so->getPos());
                //cameras[1]->setPosition(so->getPos());
                cameras[1]->setRotation(temp);

                temp = so->getPos();
                temp.Z += 20;
                cameras[2]->setTarget(temp);

                temp = so->getPos();
                temp.Z -= 20;
                temp.Y += 20;
                cameras[3]->setPosition(temp);
                cameras[3]->setTarget(so->getPos());
                //Logger::Log(std::to_string(so->getAcc().X));
            }
            so->update(frameDeltaTime);
            //ih->setAcc();
        }
        //collision check
        collision = anim->collisionOccurred();
        if (collision)
            Logger::Log("collision");


        driver->setViewPort(rect<s32>(0,0,resX, resY));
        driver->beginScene(true, true, SColor(255,100,101,140));

        smgr->setActiveCamera(cameras[0]);
        driver->setViewPort(rect<s32>(0,0,resX/2,resY/2));
        smgr->drawAll();
        smgr->setActiveCamera(cameras[1]);
        driver->setViewPort(rect<s32>(resX/2,0,resX,resY/2));
        smgr->drawAll();
        smgr->setActiveCamera(cameras[2]);
        driver->setViewPort(rect<s32>(0,resY/2,resX/2,resY));
        smgr->drawAll();
        smgr->setActiveCamera(cameras[3]);
        driver->setViewPort(rect<s32>(resX/2,resY/2,resX,resY));
        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();

        //convert Irrlicht render into OpenCV Mat
        IImage* image = driver->createScreenShot();
        for(int y = 0; y < frame->rows; y++){
            for(int x = 0; x < frame->cols; x++){
                SColor color = image->getPixel(x, y).color;
                if (color.getBlue()+150 > 255)
                    color.setBlue(255);
                else
                    color.setBlue(color.getBlue()+150);
                cv::Vec3b CVColor(color.getBlue(), color.getGreen(), color.getRed());
                frame->at<cv::Vec3b>(y,x) = CVColor;
            }
        }
        cv::imshow("frame", *frame);
        cv::waitKey(1);
        delete image;

    }
    smgr->drop();
    device->closeDevice();
    return 0;
}
