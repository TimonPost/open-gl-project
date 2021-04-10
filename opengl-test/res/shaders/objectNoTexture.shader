#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform vec3 light_pos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} vs_out;

void main()
{
	// Calculate view-space coordinate
	vec4 P = view * model * vec4(position, 1.0);

	// Calculate normal in view-space
	vs_out.N = mat3(view * model) * normal;

	// Calculate light vector
	vs_out.L = light_pos - P.xyz;

	// Calculate view vector;
	vs_out.V = -P.xyz; 

	// Calculate the clip-space position of each vertex
	gl_Position = projection * P;
}

#shader fragment
#version 330 core

uniform float mat_power;
uniform vec3 mat_specular;
uniform vec3 mat_ambient;
uniform vec3 mat_diffuse;

in VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} fs_in;

out vec4 out_Color;

void main()
{
	// Normalize the incoming N and L vectors
	vec3 N = normalize(fs_in.N);
	vec3 L = normalize(fs_in.L);
	vec3 V = normalize(fs_in.V);

	// Calculate R locally
	vec3 R = reflect(-L, N);

	// Compute the specular component for each fragment
	vec3 specular = pow(max(dot(R, V), 0.0), mat_power) * mat_specular;

	// Compute the diffuse component for each fragment
	vec3 diffuse = max(dot(N, L), 0.0) * mat_diffuse;

	// Write final color to the framebuffer
	out_Color = vec4(mat_ambient + diffuse + specular, 1.0);
}