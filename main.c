#include <windows.h>
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "DS.h"
#define _USE_MATH_DEFINES // for C


static int width = 400;
static int height = 400;

static int cellsSize = 20;

int refreshRate = 500;


int direction = 1; //1 up, 2 back, 3 left, 4 right


bool started = false;
List snakePos;

Grid grid[20][20];

Grid initialFood;


void randomFood()
{
    Grid tempFood;
    tempFood.x = rand() % 20;
    tempFood.y = rand() % 20;
    if( l_search(&snakePos, tempFood) == NULL)
    {
        initialFood = tempFood;
    }
    else
    {
        randomFood();
    }
}
void food()
{
    glPolygonMode(GL_FRONT,GL_FILL);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex2f(initialFood.x, initialFood.y);
    glVertex2f(initialFood.x, initialFood.y+1);
    glVertex2f(initialFood.x+1, initialFood.y+1);
    glVertex2f(initialFood.x+1, initialFood.y);
    glEnd();
}
void snake(List *snake)
{
    struct Elm *temp;
    temp = snake->head;
    Grid tempGrid = temp->x;
    switch(direction)
    {
    case 1:
        printf("UP\n");

        tempGrid.y++;
        l_push_front(snake, tempGrid);
        break;
    case 2:
        printf("DOWN\n");
        printf("UP\n");
        tempGrid.y--;
        l_push_front(snake, tempGrid);
        break;
    case 3:
        printf("LEFT\n");
        printf("UP\n");
        tempGrid.x--;
        l_push_front(snake, tempGrid);
        break;
    case 4:
        printf("RIGHT\n");
        printf("UP\n");
        tempGrid.x++;
        l_push_front(snake, tempGrid);
        break;
    }



    glPolygonMode(GL_FRONT,GL_FILL);
    glColor3f(1,1,1);

    do
    {
        printf("%f here\n", temp->x.x);
        glBegin(GL_QUADS);
        glVertex2f(temp->x.x,temp->x.y);
        glVertex2f(temp->x.x,temp->x.y+1);
        glVertex2f(temp->x.x+1,temp->x.y+1);
        glVertex2f(temp->x.x+1,temp->x.y);
        glEnd();
        temp=temp->next;
        glBegin(GL_QUADS);
        glVertex2f(temp->x.x,temp->x.y);
        glVertex2f(temp->x.x,temp->x.y+1);
        glVertex2f(temp->x.x+1,temp->x.y+1);
        glVertex2f(temp->x.x+1,temp->x.y);
        glEnd();
    }
    while(temp->next != NULL);

    if(temp->next == NULL)
    {
        printf("null!\n");
    }

    tempGrid = snake->head->x;

    printf("%f2here\n", tempGrid.x);
    if(tempGrid.x < 0 || tempGrid.y < 0 || tempGrid.x > 20|| tempGrid.y > 20)
    {
        exit(0);
    }

    if( l_search_noHead(&snakePos, tempGrid) == NULL)
    {
        printf("free!");
    }
    else
    {
        exit(0);
    }

    if(!(tempGrid.x == initialFood.x && tempGrid.y == initialFood.y))
    {
        l_pop_back(snake);
    }
    else
    {
        randomFood();
    }


}
void start()
{
    started = true;
    for (int i =0 ; i < 20; i++)
    {
        for (int j =0; j <20 ; j++)
        {
            glBegin(GL_LINE_LOOP);
            glVertex2f(grid[i][j].x, grid[i][j].y);
            glVertex2f(grid[i][j].x, grid[i][j].y+1);
            glVertex2f(grid[i][j].x+1, grid[i][j].y+1);
            glVertex2f(grid[i][j].x+1, grid[i][j].y);
            glEnd();
        }
    }

    glPushMatrix();
    snake(&snakePos);
    glPopMatrix();
    glPushMatrix();
    glPopMatrix();

    food();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glLineWidth(2);
    glPointSize(10);

    if(!started)
    {

        glPushMatrix();
        glPolygonMode(GL_FRONT,GL_FILL);
        glColor3f(0,1,0);
        glBegin(GL_QUADS);
        glVertex2f(2,9);
        glVertex2f(2,11);
        glVertex2f(5,11);
        glVertex2f(5,9);
        glEnd();
        glColor3f(1,1,0);
        glBegin(GL_QUADS);
        glVertex2f(8.5,9);
        glVertex2f(8.5,11);
        glVertex2f(11.5,11);
        glVertex2f(11.5,9);
        glEnd();
        glColor3f(1,0,0);
        glBegin(GL_QUADS);
        glVertex2f(15,9);
        glVertex2f(15,11);
        glVertex2f(18,11);
        glVertex2f(18,9);
        glEnd();
        glPopMatrix();
    }
    else
    {
        start();
    }




    glutSwapBuffers();
}


void specialKey(int key, int x, int y)
{
    switch(key)
    {
    case  GLUT_KEY_UP:
        if(direction==2)
        {
            break;
        }
        direction = 1;
        break;
    case GLUT_KEY_DOWN:
        if(direction==1)
        {
            break;
        }
        direction = 2;
        break;
    case GLUT_KEY_LEFT:
        if(direction==4)
        {
            break;
        }
        direction = 3;
        break;
    case GLUT_KEY_RIGHT:
        if(direction==3)
        {
            break;
        }
        direction = 4;
        break;

    }

}

void timer()

{
    glutPostRedisplay();
    glutTimerFunc(refreshRate, timer, 0);
}
void keyboard(unsigned char key,int x, int y)
{
    switch(key)
    {
    case 'q':
        exit(0);
        break;
    }
}
void ChangeSize(GLsizei w, GLsizei h)
{
    // Set Viewport to window dimensions
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,20,0,20);
    glMatrixMode(GL_MODELVIEW);


}
mouse (int button, int state,int x, int y)
{



    if(button == GLUT_LEFT_BUTTON)
    {
        if(!started)
        {
            printf("%d-%d\n", x,y);
            if(y > 9*20 && y < 11*20)
            {
                if(x < 5*20 && x > 2*20)
                {
                    refreshRate = 500;
                    started = true;

                }
                else if(x > 8.5*20 && x < 11.5*20)
                {
                    refreshRate = 300;
                    started = true;
                }
                else if(x > 15*20 && x < 18*20)
                {
                    refreshRate = 100;
                    started = true;
                }
            }
        }
    }

}

int main(int argc, char* argv[])
{
    MessageBox(0, "Snake game\n Nogoon - Amarhan \n Shar - Engiin \n Ulaan - Hetsuu \nEnehuu togloom n input huleehgui tul zahaar yavahdaa bolgoomjlooroi! \nSumnii tovchluuraar mogoigoo udirdaarai", "Introduction", 0);
    int cellOffsetX = 0;
    int cellOffsetY = 0;

    for(int i = 0; i < 20; i++)
    {


        for(int j = 0; j < 20; j++)
        {
            grid[i][j].x = cellOffsetX;
            grid[i][j].y = cellOffsetY;
            cellOffsetX += 1;
        }
        cellOffsetY+=1;
        cellOffsetX = 0;
    }

    for(int i =0; i<20; i++)
    {
        for(int j =0; j<20; j++)
        {
            printf("%f and %f\n", grid[i][j].x, grid[i][j].y);
        }
    }
    Grid initialSnakePos;
    initialSnakePos.x = 10;
    initialSnakePos.y = 10;
    l_push_back(&snakePos, initialSnakePos);
    initialSnakePos.y = 9;
    l_push_back(&snakePos, initialSnakePos);
    initialSnakePos.y = 8;
    l_push_back(&snakePos, initialSnakePos);
    randomFood();
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Snake");
    glutSpecialFunc(specialKey);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(500, timer, 0);
    glClearColor(0, 0, 0, 1);
    glutMainLoop();

    return EXIT_SUCCESS;
}
