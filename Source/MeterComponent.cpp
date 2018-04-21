/*
  ==============================================================================

    MeterComponent.cpp
    Created: 17 Apr 2018 5:39:55pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterComponent.h"


//==============================================================================
MeterComponent::MeterComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_fEpsilon = 1.0f * pow(10.0f,-5.0f); // if signal is 0 we should get -100dB
    m_fMinDb = -30.0f;
}

MeterComponent::~MeterComponent()
{
}

void MeterComponent::paint (Graphics& g)
{
    auto area = getLocalBounds();
    auto textHeight = 20;
    
    // Set text
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Meter", area.removeFromBottom(textHeight), Justification::bottom, 1);
    
    // Draw our vertical bar by defining two points
    Point<float> Corner1(0, area.getHeight()); // Bottom of the meter
    Point<float> Corner2(area.getWidth(), area.getHeight() - fMeterHeight); // Top of the meter
    Rectangle <float> Meter(Corner1,Corner2);
    g.setColour(meterColor);
    g.fillRect(Meter);
    g.drawRect(Meter);
    
  
}

void MeterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

float MeterComponent::scaleDBtoMeterHeight(float fdBValue)
{
    //DBG((1.0f-(fdBValue/-12.0f)) * 300.0f);
    float fHeightValue = (1.0f-(fdBValue/m_fMinDb)) * getLocalBounds().getHeight();  // Scale the dB value according to the height
    
    // If height is too high (above 300 pixels), clamp it to the max height
    if (fHeightValue > getLocalBounds().getHeight()) {
        fHeightValue = getLocalBounds().getHeight();
    }
    // If height is very small (less than 100 pixels), clamp the meter to a small value (can't draw a rectangle with height of 0)
    if (fHeightValue < 0) {
        fHeightValue = 1.0f * pow(10.0f,-5.0f);
    }
    //DBG(fHeightValue);
    return fHeightValue;
}

void MeterComponent::setValue(float fdBValue)
{
    //DBG(fdBValue);
    // if dB value is above threshold then paint it and set the height accordingly
    if (fdBValue > m_fMinDb) {
       fMeterHeight = scaleDBtoMeterHeight(fdBValue);
    } else {
        // make the height a very small non zero value (`DrawRect()` doesn't like 0 height)
        fMeterHeight = 1.0f * pow(10.0f,-5.0f);
    }
    //Mark the object for repainting
    repaint();
}
