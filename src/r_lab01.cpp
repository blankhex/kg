#include <iostream>
#include <gl/freeglut.h>
#include <cmath>

#include "objects.hpp"
#include "camera.hpp"
#include "app.hpp"
#include "easing.hpp"

app myapp;

// Собственные объекты 
class animated_cube : public kg::wire_cube
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

class animated_cone : public kg::wire_cone
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
    auto grid = new kg::grid();
    myapp.add(grid);
    
    auto& camera = myapp.camera();
    camera.position(kg::vector3(-5.0f, 4.0f, -5.0f));
    camera.look_at(kg::vector3(0.0f));

    auto pivot = new kg::pivot();
    myapp.add(pivot);

    auto cube = new animated_cube();
    cube->color(kg::vector4(1.0f, 1.0f, 0.0f, 1.0f));
    cube->scale(kg::vector3(2.0f));
    cube->position(kg::vector3(0.0f, 1.0f, 0.0f));
    cube->use_light(false);
    myapp.add(cube);

    auto cone = new animated_cone();
    cone->color(kg::vector4(1.0f, 0.0f, 0.0f, 1.0f));
    cone->rotation(kg::vector3(-90.0f, 0.0f, 0.0f));
    cone->scale(kg::vector3(2.5f, 5.0f, 2.5f));
    cone->use_light(false);
    myapp.add(cone);

    auto torus = new animated_torus();
    torus->color(kg::vector4(0.0f, 0.0f, 1.0f, 1.0f));
    torus->use_light(false);
    torus->position(kg::vector3(-3.0f, 0.0f,0.0f));
    torus->rotation(kg::vector3(-90.0f, 0.0f, 0.0f));
    myapp.add(torus);

    auto cylinder = new animated_cylinder();
    cylinder->color(kg::vector4(0.0f, 1.0f, 0.0f, 1.0f));
    cylinder->use_light(false);
    cylinder->position(kg::vector3(-3.0f, 2.0f, 2.0f));
    cylinder->rotation(kg::vector3(-90.0f, 0.0f, 0.0f));
    myapp.add(cylinder);

    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();

    return 0;
}