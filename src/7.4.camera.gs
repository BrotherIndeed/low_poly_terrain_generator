#version 330 core

layout (triangles) in;


layout (triangle_strip) out;
layout (max_vertices = 3) out;


out vec3 TexCoord;
out float dir;
out vec3 normal;
out float height;

in DATA
{
	vec3 TexCoord;
	float dir;
} data_in[];



vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}  

void main(void)
{
	vec3 normal_temp = GetNormal();

    int i;
    for (i = 0; i < data_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
		TexCoord = data_in[i].TexCoord;
		dir = 0.0f ;
		normal = normal_temp;
		height = (data_in[0].TexCoord.y);
        EmitVertex();
    }
    EndPrimitive();
}