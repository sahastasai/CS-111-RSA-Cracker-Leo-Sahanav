#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <cmath>
#include <vector>
#include <optional>
using namespace std;

long long extendedGCD(long long a, long long b, long long &x, long long &y); 
vector<pair<long long, long long> > factor(long long toFactor);
pair<long long, long long>* getPrimeFactorization(long long toFactor);
bool isPrime(long long toCheck);
long long modInverse(long long a, long long m);
long long modPow(long long base, long long exp, long long mod);
char decodeChar(long long num);
int main()
{
	long long e;
	long long n;
	long long m;
	string line3;

	cin >> e;
	cin >> n;
	cin >> m;
	vector<long long> message;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, line3);

	stringstream ss3(line3);
	string token;
	

	while(ss3 >> token)
	{
		message.push_back(stoll(token));
	}
	//Variables loaded and set
	
	pair<long long, long long>* pq = getPrimeFactorization(n);
	if(pq == nullptr)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	long long p = pq->first;
	long long q = pq->second;
	if(p == q)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	long long toMod = (p-1) * (q-1);
	if(e < 1 || e > toMod)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	//Now, we have everything we need to find d.
	
	long long d = modInverse(e, toMod);
	if(d < 0)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}

	cout << p << " " << q << " " << toMod << " " << d << endl;
	//Now to decode...
	vector<char> decodedChars;
	for(long long i = 0; i < m; i++)
	{
		cout << modPow(message[i], d, n) << " ";
		decodedChars.push_back(decodeChar(modPow(message[i], d, n)));
	}
	cout << endl;
	for(long long j = 0; j < m; j++)
	{		
		cout << decodedChars[j];
	}
	cout << endl;
	return 0;
		


}

long long modPow(long long base, long long exp, long long mod) {
    __int128 res = 1;          
    __int128 b = base % mod;      
    __int128 m = mod;          
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * b) % m;  
    	    exp /= 2;
        b = (b * b) % m;             }

    return (long long)res;        }

char decodeChar(long long num)
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

vector<pair<long long, long long> > factor(long long toFactor)
{
	long long sqr = (long long) sqrt(toFactor);
	vector<pair<long long, long long> > toReturn;
	for(long long i = 1; i <= sqr; i++)
	{
		if(!(modPow(toFactor, 1, i)))
		{
			toReturn.push_back(make_pair(i, toFactor/i));
		}
	}
	return toReturn;
}

pair<long long, long long>* getPrimeFactorization(long long toFactor)
{
	vector<pair<long long, long long> > sairam = factor(toFactor);
	pair<long long, long long> current;

	if(sairam.size() == 1)
	{
		return new pair<long long, long long>(sairam[0].first, sairam[0].second);
	}

	for(long long i = 1; i < sairam.size(); i++)
	{
		current = sairam[i];
		if(isPrime(current.first) && isPrime(current.second)){
			return new pair<long long, long long>(current.first, current.second);
		}
	}
	return nullptr; 
}

bool isPrime(long long toCheck)
{
	return (factor(toCheck).size() == 1);	
}

long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = extendedGCD(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}
