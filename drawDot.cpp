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

GLuint vertexBufferObject;

void init( void )
{
	if( glewInit() != GLEW_OK )
	{
		std::cerr << "Error: " << glewGetErrorString( glewInit() ) << std::endl;

		exit( 1 );
	}

	glClearColor( 0.f , 0.f , 0.f , 0.f );

	math::Vec3f vertex[ 1 ];
	vertex[ 0 ] = math::Vec3f( 0.f , 0.f , 0.f );

	glGenBuffers( 1 , &vertexBufferObject );
	glBindBuffer( GL_ARRAY_BUFFER , vertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER , sizeof( vertex ) , vertex , GL_STATIC_DRAW );
}

void render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );

	glDisableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER , vertexBufferObject );
	glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 0 , 0 );
	glDrawArrays( GL_POINTS , 0 , 1 );
	glDisableVertexAttribArray( 0 );	
	
	glutSwapBuffers();
}

void resize( int width , int height )
{
	double aspect = static_cast< double >( width ) / static_cast< double >( height );

	glViewport( 0 , 0 , width , height );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 45.0 , aspect , 1.0 , 200.0 );
}

void handleKeyboard( unsigned char key , int x , int y )
{
	switch( key )
	{
	case 27:
		exit( 0 );
		break;

	default:
		break;
	}
}

int main( int argc , char **argv )
{
	glutInit( &argc , argv );

	glutInitWindowPosition( 100 , 100 );
	glutInitWindowSize( 400 , 400 );

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );

	glutCreateWindow( "Shape" );

	glutDisplayFunc( render );
	glutReshapeFunc( resize );
	glutKeyboardFunc( handleKeyboard );
	
	init();

	glutMainLoop();

	return 0;
}
