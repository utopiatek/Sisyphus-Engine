#version 300 es

precision highp float;

layout(std140) uniform CUSTOM_PER_MATERIAL
{
	mat4x4 Proj;
};