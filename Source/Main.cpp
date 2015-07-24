#include "../JuceLibraryCode/JuceHeader.h"
#include "OwlControlGui.h"
#include "ApplicationConfiguration.h"
#include "ApplicationSettingsWindow.h"
#include "ApplicationCommands.h"

class OwlControlApplication  : public JUCEApplication {
public:
    OwlControlApplication() : settings(dm, updateGui) {
        updateGui.setValue(0);
    }

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return false; }
    AudioDeviceManager dm;
    OwlControlSettings settings;
    ScopedPointer<OwlControlGui> gui;
   
    Value updateGui; // flag used to update Gui when Owl settings are loaded
    
    
    //==============================================================================
    void initialise (const String& commandLine)
    {
        DBG("Initialising OwlControl");
        ApplicationConfiguration::initialise();
	gui = new OwlControlGui(settings, dm, updateGui);
        commands = new ApplicationCommandManager();
        commands->registerAllCommandsForTarget(this);
        commands->registerAllCommandsForTarget(gui);
	commands->setFirstCommandTarget(gui);

        // Initialize audio/midi device
        PropertySet* props = ApplicationConfiguration::getApplicationProperties();
        if(props->getBoolValue("show-low-level-items") != true)
	  dm.initialise(0, 0, nullptr, true);
        else
	  dm.initialise(2, 2, nullptr, true);

        // start GUI
        mainWindow = new MainWindow(commands, gui, dm, updateGui);        
	mainWindow->addKeyListener(commands->getKeyMappings());
    }

    void shutdown()
    {
        ApplicationConfiguration::release();
        mainWindow = nullptr;
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

  class MainMenuModel : public MenuBarModel {
  private:
    StringArray toplevel;
    Array<PopupMenu> popups;
  public:
    MainMenuModel(ApplicationCommandManager* commands){
#if !JUCE_MAC
      PopupMenu file;
      toplevel.add("File");
      file.addCommandItem(commands, StandardApplicationCommandIDs::quit);
      popups.add(file);
#endif
      PopupMenu tools;
      toplevel.add("Tools");
      tools.addCommandItem(commands, ApplicationCommands::sendPatch);
      tools.addCommandItem(commands, ApplicationCommands::updateFirmware);
      // tools.addCommandItem(commands, ApplicationCommands::checkForFirmwareUpdates);
      popups.add(tools);
        
      PopupMenu help;
      toplevel.add("Help");
      help.addCommandItem(commands, ApplicationCommands::applicationVersionInfo);
      popups.add(help);
    }
    StringArray getMenuBarNames(){
      return toplevel;
    }
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName){
      return popups[topLevelMenuIndex];
    }
    void menuItemSelected(int menuItemID, int topLevelMenuIndex){
      DBG("menu item selected " << topLevelMenuIndex << "/" << menuItemID);
    }
  };

    /*
        This class implements the desktop window
    */
    class MainWindow    : public DocumentWindow {
    public:
      MainWindow(ApplicationCommandManager* commands, 
		 OwlControlGui* gui,
		 AudioDeviceManager& dm, 
		 Value& updateGui)  : 
	  DocumentWindow(JUCEApplication::getInstance()->getApplicationName(),
			 Colours::lightgrey, DocumentWindow::allButtons)
      {
	menu = new MainMenuModel(commands);
#if JUCE_MAC
	MenuBarModel::setMacMainMenu(menu);
#else
	setMenuBar(menu);
#endif

	tabs = new TabbedComponent(TabbedButtonBar::TabsAtTop);
	setContentOwned(tabs, false);
	tabs->addTab("Main", Colours::lightgrey, gui, false, 1);
	tabs->addTab("Application Settings", Colours::lightgrey, new ApplicationSettingsWindow(dm), true, 2);
    PropertySet* props = ApplicationConfiguration::getApplicationProperties();
	tabs->setSize(779, 700);
	centreWithSize (779, 700);
	setVisible (true);
      }
      ~MainWindow(){
#if JUCE_MAC
	MenuBarModel::setMacMainMenu(NULL);
#else
	setMenuBar(NULL);
#endif

      }
      void closeButtonPressed()
      {
	// This is called when the user tries to close this window. Here, we'll just
	// ask the app to quit when this happens, but you can change this to do
	// whatever you need.
	JUCEApplication::getInstance()->systemRequestedQuit();
      }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
      ScopedPointer<TabbedComponent> tabs;
      ScopedPointer<MainMenuModel> menu;
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
  ScopedPointer<ApplicationCommandManager> commands;
  
    
    
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (OwlControlApplication)
