#include "Sound.h"

#include <cstring>

Sound::Sound()
{
    m_sourceVoice = nullptr;

    ZeroMemory(&m_buffer, sizeof(XAUDIO2_BUFFER));
}

Sound::~Sound()
{
    release();
}

bool Sound::load(IXAudio2* audioEngine, const wchar_t* fileName)
{
    OutputDebugStringA("INSIDE WAV\n");
    if (!m_wavLoader.load(fileName))
        return false;

    HRESULT hr = audioEngine->CreateSourceVoice(
        &m_sourceVoice,
        m_wavLoader.getFormat()
    );

    if (FAILED(hr))
        return false;

    m_buffer.AudioBytes = m_wavLoader.getAudioSize();
    m_buffer.pAudioData = m_wavLoader.getAudioData();
    m_buffer.Flags = XAUDIO2_END_OF_STREAM;

    hr = m_sourceVoice->SubmitSourceBuffer(&m_buffer);

    if (FAILED(hr))
        return false;

    return true;
}

void Sound::play()
{
    if (m_sourceVoice)
    {
        m_sourceVoice->Start();
    }
}

void Sound::stop()
{
    if (m_sourceVoice)
    {
        m_sourceVoice->Stop();
    }
}

void Sound::release()
{
    if (m_sourceVoice)
    {
        m_sourceVoice->DestroyVoice();
        m_sourceVoice = nullptr;
    }

    m_wavLoader.release();
}