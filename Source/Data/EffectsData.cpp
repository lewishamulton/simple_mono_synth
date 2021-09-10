/*
  ==============================================================================

    EffectsData.cpp
    Created: 10 Sep 2021 6:04:04pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "EffectsData.h"

void distortionProcess(juce::AudioBuffer<float>& buffer, const float thresh, const float mix)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            //soft clipping dist
            auto inputSample = channelData[i];
            auto cleanOut = inputSample;
            
            if (inputSample > thresh) {
                            inputSample = 1.0f - expf(-inputSample);
                
            }
            else {
                            inputSample = -1.0f + expf(inputSample);
                
            }
            channelData[i] = ((1 - mix) * cleanOut) + (mix * inputSample);
            
        }
        
    }
}

