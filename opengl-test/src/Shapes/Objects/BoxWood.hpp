#pragma once

#include "../ShapeBase.h"

// class BoxWood : public Box
// {
//
// public:
//
// 	BoxWood() : Box("lightsShader")
// 	{
// 		_shader->Bind();
// 		_shader->SetUniform1i("material.diffuse", 0);
// 		_shader->SetUniform1i("material.specular", 1);
// 		_shader->Unbind();
// 	}
//
// 	void ObjShapeBase::Draw(Graphics* graphics) override
// 	{
// 		auto* render = graphics->Render;
//
// 		_shader->SetUniform3fv("viewPos", render->camera->position);
// 		_shader->SetUniform1f("material.shininess", 32.0f);
// 		
// 		graphics->ApplyLightsToShader(_shader.get());
// 		
// 		_shader->SetUniformMatrix4fv("model", _model);
// 		_shader->SetUniformMatrix4fv("projection", render->P());
// 		_shader->SetUniformMatrix4fv("view", render->V());
// 		
// 		glActiveTexture(GL_TEXTURE0);
// 		glBindTexture(GL_TEXTURE_2D, diffuseMap);
// 		
// 		// bind specular map
// 		glActiveTexture(GL_TEXTURE1);
// 		glBindTexture(GL_TEXTURE_2D, specularMap);
//
//
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 	}
//
// 	virtual ~BoxWood() = default;
// };

