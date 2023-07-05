#include <xc.h>
#include <stdio.h>

// Configuration settings
#pragma config WDT = OFF   // Disable Watchdog Timer

// Define ADC channels
#define ADC_CHANNEL 0     // Analog input channel 0

// Function to initialize ADC module
void ADC_Init()
{
    ADCON0bits.ADON = 0;      // Disable ADC module
    
    ADCON1bits.PCFG3 = 1;     // Set AN0 as analog input
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 0;
    
    ADCON2bits.ADFM = 1;      // Right justified result
    ADCON2bits.ACQT2 = 1;     // Acquisition time = 12 TAD
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT0 = 1;
    
    ADCON2bits.ADCS2 = 1;     // Conversion clock = FOSC/16
    ADCON2bits.ADCS1 = 0;
    ADCON2bits.ADCS0 = 0;
    
    ADCON0bits.ADON = 1;      // Enable ADC module
}

// Function to read ADC value
unsigned int ADC_Read()
{
    ADCON0bits.GO = 1;           // Start conversion
    
    while (ADCON0bits.GO);      // Wait for conversion to complete
    
    return ((ADRESH << 8) + ADRESL); // Return 10-bit ADC result
}

// Delay function
void Delay()
{
    unsigned int i;
    for (i = 0; i < 1000; i++);
}

// Main function
void main()
{
    unsigned int adcValue;
    float voltage;
    
    TRISA = 0xFF;    // Set all PORTA pins as input
    
    ADC_Init();      // Initialize ADC module
    
    while (1)
    {
        adcValue = ADC_Read();                  // Read ADC value
        voltage = (adcValue * 5.0) / 1023.0;    // Convert ADC value to voltage (assuming reference voltage is 5V)
        Delay();    //Delay
        if (voltage >= 0 && voltage <= 100)      // Check if voltage is within the desired range
        {
            printf("Voltage: %.2f V\n", voltage);         //Print voltage
        }
    }
}
