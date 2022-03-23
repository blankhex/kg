#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>
#include <iostream>
#include "vector3.hpp"

namespace kg
{

class camera
{
public:
    const vector3& position() const { return _position; }
    vector3& position() { return _position; }
    void position(const vector3& position) { _position = position; }

    const float& yaw() const { return _yaw; }
    float& yaw() { return _yaw; }
    void yaw(const float& yaw) { _yaw = yaw; }

    const float& pitch() const { return _pitch; }
    float& pitch() { return _pitch; }
    void pitch(const float& pitch) { _pitch = pitch; }

    void look_at(const vector3& position)
    {
        vector3 delta = position - _position;
        delta = delta / delta.length();

        _yaw = atan2(-delta.z(), delta.x()) + (3.1415f / 180.0f) * 90.0f;
        _pitch = asin(delta.y());
    }

    void look()
    {
        vector3 target = _position;
        target.x() += sin(_yaw) * cos(_pitch);
        target.y() += sin(_pitch);
        target.z() += cos(_yaw) * cos(_pitch);
        
        glRotatef(-_pitch * (180.0f / 3.1415f), 1.0f, 0.0f, 0.0f);
        glRotatef(-_yaw * (180.0f / 3.1415f) + 180, 0.0f, 1.0f, 0.0f);
        glTranslatef(-_position.x(), -_position.y(), -_position.z());
        
        /*gluLookAt(_position.x(), _position.y(), _position.z(),
            target.x(), target.y(), target.z(),
            0.0f, 1.0f, 0.0f);*/
    }

private:
    vector3 _position;
    float _yaw = 0.0f;
    float _pitch = 0.0f;
};

}

#endif // CAMARA_HPP