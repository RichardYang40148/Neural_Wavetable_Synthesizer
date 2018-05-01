/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MeterComponent.h"
#include "Oscillator.h"
#include "Oscillator2.h"
#include "WaveWindow.h"

//==============================================================================
/**
*/
class WaveNetWaveTableAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener,  public Timer, public TextButton::Listener
{
public:
    WaveNetWaveTableAudioProcessorEditor (WaveNetWaveTableAudioProcessor&);
    ~WaveNetWaveTableAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    
    void sliderValueChanged (Slider* slider) override;
    void buttonClicked (Button *button) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveNetWaveTableAudioProcessor& processor;
    
    // For the dropdown box
    Oscillator oscGUI;
    Oscillator2 oscGUI2;
    int oscX;
    int oscY;
    int oscW;
    int oscH;
    // Create Tree objects: this is JUCE's way of communicating values between `PluginEditor` and `PluginProcessor`
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> ampTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> freqCutoffTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> interpolationTree;
    
    Slider attackSlider;
    Slider releaseSlider;
    Slider ampSlider;
    Slider freqCutoffSlider;
    Slider interpolationSlider;
    
    Label attackLabel;
    Label releaseLabel;
    Label ampLabel;
    Label freqCutoffLabel;
    Label interpolationLabel;
    
    // Button for mode switch (Normal v.s. Neural Wavetable)
    TextButton typeButton;
    // Button for smooth switch (switch on to activate smoothing, off to use original wavetable)
    TextButton smoothButton;
    // Button for Normalization switch (switch on to activate Normalization, off to use original wavetable)
    TextButton normalizeButton;
    // For PPM meter
    MeterComponent Meter;
    
    // For WaveWindow
    WaveWindow waveWindow;
    int plotDelay = 10;
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveNetWaveTableAudioProcessorEditor)
};
