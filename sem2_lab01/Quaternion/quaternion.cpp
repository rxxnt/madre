#include <iostream>
#include <cmath>
#include "quaternion.h"

using namespace std;

Quaternion::Quaternion(double s, double x, double y, double z) {
    a = s;
    b = x;
    c = y;
    d = z;
}

Quaternion::Quaternion(const Quaternion &q){
    a = q.a;
    b = q.b;
    c = q.c;
    d = q.d;
}

void Quaternion::set_quaternion(double sa, double sb, double sc, double sd){
    a = sa;
    b = sb;
    c = sc;
    d = sd;
};

void Quaternion::get_quaternion(double &sa, double &sb, double &sc, double &sd) const {
    sa = a;
    sb = b;
    sc = c;
    sd = d;
};

void Quaternion::print(){
    cout << a <<" + "<< b <<"i" <<" + "<< c <<"j" <<" + "<< d <<"k" <<endl;
}

double Quaternion::calculate_module(){
    return sqrt(a*a + b*b + c*c + d*d);
}

Quaternion Quaternion::conjugate(){
    return Quaternion(a,-b,-c,-d);
}

Quaternion Quaternion::norm_quaternion(){
    double module = calculate_module();
    return Quaternion(a/module, b/module, c/module, d/module);
}

Quaternion Quaternion::inverted_quaternion(){
    double mod = calculate_module();
    return Quaternion(a/pow(mod,2), -b/pow(mod,2), -c/pow(mod,2), -d/pow(mod,2));
}

Quaternion summa(Quaternion q1, Quaternion q2){
    return Quaternion(q1.a + q2.a, q1.b + q2.b, q1.c + q2.c, q1.d + q2.d);
}

Quaternion difference(Quaternion q1, Quaternion q2){
    return Quaternion(q1.a - q2.a, q1.b - q2.b, q1.c - q2.c, q1.d - q2.d);
}

Quaternion Quaternion_product(Quaternion q1, Quaternion q2){
    return Quaternion(q1.a*q2.a - q1.b*q2.b - q1.c*q2.c - q1.d*q2.d, q1.a*q2.b + q1.b*q2.a + q1.c*q2.d - q1.d*q2.c, q1.a*q2.c + q1.c*q2.a + q1.d*q2.b - q1.b*q2.d, q1.a*q2.d + q1.d*q2.a + q1.b*q2.c - q1.c*q2.b);
}

Quaternion Quaternion_division(Quaternion q1, Quaternion q2){
    return Quaternion_product(q1, q2.inverted_quaternion());
}

double scalar_product(Quaternion q1, Quaternion q2){
    return q1.a*q2.a + q1.b*q2.b + q1.c*q2.c + q1.d*q2.d;
}

double euclidean_dist(Quaternion q1, Quaternion q2){
    return sqrt(pow(q1.a - q2.a, 2) + pow(q1.b - q2.b, 2) + pow(q1.c - q2.c, 2) + pow(q1.d - q2.d, 2));
}

double norma_Chebisheva(Quaternion q1, Quaternion q2){
    double max = -1;
    double dif[4] = {abs(q1.a-q2.a), abs(q1.b-q2.b),abs(q1.c-q2.c),abs(q1.d-q2.d)};
    for (int i = 0; i < 4; i++){
        if (dif[i] > max){
            max = dif[i];
        }
    }
    return max;
}