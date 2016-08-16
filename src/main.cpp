//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "PKApp.h"
#include "PKStr.h"
#include "ChordableWindow.h"
#include "ChordableSettings.h"
#include "PKMenu.h"
#include "PKScreenTool.h"
#include "PKi18n.h"

// Globals

ChordableWindow  *mwindow  = NULL;
PKMenu           *mainMenu = NULL;
ChordableSettings settings;

static PKApp *app;

//
// PKApp delegates
//

int32_t PKApp::appStartupDelegate(std::wstring commandLine)
{
    // Add locales
    PKi18n::getInstance()->addLocale("fr_FR");

    // Load settings
	settings.setMaxNumberOfRecentFiles(5);
    settings.load();

    // Get chosen locale
    PKi18n::getInstance()->setLocale(PKVALUE_STRING(settings.get(ChordableSettings::LANGUAGE_STRING_PROPERTY)));

	// Create the main window
	mwindow = new ChordableWindow(L"ICON", &settings);

	// Create menu

#if(defined(WIN32) || defined(LINUX))
    std::string menuXML = "<PKMenu>"
                          "  <PKMenuItem text=\"PKI18N:&File\" id=\"MENU_ID_FILE\">"
                          "    <PKMenu>"
                          "      <PKMenuItem text=\"PKI18N:&New...\" shortcut=\"Ctrl+N\" id=\"MENU_ID_NEW\" icon=\"res|NEW_SMALL\"/>"
                          "      <PKMenuItem text=\"PKI18N:&Open...\" shortcut=\"Ctrl+O\" id=\"MENU_ID_OPEN\" icon=\"res|OPEN_SMALL\"/>"
                          "      <PKMenuItem text=\"PKI18N:Open &Recent\" id=\"MENU_ID_RECENT_FILES_ITEM\" >"
                          "        <PKMenu id=\"MENU_ID_RECENT_FILES\">"
                          "        </PKMenu>"
                          "      </PKMenuItem>"
                          "      <PKSeparator/>"
						  "      <PKMenuItem text=\"PKI18N:&Save\" shortcut=\"Ctrl+S\" id=\"MENU_ID_SAVE\" icon=\"res|SAVE_SMALL\"/>"
						  "      <PKMenuItem text=\"PKI18N:Save &As...\" shortcut=\"Ctrl+Shift+S\" id=\"MENU_ID_SAVE_AS\" />"
                          "      <PKSeparator/>"
						  "      <PKMenuItem text=\"PKI18N:&Export...\" shortcut=\"Ctrl+E\" id=\"MENU_ID_EXPORT\" icon=\"res|EXPORT_SMALL\"/>"
						  "      <PKMenuItem text=\"PKI18N:&Print...\" shortcut=\"Ctrl+P\" id=\"MENU_ID_PRINT\" icon=\"res|PRINT_SMALL\"/>"
                          "      <PKSeparator/>"
						  "      <PKMenuItem text=\"PKI18N:&Quit\" shortcut=\"Alt+F4\" id=\"MENU_ID_QUIT\" />"
                          "    </PKMenu>"
                          "  </PKMenuItem>"
                          "  <PKMenuItem text=\"PKI18N:&Edit\" id=\"MENU_ID_EDIT\" >" // We need both this ID and the next one set identical to this for cut/copy/paste
                          "    <PKMenu id=\"MENU_ID_EDIT\">"
						  "      <PKMenuItem text=\"PKI18N:&Undo\" shortcut=\"Ctrl+Z\" id=\"MENU_ID_UNDO\" icon=\"res|UNDO_SMALL\" />"
						  "      <PKMenuItem text=\"PKI18N:&Redo\" shortcut=\"Ctrl+Y\" id=\"MENU_ID_REDO\" icon=\"res|REDO_SMALL\" />"
                          "      <PKSeparator/>"
						  "      <PKMenuItem text=\"PKI18N:Cu&t\" shortcut=\"Ctrl+X\" id=\"MENU_ID_CUT\" icon=\"res|CUT_SMALL\" />"
						  "      <PKMenuItem text=\"PKI18N:&Copy\" shortcut=\"Ctrl+C\" id=\"MENU_ID_COPY\" icon=\"res|COPY_SMALL\" />"
						  "      <PKMenuItem text=\"PKI18N:&Paste\" shortcut=\"Ctrl+V\" id=\"MENU_ID_PASTE\" icon=\"res|PASTE_SMALL\" />"
                          "      <PKSeparator/>"
						  "      <PKMenuItem text=\"PKI18N:Select &All\" shortcut=\"Ctrl+A\" id=\"MENU_ID_SELECT_ALL\" />"
						  "    </PKMenu>"
						  "  </PKMenuItem>"
                          "  <PKMenuItem text=\"PKI18N:&Tools\" id=\"MENU_ID_TOOLS\" >"
						  "    <PKMenu>"
						  "      <PKMenuItem text=\"PKI18N:&Transpose...\" shortcut=\"Ctrl+T\" id=\"MENU_ID_TRANSPOSE\" icon=\"res|TRANSPOSE_SMALL\" />"
                          "      <PKSeparator/>"
						  "      <PKMenuItem text=\"PKI18N:&Options...\" shortcut=\"Ctrl+Shift+O\" id=\"MENU_ID_OPTIONS\" icon=\"res|OPTIONS_SMALL\" />"
						  "    </PKMenu>"
						  "  </PKMenuItem>"
                          "  <PKMenuItem text=\"PKI18N:&Help\" right=\"true\" id=\"MENU_ID_HELP\">"
						  "    <PKMenu>"
						  "      <PKMenuItem text=\"PKI18N:H&elp...\" shortcut=\"F1\" id=\"MENU_ID_HELP\" icon=\"res|HELP_SMALL\" />"
                          "      <PKSeparator/>"
						  "      <PKMenuItem text=\"PKI18N:&About Croque-Note...\" shortcut=\"Ctrl+A\" id=\"MENU_ID_ABOUT\" />"
						  "    </PKMenu>"
						  "  </PKMenuItem>"
                          "</PKMenu>";
#endif
	
#ifdef MACOSX
    std::string menuXML =   "<PKMenu macAboutMenuId=\"MENU_ID_ABOUT\" macAboutText=\"PKI18N:About Croque-Note...\" macPrefsMenuId=\"MENU_ID_OPTIONS\" macQuitMenuId=\"MENU_ID_QUIT\" >"
							"  <PKMenuItem text=\"PKI18N:File\" id=\"MENU_ID_FILE\">"
							"    <PKMenu id=\"MENU_ID_FILE_MENU\">"
							"      <PKMenuItem text=\"PKI18N:New...\" shortcut=\"Command+N\" id=\"MENU_ID_NEW\" />"
							"      <PKMenuItem text=\"PKI18N:Open...\" shortcut=\"Command+O\" id=\"MENU_ID_OPEN\" />"
							"      <PKMenuItem text=\"PKI18N:Open Recent File\" id=\"MENU_ID_RECENT_FILES_ITEM\" >"
							"        <PKMenu id=\"MENU_ID_RECENT_FILES\">"
							"        </PKMenu>"
							"      </PKMenuItem>"
							"      <PKSeparator/>"
							"      <PKMenuItem text=\"PKI18N:Save\" shortcut=\"Command+S\" id=\"MENU_ID_SAVE\" />"
							"      <PKMenuItem text=\"PKI18N:Save As...\" shortcut=\"Shift+Command+S\" id=\"MENU_ID_SAVE_AS\" />"
							"      <PKSeparator/>"
							"      <PKMenuItem text=\"PKI18N:Export...\" shortcut=\"Command+E\" id=\"MENU_ID_EXPORT\" />"
							"      <PKMenuItem text=\"PKI18N:Print...\" shortcut=\"Command+P\" id=\"MENU_ID_PRINT\" />"
							"    </PKMenu>"
							"  </PKMenuItem>"
							"  <PKMenuItem text=\"PKI18N:Edit\" id=\"MENU_ID_EDIT\" >"
							"    <PKMenu id=\"MENU_ID_EDIT\">"
							"      <PKMenuItem text=\"PKI18N:Undo\" shortcut=\"Command+Z\" id=\"MENU_ID_UNDO\" />"
							"      <PKMenuItem text=\"PKI18N:Redo\" shortcut=\"Shift+Command+Z\" id=\"MENU_ID_REDO\" />"
							"      <PKSeparator/>"
							"      <PKMenuItem text=\"PKI18N:Cut\" shortcut=\"Command+X\" id=\"MENU_ID_CUT\" />"
							"      <PKMenuItem text=\"PKI18N:Copy\" shortcut=\"Command+C\" id=\"MENU_ID_COPY\" />"
							"      <PKMenuItem text=\"PKI18N:Paste\" shortcut=\"Command+V\" id=\"MENU_ID_PASTE\" />"
                            "      <PKSeparator/>"
						    "      <PKMenuItem text=\"PKI18N:Select All\" shortcut=\"Command+A\" id=\"MENU_ID_SELECT_ALL\" />"
							"    </PKMenu>"
							"  </PKMenuItem>"
							"  <PKMenuItem text=\"PKI18N:Tools\" id=\"MENU_ID_TOOLS\" >"
							"    <PKMenu>"
							"      <PKMenuItem text=\"PKI18N:Transpose...\" shortcut=\"Command+R\" id=\"MENU_ID_TRANSPOSE\" />"
							"    </PKMenu>"
							"  </PKMenuItem>"
							"  <PKMenuItem text=\"PKI18N:Help\" id=\"MENU_ID_HELP\">"
							"    <PKMenu>"
							"      <PKMenuItem text=\"PKI18N:Croque-Note Help...\" shortcut=\"Command+?\" id=\"MENU_ID_HELP\" />"
							"    </PKMenu>"
							"  </PKMenuItem>"
							"</PKMenu>";
#endif

    mainMenu = PKMenu::loadMenuFromXML(menuXML);

    if(mainMenu)
    {
		mainMenu->setSettings(&settings);
		mainMenu->updateRecentFilesMenu();

		app->installRootMenu(mwindow, mainMenu);
		app->updateUIStrings();
    }

    // Update i18n strings

    mwindow->updateUIStrings();

    // Read settings

    int x = PKVALUE_INT32(settings.get(ChordableSettings::WINDOW_X_INT32_PROPERTY));
    int y = PKVALUE_INT32(settings.get(ChordableSettings::WINDOW_Y_INT32_PROPERTY));
    int w = PKVALUE_INT32(settings.get(ChordableSettings::WINDOW_W_INT32_PROPERTY));
    int h = PKVALUE_INT32(settings.get(ChordableSettings::WINDOW_H_INT32_PROPERTY));

    // Place & show the main window

    PKScreenTool screen;
    std::vector<PKRect> screens = screen.getScreens();

    if(screens.size() == 0)
    {
        // Default fallback 
        mwindow->resizeWindowAreaTo(800, 600);
        mwindow->centerOnScreen();
    }
    else
    {
        PKRect mainScreen = screens[0];

        if(x == -1 || y == -1 || h == -1 || w == -1)
        {
            // Place to best fit the main screen
            w = mainScreen.w - (mainScreen.w*30/100);
            h = mainScreen.h - (mainScreen.h*20/100);

            mwindow->resizeWindowAreaTo(w, h);
            mwindow->centerOnScreen();
        }
        else
        {
            // Place as it was last time
            // But check that it still fits the screen

            if(x + w < mainScreen.x) x = 0;
            if(y + h < mainScreen.y) y = 0;

            if(x + w > mainScreen.w) w = (mainScreen.w - x);
            if(y + h > mainScreen.h) h = (mainScreen.h - y);

            mwindow->moveWindowTo(x, y);
            mwindow->resizeWindowAreaTo(w, h);
        }
    }

    mwindow->setReady();
    mwindow->show();
    mwindow->layoutInitialDocument();
	
    return 0; 
}



int32_t PKApp::appShutdownDelegate()
{

    mwindow->release();

	if(mainMenu)
	{
		mainMenu->release();
	}

    return 0;
}
