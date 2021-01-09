#version 410 core

in vec3 fNormal;
in vec4 fPosEye;

out vec4 fColor;

//lighting
uniform	vec3 lightDir;
uniform	vec3 lightColor;

vec3 ambient;
float ambientStrength = 0.2f;
vec3 diffuse;
vec3 specular;
float specularStrength = 0.5f;
float shininess = 32.0f;
float constant = 1.0f;
float linear = 0.0045f;
float quadratic = 0.0075f;

//maps
uniform sampler2D diffuseTexture;
uniform sampler2D speculareTexture;

in vec2 passTextCoord;

void computeLightComponents()
{		
	vec3 cameraPosEye = vec3(0.0f);//in eye coordinates, the viewer is situated at the origin
	
	//transform normal
	vec3 normalEye = normalize(fNormal);	
	
	//compute light direction -- se modifica pt ca avem lumina punctiforma
	//vec3 lightDirN = normalize(lightDir);
	vec3 lightDirN = normalize(lightDir-fPosEye.xyz); //pozitia luminii - pozitia frag
	
	//compute view direction 
	vec3 viewDirN = normalize(cameraPosEye - fPosEye.xyz);

	//compute distance to light
	float dist = length(lightDir-fPosEye.xyz);
	//compute attenuation
	float att = 1.0f/(constant + linear*dist + quadratic*dist*dist);

		
	//compute ambient light
	ambient = att * ambientStrength * lightColor;
	
	//compute diffuse light
	diffuse = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor;
	
	//compute specular light
	//vec3 reflection = reflect(-lightDirN, normalEye);
	//float specCoeff = pow(max(dot(viewDirN, reflection), 0.0f), shininess);

	//compute half vector
	vec3 halfVector = normalize (lightDirN + viewDirN);
	//compute specular lightColor
	float specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specular = att * specularStrength * specCoeff * lightColor;
}



void main() 
{
	computeLightComponents();
	
	vec3 baseColor = vec3(0.9f, 0.35f, 0.0f);//orange
	
	//ambient *= baseColor;
	//diffuse *= baseColor;
	//specular *= baseColor;

	ambient *= texture(diffuseTexture, passTextCoord);
	diffuse *= texture(diffuseTexture, passTextCoord);
	specular *= texture(speculareTexture, passTextCoord);
	
	vec3 color = min((ambient + diffuse) + specular, 1.0f);
    
    fColor = vec4(color, 1.0f);
}
