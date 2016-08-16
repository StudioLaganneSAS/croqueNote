//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef SHOW_TEMPO_COMMAND_H
#define SHOW_TEMPO_COMMAND_H

#include "PKUndoableCommand.h"

//
// ShowTempoCommand
//

class ChordableWindow;

class ShowTempoCommand : public PKUndoableCommand
{
public:
	ShowTempoCommand(ChordableWindow *window);
	~ShowTempoCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
};

#endif // SHOW_TEMPO_COMMAND_H
