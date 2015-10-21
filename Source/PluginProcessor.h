/*
 ==============================================================================
 
 This file was auto-generated by the Introjucer!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
 */
class HierarchicalShiftAudioProcessor  : public AudioProcessor,
public ChangeBroadcaster,
public AudioSourcePlayer
{
public:
    //==============================================================================
    HierarchicalShiftAudioProcessor();
    ~HierarchicalShiftAudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override{return true;};
    
    //==============================================================================
    const String getName() const override;
    
    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;
    
    const String getParameterName (int index) override;
    const String getParameterText (int index) override;
    
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    typedef enum{
        STOPPED=0,
        PLAYING,
        RECORDING
    }RecordState;
    RecordState recordState;
    
    
    void recordNext(AudioSampleBuffer& b);
    void playNext(AudioSampleBuffer& b);
    int64 recordHead;
    int64 playHead;
    void prepareRecordBuffer();
    
    int64 loopLength;
    
    AudioSampleBuffer localBuffer;
    int64 minBufAhead ;
    double recordBPM;
    
    //    PositionableAudioSource buf;
    double sampleToBeat(int64 h,bool originBPM = false);
    int64 BeatToSample(double b,bool originBPM = false);
    int64 getBeatsMappedIndex(double f);
    Array<int> longestBeatMap;
    
    
    
    void setNumBeats(int num);
    void generateRandomBeatMap();
    void generateLinearBeatMap(bool reversed = false);
    Array<int> beatMap;
    

    
    void willRecQuantized(bool b);
    
    void setImmediatePlaying(bool b);
    void setImmediateRecording(bool b);
    
    void updatePosition();
    
    void checkBufferLength();
    juce::AudioPlayHead::CurrentPositionInfo position;
    int64 startRecordPosition;
    float localBpm;
    int64 localLoopBeats;
    bool hasTransportInfo;
    
    
private:
    
    
    typedef enum{
        NONE=0,
        REC,
        STOPREC
        
    } QuantizedCommand;
    
    void doQuantizedCommand();
    QuantizedCommand qCommand;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HierarchicalShiftAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
