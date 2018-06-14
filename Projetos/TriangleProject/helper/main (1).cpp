/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */


#include <GL/glut.h>
#include <windows.h>

#include <stdlib.h>
#include<stdio.h>
#include "carregamalha.hpp"
#include "malha.hpp"


#include<glm/vec4.hpp>
#include<glm/vec3.hpp>
#include <stdlib.h>
#include<stdio.h>
#include<glm/geometric.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

float xant;
float yant;
int difx, dify;
int mode=3;
GLfloat boundbox[3];


glm::vec3 center;
glm::vec3 pivot;
glm::mat4 rotUp;
glm::vec4 newDir;



struct Camera{
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up;
    glm::vec3 side;
    float speed;
    float angularSpeed;
};


Camera cam;



//Vetores para alocação de dados



Malha rabbit;
Malha chair;

int fovy=60;


float ar;

int winwidth=640;
int winheight=480;
/* GLUT callback Handlers */

static void resize(int width, int height)
    {
    ar = (float) width / (float) height;

    winwidth = width;
    winheight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, ar,0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


static void printGL(int x, int y, char *str)
   //void printtext(int x, int y, int w, int h, char *str)
{
            //(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, winwidth, 0, winheight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    int len = (int) strlen(str);
    for (int i=0; i<len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

static void DrawChair(double a){
     glColor3d(0.1,0.1,0.5);
     if(mode==1){
        glColor3f(chair.cor[0],chair.cor[1],chair.cor[2]);
     }
     glEnableClientState(GL_NORMAL_ARRAY);
     glEnableClientState(GL_VERTEX_ARRAY);

     glNormalPointer(GL_FLOAT,0,chair.vetNormais);

     glVertexPointer(3,GL_FLOAT,0,chair.vetVertice);
     glPushMatrix();

     glTranslated(-chair.centro[0],-chair.centro[1],-chair.centro[2]);
     chair.pos[0]=1.5;
     chair.pos[1]=1.5;
     chair.pos[2]=-4;
     glTranslated(chair.pos[0],chair.pos[1],chair.pos[2]);

     glDrawElements(GL_TRIANGLES, 3*chair.tamTriangles, GL_UNSIGNED_INT, chair.vetTriangles);
     glPopMatrix();
     glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
     glDisableClientState(GL_NORMAL_ARRAY);
}

static void DrawRabbit(double a){
    if(mode==1){
        glColor3f(rabbit.cor[0],rabbit.cor[1],rabbit.cor[2]);
     }
     glEnableClientState(GL_NORMAL_ARRAY);
     glEnableClientState(GL_VERTEX_ARRAY);

     glNormalPointer(GL_FLOAT,0,rabbit.vetNormais);

     glVertexPointer(3,GL_FLOAT,0,rabbit.vetVertice);
     glPushMatrix();



     glTranslated(-rabbit.centro[0],-rabbit.centro[1],-rabbit.centro[2]);

     rabbit.pos[0]=0;
     rabbit.pos[1]=0;
     rabbit.pos[2]=-3;
     glTranslated(rabbit.pos[0],rabbit.pos[1],rabbit.pos[2]);




     glDrawElements(GL_TRIANGLES, 3*rabbit.tamTriangles, GL_UNSIGNED_INT, rabbit.vetTriangles);
     glPopMatrix();





     glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
     glDisableClientState(GL_NORMAL_ARRAY);
}

static void Draw(double a){
    DrawRabbit(a);
    DrawChair(a);
}

void displaySelection(){

    GLfloat res[4];
    GLint viewport[4];

    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    rabbit.cor[0]=0.0;
    rabbit.cor[1]=1.0;
    rabbit.cor[2]=0.0;

    chair.cor[0]=0.0;
    chair.cor[1]=0.0;
    chair.cor[2]=1.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, ar, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    cam.side = glm::cross(cam.dir,cam.up);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();
    gluLookAt(cam.pos.x, cam.pos.y, cam.pos.z, center.x,center.y,center.z,cam.up.x,cam.up.y,cam.up.z);

    Draw(a);


    glGetIntegerv(GL_VIEWPORT, viewport);

    glReadPixels(xant,viewport[3]-yant,1,1,GL_RGBA,GL_FLOAT,&res);


    if(res[0]==rabbit.cor[0]){
        if(res[1]==rabbit.cor[1]){
            if(res[2]==rabbit.cor[2]){

                boundbox[0]=rabbit.maximos[0]-rabbit.minimos[0];
                //printf("\n bound box %f \n", boundbox[0]);
                boundbox[1]=rabbit.maximos[1]-rabbit.minimos[1];
                boundbox[2]=rabbit.pos[2];

                //printf("\n cadeira %f coelho %f \n", chair.minimos[0], rabbit.minimos[0]);

                pivot.x = rabbit.pos[0];
                pivot.y = rabbit.pos[1];
                pivot.z = rabbit.pos[2];
                cam.dir = pivot-cam.pos;


                mode=2;
            }
        }
    }

    if(res[0]==chair.cor[0]){
        if(res[1]==chair.cor[1]){
            if(res[2]==chair.cor[2]){

                glScalef(chair.maximos[0]-chair.minimos[0],chair.maximos[1]-chair.minimos[1],chair.maximos[2]-chair.maximos[2]);

                boundbox[0]=(chair.maximos[0]-chair.minimos[0])/2;
               // printf("\n bound box %f \n", boundbox[0]);
                boundbox[1]=(chair.maximos[1]-chair.minimos[1])/2;
                boundbox[2]=(chair.maximos[2]-chair.maximos[2])/2;

                //printf("\n cadeira %f coelho %f \n", chair.maximos[0], rabbit.maximos[0]);


                pivot.x = chair.pos[0];
                pivot.y = chair.pos[1];
                pivot.z = chair.pos[2];

                cam.dir = pivot - cam.pos;

                mode=2;

            }
        }
    }




}


static void display(void)

{

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    if(mode==1){
        displaySelection();
    }
    printGL(0,0,"Hello World");


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, ar, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    cam.side = glm::cross(cam.dir,cam.up);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0.5,1,0.5);


    center = cam.pos + cam.dir;
    glLoadIdentity();
    gluLookAt(cam.pos.x, cam.pos.y, cam.pos.z, center.x,center.y,center.z,cam.up.x,cam.up.y,cam.up.z);

    Draw(a);
    if(mode==2){

        glPushMatrix();

        glTranslatef(boundbox[0],boundbox[1],boundbox[2]);
        glutWireCube(1);
        glPopMatrix();    //parei aqui
    }

    if(mode!=1){

        glutSwapBuffers();
        glutPostRedisplay();
    }
}


static void key(unsigned char key, int x, int y)
{


    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;



        /*case 'a':
            cam.speed=cam.speed*1.1;
            break;

        case 'z':
            cam.speed=cam.speed*0.9;
            break;*/

        case 'a':
            cam.pos = cam.pos + cam.speed*cam.up;
            break;

        case 'z':
            cam.pos = cam.pos - cam.speed*cam.up;
            break;

        /*case 'w':

            break;
        case 's':

            break;
*/
        case '-':
            rotUp = glm::rotate(glm::mat4(1.0),-cam.angularSpeed,cam.up);                        //glm::mat4(1.0) cria uma matriz identidade no GLM
            newDir = rotUp * glm::vec4(cam.dir,1.0);      //newDir é uma matrix 4x4, recebendo matriz dir com um parametro a mais, o "U" que é 1.0
            cam.dir=newDir;    // no GLM pode transformar 4x4 em 3x3
            break;

        case '+':
            rotUp = glm::rotate(glm::mat4(1.0),cam.angularSpeed,cam.up);                        //glm::mat4(1.0) cria uma matriz identidade no GLM
            newDir = rotUp * glm::vec4(cam.dir,1.0);      //newDir é uma matrix 4x4, recebendo matriz dir com um parametro a mais, o "U" que é 1.0
            cam.dir=newDir;    // no GLM pode transformar 4x4 em 3x3
            break;

        case '1':
            mode=1;
            break;

        case '3':
            mode=3;
            break;

        case '2':
            mode=2;
            break;




    }

    glutPostRedisplay();
}

static void special(int key, int x, int y){
     cam.side = glm::cross(cam.dir,cam.up);
     switch (key) {
         case GLUT_KEY_UP:
            cam.pos = cam.pos + cam.speed*cam.dir;
            break;
         case GLUT_KEY_DOWN:
            cam.pos = cam.pos - cam.speed*cam.dir;
            break;
         case GLUT_KEY_LEFT:
            cam.pos = cam.pos - cam.speed*cam.side;
            break;
         case GLUT_KEY_RIGHT:
            cam.pos = cam.pos + cam.speed*cam.side;
            break;
 }
}

void mouseButton(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            printf("O botão esquerdo do mouse foi pressionado na posição x = %d, y = %d \n", x, y);
            xant = x;
            printf ("xant = %f", xant);
            yant=y;

            if(mode==3){
                rotUp = glm::rotate(glm::mat4(1.0),cam.angularSpeed,cam.up);                        //glm::mat4(1.0) cria uma matriz identidade no GLM
                newDir = rotUp * glm::vec4(cam.dir,1.0);      //newDir é uma matrix 4x4, recebendo matriz dir com um parametro a mais, o "U" que é 1.0
                cam.dir=newDir;    // no GLM pode transformar 4x4 em 3x3
            }
        }
    }
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            //printf("O botão esquerdo do mouse foi solto");

        }
    }
}
/*
void calculaTam(Malha vet*){
    for(int i=0; i<)

}*/

void mouseMove(int x2, int y) {
    if(mode!=1){



        /*printf("O mouse agora está na posição x = %d, y= %d e um dos botões do mouse está pressionado nesse momento \n",x2, y);

        printf("\n O x anterior é %d, e o y anterior é %d. Agora o x atual é %d, e o y atual é %d \n",xant, yant,x2,y);
*/

        difx=x2-xant;


        dify=y-yant;


        if(mode==2){
            cam.dir=pivot - cam.pos;
        }

        rotUp = glm::rotate(glm::mat4(1.0),difx*cam.angularSpeed,cam.up);                        //glm::mat4(1.0) cria uma matriz identidade no GLM
        newDir = rotUp * glm::vec4(cam.dir,1.0);      //newDir é uma matrix 4x4, recebendo matriz dir com um parametro a mais, o "U" que é 1.0
        cam.dir=newDir;

        cam.side = glm::cross(cam.dir,cam.up);

        rotUp = glm::rotate(glm::mat4(1.0),dify*cam.angularSpeed,cam.side);                        //glm::mat4(1.0) cria uma matriz identidade no GLM
        newDir = rotUp * glm::vec4(cam.dir,1.0);      //newDir é uma matrix 4x4, recebendo matriz dir com um parametro a mais, o "U" que é 1.0
        cam.dir=newDir;

        if (mode==2){

            cam.pos=pivot - cam.dir;
        }



        xant = x2;
        yant = y;
        glutPostRedisplay();

    }
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */



int main(int argc, char *argv[])
{

    //--------------*Abrir o arquivo com dados da malha de triângulos*-----------
    FILE *entrada,*entrada2;
	entrada= fopen("bunny.msh","r");
	entrada2=fopen("chair.msh","r");

	if(entrada==NULL){
        printf("ERROR NOT FOUND");
        exit(1);
	}
	 //-----------------------------*Fim Leitura*--------------------------------





	carregaMalhaTriangles(entrada,&rabbit); //Carregamento de dados em  vetores globais
    carregaMalhaTriangles(entrada2,&chair);


    fclose(entrada);
    fclose(entrada2);


    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    cam.pos = glm::vec3(0,0,0);
    cam.dir = glm::vec3(0,0,-1);
    cam.up = glm::vec3(0,1,0);
    cam.speed = 0.1;
    cam.angularSpeed = 0.01;

    glutMainLoop();

    return EXIT_SUCCESS;
}
