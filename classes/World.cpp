#include "World.h"

World::World(void)
{
	this->scale	= Vec3f( 1.0f , 1.0f , 1.0f );
	this->position	= Vec3f( 0.0f , 0.0f , 0.0f );
	this->rotate	= Vec3f( 0.0f , 0.0f , 0.0f );
}

void World::setScale( float x , float y , float z )
{
	this->scale.x = x;
	this->scale.y = y;
	this->scale.z = z;
}

void World::setPosition( float x , float y , float z )
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void World::setRotate( float x , float y , float z )
{
	this->rotate.x = x;
	this->rotate.y = y;
	this->rotate.z = z;
}

void World::setProjection( float FOV , float width , float height , float zNear , float zFar )
{
	this->projection.FOV	= FOV;
	this->projection.width	= width;
	this->projection.height	= height;
	this->projection.zNear	= zNear;
	this->projection.zFar	= zFar;
}

void World::setCamera( const Vec3f &eye , const Vec3f &cam , const Vec3f &up )
{
	this->camera.eye	= eye;
	this->camera.cam	= cam;
	this->camera.up		= up;
}

const Mat4f* World::getTransform()
{
	Mat4f scale, rotate, translation, camaraTranslation, camaraRotate, projection;

	scale.initScaleTransform( this->scale.x , this->scale.y , this->scale.z );
	rotate.initRotateTransform( this->rotate.x , this->rotate.y , this->rotate.z );
	translation.initTranslationTransform( this->position.x , this->position.y , this->position.z );

	camaraTranslation.initTranslationTransform( -this->camera.eye.x , -this->camera.eye.y , -this->camera.eye.z );
	camaraRotate.initCameraTransform( this->camera.cam , this->camera.up );

	projection.initPerspectiveProjectionTransform( this->projection.FOV , this->projection.width , this->projection.height , this->projection.zNear , this->projection.zFar );

	this->trasformation = projection * camaraRotate * camaraTranslation * translation * rotate * scale;

	return &this->trasformation;
}
