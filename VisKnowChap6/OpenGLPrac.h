// Methods I've created for convenience with OpenGL

#include <GL/glut.h>
#include <vector>

const int HORIZONTAL_SIZE = 920;
const int VERTICAL_SIZE = 680;

namespace GLprac {
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> GLintPoint >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    class GLintPoint {
    public:
        GLint x;
        GLint y;

        GLintPoint(GLint x, GLint y) {  // Constructor
            this->x = x;
            this->y = y;
        }
    };

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> GL6DimensionalPoint >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    class GL6DimensionalPoint {
    public:
        // Add getters and make these private
        GLfloat d1, d2, d3, d4, d5, d6;

        // Construct from GLfloats
        GL6DimensionalPoint(GLfloat d1, GLfloat d2, GLfloat d3, GLfloat d4, GLfloat d5, GLfloat d6) {
            this->d1 = d1;
            this->d2 = d2;
            this->d3 = d3;
            this->d4 = d4;
            this->d5 = d5;
            this->d6 = d6;
        }

        // Construct from vector
        GL6DimensionalPoint(std::vector<float> v)
        {
            this->d1 = v.at(0);
            this->d2 = v.at(1);
            this->d3 = v.at(2);
            this->d4 = v.at(3);
            this->d5 = v.at(4);
            this->d6 = v.at(5);
        }

        std::vector<float> toVector() {
            std::vector<float> vec{ d1, d2, d3, d4, d5, d6 };
            return vec;
        }
    };

    // Scale the values of an n-D point by the given anchor point
    GL6DimensionalPoint shiftPoint(GL6DimensionalPoint n, GLint anchor)
    {
        std::vector<float> v = n.toVector();
        for (int i = 0; i < v.size(); i++)
        {
            if (i != anchor) { v.at(i) += (v.at(anchor) - v.at(i)); }
        }

        return GL6DimensionalPoint(v);
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> GLvec2 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    class GLvec2    // A 2-D vector
    {
    public:
        GLfloat x;
        GLfloat y;

        GLvec2(GLfloat x, GLfloat y) { // Constructor
            this->x = x;
            this->y = y;
        }

        GLvec2(const GLvec2& vec) {    // Copy constructor
            this->x = vec.x;
            this->y = vec.y;
        }

        float Length() {               // Return length of vector
            return sqrt(x * x + y * y);
        }

        void Normalize() {             // Transform into normal vector in same direction
            float len = this->Length();
            this->x /= len;
            this->y /= len;
        }

        void Perpendicu() {            // Transform into vector perpendicular to current orientation
            float _x = this->x;
            this->x = -this->y;
            this->y = _x;
        }

        GLvec2 operator+(const GLvec2& b) {     // Overload + Operator
            return GLvec2(this->x + b.x, this->y + b.y);

        }

        GLvec2 operator-(const GLvec2& b) {     // Overload - Operator
            return GLvec2(this->x - b.x, this->y - b.y);

        }

        GLvec2 operator*(const GLint c) {     // Overload * Operator for * by Constants
            float constant = float(c);
            return GLvec2(this->x * c, this->y * c);
        }
    };

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drawDot >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    void drawPoint(GLint x, GLint y)
    {
        glBegin(GL_POINTS);
        glPointSize(4.0);
        glVertex2i(x, y);
        glEnd();
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drawArrow >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    void drawArrow(GLintPoint start, GLintPoint end)
    {
        // Draw Line Segment
        glBegin(GL_LINE_STRIP);
        glVertex2i(start.x, start.y);
        glVertex2i(end.x, end.y);
        glEnd();

        // Draw trangle for arrow tip
        glBegin(GL_TRIANGLES);

        GLvec2 p1 = { float(start.x), float(start.y) };
        GLvec2 p2 = { float(end.x), float(end.y) };

        GLvec2 direction = p2 - p1;
        direction.Normalize();

        GLvec2 perpendicular = GLvec2(direction);
        perpendicular.Perpendicu();

        GLvec2 pt1 = p2 - direction * (VERTICAL_SIZE / 200) * 3;
        GLvec2 pt2 = pt1 - perpendicular * (VERTICAL_SIZE / 200);
        GLvec2 pt3 = pt1 + perpendicular * (VERTICAL_SIZE / 200);

        glVertex2i(p2.x, p2.y);
        glVertex2i(pt2.x, pt2.y);
        glVertex2i(pt3.x, pt3.y);

        glEnd();
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drawParallelCoords >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    void drawParallelCoords(int dimension)
    {
        for (int i = HORIZONTAL_SIZE / 20; i < HORIZONTAL_SIZE;
            i += (HORIZONTAL_SIZE - (2 * (HORIZONTAL_SIZE / 20))) / 5)
        {
            drawArrow(GLintPoint(i, 0), GLintPoint(i, VERTICAL_SIZE - 5));
        }
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drawShiftedParallelCoordinates >>>>>>>>>>>>>>>>>>>
    void drawShiftedParallelCoords(GLint anchor)
    {
        float shift = VERTICAL_SIZE - 5;
        std::vector<float> yCoords = { shift, shift, shift, shift, shift, shift };
        std::vector<float> yCoordsShifted = shiftPoint(GL6DimensionalPoint(yCoords), anchor).toVector();

        for (int cnt = 0, i = HORIZONTAL_SIZE / 20; i < HORIZONTAL_SIZE;
            i += (HORIZONTAL_SIZE - (2 * (HORIZONTAL_SIZE / 20))) / 5)
        {
            drawArrow(GLintPoint(i, yCoordsShifted[cnt]), GLintPoint(i, yCoordsShifted[cnt] + 200));
            cnt++;
        }
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drawScaledParallelCoords >>>>>>>>>>>>>>>>>>>>>>>>>
    void drawScaledParallelCoords()
    {
        GLint yCoords[6] = { 150, 90, 130, 110, 230, 100 };
        for (int cnt = 0, i = HORIZONTAL_SIZE / 20; i < HORIZONTAL_SIZE;
            i += (HORIZONTAL_SIZE - (2 * (HORIZONTAL_SIZE / 20))) / 5)
        {
            drawArrow(GLintPoint(i, 0), GLintPoint(i, yCoords[cnt]));
            cnt++;
        }
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drawNonOrthoPC >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    void drawNonOrthoPC()
    {

    }

    void drawRadialCoords(GLint dimension)
    {

    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drawPCgraph >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    void drawPCgraph(GL6DimensionalPoint n)
    {
        std::vector<float> data = n.toVector();
        for (int i = HORIZONTAL_SIZE / 20, cnt = 0; i < HORIZONTAL_SIZE - (HORIZONTAL_SIZE / 5);
            i += (HORIZONTAL_SIZE - (2 * (HORIZONTAL_SIZE / 20))) / 5)
        {
            drawArrow(GLintPoint(i, data.at(cnt)),
                GLintPoint(i + (HORIZONTAL_SIZE - (2 * (HORIZONTAL_SIZE / 20))) / 5, data.at(cnt + 1)));
            cnt++;
        }
    };

    void setWindow(float left, float right, float bottom, float top)
    {

    }

    void setViewport(float left, float right, float bottom, float top)
    {
        glViewport(left, bottom, right - left, top - bottom);
    }

    // Adapted from StackOverflow: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
    // Draw a circle to the viewport from the given parameters
    void drawCircle(float cx, float cy, float r, int num_segments) {
        glBegin(GL_LINE_LOOP);

        for (int i = 0; i < num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);      //get the current angle 
            float x = r * cosf(theta);      //calculate the x component 
            float y = r * sinf(theta);      //calculate the y component 
            glVertex2f(x + cx, y + cy);     //output vertex 
        }

        glEnd();
    }
}