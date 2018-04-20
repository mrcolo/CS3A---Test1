#include <iostream>
#include "polynomial.h"

using namespace std;
void differentiate(polynomial x, int& i);
int main()
{
    int i = 1;
    polynomial x("123x^2 3x^3 2x^4 4");
    cout<<"Initial Polynomial: "<<endl<<endl<<x<<endl<<endl;
    differentiate(x,i);
    return 0;
}
void differentiate(polynomial x, int& i){
    polynomial new_derivative (x.derivative());
    if(!new_derivative.empty()){
        cout<<i<<" Derivative:"<<endl<<endl;
        cout<<new_derivative<<endl<<endl;

        i++;
        differentiate(new_derivative,i);
    }
    else{
        cout<<i<<" Derivative:"<<endl<<endl;
        cout<<"0"<<endl;

    }
}
