# Concepts:

## Moving average:

The moving average is intended to maintain constant measurement without varying the sample rate on peaks. The moving average acquires data and averages from the newest data point to some time in the past. The moving average is intended to give a good idea of strain magnitude over a time frame, and is thus good for trends and quite bad for spikes in activity.

## Time stamps:

Time stamps are relative to the beginning of program execution. Time is in format of Days-Minutes-Seconds and the calendar date of program execution is recorded.  

## Measurements: 
  
Measurements are constantly taken. The time domain magnitude of the signal is the most important and is measured with a rolling average. Several pre-defined thresholds are available to determine when measurements are saved. Temperature is measured through a thermocouple.

Measurements include:
- Time domain
- FFT
- Peak magnitude
- Time average
- Largest frequency component

## Data:

Measurements are saved in specific cases.  
### 1. **Large variation of moving average**

Variations in the moving average mean the average has met one of several threshold values that are pre-defined empirically. These values determine when vibrations of noticeable strength are occuring.  
    **Data recorded:**
- FFT
- Average temperature
- Peak magnitude
- Average magnitude

### 2. **Fixed increment in time**

Data should be saved in cases of obvious vibration, but general behaviour is also important. Data is saved sporadically to ensure data is plentiful.
    **Data recorded:**
- FFT
- Average temperature
- Peak magnitude
- Average magnitude

### 3. **Large spikes:**

Data is recorded when large spikes in magnitude are detected. These are expected to be frequent and will have thresholds associated with them. This method is to ensure that the rolling average doesn't miss any important fluctuations.
    **Data recorded:**
- Average temperature
- Peak magnitude
- Average magnitude

# Code:

## main.c:

The purpose of the main function is to have an easy to access initialization to the program. In this file the serial device will be registered and configured. The runtime environment will also be initialized and given appropriate arguments.
## runtime.c:

The runtime environment in this function is responsible for dynamically acquiring and moving data.
### TODO:

#### *Config interpretation:*

Config file will include:
- Moving average thresholds
- Peak value thresholds
- Generic data gathering rate  