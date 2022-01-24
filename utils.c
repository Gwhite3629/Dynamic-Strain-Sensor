//  Utility Functions
//  Dynamic Strain Sensor
//  Grady White
//  1/7/22

float moving_average(float *window, int windowSize, float *sum, int pos, float next)
{
    // Update sum
    *sum = *sum - window[pos] + next;
    // Update window
    window[pos] = next;
    // Average
    return *sum/windowSize;
}

float ReverseFloat(const float inFloat)
{
   float retVal;
   char *floatToConvert = ( char* ) & inFloat;
   char *returnFloat = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnFloat[0] = floatToConvert[3];
   returnFloat[1] = floatToConvert[2];
   returnFloat[2] = floatToConvert[1];
   returnFloat[3] = floatToConvert[0];

   return retVal;
}