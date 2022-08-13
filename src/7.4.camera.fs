#version 330 core
out vec4 FragColor;

in vec3 TexCoord;


// texture samplers
// uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	int y = int(TexCoord.y);

	FragColor = vec4(1.0f, (TexCoord.y-y), 0.2f, 1.0f);
	if(y<=0)
	{
		FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
}