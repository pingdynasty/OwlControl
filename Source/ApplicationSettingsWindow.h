/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_EA96C22743249BBE__
#define __JUCE_HEADER_EA96C22743249BBE__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "OwlControlSettings.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ApplicationSettingsWindow  : public Component,
                                   public ComboBoxListener
{
public:
    //==============================================================================
    ApplicationSettingsWindow (OwlControlSettings& settings, AudioDeviceManager& deviceManager);
    ~ApplicationSettingsWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    OwlControlSettings& theSettings;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<AudioDeviceSelectorComponent> audioSelector;
    ScopedPointer<ComboBox> midiDeviceBox;
    ScopedPointer<Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApplicationSettingsWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_EA96C22743249BBE__
