#version 300 es

precision highp float;

layout(std140) uniform CUSTOM_PER_MATERIAL
{
	vec4 Color;
	mat4x4 Proj;
};