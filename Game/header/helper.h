#ifndef HELPER_H
#define HELPER_H


#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <set>
#include <assert.h>

using namespace std;

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <..\extended\glew-1.6.0\include\GL\glew.h>
#include <..\extended\GLFW3.3.2\glfw3.h>
#include <..\extended\glew-1.6.0\include\GL/wglew.h>


#include <..\extended\glm-0.9.1.1\glm\glm.hpp>


#include <..\extended\glm-0.9.1.1\glm/gtc/matrix_transform.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtx/quaternion.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtc/half_float.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtc/type_ptr.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtx/compatibility.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtx/transform.hpp>

#include <..\extended\SOIL\SOIL.h>


#ifndef PI
#define PI 3.14159265358979323
#endif

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p){ delete (p);  (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) {if(p){ delete [] (p);  (p)=NULL; } }
#endif

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#define INVALID_MATERIAL 0xFFFFFFFF
#define INVALID_OGL_VALUE 0xFFFFFFFF

enum ACTION
{
	ACTION_LEFT = 0,
	ACTION_RIGHT,
	ACTION_UP,
	ACTION_DOWN
};

#endif