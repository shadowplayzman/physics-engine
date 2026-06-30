#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;




// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

uniform sampler2D specular0;

uniform vec3 materialDiffuseColor;
uniform vec3 materialSpecularColor;
uniform float materialShininess;

uniform bool hasDiffuseTexture;
uniform bool hasSpecularTexture;

vec4 pointLight(){
	vec3 lightVec=lightPos - crntPos;
	float dist=length(lightVec);
	float a=2.0;
	float b=0.7;
	float inten=1.0f/(a*dist*dist+b*dist+1.0f);
	// ambient lighting
	float ambient = 0.40f;

	//for checking if mesh has textutre or not

	vec4 diffuseColor;

	if(hasDiffuseTexture){
		diffuseColor=texture(diffuse0,texCoord);}
	else{
		diffuseColor=vec4(materialDiffuseColor,1.0f);}

	float specMap;

	if(hasSpecularTexture){
		specMap=texture(specular0,texCoord).r;}
	else{
		specMap=1.0f;}

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), materialShininess);
	float specular = specAmount * specularLight;



	// outputs final color
	return (diffuseColor * lightColor * (diffuse*inten + ambient )+specMap*specular*inten)*lightColor;
}
vec4 direcLight(){
	vec3 lightVec=lightPos - crntPos;
	float dist=length(lightVec);
	float a=2.0;
	float b=0.7;
	float inten=1.0f/(a*dist*dist+b*dist+1.0f);
	// ambient lighting
	float ambient = 0.40f;

	//for checking if mesh has textutre or not

	vec4 diffuseColor;

	if(hasDiffuseTexture){
		diffuseColor=texture(diffuse0,texCoord);}
	else{
		diffuseColor=vec4(materialDiffuseColor,1.0f);}

	float specMap;
	if(hasSpecularTexture){
		specMap=texture(specular0,texCoord).r;}
	else{
		specMap=1.0f;}

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f,1.0f,1.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), materialShininess);
	float specular = specAmount * specularLight;

	// outputs final color
	return (diffuseColor * lightColor * (diffuse + ambient )+specMap*specular)*lightColor;}
vec4 spotLight(){
	float outercone=0.90f;
	float innercone=0.95f;
	
	vec3 lightVec=lightPos - crntPos;
	float dist=length(lightVec);
	// ambient lighting
	float ambient = 0.40f;

	//for checking if mesh has textutre or not

	vec4 diffuseColor;

	if(hasDiffuseTexture){
		diffuseColor=texture(diffuse0,texCoord);}
	else{
		diffuseColor=vec4(materialDiffuseColor,1.0f);}

	float specMap;
	if(hasSpecularTexture){
		specMap=texture(specular0,texCoord).r;}
	else{
		specMap=1.0f;}

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), materialShininess);
	float specular = specAmount * specularLight;

	float angle=dot(vec3(0.0f,-1.0f,0.0f),-lightDirection);
	float inten=clamp((angle-outercone)/(innercone-outercone),0.0f,1.0f);

	// outputs final color
	return (diffuseColor * (diffuse * inten + ambient) + specMap * specular * inten) * lightColor;}
void main()
{
FragColor = direcLight();
   }