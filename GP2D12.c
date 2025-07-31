#include "types.h" // Include necessary type definitions (like f32, u8)

// Assuming the existing Init_ADC and Read_ADC functions are available.

// Function to convert GP2D12 analog voltage to distance in centimeters
u8 Get_Distance(f32 voltage_V) {
        f32 distance_cm;
        if(voltage_V > 0.1) { // Threshold can be adjusted based on testing
                if(voltage_V > 0.12)  // Use a threshold slightly above 0.1
                        distance_cm = (23.4 / (voltage_V - 0.1)) - 0.42; // Calculate distance using the formula
                else
                        distance_cm = 80.0; // Assume max distance for very low/invalid voltages

                if(distance_cm>80)
                        distance_cm=80;
                else if(distance_cm < 10.0)
                        distance_cm = 9.8; // Cap at minimum range (10 cm) and handle ambiguous zone
        }
        else
                distance_cm = 90.0; // Indicate object is beyond maximum range (80 cm)
return (u8)distance_cm; // Return the calculated and clamped distance in cm
}