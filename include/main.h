#ifndef MAIN_H
#define MAIN_H

#include "stm32f10x.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variables
int ROUND;
int MAX_ROUND;

// Input and Output Pin Arrays
int inputPin[] = {4, 6, 8, 9};  // Port B pins: PB4, PB6, PB8, PB9 (Buttons)
int outputPin[] = {0, 1, 4, 0}; // Port A pins: PA0, PA1, PA4, and PB0 (LEDs)
int outputPort[] = {0, 0, 0, 1}; // 0 for GPIOA, 1 for GPIOB

void setup(); //seting up the ports and enabling clocks
void delay();
void delay2();
void delayShort();
void turnoffLED(); //function for turning off all LEDS
bool startgame(); //startgame function
bool startingseq(); //starting sequence
void gamewon(); //gamewon sequence
void gameLost(); //gamelost sequence
void displayRound(); //showing the rounds
void gameendseq(); // gameendsequence
void simon(); //simon says game
int playerInput(int expectedInput, int *currRoundScore); //to check for playerInput
void debounce(void);

#endif // MAIN_H
