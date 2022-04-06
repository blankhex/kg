#include <iostream>
#include <gl/freeglut.h>
#include <cmath>

#include "objects.hpp"
#include "camera.hpp"
#include "app.hpp"
#include "easing.hpp"

app myapp;

// Собственные объекты
class animated_torus : public kg::solid_torus
{
protected:
    virtual void on_update()
    {
        time += 1;
        const float from_x = 1.0f;
        const float to_x = 0.3f;

        float factor = from_x;

        if (time < 100)
            factor = kg::ease(from_x, to_x, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(to_x, from_x, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        scale(kg::vector3(factor));
    }

private:
    int time = 0;
};

class camera_mover : public kg::object
{
protected:
    virtual void on_update()
    {
        time++;

        auto &camera = myapp.camera();
        auto &position = camera.position();

        position.x() = 3.0f;
        position.y() = 3.5f;
        position.z() = 6.0f;

        camera.look_at(kg::vector3(0.0f));
    }

private:
    int time = 0;
};

class animated_sphere : public kg::wire_sphere
{
protected:
    virtual void on_translate()
    {
        time++;
        float factor = 0.0f;
        float from_angle = 0.0f;
        float to_angle = -90.0f;

        if (time < 100)
            factor = kg::ease(from_angle, to_angle, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(to_angle, from_angle, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        glRotatef(factor, 0.0f, 0.0f, 1.0f);
    }

private:
    int time = 0;
};

class animated_tetrahedron : public kg::wire_tetrahedron
{
protected:
    virtual void on_translate()
    {
        time++;
        float factor = 0.0f;
        float from_angle = 0.0f;
        float to_angle = -180.0f;

        if (time < 100)
            factor = kg::ease(from_angle, to_angle, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(to_angle, from_angle, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        glRotatef(factor, 1.0f, 0.0f, 0.0f);
    }

private:
    int time = 0;
};

// Код проекта

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void display()
{
    myapp.update();
    myapp.draw();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("KG");

    myapp.init();

    // Собсвтенные объекты здесь
    auto grid = new kg::grid();
    myapp.add(grid);

    auto cmover = new camera_mover();
    myapp.add(cmover);

    auto pivot = new kg::pivot();
    myapp.add(pivot);

    auto torus = new animated_torus();
    torus->color(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    torus->rotation(kg::vector3(90.0f));
    torus->use_light(false);
    torus->position(kg::vector3(0.0f, 1.0f, 4.0f));
    torus->rotation(kg::vector3(0.0f, 45.0f, 0.0f));
    myapp.add(torus);

    auto cube = new kg::solid_cube();
    cube->position(kg::vector3(-1.0f, 0.0f, 3.0f));
    cube->color(kg::vector4(1.0f, 0.0f, 0.0f, 1.0f));
    cube->scale(kg::vector3(2.0f));
    cube->use_light(false);
    myapp.add(cube);

    auto tetrahedron = new animated_tetrahedron();
    tetrahedron->position(kg::vector3(-2.0f, 3.0f, 0.0f));
    tetrahedron->color(kg::vector4(1.0f, 0.0f, 1.0f, 1.0f));
    tetrahedron->use_light(false);
    tetrahedron->rotation(kg::vector3(0.0f, 0.0f, -15.0f));
    myapp.add(tetrahedron);

    auto sphere = new animated_sphere();
    sphere->color(kg::vector4(0.0f, 1.0f, 0.0f, 1.0f));
    sphere->use_light(false);
    sphere->position(kg::vector3(0.0f, 3.0f, 0.0f));
    myapp.add(sphere);

    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
}