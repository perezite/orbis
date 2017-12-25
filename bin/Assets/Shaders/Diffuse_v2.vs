attribute vec2 a_vPosition;
attribute vec2 a_vTexCoord;	
varying vec2 v_vTexCoord;

void main()
{
	gl_Position = vec4(a_vPosition.x, a_vPosition.y, 0 , 1 );
	v_vTexCoord = a_vTexCoord;	
}