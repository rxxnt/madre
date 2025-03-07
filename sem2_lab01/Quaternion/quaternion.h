#pragma once

class Quaternion{
    public:
        double a,b,c,d;

    public:
        Quaternion(double a = 1, double b = 0, double c = 0, double d = 0);
        Quaternion(const Quaternion &q);
        void set_quaternion(double sa, double sb, double sc, double sd);
        void get_quaternion(double &sa, double &sb, double &sc, double &sd) const;
        void print();
        double calculate_module();
        Quaternion conjugate();
        Quaternion norm_quaternion();
        Quaternion inverted_quaternion();
};

Quaternion summa(Quaternion q1, Quaternion q2);
Quaternion difference(Quaternion q1, Quaternion q2);
Quaternion Quaternion_product(Quaternion q1, Quaternion q2);
Quaternion Quaternion_division(Quaternion q1, Quaternion q2);
double scalar_product(Quaternion q1, Quaternion q2);
double euclidean_dist(Quaternion q1, Quaternion q2);
double norma_Chebisheva(Quaternion q1, Quaternion q2);

