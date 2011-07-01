#version 120

varying mat4 v_tex_rot;
uniform sampler2D tex;

void main(void)
{
	vec2 l_uv=gl_PointCoord;
	const vec2 l_offset=vec2(0.5,0.5);
	l_uv-=l_offset;
	l_uv=vec2(v_tex_rot*vec4(l_uv,0.0,1.0));
	l_uv+=l_offset;
	gl_FragColor=vec4(texture2D(tex,l_uv))*gl_Color;
}