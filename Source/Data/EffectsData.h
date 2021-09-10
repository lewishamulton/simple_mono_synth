/*
  ==============================================================================

    EffectsData.h
    Created: 10 Sep 2021 6:04:04pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EffectsData
{
public:
    void distortionProcess(AudioBuffer<float>& buffer, inputSample, const float thresh, const float mix);
    void updateParameters(const float distThresh, const float distMix, const float delayTime, const int delayFeedback);
    
  
private:
    
};
