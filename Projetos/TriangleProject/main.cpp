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

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "Camera.h"

GLfloat* vertices;
GLfloat* normais;
GLuint* indices;

Camera *camera = new Camera();

bool isGlBegin = true;
double x, y, z;
int wid = 800;
int hei = 600;
bool isJumping = false;
double jumpStart;

int qtdVertices = 0, incidencia = 0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 50.0f };

double T = 0, t1 = 0, t2 = 0;

void printtext(int x, int y, int w, int h, char *str)
{
    //(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0f, 1.0f);
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

/* GLUT callback Handlers */
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void jumping(double how){
    if(isJumping && y - jumpStart < 3){
        y += how;
    }
    else if(isJumping && y - jumpStart >= 3) isJumping = false;
    else if(!isJumping && jumpStart < y && jumpStart != 0 ){
        y -= how;
    }
}

static void drawBunnyGlBegin(double a){
    glPushMatrix();
        jumping(0.09);
        glTranslated(x, y, z);
        glRotated(-a,0,1,0);

        glBegin(GL_TRIANGLES);
            for(int i = 0; i < incidencia * 3; i++){
                glNormal3f(normais[(indices[i] * 3) + 0], normais[(indices[i] * 3) + 1], normais[(indices[i] * 3) + 2]);
                glVertex3f(vertices[(indices[i] * 3) + 0], vertices[(indices[i] * 3) + 1], vertices[(indices[i] * 3) + 2]);
            }
        glEnd();
    glPopMatrix();

    printtext(700, 10, wid, hei, "GLBegin");
}

static void drawBunnyGlDrawElements(double a){
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 0, normais);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glPushMatrix();
        glColor3d(0,0,1);
        jumping(0.03);
        glTranslated(x, y, z);
        glRotated(a,0,1,0);
        glDrawElements(GL_TRIANGLES, incidencia * 3, GL_UNSIGNED_INT, indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    printtext(700, 10, wid, hei, "DrawElements");
}

static void display(void)
{
    char fpsx[3];
    char showing[10] = "FPS: ";

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    char line[255];

    t1 = t2;
    t2 = t;
    T = t2 - t1;
    double fps = 1/T;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glLoadIdentity();
    gluLookAt(camera->Getpos().x, camera->Getpos().y, camera->Getpos().z,
              camera->GetCenter().x, camera->GetCenter().y, camera->GetCenter().z,
              camera->Getup().x, camera->Getup().y, camera->Getup().z);

    if(isGlBegin) drawBunnyGlBegin(a);
    else drawBunnyGlDrawElements(a);

    z = -z;

    if(isGlBegin) drawBunnyGlBegin(a);
    else drawBunnyGlDrawElements(a);

    sprintf(fpsx, "%.1f", fps);
    strcat(showing, fpsx);
    printtext(10, 10, wid, hei, showing);

    printtext(10, 580, wid, hei, "Press WASD to move. Press E to UP. Press C to DOWN");
    printtext(10, 560, wid, hei, "Press R to switch between DrawElements and GLBegin.");
    printtext(10, 540, wid, hei, "PRESS SPACE TO JUMP!!!");

    glutSwapBuffers();
}

static void key(unsigned char key, int x1, int y1)
{
    switch (key)
    {
        case 'q':
            exit(0);
            break;
        case 'w':
            camera->MoveUp();
            break;
        case 's':
            camera->MoveDown();
            break;
        case 'd':
            camera->TurnRight();
            break;
        case 'a':
            camera->TurnLeft();
            break;
        case 'r':
            if(isGlBegin){
                isGlBegin = false;
            }
            else {
                isGlBegin = true;
            }
            break;
        case 32:
            if(!isJumping){
                isJumping = true;
                jumpStart = y;
            }
            break;
    }

    glutPostRedisplay();
}

void special(int key, int x, int y){
     switch (key) {
         case GLUT_KEY_UP:
             camera->MoveFoward();
             break;
         case GLUT_KEY_DOWN:
             camera->MoveBackward();
             break;
         case GLUT_KEY_LEFT:
             camera->MoveLeft();
             break;
         case GLUT_KEY_RIGHT:
             camera->MoveRight();
             break;
     }
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Leitura de arquivo */
static FILE* openFile(char *fileName)
{
    FILE *fl;

    fl = fopen(fileName, "r");

    return fl;
}

/* Recupera Valores Vertices */
static void preencher_vertices(FILE* fl)
{
    char line[255];

    for(int i = 0; i < qtdVertices; i++){
        fscanf(fl, "%s", line);
        int id = atoi(line);

        //1 v1 v2 v3 n1 n2 n3

        for(int j = 0; j < 3; j++){
            fscanf(fl, "%s", line);
            float val = atof(line);

            vertices[(i * 3) + j] = val;
        }

        for(int j = 0; j < 3; j++){
            fscanf(fl, "%s", line);
            float val = atof(line);

            normais[(i * 3) + j] = val;
        }
    }
}

// Recupera indices
static void preencher_indices(FILE* fl)
{
    char line[255];

    for(int i = 0; i < incidencia; i++){
        fscanf(fl, "%s", line);
        int id = atoi(line);

        for(int j = 0; j < 3; j++){
            fscanf(fl, "%s", line);
            int val = atoi(line);

            indices[(i * 3) + j] = val;
        }
    }
}

static void prepara_variaveis(FILE *fl)
{
    char line[255];

    fscanf(fl, "%s", line);
    qtdVertices = atoi(line);

    fscanf(fl, "%s", line);
    incidencia = atoi(line);

    x = 0;
    y = -1;
    z = -5;

    vertices = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    normais = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    indices = (GLuint*) malloc( incidencia * 3 * sizeof(GLuint) ); // allocate memory for array

    camera->Setpos(glm::vec3(0, 0, 0));
    camera->Setdir(glm::vec3(0, 0, -1));
    camera->Setup(glm::vec3(0, 1, 0));
    camera->Setspeed(1);
    camera->SetangularSpeed(0.1);

    preencher_vertices(fl);
    preencher_indices(fl);
}

/* Program entry point */
int main(int argc, char *argv[])
{
    FILE *fl = openFile("../chair_chesterfield.msh");

    if(fl == NULL)
    {
      printf("Error!");
      exit(1);
    }

    prepara_variaveis(fl);

    glutInit(&argc, argv);
    glutInitWindowSize(wid,hei);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Little Bunny");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);
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

    glutMainLoop();

    return EXIT_SUCCESS;
}
