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
    
    //tells synth it is finished
    if(!allowTailOff || !adsr.isActive()){
        clearCurrentNote();
    }
    
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
    
    
    //arbitrary params for adsr for testing
    adsrParams.attack = 0.08f;
    adsrParams.decay = 0.8f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.5f;
    adsr.setParameters(adsrParams);
    
    
    
    //prepare to play has been called, audio callback members can be used elsewhere
    isPrepared = true;
}; 


void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    
    //stop execution of project if prepareToPlay not instantiated 
    jassert(isPrepared);
    
    
    //if voice is silent it will return nothing
    if (!isVoiceActive()) {
        return;
    }
    
    //set avoid reallocating to true as we dont want to reallocate memory for the buffer
    //with each callback, we allocate just enough for additional samples
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    
    
    
    //create alias
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    //process context replacing
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //once osc is run run audioBlock contains all sine info that gain can then
    //act upon
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    //Apply ADSR to oscillator, synthBuffer is the audioBlock basically 
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    
    if(startSample != 0) {
        jassertfalse; 
    }
    
    
    //need to add any info from the pluginProcessor's output buffer into synthBuffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        //tells synthesiser it has finished playing the note
        if(!adsr.isActive()) {
            clearCurrentNote();
        }
    }

};
