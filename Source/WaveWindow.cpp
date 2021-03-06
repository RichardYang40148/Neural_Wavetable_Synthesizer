/*
  ==============================================================================

    WaveWindow.cpp
    Created: 21 Apr 2018 3:44:32pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveWindow.h"

//==============================================================================
WaveWindow::WaveWindow()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveWindow::~WaveWindow()
{
}

void WaveWindow::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::darkgrey);   // clear the background

    
    int waveTableLength = 514;
    if (bIsNeural){
        for (int i = 1; i < waveTableLength-1; i++) {
            float x_pos = ((float)i / (float)waveTableLength) * getLocalBounds().getWidth();
            float y_pos = getLocalBounds().getHeight() * ((wavenetBuffer[i] + 1)/2);
            g.setColour(Colours::lightskyblue);
            g.drawEllipse(x_pos, y_pos, 1.0f, 1.0f, 1.0f);
        }
    }
    else{
        
        
    
        if (iWaveMode == 0) {
            for (int i = 1; i < waveTableLength-1; i++) {
                float x_pos = ((float)i / (float)waveTableLength) * getLocalBounds().getWidth();
                float y_pos = getLocalBounds().getHeight() * ((sineBuffer[i] + 1)/2);
                g.setColour(Colours::lightskyblue);
                g.drawEllipse(x_pos, y_pos, 1.0f, 1.0f, 1.0f);
            }
        }
        else if (iWaveMode == 1) {
            for (int i = 1; i < waveTableLength-1; i++) {
                float x_pos = ((float)i / (float)waveTableLength) * getLocalBounds().getWidth();
                float y_pos = getLocalBounds().getHeight() * ((sawBuffer[i] + 1)/2);
                g.setColour(Colours::lightskyblue);
                g.drawEllipse(x_pos, y_pos, 1.0f, 1.0f, 1.0f);
            }
        }
        else{
            for (int i = 1; i < waveTableLength-1; i++) {
                float x_pos = ((float)i / (float)waveTableLength) * getLocalBounds().getWidth();
                float y_pos = getLocalBounds().getHeight() * ((triBuffer[i] + 1)/2);
                g.setColour(Colours::lightskyblue);
                g.drawEllipse(x_pos, y_pos, 1.0f, 1.0f, 1.0f);
            }
        }
    
    
        
    }
}

void WaveWindow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
