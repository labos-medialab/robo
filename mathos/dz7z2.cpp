#include<iostream>
using namespace std;

template<class T, int n>
class Tuple
{
public:
	T *podaci;
	Tuple();
	Tuple(T *input){
		podaci = new T[n];
		for(int i=0; i<n; i++) podaci[i]=input[i];
	};
	~Tuple(){delete [] podaci;};
	
//	bool operator<(const Tuple &T) const;
//	bool operator>(const Tuple &T) const;

	void ispis(){
		cout << "(";
		for(int i=0; i<n-1; i++){
			cout << podaci[i] << ", ";
		}
		cout << podaci[n-1] << ")" << endl;
	};
};

template<class T, int n>
void sort(Tuple<T,n> &Ti){
	bool done=1;
	do{
		T tmp;
		done = 1;
		for(int i=0; i<n-1; i++){
			if(Ti.podaci[i]>Ti.podaci[i+1]){
				done=0;
				tmp = Ti.podaci[i+1];
				Ti.podaci[i+1]=Ti.podaci[i];
				Ti.podaci[i]=tmp;
			}
		}
	}
	while(!done);
};

template<class T, int n>
void ispis(Tuple<T,n> &Ti){
	cout << "(";
	for(int i=0; i<n-1; i++){
		cout << Ti.podaci[i] << ", ";
	}
	cout << Ti.podaci[n-1] << ")" << endl;
};

int main(){
	int *T1;
	const int n1=3;
	T1 = new int [n1];

	T1[0] = 17;
	T1[1] = 21;
	T1[2] = 11;

	Tuple <int, n1> To1(T1);
	
	cout << "T1";ispis(To1);
	sort(To1);
	cout << "T1";ispis(To1);
	cout << endl;

	float *T2;
	const int n2=4;
	T2 = new float[n2];

	T2[0] = (float)11.52;
	T2[1] = (float)8.63;
	T2[2] = (float)1.34;
	T2[3] = (float)6.24;

	Tuple <float, n2> To2(T2);
	
	cout << "T2";ispis(To2);
	sort(To2);
	cout << "T2";ispis(To2);

	return 1;
}