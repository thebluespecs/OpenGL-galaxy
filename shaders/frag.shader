#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;

out vec4 FragColor;
uniform int on[4];
uniform vec3 lightPos[4];
uniform sampler2D textureID;
uniform int source;

vec4 objectColor = texture(textureID, texCoord);
vec4 temp = vec4(0.0, 0.0, 0.0, 0.0);

void main()
{
    if(source == 0)
    {
        for(int i = 0; i<4; i++)
        {
            if(on[i] == 1)
            {
                vec3 lightColor = vec3(1.0, 1.0, 1.0);
                float ambientStrength = 0.0;
                float diffuseStrength = 1.0;

                vec3 lightVector = normalize(lightPos[i] - FragPos);
                float distance = length(lightPos[i] - FragPos);

                vec3 ambient = lightColor * ambientStrength;

                vec3 reflection = reflect(lightVector, Normal);

                float diffuse = max(0, dot(normalize(Normal), lightVector));

                float alpha = 100;

                vec3 view = vec3(0, 0, 1);

                float specular = pow(max(0, dot(view, reflection)), alpha);

                float distanceAttenuation = 1/(1 + 0.1 * distance + 0.05 * distance * distance);

                temp = temp + objectColor * vec4(ambient, 1.0) +
                            distanceAttenuation * diffuse * objectColor * diffuseStrength +
                            distanceAttenuation* objectColor * specular;
            }
            else
            {
                temp = temp + objectColor*vec4(0.0, 0.0, 0.0, 1.0f);
            }
        }
        FragColor = temp;
    }
    else
    {
       FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}