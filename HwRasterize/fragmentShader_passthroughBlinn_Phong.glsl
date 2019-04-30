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


in vec3 lightdir;
in vec3 vColor;
in vec3 vNormal;
in vec2 tCoord;
in vec3 view;

void main(void)
{
	vec3 n = normalize(vNormal);
	vec3 l = normalize(lightdir);

    vec3 hV =  l + normalize(view);
	vec3 specular = vec3(1.0f, 1.0f, 1.0f);


	vec3 kdTexel = texture(textureUnit, tCoord).rgb;
	// vec3 thisShader = ( vColor * light.intensity * max( 0.0, dot(n, l)) ) + (0.1 * vColor);
	vec3 thisShader = ( kdTexel * light.intensity * max( 0.0, dot(n, l)) ) + (0.1 * kdTexel);
	vec3 blinnPhong = specular * light.intensity *  pow ( max(0.0,dot(n, hV) ), 0.45) ;

	thisShader = thisShader + blinnPhong;

	fragmentColor = vec4( thisShader, 1.0 );
}
