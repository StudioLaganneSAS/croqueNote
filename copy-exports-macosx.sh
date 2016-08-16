#!/bin/bash

# Copy executables

zip -r export/macosx-i386/debug/bin/Croque-Note.zip build/Debug/Croque-Note.app/
zip -r export/macosx-i386/release/bin/Croque-Note build/Release/Croque-Note.app/

# Copy DMG

cp installer/macosx/Output_Files/Croque-Note.dmg export/macosx-i386/release/bin/

