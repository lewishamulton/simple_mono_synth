/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/EffectsComponent.h"
#include "StyleSheet.h"

//==============================================================================
/**
*/
class TapSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TapSynthAudioProcessorEditor (TapSynthAudioProcessor&);
    ~TapSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    
    //method to affect slider parameters
    void setSliderParams (juce::Slider& slider);
    TapSynthAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;
    FilterComponent filter;
    AdsrComponent modAdsr;
    EffectsComponent effects;
    
    juce::CustomStyleSheet customStyleSheet;
    
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TapSynthAudioProcessorEditor)
};
