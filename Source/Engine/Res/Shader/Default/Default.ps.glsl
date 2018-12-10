
uniform sampler2D tex0;

uniform vec4 v3;
uniform vec4 v4;

in vec2 pUV;

out vec4 oColor;

void main()
{
	oColor = v3;
	oColor = v4;
	oColor = texture(tex0, pUV);
}
