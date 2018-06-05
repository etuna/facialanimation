//
//  Display a rotating cube with lighting - Gouraud shading
//
//  Light and material properties are sent to the shader as uniform
//    variables.  Vertex positions and normals are sent as vertex attributes
//

#include "Angel.h"
#include "mat.h"
#include <iostream>
#include <string>
#include <fstream>
#include "vec.h"
#include "MenuHandler.h"



#define v1 0
#define v2 1
#define v3 2
#define v4 3

#define NEUTRAL 100
#define HAPPY 101
#define ANGRY 102
#define SAD 103
#define SHOCKED 104
#define SLEEP 105
#define SUSPICIOUS 106
#define INPEACE 107

using namespace std;

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
//const int  TextureSize = 2048;
fstream file;
point4 *mvertices;
vec3  * mnormals;
vec3 *triangles;
//GLuint texture[1];
//GLubyte image[TextureSize][TextureSize][3];
GLuint mprogram;
point4 *pts;
//vec3 *nors;
int numvertices, numtriangles;
MenuHandler* menuHandler;
float scale = 1;
GLfloat w, h;
int mood = 100;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[NumVertices];
vec3   normals[184*3];
vec3* loadOff(std::string filename);
//color4 *tex_colors;
//vec2 tex_coords[85617*3];
//vec2 vt_cords[45149];
color4 colors[184*3];
void populatePoints();
void setProjections();
vec3* readPPM();
// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5, -0.5, -0.5, 1.0 ),
    point4( -0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5, -0.5, -0.5, 1.0 )
};

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;

//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors
//    to the vertices

int Index = 0;
// RGBA olors
color4 vertex_colors[8] = {
	color4(0.0, 0.0, 0.0, 1.0),  // black
	color4(1.0, 0.0, 0.0, 1.0),  // red
	color4(1.0, 1.0, 0.0, 1.0),  // yellow
	color4(0.0, 1.0, 0.0, 1.0),  // green
	color4(0.0, 0.0, 1.0, 1.0),  // blue
	color4(1.0, 0.0, 1.0, 1.0),  // magenta
	color4(1.0, 1.0, 1.0, 1.0),  // white
	color4(0.0, 1.0, 1.0, 1.0)   // cyan
};

void
quad( int a, int b, int c, int d )
{
    // Initialize temporary vectors along the quad's edge to
    //   compute its face normal 
    vec4 u = vertices[b] - vertices[a];
    vec4 v = vertices[c] - vertices[b];

    vec3 normal = normalize( cross(u, v) );

    normals[Index] = normal; points[Index] = vertices[a]; Index++;
    normals[Index] = normal; points[Index] = vertices[b]; Index++;
    normals[Index] = normal; points[Index] = vertices[c]; Index++;
    normals[Index] = normal; points[Index] = vertices[a]; Index++;
    normals[Index] = normal; points[Index] = vertices[c]; Index++;
    normals[Index] = normal; points[Index] = vertices[d]; Index++;
    
    //Note that normals are fixed for a given face of the cube.
    //So the normal of a vertex is NOT computed based on neighboring faces.
    //which makes sense in this example since this is a cube with only 6 faces.
}

//----------------------------------------------------------------------------
// generate 12 triangles: 36 vertices and 36 colors
void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}
//----------------------------------------------------------------------------
// OpenGL initialization
void
minit()
{
    colorcube();

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals),
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points),
		     sizeof(normals), normals );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
	
	mprogram = program;
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    GLuint vNormal = glGetAttribLocation( program, "vNormal" ); 
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(sizeof(points)) );

    // Initialize shader lighting parameters
    point4 light_position( -2.0, 0.0, 0.0, 1.0 );
	
    color4 light_ambient( 0.2, 0.2, 0.2, 1.0 ); // L_a
    color4 light_diffuse( 1.0, 1.0, 1.0, 1.0 ); // L_d
    color4 light_specular( 1.0, 1.0, 1.0, 1.0 ); // L_s

    color4 material_ambient( 1.0, 0.0, 1.0, 1.0 ); // k_a
    color4 material_diffuse( 1.0, 0.8, 0.0, 1.0 ); // k_d
    color4 material_specular( 1.0, 0.8, 0.0, 1.0 ); // k_s
    float  material_shininess = 100.0;

    color4 ambient_product = light_ambient * material_ambient; // k_a * L_a
    color4 diffuse_product = light_diffuse * material_diffuse; // k_d * L_d
    color4 specular_product = light_specular * material_specular; // k_s * L_s
    glUniform4fv( glGetUniformLocation(program, "AmbientProduct"),
		  1, ambient_product );
    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct"),
		  1, diffuse_product );
    glUniform4fv( glGetUniformLocation(program, "SpecularProduct"),
		  1, specular_product );
	
    glUniform4fv( glGetUniformLocation(program, "LightPosition"),
		  1, light_position );

    glUniform1f( glGetUniformLocation(program, "Shininess"),
		 material_shininess );
		 
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );

    glEnable( GL_DEPTH_TEST );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}
//----------------------------------------------------------------------------










void
init()
{

	//getchar();
	loadOff("vertextriangles.txt");
	//getchar();
	cout << "ended load off" << endl;
	populatePoints();
	cout << "ended pop points" << endl;
	//getchar();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//readPPM();

	//getchar();
	//getchar();
	// Create and initialize a buffer object



	cout << "beg of buffer" << endl;
	//getchar();

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, numtriangles*3*16*2+numtriangles*3*12,
		NULL, GL_STATIC_DRAW);
	cout << numtriangles*3*16 <<"  " <<numvertices << "  " <<numtriangles << endl;
	


	glBufferSubData(GL_ARRAY_BUFFER, 0, numtriangles * 3 * 16, pts); 
	glBufferSubData(GL_ARRAY_BUFFER, numtriangles*3*16,
		numtriangles*3*16, colors);
	glBufferSubData(GL_ARRAY_BUFFER, numtriangles * 3 * 16*2,
		numtriangles*3 * 12, normals);




/*

	glBufferSubData(GL_ARRAY_BUFFER, numtriangles * 3 * 16+
		numtriangles * 3 * 12, sizeof(tex_coords),tex_coords);
	*/

	//glBufferSubData(GL_ARRAY_BUFFER, numtriangles * 3 * 16 +
	//	numtriangles * 3 * 12 +2048 * 2048 * 16, numtriangles*3*8,tex_coords);
	
	// Load shaders and use the resulting shader program
	//getchar();
	cout << "beg of shaders" << endl;
	
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
	cout << "ended shader" << endl;
//getchar();

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(numtriangles*16*3));


	//getchar();

	//getchar();

	//getchar();


	/*



	int k, n, m;
	char c, b[100];
	FILE *fd = fopen("texture.ppm", "r");
	fscanf(fd, "%[^\n] ", b);
	fscanf(fd, "%c", &c);
	while (c == '#') {
		fscanf(fd, "%[^\n] ", b);
		fscanf(fd, "%c", &c);
	}
	ungetc(c, fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);
	GLubyte *imagem = (GLubyte *)malloc(3 * sizeof(GLubyte) * n * m);
	int red, green, blue;
	for (unsigned int i = n * m; i > 0; i--) {
		fscanf(fd, "%d %d %d", &red, &green, &blue);
		imagem[3 * n * m - 3 * i] = red;
		imagem[3 * n * m - 3 * i + 1] = green;
		imagem[3 * n * m - 3 * i + 2] = blue;
	}
	GLuint textures[1];
	glGenTextures(1, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_BYTE, imagem);



	*/






	/*


	glGenTextures(1, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR); //try here different alternatives
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //try here different alternatives

	

//getchar();



*/
	menuHandler = new MenuHandler();
	menuHandler->setGlobalMenuHandler(menuHandler);
	menuHandler->setProgram(program);
	menuHandler->globalPts = pts;
	menuHandler->defaultPts = pts;
	menuHandler->defaultVertices = mvertices;
	menuHandler->globalVertices = new point4[numvertices];
	int m = 0;
	for (m = 0; m < numvertices; m++) {
		menuHandler->globalVertices[m] = mvertices[m];
	}
	menuHandler->globalNumVertices = numvertices;
	menuHandler->globalNumTriangles = numtriangles;
	menuHandler->defaultTriangles = triangles;

	cout << "ended  of menuhndler" << endl;
	//getchar();


	setProjections();
	cout << "end  of setproj" << endl;
	//getchar();
	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));


	
	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(numtriangles*16*3*2));

	

	//GLuint vColor = glGetAttribLocation(program, "vColor");
	//glEnableVertexAttribArray(vColor);
	//glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
	//	BUFFER_OFFSET(numtriangles*16*3+numtriangles*3*12));

	/*
	GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(numtriangles*16*3+numtriangles*3*12));
	*/

	

	// Initialize shader lighting parameters
	point4 light_position(-2.0, 0.0, 0.0, 1.0);
	/*
	point4 light2_position(0.0, 0.0, 2.0, 1.0);*/
	color4 light_ambient(0.2, 0.2, 0.2, 1.0); // L_a
	color4 light_diffuse(1.0, 1.0, 1.0, 1.0); // L_d
	color4 light_specular(1.0, 1.0, 1.0, 1.0); // L_s

	color4 material_ambient(1.0, 0.0, 1.0, 1.0); // k_a
	color4 material_diffuse(1.0, 0.8, 0.0, 1.0); // k_d
	color4 material_specular(1.0, 0.8, 0.0, 1.0); // k_s
	
	float  material_shininess = 100.0;


	color4 ambient_product = light_ambient * material_ambient; // k_a * L_a
	color4 diffuse_product = light_diffuse * material_diffuse; // k_d * L_d
	color4 specular_product = light_specular * material_specular; // k_s * L_s
	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"),
		1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"),
		1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"),
		1, specular_product);

	glUniform4fv(glGetUniformLocation(program, "LightPosition"),
		1, light_position);

	glUniform1f(glGetUniformLocation(program, "Shininess"),
		material_shininess);

	// Retrieve transformation uniform variable locations
	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");
	
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
}

//----------------------------------------------------------------------------





void
display( void )
{
    
	cout << "in display" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glBufferSubData(GL_ARRAY_BUFFER, 0, numtriangles * 3 * 16, menuHandler->globalPts);

    //  Generate tha model-view matrixn

    const vec3 viewer_pos( 0.0, 0.0, 3.0 );
    mat4  model_view = (Translate( -viewer_pos ) *
			 Scale( scale )*
			 Scale( scale )*
			 Scale( scale )*
		RotateX(Theta[Xaxis])*
		RotateY(Theta[Yaxis])*
		RotateZ(Theta[Zaxis]));

	menuHandler->defaultModelView = model_view;
    
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );

    glDrawArrays( GL_TRIANGLES, 0, numtriangles*3 );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) {
	switch( button ) {
	    case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
	    case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
	    //case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
	}
    }
}

//----------------------------------------------------------------------------

void
idle( void )
{
    Theta[Axis] += 0.01;

    if ( Theta[Axis] > 360.0 ) {
	Theta[Axis] -= 360.0;
    }
    
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
	GLuint mshading;
    switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
	case 'z':
		scale += 0.1;
		glutPostRedisplay();
		break;
	case 'i':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		menuHandler->shading = 0.0;
		mshading = glGetUniformLocation(mprogram, "Shading");
		glUniform1f(mshading, menuHandler->shading);
		glutPostRedisplay();
		break;
	case 'Z':
		scale -= 0.1;
		glutPostRedisplay();
		break;
	case 'h':
		std::cout << "Welcome" << endl;
		std::cout << "------HELP------" << endl;
		std::cout << "i : You can restart by typing i" << endl;
		std::cout << "h : You can type h to access help" << endl;
		std::cout << "q : You can exit by typing q" << endl;
		std::cout << "You can rotate by arrow keys" << endl;
		std::cout << "You can zoom in and out by z and Z" << endl;
		std::cout << "You can use menu by clicking right button of the mouse" << endl;
		std::cout << "You can also select corresponding menu items and display it differently" << endl;
		break;

    }
}



void keyboardplusplus(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:

		Theta[Xaxis] -= 10;
		glutPostRedisplay();
		//speed++;
		//rot_speed += 0.1;
		//scale_rh += 0.001;
		break;
	case GLUT_KEY_DOWN:
		Theta[Xaxis] += 10;

		glutPostRedisplay();

		//if (speed != 0) {
		//rot_speed -= 0.1;
		//speed--;
		//}
		break;
	case GLUT_KEY_RIGHT:

		Theta[Yaxis] += 2;

		glutPostRedisplay();

		//if (speed != 0) {
		//rot_speed -= 0.1;
		//speed--;
		//}
		break;
	case GLUT_KEY_LEFT:
		Theta[Yaxis] -= 2;


		glutPostRedisplay();
		//if (speed != 0) {
		//rot_speed -= 0.1;
		//speed--;
		//}
		break;
	}
}


//----------------------------------------------------------------------------

void
reshape( int width, int height )
{

	cout << "in reshape" << endl;
    glViewport( 0, 0, width, height );
	w = width;
	h = height;
	setProjections();
    GLfloat aspect = GLfloat(width)/height;
    mat4  projection = Perspective( 45.0, aspect, 0.5, 6.0 );

	cout << mvertices[12].x << mvertices[12].y << mvertices[12].z << "vertices 12" << endl;

   glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 800, 800 );
    glutCreateWindow( "etuna - Facial Animation" );

	glewInit();
	glewExperimental = GL_TRUE;

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    glutMouseFunc( mouse );
    //glutIdleFunc( idle );

	glutSpecialFunc(keyboardplusplus);

    glutMainLoop();
    return 0;
}


void setupLoad(std::string filename) {

}

vec3* loadOff(std::string filename) {

	int i, num_vertices, num_triangles;
	

	file = fstream(filename);
	if (!file.is_open()) {
		return false;
	}

	file >> num_vertices;

	numvertices = num_vertices;


	mvertices = new point4[numvertices];
	

	
	for (i = 0; i < num_vertices; i++) {
		GLfloat temp1, temp2, temp3;
		file >> mvertices[i][v1] >> mvertices[i][v2] >>mvertices[i][v3];
		//cout << mpoints[i][v1] << mpoints[i][v2] << mpoints[i][v3] << endl;


		/*
		
		if (i == 7) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.086957;
			mvertices[i][v3] += 0.021739;

		}
		else if (i == 33) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.065217;
			mvertices[i][v3] += 0.021739;
		}
		else if (i == 66) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.065217;
			mvertices[i][v3] += 0.021739;
		}
		else if (i == 79) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.05;
			mvertices[i][v3] += 0.021739;
		}
		else if (i == 80) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.05;
			mvertices[i][v3] += 0.021739;
		}
		else if (i == 81) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.05;
			mvertices[i][v3] += 0.021739;
		}
		else if (i == 82) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.05;
			mvertices[i][v3] += 0.021739;
		}
		else if (i == 87) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.065217;
			mvertices[i][v3] += 0.021739;
		}
		else if (i == 88) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0200;
			mvertices[i][v3] += 0;
		}
		else if (i == 89) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0200;
			mvertices[i][v3] += 0;
		}
		*/





		/*

		if (i == 21) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += -0.062000;
			mvertices[i][v3] += 0.01;

		}
		else if (i == 22) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0200;
			mvertices[i][v3] += 0.01;
		}
		else if (i == 54) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += -0.0620;
			mvertices[i][v3] += 0.01;
		}
		else if (i == 55) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0200;
			mvertices[i][v3] += 0.01;
		}
		else if (i == 97) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += -0.04500;
			mvertices[i][v3] += 0.007;
		}
		else if (i == 98) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += -0.04500;
			mvertices[i][v3] += 0.0070;
		}
		else if (i == 99) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0150;
			mvertices[i][v3] += 0.007000;
		}
		else if (i == 100) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0150;
			mvertices[i][v3] += 0.007000;
		}
		else if (i == 105) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += -0.04500;
			mvertices[i][v3] += 0.007000;
		}
		else if (i == 106) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += -0.04500;
			mvertices[i][v3] += 0.007000;
		}
		else if (i == 107) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0150;
			mvertices[i][v3] += 0.007000;
		}
		else if (i == 108) {
			mvertices[i][v1] += 0;
			mvertices[i][v2] += 0.0150;
			mvertices[i][v3] += 0.007000;
		}


//Outer brow raiser
if (i == 15) {
	mvertices[i][v1] += 0.021739;
	mvertices[i][v2] += 0.173913;
	mvertices[i][v3] += -0.021739;

}
else if (i == 16) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.152174;
	mvertices[i][v3] += -0.021739;
}
else if (i == 17) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.021739;
	mvertices[i][v3] += 0;
}
else if (i == 18) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.152174;
	mvertices[i][v3] += -0.021739;
}
else if (i == 48) {
	mvertices[i][v1] += -0.021739;
	mvertices[i][v2] += 0.173913;
	mvertices[i][v3] += -0.021739;
}
else if (i == 49) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.152174;
	mvertices[i][v3] += -0.021739;
}
else if (i == 50) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.021739;
	mvertices[i][v3] += 0;
}
else if (i == 51) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.152174;
	mvertices[i][v3] += -0.021739;
}







//Upper lid raiser
if (i == 21) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.030;
	mvertices[i][v3] += -0.0100;

}
else if (i == 54) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.030;
	mvertices[i][v3] += -0.0100;
}
else if (i == 97) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.015;
	mvertices[i][v3] += -0.00700;
}
else if (i == 98) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.015;
	mvertices[i][v3] += -0.00700;
}
else if (i == 105) {
	mvertices[i][v1] +=0;
	mvertices[i][v2] += 0.015;
	mvertices[i][v3] += -0.00700;
}
else if (i == 106) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.015;
	mvertices[i][v3] += -0.00700;
}


/*

//Raise r i eyebrow
if (i == 48) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.1;
	mvertices[i][v3] += 0;
}

if (i == 49) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.1;
	mvertices[i][v3] += 0;
}
if (i == 50) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.1;
	mvertices[i][v3] += 0;
}
if (i == 51) {
	mvertices[i][v1] += 0;
	mvertices[i][v2] += 0.1;
	mvertices[i][v3] += 0;
}


*/


/*
//Chin with
if (i == 30) {
	mvertices[i][v1] += 0.00;
	mvertices[i][v2] += 0;
	mvertices[i][v3] += 0;
}
else if (i == 63) {
	mvertices[i][v1] += -0.01;
	mvertices[i][v2] += 0;
	mvertices[i][v3] += -0;
}
*/

















		


	}


	file >> num_triangles;
	numtriangles = num_triangles;
triangles = new vec3[numtriangles];
	for (i = 0; i < num_triangles; i++)
	{
		GLfloat tempa, temp2, temp3, temp4;
		file >> triangles[i][v1] >> triangles[i][v2] >> triangles[i][v3];
		//cout << tempa << endl;
	}

	
	
	file.close();
	return triangles;
	

}



void setProjections() {
	GLfloat aspect = GLfloat(w) / h;
	mat4  projectionpers = Perspective(45.0, aspect, 0.5, 6.0);

	mat4 projectionortho = Ortho(-1.0 * h / w, 1.0 * h / w, -1.0, 1.0, -1.0, 1.0);

	menuHandler->projectionpers = projectionpers;
	menuHandler->projectionortho = projectionortho;

}








void
populatePoints() {
	int i,index = 0;
	point4 temp1,temp2,temp3,temp4;
	//vec3 nor1,nor2,nor3;
	//vec2 cord1, cord2, cord3;
	pts = new point4[numtriangles * 3];
	//nors = new vec3[numtriangles * 3];
	for (i = 0; i < numtriangles; i++) {
		temp1.x = mvertices[unsigned int(triangles[i][v1])].x;
		temp1.y = mvertices[unsigned int(triangles[i][v1])].y;
		temp1.z = mvertices[unsigned int(triangles[i][v1])].z;
		temp1.w = 1.0;

		temp2.x = mvertices[unsigned int(triangles[i][v2])].x;
		temp2.y = mvertices[unsigned int(triangles[i][v2])].y;
		temp2.z = mvertices[unsigned int(triangles[i][v2])].z;
		temp2.w = 1.0;

		temp3.x = mvertices[unsigned int(triangles[i][v3])].x;
		temp3.y = mvertices[unsigned int(triangles[i][v3])].y;
		temp3.z = mvertices[unsigned int(triangles[i][v3])].z;
		temp3.w = 1.0;

		pts[3 * i] = normalize(temp1);
		pts[(3 * i)+1] = normalize(temp2);
		pts[(3 * i)+2] = normalize(temp3);

		colors[3 * i] = vertex_colors[(3 * i )% 8];
		colors[(3 * i)+1] = vertex_colors[(3 * i + 1) % 8];
		colors[(3 * i)+2] = vertex_colors[(3 * i + 2) % 8];

		


		normals[3*i].x = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).x;
		normals[3*i].y = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).y;
		normals[3*i].z = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).z;

		normals[(3 * i)+1].x = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).x;
		normals[(3 * i) + 1].y = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).y;
		normals[(3 * i) + 1].z = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).z;

		normals[(3 * i) + 1].x = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).x;
		normals[(3 * i) + 2].y = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).y;
		normals[(3 * i) + 3].z = (-1*(mvertices[unsigned int(triangles[i][v1])] - mvertices[unsigned int(triangles[i][v2])])*(mvertices[unsigned int(triangles[i][v3])] - mvertices[unsigned int(triangles[i][v2])])).z;





		/*
		cord1 = vt_cords[unsigned int(triangles[i][v1])];
		cord2 = vt_cords[unsigned int(triangles[i][v2])];
		cord3 = vt_cords[unsigned int(triangles[i][v3])];

		tex_coords[3 * i] = cord1;
		tex_coords[(3 * i) + 1] = cord2;
		tex_coords[(3 * i) + 2] = cord3;




		nor1.x = mnormals[unsigned int(triangles[i][v1])].x;
		nor1.y = mnormals[unsigned int(triangles[i][v1])].y;
		nor1.z = mnormals[unsigned int(triangles[i][v1])].z;
		

		nor2.x = mnormals[unsigned int(triangles[i][v2])].x;
		nor2.y = mnormals[unsigned int(triangles[i][v2])].y;
		nor2.z = mnormals[unsigned int(triangles[i][v2])].z;
		

		nor3.x = mnormals[unsigned int(triangles[i][v3])].x;
		nor3.y = mnormals[unsigned int(triangles[i][v3])].y;
		nor3.z = mnormals[unsigned int(triangles[i][v3])].z;
		

		nors[3 * i] = normalize(nor1);
		nors[(3 * i) + 1] = normalize(nor2);
		nors[(3 * i) + 2] = normalize(nor3);



		*/

		}	
	}



/*

vec3 *readPPM(){
		string p3_word;
		int width, height,max_level;

		file = fstream("texture.ppm");
		if (!file.is_open()) {
			return false;
		}
	
		file >> p3_word;
		cout << p3_word << endl;

		char comment[400];
		string temp0, temp1, temp2, temp3, temp4, temp5, temp6;
		//file.getline(comment, 400);
		file >> temp0 >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6;
		cout << temp0 << temp1 << temp6 << endl;

		file >> width >> height >> max_level;

		//cout << width << " " << height << " " << max_level << endl;


		GLuint nm = width * height;
		//GLuint image[2048*2048][4];

		int red, green, blue;

		int i = 0;
		int k = 0;

		for (i = 0; i < width; i++) {
			for (k = 0; k < height; k++) {

			file >> red >> green >> blue;
			image[i][k][0] = red;
			image[i][k][1] = green;
			image[i][k][2] = blue;
			//cout << "ilk forda" << image[i][k][0] << image[i][k][1] << image[i][k][2] << i << k << endl;
			}

			//getchar();

		}

		//tex_colors = new color4[2048*2048];

		for (i = 0; i < width; i++) {
			for (k = 0; k < height; k++) {
				//cout << "geldi" << endl;
				//getchar();
				//color4 mvec(GLfloat (image[i][k][0])/256.0, GLfloat(image[i][k][1])/256.0, GLfloat(image[i][k][2])/256.0, 1.0);
				//getchar();
				//tex_colors[i*2048+k] = mvec;

			}
			//getchar();
			//cout << "ikinci forda" << endl;
		}

		//tex_coords = new vec2[2048*2048];
		for (i = 0; i < width; i++) {

			for (k = 0; k < height; k++) {
				//vec2 vec(i, k);
				//tex_coords[2048 * i + k] = vec;
			}
			
			//cout << "ucuncu forda" << endl;
		}

	

	
	//cout << "geldi" << endl;
	file.close();

}
*/