#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Values that stay constant for the whole mesh.
out vec2 TexCoords;
out vec4 ShadowCoord;

// uniform mat4 projection;
// uniform mat4 view;
// uniform mat4 model;

// uniform mat4 lightMVP;

void main()
{
    TexCoords = aTexCoords;
   gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D shadowMap;

void main()
{
    float depthValue = texture(shadowMap, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0);
} 