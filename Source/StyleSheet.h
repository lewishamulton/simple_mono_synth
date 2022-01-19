/*
  ==============================================================================

    StyleSheet.h
    Created: 15 Jan 2022 10:56:24pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


//namepace just to save time writing juce in front of many objs/classes etc 
namespace juce {

class CustomStyleSheet : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider); 

};

}
