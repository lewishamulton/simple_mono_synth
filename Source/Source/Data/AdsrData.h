/*
  ==============================================================================

    AdsrData.h
    Created: 14 Jun 2021 5:23:29pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class AdsrData : public juce::ADSR
{
    
public:
    void updateADSR(const float attack, const float decay, const float release, const float sustain);
    
private:
    juce::ADSR::Parameters adsrParams;
    
}; 
