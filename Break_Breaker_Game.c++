#include<windows.h>

#include<stdio.h>

#include<iostream>

#include<GL/glut.h>

#include<string>

#include<sstream>



//follow this copied code





using namespace std;



float barX = 200, barY = 465, barWidth = 100, barheight = 7;

float ballX = 235, ballY = 430, ballWH = 10, ballVelX = 0.3, ballVelY = 0.3;

const int brickAmount = 100;   //no of bricks

int score = 0, chances = 3, previousScore = 0, highestScore = 0;

bool flag = true, flag2 = true;

// topleft corner is (0,0)

// barx and barY are the initial x and y coordinates of the bar

//barwidth and barheight are width and height respectively

// ballx and ballY are x and y coordinates of that ball

// ballVelx and ballVely are the velocities of ball in x and y directions resplecively.

struct bricks {

    float x;

    float y;

    float width;

    float height;

    bool isAlive = true;

};

bricks bricksArray[brickAmount];



void createBricks() {

    float brickX = 41, brickY = 50;

    for (int i = 0; i < brickAmount; i++) {

        if (brickX > 400) {    //instead of 400,any value greater than(396.6+1=397.6)

                               //and less than 397.6+39.66=437.26(rightmost coordinate)

            brickX = 41;

            brickY += 11;  // this is not same as brick height(10) ,so as to look them

            //separated by a gap of 1 y value

        }

        //for each of the 100 bricks

        bricksArray[i].x = brickX;  //initially i=0 ,so its a first brick,for that brick

        // x coordinate will be brickX=41

        bricksArray[i].y = brickY;  // for first brick ,y coordinate will be 50

        //for every next brick it will increment by 11

        bricksArray[i].width = 38.66;// width of brick is set to 38.66

        bricksArray[i].height = 10;  //height of brick is set to 10

        brickX += 39.66;  //it is not incremented by the width value (38.66)

        //this will create horizontal gap of 1 x value between every 2 adjacent bricks

        // to make them appear separate bricks

    }

    glColor3ub(0, 0, 255);

    //this function specifies the color in(R,G,B)format

    // 4 th parameter is alpha(for intensity) it is implicitly 1 for glcolo3ub

    // glcolor4ub function will take that argument explicitly

    // and ub represents it is unsigned byte

    glBegin(GL_QUADS);

    //The glBegin functions delimit the vertices that define a primitive or a

    //group of like primitives.

    //The glBegin function accepts a single argument that specifies which of ten primitives

    //the vertices compose.,here as we have to create bricks ,so we used Gl_QUADS to

    //draw rectangular bricks.

    //GL_QUADS:   Treats each group of four vertices as an independent quadrilateral.



    for (int i = 0; i < brickAmount; i++) {

        if (bricksArray[i].isAlive == true) {

            glVertex2f(bricksArray[i].x, bricksArray[i].y);

            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y);

            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y + bricksArray[i].height);

            glVertex2f(bricksArray[i].x, bricksArray[i].y + bricksArray[i].height);

        }//all the above 4 vertices will be given to GL_Quads functions for creating

        //rectangular bricks

    }

    glEnd();  //end of GL_begin

}



void print(int a) {

    glRasterPos2f(490, 40);
    // glRasterPos2f is used to print or displya the specific charactor or int in the 3D plane
    stringstream ss;
    // string stream is a data type used to read(read from a certain other data type) or display the curret stored value
    ss << a;

    string s = "Score: " + ss.str();

    int len = s.length();

    for (int i = 0; i < len; i++) {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        // glutBitmapCharacter is used to select the font of the char or int to be displayed  {(18) font size}
    }

    glRasterPos2f(490, 70);

    stringstream ss2;

    ss2 << chances;

    string chance = "Chances left: " + ss2.str();

    for (int i = 0; i < chance.length(); i++) {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, chance[i]);

    }

    glRasterPos2f(490, 100);

    stringstream ss3;

    ss3 << previousScore;

    string prevScore = "Previous score: " + ss3.str();

    for (int i = 0; i < prevScore.length(); i++) {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, prevScore[i]);

    }

    glRasterPos2f(490, 130);

    stringstream ss4;

    ss4 << highestScore;

    string highScore = "Highest score: " + ss4.str();

    for (int i = 0; i < highScore.length(); i++) {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, highScore[i]);

    }

    /*    string

        for(int i = 0; i < highScore.length(); i++){

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, highScore[i]);

        }*/

}



void message(bool a) {

    if (a == false) {

        glRasterPos2f(20, 400);
        // glRasterPos2f is used to print or displya the specific charactor or int in the 3D plane
        stringstream ss;

        ss << previousScore;

        string s = "Game over. Your score: " + ss.str() + ". Click to start new game.";

        int len = s.length();

        for (int i = 0; i < len; i++) {

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
            // glutBitmapCharacter is used to select he font of the char or int to be displayed
        }

    }

}



void completeMessage(bool a) {

    if (a == false) {

        glRasterPos2f(20, 400);

        stringstream ss;

        ss << score;

        string s = "STAGE COMPLETE. Your score: " + ss.str() + ". Click to start new game.";

        int len = s.length();

        for (int i = 0; i < len; i++) {

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);

        }

    }

}



void myDisplay(void) {

    glClear(GL_COLOR_BUFFER_BIT); //it clears the buffers currently use for color writing

    //buffer here refers to the region of memory where computer renders image frames

    glColor3f(0.0, 0.0, 0.0);

    //Bar

    glBegin(GL_QUADS);         // draws quadrilateral with following 4 vertices

    glColor3ub(255, 204, 102);//color for the bar

    glVertex2f(barX, barY);

    glVertex2f(barX + barWidth, barY);

    glVertex2f(barX + barWidth, barY + barheight);

    glVertex2f(barX, barY + barheight);

    glEnd();

    //Ball

    glBegin(GL_QUADS);

    glColor3ub(255, 0, 0);

    glVertex2f(ballX, ballY);

    glVertex2f(ballX + ballWH, ballY);

    glVertex2f(ballX + ballWH, ballY + ballWH);

    glVertex2f(ballX, ballY + ballWH);

    glEnd();



    //sidebar

    glBegin(GL_QUADS);

    glColor3ub(0, 0, 0);  //black color given to the sidebar (which separates game and menu)

    glVertex2f(480, 0);

    glVertex2f(480, 480);

    glVertex2f(485, 480);

    glVertex2f(485, 0);  //anticlockwisely assigned the vertices for forming quadrilateral

    glEnd();



    print(score);

    createBricks();   // call to the createBricks function

    message(flag);   // flag is of type boolean which can have 2 values ,either true or false

                    // it is initialised to true, and as per the assigned value to flag

                    // it will be calling that particular condition of message

    completeMessage(flag2);   //flag2 parmeter is again a boolean ,initialized to true



    glutSwapBuffers();   //it is the glut function that instructs computer that u are done

                        // with current frame and buffers should be swapped so that frame

                       // be displayed and so that u can begin working on next.

    //with double buffering ,2 buffers used,(front and back),back is one on which computer

    //is busy in rendering next frame.when rendering is done 2 buffers are swapped

    //this buffer ensures that u can only ever see fully rendered frames rather than

    //work in progress

}



void myInit(void) {

    glClearColor(1.0, 1.0, 1.0, 0.0);
    // use to clear  the color buffer the arguements are ( r,g,b,a)
    glColor3f(0.0f, 0.0f, 0.0f);
    // Sets the current color.
    glViewport(0, 0, 760, 480);
    // The glViewport function specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
    glPointSize(4.0);
    // glPointSize — specify the diameter of rasterized points
    glMatrixMode(GL_MODELVIEW);
    //The glMatrixMode function specifies which matrix is the current matrix
    glLoadIdentity();
    //glLoadIdentity — replace the current matrix with the identity matrix
    gluOrtho2D(0.0, 760.0, 480.0, 0.0);
    //gluOrtho2D — define a 2D orthographic projection matrix
}
}
/* checkcollission:In simple terms, when an object makes contact with another object, a collision occurs.
OpenGL uses various collision detection techniques to detect collisions.
A and the B represent to different objects and the x, y, w, and h stands for x pos, y pos, width, and height of that specific object.
This is based on the collision theory of objects .*/


bool checkCollision(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH) {

    if (aY + aH < bY) // collision will not take place if the following condition is true, with respect to overlapping height .

        return false;        // hence return false

    else if (aY > bY + bH)  // collision will not take place if the following condition is true, with respect to height .

        return false;      // hence return false

    else if (aX + aW < bX)     // collision will not take place if the following condition is true, with respect to  overlapping width  .

        return false;    // hence return false

    else if (aX > bX + bW)  // collision will not take place if the following condition is true, with respect to  overlapping width  .

        return false;  // hence return false.

    else  

        return true;   // if all above condition fail then collision will happen.hence return true

}



void moveBall() {

    if (score >= 1000) {

        ballVelX = 0.5;

        ballVelY = 0.5;

    }

    if (score >= 1000) {

        barX = 200;

        barY = 465;

        ballX = 235;

        ballY = 430;

        ballVelX = 0;

        ballVelY = 0;

        float brickX = 2, brickY = 2;

        for (int i = 0; i < brickAmount; i++) {

            if (brickX > 450) {

                brickX = 2;

                brickY += 11;

            }

            bricksArray[i].x = brickX;

            bricksArray[i].y = brickY;

            bricksArray[i].width = 38.66;

            bricksArray[i].height = 10;

            bricksArray[i].isAlive = true;

            brickX += 39.66;

        }

        previousScore = score;

        if (highestScore < score) {

            highestScore = score;

        }

        chances = 3;

        score = 0;

        flag2 = false;

        Sleep(3000);

        completeMessage(flag2);

    }

    else {

        ballX += ballVelX;

        for (int i = 0; i < brickAmount; i++) {

            if (bricksArray[i].isAlive == true) {

                if (checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true) {

                    ballVelX = -ballVelX;

                    bricksArray[i].isAlive = false;

                    score += 10;

                    break;

                }

            }

        }

        ballY -= ballVelY;

        for (int i = 0; i < brickAmount; i++) {

            if (bricksArray[i].isAlive == true) {

                if (checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true) {

                    ballVelY = -ballVelY;

                    bricksArray[i].isAlive = false;

                    score += 10;

                    break;

                }

            }

        }

        if (ballX < 0) {

            ballVelX = -ballVelX;

        }

        else if (ballX + ballWH > 480) {

            ballVelX = -ballVelX;

        }

        if (ballY < 0) {

            ballVelY = -ballVelY;

        }

        else if (ballY + ballWH > 480) {

            if (chances <= 1) {

                barX = 200;

                barY = 465;

                ballX = 235;

                ballY = 430;

                ballVelX = 0;

                ballVelY = 0;

                float brickX = 2, brickY = 2;

                for (int i = 0; i < brickAmount; i++) {

                    if (brickX > 450) {

                        brickX = 2;

                        brickY += 11;

                    }

                    bricksArray[i].x = brickX;

                    bricksArray[i].y = brickY;

                    bricksArray[i].width = 38.66;

                    bricksArray[i].height = 10;

                    bricksArray[i].isAlive = true;

                    brickX += 39.66;

                }

                previousScore = score;

                if (highestScore < score) {

                    highestScore = score;

                }

                chances = 3;

                score = 0;

                flag = false;

                Sleep(3000);

                message(flag);

            }

            else {

                chances--;

                ballX = 235;

                ballY = 430;

                if (ballVelY < 0) {

                    ballVelY = -ballVelY;

                }

                Sleep(3000);

            }

        }

        if (checkCollision(ballX, ballY, ballWH, ballWH, barX, barY, barWidth, barheight) == true) {

            ballVelY = -ballVelY;

        }

    }

    glutPostRedisplay();// //glutPostRedisplay marks the current window as needing to be redisplayed.

}



//glutKeyboardFunc sets the keyboard callback for the current window.

//When a user types into the window, each key press generating an ASCII character

//will generate a keyboard callback.

void keyboard(int key, int x, int y) {

    switch (key) {

    case GLUT_KEY_LEFT:

        barX -= 15;   //whenever left key is pressed , the ball shifts towards negative

                      // x axis by value 10

        if (barX < 0) {

            barX = 0;   //when bar reaches to leftmost window ,as it cannot go beyond it,

                        // it is initialised to 0

        }

        glutPostRedisplay();

        //glutPostRedisplay marks the current window as needing to be redisplayed.

        break;

    case GLUT_KEY_RIGHT:

        barX += 10;   // on pressing right key , bar moves towards positive x axis by 10

        if (barX + barWidth > 480) {  //if rightmost corner is reached

            barX = 480 - barWidth;  // as it cant go more towards right ,it is stopped at

                                    //at that position

        }

        glutPostRedisplay();// //glutPostRedisplay marks the current window as needing to be redisplayed.

        break;

    default:

        break;

    }

}



void mouse(int button, int state, int x, int y) { //glutMouseFunc sets the mouse callback for the current window

    switch (button) {

    case GLUT_LEFT_BUTTON:

        //state parameter is either GLUT_UP or GLUT_DOWN ,indicating the callback was due

        //to a release or press respectively.

        if (state == GLUT_DOWN) {   //whenever left button is "pressed"

            flag = true;

            if (ballVelX <= 0 && ballVelY <= 0) {//if velocity of ball is 0

                ballVelX = 0.3;

                ballVelY = 0.3;

            }

            glutIdleFunc(moveBall);

            //sets global idle callback to be func so a GLUT program can perform background

            //processing tasks or continuous animation when window system events are not being

            //recieved

        }

        break;

    default:

        break;

    }

}

// Reading part

int main(int argc, char** argv) {

    glutInit(&argc, argv); /*glutInit is used to initialize the GLUT library.
     "argc ":A pointer to the program's unmodified argc variable from main.
     Upon return, the value pointed to by argcp will be updated, because glutInit extracts
     any command line options intended for the GLUT library.
     "argv":The program's unmodified argv variable from main.
     Like argcp, the data for argv will be updated because glutInit extracts any command line options understood by the GLUT library.*/

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//glutInitDisplayMode sets the initial display mode.

    glutInitWindowSize(760, 480);//glutInitWindowPosition and   glutInitWindowSize set the initial window position and size respectively.

    glutInitWindowPosition(100, 150);

    glutCreateWindow("Brick Breaker ");

    glutDisplayFunc(myDisplay);//glutDisplayFunc sets the display callback for the current window.

    glutSpecialFunc(keyboard); //glutSpecialFunc sets the special keyboard callback for the current window

    glutMouseFunc(mouse);//glutMouseFunc sets the mouse callback for the current window.
    //When a user presses and releases mouse buttons in the window, each press and each release generates a mouse callback.

    myInit();

    glutMainLoop();//glutMainLoop enters the GLUT event processing loop.
    // This routine should be called at most once in a GLUT program. Once called, this routine will never return.
    //It will call as necessary any callbacks that have been registered.

}
void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
    glColor3f(0.0, 0.4, 0.2); // Set line segment color to green.
    glBegin(GL_LINES);
    glTranslatef(25.0, -10.0, 0.0);
    glVertex2i(180, 15); // Specify line-segment geometry.
    glVertex2i(10, 145);
    glEnd();
    glFlush(); // Process all OpenGL routines as quickly as possible.
}

