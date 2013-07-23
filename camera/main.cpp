#include <iostream>
#include <cassert>
#include <GL\glew.h>
#include <GL\glut.h>

#include "Matrix.h"

const int WINDOW_WIDTH  = 1024;
const int WINDOW_HEIGHT =  768;

static const char *vertexShader = "																					\n\
								  #version 330																		\n\
								  layout (location = 0) in vec3 position;											\n\
								  uniform mat4 worldMatrix;															\n\
								  out vec4 color;																	\n\
								  void main()																		\n\
								  {                                                                                 \n\
									gl_Position = worldMatrix * vec4( position , 1.0 );								\n\
									color = vec4( clamp( position , 0.0 , 1.0 ) , 1.0 );							\n\
								  }																					\n\
								  ";

static const char *fragmentShader = "											\n\
									#version 330								\n\
									in vec4 color;								\n\
									out vec4 fragColor;							\n\
									void main()									\n\
									{                                           \n\
										fragColor = color;						\n\
									}											\n\
								    ";

GLuint vertexBufferID;
GLuint indexBufferID;
GLuint worldLocation;

static void createVertexBuffer( void )
{
	math::Vec3f vertex[ 4 ];

	vertex[ 0 ] = math::Vec3f( -1.0f , -1.0f ,  0.5773f );
	vertex[ 1 ] = math::Vec3f(  1.0f , -1.0f , -1.15475f );
	vertex[ 2 ] = math::Vec3f(  0.0f ,  1.0f ,  0.5773f );
	vertex[ 3 ] = math::Vec3f(  0.0f ,  1.0f ,  0.0f );

	glGenBuffers( 1 , &vertexBufferID );
	glBindBuffer( GL_ARRAY_BUFFER , vertexBufferID );
	glBufferData( GL_ARRAY_BUFFER , sizeof( vertex ) , vertex , GL_STATIC_DRAW );
}

static void createIndexBuffer( void )
{
	unsigned int indices[] = {	0 , 3 , 1 ,
								1 , 3 , 2 ,
								2 , 3 , 0 ,
								0 , 2 , 1 };

	glGenBuffers( 1 , &indexBufferID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , indexBufferID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER , sizeof( indices ) , indices , GL_STATIC_DRAW );
}

static void addShader( GLuint shaderProgram , const char *shaderText , GLenum shaderType )
{
	GLuint shaderObject = glCreateShader( shaderType );

	if( shaderObject == 0 )
	{
		std::cerr << "Error create shader type " << shaderType << std::endl;

		exit( 0 );
	}

	const GLchar *p[ 1 ];
	p[ 0 ] = shaderText;
	GLint length[ 1 ];
	length[ 0 ] = strlen( shaderText );

	glShaderSource( shaderObject , 1 , p , length );
	glCompileShader( shaderObject );

	GLint success;
	glGetShaderiv( shaderObject , GL_COMPILE_STATUS , &success );

	if( !success )
	{
		GLchar infoLog[ 1024 ];
		glGetShaderInfoLog( shaderObject , 1024 , nullptr , infoLog );

		std::cerr << "Error compiling shader type " << shaderType << "'" << infoLog << "'" << std::endl;

		exit( 1 );
	}

	glAttachShader( shaderProgram , shaderObject );
}
static void compileShader( void )
{
	GLuint shaderProgram = glCreateProgram();

	if( shaderProgram == 0 )
	{
		std::cerr << "Error create shader program" << std::endl;

		exit( 1 );
	}

	addShader( shaderProgram , vertexShader , GL_VERTEX_SHADER );
	addShader( shaderProgram , fragmentShader , GL_FRAGMENT_SHADER );

	GLint success = 0;
	GLchar infoLog[ 1024 ] = { 0 };

	glLinkProgram( shaderProgram );
	glGetProgramiv( shaderProgram , GL_LINK_STATUS , &success );

	if( success == 0 )
	{
		glGetProgramInfoLog( shaderProgram , sizeof( infoLog ) , nullptr , infoLog );

		std::cerr << "Invalid shader program '" << infoLog << "'" << std::endl;

		exit( 1 );
	}

	glValidateProgram( shaderProgram );
	glGetProgramiv( shaderProgram , GL_VALIDATE_STATUS , &success );

	if( !success )
	{
		glGetProgramInfoLog( shaderProgram , sizeof( infoLog ) , nullptr , infoLog );

		std::cerr << "Invalid shader program '" << infoLog << "'" << std::endl;

		exit( 1 );
	}

	glUseProgram( shaderProgram );

	worldLocation = glGetUniformLocation( shaderProgram , "worldMatrix" );
	assert( worldLocation != 0xFFFFFFFF );
}

void render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );

	static float scale = 0.0f;

	scale += 0.1f;

	Matrix matrix;
	matrix.rotate( 0.0f , scale , 0.0f );
	matrix.worldPosition( 0.0f , 0.0f , 5.0f );

	math::Vec3f cameraPosition( 0.0f , 0.0f , -3.0f );
	math::Vec3f cameraTarget( 0.0f , 0.0f , 2.0f );
	math::Vec3f cameraUp( 0.0f , 1.0f , 0.0f );
	matrix.setCamera( cameraPosition , cameraTarget , cameraUp );
	matrix.perspeciveProjection( 60.0f , WINDOW_WIDTH , WINDOW_HEIGHT , 1.0f , 100.0f );


	glUniformMatrix4fv( worldLocation , 1 , GL_TRUE , ( const GLfloat* ) matrix.getTranslation() );

	glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER , vertexBufferID );
		glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 0 , 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , indexBufferID );

		glDrawElements( GL_TRIANGLES , 12 , GL_UNSIGNED_INT , 0 );
	glDisableVertexAttribArray( 0 );

	glutSwapBuffers();
}

int main( int argc , char **argv )
{
	glutInit( &argc , argv );

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );

	glutInitWindowSize( WINDOW_WIDTH , WINDOW_HEIGHT );
	glutInitWindowPosition( 100 , 100 );
	
	glutCreateWindow( "Perspective Projection" );

	glutDisplayFunc( render );
	glutIdleFunc( render );

	if( glewInit() != GLEW_OK )
		return 1;

	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );
	
	createVertexBuffer();
	createIndexBuffer();

	compileShader();

	glutMainLoop();

	return 0;
}
