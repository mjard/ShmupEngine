#import "shader.h"

char * 
read_file(const char *f) 
{	
	FILE *fp;
	long size;
	char *buffer;
	size_t result;
	
	fp = fopen(f , "r");
	if (fp == NULL) goto error;
	
	fseek (fp, 0, SEEK_END);
	size = ftell(fp);
	rewind (fp);
	
	buffer = (char*) malloc(sizeof(char)*size);
	if (buffer == NULL) goto error;
	
	result = fread(buffer, 1, size, fp);
	if (result != size) goto error;
	
	fclose (fp);
	return buffer;
	
error:
	
	fprintf (stderr, "Error loading shader: %s", f); 
	exit(EXIT_FAILURE);
	
}

GLuint 
compile_shaders(const char *vsh_src, const char *fsh_src)
{	
	GLuint prog, vsh, fsh;
	GLint size;
	GLchar info_log[200];
	GLsizei log_size;
		
	vsh = glCreateShader(GL_VERTEX_SHADER);
	size = (GLint) strlen(vsh_src);
	glShaderSource(vsh, 1, &vsh_src, &size);
	glCompileShader(vsh);

	fsh = glCreateShader(GL_FRAGMENT_SHADER);
	size = (GLint) strlen(fsh_src);
	glShaderSource(fsh, 1, &fsh_src, &size);
	glCompileShader(fsh);
	
	prog = glCreateProgram();	
	glAttachShader(prog, vsh);
	glAttachShader(prog, fsh);
	glLinkProgram(prog);
			
	glDeleteShader(vsh);
	glDeleteShader(fsh);
	
	glGetProgramInfoLog(prog, 10000, &log_size, info_log);
	fprintf(stderr, "%s\n", info_log);
			
	return prog;
}

GLuint 
load_shaders(const char *vsh_file, const char *fsh_file)
{
	GLchar *vsh_src = read_file(vsh_file);
	GLchar *fsh_src = read_file(fsh_file);
	GLuint p = compile_shaders(vsh_src, fsh_src);
	free(vsh_src);
	free(fsh_src);
	return p;
}
