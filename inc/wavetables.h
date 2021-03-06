#ifndef WAVETABLES_H
#define WAVETABLES_H 
#include "audio_setup.h" 
#include "mm_wavtab.h" 

#define WAVTABLE_LENGTH_SAMPLES 8192
#define SOUND_SAMPLE_LENGTH_SECONDS    10.
#define SAMPLE_TABLE_LENGTH_SEC 30 
#define WAVTABLE_NUM_PARTIALS   8
#define NUM_SAMPLE_TABLES       2 

typedef struct __WavTabAreaPair {
    MMWavTab *wavtab;
    MMSample *area;
} WavTabAreaPair;

extern MMWavTab     WaveTable;
extern MMWavTab     soundSample;
extern MMWavTab     sampleTable[];
extern size_t       soundSampleMaxLength;
extern WavTabAreaPair theSound;
extern WavTabAreaPair recordingSound;
extern MMSample     *hannWindowTable;
extern size_t       hannWindowTableLength;
extern size_t       zeroxSearchMaxLength;

void WaveTable_init(void);
void SoundSample_init(char *path);
void SampleTable_init(void);
void HannWindowTable_init(MMSample len_sec);
void ZeroxSearch_init(MMSample len_sec);

#endif /* WAVETABLES_H */
