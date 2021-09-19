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
    float distortionProcess(float inputSample);
    void updateParameters(const float newDistThresh, const float newDistMix, const float newDelayTime, const float newDelayFeedback);
    
  
private:
    float distThresh { 1.0f };
    float distMix { 0.3f };
    float delayTime { 1.0f };
    float delayFeedback { 1 };
};
