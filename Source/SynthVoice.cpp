/*
  ==============================================================================

    SynthVoice.cpp
    Created: 31 May 2021 4:36:10pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound) {

    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
};

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    
    //sets the oscillator frequency allowing for different notes to be played 
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
};

void SynthVoice::stopNote (float velocity, bool allowTailOff) {
    
    adsr.noteOff();
};

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue) {
    
};

void SynthVoice::pitchWheelMoved (int newPitchWheelValue) {
    
};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    
    
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels; 
    osc.prepare(spec);
    gain.prepare(spec);
    
    
    //between 0 and 1 for linear
    gain.setGainLinear(0.01f);
    
    //prepare to play has been called, audio callback members can be used elsewhere
    isPrepared = true;
}; 


void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    
    //stop execution of project if prepareToPlay not instantiated 
    jassert(isPrepared);
    
    
    //create alias
    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };
    //process context replacing
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //once osc is run run audioBlock contains all sine info that gain can then
    //act upon
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    //Apply ADSR to oscillator, outputBuffer is the audioBlock 
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);

};
