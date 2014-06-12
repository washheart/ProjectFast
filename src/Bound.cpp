#include "Bound.h";

Bound::Bound(osg::Vec2 point, int width, int height){
	this->point = point; 
	this->width = width; 
	this->height = height; 
}

bool Bound::contains(osg::Vec2 p){
	p -= point;
	return ((0 < p.x() && p.x() < width)  && (p.y() > -height && p.y() < 0));
} 