#pragma once

#include "PBRTexturedBox.hpp"
#include "../../Resources/MeshObject.hpp"
#include "../../Resources/ObjectReader.h"

class StatueMesh : public MeshesLoader
{

public:
    StatueMesh() : MeshesLoader(statue_texture, statue_meshID)
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
  

class Building : public MeshesLoader
 {
	
 public:
     Building() : MeshesLoader(building_texture, building_meshID)
     {   
     	
     }
 };

class Post : public MeshesLoader
{

public:
    Post() : MeshesLoader(post_texture, post_meshID)
    {
    }
};

class WindowMesh : public MeshesLoader
{

public:
    WindowMesh() : MeshesLoader(window_texture, window_meshID)
    {
    }
};