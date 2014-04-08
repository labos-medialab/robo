#include <iostream>
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
	~matrix();
	
	// operatori pridruzivanja
	matrix& operator=(const matrix& A);
	matrix& operator+=(const matrix& A); 
	matrix& operator-=(const matrix& A); 
	matrix& operator*=(const matrix& A);
	
	// aritmeticki operatori
	matrix operator+(const matrix& A) const;
	matrix operator-(const matrix& A) const;
	matrix operator*(const matrix& A) const;
	
	// relacijski operatori
	bool operator==(const matrix& A) const;
	bool operator!=(const matrix& A) const;
	
	// operator pristupa
	float* operator[](const size_t i) {return M[i];};
	
	friend ostream& operator<<(ostream& buffer, const matrix& z);
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

matrix::~matrix(){
	for(size_t i=0; i<m; i++)
		delete [] M[i];
	delete [] M;
}

matrix& matrix::operator=(const matrix& A){
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
};

matrix& matrix::operator+=(const matrix& A){
	if(this->m != A.m || this->n != A.n){
		cout << "lol NOUP!" << endl;
		return *this;
	}
	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			this->M[i][j]+=A.M[i][j];
		}
	}
	return *this;
};

matrix& matrix::operator-=(const matrix& A){
	if(this->m != A.m || this->n != A.n){
		cout << "lol NOUP!" << endl;
		return *this;
	}
	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			this->M[i][j]-=A.M[i][j];
		}
	}
	return *this;
};

matrix& matrix::operator*=(const matrix& A){
	if(this->n != A.m){
		cout << "lol NOUP!" << endl;
		return *this;
	}

	matrix M(this->m, A.n);
	for(size_t i=0; i<this->m; i++){
		for(size_t j=0; j<A.n; j++){
			for(size_t k=0; k<this->n; k++){
				M.M[i][j]+=this->M[i][k]*A.M[k][j];
			}
		}
	}
	*this=M;
	return *this;
};

matrix matrix::operator+(const matrix& A) const{
	if(this->m != A.m || this->n != A.n){
		cout << "lol NOUP!" << endl;
		return *this;
	}
	matrix M(m, n);
	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			M.M[i][j]=this->M[i][j]+A.M[i][j];
		}
	}
	return M;
};

matrix matrix::operator-(const matrix& A) const{
	if(this->m != A.m || this->n != A.n){
		cout << "lol NOUP!" << endl;
		return *this;
	}
	matrix M(m, n);
	for(size_t i=0; i<m; i++){
		for(size_t j=0; j<n; j++){
			M.M[i][j]=this->M[i][j]-A.M[i][j];
		}
	}
	return M;
}

matrix matrix::operator*(const matrix& A) const{
	if(this->n != A.m){
		cout << "lol NOUP!" << endl;
		return *this;
	}

	matrix M(this->m, A.n);
	for(size_t i=0; i<this->m; i++){
		for(size_t j=0; j<A.n; j++){
			for(size_t k=0; k<this->n; k++){
				M.M[i][j]+=this->M[i][k]*A.M[k][j];
			}
		}
	}
	return M;
};

bool matrix::operator==(const matrix& A) const{
    if(this->m != A.m || this->n != A.n){
		return false;
	}
    for(size_t i=0; i<m; i++){
    	for(size_t j=0; j<n; j++){
			if(this->M[i][j]!=A.M[i][j])
                return false;
		}
	}
    return true;
};

bool matrix::operator!=(const matrix& A) const{
    if(this->m != A.m || this->n != A.n){
    	return true;
	}
    for(size_t i=0; i<m; i++){
        for(size_t j=0; j<n; j++){
			if(this->M[i][j]==A.M[i][j])
                return false;
		}
	}
    return true;
};

ostream& operator<<(ostream& buffer, const matrix& z){
	for(size_t i=0; i<z.m; i++){
		for(size_t j=0; j<z.n; j++){
			buffer <<  z.M[i][j]<< "  ";
		}
		buffer << endl;
	}
	buffer << endl;
	return buffer;
};

int main()
{
	matrix M1(20, 10);
	matrix M2(20, 10);
	matrix M3(10, 20);
	
	cout << "matrica M1" << endl << M1;
	cout << "matrica M2" << endl << M2;
	cout << "matrica M3" << endl << M3;
	cout << "test matrica: " << endl;
	cout << "M1+M2" << endl << M1+M2;
	M1+=M2; cout << "M1+=M2" << endl;
	cout << "matrica M1" << endl << M1;
	M1-=M2; cout << "M1-=M2" << endl;
	cout << "matrica M1" << endl << M1;
	cout << "M1*M3" << endl << M1*M3;
	M1*=M3; cout << (M1*=M3) << endl; 
	cout << "matrica M1" << endl << M1;

	cout << (M1==M2) << endl;

	matrix M4(10,10);
	matrix M5(M4);
	
	cout << "matrica M4" << endl << M4;
	cout << "matrica M5" << endl << M5;

	cout << "M4==M5" << (M4==M5) << endl;
}