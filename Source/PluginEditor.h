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
#include "WaveWindow.h"

//==============================================================================
/**
*/
class WaveNetWaveTableAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener,  public Timer
{
public:
    WaveNetWaveTableAudioProcessorEditor (WaveNetWaveTableAudioProcessor&);
    ~WaveNetWaveTableAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    
    void sliderValueChanged (Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveNetWaveTableAudioProcessor& processor;
    
    // For the dropdown box
    Oscillator oscGUI;
    
    // Create Tree objects: this is JUCE's way of communicating values between `PluginEditor` and `PluginProcessor`
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> ampTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> freqCutoffTree;
    
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    Slider ampSlider;
    Slider freqCutoffSlider;
    
    Label attackLabel;
    Label decayLabel;
    Label sustainLabel;
    Label releaseLabel;
    Label ampLabel;
    Label freqCutoffLabel;
    
    // For PPM meter
    MeterComponent Meter;
    
    // For WaveWindow
    WaveWindow waveWindow;
    
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveNetWaveTableAudioProcessorEditor)
};
