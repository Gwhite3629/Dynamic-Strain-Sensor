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