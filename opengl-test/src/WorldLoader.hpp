#pragma  once

#include "Resources/ShaderPool.h"
#include "Resources/TexturePool.h"
#include "World/World.h"
#include "Shapes/Objects/Box.hpp"
#include "Shapes/Objects/BoxMetalic.hpp"
#include "Shapes/Objects/BoxWood.hpp"
#include "Shapes/Objects/sphere.hpp"
#include "Shapes/Objects/Statue.hpp"


static float wallSize = 50;
static float wallHeight = 20;
static float translate = 25;

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
		x->RefreshShaderProperties();

		Box* y = new Box();
		y->Translate(glm::vec3(-0, -0, -0));
		y->Scale(glm::vec3(UNIT_SIZE * thickness, UNIT_SIZE * lenght, UNIT_SIZE * thickness));
		y->ambient_color = glm::vec3(0, 1, 0);
		y->RefreshShaderProperties();

		Box* z = new Box();
		z->Translate(glm::vec3(-0, -0, -0));
		z->Scale(glm::vec3(UNIT_SIZE * thickness, UNIT_SIZE * thickness, UNIT_SIZE * lenght));
		z->ambient_color = glm::vec3(0, 0, 1);
		z->RefreshShaderProperties();

		world->AddShadowShape(*x);
		world->AddBPRShape(*y);
		world->AddBPRShape(*z);
	}

	static void LoadRoom(World* world){	

		BoxMetalic* wall1 = new BoxMetalic(wall_texture);
		wall1->Translate(glm::vec3(0, 0, -translate));
		wall1->Scale(glm::vec3(wallSize, wallHeight, 1));

		BoxMetalic* wall2 = new BoxMetalic(wall_texture);
		wall2->Translate(glm::vec3(0, 0, translate));
		wall2->Scale(glm::vec3(wallSize, wallHeight, 1));

		BoxMetalic* wall3 = new BoxMetalic(wall_texture);
		wall3->Translate(glm::vec3(translate, 0, 0));
		wall3->Scale(glm::vec3(1, wallHeight, wallSize));


		BoxMetalic* wall4 = new BoxMetalic(wall_texture);
		wall4->Translate(glm::vec3(-translate, 0, 0));
		wall4->Scale(glm::vec3(1, wallHeight, wallSize));
		
		Box* lightBar = new Box();
		lightBar->Translate(glm::vec3(0, wallHeight - 5, -translate+1));
		lightBar->Scale(glm::vec3(wallSize, 1, 3));
		lightBar->ambient_color = glm::vec3(1,1,1);
		lightBar->RefreshShaderProperties();
		
		BoxMetalic* ground = new BoxMetalic("wood");
		ground->Translate(glm::vec3(0, 0, 0));
		ground->Scale(glm::vec3(wallSize, 0.1, wallSize));

		// StatueMesh* statue  = new StatueMesh();
		// statue->Translate(glm::vec3(0, 1, -translate + 0.6));
		// statue->Scale(glm::vec3(0.05, 0.05, 0.05));
		
		// RomanArch* romanArch = new RomanArch();
		// romanArch->Translate(glm::vec3(0, 10, -translate + 0.8));
		// romanArch->Scale(glm::vec3(0.03, 0.03, 0.03)); 

		DoubleCube* doubleCuebe = new DoubleCube();
		doubleCuebe->Translate(glm::vec3(0, 20, 0));
		doubleCuebe->Scale(glm::vec3(15, 15, 15));
		
		world->AddShadowShape(*ground);
		//world->AddShape(*statue);
		//world->AddShape(*romanArch);
		
		world->AddBPRShape(*wall1);
		world->AddBPRShape(*wall2);
		// world->AddShape(*wall3);
		// world->AddShape(*wall4);

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
		light2.position = glm::vec3(0, wallHeight - 10, -translate + 2);

		PointLight light3 = light1;
		light3.position = glm::vec3(-(wallSize / 2) + 2, wallHeight - 10, -translate + 2);

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
		// world->AddPointLight(light3);
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

		SpotLight spotLight;
		spotLight.position = world->MainCamera()->position;
		spotLight.direction = world->MainCamera()->Front;

		spotLight.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		spotLight.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		spotLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		spotLight.constant = 1.0f;
		spotLight.linear = 0.09f;
		spotLight.quadratic = 0.032f;

		spotLight.cutOff = glm::cos(glm::radians(12.5f));
		spotLight.outerCutOff = glm::cos(glm::radians(15.0f));

		world->SetSpotLight(spotLight);
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
		
		TexturePool* pool = TexturePool::Instance();

		pool->AddPBRTexture(pbrtTextureEntry);
		pool->AddPBRTexture(pbrGroundTexture);
		pool->AddPBRTexture(pbrStatue);
		pool->AddPBRTexture(pbrRomanArch);
		pool->AddSimpleTexture(uvTemplate);
		pool->AddSimpleTexture(wood);
	}

	const std::string PBRShader = "pbrShader";
	
	static void InitializeShaders(World* world)
	{
		
		Shader* pbrShader = new Shader("res\\shaders\\PBR.shader", "pbrShader");
		Shader* lightsShader = new Shader("res\\shaders\\lights.shader", "lightsShader");
		Shader* objectShader = new Shader("res\\shaders\\object.shader", "objectShader");
		Shader* objectNoTextureShader = new Shader("res\\shaders\\objectNoTexture.shader", "objectNoTextureShader");
		Shader* baseShapeShader = new Shader("res\\shaders\\baseShape.shader", "baseShapeShader");
		Shader* cube3dShader = new Shader("res\\shaders\\cube3d.shader", "cube3dShader");
		
		Shader* shadowMapShaderInstance = new Shader("res\\shaders\\shadowMap.shader", shadowMapShader);
		Shader* shadowMappingShaderInstance = new Shader("res\\shaders\\shadowMapping.shader", shadowMappingShader);
		Shader* debugShader = new Shader("res\\shaders\\shadowMapQuadDebug.shader", "debugShader");
		
		ShaderPool* pool = ShaderPool::Instance();

		pool->AddShader(pbrShader);
		pool->AddShader(objectShader);
		pool->AddShader(objectNoTextureShader);
		pool->AddShader(baseShapeShader);
		pool->AddShader(cube3dShader);
		pool->AddShader(lightsShader);
		pool->AddShader(shadowMapShaderInstance);
		pool->AddShader(shadowMappingShaderInstance);
		pool->AddShader(debugShader);
	}
	//
	// static void TestSpheres(World* world)
	// {
	// 	int nrRows = 3;
	// 	int nrColumns = 6;
	// 	float spacing = 0.5;
	//
	// 	for (int row = 0; row < nrRows; ++row)
	// 	{
	// 		for (int col = 0; col < nrColumns; ++col)
	// 		{
	// 			Sphere* sphere = new Sphere();
	// 			sphere->Scale(glm::vec3(0.25, 0.25, 0.25));
	// 			sphere->Translate(glm::vec3(
	// 				(float)(col - (nrColumns / 2)) * spacing,
	// 				1+(float)(row - (nrRows / 2)) * spacing,
	// 				row
	// 			));
	//
	// 			world->AddBPRShape(*sphere);
	//
	// 		}
	// 	}
	// }

public:
	WorldLoader() {  }
	
	void InitializeWorld(World* world) const
	{
		InitializeTextures(world);
		InitializeShaders(world);
		
		SetupLighting(world);
		world->Initialize();
		//TestSpheres(world);

		LoadRoom(world);
		//AddCoordinateLines(world);

		//world->shadowMap.Init();
		
		// Initialize Resources

	}
};