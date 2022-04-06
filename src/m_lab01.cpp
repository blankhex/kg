#include <iostream>
#include <gl/freeglut.h>
#include <cmath>

#include "objects.hpp"
#include "camera.hpp"
#include "app.hpp"
#include "easing.hpp"

app myapp;

// Собственные объекты 
class animated_teapot : public kg::wire_cylinder
{
protected:
    virtual void on_update()
    {
        time += 1;
        const float from_x = 0.0f;
        const float to_x = 5.0f;

        float factor = from_x;

        if (time < 100)
            factor = kg::ease(from_x, to_x, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(to_x, from_x, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        position(kg::vector3(factor, 0.0f, 0.0f));
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

        auto& camera = myapp.camera();
        auto& position = camera.position();

        position.x() = sin(time / 100.0f) * 5.0f;
        position.y() = 2.5f;
        position.z() = cos(time / 100.0f) * 5.0f;

        camera.look_at(kg::vector3(0.0f));
    }

private:
    int time = 0;
};

class custom_torus : public kg::wire_torus
{
protected:
    virtual void on_translate()
    {
        time++;
        float factor = 0.0f;

        if (time < 100)
            factor = kg::ease(0.0f, 45.0f, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(45.0f, 0.0f, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        glRotatef(factor, 0.0f, 0.0f, 1.0f);
    }

private:
    int time = 0;
};

class custom_cone : public kg::wire_cone
{
protected:
    virtual void on_translate()
    {
        time++;
        float factor = 0.0f;

        if (time < 100)
            factor = kg::ease(0.0f, 60.0f, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(60.0f, 0.0f, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        glRotatef(factor, 1.0f, 0.0f, 0.0f);
    }

private:
    int time = 0;
};


// Код проекта 

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void display()
{
    myapp.update();
    myapp.draw();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("KG");

    myapp.init();

    // Собсвтенные объекты здесь
    auto cmover = new camera_mover();
    myapp.add(cmover);

    auto pivot = new kg::pivot();
    myapp.add(pivot);

    auto teapot = new animated_teapot();
    teapot->color(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    teapot->use_light(false);
    myapp.add(teapot);

    auto cube = new kg::wire_cube();
    cube->color(kg::vector4(1.0f, 0.0f, 0.0f, 1.0f));
    cube->scale(kg::vector3(3.0f));
    cube->use_light(false);
    myapp.add(cube);

    auto cone = new custom_cone();
    cone->color(kg::vector4(0.0f, 0.0f, 1.0f, 1.0f));
    cone->use_light(false);
    cone->position(kg::vector3(3.0f, 3.0f,0.0f));
    myapp.add(cone);

    auto torus = new custom_torus();
    torus->color(kg::vector4(0.0f, 1.0f, 0.0f, 1.0f));
    torus->use_light(false);
    torus->position(kg::vector3(3.0f, 3.0f, 1.0f));
    myapp.add(torus);

    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
}