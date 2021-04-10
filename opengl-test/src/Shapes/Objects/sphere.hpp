#pragma once

#include "../ShapeBase.h"

class Animation
{
public:
    glm::mat4 _translation;

    float tick = 0;
    float increment = 0;
    virtual  glm::vec3 Advance() = 0;
};

class HorizontalCircleAnimation : public Animation
{
public:
    HorizontalCircleAnimation()
	{
        increment = glm::pi<float>() / 60;
	}
	
    glm::vec3 Advance() override
	{
        tick += increment;
                
        return glm::vec3(0.0, glm::cos(tick)*0.15, glm::sin(tick)*0.15);
	}	
};

class VerticalCircleAnimation : public Animation
{
public:
    VerticalCircleAnimation()
    {
        increment = glm::pi<float>() / 60;
    }

    glm::vec3 Advance() override
    {
        tick += increment;

        return glm::vec3(glm::sin(tick) * 0.15, glm::cos(tick) * 0.15, 0.0);
    }
};

class ZLineAnimation : public Animation
{
public:
    ZLineAnimation()
    {
        increment = glm::pi<float>() / 60;
    }

    glm::vec3 Advance() override
    {
        tick += increment;

        return glm::vec3(0, 0, glm::cos(tick) * 0.15);
    }
};

class XLineAnimation : public Animation
{
public:
    XLineAnimation()
    {
        increment = glm::pi<float>() / 60;        
    }

    glm::vec3 Advance() override
    {
        tick += increment;

        return glm::vec3(glm::sin(tick) * 0.15, 0, 0.0);
    }
};


class Sphere : public ShapeBase
{
private:
	unsigned int indexCount;
	
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    unsigned int indices[8320];
    float data[33800];

    Animation* animation;
	
	void CreateCircleArray()
	{
        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
	            const float xSegment = (float)x / (float)X_SEGMENTS;
	            const float ySegment = (float)y / (float)Y_SEGMENTS;
	            const float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
	            const float yPos = std::cos(ySegment * PI);
	            const float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

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
    Sphere(Sphere* sphere) : ShapeBase(sphere)
    {        
    }
	
	Sphere(std::string textureId, Animation* animation = nullptr) : ShapeBase(textureId)
	{
        this->animation = animation;
		CreateCircleArray();

		WithBuffer(data, sizeof(data));
		WithIndexBuffer(indices, sizeof(indices));

		_layout->AddFloat(3);	
		_layout->AddFloat(3);
        _layout->AddFloat(2);
		
		_va->AddBuffer(_vb, _layout);        
	}
    
	void ShapeBase::Draw(Graphics* graphics) override
	{
        if (animation != NULL) {
            Translate(animation->Advance());
        }
    	    	
        graphics->activeShader->SetUniformMatrix4fv("model", _model);
		
		glDrawElements(GL_TRIANGLE_STRIP, 8320, GL_UNSIGNED_INT, 0);        
	}

	virtual ~Sphere()
	{
	}
};
