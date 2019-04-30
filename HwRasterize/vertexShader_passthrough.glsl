#version 330 core

// comment

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_TexCoord;

out vec4 normal;
out vec3 h;
out vec3 lightdir;
out vec2 tCoord;


struct LightData {
    vec3 position;
    vec3 intensity;
};

uniform LightData light;

// 4 x 4 matrices
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;

void main(void)
{
	mat4 normalMatrix = transpose(inverse(modelMatrix));
    normal = normalMatrix * vec4(in_Normal, 0.0);
    vec4 pos = viewMatrix * modelMatrix * vec4(in_Position, 1.0);
    vec4 lightPos = viewMatrix * vec4(light.position, 1.0);

    vec3 v = normalize( -pos.xyz );

    lightdir = normalize( lightPos.xyz - pos.xyz );
    h = normalize( v + lightdir );
    gl_Position = projMatrix * pos;

    // Pass the texture coordinate to the fragment shader
    tCoord = in_TexCoord;

}