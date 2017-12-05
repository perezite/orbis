#version 100
precision highp float;
varying vec2 v_vTexCoord;
uniform sampler2D u_sSampler;	

void main() 
{ 
	gl_FragColor = texture2D(u_sSampler, v_vTexCoord);	
}