#include "audio_setup.h" 
#include "midi_setup.h" 
#include "signal_chain.h" 
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include "synth_control.h" 

#define NCHANS 2 
#define SAMPLE_RATE 44100 

int audio_ready = 0;

/* Pass in the name of the audio device as a string */
int audio_setup(void *data)
{
    audio_hw_setup_t ahs;
    ahs.device = (char*)data;       /* playback device */
    ahs.format = SND_PCM_FORMAT_S16;/* sample format */
    ahs.rate   = SAMPLE_RATE;	    /* stream rate */
    ahs.channels = NCHANS;		    /* count of channels */
    ahs.buffer_time = 50000;	    /* ring buffer length in us */
    ahs.period_time = 5000;	    /* period time in us */
    ahs.verbose = 1;				/* verbose flag */
    ahs.resample = 1;				/* enable alsa-lib resampling */
    ahs.period_event = 0;	        /* produce poll event after each period */
    ahs.method = "async";           /* the transfer method: "async" */
    return audio_hw_setup(&ahs);
}

void audio_hw_io(audio_hw_io_t *params)
{
    /* Process MIDI once every audioblock */
    midi_hw_process_input(NULL);
    /* Increment scheduler and do pending events */
    scheduler_incTimeAndDoEvents();
    /* Process audio */
    MMSigProc_tick(&sigChain);
    int n, c;
    for (n = 0; n < params->length; n++) {
        for (c = 0; c < params->nchans_out; c++) {
//            if (c == 0) {
                params->out[n*params->nchans_out + c] =
                    outBus->data[outBus->channels*n] *  AUDIO_HW_SAMPLE_T_MAX;
                /*
            } else {
                params->out[n*params->nchans_out + c] = 0;
            }
            */
        }
    }
     /* Because ALSA is not yet set up for audio input, we read from stdin.
     * */
    int16_t fixedPointData[params->length*params->nchans_in];
    fread(fixedPointData,sizeof(int16_t),
            params->length*params->nchans_in,stdin);
    /* convert to type MMSample */
    for (n = 0; n < params->length; n++) {
        for (c = 0; c < params->nchans_out; c++) {
            inBus->data[n*params->nchans_out + c] = 
                ((MMSample)fixedPointData[n*params->nchans_out + c])
                    /AUDIO_HW_SAMPLE_T_MAX;
            /* Pass through */
            /*
            params->out[n*params->nchans_out + c] 
                += fixedPointData[n*params->nchans_out + c] * dryGain / 127;
                */
            params->out[n*params->nchans_out + c] 
                += ((int16_t)((((MMSample)fixedPointData[n*params->nchans_out + c])
                        /AUDIO_HW_SAMPLE_T_MAX) * AUDIO_HW_SAMPLE_T_MAX))
                            * dryGain / 127;
        }
    }
}
