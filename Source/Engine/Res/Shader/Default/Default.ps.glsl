
uniform sampler2D tex0;

in vec2 pUV;

out vec4 oColor;

void main()
{
	oColor = texture(tex0, pUV);
}
