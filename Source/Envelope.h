/*
  ==============================================================================

    Envelope.h
    Created: 21 Apr 2018 12:51:51pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(WaveNetWaveTableAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveNetWaveTableAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
