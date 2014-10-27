/*
 * GL07BouncingBall.cpp: A ball bouncing inside the window
 */
//include <gl/glut.h>  // Also included gl.h, glu.h

/*



#include <GLUT/glut.h>
#include <math.h>     // Needed for sin, cos
#define PI 3.14159265f

// Global variables
char title[] = "Bouncing Ball (2D)";  // Windowed mode's title
int windowWidth  = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y

GLfloat ballRadius = 0.5f;   // Radius of the bouncing ball
GLfloat xPos = 0.0f;         // Ball's (x, y) position
GLfloat yPos = 0.0f;
GLfloat xPosMax, xPosMin, yPosMax, yPosMin; // Ball's (x, y) bounds
GLdouble xLeft, xRight, yBottom, yTop;      // Projection clipping area
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed = 0.007f;
int refreshMillis = 30;      // Refresh period in milliseconds

// Initialize OpenGL Graphics
void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}

// Callback handler for window re-paint event
void display() {
    glClear(GL_COLOR_BUFFER_BIT);    // Clear the color buffer
    
    glLoadIdentity();                // Reset model-view matrix
    glTranslatef(xPos, yPos, 0.0f);  // Translate to (xPos, yPos)
    // Use triangular segments to form a circle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue
    glVertex2f(0.0f, 0.0f);       // Center of circle
    int numSegments = 100;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
        glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
    glEnd();
    
    glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
    
    // Animation Control - compute the location for the next refresh
    xPos += xSpeed;
    yPos += ySpeed;
    // Check if the ball exceeds the edges
    if (xPos > xPosMax) {
        xPos = xPosMax;
        xSpeed = -xSpeed;
    } else if (xPos < xPosMin) {
        xPos = xPosMin;
        xSpeed = -xSpeed;
    }
    if (yPos > yPosMax) {
        yPos = yPosMax;
        ySpeed = -ySpeed;
    } else if (yPos < yPosMin) {
        yPos = yPosMin;
        ySpeed = -ySpeed;
    }
}

// Call back when the windows is re-sized.
void reshape(GLsizei weight, GLsizei height) {
    if (height == 0) height = 1;               // To prevent divide by 0
    GLfloat aspect = (GLfloat)weight / height; // Get aspect ratio
    
    // Set the viewport to cover the entire window
    glViewport(0, 0, weight, height);
    
    // Adjust the aspect ratio of clipping area to match the viewport
    glMatrixMode(GL_PROJECTION); // Select the Projection matrix
    glLoadIdentity();            // Reset
    if (weight <= height) {
        xLeft   = -1.0;
        xRight  = 1.0;
        yBottom = -1.0 / aspect;
        yTop    = 1.0 / aspect;
    } else {
        xLeft   = -1.0 * aspect;
        xRight  = 1.0 * aspect;
        yBottom = -1.0;
        yTop    = 1.0;
    }
    gluOrtho2D(xLeft, xRight, yBottom, yTop);
    xPosMin = xLeft + ballRadius;
    xPosMax = xRight - ballRadius;
    yPosMin = yBottom + ballRadius;
    yPosMax = yTop - ballRadius;
    
    // Reset the model-view matrix
    glMatrixMode(GL_MODELVIEW); // Select the model-view matrix
    glLoadIdentity();           // Reset
}

// Animation timer function
void Timer(int value) {
    glutPostRedisplay();    // Post a paint request to activate display()
    glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

// main function - GLUT run as a Console Application
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
    glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
    glutCreateWindow(title);      // Create window with given title
    glutDisplayFunc(display);     // Register callback handler for window re-paint
    glutReshapeFunc(reshape);     // Register callback handler for window re-shape
    glutTimerFunc(0, Timer, 0);   // First timer call immediately
    initGL();                     // Our own OpenGL initialization
    glutMainLoop();               // Enter event-processing loop
    return 0;
}
*/