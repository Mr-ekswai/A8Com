# A8 serial monitor is a uart/rs232/com port monitor/debug software

![Intra screenshot](screenshot.jpg?raw=true)

## Project

* Windows sdk api only, no mfc
* Primarily written in C
* Compiled with Microsoft Visual Studio Community 2022 / MSVC 2022
* No external dependencies

## Features list:

* Small exe file size, Only 33kB. Portable, no installation needed.
* Support high baudrate of USB to serial converter ICs, ex CH340、PL2303、FT232、cp2102.
* Support dynamic plug and play with usb to serial ICs.
* Display with HEX and ASCII mode.
* Fast response.
* Support all baudrates, stopbits, parity control, data bits etc.
* Send file to serial also support.
* Support time controled automatic send.
* It supports appending newline character after sending string.
