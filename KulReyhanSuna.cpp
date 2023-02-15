/*********
   CTIS164 - Template Source Program
----------
STUDENT : Reyhan Suna Kul
SECTION : 04
HOMEWORK: 1
----------
PROBLEMS: I hope there is not any issue hocam :).
----------
ADDITIONAL FEATURES: When you press "n" program switch to day/night and clouds move by themselves, yet you can change its x coordinate by using left and right arrow keys.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  16// Period for the timer.

#define TIMER_PERIOD2  12 //period for cloud timer
#define TIMER_ON         1// 0:disable timer, 1:enable timer
#define TIMER_ON2         1// timer for clouds
#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false,night=true, activeTimer=true,cloudMode=false;
int  winWidth, winHeight,count=0,// Display the snowman when its clicked.
xS,yS, //Variebles to convert snowman's coordinates.
direction,// For up,down,right,left direction.

xC,yC,//Variebles to convert clouds' coordinates.
dirC; //Directions of clouds'. (left and right)

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}
void snowman() { // It is the complex shape of program.
    
    //Drawing circles of snowman
    glColor3f(1, 1, 1);
    circle(xS, yS, 90);

    glColor3f(1, 1, 1);
    circle(xS, yS+120, 50);

    //eyes of snowman
    glColor3f(0, 0, 0);
    circle(xS+20, yS+120, 5);

    glColor3f(0, 0, 0);
    circle(xS-20, yS+120, 5);

    //buttons of snowman
    glColor3f(0, 0, 0);
    circle(xS, yS+45, 5);
    glColor3f(0, 0, 0);
    circle(xS, yS+15, 5);
    glColor3f(0, 0, 0);
    circle(xS, yS-15, 5);

    //carrot nose of snowman
    glColor3f(0.956, 0.211, 0.145);
    glBegin(GL_TRIANGLES);
    glVertex2f(xS-5, yS+110);
    glVertex2f(xS+5, yS+110);
    glVertex2f(xS, yS+90);
    glEnd();

    //arms of snowman
    glColor3f(0.647, 0.211, 0.172);
    glLineWidth(3);
    glBegin(GL_LINES);

   
    glVertex2f(xS-88, yS+25);
    glVertex2f(xS-180, yS+50);

    glColor3f(0.647, 0.211, 0.172);
    glVertex2f(xS+88, yS+25);
    glVertex2f(xS+180, yS+50);
  
    //fingers of snowman

    glVertex2f(xS+180, yS+50);
    glVertex2f(xS+180, yS+70);

    glVertex2f(xS+180, yS+50);
    glVertex2f(xS+190, yS+65);

    glVertex2f(xS+180, yS+50);
    glVertex2f(xS+200, yS+55);

    glVertex2f(xS-180, yS+50);
    glVertex2f(xS-180, yS+70);


    glVertex2f(xS-180, yS+50);
    glVertex2f(xS-190, yS+65);

    glVertex2f(xS-180, yS+50);
    glVertex2f(xS-200, yS+55);
    glEnd();



 }

void clouds() { // On day mode there are clouds.
    //cloud1
    glColor3f(1, 1, 1);

    circle(xC+200, yC+300, 40);
    circle(xC+150, yC+300, 40);
    circle(xC+180, yC+280, 40);
    circle(xC+130, yC+280, 40);
   

//cloud2

    glColor3f(1, 1, 1);

    circle(xC-200, yC+300, 40);
    circle(xC-150, yC+300, 40);
    circle(xC-180, yC+280, 40);
    circle(xC-130, yC+280, 40);

}

void snowflake() { // For the background of the program I put some snowflakes.

    int i, k;
    glLineWidth(1);
    glBegin(GL_LINES);
  
    for (i = -550; i <= 550; i+=100) 
        for (k = 300; k >=-100; k-=100) {

            glColor3f(1, 1, 1);

            glVertex2f(i+5, k+5);
            glVertex2f(i-5, k-5);

            glVertex2f(i-5, k+5);
            glVertex2f(i+5, k-5);

            glColor3f(1,1,1);
            glVertex2f(i-5, k+0);
            glVertex2f(i+5, k+0);

            glVertex2f(i+0, k+5);
            glVertex2f(i, k-5);
        }
        
    glEnd();
}
void moon() { // The moon is on the background on night mode.
    glColor3f(0.964, 0.941, 0.298);
    circle(-510, 300, 50);

    glColor3f(0.019, 0.105, 0.380);
    circle(-480, 300, 50);
    glEnd();
}

void sun() { // The sun is on the background on day mode.
    glColor3f(0.921, 0.964, 0.172);
    circle(-510, 300, 50);

   
    glEnd();
}
void display() {
    glClearColor(0.019, 0.105, 0.380, 0);
    glClear(GL_COLOR_BUFFER_BIT);


    //extra feature-changing the sky color and background by pressing n so that the mode of day-night changes.
    if (night == true) {
        glColor3f(0.019, 0.105, 0.380); 
        glRectf(-600, 400, 600, -87);

        moon();
    }

    if(night==false){
        glColor3f(0.082, 0.772, 0.878);
        glRectf(-600, 400, 600, -150);
        sun();

        clouds();
    }
  
    //Snow layer of background.
    glColor3f(1, 0.941, 0.941);
    glRectf(-600, -150, 600, -600);

    //Information about the program.
    vprint(400, 370, GLUT_BITMAP_8_BY_13, "        Reyhan Suna KUL");
    vprint(380, 350, GLUT_BITMAP_8_BY_13, "              22002481");
    vprint(-590, 380, GLUT_BITMAP_8_BY_13, "MODE: "); 
    vprint(-590, 360, GLUT_BITMAP_8_BY_13, "DIRECTION: ");

    glColor3f(0.509, 0.270, 0.850);
    vprint(-230, -350, GLUT_BITMAP_9_BY_15, "Press");
    glColor3f(0.937, 0.423, 0.525);
    vprint(-230, -350, GLUT_BITMAP_9_BY_15, "      <F1> ");
    glColor3f(0.509, 0.270, 0.850);
    vprint(-230, -350, GLUT_BITMAP_9_BY_15, "           to switch the mode and ");
    glColor3f(0.937, 0.423, 0.525);
    vprint(-230, -350, GLUT_BITMAP_9_BY_15, "                                  Arrow Keys");
    glColor3f(0.509, 0.270, 0.850);
    vprint(-230, -350, GLUT_BITMAP_9_BY_15, "                                             to control the bird ");

    glColor3f(0.937, 0.423, 0.525);
    vprint(-230, -330, GLUT_BITMAP_9_BY_15, "Press 'n' to switch day/night ");


    switch (direction) {
    case 1:  vprint(-510, 360, GLUT_BITMAP_8_BY_13, "UP");
        break;
    case 2:
        vprint(-510, 360, GLUT_BITMAP_8_BY_13, "DOWN");
        break;
    case 3: vprint(-510, 360, GLUT_BITMAP_8_BY_13, "LEFT");
        break;
    case 4:vprint(-510, 360, GLUT_BITMAP_8_BY_13, "RIGHT");
        break;
    default: vprint(-510, 360, GLUT_BITMAP_8_BY_13, "NONE");
        
    }

    if(activeTimer==true) // By pressing <F1> it changes the mode of program (auto-manual).
        vprint(-550, 380, GLUT_BITMAP_8_BY_13, " AUTONOMOUS");
    else
    vprint(-550, 380, GLUT_BITMAP_8_BY_13, "  MANUAL");


    if (count == 0) { // It displays clicking message to see and relocate the snowman.
        glColor3f(0, 1, 1);
        vprint(-120, 50, GLUT_BITMAP_8_BY_13, "Click to see/relocate the Snowman ");
    }

    snowflake();

    if (count > 0) { // Clicking message will dissappear and snowman will appear when count>0.
        snowman();
    }
    
 
    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    if (key == 'n' || key == 'N') { //It changes the day-night mode by pressing "n".
        night = !night;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) { //It increases or decreases the x and y coordinates according to arrow keys.
    case GLUT_KEY_UP: 
        direction = 1;
        yS += 10;
        up = true; break;
    case GLUT_KEY_DOWN:
        yS-=10;
        direction = 2;     
        down = true;
        break;
    case GLUT_KEY_LEFT: 
        xS-=10;
        direction = 3;
      
        dirC = 3;
        left = true; break;
    case GLUT_KEY_RIGHT:
        xS+=10;
        direction = 4;
        dirC = 4;
       right = true; break;
    case GLUT_KEY_F1: //It changes the mode of program by pressing <F1>.
        activeTimer = !activeTimer;
    }
    

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{

    // Write your codes here.
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        count++;
        xS = x-WINDOW_WIDTH/2; //Converts to coordinates according to click location. (snowman)
        yS =WINDOW_HEIGHT/2- y;
      
        xC = x - WINDOW_WIDTH / 2; //Converts to coordinates according to click location. (clouds)
        yC = WINDOW_HEIGHT / 2 - y;
    }
   
 
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
   
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    if (activeTimer) {
        // Animate the snowman until it touches the edge of the window.
        switch (direction) {

        case 1:
            if (yS + 170 <= WINDOW_HEIGHT / 2)
                yS += 2;
            else direction = 2;          
            break;

        case 2: 
            if (yS - 90 >= -(WINDOW_HEIGHT / 2))
                yS -= 2;
            else
                direction = 1;
            break;

        case 3:
            if (xS - 200 >= -(WINDOW_WIDTH / 2))
                xS -= 2;
            else direction = 4;
            break;

        case 4:
            if (xS + 200 < WINDOW_WIDTH / 2)
                xS += 2;
            else direction = 3;
            break;
      
      }
        
    }
    
    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif
#if TIMER_ON2 == 1
void onTimer2(int s) {
    glutTimerFunc(TIMER_PERIOD2, onTimer2, 0);

    // Animate the clouds until it touches the edge of the window.

    if( count>0){

        switch (dirC) {

        case 3:
            if (xC + 220 < WINDOW_WIDTH / 2)
                xC++;
            else dirC = 4;
            break;
        case 4:
            if (xC - 220 >= -(WINDOW_WIDTH / 2))
                xC--;
            else dirC= 3;
        }
          
    }

    //to refresh the window it calls display() function
    glutPostRedisplay(); //display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Template File");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif
#if  TIMER_ON2 == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD2, onTimer2, 0);
#endif
    Init();

    glutMainLoop();
}