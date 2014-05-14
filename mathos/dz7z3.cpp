#include<iostream>
#include <cstdlib>
using namespace std;


void fill(float *x, unsigned int N){
	for(unsigned int i=0; i<N; i++)
		x[i]=((float)rand()/RAND_MAX*49999);
}

template<class T>
void sort(T *x, int N){
	bool done=1;
	unsigned int k=0;
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
		cout << k << "\r";
		k++;
	}
	while(!done);
	cout << endl;
};

template<class T>
void ispis(T *x, int N){
	cout << x[0];
	for(int i=1; i<N; i++){
		cout << ", " << x[i];
	}
	cout << ";" << endl;
};

class Par{
	float x, y;
public:
	Par(): x(0), y(0) {};
	Par(float x, float y): x(x), y(y) {};
	Par(const Par &T): x(T.x), y(T.y) {};

	bool operator<(const Par &P)const{return(x<P.x);};
	bool operator>(const Par &P)const{return(x>P.x);};

	friend ostream& operator<<(ostream& buffer, const Par& T)
	{return buffer << "(" << T.x << "," << T.y << ")";};
};

int main(){
	float *x;
	unsigned int n=100000;
	x = new float[n];

	cout << "filanje" << endl;
	fill(x,n);
	cout << "sortiranje" << endl;
	sort(x,n);
	cout << "end" << endl;
	//ispis(x,n);

	return 0;
}