#version 120

uniform sampler2D u_Texture;

varying vec2	v_UV;
varying vec3	v_Normal;
varying vec3	v_Position;

uniform vec3	u_LightPosition[10];
uniform vec3	u_LightColor[10];
uniform float	u_LightIntensity[10];
uniform vec3	u_ViewPosition;

uniform float	u_AmbientIntensity;
uniform vec3	u_AmbientColor;

void main()
{
	vec3 ambient = u_AmbientIntensity * u_AmbientColor;
	vec3 light = vec3(0,0,0);

	vec3 diffuse = vec3(0,0,0);
	vec3 specular = vec3(0,0,0);

	int amountOfLights = 10;

	for(int i = 0; i < 10; i++)
	{
		if(u_LightIntensity[i] < 0)
		{
			amountOfLights = i;
			break;
		}

		vec3 normal = normalize(v_Normal);
		vec3 lightDir = normalize( u_LightPosition[i] - v_Position);
		float diff = max(dot(normal, lightDir), 0.0);
		vec3 diffuseLight = diff * u_LightColor[i];

		diffuse += diffuseLight;

		vec3 viewDir = normalize(u_ViewPosition - v_Position);
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		specular += spec * u_LightIntensity[i] * u_LightColor[i];
	}

	vec4 texColor = texture2D( u_Texture, v_UV );
	vec3 color = vec3(texColor);

	color *= ambient + diffuse + specular; 

	gl_FragColor = vec4(color, texColor.w);
}
