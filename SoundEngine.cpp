#include "SoundEngine.h"

#include <Windows.h>
#include <combaseapi.h>
#include <xaudio2.h>

SoundEngine::SoundEngine()
{
    m_xaudio = nullptr;
    m_masterVoice = nullptr;
}

SoundEngine::~SoundEngine()
{
}

bool SoundEngine::init()
{
    HRESULT hr;

    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        return false;
    }

    hr = XAudio2Create(&m_xaudio, 0);
    if (FAILED(hr))
    {
        return false;
    }

    hr = m_xaudio->CreateMasteringVoice(&m_masterVoice);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

void SoundEngine::Release()
{
    if (m_masterVoice)
    {
        m_masterVoice->DestroyVoice();
        m_masterVoice = nullptr;
    }

    if (m_xaudio)
    {
        m_xaudio->Release();
        m_xaudio = nullptr;
    }

    CoUninitialize();
}

IXAudio2* SoundEngine::getAudioEngine()
{
    return m_xaudio;
}