#ifndef WAVETABLES_H
#define WAVETABLES_H 
#include "audio_setup.h" 
#include "mm_wavtab.h" 

#define WAVTABLE_LENGTH_SAMPLES 8192
#define SOUND_SAMPLE_LENGTH_SECONDS    10.
#define SAMPLE_TABLE_LENGTH_SEC 2 
#define WAVTABLE_NUM_PARTIALS   8

extern MMWavTab     WaveTable;
extern MMWavTab     soundSample;
extern MMWavTab     *theSound;
extern MMWavTab sampleTable;

void WaveTable_init(void);
void SoundSample_init(char *path);
void SampleTable_init(void);

#endif /* WAVETABLES_H */
