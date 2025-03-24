# 2023D
The source code for Question D of the 2023 National College Students' Electronic Design Competition.

The hardware circuit utilizes chips such as AD9959, AD835, ADF4351, ADF4002, STM32H743, ADL5511, OPA690, and OPA695, along with several low-pass filters.

The requirements for the program primarily involve distinguishing AM, FM, 2ASK, 2FSK, and 2PSK signals, and subsequently entering the corresponding hardware circuit for demodulation.

In response to this requirement, My solution is to perform FFT calculations on the signals and distinguish each signal in the frequency domain based on the amplitude and phase diagrams.

For the programming, I employed STM32CubeMX software to generate the main framework of the HAL library code, and then I wrote the corresponding code for the specific requirements in Keil.

Here, I extend my gratitude to my teammates Shen Liu and Xinyi Duan for their substantial support in constructing the hardware circuit.
