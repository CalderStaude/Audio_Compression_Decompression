#include <stdio.h>

#define DEBUG 1
#define debug_print(fmt, ...)                    \
    do                                           \
    {                                            \
        if (DEBUG)                               \
            fprintf(stderr, fmt, ##__VA_ARGS__); \
    }   while (0)

//Convers decimal to bin
void convertToBinary(unsigned int n)
{
    if (n / 2 != 0) {
        convertToBinary(n / 2);
    }
    printf("%d", n % 2);
}

int signum(int sample)
{
    if (sample < 0)
    {
        //debug_print("\nNegative\n");
        return (0); /* sign is ’0’ for negative samples */
    }
    else
    {
        //debug_print("\nPositive\n");
        return (1); /* sign is ’1’ for positive samples */
    }
}

int magnitude(int sample)
{   
    if (sample < 0)
    {
        sample = -sample;
    }
    //debug_print("Magnatude: %d", sample);
    return (sample);
}

int codeword_compression(unsigned int sample_magnitude, int sign)
{
    int chord, step;
    int codeword_tmp;

    if (sample_magnitude & (1 << 12))
    {
        chord = 0x7;
        step = (sample_magnitude >> 8) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 11))
    {
        chord = 0x6;
        step = (sample_magnitude >> 7) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 10))
    {
        chord = 0x5;
        step = (sample_magnitude >> 6) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("chord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 9))
    {
        chord = 0x4;
        step = (sample_magnitude >> 5) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return ((int)codeword_tmp);
    }
    if (sample_magnitude & (1 << 8))
    {
        chord = 0x3;
        step = (sample_magnitude >> 4) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 7))
    {
        chord = 0x2;
        step = (sample_magnitude >> 3) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 6))
    {
        chord = 0x1;
        step = (sample_magnitude >> 2) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 5))
    {
        chord = 0x0;
        step = (sample_magnitude >> 1) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
}

int codeword_decompression(int codeWord)
{
    int chord, step;
    int word;
 
    chord = (codeWord >> 4) & 7;
    
    debug_print("CodeWord: %d | ", codeWord);
    if(DEBUG) convertToBinary(codeWord);
    debug_print("\nSign: %d | ", codeWord >> 7);
    if(DEBUG) convertToBinary(codeWord >> 7);
    debug_print("\nChord: %d | ", chord);
    if(DEBUG) convertToBinary(chord);
    debug_print("\nStep: %d | ", codeWord & 0xF);
    if(DEBUG) convertToBinary(codeWord & 0xF);
    debug_print("\n<============== Checking word operation ==============>");
    if(DEBUG)
    {
        int Pos_Neg_Shift = (codeWord << 6);
        int Pos_Neg_Mask = Pos_Neg_Shift & 8192;
        int Word_Mask = (codeWord & 0xF);
        int shift_val = ((codeWord >> 4) & 7);
        int Word_Shift =  ((codeWord & 0xF) << ((codeWord >> 4) & 7));
        int word1 = (codeWord << 12) & 12 ^ ((codeWord & 0xF) << ((codeWord >> 4) & 7));

        debug_print("\n Pos/Neg value: %d | ", Pos_Neg_Shift);
        convertToBinary(Pos_Neg_Shift);
        debug_print("\n Pos/Neg value: %d | ", Pos_Neg_Mask);
        convertToBinary(Pos_Neg_Mask);
        debug_print("\n Pos/Neg value: %d | ", Word_Mask);
        convertToBinary(Word_Mask);
        debug_print("\n Pos/Neg value: %d | ", shift_val);
        convertToBinary(shift_val);
        debug_print("\n Pos/Neg value: %d | ", Word_Shift);
        convertToBinary(Word_Shift);
        debug_print("\n Pos/Neg value: %d | ", word1);
        convertToBinary(word1);
    }

    //     Sign                                                     
    word = (codeWord << 12) & 12 ^ ((codeWord & 0xF) << ((codeWord >> 4) & 7));

/*
    if(chord & 7)
    {

        return();
    }

    if (sample_magnitude & (1 << 12))
    {
        chord = 0x7;
        step = (sample_magnitude >> 8) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 11))
    {
        chord = 0x6;
        step = (sample_magnitude >> 7) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 10))
    {
        chord = 0x5;
        step = (sample_magnitude >> 6) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("chord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 9))
    {
        chord = 0x4;
        step = (sample_magnitude >> 5) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return ((int)codeword_tmp);
    }
    if (sample_magnitude & (1 << 8))
    {
        chord = 0x3;
        step = (sample_magnitude >> 4) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 7))
    {
        chord = 0x2;
        step = (sample_magnitude >> 3) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 6))
    {
        chord = 0x1;
        step = (sample_magnitude >> 2) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    if (sample_magnitude & (1 << 5))
    {
        chord = 0x0;
        step = (sample_magnitude >> 1) & 0xF;
        codeword_tmp = (sign << 7) ^ (chord << 4) ^ step;
        debug_print("\nchord: %d, step: %d, codeword_tmp: %d\n", chord, step, codeword_tmp);
        return (codeword_tmp);
    }
    */
   return 0;
}

int Test(int sample)
{
    printf("<=====================================================>");
    /*
    printf("Intiger being evaluated: %d\n", sample);

        //Get sign
        if (signum(sample) == 0)
        {
            printf("Sample is negative %d", signum(sample));
        }
        else if (signum(sample) == 1)
        {
            printf("Sample is positive %d", signum(sample));
        }
        else
        {
            printf("Failed to print sample");
        }

        //Get Magnitude
        printf("\nThe Magnatude of Sample is: %d\n", magnitude(sample));
    */
    int codeword = codeword_compression(magnitude(sample), signum(sample));

    printf("RESULTS: \n Input: %d | ", sample);
    convertToBinary(sample);
    printf("\nOUTPUT: %d | ", codeword);
    convertToBinary(codeword);

    return 0;
}

int main()
{
    int sample = 181;

   //int codeword = codeword_compression(magnitude(sample), signum(sample));

    int codeword = 181;

    codeword_decompression(codeword);

    //Test(553);
    //Test(181);
    //Test(-1910);

    return 0;
}