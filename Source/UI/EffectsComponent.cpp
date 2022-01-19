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
    
    g.fillAll (juce::Colour(0x1001312));
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    //g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
    
    
}

void EffectsComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 80;
    const auto sliderHeight = 70;
    const auto labelYOffset = 10;
    const auto labelHeight = 20;
    const auto elementPadding = 20;
    
    
    distMixSlider.setBounds (0, startY, sliderWidth, sliderHeight);
    distMixLabel.setBounds (distMixSlider.getX(), distMixSlider.getY() - labelYOffset, distMixSlider.getWidth(), labelHeight);
    
    
    delayTimeSlider.setBounds(0,(startY + sliderHeight + elementPadding), sliderWidth, sliderHeight);
    delayTimeLabel.setBounds(delayTimeSlider.getX(), delayTimeSlider.getY() - labelYOffset, delayTimeSlider.getWidth(), labelHeight);
    
    delayFeedbackSlider.setBounds(delayTimeSlider.getRight(),(startY + sliderHeight + elementPadding), sliderWidth, sliderHeight);
    delayFeedbackLabel.setBounds(delayFeedbackSlider.getX(), delayFeedbackSlider.getY() - labelYOffset, delayFeedbackSlider.getWidth(), labelHeight);
    
    delayMixSlider.setBounds(delayFeedbackSlider.getRight(), (startY + sliderHeight + elementPadding), sliderWidth, sliderHeight);
    delayMixLabel.setBounds(delayMixSlider.getX(), delayFeedbackSlider.getY() - labelYOffset, delayMixSlider.getWidth(), labelHeight);
    
    //delayEngage.setBounds(delayMixSlider.getRight()+10,(startY + sliderHeight + elementPadding),sliderWidth, sliderHeight);
    //distEngage.setBounds(delayMixSlider.getRight()+10, startY, sliderWidth, sliderHeight);
    
    //Set up engage buttons
    engageBoxDelay.startNewSubPath(665, distMixSlider.getY());
    engageBoxDelay.lineTo((665+30), (distMixSlider.getY() - 30));
    engageBoxDelay.closeSubPath();
    engageBoxDelay.addRectangle(engageBoxDelay.getBounds());
    delayEngage.setBounds(275, delayMixSlider.getY()+sliderHeight/3, 30, 30);

    engageBoxDist.startNewSubPath(665, delayMixSlider.getY());
    engageBoxDist.lineTo((665+30), (delayMixSlider.getY() - 30));
    engageBoxDist.closeSubPath();
    engageBoxDist.addRectangle(engageBoxDist.getBounds());
    distEngage.setBounds(275, distMixSlider.getY()+sliderHeight/3, 30, 30);
    
    delayEngage.setShape(engageBoxDelay, false, true, false);
    distEngage.setShape(engageBoxDist, true, true, false);
    
    addAndMakeVisible(delayEngage);
    addAndMakeVisible(distEngage);
    
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
    slider.setTextBoxStyle (juce::Slider::NoTextBox, true, 50, 25);
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

void EffectsComponent::setUpButton(juce::ShapeButton& tButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<bAttachment>& attachment)
{
    
    tButton.setToggleable(true);
    tButton.setClickingTogglesState(true);
    tButton.setOnColours (juce::Colours::whitesmoke, juce::Colours::whitesmoke, juce::Colours::whitesmoke);
    tButton.shouldUseOnColours(true);
    tButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, paramId, tButton);
}




