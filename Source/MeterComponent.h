/*
  ==============================================================================

    MeterComponent.h
    Created: 17 Apr 2018 5:39:55pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MeterComponent    : public Component
{
public:
    MeterComponent();
    ~MeterComponent();

    void paint (Graphics&) override;
    void resized() override;
    void setValue(float fdBValue);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
    
    Colour meterColor = Colours::mediumorchid;
    float fMeterHeight;
    float m_fEpsilon;
    float m_fMaxHeight;
    float m_fMinDb;
    
    float scaleDBtoMeterHeight(float fdBValue);
};
