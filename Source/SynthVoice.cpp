/*
  ==============================================================================

    SynthVoice.cpp
    Created: 31 May 2021 4:36:10pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{

    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
};

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    
    //sets the oscillator frequency allowing for different notes to be played 
    osc.setWaveFrequency(midiNoteNumber);
    osc2.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modAdsr.noteOn();
};

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    
    adsr.noteOff();
    modAdsr.noteOff();
    
    //tells synth it is finished
    if(!allowTailOff || !adsr.isActive()){
        clearCurrentNote();
    }
    
};

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
};

void SynthVoice::pitchWheelMoved (int newPitchWheelValue) {
    
};

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    
    
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    //process chain oscillator -> amp adsr -> filter -> mod (filter) adsr
    osc.prepareToPlay(spec);
    osc2.prepareToPlay(spec);
    adsr.setSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock,outputChannels);
    modAdsr.setSampleRate(sampleRate);
    
    
    
    //between 0 and 1 for linear
    gain.prepare(spec);
    gain.setGainLinear(0.07f);
    
    
    //prepare to play has been called, audio callback members can be used elsewhere
    isPrepared = true;
};

void SynthVoice::updateAdsr (const float attack, const float decay, const float release, const float sustain)
{
    
    adsr.updateADSR(attack, decay, release, sustain);
    
}; 


void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
    //stop execution of project if prepareToPlay not instantiated 
    jassert(isPrepared);
    
    
    //if voice is silent it will return nothing
    if (!isVoiceActive()) {
        return;
    }
    
    //set 'avoid reallocating' to true as we allocate just enough memory for additional samples
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    
    //activate ADSR, however does not modify anything in synth buffer
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    synthBuffer.clear();
    
    //oscillators
    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer (ch, 0);
        
        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = osc.processNextSample (buffer[s]) + osc2.processNextSample (buffer[s]);
        }
    }
    
    
    //create alias
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    //osc.getNextAudioBlock(audioBlock);
    
    //Apply ADSR to oscillator, synthBuffer is the audioBlock basically
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
        
    //call process to actually run audio through it
    filter.process(synthBuffer);
    
    

    
    
    //crashes if startSample before operation is not zero
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
    
}

void SynthVoice::updateFilter (const int filterType, const float cutoff, const float resonance)
{
    
    float modulator =  modAdsr.getNextSample();
    
    filter.updateParameters(filterType, cutoff, resonance, modulator);

}

void SynthVoice::updateModAdsr (const float attack, const float decay, const float release, const float sustain)
{
    modAdsr.updateADSR(attack, decay, release, sustain); 
}
