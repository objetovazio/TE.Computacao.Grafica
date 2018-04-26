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
const GLfloat high_shininess[] = { 50.0f };



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
    char line[255];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    glTranslated(0, 0, -3);

    /*glBegin(GL_TRIANGLES);
        glVertex3f(-3, 0, 0);
        glVertex3f(0, 3, 0);
        glVertex3f(3, 0, 0);
    glEnd();*/

    int i = 0;
    while(i < incidencia){
        glBegin(GL_TRIANGLES);
            for(int j = 0; j < 9; j += 3){
                glNormal3f(normais[(indices[i] * 3) + j], normais[(indices[i] * 3) + j + 1], normais[(indices[i] * 3) + j + 2]);
                glVertex3f(vertices[(indices[i] * 3) + j], vertices[(indices[i] * 3) + j + 1], vertices[(indices[i] * 3) + j + 2]);
            }
        glEnd();

   /*    printf("vertice: %.5f %.5f %.5f normais: %.5f %.5f %.5f\n", vertices[indices[i]], vertices[indices[i] + 1], vertices[indices[i] + 2], normais[indices[i]], normais[indices[i] + 1], normais[indices[i] + 2]);

        printf("vertice: %.5f %.5f %.5f normais: %.5f %.5f %.5f\n", vertices[i], vertices[i + 1], vertices[i + 2], normais[i], normais[i + 1], normais[i + 2]);

        scanf("%s", &line);*/

        i += 9;
    }

    glutSwapBuffers();
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

    vertices = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    normais = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    indices = (GLuint*) malloc( incidencia * 3 * sizeof(GLuint) ); // allocate memory for array

    preencher_vertices(fl);
    preencher_indices(fl);
}

static void draw()
{
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 0, normais);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glPushMatrix();
    glTranslatef(0, 0, -6);

    glDrawElements(GL_TRIANGLES, incidencia*3, GL_UNSIGNED_INT, indices);

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

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(5,5);
    glutInitWindowSize(640,480);
    glutCreateWindow("Little Bunny");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);

    glClearColor(1,1,1,1);
   /* glEnable(GL_CULL_FACE);
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
*/
    glutMainLoop();


    return EXIT_SUCCESS;
}
