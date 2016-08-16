//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHORDABLE_SELECTION_H
#define CHORDABLE_SELECTION_H

#include "BarViewVectorControl.h"

//
// ChordableSelection
// 

class ChordableSelection
{
public:
	
	ChordableSelection();
	~ChordableSelection();
	
	// Selection management
	
	int32_t getSize();
	
	void addBar(BarViewVectorControl *bar, int32_t fromDocumentIndex);
	void removeBar(BarViewVectorControl *bar);
	
	BarViewVectorControl *getFirstBar();
	BarViewVectorControl *getBarAt(int32_t index);
	
	void clear();
	
	bool hasBar(BarViewVectorControl *bar);
	
private:
	
	std::vector <BarViewVectorControl *> bars;
	std::vector <int32_t> doc_indexes;
};

#endif // CHORDABLE_SELECTION_H
