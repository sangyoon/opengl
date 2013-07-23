#ifndef MATH_HEADER_INCLUDED
#define MATH_HEADER_INCLUDED

#define _USE_MATH_DEFINES
#include <cmath>

#define toRadian( x ) static_cast< float >( ( ( x ) * M_PI / 180.0f ) )
#define toDegree( x ) static_cast< float >( ( ( x ) * 180.0f / M_PI ) )

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

		Vec3f cross( const Vec3f &vector ) const;
		Vec3f &normalize( void );
		
		void toString() const;
	};

	struct Mat4f
	{
		float m[ 4 ][ 4 ];

		Mat4f() { }
		
		inline void initalize( void )
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
		void initCameraTransform( const math::Vec3f &target , const math::Vec3f &up );
		void initPersProjTransform( float FOV , float width , float height , float zNear, float zFar);
	};
}

#endif
