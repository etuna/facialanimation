

#include "MenuHandler.h"
#include "GL\freeglut.h"
#include "mat.h"
#include "vec.h"
#include "Angel.h"




#define v1 0
#define v2 1
#define v3 2
#define v4 3


GLuint program;
MenuHandler *menu;

using namespace std;
typedef Angel::vec4  point4;
void changeLightDirection(float dir);
void selectLights(int opt);
void neutralFace();
void sleepFace();
void popPoints();
void happyFace();
void shockedFace();
void sadFace();
void angryFace();
void suspiciousFace();
void inPeaceFace();
void noseWrinkle();
void MenuHandler::setGlobalMenuHandler(MenuHandler* m) {
	menu = m;
}

void MenuHandler::setProgram(GLuint p) {
	program = p;
}



void MenuHandler::setProjection(mat4 pr) {
	projection = pr;
}

void MenuHandler::setWH(GLfloat x, GLfloat y) {
	menu->w = x;
	menu->h = y;
}

void mainMenu(int opt) {

}



void dm_gouraudshading() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	menu->shading = 1.0;
	GLuint shading = glGetUniformLocation(program, "Shading");
	glUniform1f(shading , menu->shading);
	GLuint phgo = glGetUniformLocation(program, "ph_go");
	glUniform1f(phgo, 1.0);
	glutPostRedisplay();
}




void dm_phongshading() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	menu->shading = 1.0;
	GLuint shading = glGetUniformLocation(program, "Shading");
	glUniform1f(shading, menu->shading);
	GLuint phgo = glGetUniformLocation(program, "ph_go");
	glUniform1f(phgo,0.0);

	glutPostRedisplay();
}



void dm_wireframes() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	menu->shading = 0.0;
	GLuint shading = glGetUniformLocation(program, "Shading");
	glUniform1f(shading, menu->shading);
	glutPostRedisplay();
}

void drawCube() {
	//off_obj->load("cube.off");
	//off_obj->control = 0;
	//off_obj->reinit = 1;
	glutPostRedisplay();
}

void drawSphere() {
	//off_obj->load("shapeX.offx");
	//menu->shading = 1.0;
	//GLuint shading = glGetUniformLocation(program, "shading");
	//glUniform1f(shading , menu->shading);
	//std::cout << "SHADER : " << menu->shading << std::endl;
	//off_obj->control = 1;
	//off_obj->reinit = 1;
	
	glutPostRedisplay();

}


void drawCar() {
	//off_obj->load("car.off"); 
	//off_obj->control = 1;
	//off_obj->reinit = 1;
	glutPostRedisplay();
}

void drawTriangle() {
	//off_obj->load("triangle.off");
	//off_obj->control = 1;
	//off_obj->reinit = 1;
	glutPostRedisplay();
}


void drawCone() {
	//off_obj->load("cone.off");
	//off_obj->control = 1;
	//off_obj->reinit = 1;
	glutPostRedisplay();
}


void subMenu_obj(int opt) {

	switch (opt) {

	case 0:
		drawSphere();
		break;
	case 1:
		drawSphere();
		break;
	case 2:
		drawCar();
		break;
	case 3:
		drawTriangle();
		break;
	case 4:
		drawCone(); 
		break;
	}

}

void subMenu_drawing(int opt) {

	switch (opt) {
	case 0:
		dm_wireframes();
		break;
	case 1:
		dm_gouraudshading();
		break;
	case 2:
		dm_phongshading();
		break;
	case 3:
		menu->shading = 2.0;
		GLuint shading = glGetUniformLocation(program, "Shading");
		glUniform1f(shading, 2.0);
		GLuint phgo = glGetUniformLocation(program, "ph_go");
		glUniform1f(phgo, 1.0);
		glutPostRedisplay();
	}

}
void subMenu_color(int opt) {
	GLuint mcontrol;GLuint myColor;
	switch (opt) {
	case 0:
		
		//myColor = glGetUniformLocation(program, "myColor");
		//mcontrol = glGetUniformLocation(program, "control");
		//glUniform1f(mcontrol, 1.0);
		//glUniform4f(myColor, 1.0, 0.0, 0.0, 0.0);
		//glutPostRedisplay();
		break;
	case 1:
		
		//myColor = glGetUniformLocation(program, "myColor");
		
		//mcontrol = glGetUniformLocation(program, "control");
		//glUniform1f(mcontrol, 1.0);
		//glUniform4f(myColor, 1.0,1.0, 0.0, 1.0);
		//glutPostRedisplay();
		break;
	case 2:
		
		//myColor = glGetUniformLocation(program, "myColor");
		
		//mcontrol = glGetUniformLocation(program, "control");
		//glUniform1f(mcontrol, 1.0);
		//glUniform4f(myColor,0.0,1.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 3:/*
		color4(0.0, 0.0, 0.0, 1.0),  // black
			color4(1.0, 0.0, 0.0, 1.0),  // red
			color4(1.0, 1.0, 0.0, 1.0),  // yellow
			color4(0.0, 1.0, 0.0, 1.0),  // green
			color4(0.0, 0.0, 1.0, 1.0),  // blue
			color4(1.0, 0.0, 1.0, 1.0),  // magenta
			color4(1.0, 1.0, 1.0, 1.0),  // white
			color4(0.0, 1.0, 1.0, 1.0)   // cyan*/
		
		//myColor = glGetUniformLocation(program, "myColor");
		
		//mcontrol = glGetUniformLocation(program, "control");
		//glUniform1f(mcontrol, 1.0);
		//glUniform4f(myColor, 0.0, 0.0, 1.0, 1.0);
		//glutPostRedisplay();
		break;
	case 4:
		
		//myColor = glGetUniformLocation(program, "myColor");
		
		//mcontrol = glGetUniformLocation(program, "control");
		//glUniform1f(mcontrol, 1.0);
		//glUniform4f(myColor, 1.0, 0.0, 1.0, 1.0);
		//glutPostRedisplay();
		break;
	case 5:
		
		//myColor = glGetUniformLocation(program, "myColor");
		
		//mcontrol = glGetUniformLocation(program, "control");
		//glUniform1f(mcontrol, 1.0);
		//glUniform4f(myColor, 0.0, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	}

}

void MenuHandler::setRotHB(int i) {
	rotation_hearthbeat = i;
}

void subMenu_motion(int opt) {
	switch (opt) {
	case 0:
		menu->rotation_hearthbeat = 0;
		break;
	case 1:
		menu->rotation_hearthbeat = 1;
		break;
	}
}


void subMenu_plasticmetal(int opt) {
	GLuint metal_plastic;
	switch (opt) {
	case 0:
		metal_plastic = glGetUniformLocation(program, "metal_plastic");
		glUniform1f(metal_plastic, 0.01);
		glutPostRedisplay();
		break;
	case 1:
		metal_plastic = glGetUniformLocation(program, "metal_plastic");
		glUniform1f(metal_plastic, 5);
		glutPostRedisplay();
		break;
	}
}




void subMenu_bgcolor(int opt) {
	switch (opt) {
	case 0:
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glutPostRedisplay();
		break;
	case 1:
		glClearColor(0, 0, 0, 1);
		glutPostRedisplay();
		break;
	case 2:
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glutPostRedisplay();
		break;
	}
}

void subMenu_proj(int opt) {
	switch (opt) {
		int ModelView;
		int Projection;
	case 0:
		Projection = glGetUniformLocation(program, "Projection");
		//ModelView = glGetUniformLocation(program, "ModelView");
		//glUniformMatrix4fv(ModelView, 1, GL_TRUE, Translate(vec3(0.0, 0.0, -3.0))*Scale(0.2, 0.2, 0.2));
		menu->projectionortho = Ortho(-1.0 , 1.0 , -1.0, 1.0, -1.0, 1.0)*Scale(0.8, 0.8, 0.8)*Translate(vec3(0.0, 0.0, 3.0));
		glUniformMatrix4fv(Projection, 1, GL_TRUE, menu->projectionortho);
		glutPostRedisplay();
		break;
	case 1:
		//ModelView = glGetUniformLocation(program, "ModelView");
		//glUniformMatrix4fv(ModelView, 1, GL_TRUE, menu->defaultModelView);
		Projection = glGetUniformLocation(program, "Projection");
		glUniformMatrix4fv(Projection, 1, GL_TRUE, menu->projectionpers);
		glutPostRedisplay();
		break;
	}
}



void subMenu_mood(int opt) {
	switch (opt) {

	case 0:neutralFace(); glutPostRedisplay(); break;
	case 1:happyFace(); glutPostRedisplay(); break;
	case 2:angryFace(); glutPostRedisplay(); break;
	case 3:sadFace(); glutPostRedisplay(); break;
	case 4:shockedFace(); glutPostRedisplay(); break;
	case 5:sleepFace(); glutPostRedisplay();break;
	case 6:suspiciousFace(); glutPostRedisplay(); break;
	case 7:inPeaceFace(); glutPostRedisplay(); break;
	case 8:noseWrinkle(); glutPostRedisplay(); break;
	}
}



void neutralFace() {
	menu->globalPts = menu->defaultPts;
	glutPostRedisplay;
}

void sleepFace() {

	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {

		if (i == 21) {
			menu->globalVertices[21][v1] += 0;
			menu->globalVertices[21][v2] += -0.062000;
			menu->globalVertices[21][v3] += 0.01;

		}
		else if (i == 22) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0.01;
		}
		else if (i == 54) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0620;
			menu->globalVertices[i][v3] += 0.01;
		}
		else if (i == 55) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0.01;
		}
		else if (i == 97) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.007;
		}
		else if (i == 98) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.0070;
		}
		else if (i == 99) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 100) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 105) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 106) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 107) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 108) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}


		popPoints();





	}

	

}

void happyFace() {



	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {
	
	
		if (i == 31) {
			menu->globalVertices[21][v1] += 0.100000;
			menu->globalVertices[21][v2] += 0;
			menu->globalVertices[21][v3] += 0;

		}
		else if (i == 64) {
			menu->globalVertices[i][v1] += -0.100000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 88) {
			menu->globalVertices[i][v1] += 0.100000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 89) {
			menu->globalVertices[i][v1] += -0.100000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 79) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 80) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 81) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 82) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 83) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 84) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 85) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 86) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 90) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 91) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 81) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.2;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 82) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.2;
			menu->globalVertices[i][v3] += 0;
		}





		//lower lip
		if (i == 8) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0400;
			menu->globalVertices[i][v3] += 0;
		}

		else if (i == 83) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 84) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 85) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 86) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 90) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 91) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 40) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0700;
			menu->globalVertices[i][v3] += 0;
		}







		else if (i == 17) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0400;
			menu->globalVertices[i][v3] += 0;
		}

		else if (i == 50) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0400;
			menu->globalVertices[i][v3] += 0;
		}







		//left eyeball
		if (i == 67) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 68) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 71) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 72) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;

		}
		//right eyeball
		if (i == 69) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 70) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 73) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 74) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;

		}

		
	
	}


popPoints();

}

void noseWrinkle() {
	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {

		if (i == 2) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.086957;
			menu->globalVertices[i][v3] += 0.013043;
		}
		if (i == 3) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.043478;
			menu->globalVertices[i][v3] += 0;
		}if (i == 5) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.086957;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 26) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.043478;
			menu->globalVertices[i][v3] += -0.0173910;
		}if (i == 25) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.043478;
			menu->globalVertices[i][v3] += -0.008696;
		}
		if (i == 24) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}if (i == 22) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 59) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.043478;
			menu->globalVertices[i][v3] += -0.017391;
		}if (i == 58) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.043478;
			menu->globalVertices[i][v3] += -0.008696;
		}
		if (i == 57) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}if (i == 55) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 68) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.008696;
			menu->globalVertices[i][v3] += 0;
		}if (i == 70) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.008696;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 72) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.008696;
			menu->globalVertices[i][v3] += 0;
		}if (i == 74) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.008696;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 99) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}if (i == 100) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 101) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}if (i == 102) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 107) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}if (i == 108) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.032500;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 109) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}if (i == 110) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.017391;
			menu->globalVertices[i][v3] += 0;
		}



	}
	popPoints();
}

void sadFace() {



	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {


		if (i == 17) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.120;
			menu->globalVertices[i][v3] += 0;
		}

		else if (i == 50) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.120;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 31) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.070;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 64) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.070;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 88) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.040;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 89) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.040;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 8) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.020;
			menu->globalVertices[i][v3] += 0;
		}





		if (i == 7) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.086957;
			menu->globalVertices[i][v3] += 0.021739;

		}
		else if (i == 33) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.065217;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 66) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.065217;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 79) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 80) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 81) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 82) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 87) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.065217;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 88) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 89) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0;
		}

	}
	popPoints();
}

void shockedFace() {



	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {


		if (i == 7) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.086957;
			menu->globalVertices[i][v3] += 0.021739;

		}
		else if (i == 33) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.065217;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 66) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.065217;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 79) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 80) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 81) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 82) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.05;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 87) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.065217;
			menu->globalVertices[i][v3] += 0.021739;
		}
		else if (i == 88) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 89) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 8) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0400;
			menu->globalVertices[i][v3] += 0;
		}

		else if (i == 83) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 84) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 85) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 86) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 90) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 91) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 40) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}





		if (i == 15) {
			menu->globalVertices[i][v1] += 0.021739;
			menu->globalVertices[i][v2] += 0.173913;
			menu->globalVertices[i][v3] += -0.021739;

		}
		else if (i == 16) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}
		else if (i == 17) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.021739;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 18) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}
		else if (i == 48) {
			menu->globalVertices[i][v1] += -0.021739;
			menu->globalVertices[i][v2] += 0.173913;
			menu->globalVertices[i][v3] += -0.021739;
		}
		else if (i == 49) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}
		else if (i == 50) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.021739;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 51) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}


		if (i == 21) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.030;
			menu->globalVertices[i][v3] += -0.0100;

		}
		else if (i == 54) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.030;
			menu->globalVertices[i][v3] += -0.0100;
		}
		else if (i == 97) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;
		}
		else if (i == 98) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;
		}
		else if (i == 105) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;
		}
		else if (i == 106) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;

		}





		//left eyeball
		if (i == 67) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 68) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 71) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 72) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;

		}
		//right eyeball
		if (i == 69) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 70) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 73) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 74) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;

		}










	}


		popPoints();

}

void angryFace() {
	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {

		//left eye
		if (i == 16) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.060;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 17) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.060;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 18) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.060;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 15) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.020;
			menu->globalVertices[i][v3] += 0;
		}


		//righteye

		if (i == 48) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.020;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 49) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.060;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 50) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.060;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 51) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] -= 0.060;
			menu->globalVertices[i][v3] += 0;
		}



		//lip press
		if (i == 8) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.032500;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 33) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 66) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 7) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0210;
			menu->globalVertices[i][v3] += 0;
		}if (i == 79) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.02000;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 80) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.02000;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 85) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.023;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 86) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.023;
			menu->globalVertices[i][v3] += 0;
		}







		//left eyeball
		if (i == 67) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 68) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 71) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 72) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;

		}
		//right eyeball
		if (i == 69) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 70) {
			menu->globalVertices[i][v1] += 0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 73) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += -0.015;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 74) {
			menu->globalVertices[i][v1] += -0.015;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += 0;

		}











	
	}

	popPoints();
}

void inPeaceFace() {

	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {


		if (i == 31) {
			menu->globalVertices[21][v1] += 0.100000;
			menu->globalVertices[21][v2] += 0;
			menu->globalVertices[21][v3] += 0;

		}
		else if (i == 64) {
			menu->globalVertices[i][v1] += -0.100000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 88) {
			menu->globalVertices[i][v1] += 0.100000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 89) {
			menu->globalVertices[i][v1] += -0.100000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 79) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 80) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 81) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 82) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 83) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 84) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 85) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 86) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 90) {
			menu->globalVertices[i][v1] += 0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 91) {
			menu->globalVertices[i][v1] += -0.050000;
			menu->globalVertices[i][v2] += 0;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 81) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.2;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 82) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.2;
			menu->globalVertices[i][v3] += 0;
		}





		//lower lip
		if (i == 8) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0400;
			menu->globalVertices[i][v3] += 0;
		}

		else if (i == 83) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 84) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 85) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 86) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 90) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 91) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 40) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0700;
			menu->globalVertices[i][v3] += 0;
		}







		else if (i == 17) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0400;
			menu->globalVertices[i][v3] += 0;
		}

		else if (i == 50) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0400;
			menu->globalVertices[i][v3] += 0;
		}






		//Eyes closed
		if (i == 21) {
			menu->globalVertices[21][v1] += 0;
			menu->globalVertices[21][v2] += -0.062000;
			menu->globalVertices[21][v3] += 0.01;

		}
		else if (i == 22) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0.01;
		}
		else if (i == 54) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0620;
			menu->globalVertices[i][v3] += 0.01;
		}
		else if (i == 55) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0200;
			menu->globalVertices[i][v3] += 0.01;
		}
		else if (i == 97) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.007;
		}
		else if (i == 98) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.0070;
		}
		else if (i == 99) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 100) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 105) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 106) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.04500;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 107) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}
		else if (i == 108) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.0150;
			menu->globalVertices[i][v3] += 0.007000;
		}




	}


	popPoints();

}

void suspiciousFace() {


	int k = 0;
	for (k = 0; k < menu->globalNumVertices; k++) {
		menu->globalVertices[k] = menu->defaultVertices[k];
	}


	int i = 0;
	for (i = 0; i < menu->globalNumVertices; i++) {


		//lip press
		if (i == 8) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.032500;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 33) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 66) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0200;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 7) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.0210;
			menu->globalVertices[i][v3] += 0;
		}if (i == 79) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.02000;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 80) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += -0.02000;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 85) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.023;
			menu->globalVertices[i][v3] += 0;
		}
		if (i == 86) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.023;
			menu->globalVertices[i][v3] += 0;
		}


		/*

		if (i == 15) {
			menu->globalVertices[i][v1] += 0.021739;
			menu->globalVertices[i][v2] += 0.173913;
			menu->globalVertices[i][v3] += -0.021739;

		}
		else if (i == 16) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}
		else if (i == 17) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.021739;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 18) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}*/
		else if (i == 48) {
			menu->globalVertices[i][v1] += -0.021739;
			menu->globalVertices[i][v2] += 0.173913;
			menu->globalVertices[i][v3] += -0.021739;
		}
		else if (i == 49) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}
		else if (i == 50) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.021739;
			menu->globalVertices[i][v3] += 0;
		}
		else if (i == 51) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.152174;
			menu->globalVertices[i][v3] += -0.021739;
		}


		if (i == 21) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.030;
			menu->globalVertices[i][v3] += -0.0100;

		}
		else if (i == 54) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.030;
			menu->globalVertices[i][v3] += -0.0100;
		}
		else if (i == 97) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;
		}
		else if (i == 98) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;
		}
		else if (i == 105) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;
		}
		else if (i == 106) {
			menu->globalVertices[i][v1] += 0;
			menu->globalVertices[i][v2] += 0.015;
			menu->globalVertices[i][v3] += -0.00700;

		}
	}
	popPoints();



}

void
popPoints() {
	int i, index = 0;
	point4 temp1, temp2, temp3, temp4;
	//vec3 nor1,nor2,nor3;
	//vec2 cord1, cord2, cord3;
	menu->globalPts = new point4[menu->globalNumTriangles * 3];
	//nors = new vec3[numtriangles * 3];
	for (i = 0; i < menu->globalNumTriangles; i++) {
		temp1.x = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v1])].x;
		temp1.y = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v1])].y;
		temp1.z = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v1])].z;
		temp1.w = 1.0;

		temp2.x = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v2])].x;
		temp2.y = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v2])].y;
		temp2.z = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v2])].z;
		temp2.w = 1.0;

		temp3.x = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v3])].x;
		temp3.y = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v3])].y;
		temp3.z = menu->globalVertices[unsigned int(menu->defaultTriangles[i][v3])].z;
		temp3.w = 1.0;

		menu->globalPts[3 * i] = normalize(temp1);
		menu->globalPts[(3 * i) + 1] = normalize(temp2);
		menu->globalPts[(3 * i) + 2] = normalize(temp3);



	}
}


void subMenu_lights(int opt) {
	switch (opt) {
	case 0:
		selectLights(0);
		glutPostRedisplay();
		break;
	case 1:
		selectLights(1);
		glutPostRedisplay();
		break;
	
	case 2:
		selectLights(2);
		glutPostRedisplay();
		break;
}
}

void selectLights(int opt) {
	if (opt == 0) {
		GLuint lights = glGetUniformLocation(program, "lights");
		glUniform1f(lights, 0.0);
	}else if (opt == 1) {
		//we have already one
		point4 light_position(-2.0, 0.0, 0.0, 1.0);
		glUniform4fv(glGetUniformLocation(program, "LightPosition"),
			1, light_position);
		GLuint lights = glGetUniformLocation(program, "lights");
		glUniform1f(lights, 1.0);
	}
	else {
		//add one more
		point4 light_position(-2.0, 0.0, 0.0, 1.0);
		glUniform4fv(glGetUniformLocation(program, "LightPosition"),
			1, light_position);
		GLuint lights = glGetUniformLocation(program, "lights");
		glUniform1f(lights, 1.0);


		point4 light2_position(2.0, 0.0, 0.0, 1.0);
		glUniform4fv(glGetUniformLocation(program, "Light2Position"),
			1, light2_position);
		
		 lights = glGetUniformLocation(program, "lights");
		glUniform1f(lights, 2.0);
	}
}

void subMenu_lightDir(int opt) {
	switch (opt) {
	case 0:
		changeLightDirection(0.0);
		glutPostRedisplay();
		break;
	case 1:
		changeLightDirection(1.0);
		glutPostRedisplay();
		break;
	case 2:
		changeLightDirection(5.0);
		glutPostRedisplay();
		break;
	}
}

void changeLightDirection(float dir) {
	if (dir == 0.0) {
		point4 light_position(-2.0, 0.0, 0.0, 1.0);
		glUniform4fv(glGetUniformLocation(program, "LightPosition"),
			1, light_position);
		glutPostRedisplay();
		
	}
	else if (dir == 1.0) {
		point4 light_position(0.0, 0.0, 1.0, 1.0);
		glUniform4fv(glGetUniformLocation(program, "LightPosition"),
			1, light_position);
		glutPostRedisplay();
	}
	else {
		point4 light_position(2.0, 0.0, 1.0, 1.0);
		glUniform4fv(glGetUniformLocation(program, "LightPosition"),
			1, light_position);
		glutPostRedisplay();
	}
}




MenuHandler::MenuHandler() {

	//menu->drawingMode = 0.0;

	rotation_hearthbeat = 0;
	scl = 0.4;
	orth_pers = 0;

	int proj_type = glutCreateMenu(subMenu_proj);
	glutAddMenuEntry("Ortho", 0);
	glutAddMenuEntry("Perspective", 1);


	int bgcolor = glutCreateMenu(subMenu_bgcolor);
	glutAddMenuEntry("white", 0);
	glutAddMenuEntry("black", 1);
	glutAddMenuEntry("gray", 2);


	int obj_type = glutCreateMenu(subMenu_obj);
	glutAddMenuEntry("Cube", 0);
	glutAddMenuEntry("Sphere", 1);
	glutAddMenuEntry("Car", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Cone", 4);


	int mood_menu = glutCreateMenu(subMenu_mood);
	glutAddMenuEntry("NEUTRAL", 0);
	glutAddMenuEntry("HAPPY", 1);
	glutAddMenuEntry("ANGRY", 2);
	glutAddMenuEntry("SAD", 3);
	glutAddMenuEntry("SHOCKED", 4);
	glutAddMenuEntry("SLEEP", 5);
	glutAddMenuEntry("SUSPICIOUS", 6);
	glutAddMenuEntry("IN PEACE", 7);
	glutAddMenuEntry("NOSE WRINKLE", 8);

	int motion_menu = glutCreateMenu(subMenu_motion);
	glutAddMenuEntry("Rotate", 0);
	glutAddMenuEntry("Hearth Beat", 1);


	int drawing_mode = glutCreateMenu(subMenu_drawing);
	glutAddMenuEntry("wireframe", 0);
	glutAddMenuEntry("Shaded", 1);
	glutAddMenuEntry("Colored", 2);

	int plastic_metal = glutCreateMenu(subMenu_plasticmetal);
	glutAddMenuEntry("plastic", 0);
	glutAddMenuEntry("metal", 1);
 
	int color = glutCreateMenu(subMenu_color);
	glutAddMenuEntry("red", 0);
	glutAddMenuEntry("yellow", 1);
	glutAddMenuEntry("green", 2);
	glutAddMenuEntry("blue", 3);
	glutAddMenuEntry("magenta", 4);
	glutAddMenuEntry("black", 5);

	int lightdir = glutCreateMenu(subMenu_lightDir);
	glutAddMenuEntry("left", 0);
	glutAddMenuEntry("center", 1);
	glutAddMenuEntry("right", 2);

	int lights = glutCreateMenu(subMenu_lights);
	glutAddMenuEntry("zero", 0);
	glutAddMenuEntry("one", 1);
	glutAddMenuEntry("two", 2);

	glutCreateMenu(mainMenu);
	glutAddSubMenu("BACKGROUND", bgcolor);
	glutAddSubMenu("PROJECTION", proj_type);
	glutAddSubMenu("MOOD", mood_menu);
	//glutAddSubMenu("MOTION TYPE", motion_menu);
	glutAddSubMenu("DRAWING MODE", drawing_mode);
	//glutAddSubMenu("MATERIAL", plastic_metal);
	//glutAddSubMenu("LIGHT DIRECTION", lightdir);
	//glutAddSubMenu("NUMBER OF LIGHTS", lights);
	//glutAddSubMenu("COLOR", color);

	glutAttachMenu(GLUT_RIGHT_BUTTON);



}

MenuHandler::~MenuHandler() {

}



