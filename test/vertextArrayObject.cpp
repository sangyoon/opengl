#include <iostream>
#include <GL\glew.h>
#include <GL\glut.h>

void render( void )
{	
	static float angle = 50.0f;
	static const GLfloat vertices[] = { -1.0f , -1.0f , 0.0f , 1.0f , -1.0f , 0.0f , 0.0f , 1.0f , 0.0f , };

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glEnableClientState( GL_VERTEX_ARRAY );
	{
		glVertexPointer( 3 , GL_FLOAT , 0 , vertices );
		glDrawArrays( GL_TRIANGLES , 0 , 9 );		
	}
	glDisableClientState( GL_VERTEX_ARRAY );

	glFlush();
	glutSwapBuffers();
}

int main( int argc , char **argv )
{
	glutInit( &argc , argv );

	glutInitWindowPosition( 100 , 100 );
	glutInitWindowSize( 320 , 320 );

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA );

	glutCreateWindow( "Vertext Array Object" );

	glutDisplayFunc( render );

	glutMainLoop();

	return 0;
}
