#include "InputHandler.h"

InputHandler::InputHandler(bool u){
    for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;

    acc = irr::core::vector3df(0,0,0);
    rot = irr::core::vector3df(0,0,0);
    useKey = u;
}

void InputHandler::update(irr::f32 dt, irr::core::vector3df dir){
    acc.X = 0;
    acc.Y = 0;
    acc.Z = 0;
    if (useKey){
        //input processing
        irr::core::vector3df temp;
        temp.X = -cos(dir.Y*3.141589f/180.0f);
        if (fabs(dir.Y) > 0){
            float dZ = sin(dir.Y*3.141589f/180.0f);
            temp.Z = dZ;
        }
        temp.normalize();
        if(IsKeyDown(irr::KEY_KEY_W)){
            acc = temp*5;
        } else if(IsKeyDown(irr::KEY_KEY_S)) {
            acc = -temp*5;
        }

        if(IsKeyDown(irr::KEY_KEY_A)) {
            acc.X = -temp.Z*5;
            acc.Z = temp.X*5;
        } else if(IsKeyDown(irr::KEY_KEY_D)) {
            acc.X = temp.Z*5;
            acc.Z = -temp.X*5;
        }
        if (IsKeyDown(irr::KEY_SPACE))
            acc.Y = 5 ;
        else if (IsKeyDown(irr::KEY_LSHIFT))
            acc.Y = -5;

        if (IsKeyDown(irr::KEY_KEY_Q)){
            rot.Y += -50*dt;
        }else if (IsKeyDown(irr::KEY_KEY_E)){
            rot.Y += 50*dt;
        }
    }

}


void InputHandler::setAcc(irr::core::vector3df a){
    acc = a;
}
void InputHandler::setRot(irr::core::vector3df r){
    rot = r;
}

irr::core::vector3df InputHandler::getAcc(){
    return acc;
}
irr::core::vector3df InputHandler::getRot(){
    return rot;
}
