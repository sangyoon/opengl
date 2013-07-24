#ifndef CAMERA_HEADER_INCLUDED
#define CAMERA_HEADER_INCLUDED

#include "Math.h"

class Camera
{
public:
	Camera( int width , int height );
	Camera( int width , int height , const Vec3f &e , const Vec3f &c , const Vec3f &u );

	bool onKeyboard( int key );
	void onMouse( int x , int y );
	void onReder( void );

	const Vec3f& getEye( void ) const;
	const Vec3f& getCamera( void ) const;
	const Vec3f& getUp( void ) const;

private:
	void initialize( void );
	void update( void );

private:
	Vec3f eye, cam, up;
	int windowWidth, windowHeight;
	float angleH, angleV;
	bool onTopEdge, onBottomEdge, onLeftEdge, onRightEdge;
	Vec2i mousePosition;
};

#endif
