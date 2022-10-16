#version 330 core
out vec4 FragColor;

in vec3 TexCoord;
in float dir;
in vec3 normal;
in float height;

	float direction = sin(normal.z/normal.x);

float min_max(float minimum, float maximum)
{
	float range = (maximum-minimum);
	return minimum + (range*direction);

}
void main()
{
	
	int scale = 10;



	if(height>0)
	{
		FragColor = vec4(0.250+direction/10, 0.420+(height/130), 0.340+direction/10, 1.0);

	}
	if(height>50)
	{
		FragColor = vec4(min_max(0.733,0.929), min_max(0.769,0.933),min_max(0.816,0.941), 1.0);

	}
	if(height<0)
	{
		FragColor = vec4(0.114+direction/20+(height/100), 0.650+(height/100)+direction/20, 0.710+direction/20+(height/100), 1.0);
		// FragColor = vec4(0.392, 0.588, 0.655, 1.0);
	}
}



	// if(y>20*scale )
	// {
	// 	// FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// 	// FragColor = vec4(0.6f* (TexCoord.y-y+0.6), 0.6f* (TexCoord.y-y+0.6), 0.6f* (TexCoord.y-y+0.6), 1.0f);
	// 	// FragColor = vec4(0.6f * (((y%scale)*1.0f/scale)+0.6), 0.6f* (((y%scale)*1.0f/scale)+0.6), 0.6f* (((y%scale)*1.0f/scale)+0.6), 1.0f);
	// 	FragColor = vec4(0.6f * (((y%scale)*1.0f/scale)+0.6), 0.6f* (((y%scale)*1.0f/scale)+0.6), 0.6f* (((y%scale)*1.0f/scale)+0.6), 1.0f);

	// }
// if(y<20*scale && y>10*scale)
// 	{	
// 		// FragColor = vec4(0.33f* ((y%(2*scale))/scale+0.5), 0.33f* (((y%(2*scale))/scale)+0.5), 0.33f*( ((y%(2*scale))/scale)+0.5), 1.0f);
// 	}
// * ((y%2)+0.5)
	// if(TexCoord.y<=2*scale )
	// {
	// 	FragColor = vec4(0.8235f, 0.6667f, 0.4275f, 1.0f);
	// }

	// if(y<=0)
	// {
	// 	FragColor = vec4(0.1f, 0.1f, 0.8f, 1.0f);
	// }
// 	int d=int(dir);
// FragColor = vec4(0.1f*(dir-d), 0.1f, 0.8f, 1.0f);
	// if(gl_FrontFacing)
	// {
	// 	FragColor.y = FragColor.y*2;
	// }