﻿#include <iostream>
#include <cmath>
using namespace std;

float PI = 3.14159265;

class Tocka{
protected:
	float x, y;
public:
	Tocka(): x(0), y(0){};
	Tocka(float x, float y): x(x), y(y){};
	Tocka(const Tocka& T){
		this->x=T.x;
		this->y=T.y;
	};

	Tocka& operator=(const Tocka& T){
		this->x=T.x;
		this->y=T.y;
		return *this;
	};

	friend float d(const Tocka &T1, const Tocka &T2);
	friend float k(const Tocka &T1, const Tocka &T2);
	friend float s(const Tocka &T1, const Tocka &T2, const Tocka &T3);
	friend float r(const Tocka &B, const Tocka &A, const Tocka &C);
	friend ostream& operator<<(ostream& buffer, const Tocka& z);
	friend class Trokut;

	Tocka * makeMeMnogokut(const Tocka &S, const float &N, const float &R);
};

class Lik{
public:
	void status();
	virtual float povrsina() = 0;
	virtual float opseg() = 0;
	virtual float radiusUpKruz() = 0;
};

class Trokut : public Lik{ 
protected:
	Tocka A,B,C;
public:
	Trokut();
	Trokut::Trokut(Tocka &A, Tocka &B, Tocka &C): A(A),B(B),C(C){
		if(isTrokut()){
			cout << "Trokut: " << endl;
			cout << "Vrhovi: "<< A << B << C << endl;
			status();
			cout << endl;
		}
	};

	float povrsina(){return sqrt(opseg()/2*(opseg()/2-d(A,B))*(opseg()/2-d(B,C))*(opseg()/2-d(C,A)));};
	float opseg(){return d(A,B)+d(B,C)+d(C,A);};
	float radiusUpKruz(){
		float r1=r(A,B,C);
		float r2=r(C,A,B);
		float r3=r(B,C,A);

		if(abs(r1-r2)<0.00001) return r1;
		if(abs(r2-r3)<0.00001) return r2;
		if(abs(r3-r1)<0.00001) return r3;
		return 0;
	};

	bool isTrokut();
};

class Krug : public Lik{
private:
	Tocka S;
	float radius;
public:
	Krug();
	Krug(Tocka &S,float r): S(S), radius(r){
		cout << "Krug: " << endl;
		cout << "Srediste: " << S << endl;
		status();
		cout << endl;
	};

	float povrsina(){return radius*radius*PI;};
	float opseg(){return 2*radius*PI;};
	float radiusUpKruz(){return radius;};
};

class PravilniPoligon : public Lik{ 
private:
	int N;
	Tocka *vrhovi;
public:
	PravilniPoligon();
	PravilniPoligon(Tocka *vrhovi, int N): N(N){
		this->vrhovi = new Tocka [N];
		for(int i=0; i<N; i++){
			this->vrhovi[i]=vrhovi[i];
		}
		if(ifPravilni()){
			for(int i=0; i<N; i++){
				cout << vrhovi[i];
			}
			cout << endl;
			status();
		}
	};

	float povrsina(){
		float Alfa=PI-(((N-2)*PI)/N);
		float R=d(vrhovi[0],vrhovi[1])/(2*sin(Alfa/2));
		return (N/2)*R*R*sin(Alfa);
	};
	float opseg(){return N*d(vrhovi[0],vrhovi[1]);};
	float radiusUpKruz(){return d(vrhovi[0],vrhovi[1])/(2*tan((PI-(((N-2)*PI)/N))/2));};

	bool ifPravilni(){
		float *a;
		a = new float [N];
		for(int i=0; i<N-1; i++){
			a[i]=d(vrhovi[i],vrhovi[i+1]);
		}
		a[N-1]= d(vrhovi[0],vrhovi[N-1]);

		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				if(a[i]!=a[j]) return 0;
			}
		}

		float FI=((N-2)*PI)/N;
		//cout << FI << endl;
		return 1;
	};
};

void Lik::status(){
	cout << "Opseg: " << opseg() << endl;
	cout << "Povrsina: " << povrsina() << endl;
	cout << "Radius: " << radiusUpKruz() << endl;
};

//end of classes

float d(const Tocka &T1, const Tocka &T2){
	return sqrt((T2.x-T1.x)*(T2.x-T1.x) + (T2.y-T1.y)*(T2.y-T1.y));
}

ostream& operator<<(ostream& buffer, const Tocka& T){
	return buffer << "T(" << T.x << ", " << T.y << ") ";
};

float povrsinaTrokuta(const Tocka &T1, const Tocka &T2, const Tocka &T3){
	float s = (d(T1,T2)+d(T2,T3)+d(T3,T1))/2;
	return sqrt(s*(s-d(T1,T2))*(s-d(T2,T3))*(s-d(T3,T1)));
}

float r(const Tocka &B, const Tocka &A, const Tocka &C){
	float a,b,c;
	a = d(B,C);
	b = d(A,C);
	c = d(A,B);

	float s = (a+b+c)/2;

	float k1=k(A,B), k2=k(A,C), fi;
	if(k2 == -k1) fi = PI/2;
	else {
		fi = abs(atan((k2-k1)/(1+k1*k2)));
	}

	if((k1<0 && k2>0) || (k2<0 && k1>0)){
		if(fi > 1.57079633 && (a<b || a<c))fi=PI-fi;
	}
	
//	cout << fi*180/PI << endl;
//	cout << (s-a)*tan(fi/2) << endl;
	return (s-a)*tan(fi/2);
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
	Tocka T1(0,0), T2(10,0), T3(10,10), T4(0,10);
	Trokut T(T1,T2,T3);
	Krug K(T1, 1);

	int n=4;
	Tocka *vrsi;
	vrsi = new Tocka[n];
	vrsi[0]=T1;vrsi[1]=T2;vrsi[2]=T3;vrsi[3]=T4;
	PravilniPoligon P(vrsi,n);
	return 0;
}