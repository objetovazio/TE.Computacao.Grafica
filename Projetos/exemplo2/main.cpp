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
#include <GL/glut.h>
#endif


#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

struct Camera
{
    glm::vec3 pos; // Posição da camera
    glm::vec3 dir; // Direlçao da camera
    glm::vec3 up; // Direlçao da camera
    float angularSpeed;
    float speed; // Velocidade da camera
};

Camera cam;

static int slices = 16;
static int stacks = 16;
int flovy = 60;
float arx = 0;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    arx = ar;

    glViewport(0, 0, 0, height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(flovy, ar, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}



static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glLoadIdentity();
    //gluLookAt(0,0,0.001, 0,0,-1, 0,1,0);
    glm::vec3 center = cam.pos + cam.dir;
    gluLookAt(cam.pos.x, cam.pos.y, cam.pos.z,
              center.x, center.y, center.z,
              cam.up.x, cam.up.y, cam.up.z);

    glPushMatrix();
    glTranslated(-2.4,1.2,-10);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    glm::mat4 rotUp;
    glm::vec4 newDir;

    switch (key)
    {
    case 's':
        cam.speed *= 1.1;
        printf("%f ", cam.speed);
        break;
    case 'x':
        cam.speed *= 0.9;
        printf("%f ", cam.speed);
        break;

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
    case 'a':
    case 'A':
        flovy += 15;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(flovy, arx, 2.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
        break;
    case 'z':
    case 'Z':
        flovy -= 15;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(flovy, arx, 2.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
        break;

    case '8':
        cam.pos  = cam.pos - cam.speed * cam.up;
        break;
    case '2':
        cam.pos  = cam.pos + cam.speed * cam.up;
        break;
    case '4':
        rotUp = glm::rotate(glm::mat4(1.0), cam.angularSpeed, cam.up);
        newDir = rotUp * glm::vec4(cam.dir, 1.0);
        cam.dir = newDir;
        break;
    case '6':
        rotUp = glm::rotate(glm::mat4(1.0), -cam.angularSpeed, cam.up);
        newDir = rotUp * glm::vec4(cam.dir, 1.0);
        cam.dir = newDir;
        break;

    }

    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    glm::vec3 side = glm::cross(cam.dir, cam.up);

    switch (key)
    {
    case GLUT_KEY_UP:
        cam.pos  = cam.pos + cam.speed * cam.dir;
        break;
    case GLUT_KEY_DOWN:
        cam.pos  = cam.pos - cam.speed * cam.dir;
        break;
    case GLUT_KEY_LEFT:
        cam.pos  = cam.pos - cam.speed * side;
        break;
    case GLUT_KEY_RIGHT:
        cam.pos  = cam.pos + cam.speed * side;
        break;
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
const GLfloat high_shininess[] = { 50.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
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

    cam.pos = glm::vec3(0, 0, 0);
    cam.dir = glm::vec3(0, 0, -1);
    cam.up = glm::vec3(0, 1, 0);
    cam.speed = 1;
    cam.angularSpeed = 0.1;

    glutMainLoop();

    return EXIT_SUCCESS;
}
