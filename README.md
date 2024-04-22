# Arduino File Transfer

This project demonstrates file transfer functionality from an Arduino device to a Python server over Ethernet.

## Description

The project consists of two parts: an Arduino sketch and a Python server script.

### Arduino Sketch

The Arduino sketch (`arduino_file_transfer.ino`) reads a file from an SD card and sends its contents to a Python server over Ethernet. It uses the Ethernet and SPI libraries to establish a connection and the SdFat library to read from the SD card.

### Python Server Script

The Python server script (`server.py`) listens for connections from the Arduino device and writes the received data to a file. It uses the `socket` module for network communication.

## Requirements

- Arduino Mega (or compatible) board
- Ethernet shield or module
- SD card module
- Python 3.x installed on the server machine

## Usage

1. Upload the `arduino_file_transfer.ino` sketch to your Arduino board.
2. Connect the Arduino to the Ethernet network.
3. Run the `server.py` script on your Python server.
4. The Arduino will start transferring the file to the server once it's connected.

## File Format

The file to be transferred should be named `file.txt` and placed in the root directory of the SD card.

## Notes

- Ensure that the Ethernet configuration (IP address, MAC address, etc.) in both the Arduino sketch and the Python script matches your network setup.
- Modify the code as needed to adapt it to your specific requirements.


