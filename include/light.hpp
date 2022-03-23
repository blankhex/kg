#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/freeglut.h>

#include <vector3.hpp>
#include <vector4.hpp>

namespace kg
{

class light
{
public:
    light(int id = 0) { _id = id; }

    const vector4& ambient() const { return _ambient; }
    vector4& ambient() { return _ambient; }
    void ambient(const vector4& ambient) { _ambient = ambient; } 

    const vector4& diffuse() const { return _diffuse; }
    vector4& diffuse() { return _diffuse; }
    void diffuse(const vector4& diffuse) { _diffuse = diffuse; } 

    const vector4& specular() const { return _specular; }
    vector4& specular() { return _specular; }
    void specular(const vector4& specular) { _specular = specular; } 

    const vector4& position() const { return _position; }
    vector4& position() { return _position; }
    void position(const vector4& position) { _position = position; } 

    const float& cutoff() const { return _cutoff; }
    float& cutoff() { return _cutoff; }
    void cutoff(float cutoff) { _cutoff = cutoff; }

    const float& exponent() const { return _exponent; }
    float& exponent() { return _exponent; }
    void exponent(float exponent) { _exponent = exponent; }

    const float& constant_attenuation() const { return _constant_attenuation; }
    float& constant_attenuation() { return _constant_attenuation; }
    void constant_attenuation(float constant_attenuation) { _constant_attenuation = constant_attenuation; }

    const float& linear_attenuation() const { return _linear_attenuation; }
    float& linear_attenuation() { return _linear_attenuation; }
    void linear_attenuation(float linear_attenuation) { _linear_attenuation = linear_attenuation; }

    const float& quadratic_attenuation() const { return _quadratic_attenuation; }
    float& quadratic_attenuation() { return _quadratic_attenuation; }
    void quadratic_attenuation(float quadratic_attenuation) { _quadratic_attenuation = quadratic_attenuation; }

    void enable()
    {
        glEnable(GL_LIGHT0 + _id);
        
        glLightfv(GL_LIGHT0 + _id, GL_AMBIENT, _ambient.data);
        glLightfv(GL_LIGHT0 + _id, GL_DIFFUSE, _diffuse.data);
        glLightfv(GL_LIGHT0 + _id, GL_SPECULAR, _specular.data);
        glLightfv(GL_LIGHT0 + _id, GL_POSITION, _position.data);
        glLightfv(GL_LIGHT0 + _id, GL_SPOT_DIRECTION, _direction.data);

        glLightf(GL_LIGHT0 + _id, GL_SPOT_CUTOFF, _cutoff);
        glLightf(GL_LIGHT0 + _id, GL_SPOT_EXPONENT, _exponent);
        glLightf(GL_LIGHT0 + _id, GL_CONSTANT_ATTENUATION, _constant_attenuation);
        glLightf(GL_LIGHT0 + _id, GL_LINEAR_ATTENUATION, _linear_attenuation);
        glLightf(GL_LIGHT0 + _id, GL_QUADRATIC_ATTENUATION, _quadratic_attenuation);
    }

    void disable()
    {
        glDisable(GL_LIGHT0 + _id);
    }

private:
    int _id = GL_LIGHT0;

    vector4 _ambient = vector4(0.0f, 0.0f, 0.0f, 1.0f);
    vector4 _diffuse = vector4(1.0f);
    vector4 _specular = vector4(1.0f);
    vector4 _position = vector4(0.0f, 0.0f, 1.0f, 0.0f);
    vector3 _direction = vector3(0.0f, 0.0f, -1.0f);

    float _cutoff = 180.0f;
    float _exponent = 0.0f;
    float _constant_attenuation = 1.0f;
    float _linear_attenuation = 0.0f;
    float _quadratic_attenuation = 0.0f;
};
}

#endif // LIGHT_HPP