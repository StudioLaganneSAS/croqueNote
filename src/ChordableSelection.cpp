//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChordableSelection.h"

//
// ChordableSelection
// 

ChordableSelection::ChordableSelection()
{
	
}

ChordableSelection::~ChordableSelection()
{
	
}

// Selection management

int32_t ChordableSelection::getSize()
{
    return this->bars.size();
}

void ChordableSelection::addBar(BarViewVectorControl *bar, int32_t fromDocumentIndex)
{
	// Check that we don't already have it

	for(uint32_t i=0; i<this->bars.size(); i++)
	{
		if(this->bars[i] == bar)
		{
			// nothing to be done
			return;
		}
	}
	
	// Now add it, at the right index
	
	bool inserted = false;
	
	for(uint32_t i=0; i<this->doc_indexes.size(); i++)
	{
		if(this->doc_indexes[i] > fromDocumentIndex)
		{
			// insert before
			this->bars.insert(this->bars.begin()+i, bar);
			this->doc_indexes.insert(this->doc_indexes.begin()+i, fromDocumentIndex);
			inserted = true;
			break;
		}
	}
	
	if(!inserted)
	{
		// push it back
		this->bars.push_back(bar);
		this->doc_indexes.push_back(fromDocumentIndex);
	}
	
	// select it
	PKVariantBool b(true);
	bar->set(BarViewVectorControl::SELECTED_BOOL_PROPERTY, &b);	
}

void ChordableSelection::removeBar(BarViewVectorControl *bar)
{
	for(uint32_t i=0; i<this->bars.size(); i++)
	{
		if(this->bars[i] == bar)
		{
			PKVariantBool b(false);
			this->bars[i]->set(BarViewVectorControl::SELECTED_BOOL_PROPERTY, &b);

			this->bars.erase(this->bars.begin()+i);
			this->doc_indexes.erase(this->doc_indexes.begin()+i);
			break;
		}
	}
}

BarViewVectorControl *ChordableSelection::getFirstBar()
{
	if(this->getSize() > 0)
	{
		return this->bars[0];
	}

    return NULL;
}

BarViewVectorControl *ChordableSelection::getBarAt(int32_t index)
{
	if(index >= 0 && index < this->bars.size())
	{
		return NULL;
	}
	
	return this->bars[index];
}

void ChordableSelection::clear()
{
	for(uint32_t i=0; i<this->bars.size(); i++)
	{
		PKVariantBool b(false);
		this->bars[i]->set(BarViewVectorControl::SELECTED_BOOL_PROPERTY, &b);
	}
	
	this->bars.clear();
	this->doc_indexes.clear();
}

bool ChordableSelection::hasBar(BarViewVectorControl *bar)
{
	for(uint32_t i=0; i<this->bars.size(); i++)
	{
		if(this->bars[i] == bar)
		{
			return true;
		}
	}	

	return false;
}


