# Typewriter to keyboard

Got an old typewriter from my grandmother, had in mind to turn it into a keyboard. This finally sort of worked for most of the characters. 

Technically, this mainly uses a membrane potentiometer (ex here: https://coolcomponents.co.uk/products/softpot-membrane-potentiometer-200mm) that reacts to the metallic bars of the keys being raised, each hitting in a different area of the potentiometer.

Important point: to be able to write as a keyboard and not only in the serial monitor, you need a board "keyboard.h-compatible". I used a pro micro with a 32U4 chip (it is important). Explanations can be found here: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/

To compile, the three ino file need to be in a foler named after the main file, Typewriter.ino
- Typewriter.ino contains the main loop,
- Keyboard_French1-2.ino i borrowed from another user (see link here: https://forum.arduino.cc/index.php?topic=552465.0) and helps deal with an issue coming from the fact my keyboard is Azerty whereas the Keyboard.h library only maps to a Qwerty keyboard.*
- Typewriter_alphabet.ino is basically the mapping for the alphabet and special characters.

Result can be seen here: https://youtu.be/q-F_wrZprTk
