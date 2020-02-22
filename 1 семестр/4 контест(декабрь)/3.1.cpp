/*  Высокая пирамида
Дано N кубиков.Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.*/
#include <vector>
#include <string>
#include <iostream>
using namespace std;
long long result(long long n) {
	vector<vector<long long>> matrix;
	vector <long long> j(n+1);
	for (int i = 0; i <= n; ++i) {
		matrix.push_back(j);
	}
	(matrix[0])[0] = 1;
	for (int i = 1; i <= n; ++i) {
		(matrix[0])[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			// у нас есть известная рекурентная формула. P(n,k)=P1(n,k-1)+P2(n-k,k) 
			long long P1 = (matrix[i-1])[j];
			long long P2;
			if ((j - i) < 0) {
				P2 = 0;
			}
			else {
				P2 = (matrix[i])[j-i];
			}
			(matrix[i])[j] = P1 + P2;
		}
	}
	return ((matrix[n])[n]);
}
int main() {
	long long n;
	cin >> n;
	long long res = result(n);
	cout << res;
}