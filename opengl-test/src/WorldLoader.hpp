#pragma  once

#include "Resources/ShaderPool.h"
#include "Resources/TexturePool.h"
#include "World/World.h"
#include "Shapes/Objects/Box.hpp"
#include "Shapes/Objects/BoxWood.hpp"
#include "Shapes/Objects/Models.hpp"
#include "Shapes/Objects/Sphere.hpp"


static float wallSize = 100;
static float wallHeight = 30;
static float translate = 30;

class WorldLoader
{	
	static void AddCoordinateLines(World* world)
	{
		float thickness = 0.3;
		float lenght = 200;

		Box* x = new Box();
		x->Translate(glm::vec3(-0, -0, -0));
		x->Scale(glm::vec3(UNIT_SIZE * lenght, UNIT_SIZE * thickness, UNIT_SIZE * thickness));
		x->ambient_color = glm::vec3(1, 0, 0);

		Box* y = new Box();
		y->Translate(glm::vec3(-0, -0, -0));
		y->Scale(glm::vec3(UNIT_SIZE * thickness, UNIT_SIZE * lenght, UNIT_SIZE * thickness));
		y->ambient_color = glm::vec3(0, 1, 0);

		Box* z = new Box();
		z->Translate(glm::vec3(-0, -0, -0));
		z->Scale(glm::vec3(UNIT_SIZE * thickness, UNIT_SIZE * thickness, UNIT_SIZE * lenght));
		z->ambient_color = glm::vec3(0, 0, 1);

		world->AddObjectShape(*x);
		world->AddObjectShape(*y);
		world->AddObjectShape(*z);
	}

	static void LoadRoom(World* world){	

		PBRTexturedBox* front = new PBRTexturedBox(wall_texture);
		front->Translate(glm::vec3(0, 0, -translate));
		front->Scale(glm::vec3(wallSize, wallHeight, 1));
		//
		PBRTexturedBox* back = new PBRTexturedBox(wall_texture);
		back->Translate(glm::vec3(0, 0, translate));
		back->Scale(glm::vec3(wallSize, wallHeight, 1));
		
		PBRTexturedBox* right = new PBRTexturedBox(wall_texture);
		right->Translate(glm::vec3(translate, 0, 0));
		right->Scale(glm::vec3(1, wallHeight, wallSize));		
		
		PBRTexturedBox* left = new PBRTexturedBox(wall_texture);
		left->Translate(glm::vec3(-translate, 0, 0));
		left->Scale(glm::vec3(1, wallHeight, wallSize));
		
		CubeShadowObject* lightBar = new CubeShadowObject("container");
		lightBar->Translate(glm::vec3(0, wallHeight - 5, -translate+1));
		lightBar->Scale(glm::vec3(wallSize, 1, 3));
		
		CubeShadowObject* ground = new CubeShadowObject("wood");
		ground->Translate(glm::vec3(0, 0, 0));
		ground->Scale(glm::vec3(wallSize, 0.1, wallSize));

		PBRTexturedBox* cube1 = new PBRTexturedBox(ground_texture);
		cube1->Translate(glm::vec3(-translate + 5, 0, -5));
		cube1->Scale(glm::vec3(5, 5, 5));
		
		// StatueMesh* statue  = new StatueMesh();
		// statue->Translate(glm::vec3(0, 1, -translate + 0.6));
		// statue->Scale(glm::vec3(0.05, 0.05, 0.05));
		
		// RomanArch* romanArch = new RomanArch();
		// romanArch->Translate(glm::vec3(0, 10, -translate + 0.8));
		// romanArch->Scale(glm::vec3(0.03, 0.03, 0.03)); 

		// DoubleCube* doubleCuebe = new DoubleCube();
		// doubleCuebe->Translate(glm::vec3(0, 20, 0));
		// doubleCuebe->Scale(glm::vec3(15, 15, 15));
		
		world->AddShadowShape(*ground);
		//world->AddShape(*statue);
		//world->AddShape(*romanArch);
		
		world->AddBPRShape(*front);
		world->AddBPRShape(*back);
		world->AddBPRShape(*right);
		world->AddBPRShape(*left);
		world->AddBPRShape(*cube1);
		//world->AddShape(*lightBar);
	}

	void SetupLighting(World* world) const
	{
		PointLight light1;
		light1.position = glm::vec3(0.0f, 5.0f, 0);
		light1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		light1.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		light1.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		light1.constant = 1.0f;
		light1.linear = 0.09f;
		light1.quadratic = 0.032f;

		PointLight light2 = light1;
		light2.position = glm::vec3(0, wallHeight *0.30, -translate + 5);

		PointLight light3 = light1;
		light3.position = glm::vec3(0, wallHeight *0.30, translate - 5);

		PointLight light4 = light1;
		light4.position = glm::vec3((wallSize / 2) - 2, wallHeight - 10, -translate + 2);
				
		PointLight light6 = light1;
		light6.position = glm::vec3(0, wallHeight - 10, -translate + 10);

		PointLight light7 = light1;
		light7.position = glm::vec3(-(wallSize / 2) + 2, wallHeight - 10, -translate + 10);

		PointLight light8 = light1;
		light8.position = glm::vec3((wallSize / 2) - 2, wallHeight - 10, -translate + 10);
		
		
		world->AddPointLight(light1);
		world->AddPointLight(light2);
		world->AddPointLight(light3);
		// world->AddPointLight(light4);
		// world->AddPointLight(light6);
		// world->AddPointLight(light7);
		// world->AddPointLight(light8);
		
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
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\metallness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\statue\\2k\\tgeodcxda_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\metallness.jpg"
		);

		PBRTextureEntry* pbrRomanArch = new PBRTextureEntry(romanArchTexture,
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\romanArch\\2k\\thedegyfa_2K_Albedo.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\romanArch\\2k\\thedegyfa_2K_Normal_LOD0.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\metallness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\romanArch\\2k\\thedegyfa_2K_Roughness.jpg",
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\textures\\metallness.jpg"
		);

		SimpleTextureEntry* uvTemplate = new SimpleTextureEntry("uvTemplateTexture", "res\\textures\\uvtemplate.bmp");
		SimpleTextureEntry* wood = new SimpleTextureEntry("wood", "res\\textures\\wood.png");
		ObjectTextureEntry* woodCrate = new ObjectTextureEntry("woodCrate", "res\\textures\\container2.bmp", "res\\textures\\container2_specular.bmp");
		
		TexturePool* pool = TexturePool::Instance();

		pool->AddPBRTexture(pbrtTextureEntry);
		pool->AddPBRTexture(pbrGroundTexture);
		pool->AddPBRTexture(pbrStatue);
		pool->AddPBRTexture(pbrRomanArch);
		pool->AddSimpleTexture(uvTemplate);
		pool->AddSimpleTexture(wood);
		pool->AddObjectTexture(woodCrate);
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

		// Shader* lightingShader = new Shader("res\\shaders\\lighting.shader", lightingShaderID);
		// lightingShader->Bind();
		// lightingShader->SetUniform1i("material.diffuseMap", 0);
		// lightingShader->SetUniform1i("material.specularMap", 1);
		
		Shader* debugShader = new Shader("res\\shaders\\shadowMapQuadDebug.shader", "debugShader");
		
		ShaderPool* pool = ShaderPool::Instance();

		pool->AddShader(pbrShader);
		pool->AddShader(objectShader);
		pool->AddShader(shadowMapShader);
		pool->AddShader(shadowMappingShader);
		pool->AddShader(debugShader);
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
					row
				);
				
				Sphere* sphere = new Sphere("wood");
				sphere->Scale(glm::vec3(0.70, 0.70, 0.70));
				sphere->Translate(transform);
				 
				world->AddShadowShape(*sphere);

				Sphere* sphere1 = new Sphere(wall_texture);
				sphere1->Translate(transform);
				sphere1->Scale(glm::vec3(0.75, 0.75, 0.75));
				
				world->AddBPRShape(*sphere1);
			}
		}
	}

public:
	WorldLoader() {  }
	
	void InitializeWorld(World* world) const
	{
		InitializeTextures(world);
		InitializeShaders(world);
		
		SetupLighting(world);
		world->Initialize();
		TestSpheres(world);

		LoadRoom(world);
		//AddCoordinateLines(world);

		//world->shadowMap.Init();
		
		// Initialize Resources

	}
};