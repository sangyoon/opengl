#include "Matrix.h"

Matrix::Matrix( void )
{
	this->scaleVector			= math::Vec3f( 1.0f , 1.0f , 1.0f );
	this->worldPosVector		= math::Vec3f( 0.0f , 0.0f , 0.0f );
	this->rotateInformVector	= math::Vec3f( 0.0f , 0.0f , 0.0f );
}

Matrix::~Matrix( void ) {}

void Matrix::scale( float scaleX , float scaleY , float scaleZ )
{
	this->scaleVector.x = scaleX;
	this->scaleVector.y = scaleY;
	this->scaleVector.z = scaleZ;
}

void Matrix::worldPosition( float x , float y , float z )
{
	this->worldPosVector.x = x;
	this->worldPosVector.y = y;
	this->worldPosVector.z = z;
}

void Matrix::rotate( float rotateX , float rotateY , float rotateZ )
{
	this->rotateInformVector.x = rotateX;
	this->rotateInformVector.y = rotateY;
	this->rotateInformVector.z = rotateZ;
}

void Matrix::perspeciveProjection( float FOV , float width , float height ,  float zNear , float zFar )
{
	this->perspectiveProj.FOV		= FOV;
	this->perspectiveProj.width		= width;
	this->perspectiveProj.height	= height;
	this->perspectiveProj.zNear		= zNear;
	this->perspectiveProj.zFar		= zFar;
}

void Matrix::setCamera(  const math::Vec3f &position , const math::Vec3f &target , const math::Vec3f &up )
{
	this->camera.position	= position;
	this->camera.target		= target;
	this->camera.up			= up;
}

const math::Mat4f* Matrix::getTranslation( void )
{
	math::Mat4f scaleMat, rotateMat, translationMat, perspectiveProjectMat, cameraTranslateMat, cameraRotateMat;

	scaleMat.initScaleTransform( this->scaleVector.x , this->scaleVector.y , this->scaleVector.z );
	rotateMat.initRotateTransform( this->rotateInformVector.x , this->rotateInformVector.y , this->rotateInformVector.z );
	translationMat.initTranslationTransform( this->worldPosVector.x , this->worldPosVector.y , this->worldPosVector.z );
	cameraTranslateMat.initTranslationTransform( -this->camera.position.x , -this->camera.position.y , -this->camera.position.z );
	cameraRotateMat.initCameraTransform( this->camera.target , this->camera.up );
	perspectiveProjectMat.initPersProjTransform( this->perspectiveProj.FOV , this->perspectiveProj.width , this->perspectiveProj.height , this->perspectiveProj.zNear , this->perspectiveProj.zFar );

	this->transformation = perspectiveProjectMat * cameraRotateMat * cameraTranslateMat * translationMat * rotateMat * scaleMat;

	return &this->transformation;
}
