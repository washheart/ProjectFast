#include "Gun.h"
#include "Shoot.h"
#include "Component.h"
#include <iostream>
Gun::Gun(){
	shoot = new Shoot();
	this->setUpdateCallback(shoot);
}

void Gun::toggle(){
	shoot->toggle();
}