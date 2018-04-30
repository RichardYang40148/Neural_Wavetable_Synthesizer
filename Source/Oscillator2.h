/*
 ==============================================================================
 
 Oscillator2.h
 Created: 21 Apr 2018 10:21:32am
 Author:  Lamtharn Hantrakul
 Edit by: Richard Yang
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator2    : public Component, public ComboBox::Listener
{
public:
    Oscillator2(WaveNetWaveTableAudioProcessor&);
    ~Oscillator2();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox* box) override;
    bool comboBoxChangeState = false;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveNetWaveTableAudioProcessor& processor;

    ComboBox oscMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator2)
    
};
