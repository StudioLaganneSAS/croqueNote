#!/bin/bash

# Call CMake first
./cleanup-project-macosx.sh
./generate-project-macosx.sh

# Now build the solution configurations
xcodebuild -project build/CroqueNote.xcodeproj/ -alltargets -configuration Debug clean
xcodebuild -project build/CroqueNote.xcodeproj/ -alltargets -configuration Debug build
xcodebuild -project build/CroqueNote.xcodeproj/ -alltargets -configuration Release clean
xcodebuild -project build/CroqueNote.xcodeproj/ -alltargets -configuration Release build

# Now build the installer/DMG
cd installer/macosx
./BuildInstallerAndDMG.sh
cd ../..

# Now copy exports
./copy-exports-macosx.sh

