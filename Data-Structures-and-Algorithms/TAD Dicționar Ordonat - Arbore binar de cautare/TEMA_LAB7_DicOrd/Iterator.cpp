#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

//Complexitate timp: ?(1)
Iterator::Iterator(const DO& d) : dict(d){
	curent = dict.rad;
}

//Complexitate timp: ?(1)
void Iterator::prim(){
	curent = dict.rad;
}

//Complexitate timp: O(h)
void Iterator::urmator(){
	if (this->valid() == false) {
		throw std::exception("Iterator invalid!");
	}
	curent = dict.urm(curent);
}

//Complexitate timp: ?(1)
bool Iterator::valid() const{
	return curent != nullptr;
}

//Complexitate timp: ?(1)
TElem Iterator::element() const{
	if (this->valid() == false) {
		throw std::exception("Iterator invalid!");
	}
	return curent->element();
}


