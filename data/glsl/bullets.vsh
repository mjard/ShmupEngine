#version 120

varying mat4 v_tex_rot;
void main(void)
{
	vec4 l_position=gl_Vertex;
	vec2 l_direction=normalize(vec2(l_position.z,l_position.w));
	v_tex_rot=mat4(l_direction.x,l_direction.y,0.0,0.0,
		       -l_direction.y,l_direction.x,0.0,0.0,
		       0.0,0.0,1.0,0.0,
		       0.0,0.0,0.0,1.0);
	l_position.z=0.0;
	l_position.w=1.0;
	gl_FrontColor=gl_Color;
	gl_Position=gl_ModelViewProjectionMatrix*l_position;
}
