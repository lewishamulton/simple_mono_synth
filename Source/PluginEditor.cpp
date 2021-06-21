

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , osc (audioProcessor.apvts, "OSC1WAVETYPE","OSC1FMFREQ","OSC1FMDEPTH")
    , adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filter (audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (620, 500);
            
    //make oscillator visible in GUI
    addAndMakeVisible(osc);
    
    //make ADSR visible in GUI
    addAndMakeVisible(adsr);
    
    //make filter visible in GUI
    addAndMakeVisible(filter); 
}


TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
    
}


//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
   
    g.fillAll (juce::Colours::black);

}

void TapSynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 35;
    //Y2 set below osc, y coordinate set at 35 with height of 200 then extra 35 padding of pixels hence 270
    const auto paddingY2 = 235;
    
    //x,y,width,height
    osc.setBounds (paddingX, paddingY, 300, 200);
    adsr.setBounds (osc.getRight(), paddingY, 300, 200);
    filter.setBounds(paddingX, paddingY2, 300, 200);

}



