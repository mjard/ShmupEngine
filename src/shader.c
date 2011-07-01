#import "shader.h"

char * 
read_file(const char *filename) 
{	
	FILE *fp;
	long size;
	char *buffer;
	size_t result;
	
	fp = fopen(filename , "r");
	if (fp == NULL) goto error_open;
	
	fseek (fp, 0, SEEK_END);
	size = ftell(fp);
	rewind (fp);
	
	buffer = (char*) malloc(sizeof(char) * size + 1);
	if (buffer == NULL) goto error_malloc;
	
	result = fread(buffer, 1, size, fp);
	if (result != size) goto error_fread;
	
	buffer[size] = '\0';
	
	fclose (fp);
	return buffer;
	
error_fread:
	free(buffer);
error_malloc:
	fclose(fp);
error_open:	
	fprintf (stderr, "Error reading file: %s", filename); 
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

	glGetShaderInfoLog(vsh, 200, &log_size, info_log);	
	if (strstr(info_log, "ERROR") != NULL) {
		fprintf(stderr, "vsh info: %s\n", info_log);
		fprintf(stderr, "vsh:\n%s\n", vsh_src);
		exit(EXIT_FAILURE);
	}	
	
	fsh = glCreateShader(GL_FRAGMENT_SHADER);
	size = (GLint) strlen(fsh_src);
	glShaderSource(fsh, 1, &fsh_src, &size);
	glCompileShader(fsh);
	
	glGetShaderInfoLog(fsh, 200, &log_size, info_log);	
	if (strstr(info_log, "ERROR") != NULL) {
		fprintf(stderr, "fsh info: %s\n", info_log);
		fprintf(stderr, "fsh:\n%s\n", fsh_src);
		exit(EXIT_FAILURE);
	}	
		
	prog = glCreateProgram();	
	glAttachShader(prog, vsh);
	glAttachShader(prog, fsh);
	glLinkProgram(prog);
			
	glDeleteShader(vsh);
	glDeleteShader(fsh);
		
	glGetProgramInfoLog(prog, 200, &log_size, info_log);
	if (strstr(info_log, "ERROR") != NULL) {
		fprintf(stderr, "prog info: %s\n", info_log);
		exit(EXIT_FAILURE);
	}	

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
