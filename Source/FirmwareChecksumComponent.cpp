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
//[/Headers]

#include "FirmwareChecksumComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FirmwareChecksumComponent::FirmwareChecksumComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (checksumEditor = new TextEditor ("new text editor"));
    checksumEditor->setTooltip (TRANS("Enter checksum"));
    checksumEditor->setMultiLine (false);
    checksumEditor->setReturnKeyStartsNewLine (false);
    checksumEditor->setReadOnly (false);
    checksumEditor->setScrollbarsShown (true);
    checksumEditor->setCaretVisible (true);
    checksumEditor->setPopupMenuEnabled (true);
    checksumEditor->setText (String());

    addAndMakeVisible (confirmButton = new TextButton ("new button"));
    confirmButton->setButtonText (TRANS("Confirm"));
    confirmButton->addListener (this);

    addAndMakeVisible (cancelButton = new TextButton ("new button"));
    cancelButton->setButtonText (TRANS("Cancel"));
    cancelButton->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Enter Firmware Checksum")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FirmwareChecksumComponent::~FirmwareChecksumComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    checksumEditor = nullptr;
    confirmButton = nullptr;
    cancelButton = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FirmwareChecksumComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FirmwareChecksumComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    checksumEditor->setBounds (17, 48, 150, 24);
    confirmButton->setBounds (97, 88, 71, 24);
    cancelButton->setBounds (16, 88, 71, 24);
    label->setBounds (16, 16, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FirmwareChecksumComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == confirmButton)
    {
        //[UserButtonCode_confirmButton] -- add your button handler code here..
      if(DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
	dw->exitModalState(0);
        //[/UserButtonCode_confirmButton]
    }
    else if (buttonThatWasClicked == cancelButton)
    {
        //[UserButtonCode_cancelButton] -- add your button handler code here..
      if(DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
	dw->exitModalState(-1);
        //[/UserButtonCode_cancelButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
String FirmwareChecksumComponent::getChecksum(){
  return checksumEditor->getText();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FirmwareChecksumComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="new text editor" id="17aab5a7a252538f" memberName="checksumEditor"
              virtualName="" explicitFocusOrder="0" pos="17 48 150 24" tooltip="Enter checksum"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="3956e3bd9c035518" memberName="confirmButton"
              virtualName="" explicitFocusOrder="0" pos="97 88 71 24" buttonText="Confirm"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="b0d06f5266dac4f6" memberName="cancelButton"
              virtualName="" explicitFocusOrder="0" pos="16 88 71 24" buttonText="Cancel"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="1e6b2473a4c5f6ca" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Enter Firmware Checksum" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
