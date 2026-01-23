#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <cmath>
#include <vector>
using namespace std;
int main()
{
	string line1;
	string line2;
	string line3;

	cin >> line1;
	cin >> line2;
	cin >> line3;

	stringstream ss1(line1);
	//stringstream ss2(line2);
	stringstream ss3(line3);
	string token;
	
	int e = 0;
	int n = 0;
	while(ss1 >> token)
	{
		if(e){
			n = stoi(token);
		}else{
			e = stoi(token);
		}
	}

	int m = stoi(line2);

	vector<int> message;
	while(ss3 >> token)
	{
		message.push_back(stoi(token));
	}
	//Variables loaded and set
	
	pair<int, int> pq = getPrimeFactorization(n);
	int p = pq.first;
	int q = pq.second;
	int toMod = (p-1) * (q-1);
	//Now, we have everything we need to find d.
	
	int d = modInverse(e, toMod);

	//Now to decode...
	vector<int> decoded;
	for(int i = 0; i < m; i++)
	{
		decoded.push_back(pow(message[i], d) % n);
	}	



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

pair<int, int> getPrimeFactorization(int toFactor)
{
	vector<pair<int, int> > sairam = factor(toFactor);
	pair<int, int> current;

	if(sairam.size() == 1)
	{
		return sairam[0];
	}

	for(int i = 1; i < sairam.size(); i++)
	{
		current = sairam[i];
		if(isPrime(current.first) && isPrime(current.second)){
			return current;
		}
	}
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
