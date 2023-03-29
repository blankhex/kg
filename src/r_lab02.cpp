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

// Собственные объекты 
class animated_cube : public kg::textured_cube
{
protected:
    virtual void on_update()
    {
        time += 1;
        
        float factor = 2.0f;

        if (time < 100)
            factor = kg::ease(2.0f, 4.0f, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(4.0f, 2.0f, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        scale(kg::vector3(factor));
    }
    
private:
    int time = 0;
};

class animated_cone : public kg::solid_cone
{
protected:
    virtual void on_update()
    {
        time += 1;
        
        float factor = 0.0f;

        if (time < 100)
            factor = kg::ease(0.0f, 2.0f, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            factor = kg::ease(2.0f, 0.0f, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        position(kg::vector3(factor, 0.0f, 0.0f));
    }
    
private:
    int time = 0;
};

class animated_torus : public kg::solid_torus
{
protected:
    virtual void on_update()
    {
        time += 1;
        
        kg::vector3 from = kg::vector3(-3.0f, 0.0f,0.0f);
        kg::vector3 to = kg::vector3(-3.0f, 3.25f,2.0f);
        
        kg::vector3 result = from;
        
        if (time < 100)
            result = kg::ease(from, to, time / 100.0f, kg::ease_in_out_cubic);
        else if (time < 200)
            result = kg::ease(to, from, (time - 100.0f) / 100.0f, kg::ease_in_out_cubic);
        else
            time = 0;

        position(result);
    }
    
private:
    int time = 0;
};

class animated_cylinder : public kg::solid_cylinder
{
protected:
    virtual void on_update()
    {
        time += 1;
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


// Код проекта 

void keyboard_down(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'o':
        action_a = true;
        break;
    
    default:
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
    
    default:
        break;
    }
}

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
    myapp.load_image("stone.bmp");

    // Собсвтенные объекты здесь
    auto grid = new kg::grid();
    myapp.add(grid);
    
    auto& camera = myapp.camera();
    camera.position(kg::vector3(-5.0f, 4.0f, -5.0f));
    camera.look_at(kg::vector3(0.0f));

    auto light = new light_mover();
    myapp.add(light);
    
    auto pivot = new kg::pivot();
    myapp.add(pivot);

    auto cube = new animated_cube();
    cube->color(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    cube->scale(kg::vector3(2.0f));
    cube->position(kg::vector3(0.0f, 1.0f, 0.0f));
    cube->use_texture(true);
    myapp.add(cube);

    auto cone = new animated_cone();
    cone->color(kg::vector4(1.0f, 0.0f, 0.0f, 1.0f));
    cone->rotation(kg::vector3(-90.0f, 0.0f, 0.0f));
    cone->scale(kg::vector3(2.5f, 5.0f, 2.5f));
    cone->shininess(128.0f);
    cone->specular(kg::vector4(1.0f));
    myapp.add(cone);

    auto torus = new animated_torus();
    torus->color(kg::vector4(0.0f, 0.0f, 1.0f, 1.0f));
    torus->position(kg::vector3(-3.0f, 0.0f,0.0f));
    torus->rotation(kg::vector3(-90.0f, 0.0f, 0.0f));
    torus->shininess(128.0f);
    torus->specular(kg::vector4(1.0f));
    myapp.add(torus);

    auto cylinder = new animated_cylinder();
    cylinder->color(kg::vector4(0.0f, 1.0f, 0.0f, 1.0f));
    cylinder->position(kg::vector3(-3.0f, 2.0f, 2.0f));
    cylinder->rotation(kg::vector3(-90.0f, 0.0f, 0.0f));
    myapp.add(cylinder);
    
    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);
    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
}