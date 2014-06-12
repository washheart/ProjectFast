#include "Star.h"

#include "Component.h"
#include "Scene.h"

#include <osg/Material>
#include <osg/Shader>
#include <osg/Program>
#include <iostream>

Star::Star(){
	this->addChild(Component::getStar());
	this->approachVelocity(osg::Vec3(0.0, -2.0, 0.0), 1);

	osg::ref_ptr<osg::StateSet> starState = this->getOrCreateStateSet();
	osg::ref_ptr<osg::Material> starMaterial = new osg::Material;
	starMaterial->setDiffuse(osg::Material::FRONT, osg::Vec4(0.2f, 0.2f, 0.1f, 1.0f));
	starMaterial->setSpecular(osg::Material::FRONT, osg::Vec4(0.8f, 0.8f, 0.4f, 1.0f));
	starMaterial->setShininess(osg::Material::FRONT, 128.0f);
	starState->setAttribute(starMaterial.get());
}