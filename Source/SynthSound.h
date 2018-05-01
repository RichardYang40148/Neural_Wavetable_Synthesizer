/*
  ==============================================================================

    SynthSound.h
    Created: 18 Apr 2018 10:46:05pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    // This is required by the class `SynthesizerSound`
    bool appliesToNote (int /*midiNoteNumber*/)
    {
        return true;
    }
    
    // This is required by the class `SynthesizerSound`
    bool appliesToChannel (int /*midiNoteNumber*/)
    {
        return true;
    }
};
