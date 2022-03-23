#ifndef EASING_HPP
#define EASING_HPP

#include <functional>

namespace kg
{

template<typename T>
T ease(T from, T to, float t, std::function<float(float)> func)
{
    T delta = to - from;
    return from + (delta * func(t));
}

float ease_in_sine(float t);
float ease_out_sine(float t);
float ease_in_out_sine(float t);
float ease_in_quad(float t);
float ease_out_quad(float t);
float ease_in_out_quad(float t);
float ease_in_cubic(float t);
float ease_out_cubic(float t);
float ease_in_out_cubic(float t);
float ease_in_quart(float t);
float ease_out_quart(float t);
float ease_in_out_quart(float t);
float ease_in_quint(float t);
float ease_out_quint(float t);
float ease_in_out_quint(float t);
float ease_in_expo(float t);
float ease_out_expo(float t);
float ease_in_out_expo(float t);
float ease_in_circ(float t);
float ease_out_circ(float t);
float ease_in_out_circ(float t);
float ease_in_back(float t);
float ease_out_back(float t);
float ease_in_out_back(float t);
float ease_in_elastic(float t);
float ease_out_elastic(float t);
float ease_in_out_elastic(float t);
float ease_in_bounce(float t);
float ease_out_bounce(float t);
float ease_in_out_bounce(float t);

}

#endif // EASING_HPP