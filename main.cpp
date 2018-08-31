
/**************************************************
 Name: Xiaoning Wang
 Project2
 Date: August 2 2018
 Class: CS 368
 Instructor:  Zhigang Xiang
 *************************************************/

#include <GLUT/GLUT.h>

/* set the window's width and height */
int width = 800, height = 600;

/* r, g, b are the arguments for glColor3ub(r,g,b), range [0,255];
 * recX and recY are the x and y coordinates on the rectangle.
 * Rx,Ry, Gx, Gy, Bx,By are the x and y coordinates on R,G,B slider bar respectively.
*/
int r=127,g=127,b=127,recX,recY,Rx=100,Ry=307.5,Gx=230,Gy=307.5,Bx=360,By=307.5;

/* Display 3-digit numbers on top of the R,G,B slider bar. convert the r, g, b value from int to char.*/
char r1, r2, r3, g1, g2, g3, b1, b2, b3;

/* Set the flags.
 * highLightR, highLightG, highLightB are for indicating the cursor are in the region that we can move the bar.
 * setR, setG, setB are for controling the slider bar.
 * setLeftColor, setRightColor are for set left and right color of the rectangle.
 * readRectangle is for reading pixel value on the ractangle.
 */
bool highLightR = false, highLightG = false, highLightB = false,setR=false,setG = false, setB = false, setLeftColor = false, setRightColor = false, readRectangle = false;

void draw_slider(void){
    glBegin(GL_LINES); // draw a line for the slider
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(100, 180); // set y = 170 for the min(0) value of the bar.
    glVertex2f(100, 435);// 425 = 255(max adjust value) + 170 (y value of the min adjust);
    glEnd();
}

void draw_3_slider(void){
    for (int i = 0; i < 3 ; i ++){
        glPushMatrix();
        glTranslated(i*130,0,0); //draw 3 sliders with the value of x coordinate increment by 130 every time.
        draw_slider();
        glPopMatrix();
    }
    glFlush();
}

void draw_R_bar(void){
    if (highLightR || setR){
        glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(Rx - 15,Ry + 7.5);// the height of the handle is 15, in order to keep the pixle we select in the center of the handle, we set the y value of left bottom corner vertex  as y - 7.5.
        glVertex2f(Rx - 15,Ry - 7.5); // same reason for set the y value of the left top vertex to y + 7.5.
        glVertex2f(Rx + 15,Ry - 7.5);
        glVertex2f(Rx + 15,Ry + 7.5);
        glEnd();
    }else{
        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(Rx - 15,Ry - 7.5);// the height of the handle is 15, in order to keep the pixle we select in the center of the handle, we set the y value of left bottom corner vertex  as y - 7.5.
        glVertex2f(Rx - 15,Ry + 7.5); // same reason for set the y value of the left top vertex to y + 7.5.
        glVertex2f(Rx + 15,Ry + 7.5);
        glVertex2f(Rx + 15,Ry - 7.5);
        glEnd();
    }
}

void draw_G_bar(void){
    if (highLightG || setG){
        glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(Gx - 15,Gy - 7.5);// the height of the handle is 15, in order to keep the pixle we select in the center of the handle, we set the y value of left bottom corner vertex  as y - 7.5.
        glVertex2f(Gx - 15,Gy + 7.5); // same reason for set the y value of the left top vertex to y + 7.5.
        glVertex2f(Gx + 15,Gy + 7.5);
        glVertex2f(Gx + 15,Gy - 7.5);
        glEnd();
    }else{
        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(Gx - 15,Gy - 7.5);// the height of the handle is 15, in order to keep the pixle we select in the center of the handle, we set the y value of left bottom corner vertex  as y - 7.5.
        glVertex2f(Gx - 15,Gy + 7.5); // same reason for set the y value of the left top vertex to y + 7.5.
        glVertex2f(Gx + 15,Gy + 7.5);
        glVertex2f(Gx + 15,Gy - 7.5);
        glEnd();
    }
}

void draw_B_bar(void){
    if (highLightB || setB){
        glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(Bx - 15,By - 7.5);// the height of the handle is 15, in order to keep the pixle we select in the center of the handle, we1 set the y value of left bottom corner vertex  as y - 7.5.
        glVertex2f(Bx - 15,By + 7.5); // same reason for set the y value of the left top vertex to y + 7.5.
        glVertex2f(Bx + 15,By + 7.5);
        glVertex2f(Bx + 15,By - 7.5);
        glEnd();
    }else{
        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(Bx - 15,By - 7.5);// the height of the handle is 15, in order to keep the pixle we select in the center of the handle, we1 set the y value of left bottom corner vertex  as y - 7.5.
        glVertex2f(Bx - 15,By + 7.5); // same reason for set the y value of the left top vertex to y + 7.5.
        glVertex2f(Bx + 15,By + 7.5);
        glVertex2f(Bx + 15,By - 7.5);
        glEnd();
    }
}

void mouse (int button, int state, int x, int y){
    switch (button) {
        case GLUT_LEFT_BUTTON:
            
            if(state == GLUT_DOWN && (85 <= x) && (115>= x) && (164 <= y) && (419 >= y)){ // Make sure Ry is between 180 and 435, calculate y by height - 1 - 180, and height - 1 - 435.
                Rx = 100;
                Ry =  height - 1 - y; // (180 <= Ry <= 435)
                setR = true;
                glutPostRedisplay();
            } else
                setR = false;
            if ((state == GLUT_DOWN) && ((215 <= x) && (245>= x) && (164 <= y) && (419 >= y))){
                Gx = 230;
                Gy = height - 1 - y;
                setG = true;
                glutPostRedisplay();
            } else
                setG = false;
            if ((state == GLUT_DOWN)&& ((345 <= x) && (375>= x) && (164 <= y) && (419 >= y))){
                Bx = 360;
                By = height - 1 - y;
                setB = true;
                glutPostRedisplay();
            } else
                setB = false;
            
            /* select the color inside the rectangular region */
            if((state == GLUT_DOWN) && ((430 <= x) && (750>= x) && (419 <= y) && (459 >= y))){ // y value is converted to mouse y value.
                recX = x;
                recY = height - 1 - y;
                readRectangle = true;
                GLfloat pixels[3];
                glReadPixels(recX,recY, 1,1, GL_RGB,GL_FLOAT, &pixels);
                r = pixels[0]*255;//convert r value from float to int by multiply 255.
                Ry = r + 180;
                g = pixels[1]*255;
                Gy = g + 180;
                b = pixels[2]*255;
                By = b + 180;
                glutPostRedisplay();
            } else
                readRectangle = false;
    }
}

void passive(int mousex, int mousey){
    int x = mousex;
    int y = height - 1 - mousey;
    
    if ( (85 <= x) && (115>= x) && (Ry - 7.5 <= y) && (Ry + 7.5 >= y)){
        highLightR = true;
    }
    else if ( (215 <= x) && (245>= x) && (Gy - 7.5 <= y) && (Gy + 7.5 >= y)){
        highLightG = true;
    }
    else if ( (345 <= x) && (375>= x) && (By - 7.5 <= y) && (By + 7.5 >= y)){
        highLightB = true;
    }else
        highLightB = highLightG = highLightR = false;
    glutPostRedisplay();
    
}


void motion(int x, int y) { //y value is converted to mouseY value.
    if (setR &&(164 <= y) && (419 >= y) && (85 <= x) && (115>= x)){
        Rx = 100;
        Ry = height - 1 - y; // 180 <= Ry <= 435
        r = Ry - 180; // 0 <= r <= 255;
        glutPostRedisplay();
    }
    
    else if (setG &&(164 <= y) && (419 >= y)&& (215 <= x) && (245>= x)){
        Gx = 230;
        Gy = height - 1 - y;
        g = Gy - 180; // 0 <= g <= 255;
        glutPostRedisplay();
        
    }
    else if(setB && (164 <= y) && (419 >= y) && (345 <= x) && (375>= x)){
        Bx = 360;
        By = height - 1 - y;
        b = By - 180; //0 <= b <= 255.
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'l' : setLeftColor = ! setLeftColor;
            if (setLeftColor){
                setLeftColor = true;
            }
            else
                setLeftColor = false;
            break;
            
        case 'r' : setRightColor = ! setRightColor;
            if (setRightColor){
                setRightColor = true;
            }
            else
                setRightColor = false;
            break;
    }
    glutPostRedisplay();
}

void draw_square(void){
    glBegin(GL_POLYGON);
    glColor3ub(r,g,b);
    glVertex2i(480, 270);
    glVertex2i(700, 270);
    glVertex2i(700, 490);
    glVertex2i(480, 490);
    glEnd();
}

void draw_rectangle(void){
    if (setLeftColor){
        glBegin(GL_POLYGON);
        glColor3ub(r,g,b);
        glVertex2i(430, 140);
        glColor3ub(r,g,b);
        glVertex2i(430, 180);
        glColor3ub(0, 0, 0);
        glVertex2i(750,180);
        glColor3ub(0, 0, 0);
        glVertex2i(750,140);
        glEnd();
        
    }
    else if (setRightColor){
        glBegin(GL_POLYGON);
        glColor3ub(r, g, b);
        glVertex2i(750, 180);
        glColor3ub(r, g, b);
        glVertex2i(750, 140);
        glColor3ub(255, 255, 255);
        glVertex2i(430, 140);
        glColor3ub(255, 255, 255);
        glVertex2i(430, 180);
        glEnd();
    }
    else {
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2i(430, 140);
        glColor3ub(255, 255, 255);
        glVertex2i(430, 180);
        glColor3ub(0, 0, 0);
        glVertex2i(750, 180);
        glColor3ub(0, 0, 0);
        glVertex2i(750, 140);
        glEnd();
    }
}

/* Three convert{R,G,B}functions below convert r,g,v values to 3 chars respecrtively to display */
void convertR(int r){
    int num[3];
    for(int i=0;i<3; i++, r/=10)
    {
        num[i] = r % 10;
    }
    r1 = num[0] + '0';
    r2 = num[1] + '0';
    r3 = num[2] + '0';
}

void convertG(int g){
    int num[3];
    for(int i=0;i<3; i++, g/=10)
    {
        num[i] = g % 10;
    }
    g1 = num[0] + '0';
    g2 = num[1] + '0';
    g3 = num[2] + '0';
}

void convertB(int b){
    int num[3];
    for(int i=0;i<3; i++, b/=10)
    {
        num[i] = b % 10;
    }
    b1 = num[0] + '0';
    b2 = num[1] + '0';
    b3 = num[2] + '0';
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    draw_3_slider();
    draw_R_bar();
    draw_G_bar();
    draw_B_bar();
    draw_square();
    draw_rectangle();
    
    /*Display R slider Bar: Number on top and 'R' on bottom */
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(93, 140);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
    convertR(r);
    if (r3 == '0' && r2 == '0'){
        glRasterPos2i(93, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r1);
    }
    else if (r3 == '0' && r2 != '0'){
        glRasterPos2i(86, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r2);
        glRasterPos2i(98, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r1);
    }
    else if (r3 != '0'){
        glRasterPos2i(83, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r3);
        glRasterPos2i(95, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r2);
        glRasterPos2i(107, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r1);
    }
    
    /*Display G slider Bar: Number on top and 'G' on bottom */
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2i(222, 140);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
    convertG(g);
    if (g3 == '0' && g2 == '0'){
        glRasterPos2i(222, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g1);
    }
    else if (g3 == '0' && g2 != '0'){
        glRasterPos2i(215, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g2);
        glRasterPos2i(227, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g1);
    }
    else if (g3 != '0'){
        glRasterPos2i(210, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g3);
        glRasterPos2i(222, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g2);
        glRasterPos2i(234, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g1);
    }
    
    /*Display B slider Bar: Number on top and 'B' on bottom */
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2i(353, 140);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
    convertB(b);
    if (b3 == '0' && b2 == '0'){
        glRasterPos2i(353, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, b1);
    }
    else if (b3 == '0' && b2 != '0'){
        glRasterPos2i(348, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, b2);
        glRasterPos2i(360, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, b1);
    }
    else if (b3 != '0'){
        glRasterPos2i(341, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, b3);
        glRasterPos2i(353, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, b2);
        glRasterPos2i(365, 460);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, b1);
    }
    
    glEnd();
    glutSwapBuffers();//use GLUT_DOUBLE in glutinitDisplaymode for double buffer animation
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Color Mixer");
    glClearColor(0.75,0.75,0.75,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passive);
    glutMainLoop();
}






