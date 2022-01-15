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
#include "Data/OscData.h"
#include "Data/AdsrData.h"
#include "Data/FilterData.h"
#include "Data/EffectsData.h"






class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

    
    void updateAdsr (const float attack, const float decay, const float release, const float sustain);
    void updateFilter (const int filterType, const float cutoff, const float resonance);
    void updateModAdsr (const float attack, const float decay, const float release, const float sustain);
    void updateEffects (const bool distEngage, const float distMix, const bool delayEngage, const float delayTime, const float delayFeedback, const float delayMix);
    

    
    //inline function used to connect oscillator data to pluginprocessor
    //OscData& getOscillator1() { return osc; }
    //OscData& getOscillator2() { return osc2; }
    
    std::array<OscData, 2>& getOscillator1() { return osc1; }
    std::array<OscData, 2>& getOscillator2() { return osc2; }
    
    
    
private:
    
    
    juce::AudioBuffer<float> synthBuffer; 
    
    //Oscillators Declaration
    //OscData osc;
    //OscData osc2;
    
    static constexpr int numChannelsToProcess { 2 };
    std::array<OscData, numChannelsToProcess> osc1;
    std::array<OscData, numChannelsToProcess> osc2;
    
    //Amplitude ADSR
    AdsrData adsr;
    //Filter Declaration
    FilterData filter;
    //Modulation ADSR
    AdsrData modAdsr;
    
    //Effects Processor
    EffectsData effectsProcessor;
    
    juce::dsp::Gain<float> gain;
    
    
    
    //check used to ensure that nothing is used in audio callback before it's instantiated
    bool isPrepared { false };
};

