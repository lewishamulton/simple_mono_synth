/*
  ==============================================================================

    OscComponent.cpp
    Created: 16 Jun 2021 6:35:45pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String gainId, juce::String pitchId, juce::String fmFreqId, juce::String fmDepthId)
{
    
    
    juce::StringArray choices {"sine", "saw", "square"};
    oscWaveSelector.addItemList(choices, 1);
    oscWaveSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour(0x1001312));
    oscWaveSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colour(0x1001312));
    addAndMakeVisible(oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
    
    //slider for gain control 
    setSliderWithLabel (gainSlider, gainLabel, apvts, gainId, gainAttachment);
    
    //slider for pitch
    setSliderWithLabel(pitchSlider, pitchLabel, apvts, pitchId, pitchAttachment); 
    
    //slider for fm frequency/depth
    setSliderWithLabel (fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttachment);
    setSliderWithLabel (fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment);
    
    //oscillator selector
    waveSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel.setFont (15.0f);
    waveSelectorLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (waveSelectorLabel);

    
    
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    g.fillAll (juce::Colour(0x1001312));
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    //g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
    
}

void OscComponent::resized()
{
    //static numbers for now
    const auto startY = 55;
    const auto sliderWidth = 80;
    const auto sliderHeight = 70;
    const auto labelYOffset = 10;
    const auto labelHeight = 20;
    
    oscWaveSelector.setBounds(10, startY + 5, 90, 30);
    waveSelectorLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);
    
    gainSlider.setBounds(oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - labelYOffset, gainSlider.getWidth(), labelHeight);
    
    pitchSlider.setBounds(gainSlider.getRight(), startY, sliderWidth, sliderHeight);
    pitchLabel.setBounds(pitchSlider.getX(), pitchSlider.getY() - labelYOffset, pitchSlider.getWidth(), labelHeight);
    
    fmFreqSlider.setBounds(pitchSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);

    fmDepthSlider.setBounds(fmFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
    
    
    
    
}




using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
