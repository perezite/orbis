attribute vec2 a_vPosition;

void main()
{
	gl_Position = vec4(a_vPosition.x, a_vPosition.y, 0 , 1 );
}