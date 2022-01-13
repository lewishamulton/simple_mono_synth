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
    void delayProcess(juce::AudioBuffer<float>& distBuffer, int numInputChannels, int numOutputChannels);
    void updateParameters(const bool newDistEngaged, const float newDistMix,const bool newDelayEngaged, const float newDelayTime, const float newDelayFeedback, float newDelayMix); 
    void fxEngaged(juce::AudioBuffer<float>& synthBuffer, int numInputChannels, int numOutputChannels);
    
    void reset() noexcept;

    
  
private:
    bool distEngaged { false };
    float distMix { 0.3f };
    
    bool delayEngaged { false }; 
    float delayTime { 1.0f };
    float delayFeedback { 0.75f };
    float delayMix { 1.0f };
    
    // circular buffer variables
    juce::AudioBuffer<float> delayBuffer;
    int delayBufferLength { 1 };
    int delayReadPosition { 0 };
    int delayWritePosition{ 0 };
    
    bool isPrepared  = false;
    enum{ preGainIndex, waveshaperIndex, postGainIndex };

    juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::WaveShaper<float, std::function<float(float)>>, juce::dsp::Gain<float>> distFx;
    
};
