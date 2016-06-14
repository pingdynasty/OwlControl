#include <iomanip>
#include <stdio.h>
#include "OwlControlSettings.h"
#include "OpenWareMidiControl.h"
#include "ApplicationCommands.h"
#include "ApplicationConfiguration.h"
#include "sysex.h"

void OwlControlSettings::resetParameterNames(){
  parameters.set(0, "A");
  parameters.set(1, "B");
  parameters.set(2, "C");
  parameters.set(3, "D");
  parameters.set(4, "E");
}

OwlControlSettings::OwlControlSettings(AudioDeviceManager& dm, Value& updateGui):
  pc(0), theUpdateGui(updateGui), theDm(dm)
{
  memset(midiArray, 0, NB_CHANNELS);
  theDm.addMidiInputCallback(String::empty, this);
  lastMidiMessageTime=0;
  firmwareVersion="";
  resetParameterNames();
}

OwlControlSettings::~OwlControlSettings(){
  theDm.removeMidiInputCallback(String::empty, this);
}

StringArray& OwlControlSettings::getPresetNames(){
  return presets;
}

StringArray& OwlControlSettings::getParameterNames(){
  return parameters;
}

String OwlControlSettings::getFirmwareVersion(){
    return firmwareVersion;
}

void OwlControlSettings::handlePresetNameMessage(uint8_t index, const char* name, int size){
  while(index>presets.size())
    presets.add("---");
  presets.set(index, String(name, size));
#ifdef DEBUG
  std::cout << "preset name " << (int)index << ": " << String(name, size) << std::endl;
#endif // DEBUG
  theUpdateGui.setValue(!(bool)theUpdateGui.getValue());
}

void OwlControlSettings::handleParameterNameMessage(uint8_t index, const char* name, int size){
  parameters.set(index, String(name, size));
#ifdef DEBUG
  std::cout << "parameter name " << (int)index << ": " << String(name, size) << std::endl;
#endif // DEBUG
  theUpdateGui.setValue(!(bool)theUpdateGui.getValue());
}

void OwlControlSettings::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message){
  lastMidiMessageTime = Time::currentTimeMillis();
  bool hasChanged = false;
  if(message.isController()){
    int cc = message.getControllerNumber();
    int value = message.getControllerValue();
    midiArray[cc] = value;
    hasChanged = true;
#ifdef DEBUG
    std::cout << "rx cc " << cc << ": " << value << std::endl;
#endif // DEBUG
  }else if(message.isSysEx() && message.getSysExDataSize() > 2){
    const uint8 *data = message.getSysExData();
    if(data[0] == MIDI_SYSEX_MANUFACTURER && data[1] == MIDI_SYSEX_DEVICE){
      switch(data[2]){
      case SYSEX_PRESET_NAME_COMMAND: {
	handlePresetNameMessage(data[3], (const char*)&data[4], message.getSysExDataSize()-4);
	// hasChanged = true;
	break;
      }
      case SYSEX_PARAMETER_NAME_COMMAND: {
	handleParameterNameMessage(data[3], (const char*)&data[4], message.getSysExDataSize()-4);
	hasChanged = true;
	break;
      }
      case SYSEX_DEVICE_STATS:
      case SYSEX_PROGRAM_STATS: 
	handleDeviceStatsMessage((const char*)&data[3], message.getSysExDataSize()-3);
	break;
      case SYSEX_PROGRAM_MESSAGE:
	handleProgramMessage((const char*)&data[3], message.getSysExDataSize()-3);
	break;
      case SYSEX_FIRMWARE_VERSION:
	handleFirmwareVersionMessage((const char*)&data[3], message.getSysExDataSize()-3);
	break;
      case SYSEX_CONFIGURATION_COMMAND:
	handleSysexConfigurationCommand((const char*)&data[3], message.getSysExDataSize()-3);
	break;
      case SYSEX_DEVICE_ID:
	handleDeviceIdMessage((const char*)&data[3], message.getSysExDataSize()-3);
	break;
      }
    }
  }else if(message.isProgramChange()){
    if(pc != message.getProgramChangeNumber()){
      resetParameterNames();
      pc = message.getProgramChangeNumber();
    }
#ifdef DEBUG
    std::cout << "rx pc " << pc << std::endl;
#endif // DEBUG
  }
  if(hasChanged)
    theUpdateGui.setValue(!(bool)theUpdateGui.getValue());
}

int OwlControlSettings::getConfigurationValue(const char* name){
  return configuration[String(name)];
}

void OwlControlSettings::setConfigurationValue(const char* name, int value){
  configuration.set(String(name), value);
  if(theDm.getDefaultMidiOutput() != NULL){
    String data(name);
    data += String::toHexString(value);
    const char* datap = static_cast<const char*>(data.getCharPointer());
    int size = data.length() + 4;
    uint8_t *buf = (uint8_t*)alloca(size);
    buf[0] = MIDI_SYSEX_MANUFACTURER;
    buf[1] = MIDI_SYSEX_DEVICE;
    buf[2] = SYSEX_CONFIGURATION_COMMAND;
    memcpy(&buf[3], datap, data.length());
    buf[size-1] = '\0';
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::createSysExMessage(buf, size));
  }
#ifdef DEBUG
  std::cout << "tx sysex " << name << ": " << value << std::endl;
#endif // DEBUG  
}

void OwlControlSettings::handleSysexConfigurationCommand(const char* str, int size){  
  String name(str, 2);
  int value = String(str+2, size-2).getHexValue32();
#ifdef DEBUG
  std::cout << "Configuration " << name << ": " << value << std::endl;
#endif // DEBUG
  configuration.set(name, value);
}

void OwlControlSettings::handleDeviceStatsMessage(const char* name, int size){
  statsMessage = String(name, size);
#ifdef DEBUG
  std::cout << "Device stats: " << statsMessage << std::endl;
#endif // DEBUG
  // AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Device Statistics", str);
  theUpdateGui.setValue(!(bool)theUpdateGui.getValue());
}

void OwlControlSettings::handleProgramMessage(const char* name, int size){
  programMessage = String(name, size);
#ifdef DEBUG
  std::cout << "Program message: " << programMessage << std::endl;
#endif // DEBUG
  // AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Program Message", str);
}

void OwlControlSettings::handleFirmwareVersionMessage(const char* name, int size){
  String str(name, size);
  firmwareVersion = str;
#ifdef DEBUG
  std::cout << "Device Firmware: " << str << std::endl;
#endif // DEBUG
  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Device Firmware", "Currently installed: "+str);
}

void OwlControlSettings::handleDeviceIdMessage(const char* data, int size){
#ifdef DEBUG
  std::cout << "Device ID: " << String(data, size) << std::endl;
  // for(int i=0; i<size; ++i)
  //   std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)data[i];
  // std::cout << std::endl;
#endif // DEBUG
}

void OwlControlSettings::handleErrorMessage(uint8_t data){
#ifdef DEBUG
  if(data == 0)
    std::cout << "Error status 0: OK" << std::endl;
  else
    std::cout << "Error status " << data << ": " << strerror(data) << std::endl;
#endif // DEBUG
}

void OwlControlSettings::handleSelfTestMessage(uint8_t data){
#ifdef DEBUG
  if(data & 0x01)
    std::cout << "Preset stored in FLASH" << std::endl;
  else
    std::cout << "Preset not stored in FLASH" << std::endl;
  std::cout << ((data & 0x02) ? "PASSED" : "FAILED") << " Memory test" << std::endl;
  std::cout << ((data & 0x04) ? "PASSED" : "FAILED") << " External 8MHz oscillator" << std::endl;
#endif // DEBUG
}

void OwlControlSettings::setCc(int cc,int value)
{
    // check value range
  value = std::min(NB_CHANNELS-1, std::max(0, value));
    // set midiArray and update Owl
    if (cc>0 && cc<NB_CHANNELS){
      midiArray[cc] = value;
      if(theDm.getDefaultMidiOutput() != NULL)
        theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,cc,value));
#ifdef DEBUG
      std::cout << "tx cc " << cc << ": " << value << std::endl;
#endif // DEBUG
    }
}

void OwlControlSettings::sendPc(int pc)
{
  // clip to valid value range
  pc = std::min(127, std::max(0, pc));
  if(theDm.getDefaultMidiOutput() != NULL){
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::programChange(1, pc));
  }
#ifdef DEBUG
  std::cout << "tx pc: " << (int)pc << std::endl;
#endif // DEBUG
}

int OwlControlSettings::getCc(int cc)
{
    if (cc>0 && cc<NB_CHANNELS){
        return midiArray[cc];
    }
    else{
        return -1;
    }
}

void OwlControlSettings::storeFirmware(uint8_t slot){
  if(theDm.getDefaultMidiOutput() != NULL){
    uint8_t buf[4];
    buf[0] = MIDI_SYSEX_MANUFACTURER;
    buf[1] = MIDI_SYSEX_DEVICE;
    buf[2] = SYSEX_FIRMWARE_STORE;
    buf[3] = slot & 0x7f;
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::createSysExMessage(buf, sizeof(buf)));
  }
#ifdef DEBUG
  std::cout << "tx store firmware: " << (int)slot << std::endl;
#endif // DEBUG
}

void OwlControlSettings::saveToOwl(){
  if(theDm.getDefaultMidiOutput() != NULL)
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,SAVE_SETTINGS,127));
}

void OwlControlSettings::loadFromOwl(){
  if(theDm.getDefaultMidiOutput() != NULL){
    presets.clear();
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,REQUEST_SETTINGS,127)); // Will provoke incoming midi messages
  }
}

uint64 OwlControlSettings::getLastMidiMessageTime(){
    return lastMidiMessageTime;
}

void OwlControlSettings::sendSysexMessage(InputStream* stream){
  uint8_t data[256];
  int i=0;
  // read until SySEX_EOX byte 0xf7
  do{
    data[i] = stream->readByte();
  }while (i<255 && data[i++] != 0xf7 && !stream->isExhausted());
  if(theDm.getDefaultMidiOutput() != nullptr)
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage(data, i));
}

static void encodeInt(MemoryBlock& block, uint32_t data){
    uint8_t in[4];
    uint8_t out[5];
    in[3] = (uint8_t)data & 0xff;
    in[2] = (uint8_t)(data >> 8) & 0xff;
    in[1] = (uint8_t)(data >> 16) & 0xff;
    in[0] = (uint8_t)(data >> 24) & 0xff;
    int len = data_to_sysex(in, out, 4);
    block.append(out, len);
}

void OwlControlSettings::runSysexPatch(){
    const char tailer[] =  { MIDI_SYSEX_MANUFACTURER, MIDI_SYSEX_DEVICE, SYSEX_FIRMWARE_RUN };
    MemoryBlock block; // = MemoryBlock();
    block.append(tailer, sizeof(tailer));
    if(theDm.getDefaultMidiOutput()!=nullptr)
      theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::createSysExMessage(block.getData(), block.getSize()));
}

void OwlControlSettings::storeSysexPatch(uint8_t userSlot){
  if(userSlot>=0){
    const char tailer[] =  { MIDI_SYSEX_MANUFACTURER, MIDI_SYSEX_DEVICE, SYSEX_FIRMWARE_STORE };
    MemoryBlock block = MemoryBlock();
    block.append(tailer, sizeof(tailer));
    encodeInt(block, userSlot);
    if(theDm.getDefaultMidiOutput()!=nullptr)
      theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::createSysExMessage(block.getData(), block.getSize()));
    }
}

void OwlControlSettings::flashFirmware(uint32_t checksum){
  const char tailer[] =  { MIDI_SYSEX_MANUFACTURER, MIDI_SYSEX_DEVICE, SYSEX_FIRMWARE_FLASH };
  MemoryBlock block = MemoryBlock();
  block.append(tailer, sizeof(tailer));
  encodeInt(block, checksum);
  if(theDm.getDefaultMidiOutput()!=nullptr)
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::createSysExMessage(block.getData(), block.getSize()));
}
