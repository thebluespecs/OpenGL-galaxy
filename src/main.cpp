#include "Controller.h"

int main(){
	View v(1000,1000);
	Renderer r;
	Controller c(v, r);
	c.display();
}