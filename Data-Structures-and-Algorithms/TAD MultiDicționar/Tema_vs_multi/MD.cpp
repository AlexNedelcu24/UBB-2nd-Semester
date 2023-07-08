#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

//	Complexitate timp: ?(1)
int MD::aloca() {
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

//	Complexitate timp: ?(1)
void MD::dealoca(int i) {
	urm[i] = primLiber;
	prec[i] = primLiber;
	primLiber = i;
}

void MD::initSpatiuLiber() {
	// Complexitate ?(cp)
	for (unsigned i = 0; i < cp - 1; i++) {
		urm[i] = i + 1;
		prec[i] = i + 1;
	}
	urm[cp - 1] = -1;
	prec[cp - 1] = -1;
	primLiber = 0;
}

//	 Complexitate timp: ?(1)
int MD::creeazaNod(TElem e) {	
	int i = aloca();
	if (i != -1) {
		multi[i] = e;
		prec[i] = -1;
		urm[i] = -1;
	}
	return i;
}

//	Complexitate timp: ?(n)
void MD::redim() {	
	primLiber = elems;
	int newCp = cp * 2;
	TElem* newElem = new TElem[newCp];
	int* newUrm = new int[newCp];
	int* newPrec = new int[newCp];

	for (int i = 0; i < elems; i++) {
		newElem[i] = multi[i];
		newUrm[i] = urm[i];
		newPrec[i] = prec[i];
	}

	for (int i = elems; i < newCp - 1; i++) {
		newUrm[i] = i + 1;
		newPrec[i] = i + 1;
	}
	newUrm[newCp - 1] = -1;
	newPrec[newCp - 1] = -1;

	delete[] multi;
	delete[] urm;
	delete[] prec;

	multi = newElem;
	urm = newUrm;
	prec = newPrec;
	cp = newCp;
}

//	Complexitate timp: ?(1)
MD::MD() {
	cp = 1;
	elems = 0;
	multi = new TElem[cp];
	urm = new int[cp];
	prec = new int[cp];

	//initSpatiuLiber();
	for (unsigned i = 0; i < cp - 1; i++) {
		urm[i] = i + 1;
		prec[i] = i + 1;
	}
	urm[cp - 1] = -1;
	prec[cp - 1] = -1;
	primLiber = 0;

	prim = -1;
	ultim = -1;
	
}

/*
-caz favorabil:
T(n) = 1 = ?(1)

-caz defavorabil:
T(n) = n = ?(n)

-caz mediu:
T(n) = 1/n * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = ?(n)

--Complexitatea: O(n)
*/
void MD::adauga(TCheie c, TValoare v) {
	int nou = creeazaNod({ c, v });
	elems++;

	if (primLiber == -1) {
		redim();
	}

	if (elems == 1) {
		prim = nou;
		ultim = nou;
	}
	else {
		urm[nou] = prim;
		prec[prim] = nou;
		prim = nou;
	}
}

/*
-caz favorabil:
T(n) = 1 = ?(1)

-caz defavorabil:
T(n) = n = ?(n)

-caz mediu:
T(n) = 1/n * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = ?(n)

--Complexitatea: O(n)
*/
bool MD::sterge(TCheie c, TValoare v) {
	bool afis = true;
	if (elems == 0)
		return false;
	if (multi[prim].first == c && multi[prim].second == v)
	{
		int dl = prim;
		prim = urm[prim];
		dealoca(dl);
		elems--;
		return true;
	}
	else {
		int q = prim;


		while ((multi[q].first != c || multi[q].second != v) && q != -1) {

			q = urm[q];
		}

		if (q != -1)
		{
			if (q == ultim) {
				ultim = prec[q];
				urm[ultim] = -1;
			}
			else {
				urm[prec[q]] = urm[q];
				prec[urm[q]] = prec[q];
			}
			dealoca(q);
			elems--;
			return true;
		}
	}
	return false;
}

//	Complexitate timp: ?(n)
vector<TValoare> MD::cauta(TCheie c) {
	//return vector<TValoare>();

	vector<TValoare> vect;

	IteratorMD i = iterator();
	while (i.valid()) {
		if (i.element().first == c)
			vect.push_back(i.element().second);
		i.urmator();
	}

	return vect;

}

//	Complexitate timp: ?(1)
int MD::dim() const {
	return elems;
}

//	Complexitate timp: ?(1)
bool MD::vid() const {
	if (elems == 0)
	    return true;
	return false;
}

//	Complexitate timp: ?(1)
IteratorMD MD::iterator() {
	return IteratorMD(*this);
}

//	Complexitate timp: ?(1)
MD::~MD() {
	delete[] multi;
	delete[] urm;
	delete[] prec;
}


