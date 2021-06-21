/*
  ==============================================================================

    FilterData.cpp
    Created: 21 Jun 2021 1:14:34pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "FilterData.h"


void FilterData:: prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
{
    //clears anything previous
    filter.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    
    filter.prepare(spec);
    
    isPrepared = true;
}

void FilterData::process (juce::AudioBuffer<float>& buffer)
{
    
    //make sure prepareToPlay has been called before process
    jassert (isPrepared);

    juce::dsp::AudioBlock<float> block { buffer };
    //could possibly break, more testing needed
    filter.process(juce::dsp::ProcessContextReplacing<float> { block });
}

//for enumarated type
void FilterData::updateParameters (const int filterType, const float freq, const float resonance)
{
    switch (filterType) {
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        
        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
            
        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    
    filter.setCutoffFrequency(freq);
    filter.setResonance(resonance);
    
}

void FilterData::reset ()
{
    filter.reset();
}
