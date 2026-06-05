#pragma once

#include <xaudio2.h>

#include "WavLoader.h"

class Sound
{
public:
    Sound();
    ~Sound();

    bool load(IXAudio2* audioEngine, const wchar_t* fileName);

    void play();
    void stop();
    void release();

private:
    WavLoader m_wavLoader;

    IXAudio2SourceVoice* m_sourceVoice;

    XAUDIO2_BUFFER m_buffer;
};