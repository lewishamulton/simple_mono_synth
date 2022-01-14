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
    void distortionProcess(juce::dsp::AudioBlock<float>& block);
    void delayProcess(juce::dsp::AudioBlock<float>& block);
    void updateParameters(const bool newDistEngaged, const float newDistMix,const bool newDelayEngaged, const float newDelayTime, const float newDelayFeedback, float newDelayMix); 
    void fxEngaged(juce::AudioBuffer<float>& synthBuffer);
    
    void reset() noexcept;

    
  
private:
    double sampleRate { 44100.0 };
    
    bool distEngaged { false };
    float distMix { 0.3f };
    
    bool delayEngaged { false }; 
    float delayTime { 1.0f };
    float delayFeedback { 0.75f };
    float delayMix { 1.0f };
    
    
    bool isPrepared  = false;
    enum{ preGainIndex, waveshaperIndex, postGainIndex };

    juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::WaveShaper<float, std::function<float(float)>>, juce::dsp::Gain<float>> distFx;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayFx { 44100 };
    //array needed for feedback effect
    std::array<float, 2> lastDelayEffectOutput;
    // Double precision to avoid some approximation issues
    juce::dsp::FirstOrderTPTFilter<double> smoothFilter;
    
    void updateDelayLineSize();
    int calculateDelayTimeSamples(float delayTimeSecs);
    float getDelayedSample(float sample); 

    
};
