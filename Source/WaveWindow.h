/*
  ==============================================================================

    WaveWindow.h
    Created: 21 Apr 2018 3:44:32pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "maximilian.h"

//==============================================================================
/*
*/
class WaveWindow    : public Component
{
public:
    WaveWindow();
    ~WaveWindow();

    void paint (Graphics&) override;
    void resized() override;
    bool bIsWavenet = false;
    int  iWaveMode = 0;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveWindow)
    
    
    
};
