#include "Math.h"

math::Vec3f math::Vec3f::cross( const math::Vec3f &vector ) const
{
	const float _x = this->y * vector.z - this->z * vector.y;
	const float _y = this->z * vector.x - this->x * vector.z;
	const float _z = this->x * vector.y - this->y * vector.x;

	return math::Vec3f( _x , _y , _z );
}

math::Vec3f& math::Vec3f::normalize( void )
{
	const float length = sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
	
	this->x /= length;
	this->y /= length;
	this->z /= length;

	return *this;
}

void math::Mat4f::initScaleTransform( float scaleX , float scaleY , float scaleZ )
{
	this->m[ 0 ][ 0 ] = scaleX;	this->m[ 0 ][ 1 ] = 0.0f;	this->m[ 0 ][ 2 ] = 0.0f;	this->m[ 0 ][ 3 ] = 0.0f;
	this->m[ 1 ][ 0 ] = 0.0f;	this->m[ 1 ][ 1 ] = scaleY;	this->m[ 1 ][ 2 ] = 0.0f;	this->m[ 1 ][ 3 ] = 0.0f;
	this->m[ 2 ][ 0 ] = 0.0f;	this->m[ 2 ][ 1 ] = 0.0f;	this->m[ 2 ][ 2 ] = scaleZ;	this->m[ 2 ][ 3 ] = 0.0f;
	this->m[ 3 ][ 0 ] = 0.0f;	this->m[ 3 ][ 1 ] = 0.0f;	this->m[ 3 ][ 2 ] = 0.0f;	this->m[ 3 ][ 3 ] = 1.0f;
}

void math::Mat4f::initRotateTransform( float rotateX , float rotateY , float rotateZ )
{
	math::Mat4f rx, ry, rz;

	const float x = toRadian( rotateX );
	const float y = toRadian( rotateY );
	const float z = toRadian( rotateZ );

	rx.m[ 0 ][ 0 ] = 1.0f; rx.m[ 0 ][ 1 ] = 0.0f;		rx.m[ 0 ][ 2 ] = 0.0f;			rx.m[ 0 ][ 3 ] = 0.0f;
	rx.m[ 1 ][ 0 ] = 0.0f; rx.m[ 1 ][ 1 ] = cosf( x );	rx.m[ 1 ][ 2 ] = -sinf( x );	rx.m[ 1 ][ 3 ] = 0.0f;
	rx.m[ 2 ][ 0 ] = 0.0f; rx.m[ 2 ][ 1 ] = sinf( x );	rx.m[ 2 ][ 2 ] = cosf( x );		rx.m[ 2 ][ 3 ] = 0.0f;
	rx.m[ 3 ][ 0 ] = 0.0f; rx.m[ 3 ][ 1 ] = 0.0f;		rx.m[ 3 ][ 2 ] = 0.0f;			rx.m[ 3 ][ 3 ] = 1.0f;

	ry.m[ 0 ][ 0 ] = cosf( y );	ry.m[ 0 ][ 1 ] = 0.0f;	ry.m[ 0 ][ 2 ] = -sinf( y );	ry.m[ 0 ][ 3 ] = 0.0f;
	ry.m[ 1 ][ 0 ] = 0.0f;		ry.m[ 1 ][ 1 ] = 1.0f;	ry.m[ 1 ][ 2 ] = 0.0f;			ry.m[ 1 ][ 3 ] = 0.0f;
	ry.m[ 2 ][ 0 ] = sinf( y ); ry.m[ 2 ][ 1 ] = 0.0f;	ry.m[ 2 ][ 2 ] = cosf( y );		ry.m[ 2 ][ 3 ] = 0.0f;
	ry.m[ 3 ][ 0 ] = 0.0f;		ry.m[ 3 ][ 1 ] = 0.0f;	ry.m[ 3 ][ 2 ] = 0.0f;			ry.m[ 3 ][ 3 ] = 1.0f;

	rz.m[ 0 ][ 0 ] = cosf( z ); rz.m[ 0 ][ 1 ] = -sinf( z );	rz.m[ 0 ][ 2 ] = 0.0f;	rz.m[ 0 ][ 3 ] = 0.0f;
	rz.m[ 1 ][ 0 ] = sinf( z ); rz.m[ 1 ][ 1 ] = cosf( z );		rz.m[ 1 ][ 2 ] = 0.0f;	rz.m[ 1 ][ 3 ] = 0.0f;
	rz.m[ 2 ][ 0 ] = 0.0f;		rz.m[ 2 ][ 1 ] = 0.0f;			rz.m[ 2 ][ 2 ] = 1.0f;	rz.m[ 2 ][ 3 ] = 0.0f;
	rz.m[ 3 ][ 0 ] = 0.0f;		rz.m[ 3 ][ 1 ] = 0.0f;			rz.m[ 3 ][ 2 ] = 0.0f;	rz.m[ 3 ][ 3 ] = 1.0f;

	*this = rz * ry * rx;
}

void math::Mat4f::initTranslationTransform( float x , float y , float z )
{
	this->m[ 0 ][ 0 ] = 1.0f; this->m[ 0 ][ 1 ] = 0.0f; this->m[ 0 ][ 2 ] = 0.0f; this->m[ 0 ][ 3 ] = x;
	this->m[ 1 ][ 0 ] = 0.0f; this->m[ 1 ][ 1 ] = 1.0f; this->m[ 1 ][ 2 ] = 0.0f; this->m[ 1 ][ 3 ] = y;
	this->m[ 2 ][ 0 ] = 0.0f; this->m[ 2 ][ 1 ] = 0.0f; this->m[ 2 ][ 2 ] = 1.0f; this->m[ 2 ][ 3 ] = z;
	this->m[ 3 ][ 0 ] = 0.0f; this->m[ 3 ][ 1 ] = 0.0f; this->m[ 3 ][ 2 ] = 0.0f; this->m[ 3 ][ 3 ] = 1.0f;
}

void math::Mat4f::initCameraTransform( const math::Vec3f &target , const math::Vec3f &up )
{
	math::Vec3f N = target;
	N.normalize();

	math::Vec3f U = up;
	U.normalize();
	U = U.cross( N );

	math::Vec3f V = N.cross( U );

	m[ 0 ][ 0 ] = U.x;	m[ 0 ][ 1 ] = U.y;	m[ 0 ][ 2 ] = U.z;	m[ 0 ][ 3 ] = 0.0f;
	m[ 1 ][ 0 ] = U.x;	m[ 1 ][ 1 ] = V.y;	m[ 1 ][ 2 ] = V.z;	m[ 1 ][ 3 ] = 0.0f;
	m[ 2 ][ 0 ] = U.x;	m[ 2 ][ 1 ] = N.y;	m[ 2 ][ 2 ] = N.z;	m[ 2 ][ 3 ] = 0.0f;
	m[ 3 ][ 0 ] = 0.0f;	m[ 3 ][ 1 ] = 0.0f;	m[ 3 ][ 2 ] = 0.0f;	m[ 3 ][ 3 ] = 1.0f;
}

void math::Mat4f::initPersProjTransform( float FOV , float width , float height , float zNear, float zFar)
{
	const float ar			= width / height;
	const float zRange		= zNear - zFar;
	const float tanHalfFOV	= tanf( toRadian( FOV / 2.0f ) );
	
	this->m[ 0 ][ 0 ] = 1.0f / ( tanHalfFOV * ar );	this->m[ 0 ][ 1 ] = 0.0f;						this->m[ 0 ][ 2 ] = 0.0f;						this->m[ 0 ][ 3 ] = 0.0f;
	this->m[ 1 ][ 0 ] = 0.0f;						this->m[ 1 ][ 1 ] = 1.0f / ( tanHalfFOV * ar );	this->m[ 1 ][ 2 ] = 0.0f;						this->m[ 1 ][ 3 ] = 0.0f;
	this->m[ 2 ][ 0 ] = 0.0f;						this->m[ 2 ][ 1 ] = 0.0f;						this->m[ 2 ][ 2 ] = ( -zNear -zFar ) / zRange;	this->m[ 2 ][ 3 ] = 2.0f * zFar * zNear / zRange;
	this->m[ 3 ][ 0 ] = 0.0f;						this->m[ 3 ][ 1 ] = 0.0f;						this->m[ 3 ][ 2 ] = 1.0f;						this->m[ 3 ][ 3 ] = 0.0f;
}
