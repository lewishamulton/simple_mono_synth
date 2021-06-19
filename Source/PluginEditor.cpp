

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc (audioProcessor.apvts, "OSC1WAVETYPE","OSC1FMFREQ","OSC1FMDEPTH"), adsr (audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
            
    //make oscillator visible in GUI
    addAndMakeVisible(osc);
    
    //make ADSR visible in GUI
    addAndMakeVisible(adsr);
}


TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
    
}


//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
   

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void TapSynthAudioProcessorEditor::resized()
{
    //x,y,width,height
    osc.setBounds(10, 10, 180, 200);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}



