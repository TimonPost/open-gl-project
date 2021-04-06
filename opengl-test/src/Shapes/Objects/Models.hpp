#pragma once

#include "PBRTexturedBox.hpp"
 #include "../ShapeBase.h"
#include "../../WorldLoader.hpp"
#include "../../../objectLoader.h"
#include "../../Resources/ObjectReader.hpp"

class StatueMesh : public PBRTexturedObject
{

public:
    StatueMesh() : PBRTexturedObject(statue_texture, "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\statue\\2k\\export.obj")
    {
    }
};

 class RomanArch : public PBRTexturedObject
 {

 public:
     RomanArch() : PBRTexturedObject(statue_texture, "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\romanArch\\2k\\thedegyfa_LOD0.obj")
     {
     }     
 };

 class DoubleCube : public PBRTexturedObject
 {

 public:
     DoubleCube() : PBRTexturedObject(statue_texture, "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\doubleCube.obj")
     {
     }     
 };