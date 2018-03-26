#version 100
precision highp float;
varying vec2 v_vTexCoord;
varying vec4 v_vVertexColor;
uniform sampler2D u_sSampler;	

void main() 
{ 
	gl_FragColor = texture2D(u_sSampler, v_vTexCoord) * v_vVertexColor;	
}