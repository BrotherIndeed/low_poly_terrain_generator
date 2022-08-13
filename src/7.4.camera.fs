#version 330 core
out vec4 FragColor;

in vec3 TexCoord;
in float dir;

// texture samplers
// uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	int y = int(TexCoord.y);
	int x = int(TexCoord.x);
	int z = int(TexCoord.z);

	FragColor = vec4(0.0f, 0.4f* ((y%2)+0.5), 0.2f, 1.0f);

	if(y>20 )
	{
		// FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		FragColor = vec4(0.6f* (TexCoord.y-y+0.6), 0.6f* (TexCoord.y-y+0.6), 0.6f* (TexCoord.y-y+0.6), 1.0f);

	}
	if(y<=2 )
	{
		FragColor = vec4(0.8235f, 0.6667f, 0.4275f, 1.0f);
	}

	if(y<=0)
	{
		FragColor = vec4(0.1f, 0.1f, 0.8f, 1.0f);
	}

	// if(gl_FrontFacing)
	// {
	// 	FragColor.y = FragColor.y*2;
	// }
}