//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHORDABLE_FACTORY_H
#define CHORDABLE_FACTORY_H

#include "IPKObjectFactory.h"

//
// ChordableFactory
//

class ChordableFactory : public IPKObjectFactory
	{
	public:
		
		ChordableFactory();
		~ChordableFactory();
		
		std::vector<std::string> getAvailableObjectsList();
		
		PKObject *createObject(std::string className);	
		
	private:
		
		std::vector<std::string> objectsAvailable;
	};

#endif // CHORDABLE_FACTORY_H