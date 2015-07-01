/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_894D3EBAC9C694FA__
#define __JUCE_HEADER_894D3EBAC9C694FA__

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
class OwlControlGui  : public Component,
                    public Value::Listener,
                    public Timer,
                    public ComboBoxListener,
                    public ButtonListener,
                    public SliderListener
{
public:
    //==============================================================================
    OwlControlGui (OwlControlSettings& settings, AudioDeviceManager& dm, Value& updateGui);
    ~OwlControlGui();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void settingsChanged();
    void valueChanged(juce::Value &value);
    void setStatus(const String& msg);
    void timerCallback();
    int inGainDbToMidi( float gain);
    int outGainDbToMidi( float gain);
    float midiToInGainDb (int midiValue);
    float midiToOutGainDb (int midiValue);
    void updateSensivity();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* owlFaceplate_png;
    static const int owlFaceplate_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    OwlControlSettings& theSettings;
    AudioDeviceManager& theDm;
    ScopedPointer<AudioDeviceSelectorComponent> audioSelector;
    uint32 timerInterval;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> samplingRateComboBox;
    ScopedPointer<Label> samplingRateLabel;
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<Slider> leftGainSlider;
    ScopedPointer<Label> leftGainLabel;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<TextButton> deviceInfoButton;
    ScopedPointer<ToggleButton> bypassButton;
    ScopedPointer<ToggleButton> swapLRButton;
    ScopedPointer<Label> rightGainLabel;
    ScopedPointer<Slider> rightGainSlider;
    ScopedPointer<Slider> leftOutGainSlider;
    ScopedPointer<Label> leftOutGainLabel;
    ScopedPointer<Label> rightOutGainLabel;
    ScopedPointer<Slider> rightOutGainSlider;
    ScopedPointer<ToggleButton> leftInputMuteButton;
    ScopedPointer<ToggleButton> rightInputMuteButton;
    ScopedPointer<ToggleButton> leftOutputMuteButton;
    ScopedPointer<ToggleButton> rightOutputMuteButton;
    ScopedPointer<ComboBox> samplingBitsComboBox;
    ScopedPointer<Label> samplingBitsLabel;
    ScopedPointer<TextButton> ledButton;
    ScopedPointer<ComboBox> protocolComboBox;
    ScopedPointer<Label> protocolLabel;
    ScopedPointer<ToggleButton> masterButton;
    ScopedPointer<Label> statusLabel;
    ScopedPointer<ComboBox> patchSlotAComboBox;
    ScopedPointer<Label> patchSlotALabel;
    ScopedPointer<TextButton> resetButton;
    ScopedPointer<ComboBox> sensitivityComboBox;
    ScopedPointer<Label> sensitivityLabel;
    ScopedPointer<TextButton> connectionButton;
    ScopedPointer<Slider> slider4;
    ScopedPointer<Slider> slider3;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label1;
    ScopedPointer<Slider> slider1;
    ScopedPointer<Label> label2;
    ScopedPointer<Slider> slider2;
    ScopedPointer<Slider> slider5;
    ScopedPointer<Label> label5;
    ScopedPointer<ComboBox> modeComboBox;
    ScopedPointer<Label> modeLabel;
    ScopedPointer<ToggleButton> remoteControlButton;
    ScopedPointer<ComboBox> blockSizeComboBox;
    ScopedPointer<Label> blockSizeeLabel;
    ScopedPointer<ToggleButton> halfSpeedButton;
    ScopedPointer<Label> messageLabel;
    ScopedPointer<Label> statsLabel;
    Image cachedImage_owlFaceplate_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OwlControlGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_894D3EBAC9C694FA__
