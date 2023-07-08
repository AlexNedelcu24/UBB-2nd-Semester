#include <exception>
#include "Iterator.h"
#include "LO.h"

Iterator::Iterator(const LO& lo) : lo(lo){
	/* de adaugat */
	curent = lo.p;
}

void Iterator::prim(){
	curent = lo.p;
}

void Iterator::urmator(){
	if (this->valid() == false) {
		throw std::exception("Iterator invalid!");
	}
	curent = curent->next;
}

bool Iterator::valid() const{
	return curent != nullptr;
}

TElement Iterator::element() const{
	if (this->valid() == false) {
		throw std::exception("Iterator invalid!");
	}
	return curent->elem;
}


