#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);


class Nod;
typedef Nod* PNod;

class Nod

{

public:

	friend class DO;

	Nod(TElem e, PNod st, PNod dr, PNod parinte);

	TElem element();

	PNod stanga();

	PNod dreapta();


private:

	TElem e;

	PNod st, dr, parinte;

};



class DO {
	friend class Iterator;
    private:
		Relatie r;

		PNod rad;

		int nr;

		PNod adauga_rec(PNod p, TElem e);

		PNod cauta_rec(PNod p, TElem e);

		PNod sterge_rec(PNod p, TElem e);

		PNod minim(PNod p) const;

		void distrug_rec(PNod);

		PNod urm(PNod curent) const;

    public:

	// constructorul implicit al dictionarului
	DO(Relatie r);



	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) ;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;


	// destructorul dictionarului
	~DO();

	TValoare ceaMaiFrecventaValoare() const;

};
