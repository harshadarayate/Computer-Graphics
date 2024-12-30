#include <GL/freeglut.h>
#include <stdio.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

// Define the triangle vertices (updated to ensure half is inside the clipping rectangle)
GLfloat vertices[][2] = {
    {100.0f, 400.0f}, // Vertex 1 (top vertex)
    {400.0f, 400.0f}, // Vertex 2 (top vertex)
    {250.0f, 200.0f}  // Vertex 3 (bottom vertex, inside clipping rectangle)
};

// Define the clipping rectangle
GLfloat clipRect[4][2] = {
    {150.0f, 150.0f}, // Bottom left corner
    {350.0f, 150.0f}, // Bottom right corner
    {350.0f, 350.0f}, // Top right corner
    {150.0f, 350.0f}  // Top left corner
};

// Function to check if a point is inside the clipping rectangle
int isInsideClipRect(GLfloat x, GLfloat y) {
    return (x >= clipRect[0][0] && x <= clipRect[1][0] && 
            y >= clipRect[0][1] && y <= clipRect[2][1]);
}

// Function to clip the triangle against the clipping rectangle
void clipTriangle() {
    GLfloat clippedVertices[3][2];
    int clippedCount = 0;

    for (int i = 0; i < 3; i++) {
        if (isInsideClipRect(vertices[i][0], vertices[i][1])) {
            clippedVertices[clippedCount][0] = vertices[i][0];
            clippedVertices[clippedCount][1] = vertices[i][1];
            clippedCount++;
        }
    }

    // If any vertex is inside, draw the clipped triangle
    if (clippedCount > 0) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < clippedCount; i++) {
            glVertex2fv(clippedVertices[i]);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping rectangle
    glColor3f(1.0, 1.0, 1.0); // White color for the rectangle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2fv(clipRect[i]);
    }
    glEnd();

    // Set color for the triangle
    glColor3f(1.0, 0.0, 0.0); // Red color for the triangle

    // Clip and draw the triangle
    clipTriangle();

    glFlush();
}

void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT); // Set up orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    glutCreateWindow("Clipping Half Triangle in Rectangular Window");

    initOpenGL();
    
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
