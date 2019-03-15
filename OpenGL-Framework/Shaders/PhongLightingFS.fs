#version 450 core

in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;

uniform float fStartX; //This seems messy but uniform vec2 just didn't render
uniform float fStartY;

uniform float fEndX;
uniform float fEndY;


uniform vec3 lightColor; // = glm::vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos; // = glm::vec3(5.0f, 5.0f, 0.5f);

uniform float lightSpecStr; // = 1.0f;
uniform vec3 camPos; // = glm::vec3(1.0f, 1.0f, 3.0f);
uniform float shininess; // = 32.0f;

void main(void)
{	
	vec2 newCoords = vec2(fragTexCoord.x * fEndX, fragTexCoord.y * fEndY);
	newCoords = vec2(newCoords.x + fStartX, newCoords.y + fStartY);
	vec4 newAlpha = vec4(1.0, 1.0, 1.0, 1.0);

	vec3 ambient = ambientStr * ambientColor;

	// Light Direction
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fragPos - lightPos);
	// Diffuse Coloring
	float diffuseStr = max(dot(norm, -lightDir ), 0.0f);
	vec3 diffuse = diffuseStr * lightColor;

	// Specular Highlight
	vec3 negViewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(lightDir, norm);
	float spec = pow(max(dot(negViewDir , reflectDir), 0.0f), shininess);
	vec3 specular = lightSpecStr * spec * lightColor;

	color =  vec4(ambient + diffuse + specular, 1.0f) * texture(tex, newCoords) * newAlpha;
} 