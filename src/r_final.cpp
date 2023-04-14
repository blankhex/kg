#include <iostream>
#include <gl/freeglut.h>
#include <cmath>

#include "objects.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "bitmap.hpp"
#include "app.hpp"
#include "easing.hpp"

app myapp;


class textured_torus: public kg::object
{

private:
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _uv;
    std::vector<GLfloat> _normals;
    const int _nR = 128;
    const int _nr = 128;
    const float _r  = 0.40f;
    const float _R = 0.80f;
    int _frame = 0;

protected:
    void prepare()
    {
        float du = 2 * M_PI / _nR;
        float dv = 2 * M_PI / _nr;

        for (size_t i = 0; i < _nR; i++)
        {
            float u = i * du;

            for (size_t j = 0; j <= _nr; j++)
            {
                float v = (j % _nr) * dv;

                for (size_t k = 0; k < 2; k++)
                {
                    float uu = u + k * du;
                    // compute vertex
                    float x = (_R + _r * cos(v)) * cos(uu);
                    float y = (_R + _r * cos(v)) * sin(uu);
                    float z = _r * sin(v);

                    // add vertex 
                    _vertices.push_back(x);
                    _vertices.push_back(y);
                    _vertices.push_back(z);

                    // compute texture coords
                    float tx = uu / (2 * M_PI);
                    float ty = v / (2 * M_PI);

                    // add tex coords
                    _uv.push_back(tx);
                    _uv.push_back(ty);

                    // compute normal 
                    float nx = cos(v) * cos(uu);
                    float ny = cos(v) * sin(uu);
                    float nz = sin(v);

                    // add normal 
                    _normals.push_back(nx);
                    _normals.push_back(ny);
                    _normals.push_back(nz);
                }
                // incr angle
                v += dv;
            }
        }
    }

    virtual void on_draw()
    {
        if (_vertices.size() == 0 || _uv.size() == 0 || _normals.size() == 0)
        {
            prepare();
        }

        glBegin(GL_TRIANGLE_STRIP);
        for (size_t i = 0; i < _vertices.size() / 3; i++)
        {
            glNormal3fv(&_normals[i * 3]);
            glTexCoord2f(_uv[i * 2], _uv[i * 2 + 1]);
            glVertex3fv(&_vertices[i * 3]);
        }
        glEnd();
    }

    virtual void on_update()
    {
        _frame++;
        const kg::vector3 fromA1(-90.0f, 0.0f, 0.0f);
        const kg::vector3 middleA1(0.0f, 0.0f, 0.0f);
        const kg::vector3 toA1(90.0f, 0.0f, 0.0f);

        const kg::vector3 fromP1(0.0f, 0.78f, -0.75f);
        const kg::vector3 middleP1(0.0f, 0.35f, 0.0f);
        const kg::vector3 toP1(0.0f, 0.78f, 0.75f);

        const kg::vector3 fromA2(-90.0f, 0.0f, 0.0f);
        const kg::vector3 middleA2(0.0f, 0.0f, 0.0f);
        const kg::vector3 toA2(90.0f, 0.0f, 0.0f);

        const kg::vector3 fromP2(0.0f, 0.78f, 4.75f);
        const kg::vector3 middleP2(0.0f, 0.35f, 5.5f);
        const kg::vector3 toP2(0.0f, 0.78f, 6.25f);

        kg::vector3 resultA = fromA1;
        kg::vector3 resultP = fromP1;

        if (_frame < 100)
        {
            resultA = fromA1;
            resultP = fromP1;
        }
        else if (_frame < 200)
        {
            // kg::ease_out_cubic
            resultA = kg::ease(fromA1, middleA1, (_frame - 100.0f) / 100.0f, kg::ease_in_cubic);
            resultP = kg::ease(fromP1, middleP1, (_frame - 100.0f) / 100.0f, kg::ease_in_cubic);
        }
        else if (_frame < 240)
        {
            // < 200
            // / 100.0f
            // kg::ease_in_bounce
            // kg::ease_in_sine
            resultA = kg::ease(middleA1, toA1, (_frame - 200.0f) / 40.0f, kg::ease_out_sine);
            resultP = kg::ease(middleP1, toP1, (_frame - 200.0f) / 40.0f, kg::ease_out_sine);
        }
        else if (_frame < 290)
        {
            resultA = kg::ease(fromA2, middleA2, (_frame - 240.0f) / 50.0f, kg::ease_in_sine);
            resultP = kg::ease(fromP2, middleP2, (_frame - 240.0f) / 50.0f, kg::ease_in_sine);
        }
        else if (_frame < 540)
        {
            // < 200
            // / 100.0f
            // kg::ease_in_bounce
            // kg::ease_in_sine
            resultA = kg::ease(middleA2, toA2, (_frame - 290.0f) / 250.0f, kg::ease_out_bounce);
            resultP = kg::ease(middleP2, toP2, (_frame - 290.0f) / 250.0f, kg::ease_out_bounce);
        }
        else if (_frame < 640)
        {
            // < 300
            resultA = toA2;
            resultP = toP2;
        }
        else
        {
            _frame = 0;
        }

        position(resultP);
        rotation(resultA);
    }
};


void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void display()
{
    myapp.update();
    myapp.draw();
}

void keyboard_down(unsigned char key, int x, int y)
{
    auto& camera = myapp.camera();
    switch (key)
    {
    case 'o':
        camera.position(kg::vector3(-5.0f, 0.5f, 0.0f));
        camera.look_at(kg::vector3(0.0f));
        break;
    
    default:
        break;
    }
}

void keyboard_up(unsigned char key, int x, int y)
{
    auto& camera = myapp.camera();
    switch (key)
    {
    case 'o':
        camera.position(kg::vector3(-3.5f, 4.0f, -3.5f));
        camera.look_at(kg::vector3(0.0f));
        break;
    
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("KG");

    myapp.init(kg::vector4(0.30f, 0.30f, 0.30f, 1.0f));
    myapp.load_image("wood.bmp");

    
    // Основная сцена
    auto grid = new kg::grid();
    myapp.add(grid);

    auto pivot = new kg::pivot();
    myapp.add(pivot);

    auto& camera = myapp.camera();
    camera.position(kg::vector3(-3.5f, 4.0f, -3.5f));
    camera.look_at(kg::vector3(0.0f));

    // Освещение
    auto& light = myapp.light();
    auto& light_position = light.position();

    light_position.x() = 0.0f;
    light_position.y() = 2.5f;
    light_position.z() = 0.0f;
    light_position.w() = 1.0f;

    light.linear_attenuation() = 0.80f;
    light.quadratic_attenuation() = 0.08f;
    light.ambient(kg::vector4(0.6f, 0.6f, 0.6f, 1.0f));
    
    auto sphere = new kg::solid_sphere();
    sphere->position(light_position.vector3());
    sphere->color(kg::vector4(1.0f, 1.0f, 1.0f, 1.0f));
    sphere->scale(kg::vector3(0.2f));
    sphere->use_light(false);
    myapp.add(sphere);


    // Собсвтенные объекты здесь
    auto torus = new textured_torus();
    torus->color(kg::vector4(1.0f, 1.0f, 1.0f, 1.0f));
    torus->origin(kg::vector3(0.0f, 1.0f, 0.0f));
    torus->rotation(kg::vector3(45.0f, 0.0f, 0.0f));
    torus->scale(kg::vector3(2.0f, 2.0f, 2.0f));
    torus->use_light(true);
    torus->use_texture(true);
    torus->shininess(128.0f);
    torus->specular(kg::vector4(1.0f));
    myapp.add(torus);

    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);
    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
    return 0;
}