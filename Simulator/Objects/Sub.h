#ifndef SUB_H
#define SUB_H
#include "SimObject.h"
#include "irrlicht.h"
#include "InputHandler.h"

class Sub: public SimObject
{
public:
    Sub(std::string, irr::scene::ISceneNode*, InputHandler* ih);
    void setCam(irr::scene::ICameraSceneNode*);
    void update();
    irr::scene::ICameraSceneNode* getSceneNode(){
        return cam;
    }

private:
    irr::scene::ICameraSceneNode* cam = 0;
    InputHandler* ih;
};

#endif // SUB_H
