/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "maximilian.h"
#include "Ppm.h"

//==============================================================================
/**
*/
class WaveNetWaveTableAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    WaveNetWaveTableAudioProcessor();
    ~WaveNetWaveTableAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    float attackTime;
    float decayTime;
    float sustainTime;
    float releaseTime;
    float ampValue;
    float freqCutoff;
    AudioProcessorValueTreeState tree;
    
    //==============================================================================
    float getVppm();

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveNetWaveTableAudioProcessor)
    // For Synthesizer
    Synthesiser mySynth;
    SynthVoice* myVoice;
    maxiOsc testOsc;
    
    double lastSampleRate;
    
    // for Ppm meter
    CPpm* m_pCPpm;
    float* m_pfOutputVppm;
    int m_iTotalNumInputChannels;
    
    
};
