#include "TurnEngine/wrapper/Audio.hpp"

namespace TurnEngine {
    Music::Music(std::string filePath) {
        music = Mix_LoadMUS(filePath.c_str());
    }

    void Music::play(int loops) {
        Mix_PlayMusic(music, loops);
    }

    void Music::pause() {
        Mix_PauseMusic();
    }

    bool Music::isPlaying() {
        return Mix_PlayingMusic();
    }

    void Music::resume() {
        Mix_ResumeMusic();
    }

    void Music::rewind() {
        Mix_RewindMusic();
    }

    Music::~Music() {
        Mix_FreeMusic(music);
    }

    Mix_Music *Music::native_handle() {
        return music;
    }

    Sample::Sample(std::string filePath) {
        sample = Mix_LoadWAV(filePath.c_str());
    }

    void Sample::play(int loops, int _channel) {
        channel = Mix_PlayChannel(_channel, sample, loops);
    }

    void Sample::pause() {
        Mix_Pause(channel);
    }

    void Sample::resume() {
        Mix_Resume(channel);
    }

    bool Sample::isPlaying() {
        return Mix_Playing(channel);
    }

    Sample::~Sample() {
        Mix_FreeChunk(sample);
    }

    void Audio::init(int flags) {
        Mix_Init(flags);
    }

    bool Audio::open(int freq, int channels, int chunksize) {
        return Mix_OpenAudio(freq, MIX_DEFAULT_FORMAT, channels, chunksize) == 0;
    }

    void Audio::setSampleVolume(int volume) {
        Mix_MasterVolume((int) (volume / 100.0 * MIX_MAX_VOLUME));
    }

    int Audio::getSampleVolume() {
        return (int) (Mix_MasterVolume(-1) * 100.0 / MIX_MAX_VOLUME);
    }

    void Audio::setMusicVolume(int volume) {
        Mix_VolumeMusic((int) (volume / 100.0 * MIX_MAX_VOLUME));
    }

    int Audio::getMusicVolume(Music* music) {
        return (int) (Mix_GetMusicVolume(music->native_handle()) * 100.0 / MIX_MAX_VOLUME);
    }

    void Audio::close() {
        Mix_CloseAudio();
    }
}