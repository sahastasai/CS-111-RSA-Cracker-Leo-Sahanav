#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
#include <optional>
using namespace std;

__int128 extendedGCD(__int128 a, __int128 b, __int128 &x, __int128 &y); 
vector<pair<__int128, __int128> > factor(__int128 toFactor);
pair<__int128, __int128>* getPrimeFactorization(__int128 toFactor);
bool isPrime(__int128 toCheck);
__int128 modInverse(__int128 a, __int128 m);
__int128 modPow(__int128 base, __int128 exp, __int128 mod);
char decodeChar(__int128 num);
istream& operator>>(istream& is, __int128& v);
ostream& operator<<(ostream& os, const __int128& v);
int main()
{
	__int128 e;
	__int128 n;
	__int128 m;
	string line3;

	cin >> e;
	cin >> n;
	cin >> m;
	vector<__int128> message;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, line3);

	stringstream ss3(line3);
	string token;
	

	while(ss3 >> token)
	{
		message.push_back(stoll(token));
	}
	//Variables loaded and set
	
	pair<__int128, __int128>* pq = getPrimeFactorization(n);
	if(pq == nullptr)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	__int128 p = pq->first;
	__int128 q = pq->second;
	if(p == q)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	__int128 toMod = (p-1) * (q-1);
	if(e < 1 || e > toMod)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	//Now, we have everything we need to find d.
	
	__int128 d = modInverse(e, toMod);
	if(d < 0)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}

	cout << p << " " << q << " " << toMod << " " << d << endl;
	//Now to decode...
	vector<char> decodedChars;
	for(__int128 i = 0; i < m; i++)
	{
		cout << modPow(message[i], d, n) << " ";
		decodedChars.push_back(decodeChar(modPow(message[i], d, n)));
	}
	cout << endl;
	for(__int128 j = 0; j < m; j++)
	{		
		cout << decodedChars[j];
	}
	cout << endl;
	return 0;
		


}

__int128 modPow(__int128 base, __int128 exp, __int128 mod) {
    __int128 res = 1;          
    __int128 b = base % mod;      
    __int128 m = mod;          
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * b) % m;  
    	    exp /= 2;
        b = (b * b) % m;             }

    return (__int128)res;        }

char decodeChar(__int128 num)
{
    if(num >= 6 && num <= 26+6)
        return 'A' + (num - 7);
    else if(num == 33)
        return ' ';
    else if(num == 34)
        return '"';
    else if(num == 37)
        return '\'';
    else
        return (char)(int)num; }

vector<pair<__int128, __int128> > factor(__int128 toFactor)
{
	__int128 sqr = (__int128) sqrt(toFactor);
	vector<pair<__int128, __int128> > toReturn;
	for(__int128 i = 1; i <= sqr; i++)
	{
		if(!(modPow(toFactor, 1, i)))
		{
			toReturn.push_back(make_pair(i, toFactor/i));
		}
	}
	return toReturn;
}

pair<__int128, __int128>* getPrimeFactorization(__int128 toFactor)
{
	vector<pair<__int128, __int128> > sairam = factor(toFactor);
	pair<__int128, __int128> current;

	if(sairam.size() == 1)
	{
		return new pair<__int128, __int128>(sairam[0].first, sairam[0].second);
	}

	for(__int128 i = 1; i < sairam.size(); i++)
	{
		current = sairam[i];
		if(isPrime(current.first) && isPrime(current.second)){
			return new pair<__int128, __int128>(current.first, current.second);
		}
	}
	return nullptr; 
}

bool isPrime(__int128 toCheck)
{
	return (factor(toCheck).size() == 1);	
}

__int128 extendedGCD(__int128 a, __int128 b, __int128 &x, __int128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    __int128 x1, y1;
    __int128 gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}
__int128 modInverse(__int128 a, __int128 m) {
    __int128 x, y;
    __int128 g = extendedGCD(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

istream& operator>>(istream& is, __int128& v) {
    string s;
    is >> s;
    v = 0;
    int start = (s[0] == '-') ? 1 : 0;
    for (size_t i = start; i < s.size(); ++i) {
        v = v * 10 + (s[i] - '0');
    }
    if (s[0] == '-') {
        v = -v;
    }
    return is;
}

ostream& operator<<(ostream& os, const __int128& v) {
    if (v == 0) {
        return os << "0";
    }
    __int128 temp = v;
    if (temp < 0) {
        os << "-";
        temp = -temp;
    }
    string s;
    while (temp > 0) {
        s += (char)((temp % 10) + '0');
        temp /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}