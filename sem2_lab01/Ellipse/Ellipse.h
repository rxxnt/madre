#pragma once
#include <iostream>
#include <cmath>

class Ellipse {
    private:
        double h;
        double k;
        double a;
        double b;
        double c;
    
    public:
        Ellipse();
        Ellipse(double h, double k, double a, double b);
        Ellipse(const Ellipse &el);
        ~Ellipse();

        void set_h(double h);
        void set_k(double k);
        void set_a(double a);
        void set_b(double b);

        double get_h() const;
        double get_k() const;
        double get_a() const;
        double get_b() const;

        double get_c() const;

        std::pair<std::pair<double, double>, std::pair<double, double>> get_vertices();
        std::pair<std::pair<double, double>, std::pair<double, double>> get_focuses();

        double focal_chord_length();
        double eccentricity();

        void print();

        std::string where_is_point(double x, double y);

        double approximate_perimeter();

        double area();

        double second_coordinate(double coord, bool isX);
};
