//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef HIDE_TEMPO_COMMAND_H
#define HIDE_TEMPO_COMMAND_H

#include "PKUndoableCommand.h"

//
// HideTempoCommand
//

class ChordableWindow;

class HideTempoCommand : public PKUndoableCommand
{
public:
	HideTempoCommand(ChordableWindow *window);
	~HideTempoCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
};

#endif // HIDE_TEMPO_COMMAND_H
