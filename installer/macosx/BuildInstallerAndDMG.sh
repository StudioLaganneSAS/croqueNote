
echo "Creating output folder (Output_Files)..."
rm -rf Output_Files
mkdir Output_Files
echo "Copying Release app.."
cp -r ../../build/Release/Croque-Note.app Output_Files/
echo "Mounting DMG image to Desktop..."
hdiutil mount "Croque-Note.dmg"
open /Volumes/Croque-Note/
sleep 2
echo "Removing old app..."
rm -rf /Volumes/Croque-Note/Croque-Note.app
sleep 2
echo "Copying new app..."
cp -r Output_Files/Croque-Note.app /Volumes/Croque-Note/
sleep 2
echo "Unmounting DMG image..."
hdiutil unmount /Volumes/Croque-Note/
sleep 4
killall -9 diskimages-helper
echo "Converting DMG Image..."
hdiutil convert -format UDCO -o "Output_Files/Croque-Note.dmg" Croque-Note.dmg
echo "Done!"

