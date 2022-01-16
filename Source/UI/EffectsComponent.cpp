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
 EffectsComponent::EffectsComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distEngagedId, juce::String distMixId,juce::String delayEngagedId, juce::String delayTimeId,juce::String delayFeedbackId, juce::String delayMixId)
{
    //Engaged Buttons
    setUpButton(distEngage, apvts, distEngagedId, distEngageAttachment);
    setUpButton(delayEngage, apvts, delayEngagedId, delayEngageAttachment); 
    
    //Distortion Mix control
    setSliderWithLabel(distMixSlider, distMixLabel, apvts, distMixId, distMixAttachment);
    
    //Delay Controls
    setSliderWithLabel(delayTimeSlider, delayTimeLabel, apvts, delayTimeId, delayTimeAttachment);
    setSliderWithLabel(delayFeedbackSlider, delayFeedbackLabel, apvts, delayFeedbackId, delayFeedbackAttachment);
    setSliderWithLabel(delayMixSlider, delayMixLabel, apvts, delayMixId, delayMixAttachment);

    
}

EffectsComponent::~EffectsComponent()
{
}

void EffectsComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    
    g.fillAll (juce::Colours::darkgrey);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
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
    
    delayTimeSlider.setBounds(0,startY + sliderHeight, sliderWidth, sliderHeight);
    delayTimeLabel.setBounds(delayTimeSlider.getX(), delayTimeSlider.getY() - labelYOffset, delayTimeSlider.getWidth(), labelHeight);
    
    delayFeedbackSlider.setBounds(delayTimeSlider.getRight(),startY + sliderHeight, sliderWidth, sliderHeight);
    delayFeedbackLabel.setBounds(delayFeedbackSlider.getX(), delayFeedbackSlider.getY() - labelYOffset, delayFeedbackSlider.getWidth(), labelHeight);
    
    delayMixSlider.setBounds(delayFeedbackSlider.getRight(), startY + sliderHeight, sliderWidth, sliderHeight);
    delayMixLabel.setBounds(delayMixSlider.getX(), delayFeedbackSlider.getY() - labelYOffset, delayMixSlider.getWidth(), labelHeight);
    delayEngage.setBounds(delayMixSlider.getRight(),startY + sliderHeight,sliderWidth, sliderHeight);
    
    
    

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

bool EffectsComponent::delayEngaged()
{
    if(delayEngage.getToggleState())
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
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
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




