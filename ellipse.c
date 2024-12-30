#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int xc, yc, rx, ry; // Center coordinates and radii

// Function to plot points in all four quadrants
void plotEllipsePoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y); // Quadrant I
    glVertex2i(xc - x, yc + y); // Quadrant II
    glVertex2i(xc + x, yc - y); // Quadrant III
    glVertex2i(xc - x, yc - y); // Quadrant IV
    glEnd();
}

// Midpoint Ellipse Drawing Algorithm
void drawEllipse() {
    int x = 0;
    int y = ry;
    
    // Decision parameter for region 1
    float d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    float dx = 2 * ry * ry * x;
    float dy = 2 * rx * rx * y;

    // Region 1
    while (dx < dy) {
        plotEllipsePoints(x, y);
        if (d1 < 0) {
            d1 += dx + (ry * ry);
        } else {
            y--;
            dy -= 2 * rx * rx;
            d1 += dx - dy + (ry * ry);
        }
        x++;
        dx += 2 * ry * ry;
    }

    // Decision parameter for region 2
    float d2 = (ry * ry) * ((x + 0.5) * (x + 0.5)) + (rx * rx) * ((y - 1) * (y - 1)) - (rx * rx * ry * ry);

    // Region 2
    while (y >= 0) {
        plotEllipsePoints(x, y);
        if (d2 > 0) {
            y--;
            dy -= 2 * rx * rx;
            d2 += (rx * rx) - dy;
        } else {
            x++;
            dx += 2 * ry * ry;
            d2 += dx - (rx * rx);
            y--;
            dy -= 2 * rx * rx;
        }
    }
    
    glFlush(); // Render now
}

// Initialization function
void init() {
    glClearColor(1.0, 1.0, 1.0, 0); // Set clear color to white
    glColor3f(0.0, 0.0, 0.0);       // Set drawing color to black
    gluOrtho2D(0, 640, 0, 480);     // Set the coordinate system
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawEllipse(); // Call the ellipse drawing function
}

// Main function
int main(int argc, char** argv) {
    printf("Enter the center of the ellipse (xc yc): ");
    scanf("%d %d", &xc, &yc);
    
    printf("Enter the radii of the ellipse (rx ry): ");
    scanf("%d %d", &rx, &ry);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Ellipse Drawing Algorithm");

    init();
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
    return 0;
}