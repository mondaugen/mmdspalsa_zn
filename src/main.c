#include "err.h" 
#include "audio_setup.h"
#include "midi_setup.h" 
#include "wavetables.h" 
#include "signal_chain.h" 
#include <unistd.h> 

void play_note_rate(int midinote, float rate)
{
    MMTrapEnvedSamplePlayer_noteOn_Rate(
        &spsps[0],
        midinote,
        1,
        MMInterpMethod_CUBIC,
        0,
        1.,
        4.,
        10.,
        theSound.wavtab,
        1,
        rate);
}

void play_note(int midinote)
{
    MMTrapEnvedSamplePlayer_noteOn(
        &spsps[0],
        midinote,
        1,
        MMInterpMethod_CUBIC,
        0,
        1.,
        4.,
        10.,
        theSound.wavtab,
        1);
}

int main (int argc, char **argv)
{
    if ((argc != 3) && (argc != 4)) {
        fprintf(stderr,
                "Arguments are %s audio-device midi-input-port\n",argv[0]);
        return(-1);
    }
    if (audio_setup(argv[1])) {
        THROW_ERR("Error setting up audio.");
    }
    if (midi_setup(argv[2])) {
        THROW_ERR("Error setting up MIDI.");
    }
    if (argc == 3) {
        SampleTable_init();
    }
    if (argc == 4) {
        SoundSample_init(argv[3]);
    }
    sc_presets_init("/tmp/zn_presets.dat");
    signal_chain_setup();
//    poly_management_setup();
    synth_control_setup();
    scheduler_setup();
    audio_start();
    while(1) {
    }
    return(0);
}
