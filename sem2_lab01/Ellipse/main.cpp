#include <iostream>
#include <cmath>
#include "Ellipse.h"

int main() {
    Ellipse ellipse(0., 0., 5., 3.); 

    ellipse.print();
    std::cout << "Focal chord length: " << ellipse.focal_chord_length() << "\n";
    std::cout << "Eccentricity: " << ellipse.eccentricity() << "\n";
    std::cout << "Point (2, 1) is " << ellipse.where_is_point(2,1) << "\n";
    std::cout << "Approximate perimeter: " << ellipse.approximate_perimeter() << "\n";
    std::cout << "Area: " << ellipse.area() << "\n";

    double y = ellipse.second_coordinate(2, true); 
    std::cout << "For x=2, y=" << y << "\n";
    return 0;
}