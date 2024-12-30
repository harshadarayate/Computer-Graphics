#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double X1, Y1, X2, Y2;

// Function to round float values
float round_value(float v) {
    return floor(v + 0.5);
}

// DDA Line Drawing Algorithm
void LineDDA(void) {
    double dx = (X2 - X1);
    double dy = (Y2 - Y1);
    double steps;
    float xInc, yInc, x = X1, y = Y1;

    // Determine the number of steps needed
    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    
    // Calculate increments for x and y
    xInc = dx / (float)steps;
    yInc = dy / (float)steps;

    // Clear buffers to preset values
    glClear(GL_COLOR_BUFFER_BIT);

    // Plot the points
    glBegin(GL_POINTS);
    glVertex2d(x, y);  // Plot the first point

    for (int k = 0; k < steps; k++) {
        x += xInc;
        y += yInc;
        glVertex2d(round_value(x), round_value(y));  // Plot each intermediate point
    }
    
    glEnd();
    glFlush();  // Render now
}

// Initialization function
void Init() {
    glClearColor(1.0, 1.0, 1.0, 0);  // Set clear color to white
    glColor3f(0.0, 0.0, 0.0);         // Set fill color to black
    gluOrtho2D(0, 640, 0, 480);       // Set the coordinate system
}

int main(int argc, char** argv) {
    printf("Enter two end points of the line to be drawn:\n");
    
    printf("Enter Point1 (X1 Y1): ");
    scanf("%lf %lf", &X1, &Y1);
    
    printf("Enter Point2 (X2 Y2): ");
    scanf("%lf %lf", &X2, &Y2);

    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode
    glutInitWindowPosition(100, 100);               // Set window position
    glutInitWindowSize(640, 480);                   // Set window size
    glutCreateWindow("DDA Line Drawing");           // Create window with title

    Init();                                         // Call initialization function
    glutDisplayFunc(LineDDA);                       // Register display function

    glutMainLoop();                                 // Enter the GLUT event loop
    return 0;
}
