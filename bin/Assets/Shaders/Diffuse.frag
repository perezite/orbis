#version 100
precision highp float;
varying vec2 v_vTexCoord;
uniform sampler2D u_sSampler;	

void main() 
{ 
	/*gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 ); */
	gl_FragColor = texture2D(u_sSampler, v_vTexCoord);	
}