#pragma once

#include "../Buffers/VertexBuffer.h"
#include <ext/matrix_transform.hpp>

#include "../Graphics.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Resources/Shader.h"
#include "../Resources/ShaderPool.h"

class ShapeBase
{
public:
	glm::mat4 _rotate;
	glm::mat4 _translate;
	glm::mat4 _scale;

protected:
	

	std::shared_ptr<VertexBuffer> _vb;
	std::shared_ptr<VertexBufferLayout> _layout;
	std::shared_ptr<IndexBuffer> _indexBuffer;

	Shader* _shader;
	std::unique_ptr<VertexArray> _va;

	bool _hasIndexBuffer = false;
	int _size;
	glm::mat4 _model = glm::mat4(1.0f);

	void RefreshModel()
	{
		_model = _translate * _scale * _rotate;
	}

public:
	std::string TextureIdentifier;
	std::string ShaderIdentifier;
	
	ShapeBase(ShapeBase* shape) : ShapeBase(shape->TextureIdentifier, shape->ShaderIdentifier)
	{
		_vb = shape->_vb;
		_layout = shape->_layout;
		_indexBuffer = shape->_indexBuffer;

		_size = shape->_size;

		_va = std::make_unique<VertexArray>();
		_va->AddBuffer(_vb, _layout);

		WithShader(shape->ShaderIdentifier);
	}

	ShapeBase(std::string textureIdentifier, std::string shaderIdentifier)
	{
		_rotate = glm::mat4(1.0f);
		_translate = glm::mat4(1.0f);
		_scale = glm::mat4(1.0f);
		TextureIdentifier = textureIdentifier;
		ShaderIdentifier = shaderIdentifier;

		RefreshModel();
	}
	
	void Scale(glm::vec3 scale)
	{
		_scale = glm::scale(_scale, scale);
		RefreshModel();
	}

	void Rotate(glm::vec3 rotate, float angle)
	{
		_rotate = glm::rotate(_rotate, angle, rotate);
		RefreshModel();
	}

	void Translate(glm::vec3 translate)
	{
		_translate = glm::translate(_translate, translate);
		RefreshModel();
	}

	void WithBuffer(void* data, int size)
	{
		_va = std::make_unique<VertexArray>();
		_vb = std::make_shared<VertexBuffer>(data, size);
		_layout = std::make_shared<VertexBufferLayout>();
	}

	void WithShader(std::string shaderIdentifier)
	{
		_shader = ShaderPool::Instance()->GetShaderById(shaderIdentifier);
	}

	void WithIndexBuffer(unsigned int* indices, unsigned int size)
	{
		_indexBuffer = std::make_unique<IndexBuffer>(indices, size);
		_hasIndexBuffer = true;
	}

	virtual void Bind() const
	{
		_shader->Bind();
		_va->Bind();
		if (_hasIndexBuffer)
			_indexBuffer->Bind();
	}

	virtual void Unbind() const
	{
		if (_hasIndexBuffer)
			_indexBuffer->Unbind();
		_va->Unbind();
		_shader->Unbind();
	}

	virtual void Draw(Graphics* graphics) = 0;

	virtual ~ShapeBase() = default;
};


