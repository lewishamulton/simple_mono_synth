/*
  ==============================================================================

    OscData.h
    Created: 16 Jun 2021 5:24:18pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class OscData : public juce::dsp::Oscillator<float>
{
    
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void setGainLevel(const float decibelLevel);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams(const float fmDepth, const float freq); 

    
    
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); }};
    juce::dsp::Gain<float> gain; 
    float fmMod { 0.0f };
    float fmDepth { 0.0f };
    int lastMidiNote; 

};
