#include "main.h"


int ROUND = 0;
int MAX_ROUND = 4;
  int TIMEOUT = 1000000; //timeout for game


int main() {
    setup();

    while (1) { 
			    ROUND = 0; 
        int seed = 0;
      
            bool gamestarted = false;
						// this while loop is for looping untill a user has pressed a button to start the game 
						// while thats happening the seed is incrementing
            while (!gamestarted) {
                seed++;
                gamestarted = startingseq(); // Run starting sequence
            }
            srand(seed);
            simon();
            delay();
            gameendseq(); // Run end sequence
        }
    
}

void setup() {
	//Enable clock for GPIOA and GPIOB
 RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 3); 
 

    // Configure GPIOA
	// PA0, PA1, PA4 as outputs 
    GPIOA->CRL = 0x00030033; 

    // Configure GPIOB
	// PB0 as output, PB4 and PB6 as inputs 
	// PB8, PB9 as inputs
    GPIOB->CRL = 0x04040003; 
    GPIOB->CRH = 0x00000044; 
	
}

void delay() {
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 750; j++) {}
    }
}

void delay2() {
    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 1000; j++) {}
    }
}
void delayShort() {
    for ( int i = 0; i < 50000; i++) {} 
}

void debounce() {
    delayShort();
}

void turnoffLED() {
	// Turning of PBO, PA0, PA1, PA4
    GPIOB->ODR &= ~(1 << 0);       // Turn off PB0
    GPIOA->ODR &= ~((1 << 0) | (1 << 1) | (1 << 4)); 
}

bool startgame() {
    // Checking if any game button is pressed (PB4, PB6, PB8, PB9)
    return ((!(GPIOB->IDR & (1 << 9))) || (!(GPIOB->IDR & (1 << 8))) ||
            (!(GPIOB->IDR & (1 << 6))) || (!(GPIOB->IDR & (1 << 4))));
}

bool startingseq() {

	
	//Forward Sequence 
	// using for loop to enable and turn on LED 
	// For loop for turning LED on and Turning off
    for (int i = 0; i < 4; i++) {
    //Turning LEDs on
        if (outputPort[i] == 1) { 
            GPIOB->ODR |= (1 << outputPin[i]); 
        } else { 
            GPIOA->ODR |= (1 << outputPin[i]); 
        }
				
        delay();
				//Turning LEDS off
        if (outputPort[i] == 1) { 
            GPIOB->ODR &= ~(1 << outputPin[i]); 
        } else { 
            GPIOA->ODR &= ~(1 << outputPin[i]); 
        }
				
				//while the sequence is happening we check if the the startgame() is called

        if (startgame()) {
            return true;
        }
    }

    // Reverse sequence 
		// using for loop to enable and turn on LED 
	// For loop for turning LED on and Turning off
		//starting from the back 
    for (int i = 2; i >= 0; i--) {
			  //Turning LEDs on
        if (outputPort[i] == 1) { 
            GPIOB->ODR |= (1 << outputPin[i]); 
        } else { // GPIOA
            GPIOA->ODR |= (1 << outputPin[i]); 
        }
        delay();
				//Turning LEDS off
        if (outputPort[i] == 1) {
            GPIOB->ODR &= ~(1 << outputPin[i]);
        } else { // GPIOA
            GPIOA->ODR &= ~(1 << outputPin[i]); 
        }

        if (startgame()) {
            return true;
        }
    }

    return false;
}
 

 void gamewon() {
	//gaming wining sequence which will repeat 4 times
	//flashing 4 leds 4 times
    for (int repeat = 0; repeat < 4; repeat++) { 
        // Turn on all LEDs
        for (int i = 0; i < 4; i++) {
            if (outputPort[i] == 1) { 
                GPIOB->ODR |= (1 << outputPin[i]); 
            } else { 
                GPIOA->ODR |= (1 << outputPin[i]); 
            }
        }
        delay(); 
     turnoffLED();
        delay();
    }
}


void gameLost() {
		//gaming losing sequence which will repeat 4 times
	//will flash 2 even indicies first then flash 2 odd indicies 4 times
	
	  // First Set: Turn on LEDs at even indicies
    for (int repeat = 0; repeat < 4; repeat++) { 

        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) { 
                if (outputPort[i] == 1) { 
                    GPIOB->ODR |= (1 << outputPin[i]); 
                } else { 
                    GPIOA->ODR |= (1 << outputPin[i]); 
                }
            }
        }
        delay(); 

        turnoffLED();

        // Second Set: Turn on LEDs at odd indicies
        for (int i = 0; i < 4; i++) {
            if (i % 2 != 0) { 
                if (outputPort[i] == 1) {
                    GPIOB->ODR |= (1 << outputPin[i]); 
                } else {
                    GPIOA->ODR |= (1 << outputPin[i]); 
                }
            }
        }
        delay(); 

    turnoffLED();
    }
}


void displayRound() {
    turnoffLED(); // Ensure all LEDs are off before displaying the round
	
    switch (ROUND) {
        case 1:
            GPIOB->ODR |= (1 << 0); // PB0 = 1 0001
            break;
        case 2:
            GPIOA->ODR |= (1 << 4); // PA4 = 1 0010
            break;
        case 3:
            GPIOA->ODR |= (1 << 4); // PA4 = 1 0011
            GPIOB->ODR |= (1 << 0); // PB0 = 1
            break;
        case 4:
            GPIOA->ODR |= (1 << 1); // PA1 = 1 0100
            break;
        case 5:
            GPIOA->ODR |= (1 << 1); // PA1 = 1 0101
            GPIOB->ODR |= (1 << 0); // PB0 = 1
            break;
        case 6:
            GPIOA->ODR |= (1 << 1); // PA1 = 1 0110
            GPIOA->ODR |= (1 << 4); // PA4 = 1
            break;
        case 7:
            GPIOA->ODR |= (1 << 1); // PA1 = 1 0111
            GPIOA->ODR |= (1 << 4); // PA4 = 1
            GPIOB->ODR |= (1 << 0); // PB0 = 1
            break;
        case 8:
            GPIOA->ODR |= (1 << 0); // PA0 = 1 1000
            break;
        case 9:
            GPIOA->ODR |= (1 << 0); // PA0 = 1 1001
            GPIOB->ODR |= (1 << 0); // PB0 = 1
            break;
        case 10:
            GPIOA->ODR |= (1 << 0); // PA0 = 1 1010
            GPIOA->ODR |= (1 << 4); // PA4 = 1
            break;
        default:
            break;
    }
}

void gameendseq() {
    while (1) {
        displayRound(); 
			// Break the loop on a button press
        if (startgame()) { 
            turnoffLED();
            break;
        }
    }
    return;
}



void simon() {
    int sequence[10] = {0};
    int currRoundScore = 0;

    // Generate the First random LED for the first round
    sequence[0] = rand() % 4;

		//loop untill the Round doesnt reach the MAX Round
    while (ROUND <= MAX_ROUND) {
			
			
        // Show the LED sequence for the current round
        for (int i = 0; i < ROUND; i++) {
            int currentLED = sequence[i];

            // Flash the LED for the sequence
            if (outputPort[currentLED] == 1) { 
                GPIOB->ODR |= (1 << outputPin[currentLED]); 
                delay2();
                GPIOB->ODR &= ~(1 << outputPin[currentLED]); 
            } else { 
                GPIOA->ODR |= (1 << outputPin[currentLED]);
                delay2();
                GPIOA->ODR &= ~(1 << outputPin[currentLED]); 
            }

            delay2(); 
        }

        delay(); 

        // Get Player Input
        for (int i = 0; i < ROUND; i++) {
            int success = playerInput(sequence[i], &currRoundScore);
				// If the player fails to match the sequence or times out
            if (!success) { 
							ROUND --;
             
                gameLost(); 
                return;
            }
        }

       // if got the round done we increment round and add another # to random Seq
				//checking if the current Round is < then MAX
        if (ROUND < MAX_ROUND) {
            sequence[ROUND] = rand() % 4;
            ROUND++;
        } else {
            // we done the game 
					
            gamewon();
            return;
        }

        delay2();
    }
}


 int playerInput(int expectedInput, int *currRoundScore) {
	 
  
    int feedbackLED = outputPin[expectedInput]; 
    int port = outputPort[expectedInput];       

    while (TIMEOUT--) {
        // Check for the correct button press 
        if (!(GPIOB->IDR & (1 << inputPin[expectedInput]))) { 
            debounce(); 
					// Confirm button press if it is we increment the round score
            if (!(GPIOB->IDR & (1 << inputPin[expectedInput]))) { 
                (*currRoundScore)++;
						
							
							//after user presses button we will show the user a feedbackLED indicating which button theypressed
               
										if (port == 1) { 
												GPIOB->ODR |= (1 << feedbackLED);  
												delay2();                          
												GPIOB->ODR &= ~(1 << feedbackLED); 
										} else { 
												GPIOA->ODR |= (1 << feedbackLED);  
												delay2();                          
												GPIOA->ODR &= ~(1 << feedbackLED); 
										}
                return 1; 
            }
        }

        // Check for incorrect button presses
        for (int i = 0; i < 4; i++) {
            if (i != expectedInput) {
                if (!(GPIOB->IDR & (1 << inputPin[i]))) { 
                    debounce(); 
                    if (!(GPIOB->IDR & (1 << inputPin[i]))) { 
                        return 0;
                    }
                }
            }
        }
    }

    return 0; // return 0 if the timeout expires
}
