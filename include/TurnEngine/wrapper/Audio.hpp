#include <iostream>

#include "SDL_mixer.h"

namespace TurnEngine {

    /// @brief
    /// That class wraps Mix_Music
    class Music {
    private:
        Mix_Music *music;
    public:
        /// @brief
        /// the constructor
        /// @param std::string filePath
        Music(std::string filePath);

        /// @brief
        /// the destructor
        ~Music();

        /// @brief
        /// That method starts playing music
        /// @param int loops
        void play(int loops = -1);

        /// @brief
        /// That method pauses music
        void pause();

        /// @brief
        /// That method resumes music
        void resume();

        /// @brief
        /// That method rewinds music
        void rewind();

        /// @brief
        /// That method checks if music is playing
        /// @return
        /// Boolean `true` if music is playing, else `false`
        bool isPlaying();

        /// @brief
        /// That method returns SDL_mixer Mix_Music pointer on structure
        /// @return
        /// pointer on Mix_Music structure
        Mix_Music* native_handle();
    };

    /// @brief
    /// That class wraps Mix_Chunk
    class Sample {
    private:
        Mix_Chunk *sample;
        int channel;
    public:

        /// @brief
        /// the constructor
        /// @param std::string filePath
        Sample(std::string filePath);

        /// @brief
        /// the destructor
        ~Sample();

        /// @brief
        /// That method starts playing sample
        void play(int loops = 0, int _channel = -1);

        /// @brief
        /// That method pauses sample
        void pause();

        /// @brief
        /// That method resumes sample
        void resume();

        /// @brief
        /// That method checks if sample is playing
        /// @return
        /// Boolean `true` if sample is playing, else `false`
        bool isPlaying();
    };

    /// @brief
    /// That class stands for initialization and configuring audio system
    class Audio {
    public:
        /// @brief
        /// That static method initializes SDL_mixer library
        static void init(int flags);

        /// @brief
        /// That static method opens audio device
        /// @return
        /// Boolean `true` if audio device opened successfully, else `false`
        static bool open(int freq = 44100, int channels = 2, int chunksize = 2048);

        /// @brief
        /// That static method sets sample volume
        static void setSampleVolume(int volume);

        /// @brief
        /// That static method gets sample volume
        /// @return
        /// Volume percentage (int)
        static int getSampleVolume();

        /// @brief
        /// That static method sets music volume
        static void setMusicVolume(int volume);

        /// @brief
        /// That static method gets music volume
        /// @return
        /// Volume percentage (int)
        static int getMusicVolume(Music* music);

        /// @brief
        /// That static method closes opened audio device
        static void close();
    };
}