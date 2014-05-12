#include<iostream>
using namespace std;

template<class T>
void sort(T *x, int N){
	bool done=1;
	do{
		done = 1;
		for(int i=0; i<N-1; i++){
			if(x[i]>x[i+1]){
				done=0;
				T tmp = x[i+1];
				x[i+1]=x[i];
				x[i]=tmp;
			}
		}
	}
	while(!done);
};

class Par{
	float x, y;
public:
	Par(): x(0), y(0) {};
	Par(float x, float y): x(x), y(y) {};
	Par(const Par &T): x(T.x), y(T.y) {};

	bool operator<(const Par &P)const{return(x<T.x);};
	bool operator>(const Par &P)const{return(x>T.x);};

	friend ostream& operator<<(ostream& buffer, const Par& T)
	{return buffer << "(" << T.x << "," << T.y << ")";};
};

int main(){
	Par P1(10,0), P2(1,0);

	int *x, N=5;
	x = new int[N];
	x[0]=5;
	x[1]=4;
	x[2]=3;
	x[3]=2;
	x[4]=1;

	sort(x,N);

	cout << x[0];
	for(int i=1; i<N; i++){
		cout << ", " << x[i];
	}
	cout << ";" << endl;

	float *y; N=5;
	y = new float[N];
	y[0]=(float)5.1;
	y[1]=(float)4.2;
	y[2]=(float)3.3;
	y[3]=(float)2.4;
	y[4]=(float)1.5;

	sort(y,N);

	cout << y[0];
	for(int i=1; i<N; i++){
		cout << ", " << y[i];
	}
	cout << ";" << endl;

	Par *z; N=5;
	z = new Par[N];
	z[0]=Par(5,75);
	z[1]=Par(4,75);
	z[2]=Par(3,75);
	z[3]=Par(2,75);
	z[4]=Par(1,75);

	sort(z,N);

	cout << z[0];
	for(int i=1; i<N; i++){
		cout << ", " << z[i];
	}
	cout << ";" << endl;

	return 0;
}