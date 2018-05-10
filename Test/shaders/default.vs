#version 330

layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;

out vec2 outTexCoord;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 meshMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix  * meshMatrix *vec4(position, 1.0);
    outTexCoord = texCoord;
}