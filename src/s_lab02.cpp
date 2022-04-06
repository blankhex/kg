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

bool action_a = false;
bool action_b = false;

// Собственные объекты 
class animated_teapot : public kg::solid_teapot
{
protected:
    virtual void on_update()
    {
        time += 1;
        
        float factor = 1.0f;

        if (time < 100)
            factor = kg::ease(1.0f, 2.15f, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(2.15f, 1.0f, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
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

        auto& camera = myapp.camera();
        auto& position = camera.position();

        position.x() = sin(time / 200.0f) * 6.5f;
        position.y() = 4.0f;
        position.z() = cos(time / 200.0f) * 6.5f;

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
        position.y() = 2.5f; //cos(time / 25.0f) * 2.5f;
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
            diffuse_light.y() = kg::ease(diffuse_light.y(), 0.2f, 0.1, kg::ease_in_out_sine);
        else
            diffuse_light.y() = kg::ease(diffuse_light.y(), 1.0f, 0.1, kg::ease_in_out_sine);
        
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

class custom_torus : public kg::solid_torus
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

class custom_cone : public kg::solid_cone
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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("KG");

    myapp.init();
    myapp.load_image("wood.bmp");

    // Собсвтенные объекты здесь
    auto cmover = new camera_mover();
    myapp.add(cmover);

    auto light = new light_mover();
    myapp.add(light);

    auto pivot = new kg::pivot();
    myapp.add(pivot);

    auto teapot = new animated_teapot();
    teapot->color(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    teapot->shininess(128.0f);
    teapot->specular(kg::vector4(1.0f));
    
    myapp.add(teapot);

    auto cube = new kg::textured_cube();
    cube->color(kg::vector4(1.0f, 1.0f, 1.0f, 1.0f));
    cube->position(kg::vector3(-3.0f, 1.0f, 0.0f));
    cube->use_texture(true);
    myapp.add(cube);

    auto cone = new custom_cone();
    cone->color(kg::vector4(1.0f, 0.1f, 0.1f, 1.0f));
    cone->position(kg::vector3(3.0f, 3.0f,0.0f));
    myapp.add(cone);

    auto torus = new custom_torus();
    torus->color(kg::vector4(0.0f, 1.0f, 0.0f, 0.5f));
    torus->position(kg::vector3(3.0f, 3.0f, 1.0f));
    myapp.add(torus);

    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);
    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
}