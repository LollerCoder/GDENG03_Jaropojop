#pragma once

#include <xaudio2.h>

class SoundEngine
{
public:
    SoundEngine();
    ~SoundEngine();

    bool init();
    void Release();

    IXAudio2* getAudioEngine();

private:
    IXAudio2* m_xaudio;
    IXAudio2MasteringVoice* m_masterVoice;
};