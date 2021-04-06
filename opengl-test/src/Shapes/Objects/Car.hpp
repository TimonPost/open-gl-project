#pragma once

// #include "../ShapeBase.h"
// #include "../../Resources/Texture.hpp"

// class CarMesh : public ShapeBase
// {
//
// public:
// 	int texture_id;
// 	
// 	std::string name;
// 	vector<VertexFormatObjectWithUV> _verticies;
// 	
// 	CarMesh(CarMesh* toClone)
// 		: ShapeBase(toClone)
// 	{
// 	}
//
// 	CarMesh(const std::string& uv_map_path, vector<VertexFormatObjectWithUV> verticies) : ShapeBase("", "objectShader")
// 	{
// 		_verticies = verticies;
// 		
// 		texture_id = loadTexture(uv_map_path.c_str());
//
// 		_size = (sizeof(VertexFormatObjectWithUV) * verticies.size());
//
// 		WithBuffer(&_verticies[0], _size);
//
// 		_layout->AddFloat(3);
// 		_layout->AddFloat(3);
// 		_layout->AddFloat(2);
//
// 		_va->AddBuffer(_vb, _layout);
// 	}
//
// 	void Bind() const override
// 	{
// 		_va->Bind();
// 	}
//
// 	void Unbind() const override
// 	{
// 		_va->Unbind();
// 	}
// 	
// 	void Draw(Graphics* graphics) override
// 	{
// 		glBindTexture(GL_TEXTURE_2D, texture_id);
// 		
// 		glDrawArrays(GL_TRIANGLES, 0, _size);
//
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 	}
// };
//
// class Car : public ShapeBase
// {
// private:
//
//
// public:
// 	std::vector<CarMesh*> carMeshes;
// 	glm::vec3 light_position, ambient_color, diffuse_color,  specular;
// 	float power;
// 	
// 	Car(Car* teaPot) : ShapeBase(teaPot)
// 	{
// 	}
//
// 	Car() : ShapeBase("", "objectShader")
// 	{
// 		light_position = glm::vec3(10, 10, 10);
// 		ambient_color = glm::vec3(0.2, 0.2, 0.1);
// 		diffuse_color = glm::vec3(0.5, 0.5, 0.3);
// 		specular = glm::vec3(0.7, 0.7, 0.7);
// 		power = 1024;
// 		
// 		std::string carObj = "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\export4.obj";
//
// 		WithShader(ShaderIdentifier);
// 		
// 		std::vector<Mesh> meshes = ObjReader::LoadMeshes(carObj);
// 		
// 		for (int i = 0; i < meshes.size(); i++)
// 		{
// 			Mesh mesh = meshes[i];
// 			
// 			// Load vertex info
// 			vector<VertexFormatObjectWithUV> vertexes = vector<VertexFormatObjectWithUV>();
// 			for (int i = 0; i < mesh.Vertices.size(); i++)
// 			{
// 				Vertex vertex = mesh.Vertices[i];
// 				
// 				vertexes.push_back(VertexFormatObjectWithUV(vertex.Position, vertex.Normal, vertex.TextureCoordinate));
// 			}
// 						
// 			 if (mesh.MeshName.find("Wheel") != std::string::npos)
// 			 {
// 				 carMeshes.push_back(new CarMesh("res\\textures\\tire.bmp",  vertexes));
// 			
// 			 } else if(mesh.MeshName.find("BackLight") != std::string::npos)
// 			 {
// 				 carMeshes.push_back(new CarMesh("res\\textures\\front_light.bmp",  vertexes));
// 			 }
// 			 else if (mesh.MeshName.find("HeadLight") != std::string::npos)
// 			 {
// 				 carMeshes.push_back(new CarMesh("res\\textures\\back_light.bmp",  vertexes));
// 			 }
// 			 else 
// 			 {
// 				 carMeshes.push_back(new CarMesh("res\\textures\\uvtemplate.bmp", vertexes));
// 			 }
// 		}
// 	}
//
// 	void Bind() const override
// 	{
// 		_shader->Bind();
// 	}
//
// 	void Unbind() const override
// 	{
// 		_shader->Unbind();
// 	}
//
// 	void ShapeBase::Draw(Graphics* graphics) override
// 	{
// 			auto* render = graphics->Render;
// 		
// 		_shader->SetUniformMatrix4fv("mv", render->V() * _model);
// 		_shader->SetUniformMatrix4fv("projection", render->P());
// 		
// 		for (int i = 0; i < carMeshes.size(); i++)
// 		{
// 			CarMesh* carMesh = carMeshes[i];
// 			carMesh->Bind();
// 			carMesh->Draw(graphics);
// 			carMesh->Unbind();
// 		}
// 	}
//
// 	void RefreshShaderProperties() const
// 	{
// 		_shader->Bind();
// 		_shader->SetUniform3fv("light_pos", light_position);
// 		_shader->SetUniform3fv("mat_ambient", ambient_color);
// 		_shader->SetUniform3fv("mat_specular", specular);
// 		_shader->SetUniform1f("mat_power", power);
// 		_shader->Unbind();
// 	}
// 	
// 	virtual ~Car() = default;
// };
