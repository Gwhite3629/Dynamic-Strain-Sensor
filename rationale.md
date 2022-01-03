# Concepts:

## Hysteresis:

Measurements are taken at a fixed rate.  
When a measurement goes above the threshold the sample rate increases. As long as the measurements remain above the threshold they will continue at this rate.  
When the measurements go below the threshold there will be a continued time of increased sampling. If the measurement goes back above the threshold then the timer will reset. If the timer runs out then the sample rate will be lowered.  

## Time stamps:

Time stamps are relative to the beginning of program execution. Time is in format of Days-Minutes-Seconds and the calendar date of program execution is recorded.  

## Measurements:

Measurements are taken on intervals.  
1. **Initial-temperature**
2. **Dynamic-Strain-Magnitude**
3. **Dynamic-Strain-Frequency**
4. **Final-temperature**  
Measurements are recorded in CSV format with a header.
Measurement headers are in the following format:  
    `<Start Time>`  
    `<Measurement Time><Intitial Temp><Magnitude><Frequency><Final Temp>`  
    Header Example:
        `Start Time 1-3-2022-11-32-45`  
        `Time | ITemp | Mag | Freq | FTemp`  
Measurement data is recorded in the following format:  
    `<Integer><Float><Sci><Sci><Float>`  
    Data Example:  
        `0  | 30   | 1.0e-3 | 2.0e2  | 30.5`  
        `5  | 31   | 1.1e-2 | 2.01e2 | 31.2`  
        `10 | 31.4 | 2.0e-2 | 2.0e2  | 31.3`  

# Code:

## main.c:

        The purpose of the main function is to have an
        easy to access initialization to the program. In this
        file the serial device will be registered and configured.
        The runtime environment will also be initialized and given
        appropriate arguments.
## runtime.c:

        The runtime environment in this function is responsible for
        dynamically measuring the data at two fixed sample rates depending
        upon user provided thresholds. The user provided thresholds are sent
        either via config file or via command line depending on the selected mode.
        Command line mode is a debug mode.
### TODO:

            - Selectable modes, debug and config: (High priority)
                Debug mode:
                    Takes threshold values on the command line, every time a new threshold value is typed the
                    program dynamically starts using this new value.
                    Flow:
                        - Threshold value is a global atomic set to config value.
                        - While loop waiting for user input writes to a temp variable.
                        - If temp variable is updated then lock all threads and update global atomic.
                        - Unlock all threads.
                Config mode:
                    Takes default values in a config file. This file includes threshold, as well as sample rates

            - Dynamic threshold mode: (Lowest priority)
                Run different threshold values in a row, either repeating or terminating
                Generally follows the form:
                    ([{<Threshold>,<Period>,<Lower Rate>,<Upper Rate>}(arbitrarily many)])(<space> [] or ((...; or ...<number>;) or ;))
                Example 1:
                    ([{<T1>,<P1>,<L1>,<U1>}{<T2>,<L2>,<U2>}]...;);

                    This example executes:
                        T1 for P1 seconds with a lower rate of L1 and an upper rate of U1,
                        T2 for P1 seconds with a lower rate of L2 and an upper rate of U2,
                        Repeats indefinitely
                Example 2:
                    ([{<T1>,<P1>,<L1>,<U1>}{<T2>,<L2>,<U2>}];);

                    This example executes:
                        T1 for P1 seconds with a lower rate of L1 and an upper rate of U1,
                        T2 for P1 seconds with a lower rate of L2 and an upper rate of U2,
                        Stops after 2*P1 seconds
                Example 3:
                    ([{<T1>,<P1>,<L1>,<U1>}] [{<T2>,<P2>,<L2>}{<T3>,<P3>,<U2>}]...2;)...;

                    This example executes:
                        T1 for P1 seconds with a lower rate of L1 and an upper rate of U1,
                        T2 for P2 seconds with a lower rate of L2 and an upper rate of U1,
                        T3 for P3 seconds with a lower rate of L2 and an upper rate of U2,
                        T2 for P2 seconds with a lower rate of L2 and an upper rate of U2,
                        T3 for P3 seconds with a lower rate of L2 and an upper rate of U2,
                        Repeats indefinitely

            - Runtime loop:
                Primary program loop that gets measurements and then writes them to a file.
                Flow:
                    - Outside the loop the program start date is written with the header
                    - Loop waits for exit command, while(!exit), where exit is a global atomic
                    - Suspend thread according to the sample rate, sample rate is an atomic pointer
                    that is passed to the function.
                    - Record measurements:
                        - Get time difference (seconds) between current and program execution
                        - Record thermocouple
                        - Record magnitude:
                            Check against threshold, set global atomic bool (Trigger used by hysteresis)
                        - Record frequency
                        - Record thermocouple
                        - Append values to formatted string
                    - Write formatted string to data file
                    - Acquire mutex to prevent user input during measurement and write phase.

            - Hysteresis:
                Thread that detects a trigger bool and updates sample frequency.
                Flow:
                    - Loop waits for trigger value to be set, while(!exit); if(Trigger){...}.
                    - Trigger:
                        - Timer?:
                            Reset timer.
                        - No Timer?:
                            Update rate, start timer.
                    - Acquire mutex to prevent user input during this time.

## measurement.c:

        This file contains custom commands that are sent to the oscilloscope to record
        and return measurement data. This file has four functions.
        - get_time:
            Returns time since program execution
        - get_mag:
            Returns dynamic strain magnitude
        - get_freq:
            Returns dynamic strain frequency
        - get_temp:
            Returns temperature reading from thermocouple

## file.c:

        This file contains a custom wrapper around C file operations to cleanly write to output data files.
        Takes a formatted string and writes to output.