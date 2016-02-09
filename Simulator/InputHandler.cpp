/*#include "InputHandler.h"

InputHandler::InputHandler()
{
    for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}
virtual bool InputHandler::OnEvent(const irr::SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
}
/*
// This is used to check whether a key is being held down
virtual bool IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

MyEventReceiver()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}
*/
