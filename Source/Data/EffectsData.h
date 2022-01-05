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
    
    EffectsData(); 
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels);
    void distortionProcess(juce::AudioBuffer<float>& synthBuffer);
    void distortionEffect(); 
    void updateParameters(const float newDistThresh, const float newDistMix, const float newDelayTime, const float newDelayFeedback);
    void reset() noexcept;

    
  
private:
    float distThresh { 1.0f };
    float distMix { 0.3f };
    float delayTime { 1.0f };
    float delayFeedback { 1 };
    bool isPrepared  = false;
    enum{ preGainIndex, waveshaperIndex, postGainIndex }; 
    juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::WaveShaper<float, std::function<float(float)>>, juce::dsp::Gain<float>> distFx;
    
    
};
