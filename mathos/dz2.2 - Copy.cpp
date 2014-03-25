#include <iostream>
using namespace std;

class Stack{
protected:
	size_t capacity;
	int size;
	int *container;
public:
	Stack();			//konstruktor koji se poziva kad je objekt bez parametara
	Stack(int *brojevi, int n){	//konstruktor koji se poziva kad je 
					//objekt pozvan nizom sranja i njegovom veliï¿½inom
		size = n-1;			//size mora bit veliï¿½ina n-1 jer push i pop traï¿½e da je uvijet -1
		capacity=n;			//minimaln kapacitet je veliï¿½ina. 
		container = new int [capacity];	//napravi kontejner kapaciteta
		for(int i = 0; i <= size; i++){	//sve izbrojeva prebaci u kontejner
			container[i]=brojevi[i];	//for ili do while petljom. ili nekako veï¿½
		}
	};
	Stack(const Stack& S){				//konstruktor kopije koji uzima objekt klase
		capacity = S.capacity;			//uzmia njegov kapacitet
		size = S.size;				//i veliï¿½inu 
		container = new int [capacity];	//te stvara kontejner kapaciteta
		for(int i = 0; i <= size; i++){	//i kopira
			container[i]=S.container[i];//jedan u drugog
		}
	};
	~Stack(){ delete[] container; };	//destruktor alocirane memorije
	
	void push(int broj);			// dodaj na kraj vektora 
	void pop();				// skini s kraja vektora 
	int& top();				// funkcija koja vraï¿½a referencu zadnjeg elementa u stogu 
	
	void print_S(){				//funkcija printanja stoga
		for(int i = 0; i <= size; i++){	//nije potrebo ali je simpa :)
			cout << container[i] << "\t";
		}
		cout << endl << endl;
	}
	void print_cs(){		//print creep score (lol XD)
		cout << "capacity: " << capacity << endl;	//printa kapacitet i veliï¿½inu
		cout << "size: " << size+1 << endl << endl;	//jer se traï¿½i u zadatku
	};							//moï¿½e se na viï¿½e naï¿½ina
	bool is_empty() const; // provjerava je li stog prazan 
};

Stack::Stack(){		//trivijalni konstruktor, tako se zove :)
	size = -1;	//zaï¿½to minus jedan?! because FUCK YOU! thats why.
	capacity = 4;	//nekako kontam da su vam na vjeï¿½bama objasnili zaï¿½to -1 ako nisu, objasniï¿½u vam naï¿½ivo
	container = new int [capacity];	//alociraj contejner veliï¿½ine int kapaciteta.
	print_cs();		//isprintaj ... netreba to tu.
}

void Stack::push(int broj){	//push metoda koja meï¿½e na vrh
	if(size == capacity-1){	//ako je kontejner pun
		capacity*=2;		//jebiga ovo je sranje
		int *temp;			//neznam kako da objasnim
		temp = new int [capacity];	//na predavanju ï¿½u valjda moï¿½...
		for(int i=0; i <= size; i++){	//temp je jedna od onih koji se mogu mjenjat ime...
			temp[i]=container[i];	//bla bla ... :D
		}
		container = new int[capacity];
		*container=*temp;	
		delete [] temp;
	}
	size++;					//ali ako nije i ako je prvi elemet onda ï¿½e se prebacit u 0
	container[size]=broj;			//i onda na vrh meti broj koji si prosljedio
	cout << "push(" << broj << ");" << endl;//ispis nije potreban ovakav ali mi se sviï¿½a
	print_cs();				//printaj to zato jer moraï¿½.
}

void Stack::pop(){			//pop metoda koja
	if(is_empty()){
		if(size==capacity/2-1){		//ako je kontejner poluprazan
			capacity/=2;		//isto sranje ko i sa puï¿½em
			int *temp;		//na predavanju ï¿½emo pojasnit ï¿½to je viï¿½e moguï¿½e
			temp = new int [capacity];
			for(int i=0; i <= size; i++){
				temp[i]=container[i];
			}
			container = new int[capacity];
			*container=*temp;	
			delete [] temp;
		}						
		container[size]=0;		//legitimno brisanje? neznam, nisam joï¿½ nikad morao brisat element ...
		size--;				//kad obriï¿½eï¿½ smanji za 1
		cout << "pop(); " << endl;	//ispis iz fore za lakï¿½e praï¿½enje zbivanja koda... 
		print_cs();			//printaj to zato jer moraï¿½.
	}
	else cout << "nop" << endl;
}

int& Stack::top(){		//pretty much straight forward
	cout << "top(); ";	//javi da si ti.
	return container[size];	//i returnaj zadnjeg s liste
}

bool Stack::is_empty() const{		//provjerav jeli ima ï¿½togod u stogu
	if (size >= 0) return 1;	//ako ima vrati 1
	else return 0;			//ako nema vrati 0
}

int main(){
	int n = 7, *nekoliko_brojeva = new int [n]; 
	nekoliko_brojeva[0]=6;	//deklariram niz i veliï¿½inu niza
	nekoliko_brojeva[1]=5;	//u prvom redu main() funkicje
	nekoliko_brojeva[2]=4;	//pa za svaki element
	nekoliko_brojeva[3]=3;	//dojelim neku broj
	nekoliko_brojeva[4]=2;	//a mogao sam i for funkcijom
	nekoliko_brojeva[5]=1;	//ali ovako je jasnije ï¿½to se dogaï¿½a
	nekoliko_brojeva[6]=0;	//... iako izgleda glupo
	Stack neki(nekoliko_brojeva, n); //deklaracija nekog objekta, nizom i veliï¿½inom
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
	S1.pop();S1.pop();S1.pop();S1.pop();
	return 0;
}