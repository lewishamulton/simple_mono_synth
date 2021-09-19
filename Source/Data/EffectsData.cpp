/*
  ==============================================================================

    EffectsData.cpp
    Created: 10 Sep 2021 6:04:04pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "EffectsData.h"



float EffectsData::distortionProcess(float inputSample)
{
    auto cleanOut = inputSample;
            
    if (inputSample > distThresh) {
                    inputSample = 1.0f - expf(-inputSample);
                
    }
    else {
                    inputSample = -1.0f + expf(inputSample);
                
    }
    return ((1 - distMix) * cleanOut) + (distMix * inputSample);
}


void EffectsData::updateParameters(const float newDistThresh, const float newDistMix, const float newDelayTime, const float newDelayFeedback)
{
    distThresh = newDistThresh;
    distMix = newDistMix;
    delayTime = newDelayTime;
    delayFeedback = newDelayFeedback;
}


