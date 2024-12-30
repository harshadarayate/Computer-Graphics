#include <stdio.h>
#include <GL/glut.h>

int centerX, centerY, radius;

// Function to plot points in all octants
void plotCirclePoints(int x, int y) {
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

// Midpoint Circle Drawing Algorithm
void drawCircle() {
    int x = 0;
    int y = radius;
    int p = 1 - radius; // Initial decision parameter

    plotCirclePoints(x, y); // Plot initial point

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1; // Midpoint is inside the circle
        } else {
            y--;
            p += 2 * (x - y) + 1; // Midpoint is outside the circle
        }
        plotCirclePoints(x, y); // Plot points in all octants
    }
}

// Initialization function
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glColor3f(0.0f, 0.0f, 0.0f);      // Set point color to black
    glPointSize(1.0);                 // Set point size
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); // Set the coordinate system
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    drawCircle();                 // Draw the circle
    glFlush();                    // Render now
}

int main(int argc, char** argv) {
    printf("Enter the coordinates of the center:\n");
    printf("X-coordinate: ");
    scanf("%d", &centerX);
    printf("Y-coordinate: ");
    scanf("%d", &centerY);
    printf("Enter radius: ");
    scanf("%d", &radius);

    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode
    glutInitWindowSize(640, 480);                   // Set window size
    glutInitWindowPosition(100, 150);               // Set window position
    glutCreateWindow("Midpoint Circle Drawing");     // Create window with title

    init();                                         // Call initialization function
    glutDisplayFunc(display);                       // Register display function

    glutMainLoop();                                 // Enter the GLUT event loop
    return 0;
}
