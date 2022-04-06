#ifndef APP_HPP
#define APP_HPP

#include <vector>
#include <algorithm>
#include <GL/freeglut.h>
#include "bitmap.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "object.hpp"


class app
{
public:
    void init(kg::vector4 color = kg::vector4(0.0f))
    {
        static float lighting_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

        glClearColor(color.x(), color.y(), color.z(), color.w());
        glClearDepth(1.0f);
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        glEnable(GL_TEXTURE_2D);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lighting_ambient);
        
        glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_COLOR_MATERIAL);

        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        glViewport(0, 0, 640, 480);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, 640.0f / 480.0f, 0.01, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    }

    void load_image(const std::string& path)
    {
        _bitmap.load(path);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, _bitmap.width(), _bitmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _bitmap.data().data());
    }

    void update()
    {
        for (auto& obj : _objects)
        {
            obj->update();
        }

        auto remove_iterator = std::remove_if(_objects.begin(), _objects.end(), [](kg::object* obj) {
            if (obj->remove())
            {
                delete obj;
                return true;
            }
            return false;
        });

        _objects.erase(remove_iterator, _objects.end());
    }

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        _camera.look();
        _light.enable();

        for (auto& obj : _objects)
        {
            if (obj->use_texture())
            {
                glBindTexture(GL_TEXTURE_2D, _texture);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            obj->draw();
        }

        //_light.disable();
        glutSwapBuffers();
    }

    void add(kg::object* obj)
    {
        _objects.push_back(obj);
    }

    const kg::light& light() const { return _light; }
    kg::light& light() { return _light; }

    const kg::camera& camera() const { return _camera; }
    kg::camera& camera() { return _camera; }

    const kg::bitmap& bitmap() const { return _bitmap; }
    kg::bitmap& bitmap() { return _bitmap; }

private:
    GLuint _texture;
    kg::bitmap _bitmap;
    kg::light _light;
    kg::camera _camera;
    std::vector<kg::object*> _objects;
};

#endif // APP_HPP