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

GLfloat* vertices;
GLfloat* normais;
GLuint* indices;


bool isGlBegin = false;
int x, y, z;

int qtdVertices = 0, incidencia = 0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 50.0f };

GLint gFramesPerSecond = 0;

void FPS(void) {
  static GLint Frames = 0;         // frames averaged over 1000mS
  static GLuint Clock;             // [milliSeconds]
  static GLuint PreviousClock = 0; // [milliSeconds]
  static GLuint NextClock = 0;     // [milliSeconds]

  ++Frames;
  Clock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
  if ( Clock < NextClock ) return;

  gFramesPerSecond = Frames/1; // store the averaged number of frames per second

  PreviousClock = Clock;
  NextClock = Clock+1000; // 1000mS=1S in the future
  Frames=0;
}

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

static void display(void)
{
    char fpsx[3];
    char showing[10] = "FPS: ";

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    char line[255];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //printf("FPS %d\n",gFramesPerSecond);

    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(x, y, z);
        glRotated(-a,0,1,0);

        glBegin(GL_TRIANGLES);
            for(int i = 0; i < incidencia * 3; i++){
                glNormal3f(normais[(indices[i] * 3) + 0], normais[(indices[i] * 3) + 1], normais[(indices[i] * 3) + 2]);
                glVertex3f(vertices[(indices[i] * 3) + 0], vertices[(indices[i] * 3) + 1], vertices[(indices[i] * 3) + 2]);
            }
        glEnd();
    glPopMatrix();

    sprintf(fpsx, "%d", gFramesPerSecond);
    strcat(showing, fpsx);
    printtext(0, 1, 12, 12, showing);

    glutSwapBuffers();
}

static void draw()
{
    printf("DrawElements");

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 0, normais);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glPushMatrix();
        glColor3d(0,0,1);
        glTranslated(x, y, z);
        glDrawElements(GL_TRIANGLES, incidencia * 3, GL_UNSIGNED_INT, indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
            exit(0);
            break;
        case 'w':
            z++;
            printf("mudei z para: %d", z);
            break;
        case 's':
            z--;
            printf("mudei z para: %d", z);
            break;
        case 'r':
            if(isGlBegin){
                glutDisplayFunc(display);
                isGlBegin = false;
            }
            else {
                    glutDisplayFunc(draw);
                    isGlBegin = true;
            }
            break;
    }
    glutPostRedisplay();
}

static void idle(void)
{
    #define REGULATE_FPS
    #ifdef REGULATE_FPS
    static GLuint PreviousClock=glutGet(GLUT_ELAPSED_TIME);
    static GLuint Clock=glutGet(GLUT_ELAPSED_TIME);
    static GLfloat deltaT;

    Clock = glutGet(GLUT_ELAPSED_TIME);
    deltaT=Clock-PreviousClock;
    if (deltaT < 35) {return;} else {PreviousClock=Clock;}
    #endif

    //printf(".");
    FPS(); //only call once per frame loop
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
    z = -3;

    vertices = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    normais = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    indices = (GLuint*) malloc( incidencia * 3 * sizeof(GLuint) ); // allocate memory for array

    preencher_vertices(fl);
    preencher_indices(fl);
}

/* Program entry point */
int main(int argc, char *argv[])
{
    FILE *fl = openFile("../bunny.msh");

    if(fl == NULL)
    {
      printf("Error!");
      exit(1);
    }

    prepara_variaveis(fl);

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Little Bunny");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
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
