eMidiDrumController
===================

The electronic MIDI drum controller project on AVR ATMega128 microcontroller.

Links:

Pictures: http://goo.gl/MCKLs9
Presentation: http://goo.gl/ddCL1l
>Yet to upload schematic.

I found myself a way to make the electronic drum kit as I could not afford one. Necessity is the mother of all inventions and I decided to mother mine. I figured I could also record drum tracks with it for my band, practice with head-phones on and have a lot of fun!

After a lot of research and looking at DIY websites, fathers of its invention and people who had already done this, it was inspiring. Instead of making an entire stand-alone drum kit, it struck to me that I should take advantage of equipment I already owned (a computer with audio workstation software and a micro-controller based development board) to produce the drum sound. So, all that was needed was Trigger-to-MIDI conversion. I did not have to worry about sounds. Thus, by using MIDI, the possibilities are endless. Any sound is possible!

Basically, I was making a drum-trigger-module which took input from any external source (switches, pads, gestures, etc.) and triggered the MIDI message. I took it up as my project for the summer internship I enrolled for at ThinkLabs.

Let us go through, each of the things required to understand the operation of this drum kit:

The Hardware: Consists of 6 drum pads, an analog input board and an AVR micro-controller-based development board.
I made drum pads using small piezo sensors which could take the beating, super-glued to a thin metal sheet and enclosed in small layers of foam on both sides, placed on a round wooden surface. I had the piezo’s wired to an RC jack protruding from the pads.
A simple circuit required to ensure that the piezo outputs voltages between 0V to 5V in the acceptable range to the analog-to-digital converter (ADC) on the μC board is used as the analog input board and pads are connected using cables.
The heart of the system is usually something that can think and get all the work done! Here, it is the AVR μC based development board. It has an LCD display, LED’s on it, a serial port for connecting it to the computer and an easy to connect sensor port. The analog board gives the analog input from drum-pads to the sensor port on this board, which is then converted into a digital input by the ADC triggering the MIDI note after it crosses a certain threshold!

LED port: Port C

ADC port: Port F

UART0

Timer0 - Interrupt Clear Timer on Compare match (CTC mode)

The basics of MIDI: Musical Instrument Digital Interface abbreviated as MIDI is an industry-standard communication protocol that was developed so that electronic musical instruments and other equipment like computers or any other devices could communicate, control and synchronize with each other and exchange system data.
Putting this in simple terms, I had to assign a specific MIDI note message for a specific sound and send it to the PC through the serial port when that particular pad was hit.

Example: In a note event, three bytes are sent; Status, Note On, Velocity. If we assume we're working on MIDI
Channel 1, the data would look something like this 0x90, 0x24, 0x7F. First the status byte, 0x90 if we translate this into binary we get 10010000. The upper nibble (1001) shows we have a Note On event, the lower nibble (0000) is the MIDI channel 1. MIDI devices can have 16 channels, allowing multiple notes to play at the same time.
The next byte is the note value, in this case 0x24, which is the Bass drum note. The final byte is 0x7F, which is the velocity i.e. how hard the key was pressed, in this case maximum.

The Programming and software: The velocity byte is linked to the force of hitting the drumpad, making it velocity sensitive. The above message is recognized by MIDI software’s available today, it seems like Cakewalk! I was using a Digital Audio Workstation software by Sony called Acid Pro along with an additional plugin i.e. EzDrummer. I had to install a driver called Roland Serial MIDI driver for using input to the Serial port of the computer as a MIDI-IN port (thus converting 38400 bps baud rate to 31250 bps, which is required for MIDI), in this case.

The nerve-wrecking programming is done in C using WinAVR compiler. The program detects the hit on each pad, one-by-one. So, we get the hits in Time Division Multiplexed fashion and multiple hits are made possible by storing each value in an array, which pops out the individual pad velocities during hits. Macros have also been used extensively for ease of changing notes on channels. When the Bass drum is hit, its equivalent MIDI note is sent to the PC and is played on the software, while the μC board displays B^ on the LCD and lights up the 1st LED (since, it’s on the 1st ADC channel). Also implemented millis() function found on the Arduino development to count milliseconds elapsed since board boot-up.

Files:

main.c //start here

midi.h //MIDI macros for note numbers

adc.h //adc routines and configuration

serial.h //RS232 serial port configuration

LCD_meg128.h //LCD library
