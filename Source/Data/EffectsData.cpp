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
    
    auto& waveshaper = distFx.template get<waveshaperIndex>();
    waveshaper.functionToUse = [this] (float inputSignal)
                            {
                                return std::atan (inputSignal * distMix);
                            };
    
    auto& preGain = distFx.template get<preGainIndex>();
    preGain.setGainDecibels (30.0f);

    auto& postGain = distFx.template get<postGainIndex>();
    postGain.setGainDecibels (-5.0f);
    
    //smoothing filter for delay
    smoothFilter.setType(juce::dsp::FirstOrderTPTFilterType::lowpass);
    smoothFilter.setCutoffFrequency(3000.0);
}


void EffectsData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    delayFx.reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
        
    //set up delay buffer
    updateDelayLineSize();
    delayFx.setDelay(calculateDelayTimeSamples(delayTime));
    
    distFx.prepare(spec);
    delayFx.prepare(spec);
    smoothFilter.prepare(spec); 
    isPrepared = true;
}




void EffectsData::distortionProcess(juce::dsp::AudioBlock<float>& block)
{
    distFx.reset();
    
    //make sure prepareToPlay has been called before process
    jassert (isPrepared);

    distFx.process(juce::dsp::ProcessContextReplacing<float> { block });
        
    
}

void EffectsData::delayProcess(juce::dsp::AudioBlock<float>& block)
{
    
    juce::dsp::ProcessContextReplacing<float>context { block };
    
    //make sure prepareToPlay has been called before process
    jassert (isPrepared);
    
    const auto& inputBlock  = context.getInputBlock();
    const auto& outputBlock = context.getOutputBlock();
    const auto numSamples  = inputBlock.getNumSamples();
    const auto numChannels = inputBlock.getNumChannels();
    
    for (size_t channel = 0; channel < numChannels; ++channel) {
        
        auto* samplesIn  = inputBlock .getChannelPointer(channel);
        auto* samplesOut = outputBlock.getChannelPointer(channel);
        
        for (size_t i = 0; i < numSamples; ++i) {
            auto input = samplesIn[i] - lastDelayEffectOutput[channel];
            auto delay = smoothFilter.processSample (int (channel), calculateDelayTimeSamples(delayTime));
            
            delayFx.pushSample (int (channel), input);
            delayFx.setDelay ((float) delay);
            const auto output =  delayFx.popSample (int (channel));
            samplesOut[i] = input + delayMix*output;
            lastDelayEffectOutput[channel] = output * delayFeedback;
        }
    }
}

void EffectsData::updateDelayLineSize()
{
    auto delayLineSizeSamples = 0;
    jassert(delayTime > 0 && delayTime <= 1);
}

int EffectsData::calculateDelayTimeSamples(float delayTimeSecs)
{
    jassert(delayTimeSecs > 0);
    int dSample =  juce::roundToInt(delayTimeSecs * sampleRate);
    
    return dSample;
}






void EffectsData::updateParameters(const bool newDistEngaged, const float newDistMix,const bool newDelayEngaged, const float newDelayTime, const float newDelayFeedback, float newDelayMix)
{
    distEngaged = newDistEngaged;
    distMix = newDistMix;
    
    delayEngaged = newDelayEngaged; 
    delayTime = newDelayTime;
    updateDelayLineSize();
    delayFeedback = newDelayFeedback;
    delayMix = newDelayMix;
}

void EffectsData::fxEngaged(juce::AudioBuffer<float>& synthBuffer)
{
    juce::dsp::AudioBlock<float> block { synthBuffer };
    if (distEngaged)
          distortionProcess(block);
    if (delayEngaged)
        delayProcess(block);

}

void EffectsData::reset() noexcept
{
    distFx.reset();
    delayFx.reset();
    smoothFilter.reset();
}


