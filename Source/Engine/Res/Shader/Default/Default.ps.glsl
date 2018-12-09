
uniform sampler2D tex0;

uniform vec4 data;

in vec2 pUV;

out vec4 oColor;

void main()
{
	oColor = texture(tex0, pUV);
}
