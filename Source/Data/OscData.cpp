/*
  ==============================================================================

    OscData.cpp
    Created: 16 Jun 2021 5:24:18pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{

    prepare(spec);

    fmOsc.prepare(spec);
    gain.prepare(spec);
    
}


void OscData::setWaveType(const int choice)
{

    switch (choice) {
        case 0:
            //sine wave
            initialise( [](float x) { return std::sin (x); });
            break;
            
        case 1:
            //saw wave
             initialise( [](float x) { return x / juce::MathConstants<float>::pi; });
            break;
        
        case 2:
            //square wave
            initialise( [](float x) { return x <0.0f ? -0.1f : 0.01f; });
            break;
                   
        default:
            //should not reach here
            jassert(false);
            break;
    }
}


void OscData::setWaveFrequency(const int midiNoteNumber)
{
    //sets the oscillator frequency allowing for different notes to be played, with fmMod modulating freq 
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + lastPitch) + fmMod);
    lastMidiNote = midiNoteNumber;

}

void OscData::setPitch(const int pitch)
{
    lastPitch = pitch;
    setFrequency (juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch) + fmMod));
}

 void OscData::setUnisonPitch(const int pitch)
{
    lastPitch = pitch;
    setFrequency (juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch + 1.1f) + fmMod));
}


void OscData::setGainLevel(const float decibelLevel)
{
    gain.setGainDecibels (decibelLevel);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    
    //sample by sample processing for fm synthesis
    for (int ch =0; ch < block.getNumChannels(); ++ch)
    {
        for (int s = 0; s < block.getNumSamples(); ++s)
        {
            //value of the wave at one given point in time
            fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
        }
    }

    process (juce::dsp::ProcessContextReplacing<float>(block));
    gain.process (juce::dsp::ProcessContextReplacing<float> (block));
}


//version of function used to replace getNextAudioBlock for multi osc synth 
float OscData::processNextSample(float sample)
{
    //value of the wave at one given point in time
    fmMod = fmOsc.processSample(sample) * fmDepth;
    return gain.processSample(processSample(sample));
}

void OscData::setFmParams(const float depth, const float freq)
{
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + lastPitch) + fmMod;
    
    //updates main oscillator, ensuring no negative frequencies
    setFrequency(currentFreq >=0 ? currentFreq : currentFreq * -1.0f);
    
}


