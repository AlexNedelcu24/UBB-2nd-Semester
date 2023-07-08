#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//Complexitate timp: ?(1)
Nod::Nod(TElem e, PNod st, PNod dr, PNod parinte) {
	this->e = e;
	this->st = st;
	this->dr = dr;
	this->parinte = parinte;
}

//Complexitate timp: ?(1)
TElem Nod::element() {
	return e;
}

//Complexitate timp: ?(1)
PNod Nod::stanga() {
	return st;
}

//Complexitate timp: ?(1)
PNod Nod::dreapta() {
	return dr;
}


//Complexitate timp: ?(1)
DO::DO(Relatie r) {
	rad = nullptr;
	this->r = r;
	this->nr = 0;
}

//Complexitate timp: O(h)
PNod DO::adauga_rec(PNod p, TElem e) {
	if (p == nullptr) {
		p = new Nod(e, nullptr, nullptr, nullptr);
	}
	else if (e.first == p->e.first) {
		p->e.second = e.second;
	}
	else {
		if (r(e.first, p->e.first)) {
			p->st = adauga_rec(p->st, e);
			p->st->parinte = p;
		}
		else {
			p->dr = adauga_rec(p->dr, e);
			p->dr->parinte = p;
		}
	}
	return p;
}

//Complexitate timp: O(h)
//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	TValoare ret = cauta(c);
	if (ret == NULL_TVALOARE) {
		nr++;
		rad = adauga_rec(rad, { c,v });
		return NULL_TVALOARE;
	}
	else {
		rad = adauga_rec(rad, { c,v });
		return ret;
	}
}

//Complexitate timp: O(h)
PNod DO::cauta_rec(PNod p, TElem e) {
	if (p == nullptr || p->e.first == e.first) {
		return p;
	}
	else {
		if (r(e.first, p->e.first)) 
			return cauta_rec(p->st, e);

		else
			return cauta_rec(p->dr, e);
	}
}

//Complexitate timp: O(h)
//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) {
	PNod gasit = cauta_rec(rad, { c,0 });
	if (gasit == nullptr)
		return NULL_TVALOARE;
	else
		return gasit->e.second;
}

//Complexitate timp: O(h)
PNod DO::minim(PNod p) const{
	
		while (p->st != nullptr)
				p = p->st;
	
	return p;
}

//Complexitate timp: O(h)
PNod DO::sterge_rec(PNod p, TElem e) {
	if (p == nullptr)
		return nullptr;
	else {
		if (r(e.first, p->e.first) && e.first != p->e.first) {
			p->st = sterge_rec(p->st, e);
			return p;
		}
		else {
			if (!r(e.first, p->e.first) && e.first != p->e.first) {
				p->dr = sterge_rec(p->dr, e);
				return p;
			}
			else {
				PNod temp;
				PNod repl;
				if (p->st != nullptr && p->dr != nullptr) {
					temp = minim(p->dr);
					p->e = temp->e;
					p->dr = sterge_rec(p->dr, p->e);
					return p;
				}
				else {
					temp = p;
					if (p->st == nullptr && p->dr != nullptr) {
						repl = p->dr;
						repl->parinte = p->parinte;
					}
					else if (p->st != nullptr && p->dr == nullptr) {
						repl = p->st;
						repl->parinte = p->parinte;
					}
					else
						repl = nullptr;
				}
				delete temp;
				return repl;
			}
		}
	}
}

//Complexitate timp: O(h)
//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	TValoare ret = cauta(c);
	if(ret == NULL_TVALOARE)
		return NULL_TVALOARE;
	else {
		nr--;
		rad = sterge_rec(rad, { c,0 });
		return ret;
	}
}

//Complexitate timp: O(h)
PNod DO::urm(PNod curent) const {
	PNod succesor, predecesor;
	if (curent->dr != nullptr) {
		succesor = minim(curent->dr);
	}
	else {
		predecesor = curent->parinte;
		while (predecesor != nullptr && curent == predecesor->dr) {
			curent = predecesor;
			predecesor = curent->parinte;
		}
		succesor = predecesor;
	}

	return succesor;
}

//Complexitate timp: ?(1)
//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return nr;
}

//Complexitate timp: ?(1)
//verifica daca dictionarul e vid
bool DO::vid() const {
	return nr == 0;
}

//Complexitate timp: ?(1)
Iterator DO::iterator() const {
	return  Iterator(*this);
}

//Complexitate timp: O(h)
void DO::distrug_rec(PNod p) {
	if (p != nullptr) {
		distrug_rec(p->stanga());
		distrug_rec(p->dreapta());
		delete p;
	}
}

//Complexitate timp: O(h)
DO::~DO() {
	distrug_rec(rad);
}


//Complexitate timp: O(n)
//
//Subalgoritmul ceaMaiFrecventaValoare(dictionar)
//pre: it (Iterator) - iteratorul pentru dictionarul curent
//post: functia returneaza unul dintre elementele cu cea mai mare frecventa
//daca vid(dictionar) == 1
//	return -1
//altfel
//max = 0 
//pentru i -> 0,1000
//	v[i] = 0
//	it = dictionar.iterator
// cat timp valid(it) == 1
//		v[it.element.second]++
//		daca v[element(it).second] > max
//			max = v[element(it).second]
//			maxim = element(it).second
//		urmator(it)
//  return maxim
TValoare DO::ceaMaiFrecventaValoare() const {
	if (this->vid())
		return NULL_TVALOARE;
	else {
		TValoare v[1000], maxim;
		TValoare max = 0;
		for (int i = 0; i < 1000; i++) {
			v[i] = 0;
		}
		Iterator it = this->iterator();
		while (it.valid())
		{
			v[it.element().second]++;
			if (v[it.element().second] > max) {
				max = v[it.element().second];
				maxim = it.element().second;
			}
			it.urmator();
		}
		return maxim;
	}

}
