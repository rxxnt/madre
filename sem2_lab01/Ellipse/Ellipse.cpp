#include "Ellipse.h"
#include <iostream>
#include <cmath>

Ellipse::Ellipse() : h(0), k(0) {}
Ellipse::Ellipse(double h, double k, double a, double b) : h(h), k(k) {
    if (a > b) {
        this->a = a;
        this->b = b;
    } else {
        this->a = b;
        this->b = a;
    }
    this->c = sqrt(this->a * this->a - this->b * this-> b);
}
Ellipse::Ellipse(const Ellipse &el) : h(el.h), k(el.k), a(el.a), b(el.b), c(el.c) {}

Ellipse::~Ellipse() {}

void Ellipse::set_h(double h) { this->h = h; }
void Ellipse::set_k(double k) { this->k = k; }
void Ellipse::set_a(double a) {
    if (a > b) this->a = a;
    else {
        this->b = a;
        this->a = b;
    }
    this->c = sqrt(this->a * this->a - this->b * this->b);
}
void Ellipse::set_b(double b) {
    if (b < a) this->b = b;
    else {
        this->a = b;
        this->b = a;
    }
    this->c = sqrt(this->a * this->a - this->b * this->b);
}

double Ellipse::get_h() const { return h; }
double Ellipse::get_k() const { return k; }
double Ellipse::get_a() const { return a; }
double Ellipse::get_b() const { return b; }

double Ellipse::get_c() const { return c; }

std::pair<std::pair<double, double>, std::pair<double, double>> Ellipse::get_vertices() {
    if (a > b) return { {h - a, k}, {h + a, k} };
    else return { {h, k - a}, {h, k + a} };
}
std::pair<std::pair<double, double>, std::pair<double, double>> Ellipse::get_focuses() {
    if (a > b) return { {h - c, k}, {h + c, k} };
    else return { {h, k - c}, {h, k + c} };
}

double Ellipse::focal_chord_length() { return (2 * b * b) / a; }

double Ellipse::eccentricity() { return c / a;}

void Ellipse::print() {
    if (a > b) {
    std::cout << "((x - " << h << ")^2 / " << a * a << ") + ((y - " << k << ")^2 / " << b * b << ") = 1\n";
    } else {
        std::cout << "((x - " << h << ")^2 / " << b * b << ") + ((y - " << k << ")^2 / " << a * a << ") = 1\n";
    }
    std::cout << "Center: (" << h << ", " << k << ")\n";
    auto vertices = get_vertices();
    std::cout << "Vertices: (" << vertices.first.first << ", " << vertices.first.second << ") and ("
              << vertices.second.first << ", " << vertices.second.second << ")\n";
    auto focuses = get_focuses();
    std::cout << "Focuses: (" << focuses.first.first << ", " << focuses.first.second << ") and ("
              << focuses.second.first << ", " << focuses.second.second << ")\n";
}

std::string Ellipse::where_is_point(double x, double y) {
    double xh = x - h;
    double yk = y - k;
    if (a > b) {
        if ((xh * xh / (a * a) + yk * yk / (b * b)) == 1) {
            return "on ellipse";
        } else if ((xh * xh / (a * a) + yk * yk / (b * b)) <= 1) {
            return "inside ellipse";
        } else return "outside ellipse";
    } else {
        if ((xh * xh / (b * b) + yk * yk / (a * a)) == 1) {
            return "on ellipse";
        } else if ((xh * xh / (b * b) + yk * yk / (a * a)) <= 1) {
            return "inside ellipse";
        } else return "outside ellipse";
    }
}

double Ellipse::approximate_perimeter() {
    return M_PI * round( 3 * (a + b) - sqrt( (3 * a + b) * (a + 3 * b)));
}

double Ellipse::area() {
    return M_PI * a * b;
}

double Ellipse::second_coordinate(double coord, bool isX) {
    if (isX) {
        double xh = coord - h;
        if (a > b) {
            return k + b * sqrt( (1 - (xh * xh) / (a * a)) );
        } else {
            return k + a * sqrt( (1 - (xh * xh) / (b * b)) );
        }
    } else {
        double yk = coord - k;
        if (a > b) {
            return h + a * sqrt( (1 - (yk * yk) / (b * b)) );
        } else {
            return h + b * sqrt( (1 - (yk * yk) / (a * a)) );
        }
    }
}