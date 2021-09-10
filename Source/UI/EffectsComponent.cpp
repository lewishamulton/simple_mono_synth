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
EffectsComponent::EffectsComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distThreshId, juce::String distMixId)
{
    //Dist Threshold and Distortion Mix controls
    setSliderWithLabel(distThreshSlider, distThreshLabel , apvts, distThreshId, distThreshAttachment);
    setSliderWithLabel(distMixSlider, distMixLabel, apvts, distMixId, distMixAttachment);

}

EffectsComponent::~EffectsComponent()
{
}

void EffectsComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("EffectsComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void EffectsComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

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

