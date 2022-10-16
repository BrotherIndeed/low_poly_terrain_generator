#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float direction;

// out vec3 TexCoord;
// out float dir;
out DATA
{
	vec3 TexCoord;
	float dir;
} data_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	data_out.TexCoord = vec3(aPos.x, aPos.y, -aPos.z);
	data_out.dir = direction;
}