#include <iostream>
#include <cmath>
using namespace std;

class Tocka
{
protected:
	float x,y;
public:
	Tocka(float x, float y): x(x), y(y){};
	
	friend float udaljenost(const Tocka &T1, const Tocka &T2);
	friend float k(const Tocka &T1, const Tocka &T2);
	friend ostream& operator<<(ostream& buffer, const Tocka& T);
};

class Cetverokut
{
protected:
	Tocka T1,T2,T3,T4;
public:
	Cetverokut(Tocka &T1,Tocka &T2,Tocka &T3, Tocka& T4);

	float opseg() const;
	float povrsina() const;
	float ispis() const;

	bool ifis() const;
};

class Paralelogram : public Cetverokut{
public:
	Paralelogram(Tocka &T1,Tocka &T2,Tocka &T3, Tocka& T4);
	
	float opseg() const;
	float povrsina() const;

	bool ifis() const;
};

class Trapez : public Cetverokut{
public:
	Trapez(Tocka &T1,Tocka &T2,Tocka &T3, Tocka& T4);
	
	float opseg() const;
	float povrsina() const;

	bool ifis() const;
};
//end of lulz

//ok go
float udaljenost(const Tocka &T1, const Tocka &T2){
	return sqrt((T2.x-T1.x)*(T2.x-T1.x)+(T2.y-T1.y)*(T2.y-T1.y));
}

float povrsinaTrokuta(const Tocka &T1, const Tocka &T2, const Tocka &T3){
	float s = (udaljenost(T1,T2)+udaljenost(T2,T3)+udaljenost(T3,T1))/2;
	return sqrt(s*(s-udaljenost(T1,T2))*(s-udaljenost(T2,T3))*(s-udaljenost(T3,T1)));
}

float k(const Tocka &T1, const Tocka &T2){
	if(T1.x == T2.x) return 0;
	return (T2.y-T1.y)/(T2.x-T1.x);
}

ostream& operator<<(ostream& buffer, const Tocka& T){
	return buffer << "T(" << T.x << ", " << T.y << ")" <<  endl;
};
//frendli fnc, wut?

//class Cetverokut
Cetverokut::Cetverokut(Tocka &T1,Tocka &T2,Tocka &T3, Tocka& T4): T1(T1), T2(T2), T3(T3), T4(T4){};

float Cetverokut::opseg() const{
	cout << "cetverokut opseg = ";
	if(ifis()){
		return udaljenost(T1,T2)+udaljenost(T2,T3)+udaljenost(T3,T4)+udaljenost(T4,T1);
	}
	return -1;
};

float Cetverokut::povrsina() const{
	if(ifis()){
		cout << "cetverokut povrsina = ";
		return povrsinaTrokuta(T1,T2,T3)+povrsinaTrokuta(T1,T2,T4);
	}
	cout << "cetverokut povrsina = ";
	return -1;
};

float Cetverokut::ispis() const{
	cout << T1 << T2 << T3 << T4;
	return 0;
};

bool Cetverokut::ifis() const{
	if (povrsinaTrokuta(T1,T2,T3)==0) return 0;
	if (povrsinaTrokuta(T2,T3,T4)==0) return 0;
	if (povrsinaTrokuta(T3,T4,T1)==0) return 0;
	if (povrsinaTrokuta(T4,T1,T2)==0) return 0;
	return 1;
};
//end of cetverokut

//class Paralelogram
Paralelogram::Paralelogram(Tocka &T1,Tocka &T2,Tocka &T3, Tocka& T4): Cetverokut(T1,T2,T3,T4) {};

float Paralelogram::opseg() const {
	cout << "paralelogram opseg = ";
	if(ifis()){
		return udaljenost(T1,T2)+udaljenost(T2,T3)+udaljenost(T3,T4)+udaljenost(T4,T1);
	}
	return -1;
}

float Paralelogram::povrsina() const{
	cout << "paralelogram povrsina = ";
	if(ifis()){
		return povrsinaTrokuta(T1,T2,T3) * 2;
	}
	return -1;
};

bool Paralelogram::ifis() const{
	if(udaljenost(T1,T2)==udaljenost(T3,T4) && udaljenost(T1,T4)==udaljenost(T2,T3)) return 1;
	return 0;
};
//end of paralelogram

//class Trapez
Trapez::Trapez(Tocka &T1,Tocka &T2,Tocka &T3, Tocka& T4): Cetverokut(T1,T2,T3,T4) {};

float Trapez::opseg() const {
	cout << "trapez opseg = ";
	if(ifis()){
		return udaljenost(T1,T2)+udaljenost(T2,T3)+udaljenost(T3,T4)+udaljenost(T4,T1);
	}
	return -1;
}

float Trapez::povrsina() const{
	cout << "trapez povrsina = ";
	if(ifis()){
		return povrsinaTrokuta(T1,T2,T3)+povrsinaTrokuta(T1,T2,T4);
	}
	return -1;
};

bool Trapez::ifis() const{
	if(k(T1,T2)==k(T3,T4)) return 1;
	return 0;
}
//end of trapez

int main(){
	return 0;
}