#version 120

uniform sampler2D u_Texture;

varying vec2	v_UV;
varying vec3	v_Normal;
varying vec3	v_Position;

uniform float	u_Time;

void main()
{
	gl_FragColor = texture2D( u_Texture, v_UV );
}
