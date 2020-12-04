#include "Config.h"
#include "SoundPlayer.h"
#include "Sound.h"

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

void SoundPlayer::playWAV() {
  esp_err_t err = ESP_OK;
  i2s_driver_uninstall(SPEAKER_I2S_NUMBER);
  i2s_config_t i2s_config = {
    .mode                 = (i2s_mode_t)(I2S_MODE_MASTER),
    .sample_rate          = 16000 ,
    .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format       = I2S_CHANNEL_FMT_ALL_RIGHT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count        = 6,
    .dma_buf_len          = 60,
    .use_apll             = false,
    .tx_desc_auto_clear   = true,
    .fixed_mclk           = 0
  };

  i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);

  err += i2s_driver_install(SPEAKER_I2S_NUMBER, &i2s_config, 0, NULL);

  i2s_pin_config_t tx_pin_config = {
    .bck_io_num           = CONFIG_I2S_BCK_PIN,
    .ws_io_num            = CONFIG_I2S_LRCK_PIN,
    .data_out_num         = CONFIG_I2S_DATA_PIN,
    .data_in_num          = CONFIG_I2S_DATA_IN_PIN,
  };
  err += i2s_set_pin(SPEAKER_I2S_NUMBER, &tx_pin_config);
  err += i2s_set_clk(SPEAKER_I2S_NUMBER, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

  i2s_zero_dma_buffer(SPEAKER_I2S_NUMBER);

  size_t bytes_written;
  i2s_write(SPEAKER_I2S_NUMBER, wav, sizeof(wav), &bytes_written, portMAX_DELAY);
  i2s_zero_dma_buffer(SPEAKER_I2S_NUMBER);
}