#include <iostream>
#include <iomanip>
using namespace std;

float random(float a, float b) {return ((b-a)*((float)rand()/RAND_MAX))+a;}

class matrix
{
protected:
	float **M;
	size_t m, n;

public:
	matrix();
	matrix(size_t m, size_t n);
	matrix(const matrix& A);
	
	// operatori pridruzivanja
	matrix& operator=(const matrix& A);
//	matrix& operator+=(const matrix& A); 
//	matrix& operator-=(const matrix& A); 
//	matrix& operator*=(const matrix& A);
	
	// aritmeticki operatori
	matrix operator+(const matrix& A) const;
	matrix operator-(const matrix& A) const;
	matrix operator*(const matrix& A) const;
	
	// relacijski operatori
	bool operator==(const matrix& A) const;
	bool operator!=(const matrix& A) const;
	
	// operator pristupa
	float* operator[](int i);
	
	friend ostream& operator<<(ostream& buffer, const matrix& z);

	//ispis matricve
	void ispisMatrice();
};

matrix::matrix(size_t m, size_t n){
	this->m = m;
	this->n = n;

	M = new float*[m];
	for(size_t i=0; i<m; i++)
		M[i] = new float[n];

	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			float randomBroj=random(100,-100);
			M[i][j]=randomBroj;
		}
	}
};

matrix::matrix(const matrix& A){
	this->m = A.m;
	this->n = A.n;

	M = new float*[m];
	for(size_t i=0; i<m; i++)
		M[i] = new float[n];

	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			M[i][j]=A.M[i][j];
		}
	}
};

matrix& matrix::operator=(const matrix& A){
	if(this->m != A.m || this->n != A.n){
		cout << "lol wut?!" << endl;
	}

	for(size_t i=0; i<m; i++)
		delete [] M[i];
	delete [] M;

	m=A.m;
	n=A.n;

	M = new float*[m];
	for(size_t i=0; i<m; i++)
		M[i] = new float[n];

	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			M[i][j]=A.M[i][j];
		}
	}

	return *this;
}

matrix matrix::operator+(const matrix& A) const{
	if(this->m != A.m || this->n != A.n){
		cout << "lol NOUP!" << endl;
		return *this;
	}

	else {
		matrix M(m, n);
		for(size_t i=0; i<m; i++){
			for(size_t j=0; j<n; j++){
				M.M[i][j]=this->M[i][j]+A.M[i][j];
			}
		}
		return M;
	}
};

matrix matrix::operator-(const matrix& A) const{
	if(this->m != A.m || this->n != A.n){
		cout << "lol NOUP!" << endl;
		return *this;
	}

	else {
		matrix M(m, n);
		for(size_t i=0; i<m; i++){
			for(size_t j=0; j<n; j++){
				M.M[i][j]=this->M[i][j]-A.M[i][j];
			}
		}
		return M;
	}
}

void matrix::ispisMatrice(){
	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			cout << setprecision(4) <<  M[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}


int main()
{
	matrix M1(5, 5);
	matrix M2(5, 5);
	matrix M3(5, 5);

	M3=M1+M2;

	M1.ispisMatrice();
	M3.ispisMatrice();

/*	cout << "test matrica: " << endl;
	cout << M1 + M3 << endl;
	cout << M1*M2 << endl;
	int i = 3, j = 4;
	cout << "M1[" << i << "][" << j << "] =" << M1[i][j] << endl;/**/
}