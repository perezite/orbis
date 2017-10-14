attribute vec2 a_vPosition;
attribute vec2 a_vTexCoord;	
uniform mat4 u_mTransform;
varying vec2 v_vTexCoord;

void main()
{
	gl_Position = u_mTransform * vec4( a_vPosition.xy, 0 , 1 );
	v_vTexCoord = a_vTexCoord;	
}