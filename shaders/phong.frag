// classic Phong fragment shader
#version 410
in vec4 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec2 vTexCoord;

//struct for lighting
struct DirectionalLight{
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
};

#define NUMBEROFLIGHTS 2
uniform DirectionalLight directionalLights[NUMBEROFLIGHTS];

uniform vec3 Ia; // ambient light colour
//uniform vec3 Id; // diffuse light colour
//uniform vec3 Is; // specular light colour
uniform vec3 LightDirection;
out vec4 FragColour;

uniform vec3 Ka; // ambient material colour
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour
uniform float specularPower; // material specular power

uniform vec3 cameraPosition;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

vec3 CalcDirectionLight(DirectionalLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction); 
	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	//specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularPower);
	
	//combine results
	
	vec3 amb = Ia * vec3(texture(diffuseTexture, vTexCoord).rgb);
	vec3 diffuser = light.diffuse * diff * vec3(texture(diffuseTexture, vTexCoord).rgb);
	vec3 specularity = light.specular * spec * vec3(texture(specularTexture, vTexCoord).rgb);
	
	return (amb + diffuser + specularity);
}

void main() {


	// ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 L = normalize(LightDirection);
	mat3 TBN = mat3(T,B,N);
	
	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );
	// output lambert as grayscale
	//FragColour = vec4( lambertTerm, lambertTerm, lambertTerm, 1 );
	vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
	vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
	
	N = TBN * (texNormal * 2 - 1);

	// calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect( L, N );
	// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );

	//// calculate each colour prop.
	//vec3 ambient = Ia * Ka;
	//vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	//vec3 specular = Is * Ks * texSpecular * specularTerm;
	
	vec3 result = Ia * Ka;
	
	//lighting 
	for(int i = 0; i < NUMBEROFLIGHTS; i++)
		result += CalcDirectionLight(directionalLights[i], N, V);

	// output final colour
	FragColour = vec4( result, 1 );
}