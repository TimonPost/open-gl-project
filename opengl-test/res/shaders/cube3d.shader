#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 0) in vec4 color;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core

out vec4 outColor;

void main()
{
	outColor = vec4(1.0, 1.0, 1.0, 1.0);
}