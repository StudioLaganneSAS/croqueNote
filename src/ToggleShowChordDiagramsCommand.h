//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef TOGGLE_SHOW_CHORD_DIAGRAMS_COMMAND_H
#define TOGGLE_SHOW_CHORD_DIAGRAMS_COMMAND_H

#include "PKUndoableCommand.h"

//
// ToggleShowChordDiagramsCommand
//

class ChordableWindow;

class ToggleShowChordDiagramsCommand : public PKUndoableCommand
{
public:
	ToggleShowChordDiagramsCommand(ChordableWindow *window, bool toggle);
	~ToggleShowChordDiagramsCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	bool toggle;
};

#endif // TOGGLE_SHOW_CHORD_DIAGRAMS_COMMAND_H
