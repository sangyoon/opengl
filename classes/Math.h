#ifndef MATH_HEADER_INCLUDED
#define MATH_HEADER_INCLUDED

#include <cmath>

#define M_PI 3.14159265358979323846
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

	void rotate( float angle , const Vec3< T > &axis )
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
		
	inline void initIdentity( void );

	inline Mat4f operator*( const Mat4f &target ) const;

	void initScaleTransform( float x , float y , float z );
	void initRotateTransform( float _x , float _y , float _z );
	void initTranslationTransform( float x , float y , float z );
	void initCameraTransform( const Vec3f &cam , const Vec3f &up );
	void initPerspectiveProjectionTransform( float FOV , float width , float height , float zNear , float zFar );

public:
	float m[ 4 ][ 4 ];
};

class Quaternion
{
public:
	Quaternion( void ) : x( 0 ) , y( 0 ) , z( 0 ) , w( 0 ) { };
	Quaternion( float x , float y , float z , float w );
	~Quaternion( void ) { };

	void normalize( void );
	Quaternion conjugate( void );

public:
	float x, y, z, w;
};
Quaternion operator*( const Quaternion &l , const Quaternion &r );
Quaternion operator*( const Quaternion &q , const Vec3f &v );

#endif
