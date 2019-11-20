#version 150

struct Material{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;

uniform vec3 lightPos0;
uniform vec3 cameraPos;

//functions
vec3 calculateAmbient(Material material){
  return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0){
  vec3 posToLightDirVec = normalize(vs_position - lightPos0);
  float diffuse = clamp(dot(posToLightDirVec,  vs_normal), 0, 1);
  vec3 diffuseFinal = material.diffuse * diffuse;

  return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos){
  vec3 lightToPosDirVec = normalize(lightPos0 - vs_position);
  vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
  vec3 posToViewDirVec = normalize(vs_position - cameraPos);
  float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 0);
  vec3 specularFinal = material.specular * specularConstant;

  return specularFinal;
}

void main(){

  //Ambient Light
  vec3 ambientFinal = calculateAmbient(material);

  //Diffuse Light
  vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);

  //Specular Light
  vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);


  fs_color = vec4(vs_color, 1.f) *
  (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(diffuseFinal, 1.f));
}
