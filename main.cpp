#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <cmath>
#include <vector>
#include <optional>
using namespace std;

long int extendedGCD(long int a, long int b, long int &x, long int &y); 
vector<pair<long int, long int> > factor(long int toFactor);
pair<long int, long int>* getPrimeFactorization(long int toFactor);
bool isPrime(long int toCheck);
long int modInverse(long int a, long int m);
long int modPow(long int base, long int exp, long int mod);
char decodeChar(long int num);
int main()
{
	long int e;
	long int n;
	size_t m;

	long int line3;

	cin >> e;
	cin >> n;
	cin >> m;

	vector<long int> message;
	
	while(message.size() != m && cin >> line3)
	{
		message.push_back(line3);
	}

	//Variables loaded and set
	
	pair<long int, long int>* pq = getPrimeFactorization(n);
	if(pq == nullptr)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}

	long int p = pq->first;
	long int q = pq->second;
	
	if(p == q)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	long int toMod = (p-1) * (q-1);
	if(e < 1 || e > toMod)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	//Now, we have everything we need to find d.
	
	long int d = modInverse(e, toMod);
	if(d < 0)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}

	cout << p << " " << q << " " << toMod << " " << d << endl;
	//Now to decode...
	vector<char> decodedChars;
	for(long int i = 0; i < m; i++)
	{
		cout << modPow(message[i], d, n) << " ";
		decodedChars.push_back(decodeChar(modPow(message[i], d, n)));
	}
	cout << endl;
	for(long int j = 0; j < m; j++)
	{		
		cout << decodedChars[j];
	}
	cout << endl;
	return 0;
		


}

long int modPow(long int base, long int exp, long int mod) {
    
	long long res = 1;          
    long long b = base % mod;      
    long long m = mod;

    while (exp > 0) {
        
		if (exp % 2 == 1){
			
			res = (res * b) % m;
		
			exp--;

		}
			
		exp /= 2;
        
		b = (b * b) % m;

	}

    return (long int)res;        }

char decodeChar(long int num)
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

vector<pair<long int, long int> > factor(long int toFactor)
{
	long int sqr = (long int) sqrt(toFactor);
	vector<pair<long int, long int> > toReturn;
	for(long int i = 1; i <= sqr; i++)
	{
		if(!(modPow(toFactor, 1, i)))
		{
			toReturn.push_back(make_pair(i, toFactor/i));
		}
	}
	return toReturn;
}

pair<long int, long int>* getPrimeFactorization(long int toFactor)
{
	vector<pair<long int, long int> > sairam = factor(toFactor);
	pair<long int, long int> current;

	if(sairam.size() == 1)
	{
		return new pair<long int, long int>(sairam[0].first, sairam[0].second);
	}

	for(long int i = 1; i < sairam.size(); i++)
	{
		current = sairam[i];
		if(isPrime(current.first) && isPrime(current.second)){
			return new pair<long int, long int>(current.first, current.second);
		}
	}
	return nullptr; 
}

bool isPrime(long int toCheck)
{
	return (factor(toCheck).size() == 1);	
}

long int extendedGCD(long int a, long int b, long int &x, long int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long int x1, y1;
    long int gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}
long int modInverse(long int a, long int m) {
    long int x, y;
    long int g = extendedGCD(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}