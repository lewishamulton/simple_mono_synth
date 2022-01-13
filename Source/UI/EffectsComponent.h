/*
  ==============================================================================

    EffectsComponent.h
    Created: 10 Sep 2021 6:22:03pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EffectsComponent  : public juce::Component
{
public:
    EffectsComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distEngagedId, juce::String distMixId,juce::String delayEngagedId, juce::String delayTimeId,juce::String delayFeedbackId, juce::String delayMixId);
    ~EffectsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool distEngaged();
    bool delayEngaged(); 
    
    
   
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsComponent)
    

    void setSliderParams(juce::Slider& slider);
        
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    

    juce::Slider distMixSlider;
    std::unique_ptr<Attachment> distMixAttachment;
    juce::Label distMixLabel { "Mix", "Mix" };
    
    juce::Slider delayTimeSlider;
    std::unique_ptr<Attachment> delayTimeAttachment;
    juce::Label delayTimeLabel { "Time", "Time" };
    
    juce::Slider delayFeedbackSlider;
    std::unique_ptr<Attachment> delayFeedbackAttachment;
    juce::Label delayFeedbackLabel { "Feedback", "Feedback" };
    
    juce::Slider delayMixSlider;
    std::unique_ptr<Attachment> delayMixAttachment;
    juce::Label delayMixLabel { "Mix", "Mix" };
    
    
    using bAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    juce::ToggleButton distEngage;
    std::unique_ptr<bAttachment> distEngageAttachment;
    
    juce::ToggleButton delayEngage;
    std::unique_ptr<bAttachment> delayEngageAttachment;
    
    void setUpButton(juce::ToggleButton& tButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<bAttachment>& attachment);
    

    
    
};
