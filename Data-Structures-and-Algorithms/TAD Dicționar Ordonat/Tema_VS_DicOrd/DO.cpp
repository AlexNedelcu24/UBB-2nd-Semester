#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <exception>

#include <exception>
using namespace std;

//Complexitate ?(1)
int hashCode(TCheie e) {
	return abs(e);
}

//Complexitate ?(1)
int DO::d(TCheie e) const {
	return hashCode(e) % m;
}

// Caz favorabil: ?(1)
// Caz defavorabil: ?(m)
// Complexitate generala: O(m)
void DO::actPrimLiber()
{
	primLiber++;
	while (primLiber < m && e[primLiber].first != NULL_TVALOARE)
		primLiber++;
}

// Complexitate generala: O(m)
DO::DO(Relatie r) {
	this->r = r;
	m = MAX;
	for (int i = 0; i <= m; i++)
	{
		e[i].first = NULL_TVALOARE;
		urm[i] = NULL_TVALOARE;
	}

	primLiber = 0;
	nr = 0;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
// Caz favorabil: ?(1)
// Caz defavorabil: ?(m)
// Complexitate generala: O(m)
TValoare DO::adauga(TCheie c, TValoare v) {
	TValoare ret;

	nr++;
	int i = d(c);

	if (e[i].first == NULL_TVALOARE) {
		e[i].first = c;
		e[i].second = v;
		if (i == primLiber) {
			actPrimLiber();
		}
		return NULL_TVALOARE;
	}

	int j = NULL_TVALOARE;
	while (e[i].first != c && i != NULL_TVALOARE)
	{
		j = i;
		i = urm[i];
	}

	if (e[i].first == c) {
		ret = e[i].second;
		e[i].second = v;
		if (i == primLiber) {
			actPrimLiber();
		}
		nr--;
		return ret;
	}

	if (primLiber >= m) {
		nr--;
		throw exception{ "Nu mai este spatiu" };
	}

	e[primLiber].first = c;
	e[primLiber].second = v;
	urm[j] = primLiber;
	actPrimLiber();
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
// Caz favorabil: ?(1)
// Caz defavorabil: ?(m)
// Complexitate generala: O(m)
TValoare DO::cauta(TCheie c) const {
	int i = d(c);
	while (e[i].first != c && i != NULL_TVALOARE) {
		i = urm[i];
	}

	if (i == NULL_TVALOARE) {
		return NULL_TVALOARE;
	}

	return e[i].second;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
// Caz favorabil: ?(1)
// Caz defavorabil: ?(m)
// Complexitate generala: O(m)
TValoare DO::sterge(TCheie c) {
	if (!cauta(c))
		return NULL_TVALOARE;

	int i = d(c);
	int j = NULL_TVALOARE;
	int k = 0;

	while (k < m && j == NULL_TVALOARE) {
		if (urm[k] == i)
			j = k;
		else
			k++;
	}

	while (e[i].first != c && i != NULL_TVALOARE) {
		j = i;
		i = urm[i];
	}

	if (i == NULL_TVALOARE) {
		return NULL_TVALOARE;
	}
	
		nr--;
		TValoare ret = e[i].second;
		bool gata = false;
		while(!gata) {
			int p = urm[i];
			int pp = i;
			while (p != NULL_TVALOARE && d(e[p].first != i)) {
				pp = p;
				p = urm[p];
			}
			if (p == NULL_TVALOARE) {
				gata = true;
			}
			else {
				e[i] = e[p];
				j = pp;
				i = p;
			}
		}

		if (j != NULL_TVALOARE) {
			urm[j] = urm[i];
		}
		e[i].first = NULL_TVALOARE;
		e[i].second = -1;
		urm[i] = NULL_TVALOARE;
		if (primLiber > i) {
			primLiber = i;
		}
		return ret;
	

}

//returneaza numarul de perechi (cheie, valoare) din dictionar
// Complexitate timp: ?(1)
int DO::dim() const {
	return nr;
}

//verifica daca dictionarul e vid
// Complexitate timp: ?(1)
bool DO::vid() const {
	return nr == 0;
}

// Complexitate timp: ?(1)
Iterator DO::iterator() const {
	return  Iterator(*this);
}

// Complexitate timp: ?(1)
DO::~DO() {
}

// Caz favorabil: ?(1)
// Caz defavorabil: ?(m)
// Complexitate generala: O(m)
//
// Subalgoritmul diferentaValoarea(dictionar)
// pre: it (Iterator) - iteratorul pentru dictionarul curent
// post: functia returneaza diferenta dintre valarea maxima si minima
// daca vid(dictionar) == 1 
//    return -1
// it = dictionar.iterator
// daca valid(it) == 1 
//    min = it.element.second
//    max = it.element.second
//    it.urmator
// cat timp valid(it) == 1
//    daca it.element.second < min
//        min = it.element.second
//    daca it.element.second > max
//        max = it.element.second
//    it.urmator
// return max-min
int DO::diferentaValoareMaxMin() const {
	if (this->vid())
		return -1;
	Iterator it = this->iterator();
	TValoare min, max;
	if (it.valid()) {
		min = it.element().second;
		max = it.element().second;
		it.urmator();
	}
	while (it.valid()) {
		if (it.element().second < min)
			min = it.element().second;
		if (it.element().second > max)
			max = it.element().second;
		it.urmator();
	}
	return (max - min);
}
