#include <iostream>
#include <cmath>
using namespace std;

namespace DenseGraph{
	class Graph{
		int Vcnt, Ecnt;
		int *adj;
	public:
		Graph(int V);
		~Graph();
		
		int V() const;
		int E() const;
		
		void insert(int v, int w);
		void remove(int v, int w);
		
		bool edge(int v, int w) const;
		
		void show() const;
	};//clas

	Graph::Graph(int V): Vcnt(V), Ecnt(0){
		adj = new int[Vcnt*Vcnt];
		for(int i=0; i<Vcnt*Vcnt; i++) adj[i]=0;
	};

	Graph::~Graph(){delete[] adj;};

	int Graph::V() const {return Vcnt};
	int Graph::E() const {return Ecnt};

	void Graph::insert(int v, int w){
		if(!edge(v,w)){
			Ecnt++;
			adj[v*Vcnt+w]=1;
			adj[w*Vcnt+v]=1;
		}
	};
	
	void Graph::remove(int v, int w){
		if(edge(v,w)){
			Ecnt--;
			adj[v*Vcnt+w]=0;
			adj[w*Vcnt+v]=0;
		}
	};

	bool Graph::edge(int v,int w)const{ return adj[v*Vcnt+w]; };

	void Graph::show() const{
		cout << "Vcnt=" << Vcnt << ", " << "Ecnt=" << Ecnt << endl;
		for(int i=0;i<Vcnt*Vcnt;i++){
			cout << adj[i] << " ";
			if((i+1)%Vcnt==0) cout << endl;
		}
		cout << endl;
	};
}//namespace
namespace SparseGraph
{
	class Graph{
		int Vcnt, Ecnt;
		class node{
		public:
			int v;
			node* next;
			node* prev;
			node(int x, node* prev, node* next);
		};
		node* adj;
	public:
		Graph(int V);
		int V() const;
		int E() const;
		
		void insert(int v, int w); // ubacivanje novog brida
		void remove(int v, int w); // brisanje brida 
		bool edge(int v, int w) const; // provjera postoji li brid izmedju v i w
		void show() const;
	};
}
    
int main()
{
	DenseGraph::Graph G1(5);
	G1.insert(0,1);
	G1.insert(0,3);
	G1.insert(1,2);
	G1.insert(1,3);
	G1.insert(2,3);
	G1.insert(2,4);
	G1.show();
	G1.remove(1,3);
	G1.show();

/*	SparseGraph::Graph G2(5);
	G2.insert(0,1);
	G2.insert(0,2);
	G2.insert(1,3);
	G2.insert(1,4);
	G2.insert(2,3);
	G2.show();
	G2.remove(1,3);
	G2.show();
/**/
	return 1;
}