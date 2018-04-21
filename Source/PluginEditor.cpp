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
    : AudioProcessorEditor (&p), processor (p), oscGUI(p) // give the processor instance to oscGUI
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
    
    //Drop down box
    addAndMakeVisible(&oscGUI);
    
    // AttackSlider
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(1.0f,5000.0f); // 0.1ms - 5000ms attack time
    attackSlider.setTextValueSuffix(" ms");
    attackSlider.getNumDecimalPlacesToDisplay();
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40.0, 20.0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
    attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(&attackLabel);
    attackLabel.setText("Attack", dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, false);
    
    // DecaySlider
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(1.0f,5000.0f); // 0.1ms - 5000ms attack time
    decaySlider.setTextValueSuffix(" ms");
    decaySlider.getNumDecimalPlacesToDisplay();
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40.0, 20.0);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    
    decayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(decaySlider);
    decayLabel.setText("Decay", dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, false);
    
    // SustainSlider
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(1.0f,5000.0f); // 0.1ms - 5000ms attack time
    sustainSlider.setTextValueSuffix(" ms");
    sustainSlider.getNumDecimalPlacesToDisplay();
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40.0, 20.0);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(sustainLabel);
    sustainLabel.setText("Sustain", dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, false);
    
    // ReleaseSlider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(1.0f,5000.0f); // 0.1ms - 5000ms release time
    releaseSlider.setTextValueSuffix(" ms");
    releaseSlider.getNumDecimalPlacesToDisplay();
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40.0, 20.0);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release", dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, false);
    
    // AmpSlider
    ampSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    ampSlider.setRange(0.0f,1.0f); // 0.0 - 1.0 master amp
    ampSlider.setValue(0.5f);
    ampSlider.getNumDecimalPlacesToDisplay();
    ampSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40.0, 20.0);
    ampSlider.addListener(this);
    addAndMakeVisible(&ampSlider);
    
    ampTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "amp", ampSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(&ampLabel);
    releaseLabel.setText("Amp", dontSendNotification);
    releaseLabel.attachToComponent(&ampSlider, false);
    
    // FreqSlider
    freqCutoffSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    freqCutoffSlider.setRange(0.0f,1.0f); // Maximillian Lopass takes 0.0 - 1.0 as input parameter
    freqCutoffSlider.getNumDecimalPlacesToDisplay();
    freqCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40.0, 20.0);
    freqCutoffSlider.addListener(this);
    addAndMakeVisible(&freqCutoffSlider);
    
    freqCutoffTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "cutoff", freqCutoffSlider);  // the correct way to interface the slider in editor with processor.
    
    addAndMakeVisible(&freqCutoffLabel);
    freqCutoffLabel.setText("Cutoff", dontSendNotification);
    freqCutoffLabel.attachToComponent(&freqCutoffSlider, false);
    
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
//    delete attackTree;
//    delete releaseTree;
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
    
    // >>> Sliders..this is the correct way to "sequentially" add objects by removing bounds from the original window
    auto sliderWidth = 50;
    attackSlider.setBounds(area.removeFromLeft(sliderWidth));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth));
    ampSlider.setBounds(area.removeFromLeft(sliderWidth));
    freqCutoffSlider.setBounds(area.removeFromLeft(sliderWidth));
    
    // >>> Peak Meter
    auto peakMeterWidth = 30;
    Meter.setBounds(area.removeFromLeft(peakMeterWidth));
    
    // >>> Add the combo box
    auto comboBoxHeight = 100;
    //area.removeFromLeft(comboBoxWidth);
    oscGUI.setBounds(area.removeFromTop(comboBoxHeight));
    
    // >>> Add wave window
    auto windowHeight = area.getHeight();
    waveWindow.setBounds(area.removeFromTop(windowHeight).reduced(20,20)); //`reduced()` puts a border around the window
    
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
    else if (slider == &decaySlider) {
        processor.decayTime = decaySlider.getValue();
    }
    else if (slider == &sustainSlider) {
        processor.sustainTime = sustainSlider.getValue();
    }
    else if (slider == &releaseSlider) {
        processor.releaseTime = releaseSlider.getValue();
    }
    else if (slider == &freqCutoffSlider) {
        processor.freqCutoff = freqCutoffSlider.getValue();
    }
}

//==============================================================================
void WaveNetWaveTableAudioProcessorEditor::timerCallback()
{
    //DBG(processor.getVppm());
    Meter.setValue(processor.getVppm());
}
