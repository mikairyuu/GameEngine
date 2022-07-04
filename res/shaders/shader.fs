#version 330 core

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};

in vec2 UvTex;
in vec3 Norm;
in vec3 FragPos;

out vec4 outColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main() {
    //ambient
    vec3 ambient = light.ambient * texture(material.diffuse, UvTex).rgb;
      // diffuse
    vec3 norm = normalize(Norm);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, UvTex).rgb;
     // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;
    vec3 result = ambient + diffuse + specular;

    outColor = vec4(result, 1.0f);
    }