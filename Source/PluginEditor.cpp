

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
    , effects (audioProcessor.apvts,"DISTENGAGE", "DISTMIX", "DELAYENGAGE", "DELAYTIME", "DELAYFEEDBACK", "DELAYMIX")

{
    
    juce::LookAndFeel::setDefaultLookAndFeel(&customStyleSheet);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 500);
    
    
    //sets labels for each section of synth (oscillators, filter and fx)
    
    
    
            
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    
    addAndMakeVisible(adsr);
    
    addAndMakeVisible(filter);
    
    addAndMakeVisible(modAdsr);
    
    addAndMakeVisible(effects);


}


TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);

}


//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
   
    g.fillAll (juce::Colour(0x1001312));
    
    g.setFont (20.0f);
    //g.drawText ("mono.", juce::Rectangle<int>(5, 10, 30, 40), juce::Justification::left);
    g.setColour(juce::Colours::whitesmoke);
    g.drawText("mono.", 20, 10, 60, 30, juce::Justification::left);

}

void TapSynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 0;
    //element padding is the space between elements in a section (e.g space between the 2 oscillators on the oscillator section)
    const auto elementPadding = 80;
    //Y2 is the spacing between row 1 (ADSR + osc) and row 2 (filter + fx) of synth
    const auto paddingY2 = 250;
    const auto width = 350;
    const auto height = 250;
    const auto sliderAndLabelHeight = 125;
    
    //x,y,width,height
    osc1.setBounds (paddingX, paddingY, width, sliderAndLabelHeight);
    osc2.setBounds (paddingX, elementPadding, width, sliderAndLabelHeight);
    adsr.setBounds (osc1.getRight(), paddingY, width, height);
    filter.setBounds(paddingX, paddingY2, width, sliderAndLabelHeight);
    
    //20 accounts for change in ADSR slider height
    modAdsr.setBounds(paddingX,(paddingY2 + elementPadding + 30), width, sliderAndLabelHeight);
    effects.setBounds(filter.getRight(), paddingY2, width, height);
    

    

}



