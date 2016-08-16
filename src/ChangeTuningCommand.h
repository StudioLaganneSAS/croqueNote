//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHANGE_TUNING_COMMAND_H
#define CHANGE_TUNING_COMMAND_H

#include "PKUndoableCommand.h"
#include "PKTuning.h"

//
// ChangeTuningCommand
//

class ChordableWindow;

class ChangeTuningCommand : public PKUndoableCommand
{
public:
	ChangeTuningCommand(ChordableWindow *window, 
						int32_t newSelection, 
						int32_t oldSelection,
					    PKNotationName notation);

	~ChangeTuningCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	int32_t newSelection;
	int32_t oldSelection;
	std::vector<PKTuning*> tunings;
    PKNotationName notation; 
};

#endif // CHANGE_TUNING_COMMAND_H
