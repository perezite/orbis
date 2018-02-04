#version 100
precision highp float;
varying vec2 v_vTexCoord;
uniform sampler2D u_sSampler;	
uniform vec4 u_vColor;

void main() 
{ 
	gl_FragColor = texture2D(u_sSampler, v_vTexCoord) * u_vColor;	
}