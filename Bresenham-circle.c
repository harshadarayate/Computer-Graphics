#include <stdio.h>
#include <GL/glut.h>


int centerX = 200;
int centerY = 300;

// Function to plot points in all octants of the circle
void drawCirclePoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(centerX + x, centerY + y);
    glVertex2i(centerX - x, centerY + y);
    glVertex2i(centerX + x, centerY - y);
    glVertex2i(centerX - x, centerY - y);
    glVertex2i(centerX + y, centerY + x);
    glVertex2i(centerX - y, centerY + x);
    glVertex2i(centerX + y, centerY - x);
    glVertex2i(centerX - y, centerY - x);
    glEnd();
}

// Bresenham's Circle Drawing Algorithm
void bresenhamCircle(int radius) {
    int x = 0;
    int y = radius;
    int decisionParam = 1 - radius; // Initial decision parameter

    drawCirclePoints(x, y); // Draw the initial points

    while (x < y) {
        x++;
        if (decisionParam < 0) {
            decisionParam += 2 * x + 1; // Mid-point is inside the circle
        } else {
            y--;
            decisionParam += 2 * (x - y) + 1; // Mid-point is outside the circle
        }
        drawCirclePoints(x, y); // Draw points for all octants
    }
}

// Display function to render the circle
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    int radius = 100; // Set the radius of the circle
    bresenhamCircle(radius); // Draw the circle

    glFlush(); 
}

// Initialization function to set up OpenGL settings
void initialize() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set background color to white
    glColor3f(0.0f, 0.0f, 0.0f); // Set drawing color to black
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); // Define the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(640, 480); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Bresenham's Circle Drawing"); // Create window with title

    initialize(); // Call initialization function
    glutDisplayFunc(display); // Register display callback

    glutMainLoop(); // Enter the GLUT event loop
    return 0;
}
