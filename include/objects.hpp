#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "Object.hpp"

namespace kg
{

const int OBJECTS_QUALITY = 16;

class solid_cube : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidCube(1.0);
    }
};

class wire_cube : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireCube(1.0);
    }
};

class solid_sphere : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidSphere(1.0, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class wire_sphere : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireSphere(1.0, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class solid_teapot : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidTeapot(1.0);
    }
};

class wire_teapot : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireTeapot(1.0);
    }
};

class solid_cylinder : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidCylinder(1.0, 1.0, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class wire_cylinder : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireCylinder(1.0, 1.0, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class solid_octahedron : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidOctahedron();
    }
};

class wire_octahedron : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireOctahedron();
    }
};

class solid_tetrahedron : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidTetrahedron();
    }
};

class wire_tetrahedron : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireTetrahedron();
    }
};

class solid_torus : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidTorus(0.25, 0.75, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class wire_torus : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireTorus(0.25, 0.75, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class solid_cone : public object
{
protected:
    virtual void on_draw() 
    {
        glutSolidCone(1.0, 1.0, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class wire_cone : public object
{
protected:
    virtual void on_draw() 
    {
        glutWireCone(1.0, 1.0, OBJECTS_QUALITY, OBJECTS_QUALITY);
    }
};

class textured_cube : public object
{
protected:
    virtual void on_draw()
    {
        static const GLfloat n[6][3] =
        {
            {-1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, -1.0, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, -1.0}
        };
        static const GLint faces[6][4] =
        {
            {0, 1, 2, 3},
            {3, 2, 6, 7},
            {7, 6, 5, 4},
            {4, 5, 1, 0},
            {5, 6, 2, 1},
            {7, 4, 0, 3}
        };
        GLfloat v[8][3];
        GLint i;

        v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1.0f / 2;
        v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.0f / 2;
        v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1.0f / 2;
        v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1.0f / 2;
        v[0][2] = v[3][2] = v[4][2] = v[7][2] = -1.0f / 2;
        v[1][2] = v[2][2] = v[5][2] = v[6][2] = 1.0f / 2;

        for (i = 5; i >= 0; i--)
        {
            glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0.0f, 1.0f); glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(0.0f, 0.0f); glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1.0f, 0.0f); glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(1.0f, 1.0f); glVertex3fv(&v[faces[i][3]][0]);
            glEnd();
        }
    }
};

class pivot : public object
{
protected:
    virtual void on_draw()
    {
        glDisable(GL_LIGHTING);

        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(5.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 5.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 5.0f);
        glEnd();
    }
};

}

#endif // OBJECTS_HPP