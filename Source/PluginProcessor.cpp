/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NeuralWaveTableAudioProcessor::NeuralWaveTableAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  ),
tree (*this, nullptr)
#endif
{
    // >>> For Updating slider changes... a DAW requires everything to be normalized from 0.0 - 1.0
    NormalisableRange<float> attackParam(1.0f, 5000.0f);
    NormalisableRange<float> releaseParam(1.0f, 5000.0f);
    NormalisableRange<float> ampParam(0.0f, 1.0f);
    NormalisableRange<float> freqCutoffParam(0.0f, 1.0f);  // I am using a Maximillian lopass object which takes 0.0 - 1.0 as cutoff
    
    NormalisableRange<float> interpolationParam(0, 100);
    
    // The tree object is used to communicate values between the `PluginEditor` and the `PluginProcessor`
    tree.createAndAddParameter(("attack"), "Attack", "Attack", attackParam, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter(("release"), "Release", "Release", releaseParam, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter(("amp"), "Amp", "Amp", ampParam, 0.5f, nullptr, nullptr);
    tree.createAndAddParameter(("cutoff"), "Cutoff", "Cutoff", freqCutoffParam, 1.0f, nullptr, nullptr);
    
    tree.createAndAddParameter(("interpolation"), "Interpolation", "Interpolation", interpolationParam, 50.0f, nullptr, nullptr);
    
    // For the drop down combobox
    NormalisableRange<float> wavetypeParam(0,3); // Index in the box is 1-3, but value passing in tree is from 0-2
    NormalisableRange<float> wavetype2Param(0,3); // Index in the box is 1-3, but value passing in tree is from 0-2
    tree.createAndAddParameter("wavetype", "WaveType", "Wavetype", wavetypeParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("wavetype2", "WaveType2", "Wavetype2", wavetype2Param, 1, nullptr, nullptr);
    
    
    mySynth.clearVoices();
    // >>> For Synthesizer
    // Add synth voices (max number of voices)
    for (int i = 0; i < 16; i++) {
        mySynth.addVoice(new SynthVoice());
    }
    
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
    
    // >>> For Ppm meter
    CPpm::createInstance(m_pCPpm);
}

NeuralWaveTableAudioProcessor::~NeuralWaveTableAudioProcessor()
{
    CPpm::destroyInstance(m_pCPpm);
}

//==============================================================================
const String NeuralWaveTableAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NeuralWaveTableAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool NeuralWaveTableAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool NeuralWaveTableAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double NeuralWaveTableAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NeuralWaveTableAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int NeuralWaveTableAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NeuralWaveTableAudioProcessor::setCurrentProgram (int index)
{
}

const String NeuralWaveTableAudioProcessor::getProgramName (int index)
{
    return {};
}

void NeuralWaveTableAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NeuralWaveTableAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    // Initialize CPpm object
    m_pCPpm->initInstance(sampleRate, getTotalNumInputChannels());
    
    // Create an array to store the output Vppm per channel that is computed everytime we get a block
    m_iTotalNumInputChannels = getTotalNumInputChannels();
    m_pfOutputVppm = new float [m_iTotalNumInputChannels];
}

void NeuralWaveTableAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NeuralWaveTableAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void NeuralWaveTableAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    // how to send tree value information from slider to processor is from tutorial https://www.youtube.com/watch?v=PaKXRm6RZF4&index=25&list=PLLgJJsrdwhPxa6-02-CeHW8ocwSwl2jnu
    for (int v = 0; v < mySynth.getNumVoices(); v++) {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(v))))
        {
            
            // switch between normal and Neural wavetable
            if (!buttonState) {
                
                myVoice->setOscType(tree.getRawParameterValue("wavetype"));
            }
            else{
                myVoice->setNeuralOscType(tree.getRawParameterValue("wavetype"),tree.getRawParameterValue("wavetype2") );
                myVoice->setInterpolationFile(tree.getRawParameterValue("interpolation"));
                
            }
            
            // toogle on/off wave smoothing
            if (!buttonState2) {
                myVoice->setSmooth(false);
                myVoice->setInterpolationFile(tree.getRawParameterValue("interpolation"));
            }
            else {
                
                myVoice->setSmooth(true);
                myVoice->setInterpolationFile(tree.getRawParameterValue("interpolation"));
            }
            
            
            
            // Controls the Amp and ADSR
            myVoice->setParam(tree.getRawParameterValue("amp"),
                              tree.getRawParameterValue("attack"),
                              tree.getRawParameterValue("release"));
            
            // Filter cutoff
            myVoice->setFilterCutoff(tree.getRawParameterValue("cutoff"));
        }
    }
    
    // Make sure there are no left over bits in the buffer
    buffer.clear();
    // Write audio from synth to buffer
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    // Process the audio buffer to color the meter
    const float **readPointers = buffer.getArrayOfReadPointers();
    
    m_pCPpm->process(readPointers, m_pfOutputVppm, buffer.getNumSamples());
    
    
}

//==============================================================================
bool NeuralWaveTableAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NeuralWaveTableAudioProcessor::createEditor()
{
    return new NeuralWaveTableAudioProcessorEditor (*this);
}

//==============================================================================
void NeuralWaveTableAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NeuralWaveTableAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
float NeuralWaveTableAudioProcessor::getVppm()
{
    // Output mean of Vppm across channels
    float sum = 0.0f;
    for (int c = 0; c < m_iTotalNumInputChannels; c++) {
        sum += m_pfOutputVppm[c];
    }
    return sum / static_cast<float>(m_iTotalNumInputChannels);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NeuralWaveTableAudioProcessor();
}
