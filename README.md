# Solution to Question D of the 2023 National Undergraduate Electronics Design Contest

- **Project Name**: Signal Modulation Mode Recognition and Parameter Estimation Device  

- **Competition Topic**: Question D of the 2023 National Undergraduate Electronics Design Con -test (For detailed information, see `D题_信号调制方式识别与参数估计装置.pdf`)

## Brief introduction

The source code for Question D of the 2023 National Undergraduate Electronics Design Contest.

The hardware circuit utilizes chips such as AD9959, AD835, ADF4351, ADF4002, STM32H743, ADL5511, OPA690, and OPA695, along with several low-pass filters.

The requirements of this question regarding the program code primarily involve distinguishing AM, FM, 2ASK, 2FSK, and 2PSK signals, and subsequently entering the corresponding hardware circuit for demodulation.

My solution to this requirement involves the use of ADC, DMA, and TIM to achieve ADC interrupt acquisition of the signal. Subsequently, FFT computation will be performed on the acquired signals, allowing for differentiation of each signal based on the amplitude spectrum in the frequency domain. The ADC acquisition frequency is 400 kHz, determined by TIM. The FFT computation is implemented using the DSP library.

For the programming, I employed STM32CubeMX software to generate the main framework of the HAL library code, and then I wrote the corresponding code for the specific requirements in Keil. To be able to break free from the constraints of the microcontroller, I exported the test data after performing FFT operations on various modulation signals, and I wrote a segment of test code in the C language development environment within Visual Studio Code.

## File Structure Description

- **`2023D.zip`**: Source code project (Unzip for full project).

- **`test.c`**: The C language test file distinctively distinguishes the signals.

- **`amp test data`**: The amplitude of various signals after collection using the STM32H743 microcontroller and subsequent FFT calculations.

- **`D题_信号调制方式识别与参数估计装置.pdf`**: Official problem statement (Chinese).

## Environmental dependencies
- **Compiler**: A compiler that supports the C99 standard or higher.
  
- **Toolchain**: It is recommended to use the Keil embedded development environment for the source code project file `2023D.zip`, and the C language code `test.c` for testing is recommended to be developed in the C language development environment in Visual Studio Code.

- **Hardware dependencies**: This code is designed to process signals that have been mixed by the AD835 multiplier after low-pass filtering, with frequencies around 100kHz, as required by the problem; the demodulation part is primarily implemented by hardware circuits.

## Feature description
- **Modulation mode identification**: It supports the judgment and demodulation of common modulation signals such as AM, FM, 2ASK, 2FSK, and 2PSK

- **Parameter estimation**: Realize the calculation of key parameters such as modulation signal frequency, modulation coefficient, binary code rate, etc

- **Result display**: Various modulation types and corresponding parameters are displayed via LCD


## Test data usage

Use the .log file in the `amp test data` as input into the C language program `test.c` for testing.

## note

- The source code for the signal modulation mode recognition and parameter estimation device is entirely based on solving the problem of recognizing signals modulated using the data provided in the file. This source code cannot achieve general signal modulation mode recognition and parameter estimation.

- Regarding the section on how to demodulate signals, this project only includes the code using ADF4351 and ADF4002, along with the code for the field-effect transistor switching circuit set up for different signals requiring different hardware circuits. The specific method of demodulating signals is primarily implemented using hardware circuits.

- The FFT operation is implemented using code from the DSP library.

## License

The code for this project follows the [MIT License].Please refer to the files within the project for specific copyright information.

## Acknowledgments

Here,I would like to express my gratitude to the organizing committee of the 2023 National Undergraduate Electronics Design Contest for providing the competition problem, to my advisor Douzhe Li for his technical guidance, and to my teammates Shen Liu and Xinyi Duan for their substantial support in building the hardware circuits.
