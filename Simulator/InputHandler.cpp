#include "InputHandler.h"

InputHandler::InputHandler(bool u){
    for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;

    acc = irr::core::vector3df(0,0,0);
    rot = irr::core::vector3df(0,0,0);
    useKey = u;
}

void InputHandler::update(irr::f32 dt){
    acc.X = 0;
    acc.Y = 0;
    acc.Z = 0;
    if (useKey){
        //input processing
        if(IsKeyDown(irr::KEY_KEY_W)){
            acc.X = -5;
        }
        else if(IsKeyDown(irr::KEY_KEY_S))
            acc.X = 5;
        if(IsKeyDown(irr::KEY_KEY_A))
            acc.Z = -5;
        else if(IsKeyDown(irr::KEY_KEY_D))
            acc.Z = 5 ;
        if (IsKeyDown(irr::KEY_SPACE))
            acc.Y = 5 ;
        else if (IsKeyDown(irr::KEY_LSHIFT))
            acc.Y = -5;

        if (IsKeyDown(irr::KEY_KEY_Q)){
            rot.Y += -20*dt;
        }else if (IsKeyDown(irr::KEY_KEY_E)){
            rot.Y += 20*dt;
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
