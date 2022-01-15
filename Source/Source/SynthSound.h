/*
  ==============================================================================

    SynthSound.h
    Created: 31 May 2021 4:37:27pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
    
public:
    //methods from abstract synthesiser sound 
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
    
    
}; 
