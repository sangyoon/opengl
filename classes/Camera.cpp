#include <GL/glut.h>
#include "Camera.h"

const static float SCALE	= 0.1f;
const static   int MARGIN	= 10;

Camera::Camera( int width , int height )
{
	this->windowWidth	= width;
	this->windowHeight	= height;

	this->eye		= Vec3f( 0.0f , 0.0f , 0.0f );
	this->cam		= Vec3f( 0.0f , 0.0f , 1.0f );
	this->up		= Vec3f( 0.0f , 1.0f , 0.0f );

	this->cam.normalize();

	this->initialize();
}

Camera::Camera( int width , int height , const Vec3f &e , const Vec3f &c , const Vec3f &u )
{
	this->windowWidth	= width;
	this->windowHeight	= height;

	this->eye		= e;
	this->cam		= c;
	this->up		= u;

	this->cam.normalize();
	this->up.normalize();

	this->initialize();
}

void Camera::initialize( void )
{
	Vec3f cameraH( this->cam.x , 0.0f , this->cam.z );
	cameraH.normalize();

	if( cameraH.z >= 0.0f )
		if( cameraH.x >= 0.0f )
			this->angleH = 360.0f - toDegree( asin( cameraH.z ) );
		else
			this->angleH = 180.0f + toDegree( asin( cameraH.z ) );
	else
		if( cameraH.x >= 0.0f )
			this->angleH = toDegree( asin( -cameraH.z ) );
		else
			this->angleH = 90.0f - toDegree( asin( -cameraH.z ) );

	this->angleV = -toDegree( asin( this->cam.y ) );

	this->onTopEdge		= false;
	this->onBottomEdge	= false;
	this->onLeftEdge	= false;
	this->onRightEdge	= false;

	this->mousePosition.x	= this->windowWidth / 2;
	this->mousePosition.y	= this->windowHeight / 2;

	glutWarpPointer( this->mousePosition.x , this->mousePosition.y );
}

void Camera::update( void )
{
	const Vec3f axisV( 0.0f , 1.0f , 0.0f );
	Vec3f view( 1.0f , 0.0f , 0.0f );

	view.rotate( this->angleH , axisV );
	view.normalize();

	Vec3f axisH = axisV.cross( view );
	axisH.normalize();
	view.rotate( this->angleV , axisH );

	this->cam = view;
	this->cam.normalize();

	this->up = this->cam.cross( axisH );
	this->up.normalize();
}

bool Camera::onKeyboard( int key )
{
	switch ( key )
	{
		case GLUT_KEY_UP:
		{
			this->eye += ( this->cam * SCALE );

			return true;
		}
		
		case GLUT_KEY_DOWN:
		{
			this->eye -= ( this->cam * SCALE );

			return true;
		}

		case GLUT_KEY_LEFT:
		{
			Vec3f tmp = this->cam.cross( this->up );
			tmp.normalize();
			tmp *= SCALE;
			
			this->eye += tmp;

			return true;
		}
		
		case GLUT_KEY_RIGHT:
		{
			Vec3f tmp = this->up.cross( this->cam );
			tmp.normalize();
			tmp *= SCALE;
			
			this->eye += tmp;

			return true;
		}

	default:
		return false;
	}
}

void Camera::onMouse( int x , int y )
{
	const int dx = x - this->mousePosition.x;
	const int dy = y - this->mousePosition.y;

	this->mousePosition.x = x;
	this->mousePosition.y = y;

	this->angleH += static_cast< float >( dx ) / 20.0f;
	this->angleV += static_cast< float >( dy ) / 20.0f;

	if( dx == 0 )
	{
		if( x <= MARGIN )
			this->onLeftEdge = true;
		else if( x >= ( this->windowWidth - MARGIN ) )
			this->onRightEdge = true;
	}
	else
	{
		this->onLeftEdge	= false;
		this->onRightEdge	= false;
	}

	this->update();
}

void Camera::onReder( void )
{
	bool updated = false;

	if( this->onLeftEdge )
	{
		this->angleH -= 0.1f;
		updated = true;
	}
	else if( this->onRightEdge )
	{
		this->angleH += 0.1f;
		updated = true;
	}

	if( this->onTopEdge )
	{
		if( this->angleV > -90.0f )
		{
			this->angleV -= 0.1f;
			updated = true;
		}
	}
	else if( this->onBottomEdge )
	{
		if( this->angleV < 90.0f )
		{
			this->angleV += 0.1f;
			updated = true;
		}
	}

	if( updated )
		this->update();
}

const Vec3f& Camera::getEye( void ) const
{
	return this->eye;
}

const Vec3f& Camera::getCamera( void ) const
{
	return this->cam;
}

const Vec3f& Camera::getUp( void ) const
{
	return this->up;
}
