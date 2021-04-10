#pragma  once

#include "Resources/ShaderPool.h"
#include "Resources/TexturePool.h"
#include "Resources/MeshPool.h"
#include "World/World.h"
#include "Shapes/Objects/Box.hpp"
#include "Shapes/Objects/BoxWood.hpp"
#include "Shapes/Objects/Models.hpp"
#include "Shapes/Objects/Sphere.hpp"
#include "../Resources/objectLoader.h"



class WorldLoader
{	
	static void AddCoordinateLines(World* world)
	{
		float thickness = 0.3;
		float lenght = 200;

		Box* x = new Box(uvTemplateTexture);
		x->Translate(glm::vec3(-0, -0, -0));
		x->Scale(glm::vec3(UNIT_SIZE * lenght, UNIT_SIZE * thickness, UNIT_SIZE * thickness));
		x->ambient_color = glm::vec3(1, 0, 0);

		Box* y = new Box(uvTemplateTexture);
		y->Translate(glm::vec3(-0, -0, -0));
		y->Scale(glm::vec3(UNIT_SIZE * thickness, UNIT_SIZE * lenght, UNIT_SIZE * thickness));
		y->ambient_color = glm::vec3(0, 1, 0);

		Box* z = new Box(uvTemplateTexture);
		z->Translate(glm::vec3(-0, -0, -0));
		z->Scale(glm::vec3(UNIT_SIZE * thickness, UNIT_SIZE * thickness, UNIT_SIZE * lenght));
		z->ambient_color = glm::vec3(0, 0, 1);

		world->AddObjectShape(*x);
		world->AddObjectShape(*y);
		world->AddObjectShape(*z);
	}

	static void AddMeshes(World* world, vector<MeshObjectShape*> meshes)
	{
		for (auto mesh : meshes)
		{
			world->AddBPRShape(*mesh);
		}
	}

	static void AddShadowMeshes(World* world, ShapeBase* shape)
	{
		shape->Scale(glm::vec3(0.9,0.9,0.9));
		world->AddShadowShape(*shape);
	}

	static void TestSpheres(World* world)
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

				Sphere* sphere = new Sphere("wood");
				sphere->Translate(transform);
				sphere->Scale(scale);

				AddShadowMeshes(world, sphere);

				world->AddShadowShape(*sphere);

				Sphere* sphere1 = new Sphere(sphere_textureID);
				sphere1->Translate(transform);
				sphere1->Scale(scale);

				world->AddBPRShape(*sphere1);
			}
		}
	}
	
	static void WindowWall(World* world)
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

	static void Roof(World* world)
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

	static void LoadBallPosts(World* world)
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
		
		Sphere* sphere2 = new Sphere(goldShpereID, new HorizontalCircleAnimation());
		sphere2->Translate(glm::vec3(translate- 5, 6, -20-offset));
		sphere2->Scale(ballScale);
		world->AddBPRShape(*sphere2);
		
		Sphere* sphere3 = new Sphere(medievalIronTextureID, new XLineAnimation());
		sphere3->Translate(glm::vec3(translate - 5-offset, 6, -20));
		sphere3->Scale(ballScale);
		world->AddBPRShape(*sphere3);
	}
	
	static void LoadRoom(World* world) {				
		WindowWall(world);
		Roof(world);
		LoadBallPosts(world);
		
		// Walls
		Box* sky = new Box(skyTextureID);
		sky->Translate(glm::vec3(0, 0, translate + 5));
		sky->Scale(glm::vec3(wallSize, wallHeight, 1));

		PBRTexturedBox* back = new PBRTexturedBox(wall_texture);
		back->Translate(glm::vec3(0, 0,-translate));
		back->Scale(glm::vec3(wallSize, wallHeight, 1));
		
		PBRTexturedBox* right = new PBRTexturedBox(wall_texture);
		right->Translate(glm::vec3(translate, 0, 0));
		right->Scale(glm::vec3(1, wallHeight, wallSize));

		PBRTexturedBox* left = new PBRTexturedBox(wall_texture);
		left->Translate(glm::vec3(-translate, 0, 0));
		left->Scale(glm::vec3(1, wallHeight, wallSize));

		// Ground and roof
		CubeShadowObject* ground = new CubeShadowObject(ground_texture);
		ground->Translate(glm::vec3(0, 0, 0));
		ground->Scale(glm::vec3(wallSize, 0.1, wallSize));

		PBRTexturedBox* roof = new PBRTexturedBox(brick_textureID);
		roof->Translate(glm::vec3(0, 0, 0));
		roof->Scale(glm::vec3(wallSize, wallHeight, wallSize));

		CubeShadowObject* groundShadowPlane = new CubeShadowObject("wood");
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

		// RomanArch* romanArch = new RomanArch();
		// romanArch->Translate(glm::vec3(0, 10, -translate + 0.8));
		// romanArch->Scale(glm::vec3(0.03, 0.03, 0.03)); 


		world->AddShadowShape(*groundShadowPlane);
		world->AddObjectShape(*sky);
		
		world->AddBPRShape(*ground);
		//world->AddBPRShape(*roof);
		//world->AddBPRShape(*building);
		world->AddBPRShape(*back);
		world->AddBPRShape(*right);
		world->AddBPRShape(*left);

	}

	void SetupLighting(World* world) const
	{
		PointLight light1;
		light1.position = glm::vec3(-2.0f, 8.0f, 10.0f);
		light1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		light1.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		light1.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		light1.constant = 1.0f;
		light1.linear = 0.09f;
		light1.quadratic = 0.032f;

		PointLight light2 = light1;
		light2.position = glm::vec3(10, wallHeight *0.50, 20);

		PointLight light3 = light1;
		light3.position = glm::vec3(0, wallHeight *0.50, 20);

		PointLight light4 = light1;
		light4.position = glm::vec3(0, wallHeight -4, -10);

		PointLight light5 = light1;
		light5.position = glm::vec3(0, wallHeight - 4, +10);

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
				
		DirectionalLight directionalLight;
		directionalLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		directionalLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		directionalLight.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		directionalLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);

		world->SetDirectionalLight(directionalLight);
	}

	static void InitializeTextures(World* world)
	{
		PBRTextureEntry* pbrtTextureEntry = new PBRTextureEntry(wall_texture,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wall\\2k\\albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wall\\2k\\normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wall\\2k\\metalness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wall\\2k\\roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wall\\2k\\ao.jpg"
		);

		PBRTextureEntry* pbrGroundTexture = new PBRTextureEntry(ground_texture,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\floor\\2k\\albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\floor\\2k\\normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\floor\\2k\\metallness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\floor\\2k\\roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\floor\\2k\\ao.jpg"
		);

		PBRTextureEntry* pbrStatue = new PBRTextureEntry(statue_texture,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\statue\\2k\\tgeodcxda_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\statue\\2k\\tgeodcxda_2K_Normal_LOD0.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\statue\\2k\\tgeodcxda_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* wall = new PBRTextureEntry(building_texture,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\building\\2k\\vdiwfgydw_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\building\\2k\\vdiwfgydw_2K_Normal_LOD0.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\building\\2k\\vdiwfgydw_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* post = new PBRTextureEntry(post_texture,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\post\\2k\\ujwrfhsdw_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\post\\2k\\ujwrfhsdw_2K_Normal_LOD0.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\post\\2k\\ujwrfhsdw_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* window = new PBRTextureEntry(window_texture,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\window\\2k\\vdisaihdw_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\window\\2k\\vdisaihdw_2K_Normal_LOD0.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\window\\2k\\vdisaihdw_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_ao.png"
		);

		PBRTextureEntry* sphere = new PBRTextureEntry(sphere_textureID,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\sphere\\2k\\vdfjbfvv_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\sphere\\2k\\vdfjbfvv_2K_Normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\sphere\\2k\\vdfjbfvv_2K_Metalness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\sphere\\2k\\vdfjbfvv_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\sphere\\2k\\vdfjbfvv_2K_AO.jpg"
		);

		PBRTextureEntry* brick = new PBRTextureEntry(brick_textureID,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\brick\\2k\\ulmmbgbo_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\brick\\2k\\ulmmbgbo_2K_Normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\brick\\2k\\ulmmbgbo_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\brick\\2k\\ulmmbgbo_2K_AO.jpg"
		);

		PBRTextureEntry* woodSphere = new PBRTextureEntry(wood_textureID,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wood\\ulkjbfuew_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wood\\ulkjbfuew_2K_Normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wood\\ulkjbfuew_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\wood\\ulkjbfuew_2K_AO.jpg"
		);

		PBRTextureEntry* clothSphere = new PBRTextureEntry(cloth_textureID,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\cloth\\vb1kfdt_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\cloth\\vb1kfdt_2K_Normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\cloth\\vb1kfdt_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\cloth\\vb1kfdt_2K_AO.jpg"
		);

		PBRTextureEntry* medievalIronSphere = new PBRTextureEntry(medievalIronTextureID,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\medievalIron\\ub1gfbwew_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\medievalIron\\ub1gfbwew_2K_Normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\medievalIron\\ub1gfbwew_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\medievalIron\\ub1gfbwew_2K_AO.jpg"
		);

		PBRTextureEntry* goldSphere = new PBRTextureEntry(goldShpereID,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\gold\\schvfgwp_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\gold\\schvfgwp_2K_Normal.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\gold\\schvfgwp_2K_Metalness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\gold\\schvfgwp_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_ao.png"
		);
		
		// PBRTextureEntry* pbrRomanArch = new PBRTextureEntry(romanArchTexture,
		// 	"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\romanArch\\2k\\thedegyfa_2K_Albedo.jpg",
		// 	"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\romanArch\\2k\\thedegyfa_2K_Normal_LOD0.jpg",
		// 	"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\metallness.jpg",
		// 	"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\romanArch\\2k\\thedegyfa_2K_Roughness.jpg",
		// 	"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\empty_metall.png"
		// );

		SimpleTextureEntry* uvTemplate = new SimpleTextureEntry("uvTemplateTexture", "res\\textures\\uvtemplate.bmp");
		SimpleTextureEntry* wood = new SimpleTextureEntry("wood", "res\\textures\\wood.png");
		SimpleTextureEntry* skyTexture = new SimpleTextureEntry(skyTextureID, "res\\textures\\sky.jpg");
		
		TexturePool* pool = TexturePool::Instance();

		pool->AddPBRTexture(pbrtTextureEntry);
		pool->AddPBRTexture(pbrGroundTexture);
		pool->AddPBRTexture(pbrStatue);
		pool->AddPBRTexture(wall);
		pool->AddPBRTexture(post);
		pool->AddPBRTexture(sphere);
		pool->AddPBRTexture(brick);		
		pool->AddPBRTexture(window);
		pool->AddPBRTexture(clothSphere);
		pool->AddPBRTexture(goldSphere);
		pool->AddPBRTexture(medievalIronSphere);
		pool->AddPBRTexture(woodSphere);
		
		pool->AddSimpleTexture(uvTemplate);
		pool->AddSimpleTexture(wood);
		pool->AddSimpleTexture(skyTexture);
	}


	static void AddMesh(MeshPool* meshPool, std::vector<Mesh>& meshes, std::string meshId)
	{
		for (auto& mesh : meshes)
		{
			auto* heapMesh = new Mesh(mesh);
			heapMesh->MeshName = meshId;
			meshPool->AddMesh(heapMesh);
		}
	}
	
	static void InitializeMeshes(World* world)
	{
		MeshPool* pool = MeshPool::Instance();
		
		std::vector<Mesh> meshes = ObjectReader::LoadMeshes("C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\building\\2k\\vdiwfgydw_LOD5.obj");
		AddMesh(pool, meshes, building_meshID);
		
		std::vector<Mesh> meshes1 = ObjectReader::LoadMeshes("C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\post\\2k\\ujwrfhsdw_LOD4.obj");
		AddMesh(pool, meshes1, post_meshID);

		std::vector<Mesh> meshes2 = ObjectReader::LoadMeshes("C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\window\\2k\\vdisaihdw_LOD5.obj");
		AddMesh(pool, meshes2, window_meshID);

		std::vector<Mesh> meshes3 = ObjectReader::LoadMeshes("C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\statue\\2k\\tgeodcxda_LOD5.obj");
		AddMesh(pool, meshes3, statue_meshID);

		std::vector<Mesh> meshes4 = ObjectReader::LoadMeshes("C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\box.obj");
		AddMesh(pool, meshes4, cube_meshID);
	}
	
	static void InitializeShaders(World* world)
	{		
		Shader* pbrShader = new Shader("res\\shaders\\PBR.shader", pbrShaderID);
		pbrShader->Bind();
		pbrShader->SetUniform1i("albedoMap", 0);
		pbrShader->SetUniform1i("normalMap", 1);
		pbrShader->SetUniform1i("metallicMap", 2);
		pbrShader->SetUniform1i("roughnessMap", 3);
		pbrShader->SetUniform1i("aoMap", 4);
		
		Shader* objectShader = new Shader("res\\shaders\\object.shader", objectShaderID);
		
		Shader* shadowMapShader = new Shader("res\\shaders\\shadowMap.shader", shadowMapShaderID);
		Shader* shadowMappingShader = new Shader("res\\shaders\\shadowMapping.shader", shadowMappingShaderID);
		shadowMappingShader->Bind();
		shadowMappingShader->SetUniform1i("material.diffuseMap", 0);
		shadowMappingShader->SetUniform1i("shadowMap", 1);
				
		Shader* debugShader = new Shader("res\\shaders\\shadowMapQuadDebug.shader", "debugShader");
		
		ShaderPool* pool = ShaderPool::Instance();

		pool->AddShader(pbrShader);
		pool->AddShader(objectShader);
		pool->AddShader(shadowMapShader);
		pool->AddShader(shadowMappingShader);
		pool->AddShader(debugShader);
	}
	


public:
	WorldLoader() {  }
	
	void InitializeWorld(World* world) const
	{
		InitializeTextures(world);
		InitializeShaders(world);
		InitializeMeshes(world);
		
		SetupLighting(world);
		world->Initialize();
		TestSpheres(world);

		LoadRoom(world);
		AddCoordinateLines(world);
	}
};