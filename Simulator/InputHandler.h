#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "irrlicht.h"

class InputHandler : public irr::IEventReceiver
{
public:
    //TODO, MAKE ALL THIS INTO THE .CPP FILE
    InputHandler(){
        for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

    virtual bool OnEvent(const irr::SEvent& event){
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif // INPUTHANDLER_H
