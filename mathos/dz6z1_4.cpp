#include <iostream>
#include <cmath>
using namespace std;

float PI = 3.14159265;

class Tocka{
protected:
    float x, y;
public:
	Tocka(): x(0), y(0){};
	Tocka(float x, float y): x(x), y(y){};
	Tocka(const Tocka& T): x(T.x), y(T.y){};

	Tocka& operator=(const Tocka& T){
		this->x=T.x;
		this->y=T.y;
		return *this;
	};

	friend float d(const Tocka &T1, const Tocka &T2);
	friend float phi(const Tocka &T1, const Tocka &T2, const Tocka &T3);
	friend ostream& operator<<(ostream& buffer, const Tocka& z);
};

class Lik{
public:
	void status(){
		cout << "Opseg: " << opseg() << endl;
		cout << "Povrsina: " << povrsina() << endl;
		cout << "Radius: " << radiusUpKruz() << endl;
	};

	virtual float povrsina() = 0;
	virtual float opseg() = 0;
	virtual float radiusUpKruz() = 0;
};

class Trokut : public Lik{ 
protected:
	Tocka A,B,C;
public:
	Trokut();
	Trokut(Tocka &A, Tocka &B, Tocka &C): A(A),B(B),C(C){
		if(isTrokut()){
			cout << "Trokut: " << endl;
			cout << "Vrhovi: "<< A << B << C << endl;
			status();
			cout << endl;
		}
	};

	float povrsina(){ return sqrt(opseg()/2*(opseg()/2-d(A,B))*(opseg()/2-d(B,C))*(opseg()/2-d(C,A))); };
	float opseg(){ return d(A,B)+d(B,C)+d(C,A); };
	float radiusUpKruz(){ return 2*povrsina()/opseg(); };

	bool isTrokut(){
		float s = (d(A,B)+d(B,C)+d(C,A))/2;
		if(sqrt(s*(s-d(A,B))*(s-d(B,C))*(s-d(C,A)))==0) return 0;
		return 1;
	};
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
	
	float povrsina(){ return radius*radius*PI; };
	float opseg(){ return 2*radius*PI; };
	float radiusUpKruz(){ return radius; };
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
			cout << "PravilniPoligon: " << endl;
			for(int i=0; i<N; i++){
				cout << vrhovi[i];
			}
			cout << endl;
			status();
		}
	};
	~PravilniPoligon(){delete [] vrhovi;};

	float  PravilniPoligon::povrsina(){
		float Alfa=2*PI/N;
		float R=d(vrhovi[0],vrhovi[1])/(2*sin(Alfa/2));
		return (N/2)*R*R*sin(Alfa);
	};
	float PravilniPoligon::opseg(){ return N*d(vrhovi[0],vrhovi[1]); };
	float PravilniPoligon::radiusUpKruz(){ return d(vrhovi[0],vrhovi[1])/(2*tan((PI-(((N-2)*PI)/N))/2)); };
	bool PravilniPoligon::ifPravilni(){
		float *a;
		a = new float [N];
		for(int i=0; i<N-1; i++){
			a[i]=d(vrhovi[i],vrhovi[i+1]);
		}
		a[N-1]= d(vrhovi[0],vrhovi[N-1]);
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				if(abs(a[i]-a[j])>0.001) return 0;
			}
		}
		float FI=((N-2)*PI)/N;
		float *fi;
		fi = new float [N];
		for(int i=1; i<N-1; i++){
			fi[i]=phi(vrhovi[i-1], vrhovi[i], vrhovi[i+1]);
		}
		fi[0]=phi(vrhovi[N-1],vrhovi[0],vrhovi[1]);
		fi[N-1]=phi(vrhovi[N-2],vrhovi[N-1],vrhovi[0]);
		for(int i=0; i<N; i++){
			if(abs(fi[i]-FI)>0.001) return 0;
		}
		return 1;
	};
};

//end of classes

float d(const Tocka &T1, const Tocka &T2){
	return sqrt((T2.x-T1.x)*(T2.x-T1.x) + (T2.y-T1.y)*(T2.y-T1.y));
}

float phi(const Tocka &T1, const Tocka &T2, const Tocka &T3){
	float a_x=T2.x-T1.x, a_y=T2.y-T1.y;
	float b_x=T3.x-T2.x, b_y=T3.y-T2.y;
	float ab=a_x*b_x+a_y*b_y;
	float n_a=sqrt(a_x*a_x+a_y*a_y);
	float n_b=sqrt(b_x*b_x+b_y*b_y);
	float fi=acos(ab/(n_a*n_b));
	if(fi<PI/2) fi=PI-fi;
	return fi;
}

ostream& operator<<(ostream& buffer, const Tocka& T){
	return buffer << "T(" << T.x << ", " << T.y << ") ";
};

int main(){
	Tocka T1(0,0), T2(10,0), T3(10,10), T4(0,10);
	Trokut T(T1,T2,T3);
	Krug K(T1, 1);

	int n=3;
	Tocka *vrsi;
	vrsi = new Tocka[n];
	vrsi[0]=T1;vrsi[1]=T2;vrsi[2]=T3;
	PravilniPoligon P1(vrsi,n);
	int N=6;
	
	Tocka * vrhovi;
	vrhovi = new Tocka [N];
	vrhovi[0]=Tocka(0,3);
	vrhovi[1]=Tocka(6,4);
	vrhovi[2]=Tocka(8.134,9.6962);
	vrhovi[3]=Tocka(4.2679,14.3923);
	vrhovi[4]=Tocka(-1.7321,13.3923);
	vrhovi[5]=Tocka(-3.866,7.6962);

	PravilniPoligon P(vrhovi,N);

	return 0;
}