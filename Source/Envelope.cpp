/*
  ==============================================================================

    Envelope.cpp
    Created: 21 Apr 2018 12:51:51pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(WaveNetWaveTableAudioProcessor& p):
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("Envelope", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void Envelope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
