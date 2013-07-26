#ifndef SHADERMANAGER_HEADER_INCLUDED
#define SHADERMANAGER_HEADER_INCLUDED

#include <cassert>
#include <iostream>
#include <GL\glew.h>

class Shader
{
private:
    	template< int N > GLuint compile( char const *( &source )[ N ] , GLuint shaderType );

public:
	template< int N , int M > Shader( GLchar const *( &vertextSource )[ N ] , GLchar const *( &fragmentSource )[ M ] );
	~Shader( void );

	operator GLuint();
	void operator()( void );

private:
	GLuint shaderProgram;
	GLuint vertexShader, fragmentShader;
};

#endif
