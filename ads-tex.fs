#version 150

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex1;

// The output variable receives the color of the fragment.
out vec4 fragColor;

void main()
{
	vec4 texColor = texture(tex1, texCoord);
	
	fragColor = texColor * vec4( color, 1 );
}
