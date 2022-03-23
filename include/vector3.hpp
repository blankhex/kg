#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace kg
{

struct vector3
{
    float data[3];

    enum 
    {
        X,
        Y,
        Z
    };

    vector3() { data[X] = data[Y] = data[Z] = 0.0f; }
    vector3(float value) { data[X] = data[Y] = data[Z] = value; }
    vector3(float x, float y, float z = 0.0f)
    {
        data[X] = x;
        data[Y] = y;
        data[Z] = z;
    }

    vector3& operator*=(float value) 
    {
        data[X] *= value;
        data[Y] *= value;
        data[Z] *= value;

        return *this;
    }

    vector3& operator/=(float value) 
    {
        data[X] /= value;
        data[Y] /= value;
        data[Z] /= value;

        return *this;
    }

    vector3& operator+=(const vector3& other)
    {
        data[X] += other.data[X];
        data[Y] += other.data[Y];
        data[Z] += other.data[Z];

        return *this;
    }

    vector3& operator-=(const vector3& other)
    {
        data[X] -= other.data[X];
        data[Y] -= other.data[Y];
        data[Z] -= other.data[Z];

        return *this;
    }

    vector3 operator*(float value) const
    {
        vector3 result = *this;
        
        result.data[X] *= value;
        result.data[Y] *= value;
        result.data[Z] *= value;

        return result;
    }

    vector3 operator/(float value) const
    {
        vector3 result = *this;
        
        result.data[X] /= value;
        result.data[Y] /= value;
        result.data[Z] /= value;

        return result;
    }

    vector3 operator+(const vector3& other) const
    {
        vector3 result = *this;
        
        result.data[X] += other.data[X];
        result.data[Y] += other.data[Y];
        result.data[Z] += other.data[Z];

        return result;
    }

    vector3 operator-(const vector3& other) const
    {
        vector3 result = *this;
        
        result.data[X] -= other.data[X];
        result.data[Y] -= other.data[Y];
        result.data[Z] -= other.data[Z];

        return result;
    }

    float length() const { return sqrt(x() * x() + y() * y() + z() * z()); }

    float x() const { return data[X]; }
    float y() const { return data[Y]; }
    float z() const { return data[Z]; }
    
    float& x() { return data[X]; }
    float& y() { return data[Y]; }
    float& z() { return data[Z]; }
};

}

#endif // VECTOR3_HPP