#include "Math.h"

/* Matrix 4x4 */
inline void Mat4f::initIdentity( void )
{
	m[ 0 ][ 0 ] = 1.0f; m[ 0 ][ 1 ] = 0.0f; m[ 0 ][ 2 ] = 0.0f; m[ 0 ][ 3 ] = 0.0f;
	m[ 1 ][ 0 ] = 0.0f; m[ 1 ][ 1 ] = 1.0f; m[ 1 ][ 2 ] = 0.0f; m[ 1 ][ 3 ] = 0.0f;
	m[ 2 ][ 0 ] = 0.0f; m[ 2 ][ 1 ] = 0.0f; m[ 2 ][ 2 ] = 1.0f; m[ 2 ][ 3 ] = 0.0f;
	m[ 3 ][ 0 ] = 0.0f; m[ 3 ][ 1 ] = 0.0f; m[ 3 ][ 2 ] = 0.0f; m[ 3 ][ 3 ] = 1.0f;
}

inline Mat4f Mat4f::operator*( const Mat4f &target ) const
{
	Mat4f returnMat;

	for( unsigned int i = 0 ; i < 4 ; ++i )
		for( unsigned int j = 0 ; j < 4 ; ++j )
			returnMat.m[ i ][ j ] = m[ i ][ 0 ] * target.m[ 0 ][ j ] + m[ i ][ 1 ] * target.m[ 1 ][ j ] + m[ i ][ 2 ] * target.m[ 2 ][ j ] + m[ i ][ 3 ] * target.m[ 3 ][ j ];

	return returnMat;
}

void Mat4f::initScaleTransform( float x , float y , float z )
{
	this->m[ 0 ][ 0 ] = x;		this->m[ 0 ][ 1 ] = 0.0f;	this->m[ 0 ][ 2 ] = 0.0f;	this->m[ 0 ][ 3 ] = 0.0f;
	this->m[ 1 ][ 0 ] = 0.0f;	this->m[ 1 ][ 1 ] = y;		this->m[ 1 ][ 2 ] = 0.0f;	this->m[ 1 ][ 3 ] = 0.0f;
	this->m[ 2 ][ 0 ] = 0.0f;	this->m[ 2 ][ 1 ] = 0.0f;	this->m[ 2 ][ 2 ] = z;		this->m[ 2 ][ 3 ] = 0.0f;
	this->m[ 3 ][ 0 ] = 0.0f;	this->m[ 3 ][ 1 ] = 0.0f;	this->m[ 3 ][ 2 ] = 0.0f;	this->m[ 3 ][ 3 ] = 1.0f;
}

void Mat4f::initRotateTransform( float _x , float _y , float _z )
{
	Mat4f rx, ry, rz;

	const float x = toRadian( _x );
	const float y = toRadian( _y );
	const float z = toRadian( _z );

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

void Mat4f::initTranslationTransform( float x , float y , float z )
{
	this->m[ 0 ][ 0 ] = 1.0f; this->m[ 0 ][ 1 ] = 0.0f; this->m[ 0 ][ 2 ] = 0.0f; this->m[ 0 ][ 3 ] = x;
	this->m[ 1 ][ 0 ] = 0.0f; this->m[ 1 ][ 1 ] = 1.0f; this->m[ 1 ][ 2 ] = 0.0f; this->m[ 1 ][ 3 ] = y;
	this->m[ 2 ][ 0 ] = 0.0f; this->m[ 2 ][ 1 ] = 0.0f; this->m[ 2 ][ 2 ] = 1.0f; this->m[ 2 ][ 3 ] = z;
	this->m[ 3 ][ 0 ] = 0.0f; this->m[ 3 ][ 1 ] = 0.0f; this->m[ 3 ][ 2 ] = 0.0f; this->m[ 3 ][ 3 ] = 1.0f;
}

void Mat4f::initCameraTransform( const Vec3f &cam , const Vec3f &up )
{
	Vec3f N = cam;
	N.normalize();

	Vec3f U = up;
	U.normalize();
	U = U.cross( N );

	Vec3f V = N.cross( U );

	m[ 0 ][ 0 ] = U.x;	m[ 0 ][ 1 ] = U.y;	m[ 0 ][ 2 ] = U.z;	m[ 0 ][ 3 ] = 0.0f;
	m[ 1 ][ 0 ] = V.x;	m[ 1 ][ 1 ] = V.y;	m[ 1 ][ 2 ] = V.z;	m[ 1 ][ 3 ] = 0.0f;
	m[ 2 ][ 0 ] = N.x;	m[ 2 ][ 1 ] = N.y;	m[ 2 ][ 2 ] = N.z;	m[ 2 ][ 3 ] = 0.0f;
	m[ 3 ][ 0 ] = 0.0f;	m[ 3 ][ 1 ] = 0.0f;	m[ 3 ][ 2 ] = 0.0f;	m[ 3 ][ 3 ] = 1.0f;
}

void Mat4f::initPerspectiveProjectionTransform( float FOV , float width , float height , float zNear , float zFar )
{
	const float ar			= width / height;
	const float zRange		= zNear - zFar;
	const float tanHalfFOV	= tanf( toRadian( FOV / 2.0f ) );
	
	this->m[ 0 ][ 0 ] = 1.0f / ( tanHalfFOV * ar );	this->m[ 0 ][ 1 ] = 0.0f;				this->m[ 0 ][ 2 ] = 0.0f;						this->m[ 0 ][ 3 ] = 0.0f;
	this->m[ 1 ][ 0 ] = 0.0f;						this->m[ 1 ][ 1 ] = 1.0f / tanHalfFOV;	this->m[ 1 ][ 2 ] = 0.0f;						this->m[ 1 ][ 3 ] = 0.0f;
	this->m[ 2 ][ 0 ] = 0.0f;						this->m[ 2 ][ 1 ] = 0.0f;				this->m[ 2 ][ 2 ] = ( -zNear -zFar ) / zRange;	this->m[ 2 ][ 3 ] = 2.0f * zFar * zNear / zRange;
	this->m[ 3 ][ 0 ] = 0.0f;						this->m[ 3 ][ 1 ] = 0.0f;				this->m[ 3 ][ 2 ] = 1.0f;						this->m[ 3 ][ 3 ] = 0.0f;
}

/* Quaternion */
Quaternion::Quaternion( float x , float y , float z , float w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Quaternion::normalize( void )
{
	float length = sqrtf( this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w );

	this->x /= length;
	this->y /= length;
	this->z /= length;
	this->w /= length;
}

Quaternion Quaternion::conjugate( void )
{
	return Quaternion( -this->x , -this->y , -this->z , this->w );
}

Quaternion operator*( const Quaternion &l , const Quaternion &r )
{
	const float w = ( l.w * r.w ) - ( l.x * r.x ) - ( l.y * r.y ) - ( l.z * r.z );
	const float x = ( l.x * r.w ) + ( l.w * r.x ) + ( l.y * r.z ) - ( l.z * r.y );
	const float y = ( l.y * r.w ) + ( l.w * r.y ) + ( l.z * r.x ) - ( l.x * r.z );
	const float z = ( l.z * r.w ) + ( l.w * r.z ) + ( l.x * r.y ) - ( l.y * r.x );

	return Quaternion( x , y , z , w );
}
Quaternion operator*( const Quaternion &q , const Vec3f &v )
{
	const float w = - ( q.x * v.x ) - ( q.y * v.y ) - ( q.z * v.z );
    const float x =   ( q.w * v.x ) + ( q.y * v.z ) - ( q.z * v.y );
    const float y =   ( q.w * v.y ) + ( q.z * v.x ) - ( q.x * v.z );
    const float z =   ( q.w * v.z ) + ( q.x * v.y ) - ( q.y * v.x );

	return Quaternion( x , y , z, w );
}
