attribute vec2 a_vPosition;
attribute vec2 a_vTexCoord;	
attribute vec4 a_vVertexColor;
varying vec2 v_vTexCoord;
varying vec4 v_vVertexColor;

void main()
{
	gl_Position = vec4(a_vPosition.x, a_vPosition.y, 0 , 1 );
	v_vTexCoord = a_vTexCoord;
	v_vVertexColor = a_vVertexColor;
}