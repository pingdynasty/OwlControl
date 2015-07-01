#ifndef __APPLICATIONCONFIGURATION_H__
#define __APPLICATIONCONFIGURATION_H__

#include "../JuceLibraryCode/JuceHeader.h"

class ApplicationConfiguration {
public:
  static void initialise();
  static void release();
  static PropertiesFile* getApplicationProperties();
  static File getApplicationDirectory();
  static String getApplicationDescription();
private:
};

#endif  // __APPLICATIONCONFIGURATION_H__
