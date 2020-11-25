#include "Config.h"
#include "SoundPlayer.h"

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

// MP3再生
void SoundPlayer::playMP3(char *filename){
  file = new AudioFileSourceSD(filename);
  id3 = new AudioFileSourceID3(file);
  #if DEVICE == M5STACKBASIC
  out = new AudioOutputI2S(0, 1);
  #elif DEVICE == M5STACKCORE2
  out = new AudioOutputI2S(0, 0);
  out->SetPinout(12, 0, 2);
  #endif
  out->SetOutputModeMono(true);
  out->SetGain(0.7);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  while (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
    }
  }
}