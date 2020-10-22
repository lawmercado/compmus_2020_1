#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "../read_write_wav.h"
using namespace std;

// first step: lets read a wav file
int main(int c, char** argv)
{
 
    float* audio_buffer;
    int buffer_len;
    int sample_rate = 44100;
    int n_channels;
    int current_position = 0;

    if (c!=2)
    {
        cout << "please, use a valid wav file name." << endl;
        return 0;
    }

    cout << "reading wav file..." << endl;
    n_channels = read_wave_file(argv[1], audio_buffer, &buffer_len, &sample_rate);

    cout << "alloc memory for mono audio channels..." << endl;
    float* right = (float*) malloc(buffer_len/2*sizeof(float));
    float* left = (float*) malloc(buffer_len/2*sizeof(float));

    cout << "copying stereo into two mono..." << endl;
    
    for (int i=0; i<buffer_len; i+=2)
    {
        left[current_position] = audio_buffer[i];
        right[current_position] = audio_buffer[i+1];
        current_position++;
    }

    write_wave_file("./example_left.wav", left, buffer_len/2, sample_rate);
    write_wave_file("./example_right.wav", right, buffer_len/2, sample_rate);

    cout << "done." << endl;
    return 0;
}

