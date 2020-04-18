# Typewriter to keyboard

Got an old typewriter from my grandmother, had in mind to turn it into a keyboard. This finally sort of worked for most of the characters. 

Technically, this mainly uses a membrane potentiometer (ex here: https://coolcomponents.co.uk/products/softpot-membrane-potentiometer-200mm) that reacts to the metallic bars of the keys being raised, each hitting in a different area of the potentiometer.

<img src="https://github.com/BmnQuentin/Arduino/blob/master/Typewriter%20to%20keyboard/images/Typewriter_wiring.jpg?raw=true" width=400">

An important point when connecting the softpot is using a high value resistor (i used 100kOhm) between VCC and signal to avoid having too much noise. A (not so) self explantory picture comes after.

<img src="https://github.com/BmnQuentin/Arduino/blob/master/Typewriter%20to%20keyboard/images/Typewriter_inside.jpg" width=400">

Important point: to be able to write as a keyboard and not only in the serial monitor, you need a board "keyboard.h-compatible". I used a pro micro with a 32U4 chip (it is important). Explanations can be found here: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/

To compile, the three ino file need to be in a foler named after the main file, Typewriter.ino
- Typewriter.ino contains the main loop,
- Keyboard_French1-2.ino i borrowed from another user (see link here: https://forum.arduino.cc/index.php?topic=552465.0) and helps deal with an issue coming from the fact my keyboard is Azerty whereas the Keyboard.h library only maps to a Qwerty keyboard.*
- Typewriter_alphabet.ino is basically the mapping for the alphabet and special characters.

Result can be seen here:



<img src="https://github.com/BmnQuentin/Arduino/blob/master/Typewriter%20to%20keyboard/images/Typewriter_final_packaging.jpeg" width=400">
