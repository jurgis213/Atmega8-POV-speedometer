/**	\v1.0\
Driving shift registers using
an AVR chip's hardwarre SPI

SPI HARDVARE ATMEGA8 BITU SKAICIUOTUVAS
http://jumptuck.com

**/
#include <avr/io.h>
#include <util/delay.h>
#define SHIFT_REGISTER DDRB
#define SHIFT_PORT PORTB
#define DATA (1<<PB3) //MOSI (SI)
#define LATCH (1<<PB2) //SS (RCK)
#define CLOCK (1<<PB5) //SCK (SCK)
#include <avr/interrupt.h>
// global variable to count the number of overflows
volatile uint8_t tot_overflow;

void timer1_init()
{
    OCR1A = 78; //0,01 (75- 0.005)

    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A

    TIMSK |= (1 << OCIE1A);
    //Set interrupt on compare match

    TCCR1B |= (1 << CS10) | (1 << CS11);
    // set prescaler to 1024 and start the timer
	int tot_overflow = 0;
    sei();	
}
  
ISR (TIMER1_COMPA_vect)
{    // keep a track of number of overflows
    tot_overflow++; //persisukimu skaicius +1
	PORTC ^= (1 << 4);
	PORTC ^= (1 << 4);
  	
    if (tot_overflow >=1000 ) //i >=2000 vikdoma zemiau esanti kodo dalis
    {	
		
		PORTC ^= (1 << 4);
		_delay_ms((10));
		PORTC ^= (1 << 4);
		
		

    }

}

void init_IO(void){
//Setup IO
SHIFT_REGISTER |= (DATA | LATCH | CLOCK); //Set control pins as outputs
SHIFT_PORT &= ~(DATA | LATCH | CLOCK); //Set control pins low
}
void init_SPI(void)
	{
	//Setup SPI
	SPCR = (1<<SPE) | (1<<MSTR); //Start SPI as Master
	}
void spi_send(unsigned char byte)
	{
	SPDR = byte; //Shift in some data
	while(!(SPSR & (1<<SPIF))); //Wait for SPI process to finish
	}
int main(void)
	{
	 DDRC |= (1 << 4);			//interupto ledas

	DDRB &= ~(1 <<PINB6);		//Nustato PINB0 kaip inputa
	PORTB |= 1 <<PINB6;			//PINBO nustato auksta signala, kad butu matyti, kada nueis i zeme.
	int Pressed = 0;

	init_IO();
	init_SPI();
	unsigned int binary_counter = 0;

	timer1_init();
	int over = 0;

	int skaitliukas = 0;	
	while (1)
	{
		if (bit_is_clear(PINB, 6)) //Check is the button is pressed
		{
		//Make sure that the button was released first
			if (Pressed == 0)
			{
				over = tot_overflow;
				tot_overflow = 0;
				
				//tot_overflow = 0;

				//TCNT1 = 0;

				/**
				if (TCNT1 >= 30000);
				{
				PORTC ^= (1 << 4);
				}
				laikas= TCNT1;
				laikas= laikas/160;
				TCNT1 = 0;

				**/
						unsigned int i = 0;
				float wait = 1.5;
				char *fraze;
				
				if( skaitliukas <15 )
				   {
				skaitliukas = skaitliukas+1;

				if( 115 > over > 107 )
				   {
				    fraze = "!!!!!";
					// = 2.1;
				   }
				else if( 107 > over > 105 )
				   {
				    fraze = "14,00 ~";
					// = 2.1;
				   }
				else if( over > 98 )
				   {
				    fraze = "15,00 ~";
					// = 1.96;
				   }
				else if( over > 92 )
				   {
				    fraze = "15,96 ~";
					// = 1.84;
				   }
				else if( over > 86 )
				   {
				    fraze = "17,00 ~";
				   	// = 1.72;
				   }
				else if( over > 82 )
				   {
				    fraze = "18,00 ~";
				   	// = 1.64;
				   }
				else if( over > 77 )
				   {
				   fraze = "19,00 ~";
				   // = 1.54;
				   }
				else if( over > 73 )
				   {
				    fraze = "20,12 ~";
					// = 1.46;
				   }
				else if( over > 70 )
				   {
				    fraze = "21,00 ~";
					// = 1.4;

				   }
				else if( over > 67 )
				   {
				    fraze = "22,00 ~";
					// = 1.34;
				   }
				else if( over > 64 )
				   {
				    fraze = "23,00 ~";
					// = 1.28;
				   }
				else if( over > 61 )
				   {
				    fraze = "24,00 ~";
					// = 1.22;
				   }
				else if( over > 59 )
				   {
				    fraze = "25,00 ~";
					// = 1.18;
				   }
				else if( over > 56 )
				   {
				    fraze = "26,22 ~";
					// = 1.12;
				   }
				else if( over > 54 )
				   {
				    fraze = "27,20 ~";
					// = 1.08;
				   }
				else if( over > 52 )
				   {
				    fraze = "28,24 ~";
					// = 1.04;
				   }
				else if( over > 50 )
				   {
				    fraze = "29,37 ~";
					// = 1.0;
				   }
				else if( over > 48 )
				   {
				    fraze = "30,60 ~";
					// = 0.96;
				   }
				else if( over > 46 )
				   {
				    fraze = "31,93 ~";
					// = 0.92
				   }
				else if( over > 44 )
				   {
				    fraze = "33,38 ~";
					// = 0.88
				   }
				
				else if( over > 42)
				   {
				    fraze = "34,97 ~";
					// = 0.84;
				   }
				else if( over > 40 )
				   {
				    fraze = "36,72 ~";
					// = 0.8;
				   }
				else if( over > 39 )
				   {
				    fraze = "37,66 ~";
					// = 0.78;
				   }
				else if( over > 38 )
				   {
				    fraze = "38,65 ~";
					// = 0.76;
				   }
				else if( over > 37 )
				   {
				    fraze = "39,69 ~";
					// = 0.74;
				   }
				else if( over > 36 )
				   {
				    fraze = "40,80 ~";
					// = 0.72;
				   }
				else if( over > 35 )
				   {
				    fraze = "41,96 ~";
					// = 0.7;
				   }
				else if( over > 34 )
				   {
				    fraze = "43,20 ~";
					// = 0.68;
				   }
				else if( over > 33 )
				   {
				    fraze = "44,50 ~";
					// = 0.66;
				   }
				else if( over > 32 )
				   {
				    fraze = "45,90 ~";
					// = 0.64;
				   }
				else if( over > 31 )
				   {
				    fraze = "47,38 ~";
					// = 0.62;
				   }
				else if( over > 30 )
				   {
				    fraze = "48,96 ~";
					// = 0.6;
				   }
				else if( over > 29 )
				   {
				    fraze = "50,64 ~";
					// = 0.58;
				   }
				else if( over > 28 )
				   {
				    fraze = "52,45 ~";
					//// = 0.56;
				   }
				else if( over > 27 )
				   {
				    fraze = "47,38 ~";
					//// = 0.54;
				   }
				else
				   {
				    fraze = "505";
				   }
				}
				else if(skaitliukas >= 15)
				{fraze = "#";
				skaitliukas = skaitliukas+1;
				}
			    if (skaitliukas >30)
				{
				skaitliukas = 0;
				}  
				
				
				for (i = 0; i < 1; i++){
				
					//int masyvas [70] = {6542,53187,32995,49203,49267,49347,49267,49267,49203,49379,53187,52995,49187,51187,52275,52275,53219,51171,49155,49395,53235,53235,52419,52435,53219,50979,32771,32787,40947,40947,33683,40931,40035,32771,32771,36835,40947,38963,38963,40947,51187,49155,49155,53219,53219,53216,49184,49184,49184,53216,53219,49155,49155,52227,53235,52227,35843,52227,52227,52227,52227,52227,52227,52227,49187,65534,32704};
					/* spausdins visus elementus is masyvo*/
					int nr1[10] = {49155,49155,49155,65535,65535,3,3,3};
					int nr2[10] = {49663,49663,49539,49539,49539,49539,65411,65411};
					int nr3[10] = {49539,49539,49539,49539,49539,49539,65535,65535};
					int nr4[10] = {65408,65408,384,384,384,384,65535,65535};
					int nr5[10] = {65411,65411,49539,49539,49539,49539,49663,49663};
					int nr6[10] = {65535,65535,49539,49539,49539,49539,49663,49663};
					int nr7[10] = {49152,49152,49152,49152,49152,65535,65535};
					int nr8[10] = {65535,65535,49539,49539,49539,49539,65535,65535};
					int nr9[10] = {65411,65411,49539,49539,49539,49539,65535,65535};
					int nr0[10] = {65535,65535,49155,49155,49155,49155,65535,65535};
					int kmh[36] = {0,65535,65535,192,480,816,65055,64527,0,0,1023,1023,384,384,255,255,511,384,384,511,255,31,1016,7552,61440,0,0,65535,65535,384,384,384,511,255,0.0};
					int ornam[41] = {32769,49155,24582,12300,6168,3120,1632,960,4080,65151,61455,43690,43690,21845,21845,43690,43690,21845,21845,32769,16386,8196,4120,2144,1408,512,1280,1152,6208,12320,24592,32776,4,2,1,65535,0,65535,0,65535.0};
					int nrX[10] = {0,0,3,3,0,0};
					int space[2] = {0,0};
					int logo[64] = {6,65535,57351,52995,53187,49379,49203,49267,49347,49267,49203,49379,53187,52995,49155,49155,51171,53235,52275,52275,53235,51171,49155,49155,53235,53235,52419,53235,50995,49155,49155,53235,53235,49347,50115,53107,52275,49155,51171,53235,52275,52275,53235,51171,49155,49155,53219,53235,49203,49203,53235,53219,49155,49155,52227,52227,53235,53235,52227,52227,57351,65535,32766};



					int skaitliukas;
					int i = 0;					// ciame kintamajame bus saugomas zodzio ilgis
					i = strlen(fraze);			//nustato zodzio ilgi ir iraso i kintamaji
					char z;		

					for(skaitliukas=0; skaitliukas < i; skaitliukas++){	//ciklas For (kintamasis; salyga; didina skaitliuka)
				
					z = fraze[skaitliukas];	//ima po viena simboli is eilutes @test 	
					//printf("\n%c",z);		//atspausdina verte

						switch(z){
							case '1':				// jei skaicius = 1, tai: vykdo zemiau esancia kodo eilute
							for (int i=0;i<10;i++){
					
								binary_counter =(nr1[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;					//butinas, (break;) nutraukia visa switch salyga(jei atitiko salyga, ivygdo uzduoti ir nutraukia )
							
							case '2':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr2[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	
							
							case '3':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr3[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	

							case '4':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr4[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	

							case '5':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr5[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	

							case '6':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr6[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	

							case '7':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr7[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	

							case '8':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr8[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	

							case '9':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr9[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	

							case '0':
							for (int i=0;i<10;i++){
					
								binary_counter =(nr0[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;
							
							case ',':
							for (int i=0;i<6;i++){
					
								binary_counter =(nrX[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;	
							case '~':
							for (int i=0;i<36;i++){
					
								binary_counter =(kmh[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;

							case ' ':
							for (int i=0;i<2;i++){
					
								binary_counter =(space[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
											
								}
							break;		
							case '!':
							for (int i=0;i<41;i++){
					
								binary_counter =(ornam[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
								}
							break;

							case '#':
							for (int i=0;i<64;i++){
					
								binary_counter =(logo[i]);
								
								//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
								SHIFT_PORT &= ~LATCH;
								spi_send((unsigned char)(binary_counter>>8));
								spi_send((unsigned char)binary_counter);
								//Toggle latch to copy data to the storage register


								SHIFT_PORT |= LATCH;
								SHIFT_PORT &= ~LATCH;
								//increment the counter for next time
								binary_counter++;
								//wait for a little bit before repeating everything
								_delay_ms(wait);
								}
							break;	

							
						}
					}
/*
					for (int i=0;i<2;i++){
					
					binary_counter =(over);
					
					//Pull LATCH low (Important: this is necessary to start the SPI transfer!)
					SHIFT_PORT &= ~LATCH;
					spi_send((unsigned char)(binary_counter>>8));
					spi_send((unsigned char)binary_counter);
					//Toggle latch to copy data to the storage register


					SHIFT_PORT |= LATCH;
					SHIFT_PORT &= ~LATCH;
					//increment the counter for next time
					binary_counter++;
					//wait for a little bit before repeating everything
					_delay_ms(1);	
					}*/
					
				}
				Pressed = 1;
			}
	}
	else
	{
	
	Pressed = 0;
	}
	}

}
