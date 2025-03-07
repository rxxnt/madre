#include <iostream>
#include <cmath>
#include "quaternion.h"

using namespace std;

int main(){
    Quaternion q1, q2;
    q1 = Quaternion(1,4,4,4);
    q2 = Quaternion(2,5,2,4);
    cout << "Quaternion q1: " << endl;
    q1.print();
    cout << "Quaternion q2: " << endl;
    q2.print();
    cout << "\n";

    cout << "Module q1 = " << q1.calculate_module() << "\n";
    cout << "Module q2 = " << q2.calculate_module() << "\n";
    cout << "\n";

    cout << "Conjugate q1: " << endl;
    q1.conjugate().print();
    cout << "Conjugate q2: " << endl;
    q2.conjugate().print();
    cout << "\n";

    cout << "norm(q1): " << endl;
    q1.norm_quaternion().print();
    cout << "norm(q2): " << endl;
    q2.norm_quaternion().print();
    cout << "\n";

    cout << "Inverted quaternion q1: " << endl;
    q1.inverted_quaternion().print();
    cout << "Inverted quaternion q2: " << endl;
    q2.inverted_quaternion().print();
    cout << "\n";

    cout << "q1 + q2: " << endl;
    summa(q1,q2).print();
    cout << "q1 - q2: " << endl;
    difference(q1,q2).print();
    cout << "q1 x q2: " << endl;
    Quaternion_product(q1,q2).print();
    cout << "q1 / q2: " << endl;
    Quaternion_division(q1,q2).print();
    cout << "q1 . q2: " << endl;
    cout << scalar_product(q1,q2);

    cout << "\n\n";
    q1.set_quaternion(1,2,3,4);
    cout << "Quaternion q1: " << endl;
    q1.print();
    cout << "\n";


    double t,x,y,z;
    q1.get_quaternion(t,x,y,z);
    cout << "a = " << t << " , b = " << x << " , c = " << y << " , d = " << z;
}