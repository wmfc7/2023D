# Solution to Topic D of the 2023 National Undergraduate Electronics Design Contest

- **Project Name**: Signal Modulation Mode Recognition and Parameter Estimation Device  

- **Competition Topic**: Topic D of the 2023 National Undergraduate Electronics Design Con -test (For detailed information, see `D题_信号调制方式识别与参数估计装置.pdf`)

## Brief introduction

The source code for Topic D of the 2023 National Undergraduate Electronics Design Contest.

The hardware circuit utilizes chips such as AD9959, AD835, ADF4351, ADF4002, STM32H743, ADL5511, OPA690, and OPA695, along with several low-pass filters.

The requirements of this topic regarding the program code primarily involve distinguishing AM, FM, 2ASK, 2FSK, and 2PSK signals, and subsequently entering the corresponding hardware circuit for demodulation.

In response to this requirement, My solution is to perform FFT calculations on the signals and distinguish each signal based on the amplitude and phase diagrams in the frequency domain.

For the programming, I employed STM32CubeMX software to generate the main framework of the HAL library code, and then I wrote the corresponding code for the specific requirements in Keil.

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

## License

The code for this project follows the [MIT License].Please refer to the files within the project for specific copyright information.

## Acknowledgments

Here,I would like to express my gratitude to the organizing committee of the 2023 National Undergraduate Electronics Design Contest for providing the competition topic, to my advisor Douzhe Li for his technical guidance, and to my teammates Shen Liu and Xinyi Duan for their substantial support in building the hardware circuits.
