//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChordableFactory.h"
#include "BarViewVectorControl.h"
#include "AddBarsVectorControl.h"
#include "BarHeaderSpacer.h"
#include "ChordableVectorControlRoot.h"
#include "InsertBarsVectorControl.h"

//
// ChordableFactory
//

ChordableFactory::ChordableFactory()
{
	this->objectsAvailable.push_back("BarViewVectorControl");
    this->objectsAvailable.push_back("AddBarsVectorControl");
	this->objectsAvailable.push_back("BarHeaderSpacer");
    this->objectsAvailable.push_back("ChordableVectorControlRoot");
	this->objectsAvailable.push_back("InsertBarsVectorControl");
}

ChordableFactory::~ChordableFactory()
{
	
}

std::vector<std::string> ChordableFactory::getAvailableObjectsList()
{
	return this->objectsAvailable;
}

PKObject *ChordableFactory::createObject(std::string className)
{
	if(className == "BarViewVectorControl")
	{
		return new BarViewVectorControl();
	}
    
    if(className == "AddBarsVectorControl")
    {
        return new AddBarsVectorControl();
    }

	if(className == "BarHeaderSpacer")
	{
		return new BarHeaderSpacer();
	}

    if(className == "ChordableVectorControlRoot")
    {
        return new ChordableVectorControlRoot();
    }

    if(className == "InsertBarsVectorControl")
    {
        return new InsertBarsVectorControl();
    }

	return NULL;
}
		
