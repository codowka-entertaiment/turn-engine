#include <iostream>

#include "SDL_mixer.h"

namespace TurnEngine {

    class Audio {
    public:
        static void init(int flags);

        static bool open(int freq = 44100, int channels = 2, int chunksize = 2048);

        static void close();
    };

    class Music {
    private:
        Mix_Music* music;
    public:
        Music(std::string filePath);
        ~Music();
        void play(int loops = -1);
        void pause();
        bool isPlaying();
    };

    class Sample {
    private:
        Mix_Chunk* sample;
        int channel;
    public:
        Sample(std::string filePath);
        ~Sample();
        void play(int loops = 0, int _channel = -1);
        void pause();
        bool isPlaying();
    };
}