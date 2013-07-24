#ifndef MATH_HEADER_INCLUDED
#define MATH_HEADER_INCLUDED

#define _USE_MATH_DEFINES
#include <cmath>

#define toRadian( x ) static_cast< float >( ( ( x ) * M_PI / 180.0f ) )
#define toDegree( x ) static_cast< float >( ( ( x ) * 180.0f / M_PI ) )

template< typename T > class Vec2
{
public:
	Vec2( void ) : x( 0 ) , y( 0 ) { };

	Vec2( T x , T y )
	{
		this->x = x;
		this->y = y;
	}

	~Vec2( void ) { };
	
	Vec2& operator+=( const Vec2< T > &r )
	{
		this->x += r.x;
		this->y += r.y;

		return *this;
	}

	Vec2& operator-=( const Vec2< T > &r )
	{
		this->x -= r.x;
		this->y -= r.y;

		return *this;
	}

	Vec2& operator*=( float scale )
	{
		this->x *= scale;
		this->y *= scale;

		return *this;
	}

	Vec2 cross( const Vec2< T > &r ) const
	{
		const float x = this->y * r.z - this->z * r.y;
		const float y = this->z * r.x - this->x * r.z;

		return Vec2< T >( x , y );
	}

	Vec2< T > &normalize( void )
	{
		const float length = sqrtf( this->x * this->x + this->y * this->y );
		
		this->x /= length;
		this->y /= length;
		
		return *this;
	}

	void print( void ) const
	{
		std::cout << this->x << ", " << this->y;
	}

public:
	T x, y;
};
template < typename T > inline Vec2< T > operator+( const Vec2< T > &l , const Vec2< T > r )
{
	return Vec2< T >( l.x + r.x , l.y + r.y );
}
template < typename T > inline Vec2< T > operator-( const Vec2< T > &l , const Vec2< T > r )
{
	return Vec2< T >( l.x - r.x , l.y - r.y );
}
template < typename T > inline Vec2< T > operator*( const Vec2< T > &l , float scale )
{
	return Vec2< T >( l.x * scale , l.y * scale );
}

template < typename T > class Vec3
{
public:
	Vec3( void ) : x( 0 ) , y( 0 ) { };

	Vec3( T x , T y , T z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	~Vec3( void ) { };
	
	Vec3& operator+=( const Vec3< T > &r )
	{
		this->x += r.x;
		this->y += r.y;
		this->z += r.z;

		return *this;
	}

	Vec3& operator-=( const Vec3< T > &r )
	{
		this->x -= r.x;
		this->y -= r.y;
		this->z -= r.z;

		return *this;
	}

	Vec3& operator*=( float scale )
	{
		this->x *= scale;
		this->y *= scale;
		this->z *= scale;

		return *this;
	}

	Vec3 cross( const Vec3< T > &r ) const
	{
		const float x = this->y * r.z - this->z * r.y;
		const float y = this->z * r.x - this->x * r.z;
		const float z = this->x * r.y - this->y * r.x;

		return Vec3< T >( x , y , z );
	}

	Vec3< T > &normalize( void )
	{
		const float length = sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
		
		this->x /= length;
		this->y /= length;
		this->z /= length;
		
		return *this;
	}

	void rotate( float angle , const Vec3f axis )
	{
		const float sinHalfAngle = sinf( toRadian( angle / 2 ) );
		const float cosHalfAngle = cosf( toRadian( angle / 2 ) );

		const float rx = axis.x * sinHalfAngle;
		const float ry = axis.y * sinHalfAngle;
		const float rz = axis.z * sinHalfAngle;
		const float rw = cosHalfAngle;

		Quaternion rot( rx , ry , rz , rw );
		Quaternion conj = rot.conjugate();
		Quaternion w = rot * ( *this ) * conj;

		this->x = w.x;
		this->y = w.y;
		this->z = w.z;
	}

	void print( void ) const
	{
		std::cout << this->x << ", " << this->y << ", " << this->z;
	}

public:
	T x, y, z;
};
template < typename T > inline Vec3< T > operator+( const Vec3< T > &l , const Vec3< T > r )
{
	return Vec3< T >( l.x + r.x , l.y + r.y , l.z + r.z );
}
template < typename T > inline Vec3< T > operator-( const Vec3< T > &l , const Vec3< T > r )
{
	return Vec3< T >( l.x - r.x , l.y - r.y , l.z - r.z );
}
template < typename T > inline Vec3< T > operator*( const Vec3< T > &l , float scale )
{
	return Vec3< T >( l.x * scale , l.y * scale , l.z * scale );
}

typedef Vec2< unsigned char > Vec2b;
typedef Vec2< int > Vec2i;
typedef Vec2< float > Vec2f;
typedef Vec3< unsigned char > Vec3b;
typedef Vec3< int > Vec3i;
typedef Vec3< float > Vec3f;

class Mat4f
{
public:
	Mat4f( void ) { };
	~Mat4f( void ) { };
		
	inline void initIdentity( void )
	{
		m[ 0 ][ 0 ] = 1.0f; m[ 0 ][ 1 ] = 0.0f; m[ 0 ][ 2 ] = 0.0f; m[ 0 ][ 3 ] = 0.0f;
		m[ 1 ][ 0 ] = 0.0f; m[ 1 ][ 1 ] = 1.0f; m[ 1 ][ 2 ] = 0.0f; m[ 1 ][ 3 ] = 0.0f;
		m[ 2 ][ 0 ] = 0.0f; m[ 2 ][ 1 ] = 0.0f; m[ 2 ][ 2 ] = 1.0f; m[ 2 ][ 3 ] = 0.0f;
		m[ 3 ][ 0 ] = 0.0f; m[ 3 ][ 1 ] = 0.0f; m[ 3 ][ 2 ] = 0.0f; m[ 3 ][ 3 ] = 1.0f;
	}

	inline Mat4f operator*( const Mat4f &target ) const
	{
		Mat4f returnMat;

		for( unsigned int i = 0 ; i < 4 ; ++i )
			for( unsigned int j = 0 ; j < 4 ; ++j )
				returnMat.m[ i ][ j ] = m[ i ][ 0 ] * target.m[ 0 ][ j ] + m[ i ][ 1 ] * target.m[ 1 ][ j ] + m[ i ][ 2 ] * target.m[ 2 ][ j ] + m[ i ][ 3 ] * target.m[ 3 ][ j ];

		return returnMat;
	}

	void initScaleTransform( float scaleX , float scaleY , float scaleZ );
	void initRotateTransform( float rotateX , float rotateY , float rotateZ );
	void initTranslationTransform( float x , float y , float z );
	void initCameraTransform( const Vec3f &target , const Vec3f &up );
	void initPersProjTransform( float FOV , float width , float height , float zNear, float zFar);

public:
	float m[ 4 ][ 4 ];
};

class Quaternion
{
public:
	Quaternion( void ) : x( 0 ) , y( 0 ) , z( 0 ) , w( 0 ) { };

	Quaternion( float x , float y , float z , float w )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	~Quaternion( void ) { };

	void normalize( void )
	{
		float length = sqrtf( this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w );

		this->x /= length;
		this->y /= length;
		this->z /= length;
		this->w /= length;
	}

	Quaternion conjugate( void )
	{
		return Quaternion( -this->x , -this->y , -this->z , -this->w );
	}

public:
	float x, y, z, w;
};
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

#endif
