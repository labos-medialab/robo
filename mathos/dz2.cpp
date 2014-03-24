#include <iostream>
using namespace std;

class Stack{
protected:
	size_t capacity;
	int size;
	int *container;
public:
	Stack();					//konstruktor koji se poziva kad je objekt bez parametara
	Stack(int *brojevi, int n){	//konstruktor koji se poziva kad je 
								//objekt pozvan nizom sranja i njegovom velièinom
		size = n-1;			//size mora bit velièina n-1 jer push i pop traže da je uvijet -1
		capacity=n;			//minimaln kapacitet je velièina. 
		container = new int [capacity];	//napravi kontejner kapaciteta
		for(int i = 0; i <= size; i++){	//sve izbrojeva prebaci u kontejner
			container[i]=brojevi[i];	//for ili do while petljom. ili nekako veæ
		}
	};
	Stack(const Stack& S){				//konstruktor kopije koji uzima objekt klase
		capacity = S.capacity;			//uzmia njegov kapacitet
		size = S.size;					//i velièinu 
		container = new int [capacity];	//te stvara kontejner kapaciteta
		for(int i = 0; i <= size; i++){	//i kopira
			container[i]=S.container[i];//jedan u drugog
		}
	};
	~Stack(){ delete[] container; };	//destruktor alocirane memorije
	
	void push(int broj);				// dodaj na kraj vektora 
	void pop();							// skini s kraja vektora 
	int& top();							// funkcija koja vraæa referencu zadnjeg elementa u stogu 
	
	void print_S(){						//funkcija printanja stoga
		for(int i = 0; i <= size; i++){	//nije potrebo ali je simpa :)
			cout << container[i] << "\t";
		}
		cout << endl << endl;
	}
	void print_cs(){		//print creep score (lol XD)
		cout << "capacity: " << capacity << endl;	//printa kapacitet i velièinu
		cout << "size: " << size+1 << endl << endl;	//jer se traži u zadatku
	};												//može se na više naèina
	bool is_empty() const; // provjerava je li stog prazan 
};

Stack::Stack(){		//trivijalni konstruktor, tako se zove :)
	size = -1;		//zašto minus jedan?! because FUCK YOU! thats why.
	capacity = 4;	//nekako kontam da su vam na vježbama objasnili zašto -1 ako nisu, objasniæu vam naživo
	container = new int [capacity];	//alociraj contejner velièine int kapaciteta.
	print_cs();		//isprintaj ... netreba to tu.
}

void Stack::push(int broj){	//push metoda koja meæe na vrh
	if(size == capacity-1){	//ako je kontejner pun
		capacity*=2;		//jebiga ovo je sranje
		int *temp;			//neznam kako da objasnim
		temp = new int [capacity];	//na predavanju æu valjda moæ...
		for(int i=0; i <= size; i++){	//temp je jedna od onih koji se mogu mjenjat ime...
			temp[i]=container[i];	//bla bla ... :D
		}
		container = new int[capacity];
		*container=*temp;	
		delete [] temp;
	}
	size++;					//ali ako nije i ako je prvi elemet onda æe se prebacit u 0
	container[size]=broj;	//i onda na vrh meti broj koji si prosljedio
	cout << "push(" << broj << ");" << endl;	//ispis nije potreban ovakav ali mi se sviða
	print_cs();		//printaj to zato jer moraš.
}

void Stack::pop(){			//pop metoda koja
	if(size==capacity/2-1){	//ako je kontejner poluprazan
		capacity/=2;		//isto sranje ko i sa pušem
		int *temp;			//na predavanju èemo pojasnit što je više moguæe
		temp = new int [capacity];
		for(int i=0; i <= size; i++){
			temp[i]=container[i];
		}
		container = new int[capacity];
		*container=*temp;	
		delete [] temp;
	}						
	container[size]=0;		//legitimno brisanje? neznam, nisam još nikad morao brisat element ...
	size--;					//kad obrišeš smanji za 1
	cout << "pop(); " << endl;	//ispis iz fore za lakše praæenje zbivanja koda... 
	print_cs();		//printaj to zato jer moraš.
}

int& Stack::top(){	//pretty much straight forward
	cout << "top(); ";	//javi da si ti.
	return container[size];	//i returnaj zadnjeg s liste
}

bool Stack::is_empty() const{	//provjerav jeli ima štogod u stogu
	if (size >= 0) return 1;	//ako ima vrati 1
	else return 0;				//ako nema vrati 0
}

int main(){
	int n = 7, *nekoliko_brojeva = new int [n]; 
	nekoliko_brojeva[0]=6;	//deklariram niz i velièinu niza
	nekoliko_brojeva[1]=5;	//u prvom redu main() funkicje
	nekoliko_brojeva[2]=4;	//pa za svaki element
	nekoliko_brojeva[3]=3;	//dojelim neku broj
	nekoliko_brojeva[4]=2;	//a mogao sam i for funkcijom
	nekoliko_brojeva[5]=1;	//ali ovako je jasnije što se dogaða
	nekoliko_brojeva[6]=0;	//... iako izgleda glupo
	Stack neki(nekoliko_brojeva, n); //deklaracija nekog objekta, nizom i velièinom
	delete [] nekoliko_brojeva;	//brisanje niza nekoliko brojeva
	neki.print_S();	//printanje tog obrisanog niza iz objekta...
	neki.pop();neki.pop();neki.pop();	//izbaca nekoliko elemenata iz niza
	neki.print_S();	//i opet ga printa.
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
	return 0;
}