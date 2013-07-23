#include <iostream>
#include <GL\glew.h>
#include <GL\glut.h>

namespace math
{
	struct Vec3f
	{
		float x, y, z;

		Vec3f() { }
		Vec3f( float x , float y , float z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};
}

static const char *vertexShader = "																					\n\
								  #version 330																		\n\
								  layout (location = 0 ) in vec3 Position;											\n\
								  void main()																		\n\
								  {                                                                                 \n\
									  gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);	\n\
								  }																					\n\
								  ";

static const char *fragmentShader = "											\n\
									#version 330								\n\
									out vec4 FragColor;							\n\
									void main()									\n\
									{                                           \n\
										FragColor = vec4(1.0, 0.0, 0.0, 1.0);	\n\
									}											\n\
								    ";

GLuint vertexBufferID;

static void createVertexBuffer( void )
{
	math::Vec3f vertex[ 3 ];

	vertex[ 0 ] = math::Vec3f( -1.0f , -1.0f , 0.0f );
	vertex[ 1 ] = math::Vec3f(  1.0f , -1.0f , 0.0f );
	vertex[ 2 ] = math::Vec3f(  0.0f ,  1.0f , 0.0f );

	glGenBuffers( 1 , &vertexBufferID );
	glBindBuffer( GL_ARRAY_BUFFER , vertexBufferID );
	glBufferData( GL_ARRAY_BUFFER , sizeof( vertex ) , vertex , GL_STATIC_DRAW );
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

	glUseProgram( shaderProgram );
}

void render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );

	glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER , vertexBufferID );
		glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 0 , 0 );
		glDrawArrays( GL_TRIANGLES , 0 , 3 );
	glDisableVertexAttribArray( 0 );

	glutSwapBuffers();
}

int main( int argc , char **argv )
{
	glutInit( &argc , argv );

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

	glutInitWindowSize( 1024 , 768 );
	glutInitWindowPosition( 100 , 100 );
	
	glutCreateWindow( "Shader" );

	if( glewInit() != GLEW_OK )
		return 1;

	glutDisplayFunc( render );
	createVertexBuffer();
	compileShader();

	glutMainLoop();

	return 0;
}
