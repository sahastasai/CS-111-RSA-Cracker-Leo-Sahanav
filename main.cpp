#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <cmath>
#include <vector>
#include <optional>
using namespace std;

int extendedGCD(int a, int b, int &x, int &y); 
vector<pair<int, int> > factor(int toFactor);
pair<int, int>* getPrimeFactorization(int toFactor);
bool isPrime(int toCheck);
int modInverse(int a, int m);
int modPow(int base, int exp, int mod);
char decodeChar(int num);
int main()
{
	int e;
	int n;
	int m;
	string line3;

	cin >> e;
	cin >> n;
	cin >> m;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, line3);

	stringstream ss3(line3);
	string token;
	

	vector<int> message;
	while(ss3 >> token)
	{
		message.push_back(stoi(token));
	}
	//Variables loaded and set
	
	pair<int, int>* pq = getPrimeFactorization(n);
	if(pq == nullptr)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	int p = pq->first;
	int q = pq->second;
	if(p == q)
	{
	
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	int toMod = (p-1) * (q-1);
	if(e < 1 || e > toMod)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}
	//Now, we have everything we need to find d.
	
	int d = modInverse(e, toMod);
	if(d < 0)
	{
		cout << "Public key is not valid!" << endl;
		return 1;
	}

	cout << p << " " << q << " " << toMod << " " << d << endl;
	//Now to decode...
	vector<char> decodedChars;
	for(int i = 0; i < m; i++)
	{
		cout << modPow(message[i], d, n) << " ";
		decodedChars.push_back(decodeChar(modPow(message[i], d, n)));
	}
	cout << endl;
	for(int j = 0; j < m; j++)
	{		
		cout << decodedChars[j];
	}
	cout << endl;

	


}
int modPow(int base, int exp, int mod) {
	long long  res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
   		res = (res * b) % mod;
        exp /= 2;
        b = (b * b) % mod;
    }
    return (int)res;
}
char decodeChar(int num)
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
        return '?'; // fallback for unexpected values
}

vector<pair<int, int> > factor(int toFactor)
{
	int sqr = (int) sqrt(toFactor);
	vector<pair<int, int> > toReturn;
	for(int i = 1; i <= sqr; i++)
	{
		if(!(toFactor % i))
		{
			toReturn.push_back(make_pair(i, toFactor/i));
		}
	}
	return toReturn;
}

pair<int, int>* getPrimeFactorization(int toFactor)
{
	vector<pair<int, int> > sairam = factor(toFactor);
	pair<int, int> current;

	if(sairam.size() == 1)
	{
		return new pair<int, int>(sairam[0].first, sairam[0].second);
	}

	for(int i = 1; i < sairam.size(); i++)
	{
		current = sairam[i];
		if(isPrime(current.first) && isPrime(current.second)){
			return new pair<int, int>(current.first, current.second);
		}
	}
	return nullptr; 
}

bool isPrime(int toCheck)
{
	return (factor(toCheck).size() == 1);	
}

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int modInverse(int a, int m) {
    int x, y;
    int g = extendedGCD(a, m, x, y);

    if (g != 1) return -1;  
    return (x % m + m) % m;
}
