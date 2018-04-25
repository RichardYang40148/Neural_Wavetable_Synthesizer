/*
  ==============================================================================

    SynthVoice.h
    Created: 18 Apr 2018 10:46:12pm
    Author:  Lamtharn Hantrakul

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr; // cast otherwise leave as nullptr
    }
    
    //===========================================
    void getParam (float* amp, float* attack, float* decay, float* sustain, float* release)
    {
        // dereference the pointers
        masterAmp = *amp;
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    }
    void getInterpolationFile(float* interpolation)
    {
        osc1.interpolationRead(float(*interpolation), int(iWaveCombination), bool(bInterpolationReversed));
    }
    
    //===========================================
    // For controlling the OSC type
    void getOscType(float* selection)
    {
        theWave = *selection; //dereferenec the selection
        theMode = 0;
    }
    /* Sloppy version of handling wave combination
    sinsin     0
    sinsaw     3 1
    sintri     4 0
    
    sawsin     3 0
    sawsaw     1
    sawtri     5 1
    
    trisin     4 1
    trisaw     5 0
    tritri     2
    */
    void getNeuralOscType(float* selection, float* selection2)
    {
        if(*selection ==0)
        {
            if(*selection2 ==0)
            {
                iWaveCombination = 0;
            }
            else if (*selection2 ==1)
            {
                iWaveCombination = 3;
                bInterpolationReversed = true;
            }
            else
            {
                iWaveCombination = 4;
                bInterpolationReversed = false;
            }
        }
        else if (*selection ==1)
        {
            if(*selection2 ==0)
            {
                iWaveCombination = 3;
                bInterpolationReversed = false;
            }
            else if (*selection2 ==1)
            {
                iWaveCombination = 1;
            }
            else
            {
                iWaveCombination = 5;
                bInterpolationReversed = true;
            }
        }
        else
        {
            if(*selection2 ==0)
            {
                iWaveCombination = 4;
                bInterpolationReversed = true;
            }
            else if (*selection2 ==1)
            {
                iWaveCombination = 5;
                bInterpolationReversed = false;
            }
            else
            {
                iWaveCombination = 2;
            }
        }
        theMode = 1;
    }
    
    double setOscType ()
    {
        if (theMode == 0) {
            if (theWave == 0) {
                return osc1.sinewave(frequency);
            }
            else if (theWave == 1) {
                return osc1.saw(frequency);
            }
            else{
                return osc1.triangle(frequency);
            }
        }
        else{
            return osc1.wavenetbuf4(frequency);
        }
    }
    
    //===========================================
    // For controlling the Filter Cutoff
    void getFilterCutoff(float* cutoff)
    {
        theCutoff = *cutoff; // dereference the cutoff
    }
    
    float setFilterCutoff()
    {
  
        return theCutoff; // to follow same design pattern as `getOscType` and `setOscType`
    }
    
    //===========================================
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;  // velocity is already normalized
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    //===========================================
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0) {
            clearCurrentNote();
        }
        
    }
    
    //===========================================
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //===========================================
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
     //===========================================
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        // ADSR level is set by `getParam`.
        // Add the waveforms to the block
        for (int sample = 0; sample < numSamples; sample++) {
            double theSound = env1.adsr(setOscType(), env1.trigger) * level * masterAmp;
            double filteredSound = filter1.lopass(theSound, setFilterCutoff());  // simple lopass
            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
                outputBuffer.addSample(channel, startSample, filteredSound);
            }
            ++startSample;
        }
    }
private:
    double level;
    double frequency;
    double masterAmp;
    int theWave;  // wave type selection index
    int theMode;  // wave mode selection index
    
    int iWaveCombination = 0;  // wave type selection index
    bool bInterpolationReversed = false;  // wave mode selection index
    
    float theCutoff;  // LPF cutoff
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};
