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
    Oscillator(NeuralWaveTableAudioProcessor&);
    ~Oscillator();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox* box) override;
    bool comboBoxChangeState = false;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NeuralWaveTableAudioProcessor& processor;
    
    ComboBox oscMenu;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
    
};
