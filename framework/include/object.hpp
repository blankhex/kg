#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GL/freeglut.h>

#include "vector3.hpp"
#include "vector4.hpp"

namespace kg
{

class object
{
public:
    const vector3& position() const { return _position; }
    vector3& position() { return _position; }
    void position(const vector3& position) { _position = position; }

    const vector3& origin() const { return _origin; }
    vector3& origin() { return _origin; }
    void origin(const vector3& origin) { _origin = origin; }

    const vector3& rotation() const { return _rotation; }
    vector3& rotation() { return _rotation; }
    void rotation(const vector3& rotation) { _rotation = rotation; }

    const vector3& scale() const { return _scale; }
    vector3& scale() { return _scale; }
    void scale(const vector3& scale) { _scale = scale; }

    const vector4& ambient() const { return _ambient; }
    vector4& ambient() { return _ambient; }
    void ambient(const vector4& ambient) { _ambient = ambient; }

    const vector4& diffuse() const { return _diffuse; }
    vector4& diffuse() { return _diffuse; }
    void diffuse(const vector4& diffuse) { _diffuse = diffuse; }

    const vector4& specular() const { return _specular; }
    vector4& specular() { return _specular; }
    void specular(const vector4& specular) { _specular = specular; }

    const vector4& emmision() const { return _emmision; }
    vector4& emmision() { return _emmision; }
    void emmision(const vector4& emmision) { _emmision = emmision; }

    const vector4& color() const { return _color; }
    vector4& color() { return _color; }
    void color(const vector4& color) { _color = color; }

    const float& shininess() const { return _shininess; }
    float& shininess() { return _shininess; }
    void shininess(float shininess) { _shininess = shininess; }
    
    const bool& use_light() const { return _use_light; }
    bool& use_light() { return _use_light; }
    void use_light(bool use_light) { _use_light = use_light; }

    const bool& remove() const { return _remove; }
    bool& remove() { return _remove; }
    void remove(bool remove) { _remove = remove; }

    const bool& use_texture() const { return _use_texture; }
    bool& use_texture() { return _use_texture; }
    void use_texture(bool use_texture) { _use_texture = use_texture; }

    void draw() 
    {
        glPushMatrix();
        
        on_translate();
        glTranslatef(_position.x(), _position.y(), _position.z());

        on_scale();
        glScalef(_scale.x(), _scale.y(), _scale.z());

        on_rotate();
        glRotatef(_rotation.x(), 1.0f, 0.0f, 0.0f);
        glRotatef(_rotation.y(), 0.0f, 1.0f, 0.0f);
        glRotatef(_rotation.z(), 0.0f, 0.0f, 1.0f);

        glTranslatef(_origin.x(), _origin.y(), _origin.z());

        glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient.data);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse.data);
        glMaterialfv(GL_FRONT, GL_SPECULAR, _specular.data);
        glMaterialfv(GL_FRONT, GL_EMISSION, _emmision.data);
        glMaterialf(GL_FRONT, GL_SHININESS, _shininess);
        glColor4f(_color.x(), _color.y(), _color.z(), _color.w());
        
        if (_use_light)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        on_draw();

        glPopMatrix();
    }

    void update() 
    {
        on_update();
    }

protected:
    virtual void on_translate() {}
    virtual void on_scale() {}
    virtual void on_rotate() {}
    virtual void on_draw() {}
    virtual void on_update() {}

private:
    vector4 _color = vector4(0.0f);
    vector3 _position = vector3(0.0f);
    vector3 _origin = vector3(0.0f);
    vector3 _rotation = vector3(0.0f);
    vector3 _scale = vector3(1.0f);

    vector4 _ambient = vector4(1.0f);
    vector4 _diffuse = vector4(0.5f);
    vector4 _specular = vector4(0.0f);
    vector4 _emmision = vector4(0.0f);
    float _shininess = 0.0f;
    bool _use_light = true;
    bool _use_texture = false;
    bool _remove = false;
};

}

#endif // OBJECT_HPP