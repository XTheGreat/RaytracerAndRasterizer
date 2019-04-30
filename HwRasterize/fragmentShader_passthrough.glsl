#version 330 core
//
// Lambertian Fragment Shader
//

layout(location=0) out vec4 fragmentColor;

struct LightData {
	vec3 position;
	vec3 intensity;
};

uniform LightData light;
uniform sampler2D textureUnit;
// view Dir


in vec4 normal;
in vec3 h;
in vec3 lightdir;
in vec3 vColor;
in vec2 tCoord;

vec3 Ia;
vec3 ka, kd, ks;
float phongExp;

void main(void)
{
	vec3 n = normalize(normal.xyz);
	vec3 h = normalize(h);
	vec3 l = normalize(lightdir);

	phongExp = 32.0f;
	
	ks = vec3(0.1f, 0.1f, 0.1f);

	ka = vec3(0.001f, 0.001f, 0.001f);
	kd = vec3(0.01f, 0.01f, 0.01f);
	ks = vec3(1.0f, 1.0f, 1.0f);

	vec3 kdTexel = texture(textureUnit, tCoord).rgb;
	
	vec3 shader = ( kdTexel * light.intensity * max( 0.0, dot(n, l)) ) + (0.1 * kdTexel)
					+ ks * light.intensity
					* pow( max( 0.0, dot(n, h) ), phongExp );

	//vec3 intensity = ka * Ia
					+ kd * light.intensity * max( 0.0, dot(n, l) )
					+ ks * light.intensity
					* pow( max( 0.0, dot(n, h) ), phongExp );
					

	fragmentColor = vec4( shader, 1.0 );
}
