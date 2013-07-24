#ifndef WORLD_HEADER_INCLUDED
#define WORLD_HEADER_INCLUDED

#include "Math.h"

class World
{
public:
	World( void );
	~World( void ) { };

	void setScale( float x , float y , float z );
	void setPosition( float x , float y , float z );
	void setRotate( float x , float y , float z );
	void setProjection( float FOV , float width , float height , float zNear , float zFar );
	void setCamera( const Vec3f &eye , const Vec3f &cam , const Vec3f &up );

	const Mat4f* getTransform( void );

private:
	Vec3f scale;
	Vec3f position;
	Vec3f rotate;

	struct
	{
		float FOV;
		float width, height;
		float zNear;
		float zFar;
	} projection;

	struct
	{
		Vec3f eye;
		Vec3f cam;
		Vec3f up;
	} camera;

	Mat4f trasformation;
};

#endif
