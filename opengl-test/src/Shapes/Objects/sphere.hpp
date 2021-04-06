#pragma once

#include "../ShapeBase.h"
#include "../../Resources/TexturePool.h"
#include "../../Buffers/FrameBuffer.h"

class Sphere : public ShapeBase
{
private:
	unsigned int indexCount;
	
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    unsigned int indices[8320];
    float data[33800];
    
	
	void CreateCircleArray()
	{
        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        unsigned int indexCounter = 0;
		
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices[indexCounter++] = y * (X_SEGMENTS + 1) + x;
                    indices[indexCounter++] = (y + 1) * (X_SEGMENTS + 1) + x;
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices[indexCounter++] = (y + 1) * (X_SEGMENTS + 1) + x;
                    indices[indexCounter++] = y * (X_SEGMENTS + 1) + x;
                }
            }
            oddRow = !oddRow;
        }
        //indexCount = indices.size();

        unsigned int counter = 0;
        for (std::size_t i = 0; i < positions.size(); ++i)
        {
            data[counter++] =positions[i].x;
            data[counter++] =  positions[i].y;
            data[counter++] = positions[i].z;
            if (normals.size() > 0)
            {
                data[counter++] = normals[i].x;
                data[counter++] = normals[i].y;
                data[counter++] = normals[i].z;
            }
            if (uv.size() > 0)
            {
                data[counter++] = uv[i].x;
                data[counter++] = uv[i].y;
            }
        }
	}

public:    	
	Sphere() : ShapeBase("wood", "pbrShader")
	{
		CreateCircleArray();

		WithBuffer(data, sizeof(data));
		WithIndexBuffer(indices, sizeof(indices));
		WithShader(ShaderIdentifier);

		_layout->AddFloat(3);	
		_layout->AddFloat(3);
        _layout->AddFloat(2);
		
		_va->AddBuffer(_vb, _layout);        
	}
    
	void ShapeBase::Draw(Graphics* graphics) override
	{		
        auto* render = graphics->Render;
        
		// Render object
       
		  
        
        _shader->SetUniformMatrix4fv("model", _model);
        _shader->SetUniformMatrix4fv("projection", render->P());
		
		glDrawElements(GL_TRIANGLE_STRIP, 8320, GL_UNSIGNED_INT, 0);

		texture->Unbind();
	}

	virtual ~Sphere()
	{
	}
};
