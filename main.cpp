#include <iostream>
#include "polynomial.h"

using namespace std;

int main()
{
    int i = 1;
    try
    {

        polynomial t;
        cin>>t;
        cout<<t;
    }
    catch (string e)
    {
        cout << "ERROR:"<<endl<<e<<endl;
    }

    return 0;
}
