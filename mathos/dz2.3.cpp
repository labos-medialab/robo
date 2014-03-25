#include <iostream>
using namespace std;

class Stack{
protected:
	size_t capacity;
	int size;
	int *container;
public:
	Stack();
	Stack(int *brojevi, int n){
		size = n-1;
		capacity=n;
		container = new int [capacity];
		for(int i = 0; i <= size; i++){
			container[i]=brojevi[i];
		}
	};
	Stack(const Stack& S){
		capacity = S.capacity;
		size = S.size;
		container = new int [capacity];
		for(int i = 0; i <= size; i++){
			container[i]=S.container[i];
		}
	};

	Stack kopi(Stack& A, size_t kapacitet, const Stack& B){
		A.capacity=kapacitet;
		A.container=new int[capacity];
		for(int i = 0; i <= B.size; i++){
			A.container[i]=B.container[i];
		}
		return A;
	};

	~Stack(){ delete[] container; };
	
	void push(int broj);
	void pop();
	int& top();
	
	void print_S(){
		for(int i = 0; i <= size; i++){
			cout << container[i] << "\t";
		}
		cout << endl << endl;
	}
	void print_cs(){
		cout << "capacity: " << capacity << endl;
		cout << "size: " << size+1 << endl << endl;
	};
	
	bool is_empty() const;
};

Stack::Stack(){
	size = -1;
	capacity = 4;
	container = new int [capacity];
	print_cs();
}

void Stack::push(int broj){
	if(size == capacity-1){
		Stack temp(*this);
		capacity*=2;
		*this=kopi(*this, capacity, temp);
	}
	size++;
	container[size]=broj;
	cout << "push(" << broj << ");" << endl;
	print_cs();
}

void Stack::pop(){
	if(is_empty()){
		if(size==capacity/2-1){
			Stack temp2(*this);
			capacity/=2;
			*this=kopi(*this, capacity, temp2);
		}						
		container[size]=0;
		size--;
		cout << "pop(); " << endl;
		print_cs();
	}
	else cout << "nop" << endl;
}

int& Stack::top(){
	cout << "top(); ";
	return container[size];
}

bool Stack::is_empty() const{
	if (size >= 0) return 1;
	else return 0;
}

int main(){
	int n = 7, *nekoliko_brojeva = new int [n]; 
	nekoliko_brojeva[0]=6;
	nekoliko_brojeva[1]=5;
	nekoliko_brojeva[2]=4;
	nekoliko_brojeva[3]=3;
	nekoliko_brojeva[4]=2;
	nekoliko_brojeva[5]=1;
	nekoliko_brojeva[6]=0;
	Stack neki(nekoliko_brojeva, n);
	delete [] nekoliko_brojeva;
	neki.print_S();
	neki.pop();neki.pop();neki.pop();
	neki.print_S();
	Stack S1;
	S1.push(21);
	S1.push(11);
	S1.push(7);
	S1.push(10);
	S1.push(51);
	S1.pop();S1.pop();
	S1.pop();S1.pop();
	S1.push(10);
	S1.push(51);
	S1.push(11);
	S1.pop();S1.pop();S1.pop();S1.pop();
	return 0;
}