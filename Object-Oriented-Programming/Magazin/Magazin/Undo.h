#pragma once
#include "Produs.h"
#include "Repository.h"
#include <vector>
#include <algorithm>

class Undo
{
public:
	virtual void doUndo() = 0;
	virtual ~Undo() = default;
};

class undoUpdate : public Undo
{
	Produs p;
	ProduseRepo& repo;
public:
	undoUpdate(ProduseRepo& repo, const Produs& produs) : repo{ repo }, p{ produs } {}
	void doUndo() override
	{
		repo.modific(p);
	}
};

class undoAdd : public Undo
{
	Produs p;
	ProduseRepo& repo;
public:
	undoAdd(ProduseRepo& repo, const Produs& produs) : repo{ repo}, p{ produs} {}
	void doUndo() override
	{
		repo.remove(p);
	}
};

class undoDel : public Undo
{
	Produs p;
	ProduseRepo& repo;
public:
	undoDel(ProduseRepo& repo, const Produs& produs) : repo{ repo }, p{ produs } {}
	void doUndo() override
	{
		repo.store(p);
	}
};

