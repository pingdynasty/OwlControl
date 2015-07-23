#ifndef APPLICATIONCOMMANDS_H_INCLUDED
#define APPLICATIONCOMMANDS_H_INCLUDED

namespace ApplicationCommands {
  enum ApplicationCommands {
    updateFirmware = 0x2001,
    checkForFirmwareUpdates = 0x2002,
    sendPatch = 0x2003,
    applicationVersionInfo = 0x2005
  };
}

#endif  // APPLICATIONCOMMANDS_H_INCLUDED
