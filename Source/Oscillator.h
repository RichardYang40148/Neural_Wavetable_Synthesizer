/*
  ==============================================================================

    Oscillator.h
    Created: 21 Apr 2018 10:21:32am
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component, public ComboBox::Listener
{
public:
    Oscillator(WaveNetWaveTableAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox* box) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveNetWaveTableAudioProcessor& processor;

    ComboBox oscMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
    
};
