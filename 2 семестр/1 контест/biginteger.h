/*В этой задаче разрешается подключать <iostream>, <vector> и <string> и только их.
Напишите класс BigInteger для работы с длинными целыми числами. Должны поддерживаться операции:
сложение, вычитание, умножение, деление, остаток по модулю, работающие так же, как и для int; составное присваивание с этими операциями.
Умножение должно работать за o-малое от n2.
унарный минус, префиксный и постфиксный инкремент и декремент. Префиксный инкремент и декремент должны работать за O(1) в среднем.
операторы сравнения == != < > <= >=
вывод в поток и ввод из потока
метод toString(), возвращающий строковое представление числа
конструирование из int (в том числе неявное преобразование, когда это надо)
неявное преобразование в bool, когда это надо (должно работать в условных выражениях)
опционально - литеральный суффикс bi для написания литералов типа BigInteger, см. справку здесь https://en.cppreference.com/w/cpp/language/user_literal
Используя класс BigInteger, напишите класс Rational для работы с рациональными числами сколь угодно высокой точности. 
Числа Rational должны представляться в виде несократимых обыкновенных дробей, где числитель и знаменатель – сколь угодно длинные целые числа. 
Должны поддерживаться операции:
конструктор из BigInteger, из int
сложение, вычитание, умножение, деление, составное присваивание с этими операциями
унарный минус
операторы сравнения == != < > <= >=
метод toString(), возвращающий строковое представление числа (вида [минус]числитель/знаменатель), где числитель и знаменатель - взаимно простые числа;
если число на самом деле целое, то знаменатель выводить не надо
метод asDecimal(sizet precision=0), возвращающий строковое представление числа в виде десятичной дроби с precision знаками после запятой
оператор приведения к double
В вашем файле должна отсутствовать функция main(), а сам файл должен называться biginteger.h. В качестве компилятора необходимо указывать Make. 
Ваш код будет вставлен посредством команды #include<biginteger.h> в программу, содержащую тесты; 
вследствие этого код необходимо отправлять в файле со строго соответствующим именем!
*/
#include <iostream>
#include <vector>
#include <string>
//#include <assert.h>

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
	long long max_number = 1000000;
	size_t n = 6;// так как ты 10 в 9(было изначалаьно), но я передалал все в 6, так как на умножении было переполнение
	size_t size_of_place = 0;
	bool sign = true;//tru если + или 0
public:
	BigInteger(const BigInteger& x) {
		place = x.place;
		sign = x.sign;
		size_of_place = place.size();
	}
	/* BigInteger(const BigInteger&& x) {
		 place = x.place;
		 sign = x.sign;
		 size_of_place = place.size();
	 }*/
	BigInteger() {
		sign = true;
		place.push_back(0);
	}
	BigInteger(int x) {
		int y = std::abs(x);
		sign = x >= 0;
		if (x == -0) {
			sign = true;
		}
		if (y >= max_number) {
			place.push_back(y % max_number);
			place.push_back(y / max_number);
			size_of_place = 2;
		}
		else {
			place.push_back(y);
			size_of_place = 1;
		}
	}
	BigInteger(std::string& s) {
		int number;
		if (s.size() == 2 && s[0] == '-' && s[1] == '0') {
			sign = true;
			place.assign(1, 0);
			return;
		}
		if (s[0] == '-') {
			sign = false;
			s.erase(0, 1);
		}
		else {
			sign = true;
		}
		if (s.size() % 6 == 0) {
			number = s.size() / 6;
		}
		else {
			number = s.size() / 6 + 1;
		}
		size_t size1 = s.size() % 6;
		size_t size = 0;
		std::vector<long long> now(number);
		long long sum = 0;
		int k = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			++k;
			sum *= 10;
			sum += (s[i] - '0');
			if (size1 == i + 1 && size1 != 0) {
				now[number - 1] = sum;
				sum = 0;
				++size;
				k = 0;
			}
			if (k % 6 == 0 && i >= 5) {
				now[number - 1 - size] = sum;
				sum = 0;
				++size;
			}
		}
		place = now;
	}

	bool signOut() const {
		return(sign);
	}

	std::string toString() const {
		std::string s;
		if (!sign) {
			s += "-";
		}
		for (long long i = static_cast<long long>(place.size() - 1); i >= 0; --i) {
			std::string little_string = std::to_string(place[i]);
			if (i == static_cast<long long>(place.size() - 1)) {
				s += little_string;
			}
			else {
				for (int j = static_cast<int>(n - little_string.size()); j > 0; --j) {
					s += "0";
				}
				s += little_string;
			}
		}
		return(s);
	}

	BigInteger operator -() const {
		BigInteger x = *this;
		if (*this == 0) {
			return(*this);
		}
		x.sign = !x.sign;
		return(x);
	}

	BigInteger& PlusABS(const BigInteger& x) {
		long long perenos = 0;
		size_t i = 0;
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

	std::vector<long long> MinusABS(const BigInteger& x, const BigInteger& y) {//òóò ìû áóäåì ðàçíèöó ïî ìîäóëþ èñêàòü
		std::vector<long long> now;
		int dop = 0;
		size_t i = 0;
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
		for (; i < x.place.size(); ++i) {
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
		//убираем первые нули
		for (int j = static_cast<int>(now.size() - 1); j >= 0; --j) {
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
		if ((x.sign && sign) || (!x.sign && !sign)) {
			return(PlusABS(x));
		}
		else if (!sign && x.sign) {
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
		else if (sign && !x.sign) {
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
		return *this;
	}

	std::vector<long long> summa_for2(std::vector<long long>& a, std::vector<long long>& b) {
		std::vector<long long> res(a.size(), 0);
		for (size_t i = 0; i < a.size(); ++i) {
			res[i] += (a[i] + b[i]);
		}
		return(res);
	}

	void Difference_for_3(std::vector<long long>& a, std::vector<long long>& b, std::vector<long long>& c, size_t& size1) {

		for (size_t i = 0; i < size1; ++i) {
			a[i] -= (b[i] + c[i]);
		}
	}

	void summ_for_result(std::vector<long long>& a, std::vector<long long>& b) {
		for (size_t i = 0; i < b.size(); ++i) {
			a[i] += b[i];
		}
	}

	void shift(std::vector<long long>& result, std::vector<long long>& z, size_t index) {
		for (size_t i = index; i < result.size() / 2 + index; ++i) {//смещение на m
			result[i] += z[i - index];
		}
	}

	std::vector<long long> Karatsuba(std::vector<long long>& First, std::vector<long long>& Second) {
		size_t size1 = First.size();
		//сначала смотрим можно ли применить наиавное умножение
		if (size1 <= 2) {
			return(easy_multiplication(First, Second));
		}
		else {
			// иначе начинаем делать алгоритм карацубы
			size_t m = First.size() / 2;//мы один раз сделали нормальный размер кратный 2, а затем он будет постоянно кратен 2 или равен 1
			std::vector<long long> a1(First.begin() + m, First.end());
			std::vector<long long>& a0 = First;
			a0.resize(m);
			std::vector<long long> b1(Second.begin() + m, Second.end());
			std::vector<long long>& b0 = Second;
			b0.resize(m);
			//A * B = A0 * B0 + (( A0 + A1 ) * ( B0 + B1 ) — A0 * B0 — A1 * B1 ) * BASEm + A1 * B1 * BASE2 * m
			std::vector<long long>z0 = summa_for2(a0, a1);
			std::vector<long long>z1 = summa_for2(b0, b1);
			std::vector<long long> z2 = Karatsuba(a0, b0);
			std::vector<long long> z3 = Karatsuba(a1, b1);
			std::vector<long long> z4 = Karatsuba(z0, z1);//у него длина будет size1=2*m
			Difference_for_3(z4, z2, z3, size1);
			std::vector<long long> result(2 * size1);//такого размера, так как размер z3 2m=size1,и z3 делает смещение на 2m
			shift(result, z4, m);//смещение на m
			shift(result, z3, m * 2);//смещение на 2m
			summ_for_result(result, z2);
			return(result);
		}
	}

	std::vector<long long> easy_multiplication(std::vector<long long>& x, std::vector<long long>& y) {//static
		std::vector<long long> result((x.size() + y.size()), 0);
		for (size_t i = 0; i < x.size(); ++i) {
			for (size_t j = 0; j < y.size(); ++j) {
				result[i + j] += (x[i] * y[j]);
			}
		}
		return(result);
	}

	void return_to_normal_appearance(std::vector<long long>& result) {
		long long perenos = 0;
		long long now = 0;
		for (size_t i = 0; i < result.size() - 1; ++i) {
			if (result[i] < 0) {
				long long k = 0;//сколько разрядов надо забрать
				while (-result[i] > k* max_number) {
					++k;
				}
				result[i] += max_number * k;
				result[i + 1] -= k;
			}
			else {
				now = (result[i]) % max_number;
				perenos = result[i] / max_number;
				result[i + 1] += perenos;
				result[i] = now;
			}
		}
		size_t i = result.size() - 1;
		while (result[i] >= max_number) {
			result.push_back(result[i] / max_number);
			result[i] %= max_number;
			++i;
		}
		//убираем первые 0 если они есть
		for (int j = static_cast<int>(result.size() - 1); j >= 0; --j) {
			if (result[j] == 0 && j != 0) {
				result.pop_back();
			}
			else {
				break;
			}
		}
	}

	BigInteger& operator *=(const BigInteger& x) {//ýòî ìîÿ êàðàòñóáà
		bool sign_for_this = true;
		if ((!sign && x.sign) || (sign && !x.sign)) {
			sign_for_this = false;
		}
		else if (!sign && !x.sign) {
			sign_for_this = true;
		}
		if (x == 0 || *this == 0) {
			sign = true;
			place.resize(1);
			place[0] = 0;
		}
		std::vector<long long> First = place;
		std::vector<long long> Second = x.place;
		size_t size1 = First.size();
		size_t size2 = Second.size();
		if (size1 <= 1 && size2 <= 1) {
			std::vector<long long> res = (easy_multiplication(First, Second));
			return_to_normal_appearance(res);
			place = res;
			sign = sign_for_this;
			return(*this);
		}
		if (size1 < size2) {
			size1 = size2;
		}
		//ищем ближающую степень 2 к size1
		size_t stepen = 2;
		while (stepen < size1) {
			stepen *= 2;
		}
		size1 = stepen;
		First.resize(size1, 0);
		Second.resize(size1, 0);
		std::vector<long long> result = Karatsuba(First, Second);
		return_to_normal_appearance(result);
		place = result;
		sign = sign_for_this;
		return(*this);
	}

	void return_to_normal_view_for_prefix_incrementand_decrement() {//работает, если мы знаем, что число в результате положиельное
		long long perenos = 0;
		long long now = 0;
		for (size_t i = 0; i < place.size() - 1; ++i) {
			if (place[i] < 0) {
				long long k = 0;//сколько разрядов надо забрать
				while (-place[i] > k* max_number) {
					++k;
				}
				place[i] += max_number * k;
				place[i + 1] -= k;
			}
			else {
				now = (place[i]) % max_number;
				perenos = place[i] / max_number;
				place[i + 1] += perenos;
				place[i] = now;
			}
		}
		size_t i = place.size() - 1;
		while (place[i] >= max_number) {
			place.push_back(place[i] / max_number);
			place[i] %= max_number;
			++i;
		}
		//убираем первые 0 если они есть
		for (int j = static_cast<int>(place.size() - 1); j >= 0; --j) {
			if (place[j] == 0 && j != 0) {
				place.pop_back();
			}
			else {
				break;
			}
		}
	}

	BigInteger& operator ++() {
		if (sign) {
			++place[0];
			if (place[0] >= max_number) {
				return_to_normal_view_for_prefix_incrementand_decrement();
				size_of_place = place.size();
			}
		}
		if (!sign) {
			--place[0];
			if (place[0] < 0) {
				return_to_normal_view_for_prefix_incrementand_decrement();
				size_of_place = place.size();
			}
			if (place[0] == 0 && place.size() == 1) {
				sign = true;
			}
		}
		return(*this);
	}

	const BigInteger operator ++(int) {
		BigInteger x = *this;
		*this += 1;
		return(x);
	}

	BigInteger& operator -=(const BigInteger& x) {
		BigInteger& y = *this;
		if (!sign && x.sign) {
			return(PlusABS(x));
		}
		else if (!sign && !x.sign) {
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
		else if (sign && !x.sign) {
			return(PlusABS(x));
		}
		else if (sign && x.sign) {
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
		return *this;
	}

	BigInteger& operator --() {
		if (!sign) {
			++place[0];
			if (place[0] >= max_number) {
				return_to_normal_view_for_prefix_incrementand_decrement();
				size_of_place = place.size();
			}
		}
		if (sign) {
			--place[0];
			if (place[0] == -1 && place.size() == 1) {
				sign = false;
				place[0] = 1;
			}
			else if (place[0] < 0) {
				return_to_normal_view_for_prefix_incrementand_decrement();
				size_of_place = place.size();
			}
		}
		return(*this);
	}

	const BigInteger operator --(int) {
		BigInteger x = *this;
		*this -= 1;
		return(x);
	}

	BigInteger div_on2(const BigInteger& x, const BigInteger& y) {//äåëåíèå â ñòîëáèê íà 2 ðó÷êàìè
		if (x.place.size() == 1 && y.place.size() == 1) {
			long long sum = x.place[0] + y.place[0];
			return(sum / 2);
		}
		BigInteger sum = x + y;
		std::vector<long long> result1;
		long long remains = 0;//îñòàòîê
		for (long long i = static_cast<long long>(sum.place.size() - 1); i >= 0; --i) {
			result1.push_back((sum.place[i] + remains * max_number) / 2);
			remains = (sum.place[i] + remains * max_number) % 2;
		}
		sum.place.resize(result1.size());
		// переоврачиваю вектор
		for (size_t i = 0; i < result1.size(); ++i) {
			sum.place[i] = result1[result1.size() - 1 - i];
		}
		// избавляюсь от вед нулей, вдруг они есть
		for (long long i = static_cast<long long>(sum.place.size() - 1); i >= 0; --i) {
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
	long long bin_search_number(BigInteger now, BigInteger divider) {
		BigInteger l = -1;
		BigInteger r = now + 1;
		++r;
		while (l < r - 1) {
			BigInteger m = div_on2(r, l);
			if (m * divider > now) {
				r = m;
			}
			else {
				l = m;
			}
		}
		if (r * divider <= now) {
			return(r.place[0]);
		}
		else {
			return(l.place[0]);
		}
	}
	BigInteger& operator /=(const BigInteger& y) {
		bool sign_result = true;
		if ((sign && !y.sign) || (!sign && y.sign)) {
			sign_result = false;
		}
		BigInteger divider = (y >= 0 ? y : -y);
		BigInteger dividend = (*this >= 0 ? *this : -*this);
		if (dividend == 0 || dividend < divider) {
			place.resize(1);
			place[0] = 0;
			size_of_place = 1;
			sign = true;
			return(*this);
		}
		if (dividend == divider) {
			place.resize(1);
			place[0] = 1;
			sign = sign_result;
			size_of_place = 1;
			return(*this);
		}
		if (divider == 1) {
			place = dividend.place;
			size_of_place = place.size();
			sign = sign_result;
			return(*this);
		}

		//деление в столбик
		std::vector<long long> place_itog;
		BigInteger perenos = 0;
		BigInteger now;
		BigInteger itog = 0;
		for (long long i = static_cast<long long>(dividend.place.size() - 1); i >= 0; --i) {
			now = dividend.place[i] + perenos * max_number;
			if (now >= divider) {
				long long number_now = bin_search_number(now, divider);
				place_itog.push_back(number_now);
				perenos = now - divider * number_now;
			}
			else {
				place_itog.push_back(0);
				perenos = now;
			}
		}
		long long nomer_thefirstNo0 = -1;
		for (size_t i = 0; i < place_itog.size(); ++i) {
			if (place_itog[i] != 0 && nomer_thefirstNo0 == -1) {
				nomer_thefirstNo0 = i;
				place.resize(place_itog.size() - i);
			}
			if (nomer_thefirstNo0 != -1) {
				place[place.size() - 1 - i + nomer_thefirstNo0] = place_itog[i];
			}
		}
		sign = sign_result;
		return (*this);
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
};
// конец класса BigInt
std::ostream& operator <<(std::ostream& out, const BigInteger& x) {//cout
	out << x.toString();
	return(out);
}

std::istream& operator >>(std::istream& in, BigInteger& x) {
	std::string s;
	in >> s;
	x = BigInteger(s);
	return(in);
}
bool MAX_OF_arrays(const std::vector<long long>& a, const std::vector<long long>& b) {//ñðàâíåíèå äâóõ ìàññîâ, âûâîäèì true, åñëè ëåâûé ìåíüøå
	if (a.size() < b.size()) {
		return(true);
	}
	else if (a.size() > b.size()) {
		return(false);
	}
	else {
		for (auto i = static_cast<long long>(a.size() - 1); i >= 0; --i) {
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
	if (x.signOut() && y.signOut()) {
		return (MAX_OF_arrays(a, b));
	}
	else if (x.signOut() && !y.signOut()) {
		return(false);
	}
	else if (!x.signOut() && y.signOut()) {
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

//Начало части Rational
BigInteger Euclid(BigInteger x, BigInteger y) {
	x = (x >= 0 ? x : -x);
	y = (y >= 0 ? y : -y);
	while (x != 0 && y != 0) {
		if (x > y) {
			x %= y;
		}
		else {
			y %= x;
		}
	}
	return(x + y);
}
void NOD(BigInteger& numerator, BigInteger& denominator) {
	if (numerator != 0) {
		BigInteger NOD_Number = Euclid(numerator, denominator);
		if (NOD_Number != 1) {
			numerator /= NOD_Number;
			denominator /= NOD_Number;
		}
	}
	if (numerator < 0 && denominator < 0) {
		numerator /= -1;
		denominator /= -1;
	}
}
class Rational {
private:
	BigInteger numerator;//числитель
	BigInteger denominator;//знаменатель
	bool sign = true;
public:
	Rational(const Rational& x) {
		denominator = x.denominator;
		numerator = x.numerator;
		sign = x.sign;
	}
	Rational(const int& x, const int& y = 1) {
		denominator = y;
		numerator = x;
		if ((x > 0 && y < 0) || (x < 0 && y>0)) {
			sign = false;
		}
		if (x == 0) {
			sign = true;
		}
	}
	Rational(const BigInteger& x, const  BigInteger& y = 1) {
		denominator = y;
		numerator = x;
		if ((x.signOut() && !y.signOut()) || (!x.signOut() && y.signOut())) {
			sign = false;
		}
	}
	Rational() {
		denominator = 1;
		sign = true;
		numerator = 0;
	}
	std::string toString() const {

		//убрал приведение к общему
		BigInteger numeratorABS = (numerator >= 0 ? numerator : -numerator);
		BigInteger denominatorABS = (denominator >= 0 ? denominator : -denominator);
		std::string s;
		if (!sign) {
			s += "-";
		}
		if (numerator == 0) {
			s += "0";
			return(s);
		}
		if (numeratorABS % denominatorABS == 0 && numeratorABS >= denominatorABS) {
			BigInteger quotient = numeratorABS / denominatorABS;
			s += (quotient.toString());
		}
		else {
			s += (numeratorABS.toString());
			s += "/";
			s += (denominatorABS.toString());
		}
		return(s);
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
		func_sign();
		return(*this);
	}
	Rational& operator -=(const Rational& y) {
		numerator = (numerator * y.denominator) - (denominator * y.numerator);
		denominator *= y.denominator;
		NOD(numerator, denominator);
		func_sign();
		return(*this);
	}
	Rational& operator *=(const Rational& y) {
		numerator *= y.numerator;
		denominator *= y.denominator;
		NOD(numerator, denominator);
		func_sign();
		return(*this);
	}
	Rational& operator /=(const Rational& y) {
		numerator *= y.denominator;
		denominator *= y.numerator;
		NOD(numerator, denominator);
		func_sign();
		return(*this);
	}
	void func_sign() {
		if (numerator < 0 && denominator < 0) {
			sign = true;
		}
		else sign = numerator >= 0 && denominator > 0;
	}

	Rational operator -() const {
		Rational x = *this;
		x.numerator = -(numerator);
		return(x);
	}

	explicit operator double() {
		return(std::stod(asDecimal(17)));
	}
	std::string asDecimal(size_t precision = 0) const {
		BigInteger numeratorABS = (numerator >= 0 ? numerator : -numerator);
		BigInteger denominatorABS = (denominator >= 0 ? denominator : -denominator);
		std::string s;
		if (!sign) {
			s += "-";
		}
		BigInteger result = numeratorABS / denominatorABS;
		s += (result.toString());
		if (precision == 0) {
			return(s);
		}
		else {
			s += ".";
			BigInteger remains = numeratorABS % denominatorABS;
			size_t i = 0;
			while (i < precision) {
				remains *= 10;
				result = remains / denominatorABS;
				s += (result.toString());
				remains = remains % denominatorABS;
				++i;
			}
		}
		return(s);
	}
};


// Êîíåö êëàññà Rational
bool operator < (const Rational& x, const  Rational& y) {
	const BigInteger xn = x.numerator_out();
	const BigInteger yd = y.denominator_out();
	const BigInteger yn = y.numerator_out();
	const BigInteger xd = x.denominator_out();
	int k = 0;//сколько у нас отрц знаменателей
	if (xd < 0)
		++k;
	if (yd < 0)
		++k;
	if (k % 2 == 0) {
		return xn * yd < yn * xd;
	}
	else {
		return xn * yd > yn* xd;
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
