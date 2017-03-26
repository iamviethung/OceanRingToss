attribute vec3 a_posL;
attribute vec4 a_colorL;
varying vec4 v_color;
attribute vec2 a_uv;
varying vec2 v_uv;
uniform mat4 u_MVPMatrix;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	//gl_Position = posL;
	gl_Position = u_MVPMatrix * posL;
	v_color = a_colorL;
	v_uv = a_uv;
}
   