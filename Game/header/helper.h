//+++++++++++++++++++++++++++++++++++++++++++++++
// Projekt : Gra 2D
// Tech    : 
//           OpenGL 3.3/ GLSL 330, 
//           Glew 1.6, 
//           GLFW 3 
//           GLM 0.9.1.1
// http://www.sworek.acsoftware.pl   
//
//+++++++++++++++++++++++++++++++++++++++++++++++
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

#pragma warning(push, 0)
#include <..\extended\glm-0.9.1.1\glm\glm.hpp>


#include <..\extended\glm-0.9.1.1\glm/gtc/matrix_transform.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtx/quaternion.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtc/half_float.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtc/type_ptr.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtx/compatibility.hpp>
#include <..\extended\glm-0.9.1.1\glm\gtx/transform.hpp>

#include <..\extended\SOIL\SOIL.h>
#pragma warning(pop)

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



#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p){ delete (p);  (p)=NULL; } }
#endif

template <class item>
float Distance(item& vPoint1, item& vPoint2)
{
	double distance = sqrt((vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
		(vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y));
	return (float)distance;
}


template <class item>
bool Collide(item& b1, item& b2, item& pos1, item& pos2)
{
	if (pos1.x + b1.x > pos2.x - b2.x &&
		pos1.x - b1.x < pos2.x + b2.x &&
		pos1.y + b1.y > pos2.y - b2.y &&
		pos1.y - b1.y < pos2.y + b2.y)
		return true;
	return false;
}

template <class item>
void DeleteFromVector(vector<item>& vec, int index)
{
	vec[index] = vec[vec.size() - 1];
	vec.pop_back();
}

enum class ACTION : int
{
	GRACZ_LEFT = 0,
	GRACZ_RIGHT = 1,
	GRACZ_UP = 2,
	GRACZ_DOWN = 3
};

#endif