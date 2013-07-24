#include "Shader.h"

template< int N , int M > Shader::Shader( GLchar const *( &vertextSource )[ N ] , GLchar const *( &fragmentSource )[ M ] )
{
	this->shaderProgram = glCreateProgram();
	assert( this->shaderProgram == 0 , !"Error Create Shader Program." );

	this->vertexShader	 = compile( vertextSource , GL_VERTEX_SHADER );
	this->fragmentShader = compile( fragmentSource , GL_FRAGMENT_SHADER );

	glAttachShader( this->shaderProgram , this->vertexShader );
	glAttachShader( this->shaderProgram , this->fragmentShader );

	glLinkProgram( this->shaderProgram );		
}

Shader::~Shader( void )
{
	glDeleteProgram( this->shaderProgram );
	glDeleteShader( this->vertexShader );
	glDeleteShader( this->fragmentShader );
}

Shader::operator GLuint( void )
{
	return this->shaderProgram;
}

void Shader::operator()( void )
{
	glUseProgram( this->shaderProgram );
}

template< int N > GLuint Shader::compile( char const *( &source )[ N ] , GLuint shaderType )
{
	GLuint shader = glCreateShader( shaderType );

	glShaderSource( shader , N , source , nullptr );
	glCompileShader( shader );

	GLint compiled = 0;
	glGetShaderiv( shader , GL_COMPILE_STATUS , &compiled );

	if( !compiled )
	{
		GLint length = 0;
		glGetShaderiv( shader , GL_INFO_LOG_LENGTH , &length );

		std::string infoLog( length , ' ' );
		glGetShaderInfoLog( shader , length , &length , &infoLog[ 0 ] );

		throw std::logic_error( infoLog );

		return false;
	}

	return shader;
}
