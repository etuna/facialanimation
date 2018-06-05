#pragma once
#include "mat.h"
#include "mat.h"
#include "vec.h"
#include "Angel.h"

typedef Angel::vec4  point4;

class MenuHandler {


public: 
	
	int rotation_hearthbeat;
	mat4 projection;
	
	float drawingMode;
	GLfloat w, h;
	GLfloat scl;
	mat4 modelView;
	point4 *defaultVertices;
	point4 *globalVertices;
	int orth_pers;
	point4 *globalPts;
	point4 *defaultPts;
	float shading;
	mat4 defaultModelView;
	int globalNumVertices;
	int globalNumTriangles;
	mat4  projectionpers;
	mat4 projectionortho;
	vec3 *defaultTriangles;


	//functions
	void setWH(GLfloat, GLfloat);
	MenuHandler(void);
	~MenuHandler(void);
	void setProjection(mat4);
	//void setOffObj(OffModel*);
	void setProgram(GLuint);
	void setRotHB(int);
	void setGlobalMenuHandler(MenuHandler*);

};