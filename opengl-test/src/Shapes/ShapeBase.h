#pragma once

#include "../Buffers/VertexBuffer.h"
#include <ext/matrix_transform.hpp>

#include "../Graphics.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Resources/Shader.h"
#include "../Resources/ShaderPool.h"

/// <summary>
/// The base shape from which all objects inherit.
/// </summary>
class ShapeBase
{

protected:	
	std::shared_ptr<VertexBuffer> _vb;
	std::shared_ptr<vertex_buffer_layout> _layout;
	std::shared_ptr<IndexBuffer> _indexBuffer;
	
	std::unique_ptr<VertexArray> _va;

	bool _hasIndexBuffer = false;

	glm::mat4 _model = glm::mat4(1.0f);

	void RefreshModel()
	{
		_model = _translate * _scale * _rotate;
	}

public:
	glm::mat4 _rotate;
	glm::mat4 _translate;
	glm::mat4 _scale;
	int _size;
	
	std::string TextureIdentifier;
		
	ShapeBase(ShapeBase* shape) : ShapeBase(shape->TextureIdentifier)
	{
		_vb = shape->_vb;
		_layout = shape->_layout;
		_indexBuffer = shape->_indexBuffer;

		_size = shape->_size;

		_va = std::make_unique<VertexArray>();
		_va->AddBuffer(_vb, _layout);
	}

	ShapeBase(std::string textureIdentifier)
	{
		_rotate = glm::mat4(1.0f);
		_translate = glm::mat4(1.0f);
		_scale = glm::mat4(1.0f);
		TextureIdentifier = textureIdentifier;
		
		RefreshModel();
	}

	/// <summary>
	/// Scale the model with the by the given vector scalar.
	/// </summary>
	/// <param name="scale"></param>
	virtual void Scale(glm::vec3 scale)
	{
		_scale = glm::scale(_scale, scale);
		RefreshModel();
	}

	/// <summary>
	/// Rotate the model with the given rotate vector and the angle.
	/// </summary>
	/// <param name="rotate"></param>
	/// <param name="angle"></param>
	virtual void Rotate(glm::vec3 rotate, float angle)
	{
		_rotate = glm::rotate(_rotate, angle, rotate);
		RefreshModel();
	}

	/// <summary>
	/// Translate the model with the given translate vector.
	/// </summary>
	/// <param name="translate"></param>
	virtual void Translate(glm::vec3 translate)
	{
		_translate = glm::translate(_translate, translate);
		RefreshModel();
	}

	/// <summary>
	/// Initialize the model with a vertex buffer, array and layout.
	/// </summary>
	/// <param name="data"></param>
	/// <param name="size"></param>
	virtual void WithBuffer(void* data, int size)
	{
		_va = std::make_unique<VertexArray>();
		_vb = std::make_shared<VertexBuffer>(data, size);
		_layout = std::make_shared<vertex_buffer_layout>();
	}

	/// <summary>
	/// Initializes the buffer with a index buffer.
	/// </summary>
	/// <param name="indices"></param>
	/// <param name="size"></param>
	virtual void WithIndexBuffer(unsigned int* indices, unsigned int size)
	{
		_indexBuffer = std::make_unique<IndexBuffer>(indices, size);
		_hasIndexBuffer = true;
	}
		
	virtual void Bind() const
	{
		_va->Bind();
		if (_hasIndexBuffer)
			_indexBuffer->Bind();
	}

	virtual void Unbind() const
	{
		if (_hasIndexBuffer)
			_indexBuffer->Unbind();
		_va->Unbind();
	}

	/// <summary>
	/// Draw the given object to the game screen.
	/// </summary>
	/// <param name="graphics"></param>
	virtual void Draw(Graphics* graphics) = 0;

	virtual ~ShapeBase() = default;
};


