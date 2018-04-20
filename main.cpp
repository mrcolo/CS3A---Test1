#include <iostream>
#include "polynomial.h"

using namespace std;

int main()
{
    int i = 1;
    polynomial x("123x^2 3x^3 2x^4 4");
    cout<<"Initial Polynomial: "<<endl<<endl<<x<<endl<<endl;
    cout<<x.returnDerivative(1);
    return 0;
}
