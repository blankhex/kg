#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace kg
{

struct vector4
{
    float data[4];

    enum 
    {
        X,
        Y,
        Z,
        W
    };

    vector4() { data[X] = data[Y] = data[Z] = data[W] = 0.0f; }
    vector4(float value) { data[X] = data[Y] = data[Z] = data[W] = value; }
    vector4(float x, float y, float z = 0.0f, float w = 0.0f)
    {
        data[X] = x;
        data[Y] = y;
        data[Z] = z;
        data[W] = w;
    }

    vector4& operator*=(float value) 
    {
        data[X] *= value;
        data[Y] *= value;
        data[Z] *= value;
        data[W] *= value;

        return *this;
    }

    vector4& operator/=(float value) 
    {
        data[X] /= value;
        data[Y] /= value;
        data[Z] /= value;
        data[W] /= value;

        return *this;
    }

    vector4& operator+=(const vector4& other)
    {
        data[X] += other.data[X];
        data[Y] += other.data[Y];
        data[Z] += other.data[Z];
        data[W] += other.data[W];

        return *this;
    }

    vector4& operator-=(const vector4& other)
    {
        data[X] -= other.data[X];
        data[Y] -= other.data[Y];
        data[Z] -= other.data[Z];
        data[W] -= other.data[W];

        return *this;
    }

    vector4 operator*(float value) const
    {
        vector4 result = *this;
        
        result.data[X] *= value;
        result.data[Y] *= value;
        result.data[Z] *= value;
        result.data[W] *= value;

        return result;
    }

    vector4 operator/(float value) const
    {
        vector4 result = *this;
        
        result.data[X] /= value;
        result.data[Y] /= value;
        result.data[Z] /= value;
        result.data[W] /= value;

        return result;
    }

    vector4 operator+(const vector4& other) const
    {
        vector4 result = *this;
        
        result.data[X] += other.data[X];
        result.data[Y] += other.data[Y];
        result.data[Z] += other.data[Z];
        result.data[W] += other.data[W];

        return result;
    }

    vector4 operator-(const vector4& other) const
    {
        vector4 result = *this;
        
        result.data[X] -= other.data[X];
        result.data[Y] -= other.data[Y];
        result.data[Z] -= other.data[Z];
        result.data[W] -= other.data[W];

        return result;
    }

    vector3 vector3() const 
    {
        return kg::vector3(x(), y(), z());
    }

    float length() const { return sqrt(x() * x() + y() * y() + z() * z() + w() * w()); }

    float x() const { return data[X]; }
    float y() const { return data[Y]; }
    float z() const { return data[Z]; }
    float w() const { return data[W]; }
    
    float& x() { return data[X]; }
    float& y() { return data[Y]; }
    float& z() { return data[Z]; }
    float& w() { return data[W]; }
};

}

#endif // VECTOR3_HPP