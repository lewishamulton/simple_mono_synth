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
    //sets the oscillator frequency allowing for different notes to be played 
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));

}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    //process context replacing
    process(juce::dsp::ProcessContextReplacing<float>(block));
}


