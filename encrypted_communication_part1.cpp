//------------------------------------------------------
// Names: Amro Amanuddein and Pushkar Sabharwal
// ID's: 1572498 (Amro) 1588927 (Pushkar) 
// CMPUT274, Fall 2019
// 
// Assignment 2 Part 1: Encrypted Arduino Communication
//------------------------------------------------------
#include <Arduino.h>
// Declaring global constant variables to be used later for encryption and decryption 
const int Pin13 = 13;
const uint32_t serverPrivateKey = 27103;
const uint32_t serverModulus = 95477;
const uint32_t serverPublicKey  = 7;
const uint32_t clientPrivateKey = 38291;
const uint32_t clientModulus = 84823;
const uint32_t clientPublicKey = 11;
// Setup function for the Arduinos
void setup(){
	init();
	Serial.begin(9600);
	Serial3.begin(9600);
	pinMode(Pin13, INPUT);
	
}
// This function determines which arduino is server and which is client
bool Client_or_Server() {
	bool isServer;
	if (digitalRead(Pin13) == HIGH){
		isServer = true;
	}
	else{
		isServer = false;

	}
	return isServer;
}
// Mulmod function used in powmod to prevent overflow, by computed a*b (mod m)
uint32_t mulmod(uint32_t a, uint32_t b, uint32_t m){
	uint32_t result = 0;
	uint32_t next_bit = 1;
	for (int i=0; i < 31; i++){
		if (i == 0 ){
			next_bit = b%m;
		
		} else {
			next_bit = (2%m)*(next_bit%m) % m;
		}
		if (a&1) {
			result += (next_bit % m) % m;
		}
		a = a >> 1;
		result = result % m;


	}
	return result;
}	
// Powmod function that was created in class computes x^e (mod n)
uint32_t powmod(uint32_t x, uint32_t e, uint32_t n){
	uint32_t ans = 1;
	uint32_t pow_x = x;
	while (e != 0){
		if (e&1){
			ans = mulmod(ans,pow_x,n);

		}
	pow_x = mulmod(pow_x,pow_x,n);
	e >>= 1;
	}
	return ans;
}
// This given function writes a uint32_t to Serial 3, it starts from LS byte to MS byte  
void uint32_to_serial3(uint32_t num){
	Serial3.write((char) (num >> 0 ));
	Serial3.write((char) (num >> 8 ));
	Serial3.write((char) (num >> 16 ));
	Serial3.write((char) (num >> 24 ));
}
// This given function reads uint32_t from Serial 3, starting from LS byte to MS byte.
uint32_t uint32_from_serial3(){
	uint32_t num = 0;
	num = num | ((uint32_t) Serial3.read()) << 0;
	num = num | ((uint32_t) Serial3.read()) << 8;
	num = num | ((uint32_t) Serial3.read()) << 16;
	num = num | ((uint32_t) Serial3.read()) << 24;
	return num;
}
int main(){
	setup();
	bool isServer = Client_or_Server();
	uint32_t d,n,e,m;
// If statement to determine who is server and who is client 
	if (isServer==true){
// If it is server which is sending, the values are assigned accordingly
			d= serverPrivateKey;
			n= serverModulus;
			e = clientPublicKey;
			m = clientModulus;
		}
	else {
// Otherwise it is the client
			d = clientPrivateKey;
			n = clientModulus;
			e = serverPublicKey;
			m = serverModulus;
	}
	while(true){
		if (Serial.available() > 0){
				uint32_t x = Serial.read();
// If the enter key is pressed, using the ASCII value, we go newline.
				if (x==13){
					Serial.println();
				}
// The typed letters/words/numbers appear on the screen
				Serial.print(char(x));
// The typed letters/words/numbers are encrypted using powmod and are sent
				uint32_t encrypted = powmod(x,e,m);
				uint32_to_serial3(encrypted);

			}
// Must process 3 bits first		
		else if (Serial3.available() > 3){
				uint32_t y = uint32_from_serial3();
				uint32_t decrypted = powmod(y,d,n);
// If the decrypted ASCII value is that of ENTER (/r), we go to newline
				if (decrypted == 13){
					Serial.println();
				}
				Serial.print(char(decrypted));
			
		} 
	}
	Serial.flush();
	Serial3.flush();	
}
	