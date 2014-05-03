#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace std;

class Tocka{
protected:
	float x, y;
public:
	Tocka();
	Tocka(float x, float y): x(x), y(y){};
	
	friend float udaljenost(const Tocka &T1, const Tocka &T2);
	friend float k(const Tocka &T1, const Tocka &T2);
	friend ostream& operator<<(ostream& buffer, const Tocka& z);
};

class Lik{
public:
	void status();
	virtual float povrsina() = 0;
	virtual float opseg() = 0;	virtual float radiusUpKruz() = 0;};

class Trokut : public Lik{ 
protected:
	Tocka A,B,C;
public:
	Trokut();
	Trokut::Trokut(Tocka &A, Tocka &B, Tocka &C): A(A),B(B),C(C){};

	float povrsina(){return sqrt(opseg()/2*(opseg()/2-udaljenost(A,B))*(opseg()/2-udaljenost(B,C))*(opseg()/2-udaljenost(C,A)));};
	float opseg(){return udaljenost(A,B)+udaljenost(B,C)+udaljenost(C,A);};	float radiusUpKruz(){
		
		float k1=k(A,B), k2=k(A,C), fi;
		if(k2 == -k1) fi = 90;
		else fi =  atan((k2-k1)/(1+k1*k2))*180/PI;
		return fi;
	};

	bool isTrokut();
};

class Krug : public Lik{
private:
	Tocka S;
	float radius;
public:
	Krug();
	Krug(Tocka &S,float r);
};

class PravilniPoligon : public Lik{ 
private:
	int N;
	Tocka *vrhovi;
public:
	PravilniPoligon();
	PravilniPoligon(Tocka *vrhovi, int N);
};


void Lik::status(){
	cout << "Opseg: " << opseg() << endl;
	cout << "Povrsina: " << povrsina() << endl;
	cout << "Kut: " << radiusUpKruz() << endl;
};

//end of classes

float udaljenost(const Tocka &T1, const Tocka &T2){
	return sqrt((T2.x-T1.x)*(T2.x-T1.x) + (T2.y-T1.y)*(T2.y-T1.y));
}

ostream& operator<<(ostream& buffer, const Tocka& z){
	return buffer << "T(" << z.x << ", " << z.y << ") ";
};

float povrsinaTrokuta(const Tocka &T1, const Tocka &T2, const Tocka &T3){
	float s = (udaljenost(T1,T2)+udaljenost(T2,T3)+udaljenost(T3,T1))/2;
	return sqrt(s*(s-udaljenost(T1,T2))*(s-udaljenost(T2,T3))*(s-udaljenost(T3,T1)));
}

float k(const Tocka &T1, const Tocka &T2){
	if(T1.x == T2.x) return 0;
	return (T2.y-T1.y)/(T2.x-T1.x);
}

bool Trokut::isTrokut(){
	if(povrsinaTrokuta(A,B,C)==0) return false;
	return true;
}
//\trokut

int main(){
	Tocka T1(3,0), T2(0,3), T3(8,0);
	Trokut T(T1,T2,T3);
	if(T.isTrokut()){
		T.status();
	}
	else cout << "nije trokut" << endl;
	return 0;
}