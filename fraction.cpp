#include "fraction.h"

fraction::fraction(int n, int d) //Two argument constructor
{
    num = n;
    denom = d;
    reduce();
}

fraction::fraction(double x)
{
    stringstream ss;
    ss<<x;
    string ans;
    ss>>ans;
    cout<<"Fraction to modify: "<<ans<<endl;
    stringToFraction(ans);
}

fraction::fraction(string x)
{
    stringToFraction(x);
}

void fraction::stringToFraction(string x)
{
    char junk;
    int whole, decimal,counter = -1;
    bool isSlash = false, isDot = false, isNothing = false;
    stringstream ss;
    for(int i = 0; i < x.length();i++){
        if(x[i] == '.'){
            isDot = true;
        }
        if(x[i] == '/')
            isSlash = true;
        if(isDot)
            counter++;
        if(i == x.length()-1 && !isSlash && !isDot){
            isNothing = true;
        }
    }
    //use isSlash to evaluate only one point.
    if(isSlash){
        ss<<x;
        ss>>num>>junk>>denom;
    }
    if(isDot){
        ss<<x;
        ss>>whole>>junk>>decimal;
        denom = (int)pow(10,counter);
        num = denom*whole+decimal;
        reduce();

    }
    if(isNothing){
        ss<<x;
        ss>>num;
        denom = 1;
    }

}

fraction::~fraction() // Destructor
{

}

fraction::fraction(const fraction& other) // Copy constructor
{
    //DEBUG : cout<<"Copy constructor fired!"<<endl;
    num = other.num;
    denom = other.denom;
}

//Return by reference allows for "chaining"
//x = y = z = 2;
fraction& fraction::operator=(const fraction& other) //Assignment operator
{
     if(this != &other)
     {
         num = other.num;
         denom = other.denom;
     }
     return *this;
}

fraction& fraction::operator+=(const fraction& other) //Assignment operator
{
    *this = *this + other;
    return *this;
}

fraction& fraction::operator-=(const fraction& other)
{
    *this = *this - other;
    return *this;
}

fraction& fraction::operator/=(const fraction& other)
{
    *this = *this / other;
    return *this;
}

fraction& fraction::operator*=(const fraction& other)
{
    *this = *this * other;
    return *this;
}

void fraction::set(int n, int d) //Mutator - 2 argument
{
    num = n;
    denom = d;
    reduce();
}


int fraction::getNum() const//Accessor
{
    return num;
}

int fraction::getDenom() const//Accessor
{
    return denom;
}

void fraction::display() const//Display values
{
    cout<<num;
    if(denom != 1)
    {
        cout<<"/"<<denom<<" ";
    }
}

void fraction::input()//Get fraction from keyboard
{
    char junk;
    cin>>num>>junk>>denom;
}

void fraction::reduce() //Helper function
{
    int div = gcd(num,denom);
    num /= div;
    denom /= div;
    if(denom < 0)
    {
        num *= -1;
        denom *= -1;
    }
}

int fraction::gcd(int p, int q)//Helper function
{
    return q==0? p : gcd(q, p%q);
}
