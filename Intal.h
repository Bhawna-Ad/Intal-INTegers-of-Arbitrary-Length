#include <iostream>
#include<string>
#include <sstream>
#include <vector>
#define MAX 1000
using namespace std;

class Intal
{
    //data members
    private:
    string val;

    public:
    //constructors
    Intal();
    Intal(string s);
    Intal(int n);

    //property methods
    void setValue(string str);
    const string& getValue();

    //methods
	bool EqualIntals (Intal a, Intal b);
    string AddIntals (string a, string b);
	string SubtractIntals (string a, string b);
	string MultiplyIntals(string a, string b);
	pair<string, long long> Intal::DivideIntals (string a, long long b);
    vector<int> FactorialIntals (string a);
};





//Constructors
Intal :: Intal()
    {
        val = "0";
    }

Intal ::  Intal(string s)
    {
       setValue(s);
    }

Intal:: Intal(int n) { 
    stringstream ss;
    string s;
    ss << n;
    ss >> s;

    if( isdigit(s[0]) ) { 
        setValue( s );
    } else {
        // setValue( s.substr(1) );
    }
}





    //property methods
void Intal :: setValue(string str)
{
    val = str;
}

const string& Intal :: getValue()
{
    return val;
}






//methods
bool EqualIntals (Intal a, Intal b)               
{
    return a.getValue() == b.getValue();
}

string Intal::AddIntals(string number1, string number2) {
    string add = (number1.length() > number2.length()) ?  number1 : number2;
    char carry = '0';
    int differenceInLength = abs( (int) (number1.size() - number2.size()) );

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left

    else// if(number1.size() < number2.size())
        number1.insert(0, differenceInLength, '0');

    for(int i=number1.size()-1; i>=0; --i) {
        add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

        if(i != 0) {
            if(add[i] > '9') {
                add[i] -= 10;
                carry = '1';
            } else
                carry = '0';
        }
    }
    if(add[0] > '9') {
        add[0]-= 10;
        add.insert(0,1,'1');
    }
    return add;
}

string Intal::SubtractIntals(string number1, string number2) {
    string sub = (number1.length()>number2.length())? number1 : number2;
    int differenceInLength = abs( (int)(number1.size() - number2.size()) );

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for(int i=number1.length()-1; i>=0; --i) {
        if(number1[i] < number2[i]) {
            number1[i] += 10;
            number1[i-1]--;
        }
        sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
    }

    while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
        sub.erase(0,1);

    return sub;
}

string Intal::MultiplyIntals(string n1, string n2) {
    if(n1.length() > n2.length())
        n1.swap(n2);

    string res = "0";
    for(int i=n1.length()-1; i>=0; --i) {
        string temp = n2;
        int currentDigit = n1[i]-'0';
        int carry = 0;

        for(int j=temp.length()-1; j>=0; --j) {
            temp[j] = ((temp[j]-'0') * currentDigit) + carry;

            if(temp[j] > 9) {
                carry = (temp[j]/10);
                temp[j] -= (carry*10);
            } else
                carry = 0;

            temp[j] += '0'; // back to string mood
        }

        if(carry > 0)
            temp.insert(0, 1, (carry+'0'));

        temp.append((n1.length()-i-1), '0'); 

        res = AddIntals(res, temp); 
    }

    while(res[0] == '0' && res.length()!=1) 
        res.erase(0,1);

    return res;
}

pair<string, long long> Intal::DivideIntals(string n, long long den) {
    long long rem = 0;
    string result;
    result.resize(MAX);

    for(int indx=0, len = n.length(); indx<len; ++indx) {
        rem = (rem * 10) + (n[indx] - '0');
        result[indx] = rem / den + '0';
        rem %= den;
    }
    result.resize( n.length() );

    while( result[0] == '0' && result.length() != 1)
        result.erase(0,1);

    if(result.length() == 0)
        result = "0";

    return make_pair(result, rem);
}

vector<int> FactorialIntals (string a){
    vector<int>v;
    v.push_back(1);
    int n = a.length();
    for(int x=2; x<=n; x++)
    {
        int carry=0;
        for(int i=0; i<v.size(); i++)
        {
            int prod = v[i]*x + carry;
            v[i] = prod%10;
            carry = prod/10;
        }
        while(carry)
        {
            v.push_back(carry%10);
            carry = carry/10;
        }
    }
    return v;
        
}
