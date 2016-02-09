#include "DataStorage.h"

std::map<std::string, irr::video::ITexture*> DataStorage::textures;

DataStorage::DataStorage()
{

}

void DataStorage::setup(irr::video::IVideoDriver *driver){
    DataStorage::textures["wall.bmp"] = driver->getTexture("wall.bmp");
}
