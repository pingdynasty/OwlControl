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

//[Headers] You can add your own extra header files here...
#include "ApplicationConfiguration.h"
//[/Headers]

#include "ApplicationSettingsWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ApplicationSettingsWindow::ApplicationSettingsWindow (OwlControlSettings& settings, AudioDeviceManager& deviceManager)
    : theSettings(settings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (audioSelector = new AudioDeviceSelectorComponent (deviceManager,0,0,0,0,true,true,false,false));
    audioSelector->setName ("new component");

    addAndMakeVisible (midiDeviceBox = new ComboBox ("new combo box"));
    midiDeviceBox->setEditableText (false);
    midiDeviceBox->setJustificationType (Justification::centredLeft);
    midiDeviceBox->setTextWhenNothingSelected (String());
    midiDeviceBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    midiDeviceBox->addItem (TRANS("OMNI"), 1);
    midiDeviceBox->addItem (TRANS("1"), 2);
    midiDeviceBox->addItem (TRANS("2"), 3);
    midiDeviceBox->addItem (TRANS("3"), 4);
    midiDeviceBox->addItem (TRANS("4"), 5);
    midiDeviceBox->addItem (TRANS("5"), 6);
    midiDeviceBox->addItem (TRANS("6"), 7);
    midiDeviceBox->addItem (TRANS("7"), 8);
    midiDeviceBox->addItem (TRANS("8"), 9);
    midiDeviceBox->addItem (TRANS("9"), 10);
    midiDeviceBox->addItem (TRANS("10"), 11);
    midiDeviceBox->addItem (TRANS("11"), 12);
    midiDeviceBox->addItem (TRANS("12"), 13);
    midiDeviceBox->addItem (TRANS("13"), 14);
    midiDeviceBox->addItem (TRANS("14"), 15);
    midiDeviceBox->addItem (TRANS("15"), 16);
    midiDeviceBox->addItem (TRANS("16"), 17);
    midiDeviceBox->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("MIDI Device")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    PropertySet* properties = ApplicationConfiguration::getApplicationProperties();
    deviceManager.setDefaultMidiOutput(properties->getValue("midi-output"));
    deviceManager.setMidiInputEnabled(properties->getValue("midi-input"), 1);
    //[/Constructor]
}

ApplicationSettingsWindow::~ApplicationSettingsWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioSelector = nullptr;
    midiDeviceBox = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ApplicationSettingsWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ApplicationSettingsWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    audioSelector->setBounds (48, 40, 408, 344);
    midiDeviceBox->setBounds (304, 392, 150, 24);
    label->setBounds (200, 392, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ApplicationSettingsWindow::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == midiDeviceBox)
    {
        //[UserComboBoxCode_midiDeviceBox] -- add your combo box handling code here..
      int8_t ch = comboBoxThatHasChanged->getSelectedId()-2;
      theSettings.setMidiChannel(ch+1);
        //[/UserComboBoxCode_midiDeviceBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ApplicationSettingsWindow"
                 componentName="" parentClasses="public Component" constructorParams="OwlControlSettings&amp; settings, AudioDeviceManager&amp; deviceManager"
                 variableInitialisers="theSettings(settings)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="new component" id="29b98dd09a98b370" memberName="audioSelector"
                    virtualName="" explicitFocusOrder="0" pos="48 40 408 344" class="AudioDeviceSelectorComponent"
                    params="deviceManager,0,0,0,0,true,true,false,false"/>
  <COMBOBOX name="new combo box" id="5321cb4f4cee6a7b" memberName="midiDeviceBox"
            virtualName="" explicitFocusOrder="0" pos="304 392 150 24" editable="0"
            layout="33" items="OMNI&#10;1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="fafa92d43d575969" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="200 392 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MIDI Device" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
