#pragma  once

#include "Resources/ShaderPool.h"
#include "Resources/TexturePool.h"
#include "Resources/MeshPool.h"
#include "World/GameWorld.h"
#include "Shapes/Objects/Box.hpp"
#include "Shapes/ShadowObjectBase.hpp"
#include "Shapes/PBRTexturedObjectBase.hpp"
#include "Shapes/Objects/Models.hpp"
#include "Shapes/Objects/Sphere.hpp"
#include "../Resources/objectLoader.h"

class WorldLoader
{
	/// <summary>
	/// Adds the given meshes to the mesh pool.
	/// </summary>
	/// <param name="meshPool"></param>
	/// <param name="meshes"></param>
	/// <param name="meshId"></param>
	static void AddMeshesToPool(MeshPool* meshPool, std::vector<Mesh>& meshes, std::string meshId)
	{
		for (auto& m : meshes)
		{
			auto* heapMesh = new Mesh(m);
			heapMesh->MeshName = meshId;
			meshPool->AddMesh(heapMesh);
		}
	}
	
	static void InitializeCoordinateLines(GameWorld* world)
	{
		float thickness = 0.3;
		float lenght = 200;

		Box* x = new Box(wood_textureID);
		x->Translate(glm::vec3(-0, -0, -0));
		x->Scale(glm::vec3(1 * lenght, 1 * thickness, 1 * thickness));
		x->ambient_color = glm::vec3(1, 0, 0);

		Box* y = new Box(wood_textureID);
		y->Translate(glm::vec3(-0, -0, -0));
		y->Scale(glm::vec3(1 * thickness, 1 * lenght, 1 * thickness));
		y->ambient_color = glm::vec3(0, 1, 0);

		Box* z = new Box(wood_textureID);
		z->Translate(glm::vec3(-0, -0, -0));
		z->Scale(glm::vec3(1 * thickness, 1 * thickness, 1 * lenght));
		z->ambient_color = glm::vec3(0, 0, 1);

		world->AddObjectShape(*x);
		world->AddObjectShape(*y);
		world->AddObjectShape(*z);
	}

	static void AddMeshes(GameWorld* world, std::vector<MeshObjectShape*> meshes)
	{
		for (auto mesh : meshes)
		{
			world->AddBPRShape(*mesh);
		}
	}

	static void AddShadowMesh(GameWorld* world, ShapeBase* shape)
	{
		shape->Scale(glm::vec3(0.9,0.9,0.9));
		world->AddShadowShape(*shape);
	}

	/// <summary>
	/// Initaizlizes shadow spheres.
	/// </summary>
	/// <param name="world"></param>
	static void InitializeShadowSpheres(GameWorld* world)
	{
		int nrRows = 5;
		int nrColumns = 6;
		float spacing = 2;

		for (int row = 0; row < nrRows; ++row)
		{
			for (int col = 0; col < nrColumns; ++col)
			{
				glm::vec3 transform = glm::vec3(
					(float)(col - (nrColumns / 2)) * spacing,
					5 + (float)(row - (nrRows / 2)) * spacing,
					-row + 7
				);

				glm::vec3 scale = glm::vec3(0.75, 0.75, 0.75);

				Sphere* sphere = new Sphere(wood_textureID);
				sphere->Translate(transform);
				sphere->Scale(scale);

				AddShadowMesh(world, sphere);

				world->AddShadowShape(*sphere);

				Sphere* sphere1 = new Sphere(sphere_textureID);
				sphere1->Translate(transform);
				sphere1->Scale(scale);

				world->AddBPRShape(*sphere1);
			}
		}
	}

	/// <summary>
	/// Initializes window wall.
	/// </summary>
	/// <param name="world"></param>
	static void InitializeWindows(GameWorld* world)
	{
		int nrRows = 3;
		int nrColumns = 6;
		float spacing = 10;

		for (int row = 0; row < nrRows; ++row)
		{
			for (int col = 0; col < nrColumns; ++col)
			{
				glm::vec3 transform = glm::vec3(
					((float)(col - (nrColumns / 2)) * spacing) + 10,
					10 + (float)(row - (nrRows / 2)) * spacing,
					30
				);

				if (row == 0) {
					Building* building = new Building();
					building->Translate(transform);
					building->Scale(glm::vec3(0.034, 0.034, 0.034));
					building->Rotate(glm::vec3(0, 1, 0), glm::radians(180.0f));
					AddMeshes(world, building->meshObjects);
				}
				else {
					WindowMesh* window = new WindowMesh();
					window->Translate(transform);
					window->Scale(glm::vec3(0.034, 0.034, 0.034));
					window->Rotate(glm::vec3(0, 1, 0), glm::radians(180.0f));
					AddMeshes(world, window->meshObjects);
				}
			}
		}
	}

	/// <summary>
	/// Initializes the roof tiles.
	/// </summary>
	/// <param name="world"></param>
	static void InitializeRoof(GameWorld* world)
	{
		int nrRows = 10;
		int nrColumns = 10;
		float spacing = 6;

		for (int row = 0; row < nrRows; ++row)
		{
			for (int col = 0; col < nrColumns; ++col)
			{
				glm::vec3 transform = glm::vec3(
					((float)(col - (nrColumns / 2)) * spacing)+2,
					30,
					((float)(row - (nrRows / 2)) * spacing)+2
				);

				Box* roofTile = new Box(brick_textureID);
				roofTile->Translate(transform);
				roofTile->Scale(glm::vec3(4, 0.5,4));
				world->AddBPRShape(*roofTile);
			}
		}
	}

	/// <summary>
	/// Initializes the animated spheres.
	/// </summary>
	/// <param name="world"></param>
	static void InitializeAnimatedShperes(GameWorld* world)
	{
		float offset = 2;
		glm::vec3 ballScale = glm::vec3(0.80, 0.80, 0.80);
		glm::vec3 transform = glm::vec3(0.5, 0.5, 0.5);
		
		Sphere* sphere1 = new Sphere(cloth_textureID, new VerticalCircleAnimation());
		sphere1->Translate(glm::vec3(-translate + 5, 6, -20 - offset));
		sphere1->Scale(ballScale);
		world->AddBPRShape(*sphere1);
		Sphere* sphere4 = new Sphere(wood_textureID, new ZLineAnimation());
		sphere4->Translate(glm::vec3(-translate + 5 + offset, 6, -20));
		sphere4->Scale(ballScale);
		world->AddBPRShape(*sphere4);
		
		Sphere* sphere2 = new Sphere(gold_textureID, new HorizontalCircleAnimation());
		sphere2->Translate(glm::vec3(translate- 5, 6, -20-offset));
		sphere2->Scale(ballScale);
		world->AddBPRShape(*sphere2);
		
		Sphere* sphere3 = new Sphere(midevil_textureID, new XLineAnimation());
		sphere3->Translate(glm::vec3(translate - 5-offset, 6, -20));
		sphere3->Scale(ballScale);
		world->AddBPRShape(*sphere3);
	}

	/// <summary>
	/// Load main game room and components.
	/// </summary>
	/// <param name="world"></param>
	static void LoadRoom(GameWorld* world) {
		InitializeWindows(world);
		InitializeRoof(world);
		InitializeAnimatedShperes(world);
		
		// Walls
		Box* sky = new Box(sky_texture_ID);
		sky->Translate(glm::vec3(0, 0, translate + 5));
		sky->Scale(glm::vec3(wallSize, wallHeight, 1));

		PBRTexturedBox* back = new PBRTexturedBox(wall_textureID);
		back->Translate(glm::vec3(0, 0,-translate));
		back->Scale(glm::vec3(wallSize, wallHeight, 1));
		
		PBRTexturedBox* right = new PBRTexturedBox(wall_textureID);
		right->Translate(glm::vec3(translate, 0, 0));
		right->Scale(glm::vec3(1, wallHeight, wallSize));

		PBRTexturedBox* left = new PBRTexturedBox(wall_textureID);
		left->Translate(glm::vec3(-translate, 0, 0));
		left->Scale(glm::vec3(1, wallHeight, wallSize));

		// Ground and roof
		PBRTexturedBox* ground = new PBRTexturedBox(ground_textureID);
		ground->Translate(glm::vec3(0, 0, 0));
		ground->Scale(glm::vec3(wallSize, 0.1, wallSize));

		PBRTexturedBox* roof = new PBRTexturedBox(brick_textureID);
		roof->Translate(glm::vec3(0, 0, 0));
		roof->Scale(glm::vec3(wallSize, wallHeight, wallSize));

		CubeShadowObject* groundShadowPlane = new CubeShadowObject(wood_textureID);
		groundShadowPlane->Translate(glm::vec3(0, 0.2, -2));
		groundShadowPlane->Scale(glm::vec3(20, 0.1, 20));
		
		StatueMesh* statue = new StatueMesh();
		statue->Translate(glm::vec3(-translate + 4, 0, translate-4));
		statue->Scale(glm::vec3(0.05, 0.05, 0.05));
		statue->Rotate(glm::vec3(0, 1, 0), glm::radians(120.0f));
		AddMeshes(world, statue->meshObjects);

		StatueMesh* statue1 = new StatueMesh();
		statue1->Translate(glm::vec3(translate - 4, 0, translate - 4));
		statue1->Scale(glm::vec3(0.05, 0.05, 0.05));
		statue1->Rotate(glm::vec3(0, 1, 0), glm::radians(-120.0f));
		AddMeshes(world, statue1->meshObjects);

		glm::vec3 scale = glm::vec3(0.030, 0.030, 0.030);

		Post* rightPost = new Post();
		rightPost->Translate(glm::vec3(-9, 0.2, 7.5));
		rightPost->Scale(scale);
		rightPost->Rotate(glm::vec3(0, 1, 0), glm::radians(90.0f));
		AddMeshes(world, rightPost->meshObjects);

		Post* leftPost = new Post();
		leftPost->Translate(glm::vec3(9, 0.2, 7.5));
		leftPost->Scale(scale);
		leftPost->Rotate(glm::vec3(0, 1, 0), glm::radians(90.0f));
		AddMeshes(world, leftPost->meshObjects);

		Post* bottomPost = new Post();
		bottomPost->Translate(glm::vec3(9, 0.2, -10));
		bottomPost->Scale(scale);
		bottomPost->Rotate(glm::vec3(0, 1, 0), glm::radians(180.0f));
		AddMeshes(world, bottomPost->meshObjects);

		Post* bottomLeftPost = new Post();
		bottomLeftPost->Translate(glm::vec3(-9, 0.2, -10));
		bottomLeftPost->Scale(scale);
		bottomLeftPost->Rotate(glm::vec3(0, 1, 0), glm::radians(-90.0f));
		AddMeshes(world, bottomLeftPost->meshObjects);
				
		world->AddShadowShape(*groundShadowPlane);
		world->AddObjectShape(*sky);
		
		world->AddBPRShape(*ground);
		world->AddBPRShape(*back);
		world->AddBPRShape(*right);
		world->AddBPRShape(*left);

	}

	/// <summary>
	/// Initialize lighting in the scene.
	/// </summary>
	/// <param name="world"></param>
	void InitializeLighting(GameWorld* world) const
	{
		// base light
		PointLight light1;
		light1.position = glm::vec3(-2.0f, 8.0f, 10.0f);
		light1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		light1.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		light1.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		light1.constant = 1.0f;
		light1.linear = 0.09f;
		light1.quadratic = 0.032f;

		// room lights
		PointLight light2 = light1;
		light2.position = glm::vec3(10, wallHeight *0.50, 20);

		PointLight light3 = light1;
		light3.position = glm::vec3(-10, wallHeight *0.50, 20);

		// ceiling lights
		PointLight light4 = light1;
		light4.position = glm::vec3(0, wallHeight -4, -10);

		PointLight light5 = light1;
		light5.position = glm::vec3(0, wallHeight - 4, +10);

		// animation lights
		PointLight light6 = light1;
		light6.position = glm::vec3(-20, 5,-20);

		PointLight light7 = light1;
		light7.position = glm::vec3(22, 5, -20);
		
		world->AddPointLight(light1);
		world->AddPointLight(light2);
		world->AddPointLight(light3);
		world->AddPointLight(light4);
		world->AddPointLight(light5);
		world->AddPointLight(light6);
		world->AddPointLight(light7);

		// directional light
		DirectionalLight directionalLight;
		directionalLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		directionalLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		directionalLight.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		directionalLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);

		world->SetDirectionalLight(directionalLight);
	}

	/// <summary>
	/// Loads textures and adds them to the texture pool such that they can be accuired by the renderer for rendering objects.
	/// </summary>
	/// <param name="world"></param>
	static void InitializeTextures(GameWorld* world)
	{
		PBRTextureEntry* wallTextureEntry = new PBRTextureEntry(wall_textureID,
			"res\\textures\\wall\\2k\\albedo.jpg",
			"res\\textures\\wall\\2k\\normal.jpg",
			"res\\textures\\wall\\2k\\metalness.jpg",
			"res\\textures\\wall\\2k\\roughness.jpg",
			"res\\textures\\wall\\2k\\ao.jpg"
		);

		PBRTextureEntry* groundTextureEntry = new PBRTextureEntry(ground_textureID,
			"res\\textures\\floor\\2k\\albedo.jpg",
			"res\\textures\\floor\\2k\\normal.jpg",
			"res\\textures\\floor\\2k\\metallness.jpg",
			"res\\textures\\floor\\2k\\roughness.jpg",
			"res\\textures\\floor\\2k\\ao.jpg"
		);

		PBRTextureEntry* statueTextureEntry = new PBRTextureEntry(statue_textureID,
			"res\\objs\\statue\\2k\\tgeodcxda_2K_Albedo.jpg",
			"res\\objs\\statue\\2k\\tgeodcxda_2K_Normal_LOD0.jpg",
			"res\\textures\\empty_metall.png",
			"res\\objs\\statue\\2k\\tgeodcxda_2K_Roughness.jpg",
			"res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* buildingTextureEntry = new PBRTextureEntry(building_textureID,
			"res\\objs\\building\\2k\\vdiwfgydw_2K_Albedo.jpg",
			"res\\objs\\building\\2k\\vdiwfgydw_2K_Normal_LOD0.jpg",
			"res\\textures\\empty_metall.png",
			"res\\objs\\building\\2k\\vdiwfgydw_2K_Roughness.jpg",
			"res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* ironFenceTextureEntry = new PBRTextureEntry(ironFence_textureID,
			"res\\objs\\post\\2k\\ujwrfhsdw_2K_Albedo.jpg",
			"res\\objs\\post\\2k\\ujwrfhsdw_2K_Normal_LOD0.jpg",
			"res\\textures\\empty_metall.png",
			"res\\objs\\post\\2k\\ujwrfhsdw_2K_Roughness.jpg",
			"res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* windowTextureEntry = new PBRTextureEntry(window_textureID,
			"res\\objs\\window\\2k\\vdisaihdw_2K_Albedo.jpg",
			"res\\objs\\window\\2k\\vdisaihdw_2K_Normal_LOD0.jpg",
			"res\\textures\\empty_metall.png",
			"res\\objs\\window\\2k\\vdisaihdw_2K_Roughness.jpg",
			"res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* sphereTextureEntry = new PBRTextureEntry(sphere_textureID,
			"res\\textures\\sphere\\2k\\vdfjbfvv_2K_Albedo.jpg",
			"res\\textures\\sphere\\2k\\vdfjbfvv_2K_Normal.jpg",
			"res\\textures\\sphere\\2k\\vdfjbfvv_2K_Metalness.jpg",
			"res\\textures\\sphere\\2k\\vdfjbfvv_2K_Roughness.jpg",
			"res\\textures\\sphere\\2k\\vdfjbfvv_2K_AO.jpg"
		);

		PBRTextureEntry* brickTextureEntry = new PBRTextureEntry(brick_textureID,
			"res\\textures\\brick\\2k\\ulmmbgbo_2K_Albedo.jpg",
			"res\\textures\\brick\\2k\\ulmmbgbo_2K_Normal.jpg",
			"res\\textures\\empty_metall.png",
			"res\\textures\\brick\\2k\\ulmmbgbo_2K_Roughness.jpg",
			"res\\textures\\brick\\2k\\ulmmbgbo_2K_AO.jpg"
		);

		PBRTextureEntry* woodTextureEntry = new PBRTextureEntry(wood_textureID,
			"res\\textures\\wood\\ulkjbfuew_2K_Albedo.jpg",
			"res\\textures\\wood\\ulkjbfuew_2K_Normal.jpg",
			"res\\textures\\empty_metall.png",
			"res\\textures\\wood\\ulkjbfuew_2K_Roughness.jpg",
			"res\\textures\\wood\\ulkjbfuew_2K_AO.jpg"
		);

		PBRTextureEntry* clothTextureEntry = new PBRTextureEntry(cloth_textureID,
			"res\\textures\\cloth\\vb1kfdt_2K_Albedo.jpg",
			"res\\textures\\cloth\\vb1kfdt_2K_Normal.jpg",
			"res\\textures\\empty_metall.png",		
			"res\\textures\\cloth\\vb1kfdt_2K_Roughness.jpg",
			"res\\textures\\cloth\\vb1kfdt_2K_AO.jpg"
		);

		PBRTextureEntry* medievalIronTextureEntry = new PBRTextureEntry(midevil_textureID,
			"res\\textures\\medievalIron\\ub1gfbwew_2K_Albedo.jpg",
			"res\\textures\\medievalIron\\ub1gfbwew_2K_Normal.jpg",
			"res\\textures\\empty_metall.png",
			"res\\textures\\medievalIron\\ub1gfbwew_2K_Roughness.jpg",
			"res\\textures\\medievalIron\\ub1gfbwew_2K_AO.jpg"
		);

		PBRTextureEntry* goldTextureEntry = new PBRTextureEntry(gold_textureID,
			"res\\textures\\gold\\schvfgwp_2K_Albedo.jpg",
			"res\\textures\\gold\\schvfgwp_2K_Normal.jpg",
			"res\\textures\\gold\\schvfgwp_2K_Metalness.jpg",
			"res\\textures\\gold\\schvfgwp_2K_Roughness.jpg",
			"res\\textures\\empty_ao.png"
		);
		
		SimpleTextureEntry* wood = new SimpleTextureEntry(wood_textureID, "res\\textures\\wood.png");
		SimpleTextureEntry* skyTexture = new SimpleTextureEntry(sky_texture_ID, "res\\textures\\sky.jpg");
		
		TexturePool* pool = TexturePool::Instance();

		pool->AddPBRTexture(wallTextureEntry);
		pool->AddPBRTexture(groundTextureEntry);
		pool->AddPBRTexture(statueTextureEntry);
		pool->AddPBRTexture(buildingTextureEntry);
		pool->AddPBRTexture(ironFenceTextureEntry);
		pool->AddPBRTexture(sphereTextureEntry);
		pool->AddPBRTexture(brickTextureEntry);		
		pool->AddPBRTexture(windowTextureEntry);
		pool->AddPBRTexture(clothTextureEntry);
		pool->AddPBRTexture(goldTextureEntry);
		pool->AddPBRTexture(medievalIronTextureEntry);
		pool->AddPBRTexture(woodTextureEntry);
		
		pool->AddSimpleTexture(wood);
		pool->AddSimpleTexture(skyTexture);
	}
		
	/// <summary>
	/// Loads meshes and adds them to the mesh pool such that objects can require a copy of the loaded meshes.
	/// </summary>
	/// <param name="world"></param>
	static void InitializeMeshes(GameWorld* world)
	{
		MeshPool* pool = MeshPool::Instance();
		
		std::vector<Mesh> meshes = ObjectReader::LoadMeshes("res\\objs\\building\\2k\\vdiwfgydw_LOD5.obj");
		AddMeshesToPool(pool, meshes, building_meshID);
		
		std::vector<Mesh> meshes1 = ObjectReader::LoadMeshes("res\\objs\\post\\2k\\ujwrfhsdw_LOD4.obj");
		AddMeshesToPool(pool, meshes1, ironFence_meshID);

		std::vector<Mesh> meshes2 = ObjectReader::LoadMeshes("res\\objs\\window\\2k\\vdisaihdw_LOD5.obj");
		AddMeshesToPool(pool, meshes2, window_meshID);

		std::vector<Mesh> meshes3 = ObjectReader::LoadMeshes("res\\objs\\statue\\2k\\tgeodcxda_LOD5.obj");
		AddMeshesToPool(pool, meshes3, statue_meshID);

		std::vector<Mesh> meshes4 = ObjectReader::LoadMeshes("res\\objs\\box.obj");
		AddMeshesToPool(pool, meshes4, cube_meshID);
	}

	/// <summary>
	/// Loads shaders and adds them to the shader pool such that they can be accuired by the renderer for rendering objects.
	/// </summary>
	/// <param name="world"></param>
	static void InitializeShaders(GameWorld* world)
	{		
		Shader* pbrShader = new Shader("res\\shaders\\PBR.shader", pbr_shaderID);
		pbrShader->Bind();
		pbrShader->SetUniform1i("albedoMap", 0);
		pbrShader->SetUniform1i("normalMap", 1);
		pbrShader->SetUniform1i("metallicMap", 2);
		pbrShader->SetUniform1i("roughnessMap", 3);
		pbrShader->SetUniform1i("aoMap", 4);
		
		Shader* objectShader = new Shader("res\\shaders\\object.shader", object_shaderID);
		Shader* objectNoTextureShader = new Shader("res\\shaders\\object.shader", object_no_texture_shaderID);
		
		Shader* shadowMapShader = new Shader("res\\shaders\\shadowMap.shader", shadow_map_shaderID);
		Shader* shadowMapGenerationShader = new Shader("res\\shaders\\shadowMapping.shader", shadow_passtrough_shaderID);
		shadowMapGenerationShader->Bind();
		shadowMapGenerationShader->SetUniform1i("material.diffuseMap", 0);
		shadowMapGenerationShader->SetUniform1i("shadowMap", 1);
						
		ShaderPool* pool = ShaderPool::Instance();

		pool->AddShader(pbrShader);
		pool->AddShader(objectShader);
		pool->AddShader(objectNoTextureShader);
		pool->AddShader(shadowMapShader);
		pool->AddShader(shadowMapGenerationShader);
	}

public:	
	void InitializeWorld(GameWorld* world) const
	{
		InitializeTextures(world);
		InitializeShaders(world);
		InitializeMeshes(world);		
		InitializeLighting(world);
		
		world->Initialize();
		InitializeShadowSpheres(world);

		LoadRoom(world);
	}
};