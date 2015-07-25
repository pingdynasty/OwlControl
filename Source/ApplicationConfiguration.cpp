#include "ApplicationConfiguration.h"
#include "JuceHeader.h"

void ApplicationConfiguration::initialise(){
  PropertiesFile* properties = ApplicationConfiguration::getApplicationProperties();
  // getMidiMessageReceiver()->setMidiInput(properties->getValue("midiinput"));
  // getBlipSim()->setMidiOutput(properties->getValue("midioutput"));
}

static PropertiesFile* properties = NULL;
PropertiesFile* ApplicationConfiguration::getApplicationProperties(){
  if(properties == NULL){
    PropertiesFile::Options opts;
    opts.osxLibrarySubFolder = "Application Support";
    opts.folderName = "RebelTechnology";
    opts.applicationName = "OwlControl";
    opts.filenameSuffix = ".properties";
    properties = new PropertiesFile(opts);
    if(!properties->containsKey("application-directory"))
      properties->setValue("application-directory", File::getSpecialLocation(File::userDocumentsDirectory)
			   .getChildFile(opts.applicationName).getFullPathName());
    if(!properties->containsKey("midi-output"))
      properties->setValue("midi-output", "OWL-MIDI");
    if(!properties->containsKey("midi-input"))
      properties->setValue("midi-input", "OWL-MIDI");
    if(!properties->containsKey("bootloader-dfu-options"))
      properties->setValue("bootloader-dfu-options", "0x8000000:leave");
    if(!properties->containsKey("firmware-dfu-options"))
      properties->setValue("firmware-dfu-options", "0x8008000:leave");
    if(!properties->containsKey("owl-updates-url"))
      properties->setValue("owl-updates-url", "http://hoxtonowl.com/software/updates");
      if(!properties->containsKey("owl-updates-dir-url"))
          properties->setValue("owl-updates-dir-url", "http://hoxtonowl.com/wp-content/uploads/");
      if(!properties->containsKey("show-low-level-items"))
         properties->setValue("show-low-level-items", "0");
    if(!properties->isValidFile())
      std::cerr << "Invalid properties file: " << properties->getFile().getFullPathName() << std::endl;
  }
  return properties;
}

File ApplicationConfiguration::getApplicationDirectory(){
  PropertySet* properties = getApplicationProperties();
  File dir(properties->getValue("application-directory"));
  if(!dir.exists())
    dir.createDirectory();
  return dir;
}

String ApplicationConfiguration::getApplicationDescription(){
  return "OwlControl v0.2" + newLine
    + "Built by the OWL Team" + newLine
    + "see http://hoxtonowl.com for more information";
}

void ApplicationConfiguration::release(){
/*     If you're leaking, it's probably because you're using old-fashioned, non-RAII techniques for */
/*     your object management. Tut, tut. Always, always use ScopedPointers, OwnedArrays, */
/*     ReferenceCountedObjects, etc, and avoid the 'delete' operator at all costs! */
  if(properties != NULL)
    properties->saveIfNeeded();
  deleteAndZero(properties);
}
