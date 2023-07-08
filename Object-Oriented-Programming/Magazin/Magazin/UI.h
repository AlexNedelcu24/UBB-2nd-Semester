#pragma once
#include "Service.h"
#include <unordered_map>

class Console {
private:
	Magazin& srv;
public:
	Console(Magazin& srv) noexcept :srv{ srv } {};
	Console(const Console& o) = delete;

	void raport();
	void printMeniu();
	void printCos();
	void uiCos();
	void uiAddCos();
	void uiAddRandomCos();
	void uiEmptyCos();
	void uiAdauga();
	void uiSterge();
	void uiCauta();
	void uiModifica();
	void uiFiltreaza();
	void uiSort();
	void printProduse(const vector<Produs>& produse);
	void uiExportCos();
	void run();
};