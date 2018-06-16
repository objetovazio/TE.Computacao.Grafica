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
#include <vector>
#include <time.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "Camera.h"
#include "SceneControl.h"
#include "SceneObject.h"

SceneControl *Sc = new SceneControl();
Camera *camera = new Camera();
std::vector<SceneObject*> *listSceneObject = new std::vector<SceneObject*>;
std::vector<FILE*> *fileList = new std::vector<FILE*>;

bool isGlBegin = true;
int wid = 800;
int hei = 600;
bool isJumping = false;
double jumpStart;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 50.0f };

double T = 0, t1 = 0, t2 = 0;


void TurnLight(bool On)
{
    if(On)
    {
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
    }
    else
    {
        glDisable(GL_LIGHT0);
        glDisable(GL_NORMALIZE);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);
    }
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
    //glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);

    gluPerspective(60, ar, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void selectionMode()
{
    TurnLight(false);

    GLfloat resposta[4];
    GLint viewportCores[4];

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(camera->Getpos().x, camera->Getpos().y, camera->Getpos().z,
              camera->GetCenter().x, camera->GetCenter().y, camera->GetCenter().z,
              camera->Getup().x, camera->Getup().y, camera->Getup().z);

    for(int i = 0; i < listSceneObject->size(); i++)
    {
        SceneObject* so = listSceneObject->at(i);
        so->draw(true);
    }

    glGetIntegerv(GL_VIEWPORT, viewportCores);

    glReadPixels(Sc->GetMousePosition().x, viewportCores[3] - Sc->GetMousePosition().y, 1, 1, GL_RGBA, GL_FLOAT, &resposta);

    glm::vec3 cores = glm::vec3(resposta[0], resposta[1], resposta[2]);

    for(int i = 0; i < listSceneObject->size(); i++)
    {
        SceneObject* so = listSceneObject->at(i);
        bool isEquals = so->compareColor(cores);

        if(isEquals)
        {
            Sc->SetPivot(so);
            camera->UpdateDirection(Sc->GetPivot()->GetPosition());
            break;
        }
    }

    TurnLight(true);
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

    if(Sc->GetSceneMode() == 1 && Sc->GetMadeSelection())
    {
        selectionMode();
        Sc->SetMadeSelection(false);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glLoadIdentity();
    gluLookAt(camera->Getpos().x, camera->Getpos().y, camera->Getpos().z,
              camera->GetCenter().x, camera->GetCenter().y, camera->GetCenter().z,
              camera->Getup().x, camera->Getup().y, camera->Getup().z);


    for(int i = 0; i < listSceneObject->size(); i++)
    {
        SceneObject* so = listSceneObject->at(i);
        so->draw(false);
    }


    sprintf(fpsx, "%.1f", fps);
    strcat(showing, fpsx);
    printtext(10, 10, wid, hei, showing);

    char angularSpeedMouse[100] = "Angular Speed: ";
    char asmValue[5];

    sprintf(asmValue, "%.3f", camera->GetangularSpeed());
    strcat(angularSpeedMouse, asmValue);
    printtext(10, 580, wid, hei, angularSpeedMouse);


    glutSwapBuffers();
    glutPostRedisplay();
}

static void key(unsigned char key, int x1, int y1)
{
    switch (key)
    {
    case 'q':
        exit(0);
        break;
    case 'a':
        if(Sc->GetSceneMode() == 2)
        {
            camera->ZoomIn(Sc->GetPivot());
        }
        else camera->MoveUp();
        break;
    case 'z':
        if(Sc->GetSceneMode() == 2)
        {
            camera->ZoomOut(Sc->GetPivot());
        }
        else camera->MoveDown();
        break;
    case '1':
        Sc->SetSceneMode(1);
        break;
    case '2':
        Sc->SetSceneMode(2);
        break;
    case '3':
        Sc->SetSceneMode(3);
        break;
    case '+':
        camera->IncrementAngularSpeed();
        break;
    case '-':
        camera->DecrementAngularSpeed();
        break;
    }


    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    switch (key)
    {
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

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            if(Sc->GetSceneMode() == 3)
            {
                glm::vec3 mousePosition = glm::vec3(x, y, 0);
                Sc->SetMousePosition(mousePosition);
            }

            if(Sc->GetSceneMode() == 1)
            {
                glm::vec3 mousePosition = glm::vec3(x, y, 0);
                Sc->SetMousePosition(mousePosition);
                Sc->SetMadeSelection(true);
            }
        }
    }

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            //printf("O botão esquerdo do mouse foi solto");
        }
    }
}

void mouseMove(int x, int y)
{
    if(Sc->GetSceneMode() != 1)
    {
        int diferencaX, diferencaY;

        diferencaX = x - Sc->GetMousePosition().x;
        diferencaY = y - Sc->GetMousePosition().y;

        if(Sc->GetSceneMode() == 2)
        {
            camera->UpdateDirection(Sc->GetPivot()->GetPosition());
        }

        camera->TurnMouseX(diferencaX);
        camera->TurnMouseY(diferencaY);

        if (Sc->GetSceneMode() == 2)
        {
            camera->UpdatePosition(Sc->GetPivot()->GetPosition());
        }

        glm::vec3 mouseP = glm::vec3(x, y, 0);
        Sc->SetMousePosition(mouseP);
        glutPostRedisplay();
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

    if(fl == NULL)
    {
        printf("Error!");
        exit(1);
    }

    fileList->push_back(fl);
}

/* Recupera Valores Vertices */
static void preencher_vertices(FILE* fl, GLfloat* vertices, GLfloat* normais, int qtdVertices,
                               glm::vec3 &maiorCoordenada, glm::vec3 &menorCoordenada)
{
    char line[255];

    maiorCoordenada = glm::vec3(vertices[0], vertices[1], vertices[2]);
    menorCoordenada = glm::vec3(1000, 1000, 1000);

    for(int i = 0; i < qtdVertices; i++)
    {
        fscanf(fl, "%s", line);
        int id = atoi(line);

        //1 v1 v2 v3 n1 n2 n3

        for(int j = 0; j < 3; j++)
        {
            fscanf(fl, "%s", line);
            float val = atof(line);

            vertices[(i * 3) + j] = val;

            switch(j)
            {
            case 0:
                if(val > maiorCoordenada.x)
                {
                    maiorCoordenada.x = val;
                }
                if(val <= menorCoordenada.x)
                {
                    menorCoordenada.x = val;
                }
                break;
            case 1:
                if(val > maiorCoordenada.y)
                {
                    maiorCoordenada.y = val;
                }
                if(val <= menorCoordenada.y)
                {
                    menorCoordenada.y = val;
                }
                break;
            case 2:
                if(val > maiorCoordenada.z)
                {
                    maiorCoordenada.z = val;
                }

                if(val <= menorCoordenada.z)
                {
                    menorCoordenada.z = val;
                }
                break;

            }
        }

        for(int j = 0; j < 3; j++)
        {
            fscanf(fl, "%s", line);
            float val = atof(line);

            normais[(i * 3) + j] = val;
        }
    }
}

// Recupera indices
static void preencher_indices(FILE* fl, GLuint* indices, int incidencia)
{
    char line[255];

    for(int i = 0; i < incidencia; i++)
    {
        fscanf(fl, "%s", line);
        int id = atoi(line);

        for(int j = 0; j < 3; j++)
        {
            fscanf(fl, "%s", line);
            int val = atoi(line);

            indices[(i * 3) + j] = val;
        }
    }
}

static SceneObject* prepara_variaveis(FILE *fl, glm::vec3 posicao)
{
    char line[255];

    fscanf(fl, "%s", line);
    int qtdVertices = atoi(line);

    fscanf(fl, "%s", line);
    int incidencia = atoi(line);

    GLfloat* vertices = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    GLfloat* normais = (GLfloat*) malloc( qtdVertices * 3 * sizeof(GLfloat) ); // allocate memory for array
    GLuint* indices = (GLuint*) malloc( incidencia * 3 * sizeof(GLuint) ); // allocate memory for array
    glm::vec3 maiorCoordenada = glm::vec3(0, 0, 0);
    glm::vec3 menorCoordenada = glm::vec3(0, 0, 0);;

    preencher_vertices(fl, vertices, normais, qtdVertices, maiorCoordenada, menorCoordenada);
    preencher_indices(fl, indices, incidencia);

    //glm::vec3 posicao = glm::vec3(0, -1, 5);
    glm::vec3 cor = Sc->GetNewSelectColor();
    glm::vec3 corSelect = Sc->GetNewSelectColor();

    SceneObject *so =
        new SceneObject(posicao, cor, corSelect, vertices, normais, indices, incidencia, qtdVertices, maiorCoordenada - menorCoordenada);

    listSceneObject->push_back(so);
}

static void StartCamera()
{
    camera->Setpos(glm::vec3(0, 1, 0));
    camera->Setdir(glm::vec3(0, 0, 1));
    camera->Setup(glm::vec3(0, 1, 0));
    camera->Setspeed(0.5);
    camera->SetangularSpeed(0.005);
}

/* Program entry point */
int main(int argc, char *argv[])
{
    Sc->SetSceneMode(3); //Fly

    openFile("../bunny.msh");
    openFile("../chair_chesterfield.msh");
    openFile("../chair_chesterfield.msh");
    openFile("../bunny.msh");
    //openFile("../DeLorean.msh");

    StartCamera();

    for(int i = 0; i < fileList->size(); i++)
    {
        glm::vec3 posicao = glm::vec3(rand() % 19 + (-9), 0, rand() % 10 + 1);
        prepara_variaveis(fileList->at(i), posicao);
        fclose(fileList->at(i));
    }

    Sc->SetPivot(listSceneObject->at(0));
    Sc->SetMadeSelection(false);

    glutInit(&argc, argv);
    glutInitWindowSize(wid,hei);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Little Bunny");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
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

    TurnLight(true);

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
