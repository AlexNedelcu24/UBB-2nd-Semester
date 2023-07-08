#include "IteratorMD.h"
#include "MD.h"

using namespace std;

//Complexitate timp : ? (1)
IteratorMD::IteratorMD(MD& _md) : md(_md) {
	/* de adaugat */
	curent = _md.prim;
}

//Complexitate timp : ? (1)
TElem IteratorMD::element() const {
	if (this->valid() == false) {
		throw std::exception("Iterator invalid!");
	}
	/* de adaugat */
	//return pair <TCheie, TValoare>(-1, -1);
	return md.multi[curent];
}

//Complexitate timp : ? (1)
bool IteratorMD::valid() const {
	/* de adaugat */
	//return false;
	return curent != -1;
}

//Complexitate timp : ? (1)
void IteratorMD::urmator() {
	if (this->valid() == false) {
		throw std::exception("Iterator invalid!");
	}
	/* de adaugat */
	curent = md.urm[curent];
}

//Complexitate timp : ? (1)
void IteratorMD::prim() {
	/* de adaugat */
	curent = md.prim;
}

//Complexitate timp : ?(1)
//
//Subalgoritmul elimina(md, iterator)
//pre: md - multidictionar, iterator - IteratorMD 
//post: returneaza elementul sters ; md' 
//daca iterator.valid() == false
//   @ arunca exceptie
//deleted = md.multi[curent]
//iterator.urmator()
//md.sterge(deleted.first, deleted.second)
//return deleted
TElem IteratorMD::elimina() {
	if (valid() == false) {
		throw exception{ "Iterator invalid!" };
	}
	TElem deleted = md.multi[curent];
	urmator();
	md.sterge(deleted.first, deleted.second);
	return deleted;
}
