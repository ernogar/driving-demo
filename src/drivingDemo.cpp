#include "Utilidades.h"
#include <sstream>

float alpha = 32.0; 
float velocidad = 0.0;
float posX = 0.0;
float posZ = 0.0;
bool panelOn = false;

GLuint mitex1;
GLuint mitex2;
GLuint mitex3;
GLuint mitex4;
GLuint mitex5;

void ruta(float z)
{
	glBegin(GL_QUAD_STRIP);
		float x = 5*sin(z*PI/25);
		for(int i = 0; i<50; i++){
			GLfloat v0[] = {x-2,0.0,z};
			GLfloat v1[] = {x+2,0.0,z};
			z+=1;
			x = 5*sin(z*PI/25);
			GLfloat v2[] = {x+2,0.0,z};
			GLfloat v3[] = {x-2,0.0,z};
			quad(v0,v1,v2,v3,30,30);
		}
	glEnd();
}
void fondo()
{
	glPushMatrix();
		glTranslatef(posX,1,posZ);
		float a=deg(2*PI/10);
		float aux = 0;
		for(int i = 1; i<=10; i++){
			glBegin(GL_QUAD_STRIP);	
				glTexCoord2f(aux,0);
				glVertex3f(0,-170,-100);
				glTexCoord2f(aux,1);
				glVertex3f(0,190,-100);
				aux = (a/360)*i;
				glTexCoord2f(aux,0);
				glVertex3f(-(sin(rad(a))*100),-170,-(cos(rad(a))*100));
				glTexCoord2f(aux,1);
				glVertex3f(-(sin(rad(a))*100),190,-(cos(rad(a))*100));
			glEnd();
			glRotatef(a,0,1,0);
		}

	glPopMatrix();
}
void cartel()
{
	int z = (int)(posZ)/20 * 20;
	z+=20;
	float x = 5*sin(z*PI/25);
		glBegin(GL_QUAD_STRIP);	
			glVertex3f(x+2,0,z);
			glVertex3f(x+2,2,z);
			glVertex3f(x+1.5,0,z);
			glVertex3f(x+1.5,2,z);
		glEnd();
		glBegin(GL_QUAD_STRIP);	
				glTexCoord2f(0,0);
				glVertex3f(x+2,2,z);
				glTexCoord2f(0,1);
				glVertex3f(x+2,4,z);
				glTexCoord2f(1,0);
				glVertex3f(x-2,2,z);
				glTexCoord2f(1,1);
				glVertex3f(x-2,4,z);
		glEnd();
		glBegin(GL_QUAD_STRIP);	
			glVertex3f(x-2,0,z);
			glVertex3f(x-2,2,z);
			glVertex3f(x-1.5,0,z);
			glVertex3f(x-1.5,2,z);
		glEnd();
}
void luces()
{
	int z = (int)posZ/10 * 10;
	float x = 5*sin(z*PI/25);
	GLfloat posicionLampara1[]= {x,4.0,z, 1.0};
	glLightfv(GL_LIGHT2, GL_POSITION, posicionLampara1);
	z+=10;
	x = 5*sin(z*PI/25);
	GLfloat posicionLampara2[]= {x,4.0,z, 1.0};
	glLightfv(GL_LIGHT3, GL_POSITION, posicionLampara2);
	z+=10;
	x = 5*sin(z*PI/25);
	GLfloat posicionLampara3[]= {x,4.0,z, 1.0};
	glLightfv(GL_LIGHT4, GL_POSITION, posicionLampara3);
	z+=10;
	x = 5*sin(z*PI/25);
	GLfloat posicionLampara4[]= {x,4.0,z, 1.0};
	glLightfv(GL_LIGHT5, GL_POSITION, posicionLampara4);
}
void panel()
{
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glPushMatrix();
		glTranslatef(posX,1,posZ);
		glRotatef(alpha,0,1,0);
		glColor4f(0.3,0.8,0.3,0.8);
		glBegin(GL_QUAD_STRIP);
			for(int i = 0; i<=velocidad; i++){
				glVertex3f(0.8,-0.5+0.1*i,0.5);
				glVertex3f(0.5,-0.5+0.1*i,0.5);
				glVertex3f(0.8,-0.5+0.1*(i+1),0.5);
				glVertex3f(0.5,-0.5+0.1*(i+1),0.5);
			}
		glEnd();
		glTranslatef(-0.8,-0.3,0);
		glRotatef(alpha,0,0,1);
		glColor4f(0.8,0.0,0.3,0.8);
		glBegin(GL_TRIANGLE_STRIP);	
				glVertex3f(0.2,0.2,0.5);
				glVertex3f(-0.2,0.2,0.5);
				glVertex3f(0,0.4,0.5);
		glEnd();
		glBegin(GL_QUAD_STRIP);
				glVertex3f(0.1,-0.2,0.5);
				glVertex3f(-0.1,-0.2,0.5);
				glVertex3f(0.1,0.2,0.5);
				glVertex3f(-0.1,0.2,0.5);
			
		glEnd();
		glColor4f(1,1,1,0);
	glPopMatrix();
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
}
void capot()
{
	glPushMatrix();
		glTranslatef(posX,1,posZ);
		glRotatef(alpha,0,1,0);
		glBegin(GL_QUAD_STRIP);
				glTexCoord2f(1,1);
				glVertex3f(-0.5,-0.25,0);
				glTexCoord2f(0,1);
				glVertex3f(0.5,-0.25,0);
				glTexCoord2f(1,0);
				glVertex3f(-0.5,-0.5,0.5);
				glTexCoord2f(0,0);
				glVertex3f(0.5,-0.5,0.5);
		glEnd();
	glPopMatrix();
}
void piso()
{
	double z = posZ/50;
	double x = posX/50;
	glPushMatrix();
		glBegin(GL_QUAD_STRIP);
			glTexCoord2f(x+0,z+0);
			glVertex3f(posX-50,-0.01,posZ-50);
			glTexCoord2f(x+2,z+0);
			glVertex3f(posX+50,-0.01,posZ-50);
			glTexCoord2f(x+0,z+2);
			glVertex3f(posX-50,-0.01,posZ+50);
			glTexCoord2f(x+2,z+2);
			glVertex3f(posX+50,-0.01,posZ+50);
		glEnd();
	glPopMatrix();
}
void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);

	glClearColor(0,0,0,1);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	
	GLfloat A10[]={0.01,0.01,0.01,1.0};	// Color ambiental de la luz
	GLfloat D10[]={0.01,0.01,0.01,1.0};	// Color difuso de la luz    
	GLfloat S10[]={0.0,0.0,0.0,1.0};	// Color especular de la luz
	glLightfv(GL_LIGHT0, GL_AMBIENT, A10);	// Caracteristicas de LIGHT0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, D10);	
	glLightfv(GL_LIGHT0, GL_SPECULAR, S10);
	GLfloat posicionLuna[]={0,10,0,0};
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuna);

	GLfloat A20[]={1.0,1.0,1.0,1.0};	
	GLfloat D20[]={0.2,0.2,0.2,1.0};
	GLfloat S20[]={0.3,0.3,0.3,1.0};
	GLfloat posicionFaro[]={0, 0.7, 0, 1.0};
	GLfloat dir_centralFaro[]={0,-1.3, -0.7};
	glLightfv(GL_LIGHT1, GL_AMBIENT, A20);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, D20);	
	glLightfv(GL_LIGHT1, GL_SPECULAR, S20);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
	glLightfv(GL_LIGHT1, GL_POSITION, posicionFaro);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir_centralFaro);

	GLfloat A30[]={0.5,0.5,0.2,1.0};
	GLfloat D30[]={0.0,0.0,0.0,1.0};
	GLfloat S30[]={0.0,0.0,0.0,1.0};
	GLfloat dir_centralLampara[]= {0.0,-1.0, 0.0};
	glLightfv(GL_LIGHT2, GL_AMBIENT, A30);	
	glLightfv(GL_LIGHT2, GL_DIFFUSE, D30);	
	glLightfv(GL_LIGHT2, GL_SPECULAR, S30);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,dir_centralLampara);
	glLightfv(GL_LIGHT3, GL_AMBIENT, A30);	
	glLightfv(GL_LIGHT3, GL_DIFFUSE, D30);	
	glLightfv(GL_LIGHT3, GL_SPECULAR, S30);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,dir_centralLampara);
	glLightfv(GL_LIGHT4, GL_AMBIENT, A30);	
	glLightfv(GL_LIGHT4, GL_DIFFUSE, D30);	
	glLightfv(GL_LIGHT4, GL_SPECULAR, S30);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,dir_centralLampara);
	glLightfv(GL_LIGHT5, GL_AMBIENT, A30);	
	glLightfv(GL_LIGHT5, GL_DIFFUSE, D30);	
	glLightfv(GL_LIGHT5, GL_SPECULAR, S30);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,dir_centralLampara);

	glGenTextures(1,&mitex1);
	glGenTextures(1,&mitex2);
	glGenTextures(1,&mitex3);
	glGenTextures(1,&mitex4);
	glGenTextures(1,&mitex5);

	glBindTexture(GL_TEXTURE_2D, mitex1);
	loadImageFile("texturas/carretera.jpg");
	glBindTexture(GL_TEXTURE_2D, mitex2);
	loadImageFile("texturas/cocacola.jpg");
	glBindTexture(GL_TEXTURE_2D, mitex3);
	loadImageFile("texturas/desierto.jpg");
	glBindTexture(GL_TEXTURE_2D, mitex4);
	loadImageFile("texturas/capot.jpg");
	glBindTexture(GL_TEXTURE_2D, mitex5);
	loadImageFile("texturas/arena.jpg");

	GLfloat fog[]   = {0.5,0.3,0,1};
	glFogfv(GL_FOG_COLOR, fog);
	glFogf(GL_FOG_DENSITY, 0.3);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	gluLookAt(posX,1,posZ, 
		  posX+sin(rad(alpha)),1,posZ+cos(rad(alpha)),  
		  0,1,0); 
	
	GLfloat Dm[]= {0.8,0.8,0.8,1.0};
	GLfloat Sm[]= {0.3,0.3,0.3,1.0};
	GLfloat Am[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat Em[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat s = 3.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Em);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Am);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Dm);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Sm);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, s);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mitex1);
	ruta(floor(posZ)-5);

	GLfloat Amc[] = {0.35, 0.35, 0.35, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Amc);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mitex2);
	cartel();

	s = 5.0;
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, s);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mitex4);
	capot();

	GLfloat Dmp[]= {0.8,0.8,0.8,1.0};
	GLfloat Smp[]= {0.3,0.3,0.3,1.0};
	GLfloat Amp[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat Emp[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat sp = 3.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Emp);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Amp);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Dmp);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Smp);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sp);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mitex5);
	piso();

	GLfloat Dmf[]= {0.0,0.0,0.0,1.0};
	GLfloat Smf[]= {0.0,0.0,0.0,1.0};
	GLfloat Amf[] = {0.06, 0.06, 0.06, 1.0};
	GLfloat Emf[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat sf = 0.0;
	glMaterialfv(GL_FRONT, GL_EMISSION, Emf);
	glMaterialfv(GL_FRONT,GL_AMBIENT,Amf);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Dmf);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Smf);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sf);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, mitex3);
	fondo();

	luces();

	if(panelOn){ panel(); }

	glutSwapBuffers();
}
void reshape(GLint w, GLint h)
{
		glViewport(0,0,w,h);
		float razon = (float)w/h;		
		//configuro la camara
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( /*fovy*/120,
						/*razon*/razon,
						/*cerca*/0.1,
						/*lejos*/100);
}
void update()
{
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	//Calcular el tiempo transcurrido:
	float tiempo = (hora_actual - hora_anterior) / (float)1000;

	float distancia = velocidad * tiempo;
	posX += sin(rad(alpha))*distancia;
	posZ += cos(rad(alpha))*distancia;

	hora_anterior = hora_actual;
	glutPostRedisplay();
}
void onSpecialKey(int specialKey, int x, int y)
{
	stringstream titulo;
	switch(specialKey){
		case GLUT_KEY_LEFT:
			alpha += 2;
			break;
		case GLUT_KEY_RIGHT:
			alpha -= 2;
			break;
		case GLUT_KEY_UP:
			if(velocidad < 12){ 
				velocidad += 0.1;
				titulo << "Speed = " << velocidad << "m/sg";
				glutSetWindowTitle(titulo.str().c_str());
			}
			break;
		case GLUT_KEY_DOWN:
			if(velocidad > 0){ 
				velocidad -= 0.1;
				titulo << "Speed = " << velocidad << "m/sg";
				glutSetWindowTitle(titulo.str().c_str());
			}
			break;
	}
}
void onKey(unsigned char tecla, int x, int y)
{
	static bool luzOn = false;
	static bool nieOn = false;
	static bool wireOn = false;
	switch(tecla){
		case 'l':
		case 'L':
			if(luzOn){
				glDisable(GL_LIGHTING);
				luzOn = false;
			}
			else{
				glEnable(GL_LIGHTING);
				luzOn = true;
			}
			break;
		case 'n':
		case 'N':
			if(nieOn){
				glDisable(GL_FOG);
				nieOn = false;
			}
			else{
				glEnable(GL_FOG);
				nieOn = true;
			}
			break;
		case 's':
		case 'S':
			if(wireOn){
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				wireOn = false;
			}
			else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				wireOn = true;
			}
			break;
		case 'c':
		case 'C':
			if(panelOn)
				panelOn = false;
			else
				panelOn = true;
			break;	
		case 27:
			exit(0);
			break;

	}
}
void main(int argc, char** argv)
{
	FreeImage_Initialise();
	 glutInit(&argc, argv);

	 glutInitWindowSize(900,600);
	 glutInitWindowPosition(50, 100); 
	 glutCreateWindow("Car on road");
	
	 cout << "" << endl;
	 cout << "DEMO :: Car on road :: \n" << endl;
	 cout << "left/right: Turn the car" << endl;
	 cout << "up/down: Increase/decrease speed" << endl;
	 cout << "S/s: Enable Alambric model" << endl;
	 cout << "L/l: Enable Lights" << endl;
	 cout << "N/n: Enable Fog" << endl;
	 cout << "C/c: Enable Display" << endl;
	 cout << "ESC: Exit" << endl;

	 glutInitDisplayMode(GL_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	 
	 init();

	 glutDisplayFunc(display);
	 glutReshapeFunc(reshape);
	 glutIdleFunc(update);
	 glutSpecialFunc(onSpecialKey);
	 glutKeyboardFunc(onKey);
	 
	 glutMainLoop();
	FreeImage_DeInitialise();
}