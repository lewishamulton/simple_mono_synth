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
    
}


void EffectsData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
   
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    //set up delay buffer
    delayBufferLength  = (int) 2.0 * sampleRate;
    if (delayBufferLength < 1) {
        delayBufferLength = 1;
    }
    
    delayBuffer.setSize(2, delayBufferLength);
    delayBuffer.clear();
    
    delayReadPosition = (int) (delayWritePosition - (delayTime * sampleRate) + delayBufferLength) % delayBufferLength;
    
    distFx.prepare(spec);
    isPrepared = true;
}




void EffectsData::distortionProcess(juce::AudioBuffer<float>& synthBuffer)
{
    distFx.reset();
    
    //make sure prepareToPlay has been called before process
    jassert (isPrepared);

    juce::dsp::AudioBlock<float> block { synthBuffer };
    
    distFx.process(juce::dsp::ProcessContextReplacing<float> { block });
        
    
}

void EffectsData::delayProcess(juce::AudioBuffer<float>& distBuffer, int numInputChannels, int numOutputChannels)
{
    //make sure prepareToPlay has been called before process
    jassert (isPrepared);
    
    const int numSamples = distBuffer.getNumSamples();
    
    int delayReadPos;
    int delayWritePos;
    
    for(int channel = 0; channel < numInputChannels; ++channel) {
        
        //set up our two buffers
        float* channelData = distBuffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(fmin(channel, delayBuffer.getNumChannels() - 1));
        delayReadPos = delayReadPosition;
        delayWritePos = delayWritePosition;
        
        for(int sample = 0; sample < numSamples; ++sample) {
            const float inputSample = channelData[sample];
            float outputSample = 0.0f;
            
            outputSample = (inputSample + delayMix * delayData[delayReadPos]);
            
            delayData[delayWritePos] = inputSample * (delayData[delayReadPos] * delayFeedback);
            
            channelData[sample] = outputSample;
        }
    }
    
    delayReadPosition = delayReadPos;
    delayWritePosition = delayWritePos;
    
    //cleans the buffer just in case
    for (int i = numInputChannels; i < numOutputChannels; ++i)
        distBuffer.clear (i, 0, distBuffer.getNumSamples());
}


void EffectsData::updateParameters(const bool newDistEngaged, const float newDistMix,const bool newDelayEngaged, const float newDelayTime, const float newDelayFeedback, float newDelayMix)
{
    distEngaged = newDistEngaged;
    distMix = newDistMix;
    
    delayEngaged = newDelayEngaged; 
    delayTime = newDelayTime;
    delayFeedback = newDelayFeedback;
    delayMix = newDelayMix;
}

void EffectsData::fxEngaged(juce::AudioBuffer<float>& synthBuffer, int numInputChannels, int numOutputChannels)
{
    if (distEngaged)
        distortionProcess(synthBuffer);
    
    if (delayEngaged)
        delayProcess(synthBuffer, numInputChannels, numOutputChannels); 
    
}

void EffectsData::reset() noexcept
{
    distFx.reset();
}


