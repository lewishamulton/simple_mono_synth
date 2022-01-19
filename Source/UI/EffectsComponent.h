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
    
    //Shapes for engage buttons
    juce::Path engageBoxDist = juce::Path();
    juce::Path engageBoxDelay = juce::Path();

    juce::Slider distMixSlider;
    std::unique_ptr<Attachment> distMixAttachment;
    juce::Label distMixLabel { "Mix", "dist" };
    
    juce::Slider delayTimeSlider;
    std::unique_ptr<Attachment> delayTimeAttachment;
    juce::Label delayTimeLabel { "Time", "time" };
    
    juce::Slider delayFeedbackSlider;
    std::unique_ptr<Attachment> delayFeedbackAttachment;
    juce::Label delayFeedbackLabel { "Feedback", "fb" };
    
    juce::Slider delayMixSlider;
    std::unique_ptr<Attachment> delayMixAttachment;
    juce::Label delayMixLabel { "Mix", "mix" };
    
    
    using bAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    juce::ShapeButton distEngage {"Dist",juce::Colours::dimgrey, juce::Colours::darkgrey, juce::Colours::whitesmoke };
    std::unique_ptr<bAttachment> distEngageAttachment;
    
    juce::ShapeButton delayEngage {"Delay",juce::Colours::dimgrey, juce::Colours::darkgrey, juce::Colours::whitesmoke };
    std::unique_ptr<bAttachment> delayEngageAttachment;
    
    void setUpButton(juce::ToggleButton& tButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<bAttachment>& attachment);
    void setUpButton(juce::ShapeButton& tButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<bAttachment>& attachment);
    
    

    
    
};
