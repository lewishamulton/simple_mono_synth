/*
  ==============================================================================

    OscComponent.h
    Created: 16 Jun 2021 6:35:45pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String gainId, juce::String pitchId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    
    juce::Slider gainSlider;
    
    juce::Slider pitchSlider;
    
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmDepthAttachment;
    std::unique_ptr<Attachment> gainAttachment;
    std::unique_ptr<Attachment> pitchAttachment;
    
    
    juce::Label fmFreqLabel { "FM Freq", "fm freq" };
    juce::Label fmDepthLabel {"FM Depth", "fm depth" };
    juce::Label waveSelectorLabel { "Wave Type", "wave" };
    juce::Label gainLabel { "Gain", "gain" };
    juce::Label pitchLabel {"Pitch", "pitch"};
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
