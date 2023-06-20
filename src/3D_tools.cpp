#include "3D_tools.h"

void setCamera() {
	gluLookAt(0.0, 0.0, 1.0,
			  0.0,0.0,0.0,
			  0.0,1.0,0.0);
}
