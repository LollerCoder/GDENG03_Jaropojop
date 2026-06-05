#pragma once

#include <Windows.h>
#include <mmreg.h>

class WavLoader
{
public:
    WavLoader();
    ~WavLoader();

    bool load(const wchar_t* fileName);
    void release();

    WAVEFORMATEX* getFormat();
    BYTE* getAudioData();
    DWORD getAudioSize();

private:
    WAVEFORMATEX m_waveFormat;

    BYTE* m_audioData;
    DWORD m_audioSize;
};