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
GLubyte* indices;
int qtdVertices = 0, incidencia = 0;
static int slices = 16;
static int stacks = 16;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,0);

    int i = 0;
    while(i < qtdVertices){
        glBegin(GL_TRIANGLES);
            glPointSize(1.0f);

            for(int j = 0; j < 9; j+= 3){
                glNormal3f(normais[i + j], normais[i + j + 1], normais[i + j + 2]);
                //printf("Normal: %.2f %.2f %.2f\n", normais[i + j], normais[i + j + 1], normais[i + j + 2]);
            }

            for(int j = 0; j < 9; j+= 3){
                glVertex3f(vertices[i + j], vertices[i + j + 1], vertices[i + j + 2]);
                //printf("Vertice: %.2f %.2f %.2f ", vertices[i + j], vertices[i + j + 1], vertices[i + j + 2]);
            }


        glEnd();
        i += 9;
    }

    glFlush();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
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
static void preencher_vertices(FILE* fl){
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
static void preencher_indices(FILE* fl){
    char line[255];

    for(int i = 0; i < incidencia; i++){
        fscanf(fl, "%s", line);
        int id = atoi(line);

        for(int j = 0; j < 3; j++){
            fscanf(fl, "%s", line);
            float val = atof(line);

            indices[(i * 3) + j] = val;
        }
    }
}

static void prepara_variaveis(FILE *fl){
    char line[255];

    fscanf(fl, "%s", line);
    qtdVertices = atoi(line);

    fscanf(fl, "%s", line);
    incidencia = atoi(line);

    vertices = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    normais = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    indices = (GLubyte*) malloc( incidencia * 3 * sizeof(GLubyte) ); // allocate memory for array

    preencher_vertices(fl);
    preencher_indices(fl);
}

static void draw()
{
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 0, normais);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glPushMatrix();
    glTranslatef(-2, -2, 0);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
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

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(5,5);
    glutInitWindowSize(640,480);
    glutCreateWindow("Little Bunny");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);

    glClearColor(0,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
