#ifndef KEYBOARD_H
#define KEYBOARD_H

extern bool pause;

void processNormalKeys(unsigned char, int, int);
void processSpecialKeys(int, int, int);

#endif // KEYBOARD_H
