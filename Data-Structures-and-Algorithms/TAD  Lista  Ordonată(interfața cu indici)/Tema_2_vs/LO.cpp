#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

TNod::TNod(TElement elem) {
	this->elem = elem;
	this->next = nullptr;
}

LO::LO(Relatie r) {
	this->p = nullptr;
	this->rel = r;
}

/*
-caz favorabil:
T(n) = n = θ(n)

-caz defavorabil:
T(n) = n = θ(n)

-caz mediu:
T(n) = θ(n)

--Complexitatea: O(n)
*/
// returnare dimensiune
int LO::dim() const {
	PNod contor = p;
	int len = 0;
	while (contor != nullptr) {
		len++;
		//cout << contor->elem << " ";
	    contor = contor->next;
	}
	//cout << "\n";
	return len;
}

// verifica daca LO e vida
bool LO::vida() const {
	return p == nullptr;
}

// prima pozitie din LO
Iterator LO::prim() const {
	return Iterator(*this);
}

/*
-caz favorabil:
T(n) = 1 = θ(1)

-caz defavorabil:
T(n) = n = θ(n)

-caz mediu:
T(n) = 1/logn * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = θ(n)

--Complexitatea: O(n)
*/
// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
	PNod contor = p;
	while (contor != nullptr && rel(contor->elem, poz.element())) {
		if (contor->elem == poz.element()) {
			return poz.element();
		}
		contor = contor->next;
	}
	throw exception("Iterator invalid!");
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	PNod contor = p, anterior = nullptr;
	while (contor != nullptr && rel(contor->elem, poz.element())) {
		if (contor->elem == poz.element()) {
			if (anterior == nullptr) {
				TElement old = contor->elem;
				p = contor->next;
				poz.urmator();
				return old;
			}
			TElement old = contor->elem;
			anterior->next = contor->next;
			poz.urmator();
			return old;
		}
		anterior = contor;
		contor = contor->next;
	}
	throw exception("Iterator invalid!");
}

/*
-caz favorabil:
T(n) = 1 = θ(1)

-caz defavorabil:
T(n) = n = θ(n)

-caz mediu:
T(n) = 1/n * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = θ(n)

--Complexitatea: O(n)
*/
// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const{
	Iterator iter(*this);
	while (iter.valid()) {
		if (iter.element() == e)
			break;
		iter.urmator();
	}
	return iter;
}

/*
-caz favorabil:
T(n) = 1 = θ(1)

-caz defavorabil:
T(n) = n = θ(n)

-caz mediu:
T(n) = 1/n * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = θ(n)

--Complexitatea: O(n)
*/
// adaugare element in LO
void LO::adauga(TElement e) {
	PNod nodNou = new TNod(e);
	PNod contor, anter;
	if (p == nullptr) {
		p = nodNou;
		return;
	}
	contor = p;
	anter = nullptr;
	while (contor != NULL && rel(contor->elem ,e)) {
		anter = contor;
		contor = contor->next;
	}
	if (anter != nullptr)
		anter->next = nodNou;
	else {
		p = nodNou;
	}
	nodNou->next = contor;
}


//destructor
LO::~LO() {
	while (p != nullptr) {
		PNod aux = p;
		p = p->next;
		delete aux;
	}
}

/*
int LO::ultimulIndex(TElement e) const {
	int index = -1, poz = 1;
	Iterator iter(*this);
	while (iter.valid()) {
		if (iter.element() == e)
			index = poz;
		iter.urmator();
		poz++;
	}
	return index;
}
*/


/* 
Subalgoritm ultimulIndex(e):
pre: e = TElement
post: iter este un iterator ce reprezinta ultima aparitie a elementului
iterator(nw)
urmator(nw)
iterator(it)
Cat timp valid(nw) executa:
   Daca rel(element(nw),e) !=0 atunci:
      return iter;
   urmator(iter);
   urmator(nw);
   exceptie(Iteratorinvalid)
*/
/*
-caz favorabil:
T(n) = 1 = θ(1)

-caz defavorabil:
T(n) = n = θ(n)

-caz mediu:
T(n) = 1/n * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = θ(n)

--Complexitatea: O(n)
*/
Iterator LO::ultimulIndex(TElement e) const {
	Iterator nw(*this);
	nw.urmator();
	Iterator iter(*this);
	while (nw.valid()) {
		if (!rel(nw.element() , e))
			return iter;
		iter.urmator();
		nw.urmator();
	}
	throw exception("Iterator invalid!");
}