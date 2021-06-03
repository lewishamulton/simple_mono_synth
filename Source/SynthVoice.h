/*
  ==============================================================================

    SynthVoice.h
    Created: 31 May 2021 4:36:10pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels); 
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    
    
private:
    //ADSR
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    juce::AudioBuffer<float> synthBuffer; 
    
    //Oscillator declarations
    //juce::dsp::Oscillator<float> osc { [](float x) { return std::sin (x); }};   sine wave
    //juce::dsp::Oscillator<float> osc { [](float x) { return x <0.0f ? -0.1f : 0.01f; }}; square wave
    juce::dsp::Oscillator<float> osc { [](float x) { return x / juce::MathConstants<float>::pi; }}; //saw wave
    juce::dsp::Gain<float> gain;
    
    //check used to ensure that nothing is used in audio callback before it's instantiated
    bool isPrepared { false };
};

