#version 100
precision highp float;	
uniform vec4 u_vColor;

void main() 
{ 
	gl_FragColor = u_vColor;
}