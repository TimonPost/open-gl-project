#pragma once

#include "PBRTexturedBox.hpp"
#include "../../Resources/MeshesLoader.hpp"

class StatueMesh : public MeshLoader
{

public:
    StatueMesh() : MeshLoader(statue_textureID, statue_meshID)
    {
    }
};

class Building : public MeshLoader
 {
	
 public:
     Building() : MeshLoader(building_textureID, building_meshID)
     {   
     	
     }
 };

class Post : public MeshLoader
{

public:
    Post() : MeshLoader(ironFence_textureID, ironFence_meshID)
    {
    }
};

class WindowMesh : public MeshLoader
{

public:
    WindowMesh() : MeshLoader(window_textureID, window_meshID)
    {
    }
};