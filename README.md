# FreqDisp
FreqDisp is a simple graphical application built using the Raylib and Raygui libraries. The program allows the user to adjust the frequency of a background color flashing effect on the window. The user can control the flashing frequency through a value box in the GUI. It is designed to visualise frequencies.

# IMPORTANT SAFETY NOTE
As previously mentioned, this program when run causes the screen to flash at a certain frequency. I am not responsible for any injury that may occur from viewing the flashing lights.

## Prerequisites
- Raylib (v5.5) --> requires external installation
- Raygui (provided in repo ./ext folder)

## Usage - Running the Program
```bash
./FreqDisp
```
Upon running the program, the window will appear with the following elements:

Value Box: You can adjust the flashing frequency using the value box. The frequency is constrained between 0 Hz (no flashing) and 100 Hz (maximum flashing rate).
Start Button: Clicking the "START" button or pressing the ENTER key will begin the flashing effect at the selected frequency. The background color of the window will alternate at the specified rate.
Flashing Frequency: The current flashing frequency is displayed in the window.
FPS: The FPS (frames per second) is displayed in the top-left corner of the window for debugging purposes.
