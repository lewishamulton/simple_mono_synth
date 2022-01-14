
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessor::TapSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

TapSynthAudioProcessor::~TapSynthAudioProcessor()
{
}

//==============================================================================
const juce::String TapSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TapSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TapSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TapSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TapSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TapSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TapSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TapSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TapSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void TapSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TapSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i =0; i < synth.getNumVoices(); i++) {
        //cast synthesiser voices (JUCE class) as synth voices (own class)
        
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            //if cast successful must be a synthVoice pointer
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
        
    }
    
    //prepare the fx chain
    fxChain.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    
    
}

void TapSynthAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TapSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TapSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    for (int i = 0; i < synth.getNumVoices(); ++i) {
        
        //check if it is a synthVoice class
        if  (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            //Update below from ValueTree
            
            //Oscillators
            auto& oscWaveChoice1 = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& oscGain1 = *apvts.getRawParameterValue("OSC1GAIN");
            auto& oscPitch1 = *apvts.getRawParameterValue("OSC1PITCH");
            auto& fmDepth1 = *apvts.getRawParameterValue("OSC1FMFREQ");
            auto& fmFreq1 = *apvts.getRawParameterValue("OSC1FMDEPTH");
            
            auto& oscWaveChoice2 = *apvts.getRawParameterValue("OSC2WAVETYPE");
            auto& oscGain2 = *apvts.getRawParameterValue("OSC2GAIN");
            auto& oscPitch2 = *apvts.getRawParameterValue("OSC2PITCH");
            auto& fmDepth2 = *apvts.getRawParameterValue("OSC2FMFREQ");
            auto& fmFreq2 = *apvts.getRawParameterValue("OSC2FMDEPTH");
            
            //Amp ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            
            //Filter
            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& cutoff = *apvts.getRawParameterValue("FILTERFREQ");
            auto& resonance = *apvts.getRawParameterValue("FILTERRES");
            
            //Mod ADSR
            auto& modAttack = *apvts.getRawParameterValue("MODATTACK");
            auto& modDecay = *apvts.getRawParameterValue("MODDECAY");
            auto& modSustain = *apvts.getRawParameterValue("MODSUSTAIN");
            auto& modRelease = *apvts.getRawParameterValue("MODRELEASE");
            
            //Effects Params
            auto& distEngage = *apvts.getRawParameterValue("DISTENGAGE");
            auto& distMix = *apvts.getRawParameterValue("DISTMIX");
            
            auto& delayEngage = *apvts.getRawParameterValue("DELAYENGAGE");
            auto& delayTime = *apvts.getRawParameterValue("DELAYTIME");
            auto& delayFeedback = *apvts.getRawParameterValue("DELAYFEEDBACK");
            auto& delayMix = *apvts.getRawParameterValue("DELAYMIX");
            
            fxChain.updateParameters(distEngage, distMix, delayEngage, delayTime, delayFeedback, delayMix);
            
            voice->getOscillator1().setWaveType(oscWaveChoice1);
            voice->getOscillator1().setGainLevel(oscGain1);
            voice->getOscillator1().setPitch(oscPitch1);
            voice->getOscillator1().setFmParams(fmDepth1, fmFreq1);
            
            voice->getOscillator2().setWaveType(oscWaveChoice2);
            voice->getOscillator2().setGainLevel(oscGain2);
            voice->getOscillator2().setPitch(oscPitch2);
            voice->getOscillator2().setFmParams(fmDepth2, fmFreq2);
            
            //load shows it's an atomic float
            voice->updateAdsr (attack.load(), decay.load(), release.load(), sustain.load());
            voice->updateFilter (filterType.load(), cutoff.load(), resonance.load());
            voice->updateModAdsr(modAttack.load(), modDecay.load(), modRelease.load(), modSustain.load());
            voice->updateEffects(distEngage, distMix.load(), delayEngage, delayTime.load(), delayFeedback.load(), delayMix.load());
        }
        
            
    }
    
    //synth sound is created
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    //add the fx that are engaged
    fxChain.fxEngaged(buffer);

    

    
}

//==============================================================================
bool TapSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TapSynthAudioProcessor::createEditor()
{
    return new TapSynthAudioProcessorEditor (*this);
}

//==============================================================================
void TapSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void TapSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TapSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout TapSynthAudioProcessor::createParams()
{
        
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{"Sine","Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2", "Oscillator 2", juce::StringArray{"Sine","Saw", "Square"}, 0));
    
    //ADSR Select
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    //OSC Select, 0 is default option
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray {"Sine","Saw","Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2WAVETYPE", "Osc 2 Wave Type", juce::StringArray {"Sine","Saw","Square"}, 0));

    //OSC Gain 
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    
    //OSC Pitch
    params.push_back (std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator 1 Pitch", -48, 48, 0));
    params.push_back (std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator 2 Pitch", -48, 48, 0));
    
    //FM
    //skew factor is 0.3, logarithmic, slider focuses on lower end of freq/depth
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "Osc 1 FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01, 0.3 }, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "Osc 1 FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01, 0.3 }, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC2FMFREQ", "Osc 2 FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01, 0.3 }, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC2FMDEPTH", "Osc 2 FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01, 0.3 }, 0.0f));
    
    
    //Filter ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODATTACK", "Mod Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODDECAY", "Mod Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODSUSTAIN", "Mod Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODRELEASE", "Mod Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    //Filter
     params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray {"Low-Pass","Band-Pass","High-Pass"}, 0));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERFREQ", "Filter Freq", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f,0.6f }, 200.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f}, 1.0f));
    
    //Effects
    //skew factor on distortion threshold
    params.push_back (std::make_unique<juce::AudioParameterBool>("DISTENGAGE", "Distortion Engage", false));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DISTMIX", "Distortion Mix", juce::NormalisableRange<float> {0.0f, 1.0f, 0.001f}, 0.3f));
    params.push_back (std::make_unique<juce::AudioParameterBool>("DELAYENGAGE", "Delay Engage", false));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DELAYTIME", "Delay Time", juce::NormalisableRange<float> {0.1f, 3.0f, 0.01f}, 0.75f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DELAYFEEDBACK", "Delay Feedback", juce::NormalisableRange<float> {0.0f, 1.0f, 0.001f},0.6));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DELAYMIX", "Delay Mix", juce::NormalisableRange<float> {0.1f, 1.0f, 0.01f},1.0f));

    
    
    return { params.begin(), params.end() };
}
