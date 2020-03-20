/*Напишите класс BigInteger для работы с длинными целыми числами.Должны поддерживаться операции :
сложение, вычитание, умножение, деление, остаток по модулю, работающие так же, как и для int; составное присваивание с этими операциями.
Умножение должно работать за o - малое от n2.
унарный минус, префиксный и постфиксный инкремент и декремент.Префиксный инкремент и декремент должны работать за O(1) в среднем.
операторы сравнения == != < > <= >=
вывод в поток и ввод из потока
метод toString(), возвращающий строковое представление числа
конструирование из int(в том числе неявное преобразование, когда это надо)
неявное преобразование в bool, когда это надо(должно работать в условных выражениях)
опционально - литеральный суффикс bi для написания литералов типа BigInteger, см.справку здесь https ://en.cppreference.com/w/cpp/language/user_literal
Используя класс BigInteger, напишите класс Rational для работы с рациональными числами сколь угодно высокой точности.
Числа Rational должны представляться в виде несократимых обыкновенных дробей, где числитель и знаменатель – сколь угодно длинные целые числа.
Должны поддерживаться операции :конструктор из BigInteger, из int
сложение, вычитание, умножение, деление, составное присваивание с этими операциями
унарный минус
операторы сравнения == != < > <= >=
метод toString(), возвращающий строковое представление числа(вида[минус]числитель / знаменатель),
где числитель и знаменатель - взаимно простые числа; если число на самом деле целое, то знаменатель выводить не надо
метод asDecimal(sizet precision = 0), возвращающий строковое представление числа в виде десятичной дроби с precision знаками после запятой
оператор приведения к double
В вашем файле должна отсутствовать функция main(), а сам файл должен называться biginteger.h.В качестве компилятора необходимо указывать Make.
Ваш код будет вставлен посредством команды #include<biginteger.h> в программу, содержащую тесты; вследствие этого код необходимо отправлять
в файле со строго соответствующим именем!*/

#include <iostream>
#include <vector>
#include <string>
class BigInteger;
bool operator < (const BigInteger& x, const BigInteger& y);
bool operator == (const BigInteger& x, const BigInteger& y);
bool operator <= (const BigInteger& x, const BigInteger& y);
bool operator >= (const BigInteger& x, const BigInteger& y);
bool operator > (const BigInteger& x, const BigInteger& y);
const BigInteger operator + (const BigInteger& x, const BigInteger& y);
const BigInteger operator - (const BigInteger& x, const BigInteger& y);
const BigInteger operator * (const BigInteger& x, const BigInteger& y);
const BigInteger operator / (const BigInteger& x, const BigInteger& y);
class BigInteger {
private:
	std::vector<long long> place;
	long long max_number = 1000000000;
	int n = 9;// т.к 10 в  9
	int size_of_place = 0;
	bool sign;//true это + или 0. false это -
public:
	BigInteger() {
		place.push_back(0);
	}
	BigInteger(int x) {
		int y = std::abs(x);
		if (x < 0) {
			sign = false;
		}
		else {
			sign = true;
		}
		if (y >= max_number) {
			place.push_back(y - max_number);
			place.push_back(y / max_number);
			size_of_place = 2;
		}
		else {
			place.push_back(y);
			size_of_place = 1;
		}
	}
	BigInteger(std::string& s) {
		char now[9];
		if (s[0] != '-') {
			sign = true;
			int i = 0;
			ptrdiff_t j = s.size() - 1;
			for (j; j >= 0; --j) {
				++i;
				now[n - i] = s[j];
				if (i == n) {
					int number = std::atoi(now);
					place.push_back(number);
					i = 0;
				}
				if (j == 0 && i != 0) {
					int number = 0;
					int POW = 1;
					for (int l = 0; l < i; ++l) {
						number += ((now[n - 1 - l] - '0') * POW);
						POW *= 10;
					}
					place.push_back(number);
				}
			}
		}
		else {
			sign = false;
			int i = 0;
			ptrdiff_t j = s.size() - 1;
			for (j; j >= 1; --j) {
				++i;
				now[n - i] = s[j];
				if (i == n) {
					int number = std::atoi(now);
					place.push_back(number);
					i = 0;
				}
				if (j == 1 && i != 0) {
					int number = 0;
					int POW = 1;
					for (int l = 0; l < i; ++l) {
						number += ((now[n - 1 - l] - '0') * POW);
						POW *= 10;
					}
					place.push_back(number);
				}
			}
		}
		size_of_place = place.size();
	}
	bool signOut() const {
		return(sign);
	}
	std::string toString() {
		std::string s;
		if (sign == false) {
			s += "-";
		}
		for (int i = place.size() - 1; i >= 0; --i) {
			std::string little_string = std::to_string(place[i]);
			if (i == place.size() - 1) {
				s += little_string;
			}
			else {
				int j = n - little_string.size();
				for (j; j > 0; --j) {
					s += "0";
				}
				s += little_string;
			}
		}
		return(s);
	}
	BigInteger operator -() const {
		BigInteger x = *this;
		x.sign = (x.sign == true ? false : true);
		return(x);
	}
	BigInteger& PlusABS(const BigInteger& x) {
		int perenos = 0;
		int  i = 0;
		while (x.place.size() > i || place.size() > i) {
			if (place.size() <= i) {
				place.push_back(0);
			}
			if (x.place.size() <= i) {
				place[i] += perenos;
				perenos = 0;
			}
			else {
				place[i] += (x.place[i] + perenos);
				perenos = 0;
			}
			if (place[i] >= max_number) {
				perenos = place[i] / max_number;
				place[i] %= (max_number);
			}
			++i;
		}
		if (perenos > 0) {
			place.push_back(perenos);
		}
		size_of_place = place.size();
		return *this;
	}
	std::vector<long long> MinusABS(const BigInteger& x, const BigInteger& y) {//тут мы будем разницу по модулю искать
		std::vector<long long> now;
		int dop = 0;
		int i = 0;
		while (y.place.size() > i) {
			if (x.place[i] - dop < y.place[i]) {
				now.push_back(x.place[i] + max_number - dop - y.place[i]);
				dop = 1;
			}
			else {
				now.push_back(x.place[i] - dop - y.place[i]);
				dop = 0;
			}
			++i;
		}
		for (i; i < x.place.size(); ++i) {
			if ((i + 1 == x.size_of_place) && (x.place[i] - dop == 0)) {
			}
			else if (x.place[i] - dop >= 0) {
				now.push_back(x.place[i] - dop);
				dop = 0;
			}
			else {
				now.push_back(x.place[i] + max_number - dop);
				dop = 1;
			}
		}
		for (int j = now.size() - 1; j >= 0; --j) {
			if (now[j] == 0 && j != 0) {
				now.pop_back();
			}
			else {
				break;
			}
		}
		return(now);
	}
	BigInteger& operator +=(const BigInteger& x) {
		BigInteger& y = *this;
		if ((x.sign == true && sign == true) || (x.sign == false && sign == false)) {
			return(PlusABS(x));
		}
		else if (sign == false && x.sign == true) {
			if (-y > x) {
				place = MinusABS(y, x);
				size_of_place = place.size();
			}
			else {
				place = MinusABS(x, y);
				sign = true;
				size_of_place = place.size();
			}
			return *this;
		}
		else if (sign == true && x.sign == false) {
			if (-y <= x) {
				place = MinusABS(y, x);
				size_of_place = place.size();
			}
			else {
				place = MinusABS(x, y);
				sign = false;
				size_of_place = place.size();
			}
			return *this;
		}
	}
	BigInteger shift(BigInteger& x, int m) {
		for (int i = 0; i < m; ++i) {
			x.place.push_back(0);
		}
		for (int i = x.place.size() - 1; i >= m; --i) {
			x.place[i] = x.place[i - m];
		}
		for (int i = 0; i < m; ++i) {
			x.place[i] = 0;
		}
		x.size_of_place = x.place.size();
		return(x);
	}
	std::vector<long long> easy_multiplication(const BigInteger& x, const BigInteger& y) {
		//делаю наивное умножение
		long long a = x.place[0] * y.place[0];
		long long b = a / 1000000000;
		long long c = a % 1000000000;
		std::vector<long long> d;
		d.push_back(c);
		if (b > 0) {
			d.push_back(b);
		}
		return(d);
	}
	BigInteger& operator *=(const BigInteger& x) {//это моя каратсуба
		BigInteger x1 = (x >= 0 ? x : -x);
		BigInteger y1 = (*this >= 0 ? *this : -*this);
		bool sign_for_this = true;
		if ((sign == false && x.sign == true) || (sign == true && x.sign == false)) {
			sign_for_this = false;
		}
		else if (sign == false && x.sign == false) {
			sign_for_this = true;
		}
		int size1 = x1.size_of_place;
		int size2 = y1.size_of_place;
		int size3 = size1;
		if (size1 < size2) {
			size3 = size2;
		}
		if (size3 % 2 == 1) {
			++size3;
		}
		for (int i = 0; i < (size3 - size1); ++i) {
			x1.place.push_back(0);
		}
		for (int i = 0; i < (size3 - size2); ++i) {
			y1.place.push_back(0);
		}
		int m = size3 / 2;
		//A * B = A0 * B0(z0) + (( A0 + A1 )z2 * ( B0 + B1 )z3 — A0 * B0z0 — A1 * B1 z1) * BASEm + A1 * B1z1 * BASE2 * m
		BigInteger a0 = x1;
		BigInteger a1 = x1;
		a1.place.clear();
		a0.place.resize(m);
		a0.size_of_place = m;
		for (int i = m; i < size3; ++i) {
			a1.place.push_back(x1.place[i]);
		}
		a1.size_of_place = m;

		BigInteger b0 = y1;
		BigInteger b1 = y1;
		b1.place.clear();
		b0.place.resize(m);
		b0.size_of_place = m;
		for (int i = m; i < size3; ++i) {
			b1.place.push_back(y1.place[i]);
		}
		b1.size_of_place = m;
		BigInteger z0 = a0;
		BigInteger z1 = a1;
		BigInteger z2 = a0;
		BigInteger z3 = b0;
		if (a0.place.size() == 1 && b0.place.size() == 1) {
			z0.place = easy_multiplication(a0, b0);
			z0.size_of_place = z0.place.size();
		}
		else {
			z0 *= b0;
		}
		if (a1.place.size() == 1 && b1.place.size() == 1) {
			z1.place = easy_multiplication(a1, b1);
			z1.size_of_place = z1.place.size();
		}
		else {
			z1 *= b1;
		}
		z2 += a1;
		z3 += b1;
		if (z2.place.size() == 1 && z3.place.size() == 1) {
			z2.place = easy_multiplication(z2, z3);
			z2.size_of_place = z2.place.size();
		}
		else {
			z2 *= z3;
		}
		for (int i = z2.place.size() - 1; i >= 0; --i) {
			if (z2.place[i] == 0 && i != 0) {
				z2.place.pop_back();
			}
			else {
				break;
			}
		}
		for (int i = z1.place.size() - 1; i >= 0; --i) {
			if (z1.place[i] == 0 && i != 0) {
				z1.place.pop_back();
			}
			else {
				break;
			}
		}
		for (int i = z0.place.size() - 1; i >= 0; --i) {
			if (z0.place[i] == 0 && i != 0) {
				z0.place.pop_back();
			}
			else {
				break;
			}
		}
		z2 -= z0;
		z2 -= z1;
		z2 = shift(z2, m);
		z1 = shift(z1, size3);
		*this = z0 + z2;
		*this += z1;
		for (int i = place.size() - 1; i >= 0; --i) {
			if (place[i] == 0 && i != 0) {
				place.pop_back();
			}
			else {
				break;
			}
		}
		sign = sign_for_this;
		return(*this);
	}
	BigInteger& operator ++() {
		return(*this += 1);
	}

	const  BigInteger operator ++(int) {
		BigInteger x = *this;
		*this += 1;
		return(x);
	}

	BigInteger& operator -=(const BigInteger& x) {
		BigInteger& y = *this;
		if (sign == false && x.sign == true) {
			return(PlusABS(x));
		}
		else if (sign == false && x.sign == false) {
			if (y < x) {
				place = MinusABS(y, x);
				size_of_place = place.size();
			}
			else {
				place = MinusABS(x, y);
				sign = true;
				size_of_place = place.size();
			}
			return *this;
		}
		else if (sign == true && x.sign == false) {
			return(PlusABS(x));
		}
		else if (sign == true && x.sign == true) {
			if (y >= x) {
				place = MinusABS(y, x);
				size_of_place = place.size();
			}
			else {
				place = MinusABS(x, y);
				sign = false;
				size_of_place = place.size();
			}
			return *this;
		}
	}

	BigInteger& operator --() {
		return(*this -= 1);
	}

	const  BigInteger operator --(int) {
		BigInteger x = *this;
		*this -= 1;
		return(x);
	}

	BigInteger div_on2(const BigInteger& x, const BigInteger& y) {//деление в столбик на 2 ручками
		BigInteger sum = x + y;
		std::vector<long long> result1;
		long long remains = 0;//остаток
		for (int i = sum.place.size() - 1; i >= 0; --i) {
			result1.push_back((sum.place[i] + remains * max_number) / 2);
			remains = (sum.place[i] + remains * max_number) % 2;
		}
		sum.place.resize(result1.size());
		for (int i = 0; i < result1.size(); ++i) {
			sum.place[i] = result1[result1.size() - 1 - i];
		}
		for (int i = sum.place.size() - 1; i >= 0; --i) {
			if (sum.place[i] == 0 && i != 0) {
				sum.place.pop_back();
			}
			else {
				break;
			}
		}
		sum.size_of_place = sum.place.size();
		return(sum);
	}

	BigInteger& operator /=(const BigInteger& y) {
		bool sign_result = true;
		if ((sign == true && y.sign == false) || (sign == false && y.sign == true)) {
			sign_result = false;
		}
		BigInteger divider = (y >= 0 ? y : -y);
		BigInteger dividend = (*this >= 0 ? *this : -*this);
		BigInteger left = 1;
		BigInteger right = dividend;
		BigInteger result;
		if (dividend == 0 || dividend < divider) {
			place.resize(1);
			place[0] = 0;
			sign = sign_result;
			return(*this);
		}
		while (left <= right)
		{
			BigInteger mid = div_on2(left, right);
			if (dividend == mid * divider) {
				result = mid;
				break;
			}
			if (dividend < divider * mid) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
				result = mid;
			}
		}
		*this = result;
		sign = sign_result;
		return(*this);
	}

	BigInteger& operator %=(const BigInteger& y) {
		*this -= (y * (*this / y));
		return(*this);
	}

	const std::vector<long long>& arrays() const {
		return(place);
	}

	explicit operator bool() {
		return !(*this == 0);
	}
	explicit operator double() {
		double x;
		int POW = 1;
		for (int i = 0; i < place.size(); ++i) {
			x += (place[i] * POW);
			POW *= max_number;
		}
		return(x);
	}
};
// //КОНЕЦ КЛАССА
std::ostream& operator <<(std::ostream& out, BigInteger& x) {//cout
	out << x.toString();
	return(out);
}

std::istream& operator >>(std::istream& in, BigInteger& x) {
	std::string s;
	in >> s;
	x = BigInteger(s);
	return(in);
}
bool MAX_OF_arrays(const std::vector<long long>& a, const std::vector<long long>& b) {//сравнение двух массов, выводим true, если левый меньше 
	if (a.size() < b.size()) {
		return(true);
	}
	else if (a.size() > b.size()) {
		return(false);
	}
	else {
		ptrdiff_t i = a.size() - 1;
		for (i; i >= 0; --i) {
			if (a[i] < b[i]) {
				return(true);
			}
			else if (a[i] > b[i]) {
				return(false);
			}
		}

		return(false);

	}
}
bool operator < (const BigInteger& x, const BigInteger& y) {
	const std::vector<long long> a = x.arrays();
	const std::vector<long long> b = y.arrays();
	if (x.signOut() == true && y.signOut() == true) {
		return (MAX_OF_arrays(a, b));
	}
	else if (x.signOut() == true && y.signOut() == false) {
		return(false);
	}
	else if (x.signOut() == false && y.signOut() == true) {
		return(true);
	}
	else {
		return(MAX_OF_arrays(b, a));
	}
}

bool operator > (const BigInteger& x, const  BigInteger& y) {
	return(y < x);
}

bool operator == (const BigInteger& x, const BigInteger& y) {
	return(!((x < y) || (y < x)));
}

bool operator != (const BigInteger& x, const BigInteger& y) {
	return(!(x == y));
}

bool operator <= (const BigInteger& x, const BigInteger& y) {
	return(!(x > y));
}

bool operator >= (const BigInteger& x, const BigInteger& y) {
	return(!(x < y));
}

const BigInteger operator + (const BigInteger& x, const BigInteger& y) {
	BigInteger z = x;
	return(z += y);
}

const BigInteger operator - (const BigInteger& x, const BigInteger& y) {
	BigInteger z = x;
	return(z -= y);
}

const BigInteger operator * (const BigInteger& x, const BigInteger& y) {
	BigInteger z = x;
	return(z *= y);
}

const BigInteger operator / (const BigInteger& x, const BigInteger& y) {
	BigInteger z = x;
	return(z /= y);
}

const BigInteger operator % (const BigInteger& x, const BigInteger& y) {
	BigInteger z = x;
	return(z %= y);
}

//Закончилась часть, связнная с BigInteger
BigInteger Euclid(BigInteger x, BigInteger y) {
	x = (x ? x >= 0 : -x);
	y = (y ? y >= 0 : -y);
	while (x != y) {
		if (x > y) {
			x -= y;
		}
		else {
			y -= x;
		}
	}
	return(x);
}
void NOD(BigInteger& numerator, BigInteger& denominator) {
	BigInteger NOD_Number = Euclid(numerator, denominator);
	numerator /= NOD_Number;
	denominator /= NOD_Number;
	if (numerator < 0 && denominator < 0) {
		numerator /= -1;
		denominator /= -1;
	}
}
class Rational {
private:
	BigInteger numerator;//числитель
	BigInteger denominator;//знаменатель
	bool sign;
public:
	Rational(int x) {
		denominator = 1;
		numerator = x;
		sign = true ? x >= 0 : false;
	}
	Rational(BigInteger x) {
		denominator = 1;
		numerator = x;
		sign = numerator.signOut;
	}
	Rational() {
		denominator = 1;
		sign = true;
		numerator = 0;
	}
	std::string toString() {
		NOD(numerator, denominator);
		func_sign(*this);
		BigInteger numeratorABS = (numerator ? numerator >= 0 : -numerator);
		BigInteger denominatorABS = (denominator ? denominator >= 0 : -denominator);
		std::string s;
		if (sign == false) {
			s += "-";
		}
		if (numeratorABS % denominatorABS == 0) {
			BigInteger quotient = numeratorABS / denominatorABS;
			s += (quotient.toString);
		}
		else {
			s += (numeratorABS.toString);
			s += "/";
			s += (denominatorABS.toString);
		}
	}
	const BigInteger& numerator_out() const {
		return(numerator);
	}
	const BigInteger& denominator_out() const {
		return(denominator);
	}
	Rational& operator +=(const Rational& y) {
		numerator = (numerator * y.denominator) + (denominator * y.numerator);
		denominator *= y.denominator;
		NOD(numerator, denominator);
		func_sign(*this);
		return(*this);
	}
	Rational& operator -=(const Rational& y) {
		numerator = (numerator * y.denominator) - (denominator * y.numerator);
		denominator *= y.denominator;
		NOD(numerator, denominator);
		func_sign(*this);
		return(*this);
	}
	Rational& operator *=(const Rational& y) {
		numerator *= y.numerator;
		denominator *= y.denominator;
		NOD(numerator, denominator);
		func_sign(*this);
		return(*this);
	}
	Rational& operator /=(const Rational& y) {
		numerator *= y.denominator;
		denominator *= y.numerator;
		NOD(numerator, denominator);
		func_sign(*this);
		return(*this);
	}
	void func_sign(Rational& x) {
		if (x.numerator < 0 && x.denominator < 0) {
			x.sign = true;
		}
		else if (x.numerator >= 0 && x.denominator > 0) {
			x.sign = true;
		}
		else {
			x.sign = false;
		}
	}

	Rational operator -() const {
		Rational x = *this;
		x.sign = (x.sign == true ? false : true);
		return(x);
	}

	explicit operator double() {
		return(double(numerator) / double(denominator));
	}
	std::string asDecimsl(size_t precision = 0) {
		NOD(numerator, denominator);
		func_sign(*this);
		BigInteger numeratorABS = (numerator ? numerator >= 0 : -numerator);
		BigInteger denominatorABS = (denominator ? denominator >= 0 : -denominator);
		std::string s;
		if (sign == false) {
			s += "-";
		}
		BigInteger result = numeratorABS / denominatorABS;
		s += (result.toString);
		if (precision == 0) {
			return(s);
		}
		else {
			s += ",";
			BigInteger remains = numeratorABS % denominatorABS;
			size_t i = 0;
			while (i < precision) {
				remains *= 10;
				result = remains / denominatorABS;
				s += (result.toString);
				remains = remains % denominatorABS;
			}
		}
	}
};


// Конец класса Rational
bool operator < (const Rational& x, const  Rational& y) {
	const BigInteger xn = x.numerator_out();
	const BigInteger yd = y.denominator_out();
	const BigInteger yn = y.numerator_out();
	const BigInteger xd = x.denominator_out();
	if (xn * yd < yn * xd) {
		return(true);
	}
	else {
		return(false);
	}
}

bool operator > (const Rational& x, const  Rational& y) {
	return(y < x);
}

bool operator == (const Rational& x, const Rational& y) {
	return(!((x < y) || (y < x)));
}

bool operator != (const Rational& x, const Rational& y) {
	return(!(x == y));
}

bool operator <= (const Rational& x, const Rational& y) {
	return(!(x > y));
}

bool operator >= (const Rational& x, const Rational& y) {
	return(!(x < y));
}

const Rational operator + (const Rational& x, const Rational& y) {
	Rational z = x;
	return(z += y);
}

const Rational operator - (const Rational& x, const Rational& y) {
	Rational z = x;
	return(z -= y);
}

const Rational operator * (const Rational& x, const Rational& y) {
	Rational z = x;
	return(z *= y);
}

const Rational operator / (const Rational& x, const Rational& y) {
	Rational z = x;
	return(z /= y);
}

