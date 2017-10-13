attribute vec2 a_vPosition;
uniform float u_fRotation;

mat4 rotationMat =
	mat4(cos(u_fRotation), sin(u_fRotation), 0, 0,
	- sin(u_fRotation), cos(u_fRotation), 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

void main()
{
	gl_Position = rotationMat * vec4( a_vPosition.xy, 0, 1 );
}