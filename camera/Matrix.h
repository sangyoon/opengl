#ifndef MATRIX_HEADER_INCLUDED
#define MATRIX_HEADER_INCLUDED

#include "Math.h"

class Matrix
{
public:
  	Matrix( void );
	~Matrix( void );

	void scale( float scaleX , float scaleY , float scaleZ );
	void worldPosition( float x , float y , float z );
	void rotate( float rotateX , float rotateY , float rotateZ );
	void perspeciveProjection( float FOV , float width , float height ,  float zNear , float zFar );
	void setCamera( const math::Vec3f &position , const math::Vec3f &target , const math::Vec3f &up );

	const math::Mat4f *getTranslation( void );

private:
	math::Vec3f scaleVector;
	math::Vec3f worldPosVector;
	math::Vec3f rotateInformVector;

	struct
	{
		float FOV;
		float width;
		float height;
		float zNear;
		float zFar;
	} perspectiveProj;

	struct
	{
		math::Vec3f position;
		math::Vec3f target;
		math::Vec3f up;
	} camera;

	math::Mat4f transformation;
};

#endif
