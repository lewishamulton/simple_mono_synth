

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , osc1 (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1GAIN", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH")
    , osc2 (audioProcessor.apvts, "OSC2WAVETYPE", "OSC2GAIN", "OSC2PITCH", "OSC2FMFREQ", "OSC2FMDEPTH")
    , adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filter (audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
    , modAdsr ("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 800);
    
            
    //make oscillator visible in GUI
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    
    //make ADSR visible in GUI
    addAndMakeVisible(adsr);
    
    //make filter visible in GUI
    addAndMakeVisible(filter);
    
    //make mod ADSR in GUI
    addAndMakeVisible(modAdsr);
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
    const auto paddingY3 = 400;
    const auto width = 400;
    const auto height = 200;
    
    //x,y,width,height
    osc1.setBounds (paddingX, paddingY, width, height);
    osc2.setBounds (paddingX, paddingY3, width, height);
    adsr.setBounds (osc1.getRight(), paddingY, width, height);
    filter.setBounds(paddingX, paddingY2, width, height);
    modAdsr.setBounds(filter.getRight(), paddingY2, width, height);
    

}



