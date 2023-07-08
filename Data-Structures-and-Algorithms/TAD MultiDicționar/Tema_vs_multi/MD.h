#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */

	//capacitatea de memorare
	unsigned cp;

	//numarul de elemente
	int elems;

	//vectorul de elemente
	TElem* multi;

	//vectorii de legaturi
	int* urm, * prec;

	//referinta catre primul si ultimul element
	int prim, ultim;

	//referinta catre primul element din spatiul liber
	int primLiber;

	//functii pentru alocarea/dealocarea unui spatiu liber
	//se returneaza pozitia unui spatiu liber in lista
	int aloca();
	//dealoca spatiul de indice i
	void dealoca(int i);
	//initializare spatiu liber
	void initSpatiuLiber();
	//functie privata care creeaza un nod in lista inlantuita
	int creeazaNod(TElem e);
	// functie care redimensioneaza cele 3 tablouri dinamice
	void redim();

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c);

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator();

	// destructorul MultiDictionarului	
	~MD();



};

