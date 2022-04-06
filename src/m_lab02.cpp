#include <iostream>
#include <gl/freeglut.h>
#include <cmath>

#include "objects.hpp"
#include "camera.hpp"
#include "app.hpp"
#include "easing.hpp"

app myapp;

bool action_a = false;
bool action_b = false;

// Собственные объекты
class animated_cylinder : public kg::solid_cylinder
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

        auto &camera = myapp.camera();
        auto &position = camera.position();

        position.x() = 6.0f;
        position.y() = 3.5f;
        position.z() = 6.0f;

        camera.look_at(kg::vector3(0.0f));
    }

private:
    int time = 0;
};

class light_mover : public kg::solid_sphere
{
protected:
    virtual void on_update()
    {
        time++;

        auto& light = myapp.light();
        auto& position = light.position();

        position.x() = sin(time / 35.0f) * 3.0f;
        position.y() = cos(time / 25.0f) * 2.5f;
        position.z() = cos(time / 35.0f) * 3.0f;
        position.w() = 1.0f;

        this->position(position.vector3());
        this->scale(kg::vector3(0.1f));
        this->color(kg::vector4(1.0f));

        light.linear_attenuation() = 0.80f;
        light.quadratic_attenuation() = 0.08f;
        light.ambient(kg::vector4(0.0f, 0.0f, 0.0f, 1.0f));

        auto& diffuse_light = light.diffuse();

        if (action_a)
            diffuse_light.x() = kg::ease(diffuse_light.x(), 0.0f, 0.1, kg::ease_in_out_sine);
        else
            diffuse_light.x() = kg::ease(diffuse_light.x(), 1.0f, 0.1, kg::ease_in_out_sine);
        
        color(diffuse_light);
    }

    virtual void on_draw()
    {
        glDisable(GL_LIGHTING);
        kg::solid_sphere::on_draw();
    }

private:
    int time = 0;
};

class animated_torus : public kg::solid_torus
{
protected:
    virtual void on_translate()
    {
        time++;
        float factor = 0.0f;
        float from_angle = 0.0f;
        float to_angle = 90.0f;

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

class animated_tetrahedron : public kg::solid_tetrahedron
{
protected:
    virtual void on_update()
    {
        time += 1;
        const float from_y = 3.0f;
        const float to_y = 1.5f;

        float factor = from_y;

        if (time < 100)
            factor = kg::ease(from_y, to_y, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(to_y, from_y, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        float x = position().x();
        float z = position().z();

        position(kg::vector3(x, factor, z));
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

void keyboard_down(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'o':
        action_a = true;
        break;
    
    case 'p':
        action_b = true;
        break;
    }
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'o':
        action_a = false;
        break;
    
    case 'p':
        action_b = false;
        break;
    }
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
    auto cmover = new camera_mover();
    myapp.add(cmover);
    
    auto light = new light_mover();
    myapp.add(light);

    auto pivot = new kg::pivot();
    myapp.add(pivot);

    auto cylinder = new animated_cylinder();
    cylinder->color(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    cylinder->rotation(kg::vector3(90.0f));
    cylinder->color(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    cylinder->shininess(128.0f);
    cylinder->specular(kg::vector4(1.0f));
    cylinder->diffuse(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    myapp.add(cylinder);

    auto cube = new kg::textured_cube();
    cube->use_texture(true);
    cube->position(kg::vector3(-2.0f, 0.0f, 0.0f));
    cube->color(kg::vector4(1.0f, 1.0f, 1.0f, 1.0f));
    cube->scale(kg::vector3(2.0f));
    cube->ambient(kg::vector4(0.1f, 0.1f, 0.1f, 1.0f));
    cube->emmision(kg::vector4(0.0f, 0.0f, 0.0f, 1.0f));
    myapp.add(cube);

    auto tetrahedron = new animated_tetrahedron();
    tetrahedron->position(kg::vector3(-2.0f, 3.0f, 0.0f));
    tetrahedron->color(kg::vector4(1.0f, 0.0f, 1.0f, 1.0f));
    tetrahedron->rotation(kg::vector3(0.0f, 0.0f, -15.0f));
    myapp.add(tetrahedron);

    auto sphere = new kg::solid_sphere();
    sphere->color(kg::vector4(0.0f, 0.0f, 1.0f, 1.0f));
    sphere->scale(kg::vector3(0.74f));
    sphere->position(kg::vector3(2.5f, 0.0f, 0.0f));
    sphere->shininess(128.0f);
    sphere->specular(kg::vector4(1.0f));
    sphere->diffuse(kg::vector4(0.0f, 0.0f, 1.0f, 1.0f));
    myapp.add(sphere);

    auto torus = new animated_torus();
    torus->color(kg::vector4(0.0f, 1.0f, 0.0f, 0.5f));
    torus->position(kg::vector3(0.0f, 3.0f, 0.0f));
    myapp.add(torus);

    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);
    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
}