#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <map>
#include <string>
#include "irrlicht/irrlicht.h"

class DataStorage
{
public:
    DataStorage();
    static std::map<std::string, irr::video::ITexture*> textures;
    static void setup(irr::video::IVideoDriver*);
};

#endif // DATASTORAGE_H
