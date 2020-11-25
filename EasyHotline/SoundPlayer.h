#pragma once
#include "Config.h"
#include <AudioFileSourceSD.h>
#include <AudioFileSourceID3.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

class SoundPlayer{
private:

public:
    static void playMP3(char *filename);
};