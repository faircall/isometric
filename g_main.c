#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "glew.h"
#include "SDL.h"
#include "SDL_opengl.h"

#include "iso_math.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720


//todo:
//hot load shaders
//render with ortho projection
//render textured quad

//restrictions for this engine:
//Everything is a textured quad
//

//finish mat4 in the library


void load_text_file(char *file_name, char **buffer)
{
    FILE *fp = fopen(file_name, "rb");
    int file_size;
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    *buffer = (char*)malloc(file_size + 1);

    fread((void*)(*buffer), 1, file_size, fp);

    (*buffer)[file_size] = '\0';

    fclose(fp);
}

GLuint load_shader(char *file_name, char **buffer, GLenum shader_type)
{
    load_text_file(file_name, buffer);
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, buffer, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    char info_log[512];
    if (success == GL_FALSE) {
	glGetShaderInfoLog(shader, 512, NULL, info_log);
	if (shader_type == GL_VERTEX_SHADER) {
	    printf("error compiling vertex shader: %s\n", info_log);
	}
	if (shader_type == GL_FRAGMENT_SHADER) {
	    printf("error compiling fragment shader: %s\n", info_log);
	}
	return -1;
    }

    return shader;
}

GLuint create_shader_program(char *vertex_shader_file, char **vertex_shader_buffer, char *fragment_shader_file, char **fragment_shader_buffer)
{
    GLuint vertex_shader = load_shader(vertex_shader_file, vertex_shader_buffer, GL_VERTEX_SHADER);
    GLuint fragment_shader = load_shader(fragment_shader_file, fragment_shader_buffer, GL_FRAGMENT_SHADER);
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    char info_log[512];
    if (success == GL_FALSE) {
	glGetProgramInfoLog(shader_program, 512, NULL, info_log);
	printf("error linking shader: %s\n", info_log);
	return -1;
    }
    return shader_program;
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
	printf("didn't init SDL\n");
	return -1;
    }

    SDL_Window *window = SDL_CreateWindow("isometric", SDL_WINDOWPOS_CENTERED,
					  SDL_WINDOWPOS_CENTERED, SCREENWIDTH,
					  SCREENHEIGHT, SDL_WINDOW_OPENGL);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    GLenum glew_err = glewInit();
    if (glew_err != GLEW_OK) {
	printf("didn't init glew\n");
	return -1;
    }


    int desired_gl_major = 4;
    int desired_gl_minor = 3;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, desired_gl_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, desired_gl_minor);

    int gl_major, gl_minor;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor);
    
    int running = 1;

    char *vertex_shader_buffer = 0;
    char *fragment_shader_buffer = 0;
    GLuint shader_program = create_shader_program("test.vert", &vertex_shader_buffer,
						  "test.frag", &fragment_shader_buffer);
    if (shader_program == -1) {
	printf("shader didn't link\n");
	return -1;
    }

    //clockwise?
    float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    Mat3 test_identity;
    test_identity = mat3_create_identity();
    Vec3 v3a = vec3_init(1.0f, 1.0f, 7.0f);
    Vec3 v3b = vec3_init(2.0f, 5.0f, 8.0f);
    Vec3 v3c = vec3_init(3.0f, 3.0f, 9.0f);
    Mat3 test_matrix = mat3_init_vec3(v3a, v3b, v3c);
    printf("test matrix before multiplication\n");
    mat3_print_elements(test_matrix);
    printf("test matrix after multiplication\n");
    Mat3 test_result = mat3_mult(test_identity, test_matrix);
    mat3_print_elements(test_result);

    Mat3 test_inv = mat3_inverse(test_matrix);
    printf("test inverse:\n");
    mat3_print_elements(test_inv);
    test_identity = mat3_mult(test_matrix, test_inv);
    printf("Now check that it's identity! \n");
    mat3_print_elements(test_identity);

    Mat4 test_mat4 = mat4_init(1, 2, 3, 4,
		   1, 1, 4, 5,
		   2, 3, 3, 2,
		   5, 1, 2, 1);

    printf("for test4\n");
    mat4_print_elements(test_mat4);
    
    Mat4 test_mat4_inverse = mat4_inverse(test_mat4);
    printf("for test4 inverse\n");
    mat4_print_elements(test_mat4_inverse);
    
    Mat4 test_mat4_identity = mat4_mult(test_mat4, test_mat4_inverse);
    printf("for test4 identity\n");
    mat4_print_elements(test_mat4_identity);


    float fov = 90.0f;
    

    while (running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
	    if (event.type == SDL_QUIT) {
		running = 0;
		break;
	    }
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	SDL_GL_SwapWindow(window);
    }
    
    SDL_Quit();
    return 0;
}
