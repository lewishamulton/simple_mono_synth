/*
  ==============================================================================

    FilterData.h
    Created: 21 Jun 2021 1:14:34pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData
{
public:
    //methods always needed for any dsp process
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels);
    void process (juce::AudioBuffer<float>& buffer);
    //for enumarated type
    void updateParameters (const int filterType, const float freq, const float resonance);
    void reset ();
    
    
 
    
    
private:
    
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared  = false;
    
};
