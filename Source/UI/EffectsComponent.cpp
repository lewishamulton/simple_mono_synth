/*
  ==============================================================================

    EffectsComponent.cpp
    Created: 10 Sep 2021 6:22:03pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EffectsComponent.h"

//==============================================================================
 EffectsComponent::EffectsComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distEngagedId, juce::String distMixId,juce::String delayTimeId,juce::String delayFeedbackId)
{
    //Distortion Engaged Button
    setUpButton(distEngage, apvts, distEngagedId, distEngageAttachment); 
    //Distortion Mix control
    setSliderWithLabel(distMixSlider, distMixLabel, apvts, distMixId, distMixAttachment);
    
    
   

}

EffectsComponent::~EffectsComponent()
{
}

void EffectsComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("Effects", labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
    
    
}

void EffectsComponent::resized()
{
    //static numbers for now
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    
    distMixSlider.setBounds (0, startY, sliderWidth, sliderHeight);
    distMixLabel.setBounds (distMixSlider.getX(), distMixSlider.getY() - labelYOffset, distMixSlider.getWidth(), labelHeight);
    
    distEngage.setBounds(distMixSlider.getRight(), startY, sliderWidth, sliderHeight);

}

 bool EffectsComponent::distEngaged()
{
    if(distEngage.getToggleState())
    {
        return true;
    }
    else {
        return false;
    }
        
}




//reference slider as don't want a copy
void EffectsComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void EffectsComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

using bAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

void EffectsComponent::setUpButton(juce::ToggleButton &tButton, juce::AudioProcessorValueTreeState &apvts, juce::String paramId, std::unique_ptr<bAttachment> &attachment)
{
    tButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(tButton);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, paramId, tButton);
    
}




