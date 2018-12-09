
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vUV;

out vec2 pUV;

void main()
{
	pUV = vUV;
	gl_Position = Proj * vPosition;
}
