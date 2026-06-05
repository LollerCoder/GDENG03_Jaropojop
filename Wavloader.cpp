#include "WavLoader.h"

#include <fstream>
#include <cstring>
#include <cstdio>

#pragma pack(push, 1)

struct RIFF_HEADER
{
    char chunkId[4];
    DWORD chunkSize;
    char format[4];
};

struct CHUNK_HEADER
{
    char chunkId[4];
    DWORD chunkSize;
};

struct FMT_CHUNK
{
    WORD audioFormat;
    WORD numChannels;
    DWORD sampleRate;
    DWORD byteRate;
    WORD blockAlign;
    WORD bitsPerSample;
};

#pragma pack(pop)

static void DebugLog(const char* msg)
{
    OutputDebugStringA(msg);
    OutputDebugStringA("\n");
}

WavLoader::WavLoader()
{
    ZeroMemory(&m_waveFormat, sizeof(WAVEFORMATEX));
    m_audioData = nullptr;
    m_audioSize = 0;
}

WavLoader::~WavLoader()
{
    release();
}

bool WavLoader::load(const wchar_t* fileName)
{
    release();

    DebugLog("BEFORE LOAD");

    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        DebugLog("FAILED TO OPEN FILE");
        return false;
    }

    RIFF_HEADER riffHeader{};
    if (!file.read(reinterpret_cast<char*>(&riffHeader), sizeof(RIFF_HEADER)))
    {
        DebugLog("FAILED TO READ RIFF");
        return false;
    }

    if (memcmp(riffHeader.chunkId, "RIFF", 4) != 0 ||
        memcmp(riffHeader.format, "WAVE", 4) != 0)
    {
        DebugLog("INVALID RIFF/WAVE HEADER");
        return false;
    }

    DebugLog("VALID WAV HEADER");

    bool fmtFound = false;
    bool dataFound = false;

    while (true)
    {
        CHUNK_HEADER chunkHeader{};

        if (!file.read(reinterpret_cast<char*>(&chunkHeader), sizeof(CHUNK_HEADER)))
        {
            DebugLog("STOP: FAILED CHUNK READ");
            break;
        }

        char msg[128];
        sprintf_s(msg, "CHUNK: %.4s SIZE: %u", chunkHeader.chunkId, chunkHeader.chunkSize);
        DebugLog(msg);

        if (chunkHeader.chunkSize > 50 * 1024 * 1024)
        {
            DebugLog("INVALID CHUNK SIZE (TOO LARGE)");
            return false;
        }

        if (memcmp(chunkHeader.chunkId, "fmt ", 4) == 0)
        {
            FMT_CHUNK fmt{};

            if (!file.read(reinterpret_cast<char*>(&fmt), sizeof(FMT_CHUNK)))
            {
                DebugLog("FAILED TO READ FMT");
                return false;
            }

            m_waveFormat.wFormatTag = fmt.audioFormat;
            m_waveFormat.nChannels = fmt.numChannels;
            m_waveFormat.nSamplesPerSec = fmt.sampleRate;
            m_waveFormat.nAvgBytesPerSec = fmt.byteRate;
            m_waveFormat.nBlockAlign = fmt.blockAlign;
            m_waveFormat.wBitsPerSample = fmt.bitsPerSample;
            m_waveFormat.cbSize = 0;

            if (chunkHeader.chunkSize > sizeof(FMT_CHUNK))
                file.seekg(chunkHeader.chunkSize - sizeof(FMT_CHUNK), std::ios::cur);

            fmtFound = true;
        }
        else if (memcmp(chunkHeader.chunkId, "data", 4) == 0)
        {
            m_audioSize = chunkHeader.chunkSize;

            if (m_audioSize == 0 || m_audioSize > 50 * 1024 * 1024)
            {
                DebugLog("INVALID AUDIO SIZE");
                return false;
            }

            m_audioData = new BYTE[m_audioSize];

            if (!file.read(reinterpret_cast<char*>(m_audioData), m_audioSize))
            {
                DebugLog("FAILED TO READ AUDIO DATA");
                return false;
            }

            DebugLog("DATA LOADED SUCCESSFULLY");

            dataFound = true;
        }
        else
        {
            file.seekg(chunkHeader.chunkSize, std::ios::cur);
        }

        if (chunkHeader.chunkSize % 2 == 1)
            file.seekg(1, std::ios::cur);

        if (fmtFound && dataFound)
            break;
    }

    if (!fmtFound) DebugLog("MISSING FMT CHUNK");
    if (!dataFound) DebugLog("MISSING DATA CHUNK");

    return fmtFound && dataFound;
}

void WavLoader::release()
{
    if (m_audioData)
    {
        delete[] m_audioData;
        m_audioData = nullptr;
    }

    m_audioSize = 0;
}

WAVEFORMATEX* WavLoader::getFormat()
{
    return &m_waveFormat;
}

BYTE* WavLoader::getAudioData()
{
    return m_audioData;
}

DWORD WavLoader::getAudioSize()
{
    return m_audioSize;
}