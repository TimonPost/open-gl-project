#pragma once

#include <fwd.hpp>
#include <ext/scalar_constants.hpp>
#include "trigonometric.hpp"
#include <ext/matrix_transform.hpp>

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

        return glm::vec3(0.0, glm::cos(tick) * 0.15, glm::sin(tick) * 0.15);
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