#pragma once

#include "../ObjShapeBase.h"
#include "../../Graphics.h"
#include "../../Resources/TexturePool.h"

class PBRTexturedBox : public PBRTexturedObjectBase
{

public:
	PBRTexturedBox(const std::string textureId, const std::string shaderId) : PBRTexturedObjectBase(
		textureId,
		shaderId,
		"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\box.obj")
	{
	}

	void PBRTexturedObjectBase::Draw(Graphics* graphics) override
	{
		auto* texture = TexturePool::Instance()->GetSimpleTextureById(TextureIdentifier);
		texture->Bind();
		
		_shader->SetUniformMatrix4fv("model", _model);
		
		glDrawArrays(GL_TRIANGLES, 0, _size);

		texture->Unbind();
	}

	virtual ~PBRTexturedBox() = default;
};

class PBRTexturedObject : public PBRTexturedObjectBase
{

public:
	PBRTexturedObject(const std::string textureId, const std::string shaderId, const std::string objectPath) : PBRTexturedObjectBase(
		textureId,
		shaderId,
		objectPath)
	{
	}

	void PBRTexturedObjectBase::Draw(Graphics* graphics) override
	{
		auto* texture = TexturePool::Instance()->GetPBRById(TextureIdentifier);
		texture->Bind();

		auto* render = graphics->Render;

		graphics->ApplyLightsToShader(_shader);

		_shader->SetUniformMatrix4fv("model", _model);
		_shader->SetUniformMatrix4fv("projection", render->P());
		_shader->SetUniformMatrix4fv("view", render->V());

		glDrawArrays(GL_TRIANGLES, 0, _size);

		texture->Unbind();
	}

	virtual ~PBRTexturedObject() = default;
};

