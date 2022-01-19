/*
  ==============================================================================

    FilterComponent.cpp
    Created: 21 Jun 2021 5:42:35pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId)
{
    juce::StringArray choices {"lo-pass", "band-pass", "hi-pass"};
    filterTypeSelector.addItemList(choices, 1);
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour(0x1001312));
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colour(0x1001312));
    addAndMakeVisible(filterTypeSelector);
    
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, filterTypeSelector);
    
    
    
    //Resonance and Cutoff filter controls
    setSliderWithLabel(filterFreqSlider, filterFreqLabel , apvts, filterFreqId, filterFreqAttachment);
    setSliderWithLabel(filterResSlider, filterResLabel, apvts, filterResId, filterResAttachment);
    
    
    //filter type selector
    filterSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterSelectorLabel.setFont (15.0f);
    filterSelectorLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (filterSelectorLabel);
    
}

FilterComponent::~FilterComponent()
{
    
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    
    g.fillAll (juce::Colour(0x1001312));
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    //g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    //static numbers for now
    const auto startY = 55;
    const auto sliderWidth = 80;
    const auto sliderHeight = 70;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    filterTypeSelector.setBounds (10, startY + 5, 90, 30);
    filterSelectorLabel.setBounds (10, startY - labelYOffset, 90, labelHeight);
    
    filterFreqSlider.setBounds (filterTypeSelector.getRight(), startY, sliderWidth, sliderHeight);
    filterFreqLabel.setBounds (filterFreqSlider.getX(), filterFreqSlider.getY() - labelYOffset, filterFreqSlider.getWidth(), labelHeight);

    filterResSlider.setBounds (filterFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    filterResLabel.setBounds (filterResSlider.getX(), filterResSlider.getY() - labelYOffset, filterResSlider.getWidth(), labelHeight);

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void FilterComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
