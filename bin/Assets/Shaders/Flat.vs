attribute vec2 a_vPosition;
uniform mat4 u_mTransform;

void main()
{
	gl_Position = u_mTransform * vec4(a_vPosition.x, a_vPosition.y, 0 , 1 );
}