#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<time.h>
#include "imageloader.h"
#include "imageloader.cpp"
#include "glm.h"
#include "glm.cpp"
#include "text3d.h"
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void update(int value);
void falln(int val);
int collision();
int chckfall(float,float,float);
void handlejump(int);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void drawcube(float,int,GLuint);
void computeorigco();
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void helicopter(int x,int y);
// Global Variables
int windowWidth ;
float eps=0.000001;
int windowHeight;
int width;
int height;
float ball_rad = 0.1f;
float storex,storez;
//tiles
int flag=0;
float yco=0;
float xt=0,xt1=0.8;
int chk1=0,chk2=0;
float tiles[30][4];//store tile co-ordinate for moving or missing tiles. 4th column tells tile type
float k=0;
int chk=0;
int num=0;
float firex,firez;
int fall=0;
float tilesidex;
float tileupx=0,tileupz=0;
//variables for robot
int jump=0;
int jmp=0;
int nmoving=1;
int g=0;
float theta = 0.0f; 
float xco=0,zco=0;
int pindx=-1,indx=-1;
int fallfrmup=0;
GLMmodel *mod=NULL;
GLMmodel *mod1=NULL;
GLMmodel *mod2=NULL;
float intr=0;
float origx=-1.8,origy=0.1,origz=-0.6;
int fallfrmside=0;
int roboup=0;
int dead=0;
//camera variables
float camx=0,camy=0,camz=0;
int fps=0;
int tps=0;
int tileview=0;
float tilex=-1.6,tiley=0,tilez=-0.4;
float camxi=-1.8,camyi=0.22,camzi=-5.6;
float lookx,looky,lookz;
float camyt=1;
float add=2;
int hview=0;
//mouse
float cmxi=0,cmyi=3,cmzi=-7.4;
float cmx=cmxi,cmy=cmyi,cmz=cmzi;
GLdouble mposx, mposy, mposz;
//GLMmodel *robot = NULL;
//coin
float coin[4][3];
int no=0;
int finish=0;
float theta1=0;
//Computes a scaling value so that the strings
/*float computeScale(const char* strs[1]) {
	float maxWidth = 0; 
	//      for(int i = 0; i < 4; i++) {
	float width1 = t3dDrawWidth(strs[1]);
	if (width1 > maxWidth) {
		maxWidth = width1;
	}         
	printf("seg fault\n");
	return 3.0f / maxWidth;
}

float _angle = 0.0f;
float _scale;*/
//The four strings that are drawn
const char* STRS[1] = {"G ame Over!\nCongrats you win"};

void cleanup() {
	t3dCleanup();
}
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLfloat UpwardsScrollVelocity = -20.0;
float view=20.0;

char quote[6][80];
int numberOfQuotes=0,i;

void timeTick(void)
{
	if (UpwardsScrollVelocity< -600)
		view-=0.000011;
	if(view < 0) {view=30; UpwardsScrollVelocity = -10.0;}
	//  exit(0);
	UpwardsScrollVelocity -= 0.2;
	glutPostRedisplay();

}
void RenderToDisplay()
{
	int l,lenghOfQuote, i;

	glPushMatrix();
	glTranslatef(0.0, -50, UpwardsScrollVelocity);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.08, 0.08, 0.08);



	for(  l=0;l<numberOfQuotes;l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote*37), -(l*200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{    
			glColor3f((UpwardsScrollVelocity/5)+300+(l*10),(UpwardsScrollVelocity/5)+300+(l*10),0.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
		}
		glPopMatrix();
	}
	glPopMatrix();
}


GLuint _textureId; //The id of the texture
GLuint _textureId1; //The id of the texture
GLuint _textureId2; //The id of the texture
GLuint _textureId3; //The id of the texture


int main(int argc, char **argv) {

	strcpy(quote[0],"You are sent on Earth for some special purpose :P");
	strcpy(quote[1],"You will meet John Corner.");
	strcpy(quote[2],"Journey may be difficult. Be BRAVE. ");

	 numberOfQuotes=3;
	 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	 windowWidth = w * 2 / 3;
	 windowHeight = h * 2 / 3;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
	printf("window..(%d,%d)\n",windowWidth,windowHeight);
	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();
	//_scale=computeScale(STRS);
	int hell;
	for(hell=0;hell<4;hell++)
	{
		coin[hell][0]=0;
		coin[hell][1]=0;
		coin[hell][2]=0;
	}

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(timeTick);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(helicopter);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	glutTimerFunc(10, falln,0);
	glutTimerFunc(10,handlejump,0);
	glutMainLoop();
	return 0;
}
void drawBall(float rad) {

	glRotatef(theta1,0,1,0);
	 glColor3f(212.0/255.0,175.0/255.0,55.0/255.0);
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

// Function to draw objects on the screen
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	srand ( time(NULL) );

	//provides color in presence of lightning
	glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
	glEnable(GL_COLOR_MATERIAL);
	gluLookAt(0,30,100,0,0,0,0,1,0);
	RenderToDisplay();

	if(UpwardsScrollVelocity<-100)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		
		glLoadIdentity();

	//co-ordinate system for robot is x +ve in left and z +ve inward 
	if (fps%2==1)
	{
		camy=camyi;
		looky=camy;
		if(indx==0 || indx==-1)		//up
		{
			camx=camxi+xco;
			camz=camzi+zco;
			lookx=camx;
			lookz=camz+0.5;
		}
		else if(indx==1)		//left
		{
			camx=camxi+zco;
			camz=camzi-xco;
			lookx=camx+0.5;
			lookz=camz;
		}
		else if(indx==2)		//down
		{
			camx=camxi-xco;
			camz=camzi-zco;
			lookx=camx;
			lookz=camz-0.5;
		}
		else				//right
		{
			camx=camxi-zco;
			camz=camzi+xco;
			lookx=camx-0.5;
			lookz=camz;
		}
		gluLookAt(camx,camy,camz,lookx,looky,lookz,0,1,0);
	}
	else if (tps%2==1)
	{
		
		looky=camyt;
		if(indx==0 || indx==-1)		//up
		{
			camx=camxi+xco;
			camz=camzi+zco;
			lookx=camx;
			lookz=camz-add;
		}
		else if(indx==1)		//left
		{
			camx=camxi+zco;
			camz=camzi-xco;
			lookx=camx-add;
			lookz=camz;
		}
		else if(indx==2)		//down
		{
			camx=camxi-xco;
			camz=camzi-zco;
			lookx=camx;
			lookz=camz+add;
		}
		else				//right
		{
			camx=camxi-zco;
			camz=camzi+xco;
			lookx=camx+add;
			lookz=camz;
		}
		gluLookAt(lookx,2.5,lookz,camx,camyt,camz,0,1,0);
	}
	else if(tileview%3==2)
	{
		computeorigco();
		gluLookAt(tilex,tiley+0.2,tilez-5.1,origx-1.4,0,origz-5.6,0,1,0);
	}
	else if(hview%2==1)
	{
		printf("mouse in look at..%f,%f,%f\n",mposx,mposy,mposz);
		gluLookAt(cmx, cmy, cmz, mposx, mposy, mposz, 0.0f, 1.0f, 0.0f);
	}
	else
	gluLookAt(0, 3.5, -7.4, 0, 0.0f, -5, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	float  i,j;

	//water
	float ww;
	ww=(float)windowWidth;
	glPushMatrix();
	glTranslatef(0,-2,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_textureId1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	//glNormal3f(0,1,0);
	glTexCoord2f(0,0);
	glVertex3f( -15, 0, 15 );    
	glTexCoord2f(15,0);
	glVertex3f( -15,  0, -15 );    
	glTexCoord2f(15,15);
	glVertex3f( 15,  0, -15);    
	glTexCoord2f(0,10);
	glVertex3f( 15,  0, 15 );    
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	//tiles
	num=0;
	int c=0;
	for(i=-1.6;i<(0.4*4);i+=0.4)
	{

		for(j=-0.4;j<(0.4*6);j+=0.4)
		{
			c++;
//			printf("c..%d\n",c);
			if (c==1)
				printf("(i,j)..%f %f\n",i,j);
			//no tile present
			if(c==4 || c==10 || c==20 || c==24 || c==38 || c==50 || c==40 || c==51)
			{
	//			printf("c..%d num..%d i,j..%f %f\n",c,num,i,j);
				tiles[num][0]=i;
				tiles[num][1]=0;
				tiles[num][2]=j;
				tiles[num][3]=-1;
				num++;
				continue;
			}
			else if(c==7 || c==53)		//block
			{
				tiles[num][0]=i;
				tiles[num][1]=0;
				tiles[num][2]=j;
				tiles[num][3]=1;
				num++;

			}
			else if(c==15 || c==30 || c==56)		//tile moving up and down
			{
				tiles[num][0]=i;
				tiles[num][1]=k;
				tiles[num][2]=j;
				tiles[num][3]=0;
				num++;
			}
			else if(c==33)					//tile moving sideways
			{
				tiles[num][0]=xt;
				tiles[num][1]=0;
				tiles[num][2]=j;
				tiles[num][3]=2;
				num++;
				glPushMatrix();
				glTranslatef(xt,0,j);		
				glScalef(1,1,2);
				if(tileview%3==1 && fabs(tilex-i)<0.000001 && fabs(tilez-j)<0.000001)
				{
					drawcube(0.06,1,_textureId2);
					tiley=0;
				}
				else
				drawcube(0.06,1,_textureId);
				glPopMatrix();
			}
			else if(c==62)
			{
				firex=i;
				firez=j;
				glPushMatrix();
				glTranslatef(i,0,j);		
				glScalef(1,1,2);
				if(tileview%3==1 && fabs(tilex-i)<0.000001 && fabs(tilez-j)<0.000001)
				{
					drawcube(0.06,1,_textureId2);
					tiley=0;
				}
				else
					drawcube(0.06,1,_textureId3);
				glPopMatrix();
			}
			else if(c==44)
			{
				tiles[num][0]=xt1;
				tiles[num][1]=0;
				tiles[num][2]=j;
				tiles[num][3]=2;
				num++;
				glPushMatrix();
				glTranslatef(xt1,0,j);		
				glScalef(1,1,2);
				if(tileview%3==1 && fabs(tilex-i)<0.000001 && fabs(tilez-j)<0.000001)
				{
					drawcube(0.06,1,_textureId2);
					tiley=0;
				}
				else
				drawcube(0.06,1,_textureId);
				glPopMatrix();
			}
			else
			{
			glPushMatrix();
			glTranslatef(i,0,j);		
			glScalef(1,1,2);
			if(tileview%3==1 && fabs(tilex-i)<0.000001 && fabs(tilez-j)<0.000001)
			{
				drawcube(0.06,1,_textureId2);
				tiley=0;
			}
			else
				drawcube(0.06,1,_textureId);
			glPopMatrix();
			}
		}
	}
	int l;
	no=0;
	for(l=0;l<num;l++)
	{
		if(tiles[l][3]==0)		//tiles mving up down
		{
			glPushMatrix();
			glTranslatef(tiles[l][0],tiles[l][1],tiles[l][2]);		
			glScalef(1,1,2);
			if(tileview%3==1 && fabs(tilex-tiles[l][0])<0.000001 && fabs(tilez-tiles[l][2])<0.000001)
			{
				drawcube(0.06,1,_textureId2);
				tiley=tiles[l][1];
			}
			else
				drawcube(0.06,1,_textureId);
			if(roboup==1 && tileupx==tiles[l][0] && tileupz==tiles[l][2])
			{
				int qloop=0;
				
				for(qloop=0;qloop<3;qloop++)
				{
					if(fabs(coin[qloop][0]-tileupx)<eps && fabs(coin[qloop][1]-tileupz)<eps)
					{
						coin[qloop][2]=1;
						break;
					}
				}
			}
			else if(coin[no][2]==0)
			{
				coin[no][0]=tiles[l][0];
				coin[no][1]=tiles[l][2];
				coin[no][2]=0;
				glColor3f(0.0f, 1.0f, 0.0f);
	//			glRotatef(theta1,0,1,0);
				drawBall(ball_rad);
			}
			no++;
			glPopMatrix();

		}
		else if(tiles[l][3]==1)		//blocks
		{
			glPushMatrix();
			glTranslatef(tiles[l][0],0,tiles[l][2]);		
			glScalef(1,1,2);
			drawcube(0.5,0,_textureId);
			glPopMatrix();
		}
	}

	int xx,yy;
	for(xx=0;xx<4;xx++)
	{
		printf("coin..%f %f %f\n",coin[xx][0],coin[xx][1],coin[xx][2]);
	}
	//robot 
	glPushMatrix();
	glTranslatef(-1.8,0.1,-0.6);
	glRotatef(theta,0,1,0);
	glTranslatef(xco,yco,zco);
	glColor3f(0,0,0.5);
	if(nmoving==0)
	{
		printf("nmoving..%d\n",nmoving);
		printf("g..%d\n",g);
		if(g%2==0)
		{
			if(!mod)
			{
				mod=glmReadOBJ("orig2.obj");
				if(!mod) exit(0);
				glmUnitize(mod);
				glmFacetNormals(mod);
				glmVertexNormals(mod,90.0);
			}
			if(mod2)
				glmDelete(mod2);
			if(mod1)
				glmDelete(mod1);
			mod2=NULL;mod1=NULL;
			glmDraw(mod,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
		}
		else if(g%2==1)
		{
			printf("g..1\n");
			if(mod)
				glmDelete(mod);
			if(mod1)
				glmDelete(mod1);
			mod=NULL;
			mod1=NULL;
			if(!mod2)
			{
				mod2=glmReadOBJ("orig1.obj");
				if(!mod2) exit(0);
				glmUnitize(mod2);
				glmFacetNormals(mod2);
				glmVertexNormals(mod2,90.0);
			}
			glmDraw(mod2,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
			printf("end of g..1\n");
		}
	}
	else if(nmoving==1)
	{
		printf("nmoving..%d\n",nmoving);
		if(mod)
			glmDelete(mod);
		if(mod2)
			glmDelete(mod2);
		mod=NULL;
		mod2=NULL;
		if(!mod1)
		{
			mod1=glmReadOBJ("orig.obj");
			if(!mod1) exit(0);
			glmUnitize(mod1);
			glmFacetNormals(mod1);
			glmVertexNormals(mod1,90.0);
		}
		glmDraw(mod1,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	}
	glPopMatrix();
/*	robot = glmReadOBJ("new.obj");
//	glmLinearTexture(robot);
	glmUnitize(robot);
	glmFacetNormals(robot);
	glmVertexNormals(robot, 90.0);
	glColor3f(0.5,0.5,0);
	glmDraw(robot,  GLM_TEXTURE | GLM_MATERIAL);
 */
	glPopMatrix();
	if(hview%2==0)
	{
		int loop=0;
		float loopx=1.8;
		for(loop=0;loop<(3-dead);loop++)
		{
			glPushMatrix();
			glTranslatef(loopx, 1.8f, -5.0f);
			width=2 ;
			height=2;
			glColor3f(0,1,0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glScalef(0.08,0.04,1);
			glBegin(GL_QUADS);
			glVertex2f(-width/ 2, -height / 2);  
			glVertex2f(width / 2, -height / 2);  
			glVertex2f(width / 2, height / 2);  
			glVertex2f(-width / 2, height / 2);  
			glEnd();
			glPopMatrix();
			loopx-=0.2;
		}
	}
	if(finish==1)
	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(-2,0.5,-4.0);
		glScalef(0.412, 0.412, 0.412);
		glColor3f(0, 1.0f, 0);
		glPushMatrix();
		//glRotatef(180 , 0, 1, 0);
		glRotatef(-30,1,0,0);
		t3dDraw3D(STRS[0], -1, 0, 0.05f);
		glPopMatrix();
	}

	}
	glutSwapBuffers();
}

void drawcube(float ht,int col,GLuint _texture)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//left
	glBegin(GL_QUADS);
	glColor3f(   0,  1, 1.0 );
	glTexCoord2f(0,0);
	glVertex3f( -0.2,  ht, 0 );    
	glVertex3f( -0.2,  ht, -0.2 );    
	glVertex3f( -0.2, 0, -0.2 );    
	glVertex3f( -0.2, 0, 0 );    
	glEnd();

	//right
	glBegin(GL_QUADS);
	glColor3f(   0,  1, 1.0 );
	glVertex3f( 0.2,  ht, -0.2 );    
	glVertex3f( 0.2,  ht, 0 );    
	glVertex3f( 0.2, 0, 0 );    
	glVertex3f( 0.2, 0, -0.2 );    
	glEnd();

	//front
	glBegin(GL_QUADS);
	glColor3f(   0,  1, 1 );
	glVertex3f( -0.2, ht, -0.2 );    
	glVertex3f( 0.2, ht, -0.2 );    
	glVertex3f( 0.2,  0, -0.2 );    
	glVertex3f( -0.2,  0, -0.2);   

	//back
	glBegin(GL_QUADS);
	glColor3f(   0,  1, 1);
	glVertex3f( -0.2, ht, 0 );    
	glVertex3f( 0.2, ht, 0 );    
	glVertex3f( 0.2,  0, 0 );    
	glVertex3f( -0.2,  0, 0);    
	glEnd();

	//top
	glColor3f(   1.0,  1.0, 1.0 );
	if(col==1)
	{
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f( -0.2,  ht, 0 );    
	glTexCoord2f(1,0);
	glVertex3f( -0.2,  ht, -0.2 );    
	glTexCoord2f(1,1);
	glVertex3f( 0.2,  ht, -0.2 );    
	glTexCoord2f(0,1);
	glVertex3f( 0.2,  ht, 0 );    
	glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
		glVertex3f( -0.2,  ht, 0 );    
		glVertex3f( -0.2,  ht, -0.2 );    
		glVertex3f( 0.2,  ht, -0.2 );    
		glVertex3f( 0.2,  ht, 0 );    
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}
// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {

	theta1+=50;

	//up-down mov of tiles
	if(k < 0.5 && chk!=1)
	k+=0.1;
	else if(k>=0.5)
	{
		chk=1;
	}
	if(chk==1 && k>=0.1)
		k-=0.1;
	else
		chk=0;
	if(roboup==1)
	{
		yco=k;
	}
	//sideways mov of tiles(33)
//	printf("first time xt..%f\n",xt);
	if(xt<=0.4 && chk1!=1)
		xt+=0.1;
	else if(xt>0.4)
		chk1=1;
	if(chk1==1 && xt<=0.5 && xt>=0.1)
		xt-=0.1;
	else 
		chk1=0;
	
	//sideways mov of tile(44)
	if(xt1<=1.2 && chk2!=1)
		xt1+=0.1;
	else if(xt1>1.2)
		chk2=1;
	if(chk2==1 && xt1<=1.3 && xt1>=0.8)
		xt1-=0.1;
	else 
		chk2=0;
	//	printf("xt..%f\n",xt);

/*	if(flag==1)
	{
		float rbx=origx-1.8;
		if(!((rbx < tilesidex+0.2 || fabs(rbx-(tilesidex+0.2))<eps)&&(rbx > tilesidex-0.2 || fabs(rbx-(tilesidex-0.2))<eps)))
		{
			fallfrmside=1;
		}
		else
		{
			zco=rbx+0.1;
		}
	}*/
	glutTimerFunc(900, update, 0);
}
void falln(int val)
{
	if(fall==1 || fallfrmup==1 || fallfrmside==1)
	{
		yco-=0.2;
	}
	glutTimerFunc(100,falln,0);
}
void handlejump(int val1)
{
	if(jump==1)
	{
		zco+=0.05;
		if(yco<0.3 && jmp!=1)
			yco+=0.1;
		else if(yco>=0.3)
		{
			yco-=0.1;
			jmp=1;
		}
		else if(jmp==1 && yco<=0.3)
		{
			if(fabs(yco)<0.000001)
			{
				jump=0;
				jmp=0;
			}
			else
			{
				yco-=0.1;
			}
		}
		computeorigco();
		chckfall(origx-1.8,0,origz-0.6);
	}
	printf("final yco..%f\n",yco);
	glutTimerFunc(100,handlejump,0);
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0, 0, 0, 1.0f);   // Setting a background color
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0) ; 
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	t3dInit();
	Image* image = loadBMP("tile.bmp");
	_textureId = loadTexture(image);
	delete image;
	Image* image1 = loadBMP("water.bmp");
	_textureId1 = loadTexture(image1);
	delete image1;
	Image* image2 = loadBMP("tile1.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;
	Image* image3 = loadBMP("fire.bmp");
	_textureId3 = loadTexture(image3);
	delete image3;

	//lightns entire world
	GLfloat lightpos[] = {1.0, 0, 0, 0.0};		//directional light
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glEnable(GL_LIGHT1) ; 
	computeorigco();
	GLfloat position[] = {origx-1.8, 0.1, origz-5.6, 1.0};		//positional light
	//GLfloat position[] = {-1.9, 2, -2.7, 1.0};		//positional light
	GLfloat light_ambient1[] = { 1.0, 0.0, 0, 1.0 };
//	GLfloat color[4] = { 1.0, 0, 0, 1.0 };
//	GLfloat position[4] = {-1.9,2,-2.7,1.0};
	computeorigco();
	float LightDir[3] = {origx-1.8, 2,origz-5.6 }; // towards the viewer
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 45); 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDir);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		cleanup();
		exit(0);     // escape key is pressed
	}
	if (key==102)		//f key for fps view
	{
		fps++;
	}
	if(key==116)		//t key for third person view
	{
		tps++;
	}
	if (key==106)		// j key for jump
	{
		jump=1;
	}
	if(key==118)		//v key for tile view
	{
		tileview++;
	}
	if(tileview%3==1)
	{
		if(key==97)		// a key for left
		{
			if(tilex<1.6)
			tilex+=0.4;
		}
		else if(key==119)	//w key for up
		{
			if(tilez<2)
			tilez+=0.4;
		}
		else if(key==100)	//d key for right
		{
			if(tilex>-1.6)
			tilex-=0.4;
		}
		else if(key==115)	//s key for down
		{
			if(tilez>-0.4)
			tilez-=0.4;
		}
		printf("inside tileview..tilex..%f tilez..%f\n",tilex,tilez);
	
	}
	if(key==104)		// h key for helicopter view
	{
		hview++;
	}
}

void handleKeypress2(int key, int x, int y) 
{
	int collide=0;
	storex=xco;
	storez=zco;
	if (key == GLUT_KEY_RIGHT)
	{
		nmoving=0;
		pindx=indx;
		g++;
		theta=-90;
		indx=3;
		if(pindx!=3)
			nmoving=1;
		if(pindx==0)
		{
			intr=xco;
			xco=zco;
			zco=-intr;
		}
		else if(pindx==1)
		{
			xco=-xco;
			zco=-zco;
		}
		else if(pindx==2)
		{
			intr=zco;
			zco=xco;
			xco=-intr;
		}
		collide=collision();
		if(collide==0)
		zco+=0.1f;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		nmoving=0;
		pindx=indx;
		g++;
		theta=90;
		indx=1;
		if(pindx!=1)
			nmoving=1;
		if(pindx==0)
		{
			intr=zco;
			zco=xco;
			xco=-intr;
		}
		else if(pindx==2)
		{
			printf("up to right..initial x..%f z..%f\n",xco,zco);
			intr=xco;
			xco=zco;
			zco=-intr;
			printf("final x..%f z..%f\n",xco,zco);
		}
		else if(pindx==3)
		{
			zco=-zco;
			xco=-xco;
		}
		collide=collision();
		if(collide==0)
		zco+=0.1f;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		nmoving=0;
		pindx=indx;
		g++;
		theta=180;
		indx=2;
		if(pindx!=2)
			nmoving=1;
		if(pindx==0)
		{
			xco=-xco;
			zco=-zco;
		}
		else if(pindx==1)
		{
			intr=zco;
			zco=xco;
			xco=-intr;
		}
		else if(pindx==3)
		{
			intr=xco;
			xco=zco;
			zco=-intr;
		}
		collide=collision();
		if(collide==0)
		zco+=0.1f;
	}
	else if (key == GLUT_KEY_UP)
	{
		nmoving=0;
		pindx=indx;
		g++;
		theta=0;
		indx=0;
		if(pindx!=0)
			nmoving=1;
		if(pindx==1)
		{
			intr=xco;
			xco=zco;
			zco=-intr;
		}
		else if(pindx==2)
		{
			zco=-zco;
			xco=-xco;
		}
		else if(pindx==3)
		{
			intr=xco;
			xco=-zco;
			zco=intr;
		}
		collide=collision();
		if(collide==0)
			zco+=0.1f;
	}
	computeorigco();

	float finx=origx-1.8,finz=origz-0.6;
	if(     ((finx>(1.6-0.2)|| fabs(finx-(1.6-0.2))<eps) &&
				(finx <(1.6+0.2) || fabs(finx-(1.6+0.2))<eps)) &&
			((finz > (2-0.2) || fabs(finz-(2-0.2))<eps) &&
			 (finz <(2+0.2) || fabs(finz-(2+0.2))<eps)) )
	{
		finish=1;
		printf("finish game\n");
	}
	else
		chckfall(origx-1.8,0,origz-0.6);

	//	chckfall(origx-1.8,0,origz-0.6);
	printf("inside handle key press\n");
}
void computeorigco()
{
	if(indx==0)
	{
		origx=xco;
		origz=zco;
	}
	else if(indx==1)
	{
		origx=zco;
		origz=-xco;
	}
	else if(indx==2)
	{
		origx=-xco;
		origz=-zco;
	}
	else if(indx==3)
	{
		origx=-zco;
		origz=xco;
	}
	if(roboup==1)
	{

		int checkk=0;
		float rx=origx-1.8;
		float rz=origz-0.6;
//		printf("robot..(%f,%f) tile..(%f,%f)\n",origx,origz,tileupx,tileupz);
		if((rx>(tileupx-0.2)|| fabs(rx-(tileupx-0.2))<eps) && 
				(rx <(tileupx+0.2) || fabs(rx-(tileupx+0.2))<eps) && 
			((rz > (tileupz-0.2) || fabs(rz-(tileupz-0.2))<eps) && 
			 (rz <(tileupz+0.2) || fabs(rz-(tileupz+0.2))<eps)) )
		{
			checkk=1;
//			printf("on the tile\n");
		//	continue;
		}
		if(checkk==0)
		{
			roboup=0;
			if(fabs(yco)>=eps)
			{
				dead++;
				if(dead==3)
				fallfrmup=1;
				else
				{
					xco=0;
					yco=0;
					zco=0;
				}
			}
//			yco=0;
		}
	}
}
int collision()
{
	float collx,collz;
	if(indx==0)
	{
		collx=xco;
		collz=zco+0.1;
	}
	else if(indx==1)
	{
		collx=zco+0.1;
		collz=-xco;
	}
	else if(indx==2)
	{
		collx=-xco;
		collz=-(zco+0.1);
	}
	else if(indx==3)
	{
		collx=-(zco+0.1);
		collz=xco;
	}
	collx=collx-1.8;
	collz=collz-0.6;
	int iter=0;
	float tx,ty,tz;
//	printf("collision origx..%f origz..%f\n",collx,collz);
	for(iter=0;iter<num;iter++)
	{
		tx=tiles[iter][0];
		ty=tiles[iter][1];
		tz=tiles[iter][2];
		if(tiles[iter][3]==1)
//		printf("tx..%f tz..%f\n",tx,tz);
		if(	(tiles[iter][3]==1)&&
				((collx>(tx-0.2)|| fabs(collx-(tx-0.2))<eps) && 
				 (collx <(tx+0.2) || fabs(collx-(tx+0.2))<eps)) && 
				((collz > (tz-0.2) || fabs(collz-(tz-0.2))<eps) && 
				 (collz <(tz+0.2) || fabs(collz-(tz+0.2))<eps)) 
		  )
		{
//			printf("collides\n");
			return 1;
		}
	}
	return 0;
}
int chckfall(float robox,float roboy,float roboz)
{
	int i;
	float tx,ty,tz;
	if(	((robox>(firex-0.2)|| fabs(robox-(firex-0.2))<eps) && 
			 (robox <(firex+0.2) || fabs(robox-(firex+0.2))<eps)) && 
			((roboz > (firez-0.2) || fabs(roboz-(firez-0.2))<eps) && 
			 (roboz <(firez+0.2) || fabs(roboz-(firez+0.2))<eps)) )
	{
		xco=-0.3;
		zco=0.3;
	}
	for(i=0;i<num;i++)
	{
		tx=tiles[i][0];
		ty=tiles[i][1];
		tz=tiles[i][2];
//		printf("robox..%f roboz..%f tx..%f tz..%f type..%f\n",robox,roboz,tx,tz,tiles[i][3]);
//		printf("robox..%f roboz..%f\n",robox,roboz);

		//end of the world
		if( fabs(robox+1.9)<eps || fabs(robox-1.9)<eps || fabs(roboz+0.7)<eps || fabs(roboz-2.3)<eps ||
			  robox>1.9 || robox<-1.9 || roboz>2.3 || roboz<-0.7)
		{
			dead++;
			if(dead==3)
				fall=1;
			else
			{
				xco=0;
				zco=0;
				yco=0;
//				xco=storex;
//				zco=storez;
			}
			return fall;
		}
		//check the tiles
		if(tiles[i][3]==2)
		printf("tx for side ways..%f\n ",tx);
		if(	((robox>(tx-0.2)|| fabs(robox-(tx-0.2))<eps) && 
			 (robox <(tx+0.2) || fabs(robox-(tx+0.2))<eps)) && 
			((roboz > (tz-0.2) || fabs(roboz-(tz-0.2))<eps) && 
			 (roboz <(tz+0.2) || fabs(roboz-(tz+0.2))<eps)) )
		{
			if(tiles[i][3]==-1)
			{
			dead++;
			if(dead==3)
				fall=1;
			else
			{
				xco=0;
				yco=0;
				zco=0;
	//			xco=storex;
	//			zco=storez;
			}
				return fall;
			}
			else if(tiles[i][3]==2)
			{
					dead++;
					if(dead==3)
						fall=1;
					else
					{
						xco=0;
						yco=0;
						zco=0;
					}
				return fall;
			}
			else if(tiles[i][3]==0 && roboup==0)
			{
				printf("tile moving vertically..yco..%f ty..%f\n",yco,ty);
				if(fabs(ty-yco) >= 0.000001)
				{
					dead++;
					if(dead==3)
						fall=1;
					else
					{
						xco=0;
						yco=0;
						zco=0;
					}
					return fall;
				}
				else
				{
					roboup=1;
					tileupx=tx;
					tileupz=tz;
					printf("tileup..(%f,%f)\n",tileupx,tileupz);
				}
			}
		/*	else if(tiles[i][3]==2)
			{
				printf("xcoordinate of sideways moving tile..%f\n",tiles[i][0]);
				flag=1;
				tilesidex=tiles[i][0];
			}*/
		}
	}
	fall=0;
	return fall;
}

void handleMouseclick(int button, int state, int x, int y) 
{

	printf("mouse..(%d,%d)\n",x,y);
	if(hview%2==1)
	{
		if(state == GLUT_DOWN)
		{
			if(button == GLUT_LEFT_BUTTON)
			{
				GLint viewport[4];
				GLdouble modelview[16];
				GLdouble projection[16];
				GLfloat winX, winY, winZ;
				glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
				glGetDoublev( GL_PROJECTION_MATRIX, projection );
				glGetIntegerv( GL_VIEWPORT, viewport );

				winX = (float)x;
				winY = (float)viewport[3] - (float)y;
				glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

				gluUnProject( winX, winY, winZ, modelview, projection, viewport, &mposx, &mposy, &mposz);
				/*width=4;
				height=6;
				mposx = x/(float)windowWidth *(width)+(-width/2);
				mposy = (1-y/(float)windowHeight)*height+(-height/2);*/

			}
		}


		//zoom in
		float len=sqrt(((cmxi-mposx)*(cmxi-mposx))+((cmyi-mposy)*(cmyi-mposy))+((cmzi-mposz)*(cmzi-mposz)));
		if(button==3)
		{
			printf("zoom in\n");
			//printf("cami..%f,%f,%f cam..%f,%f,%f\n",cmxi,cmyi,cmzi,cmx,cmy,cmz);
			cmz+=(0.1*((mposz-cmzi)/len));
			cmx+=(0.1*((mposx-cmxi)/len));
			cmy+=(0.1*((mposy-cmyi)/len));
			printf("cami..%f,%f,%f cam..%f,%f,%f\n",cmxi,cmyi,cmzi,cmx,cmy,cmz);
		}
		else if(button==4)		//zoom out
		{
			cmz-=(0.1*((mposz-cmzi)/len));
			cmx-=(0.1*((mposx-cmxi)/len));
			cmy-=(0.1*((mposy-cmyi)/len));
		}
	}
	/*		computeorigco();
		float len=sqrt(((cmxi-origx)*(cmxi-origx))+((cmyi-origy)*(cmyi-origy))+((cmzi-origz)*(cmzi-origz)));
		if(button==3)
		{
			printf("zoom in\n");
			//printf("cami..%f,%f,%f cam..%f,%f,%f\n",cmxi,cmyi,cmzi,cmx,cmy,cmz);
			cmz+=(0.1*((origz-cmzi)/len));
			cmx+=(0.1*((origx-cmxi)/len));
			cmy+=(0.1*((origy-cmyi)/len));
			printf("cami..%f,%f,%f cam..%f,%f,%f\n",cmxi,cmyi,cmzi,cmx,cmy,cmz);
		}
		else if(button==4)		//zoom out
		{
			cmz-=(0.1*((origz-cmzi)/len));
			cmx-=(0.1*((origx-cmxi)/len));
			cmy-=(0.1*((origy-cmyi)/len));
		}

}*/
printf("pos..(%f,%f,%f)\n",mposx,mposy,mposz);
}
void helicopter(int x,int y)
{
	if(hview%2==1)
	{
/*				width=4;
				height=6;
				mposx = x/(float)windowWidth *(width)+(-width/2);
				mposy = (1-y/(float)windowHeight)*height+(-height/2);*/
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX, winY, winZ;
		glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
		glGetDoublev( GL_PROJECTION_MATRIX, projection );
		glGetIntegerv( GL_VIEWPORT, viewport );

		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

		gluUnProject( winX, winY, winZ, modelview, projection, viewport, &mposx, &mposy, &mposz);
	}
}
