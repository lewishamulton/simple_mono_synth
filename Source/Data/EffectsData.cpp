/*
  ==============================================================================

    EffectsData.cpp
    Created: 10 Sep 2021 6:04:04pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "EffectsData.h"
#include <JuceHeader.h>


EffectsData::EffectsData()
{
    auto& preGain = distFx.template get<preGainIndex>();
    preGain.setGainDecibels (30.0f);

    auto& postGain = distFx.template get<postGainIndex>();
    postGain.setGainDecibels (0.0f);
}


void EffectsData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
   
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    
    distFx.prepare(spec);
    isPrepared = true;
}




void EffectsData::distortionProcess(juce::AudioBuffer<float>& synthBuffer)
{
    
    distFx.reset();
    //make sure prepareToPlay has been called before process
    jassert (isPrepared);

    juce::dsp::AudioBlock<float> block { synthBuffer };
    
    auto& waveshaper = distFx.template get<waveshaperIndex>();
    waveshaper.functionToUse = [this] (float inputSignal)
                            {
                                return std::tanh (inputSignal * distMix);
                            };
    
    distFx.process(juce::dsp::ProcessContextReplacing<float> { block });
    
}


void EffectsData::updateParameters(const float newDistThresh, const float newDistMix, const float newDelayTime, const float newDelayFeedback)
{
    distThresh = newDistThresh;
    distMix = newDistMix;
    delayTime = newDelayTime;
    delayFeedback = newDelayFeedback;
}

void EffectsData::reset() noexcept
{
    distFx.reset();
}


