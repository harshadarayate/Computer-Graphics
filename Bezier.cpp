#include <GL/glut.h>
#include <iostream>

// Control points for the Bezier curve
GLfloat controlPoints[3][3] = {
    {-0.8f, -0.8f, 0.0f},  // Point 1
    {0.0f, 0.8f, 0.0f},    // Point 2
    {0.8f, -0.8f, 0.0f}    // Point 3
};

// Function to compute the Bezier curve points
void computeBezier(GLfloat t) {
    GLfloat x = (1 - t) * (1 - t) * controlPoints[0][0] + 2 * (1 - t) * t * controlPoints[1][0] + t * t * controlPoints[2][0];
    GLfloat y = (1 - t) * (1 - t) * controlPoints[0][1] + 2 * (1 - t) * t * controlPoints[1][1] + t * t * controlPoints[2][1];
    
    glVertex2f(x, y);
}

// Function to draw the Bezier curve
void drawBezierCurve() {
    glBegin(GL_LINE_STRIP);  // Draw a line strip to represent the Bezier curve
    for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
        computeBezier(t);
    }
    glEnd();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    
    glColor3f(1.0f, 0.0f, 0.0f);  // Set color to red
    drawBezierCurve();             // Draw the Bezier curve

    glColor3f(0.0f, 0.0f, 1.0f);  // Set color to blue
    glPointSize(5.0f);             // Set point size
    glBegin(GL_POINTS);            // Draw the control points
    for (int i = 0; i < 3; i++) {
        glVertex2fv(controlPoints[i]);
    }
    glEnd();

    glutSwapBuffers();  // Swap buffers for double buffering
}

// Function to initialize OpenGL
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Set background color to white
    glMatrixMode(GL_PROJECTION);            // Set projection matrix
    glLoadIdentity();                       // Reset projection matrix
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);  // Set orthographic view
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);                // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Set display mode
    glutInitWindowSize(600, 600);         // Set window size
    glutCreateWindow("Quadratic Bezier Curve");  // Create window

    initGL();                             // Initialize OpenGL settings
    glutDisplayFunc(display);             // Register display function
    
    glutMainLoop();                       // Enter GLUT main loop
    return 0;
}



