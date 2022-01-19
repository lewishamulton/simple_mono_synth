/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 14 Jun 2021 5:22:36pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    componentName = name;
    
    setSliderWithLabel (attackSlider, attackLabel, apvts, attackId, attackAttachment);
    setSliderWithLabel (decaySlider, decayLabel, apvts, decayId, decayAttachment);
    setSliderWithLabel (sustainSlider, sustainLabel, apvts, sustainId, sustainAttachment);
    setSliderWithLabel (releaseSlider, releaseLabel, apvts, releaseId, releaseAttachment);
}


AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    
    g.fillAll (juce::Colour(0x1001312));
    g.setColour (juce::Colours::white);
    //g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 25;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 35;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds (attackSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    decaySlider.setBounds (attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds (decaySlider.getX(), labelStart, sliderWidth, labelHeight);
    
    sustainSlider.setBounds (decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds (sustainSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    releaseSlider.setBounds (sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds (releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    
}


using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void AdsrComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
    slider.setTextBoxStyle (juce::Slider::NoTextBox, true, 50, 25);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}
