/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
WaveNetWaveTableAudioProcessorEditor::WaveNetWaveTableAudioProcessorEditor (WaveNetWaveTableAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI(p), oscGUI2(p) // give the processor instance to oscGUI
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (650, 350);
    
    //Type button
    typeButton.setButtonText("Normal Wavetable");
    typeButton.setClickingTogglesState(true);
    addAndMakeVisible(typeButton);
    typeButton.addListener(this);
    typeButton.triggerClick();
    
    
    //Smooth button
    smoothButton.setButtonText("smoothing on");
    smoothButton.setClickingTogglesState(true);
    addAndMakeVisible(smoothButton);
    smoothButton.setVisible(false);
    smoothButton.addListener(this);
    smoothButton.triggerClick();
    
    
    
    //Drop down box
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&oscGUI2);
    oscGUI2.setVisible(false);
    
    // AttackSlider
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(1.0f,5000.0f); // 0.1ms - 5000ms attack time
    attackSlider.getNumDecimalPlacesToDisplay();
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 50.0, 20.0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
    attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(&attackLabel);
    attackLabel.setText("Attack", dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, false);
    attackLabel.setJustificationType(Justification::centred);
    
    // ReleaseSlider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(1.0f,5000.0f); // 0.1ms - 5000ms release time
    releaseSlider.getNumDecimalPlacesToDisplay();
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 50.0, 20.0);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(&releaseLabel);
    releaseLabel.setText("Release", dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, false);
    releaseLabel.setJustificationType(Justification::centred);
    // AmpSlider
    ampSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    ampSlider.setRange(0.0f,1.0f); // 0.0 - 1.0 master amp
    ampSlider.setValue(0.5f);
    ampSlider.getNumDecimalPlacesToDisplay();
    ampSlider.setTextBoxStyle(Slider::NoTextBox, true, 50.0, 20.0);
    ampSlider.addListener(this);
    addAndMakeVisible(&ampSlider);
    
    ampTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "amp", ampSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(&ampLabel);
    ampLabel.setText("Amp", dontSendNotification);
    ampLabel.attachToComponent(&ampSlider, false);
    ampLabel.setJustificationType(Justification::centred);
    // FreqSlider
    freqCutoffSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    freqCutoffSlider.setRange(0.0f,1.0f); // Maximillian Lopass takes 0.0 - 1.0 as input parameter
    freqCutoffSlider.getNumDecimalPlacesToDisplay();
    freqCutoffSlider.setTextBoxStyle(Slider::NoTextBox, true, 50.0, 20.0);
    freqCutoffSlider.addListener(this);
    addAndMakeVisible(&freqCutoffSlider);
    
    freqCutoffTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "cutoff", freqCutoffSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(&freqCutoffLabel);
    freqCutoffLabel.setText("Cutoff", dontSendNotification);
    freqCutoffLabel.attachToComponent(&freqCutoffSlider, false);
    freqCutoffLabel.setJustificationType(Justification::centred);
    // InterpolationSlider
    
    interpolationSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    interpolationSlider.setRange(0,100); // Maximillian Lopass takes 0.0 - 1.0 as input parameter
    //interpolationSlider.getNumDecimalPlacesToDisplay();
    interpolationSlider.setTextBoxStyle(Slider::NoTextBox, true, 50.0, 20.0);
    interpolationSlider.addListener(this);
    addAndMakeVisible(&interpolationSlider);
    interpolationSlider.setVisible(false);
    
    interpolationTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "interpolation", interpolationSlider);  // the correct way to interface the slider in editor with processor.

    addAndMakeVisible(&interpolationLabel);
    interpolationLabel.setVisible(false);
    interpolationLabel.setJustificationType(Justification::centredTop);
    interpolationLabel.setText("Interpolation", dontSendNotification);
    interpolationLabel.attachToComponent(&interpolationSlider, false);
    
    
    
    // Change look and feel of all sliders
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::deeppink);
    getLookAndFeel().setColour(Slider::trackColourId, Colours::lightskyblue);    
    // Ppm Meter
    addAndMakeVisible(&Meter);
    startTimer(10);  // start the timer to tick every 10ms
    
    // Add the wave window
    addAndMakeVisible(&waveWindow);
}

WaveNetWaveTableAudioProcessorEditor::~WaveNetWaveTableAudioProcessorEditor()
{

    attackTree = nullptr;
    releaseTree = nullptr;
    ampTree = nullptr;
    freqCutoffTree = nullptr;
    interpolationTree = nullptr;
}

//==============================================================================
void WaveNetWaveTableAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("WaveNet WaveTable Synth by Hanoi Hantrakul x Richard Yang", getLocalBounds(), Justification::bottom, 1);
}

void WaveNetWaveTableAudioProcessorEditor::resized()
{
    // Define a box area size, then sequentially remove spaces from it
    auto area = getLocalBounds();
    auto headerHeight = 20;
    auto footerHeight = 20;
    area.removeFromTop    (headerHeight);
    area.removeFromBottom (footerHeight);
    
    
    
    // >>> Add type button
    auto typeButtonWidth = 650;
    auto typeButtonHeight = 30;
    typeButton.setBounds((area.removeFromTop(typeButtonHeight)).removeFromLeft(typeButtonWidth).reduced(20,0));
    
    
    //area.removeFromTop(headerHeight);
    auto subArea1 = area;
    area.removeFromTop(headerHeight);
    auto subArea2 = area;
    // >>> Sliders..this is the correct way to "sequentially" add objects by removing bounds from the original window
    auto sliderWidth = 80;
    attackSlider.setBounds(area.removeFromLeft(sliderWidth));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth));
    subArea1.removeFromLeft(sliderWidth*2);
    
    
    // >>> Add the first combo box
    auto comboBoxHeight = 80;
    auto comboBoxWidth = 120;
    
    oscGUI.setBounds((subArea1.removeFromTop(comboBoxHeight)).removeFromLeft(comboBoxWidth).reduced(0, 20));
    oscX = oscGUI.getX();
    oscY = oscGUI.getY();
    oscW = oscGUI.getWidth();
    oscH = oscGUI.getHeight();
    
    // >>> Add the second combo box base on position of the first one
    auto oscPos = oscGUI.getBounds();
    oscPos.setX(oscX+comboBoxWidth);
    oscGUI2.setBounds(oscPos);
    
    // >> paint oscGUI again to the initial location
    oscGUI.setBounds(oscX+60,oscY,oscW,oscH);
    
    // >>> Add the interpolation slider
    auto sliderHeightHorizon = 20;
    auto sliderWidthHorizon = 250;
    interpolationSlider.setBounds((subArea1.removeFromTop(sliderHeightHorizon)).removeFromLeft(sliderWidthHorizon).reduced(20,0));
    
    
    // >>> Add wave window
    auto windowHeight = 150;
    auto waveWindowPos = (subArea1.removeFromTop(windowHeight)).removeFromLeft(sliderWidthHorizon).reduced(20,10);
    waveWindow.setBounds(waveWindowPos); //`reduced()` puts a border around the window
    
    // >>> Add smooth button
    auto smoothButtonWidth = 240;

    smoothButton.setBounds((subArea1.removeFromTop(headerHeight)).removeFromLeft(smoothButtonWidth).reduced(60,0));
    
    // >>> Peak Meter
    auto peakMeterWidth = 80;
    Meter.setBounds(subArea2.removeFromRight(peakMeterWidth).reduced(20,0));
    
    // >>> Amp and cutoff Sliders
    freqCutoffSlider.setBounds(subArea2.removeFromRight(sliderWidth));
    ampSlider.setBounds(subArea2.removeFromRight(sliderWidth));
}

//==============================================================================
void WaveNetWaveTableAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // `switch` statements do not work on pointer comparisons
    if (slider == &ampSlider) {
        processor.ampValue = ampSlider.getValue();
    }
    else if (slider == &attackSlider) {
        processor.attackTime = attackSlider.getValue();
    }
    else if (slider == &releaseSlider) {
        processor.releaseTime = releaseSlider.getValue();
    }
    else if (slider == &freqCutoffSlider) {
        processor.freqCutoff = freqCutoffSlider.getValue();
    }
    else if (slider == &interpolationSlider) {
        processor.interpolation = interpolationSlider.getValue();
        Time::waitForMillisecondCounter(Time::getMillisecondCounter() + plotDelay);
        waveWindow.repaint();
    }
}

//==============================================================================
void WaveNetWaveTableAudioProcessorEditor::timerCallback()
{
    //DBG(processor.getVppm());
    Meter.setValue(processor.getVppm());
    if (oscGUI.comboBoxChangeState == true || oscGUI2.comboBoxChangeState == true)
    {
        waveWindow.iWaveMode = *processor.tree.getRawParameterValue("wavetype");
        waveWindow.repaint();
        oscGUI.comboBoxChangeState = false;
        oscGUI2.comboBoxChangeState = false;
    }
    
}

void WaveNetWaveTableAudioProcessorEditor::buttonClicked(Button *button)
{
    if (button == &typeButton)
    {
        if (!processor.buttonState)
        {

            typeButton.setButtonText("Neural Wavetable");
            waveWindow.bIsWavenet = true;
            Time::waitForMillisecondCounter(Time::getMillisecondCounter() + plotDelay);
            waveWindow.repaint();
            typeButton.setColour(TextButton::buttonOnColourId, Colours::lightskyblue);
            processor.buttonState = true;
            smoothButton.setVisible(true);
            processor.buttonState2 = true;
            oscGUI.setBounds(oscX,oscY,oscW,oscH);
            oscGUI2.setVisible(true);
            interpolationSlider.setVisible(true);
            interpolationLabel.setVisible(true);
            
        }
        else
        {
            typeButton.setButtonText("Normal Wavetable");
            waveWindow.bIsWavenet = false;
            Time::waitForMillisecondCounter(Time::getMillisecondCounter() + plotDelay);
            waveWindow.repaint();
            processor.buttonState = false;
            smoothButton.setVisible(false);
            processor.buttonState2 = true;
            oscGUI.setBounds(oscX+60,oscY,oscW,oscH);
            oscGUI2.setVisible(false);
            interpolationSlider.setVisible(false); 
            interpolationLabel.setVisible(false);
            
            
        }
    }
    if (button == &smoothButton)
    {
        if (!processor.buttonState2)
        {
            
            smoothButton.setButtonText("smoothing on");
            processor.buttonState2 = true;
            Time::waitForMillisecondCounter(Time::getMillisecondCounter() + plotDelay);
            waveWindow.repaint();
        }
        else
        {
            smoothButton.setButtonText("smoothing off");
            processor.buttonState2 = false;
            Time::waitForMillisecondCounter(Time::getMillisecondCounter() + plotDelay);
            waveWindow.repaint();
        }
    }
    
    
    
}
