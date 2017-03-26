precision mediump float;
varying vec4 v_color;
uniform sampler2D u_texture;
uniform sampler2D u_texture2;
varying vec2 v_uv;

void main()
{
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//vec4 tex2D = texture2D(u_texture, v_uv);
	//vec4 tex2D2 = texture2D(u_texture2, v_uv);
	//float grayColor = (tex2D.r * 5.0 + tex2D.g * 2.0 + tex2D.b) / 8.0;
	//gl_FragColor = vec4(grayColor, grayColor, grayColor, tex2D.a);
	//gl_FragColor = (tex2D + tex2D2) / 2.0;
	gl_FragColor = texture2D(u_texture, v_uv);
}
