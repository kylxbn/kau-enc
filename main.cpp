#include "kiss_fft.h"
#include "kiss_fftr.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#define numberOfSamples 1024

using namespace std;



int main(void)
{
    cout << "Number of waves per frame: ";
    int numwaves;
    cin >> numwaves;
    short waveampli[numwaves];
    short wavefreq[numwaves];
    struct KissFFT
    {
        kiss_fftr_cfg forwardConfig;
        kiss_fft_cpx* spectrum;
        int numSamples;
        int spectrumSize;
    } fft;
    static double dospi = 3.14159265*2;
    static double sampleRate = 44100;
    static double wantedHz = 0;
    int j,i,k;
    float dataStream[numberOfSamples];
    float mags[numberOfSamples];
    FILE * pFile;
    FILE * pIn;
    FILE * pOut;
    //Frequency to achive
    wantedHz = 1000;
    fft.forwardConfig = kiss_fftr_alloc(numberOfSamples,0,NULL,NULL);
    fft.spectrum = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx) * numberOfSamples);
    fft.numSamples = numberOfSamples;
    fft.spectrumSize = numberOfSamples/2+1;
    pFile = fopen ("c:\\testfft.txt","w");
    pIn = fopen("C:\\aud.raw", "rb");
    pOut = fopen("C:\\aud.kau", "wb");
    fwrite(&numwaves, sizeof(numwaves), 1, pOut);
    short dat;
    bool cont;
    cont = true;
    do
    {
    //filling the buffer data with a senoidal wave of frequency -wantedHz- and printing to testing it
        for (j = 0; j < 1024; j++)
        {
            fread(&dat, sizeof(dat), 1, pIn);
            dataStream[j] = dat;
            //fprintf(pFile, "%10d\n", dat);
        }
        //spectrum
        kiss_fftr(fft.forwardConfig, dataStream, fft.spectrum);
        for(i=0; i<fft.spectrumSize; i++)
        {
            mags[i] = hypotf(fft.spectrum[i].r,fft.spectrum[i].i);
        }
        int max_ampli;
        short max_ampli_write;
        int max_ampli_below;
        max_ampli_below = 10000000;
        unsigned short freq;
        for (int i=0; i<numwaves; i++)
        {
            max_ampli = 0;
            for (j=0; j<numberOfSamples; j++)
            {
                if ((mags[j] > max_ampli) && (mags[j]<max_ampli_below))
                {
                    max_ampli = mags[j];
                    freq = j*(int)sampleRate/numberOfSamples;
                }
            }

            max_ampli_below = max_ampli-10;
            max_ampli_write = max_ampli / 310;
            fwrite(&freq, sizeof(freq), 1, pOut);
            fwrite(&max_ampli_write, sizeof(max_ampli_write), 1, pOut);
        }
    } while (!feof(pIn));
    //end
    //free and close
    fclose (pFile);
    fclose(pOut);
    fclose (pIn);
    kiss_fft_cleanup();
    cout << "Work is done.";
    return 0;
}
