#define BTNSMPDELAY 5

sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;


int val = 255; // out of the range of the keyboard
int oldVal;
int textCurX = 1;
int textCurY = 1;



char numText[16];
int numLen;
char smsText[160] = {' '};
int smsLen = 0;

int cellTimeout;
int keyIndex;
char finalInput;
int firstIter;

char keyVal_0[] = "0";
char keyVal_1[] = ".,?1";
char keyVal_2[] = "abcABC2";
char keyVal_3[] = "defDEF3";
char keyVal_4[] = "ghiGHI4";
char keyVal_5[] = "jklJKL5";
char keyVal_6[] = "mnoMNO6";
char keyVal_7[] = "pqrsPQRS7";

char keyVal_8[] = "tuvTUV8";
char keyVal_9[] = "wxyzWXYZ9";
char keyVal_a[] = "@";
char keyVal_b[] = "#";
char keyVal_c[] = "$";
char keyVal_d[] = "%";
char keyVal_e[] = " ";
char keyVal_f[] = "&";


void sendSMS()
{
	int i;

        UART1_Write_Text("ATE0\r\n");
	delay_ms(1000);
        UART1_Write_Text("AT\r\n");
        delay_ms(1000);
        UART1_Write_Text("AT+CMGF = 1\r\n");
        delay_ms(1000);
        UART1_Write_Text("AT+CNMI=1,2,0,0,0\r\n");
        delay_ms(1000);
        UART1_Write_Text("AT+CMGS=\"+92"); // replace 92 with your country code (or prefix)

	for (i=0; i<numLen; ++i) {
		UART1_Write(numText[i]);
	}
	UART1_Write_Text("\"\r\n");
	
        delay_ms(500);

	for (i=0; i<smsLen; ++i) {
		UART1_Write(smsText[i]);
	}
        UART1_Write_text("\r\n");
        
        UART1_Write(26);
}


char finalInput_phoneNum(int val) {
	return val+48;
}

char finalInput_compose(int val) {
	char toReturn;

	switch (val) {
		case 0:
		toReturn=keyVal_0[keyIndex];
		keyIndex = (keyIndex + 1) % 1;
		break;

		case 1:
		toReturn=keyVal_1[keyIndex];
		keyIndex = (keyIndex + 1) % 4;
		break;

		case 2:
		toReturn=keyVal_2[keyIndex];
		keyIndex = (keyIndex + 1) % 7;
		break;

		case 3:
		toReturn=keyVal_3[keyIndex];
		keyIndex = (keyIndex + 1) % 7;
		break;

		case 4:
		toReturn=keyVal_4[keyIndex];
		keyIndex = (keyIndex + 1) % 7;
		break;

		case 5:
		toReturn=keyVal_5[keyIndex];
		keyIndex = (keyIndex + 1) % 7;
		break;

		case 6:
		toReturn=keyVal_6[keyIndex];
		keyIndex = (keyIndex + 1) % 7;
		break;

		case 7:
		toReturn=keyVal_7[keyIndex];
		keyIndex = (keyIndex + 1) % 9;
		break;

		case 8:
		toReturn=keyVal_8[keyIndex];
		keyIndex = (keyIndex + 1) % 7;
		break;

		case 9:
		toReturn=keyVal_9[keyIndex];
		keyIndex = (keyIndex + 1) % 9;
		break;

		case 10:
		toReturn=keyVal_a[keyIndex];
		keyIndex = (keyIndex + 1) % 1;
		break;
/*
		case 11:
		toReturn=keyVal_b[keyIndex];
		keyIndex = (keyIndex + 1) % 1;
		break;

		case 12:
		toReturn=keyVal_c[keyIndex];
		keyIndex = (keyIndex + 1) % 1;
		break;

		case 13:
		toReturn=keyVal_d[keyIndex];
		keyIndex = (keyIndex + 1) % 1;
		break;

		case 14:
		toReturn=keyVal_e[keyIndex];
		keyIndex = (keyIndex + 1) % 1;
		break;

		case 15:
		toReturn=keyVal_f[keyIndex];
		keyIndex = (keyIndex + 1) % 1;
		break;
		*/
	}
	return toReturn;
}

void interrupt() {
	if (TMR0IF_bit) {
		TMR0IF_bit = 0;
		TMR0H = 0xE1;
		TMR0L = 0x7A;

		cellTimeout = 1;
	}
}

void resetTimer() {
	TMR0H = 0xE1;
	TMR0L = 0x7A;
	cellTimeout = 0;
}

short readKeypad() {
	short i;
	short press = 1;
	short sample[16] = {0};

	PORTD = 128;

	for (i=0; i < 4; ++i) {
		if (RD0_bit) {
			++sample[10];
		}
		if (RD1_bit) {
			++sample[3];
		}
		if (RD2_bit) {
			++sample[2];
		}
		if (RD3_bit) {
			++sample[1];
		}
		delay_ms(BTNSMPDELAY);
	}

	PORTD = 64;

	for (i=0; i < 4; ++i) {
		if (RD0_bit) {
			++sample[11];
		}
		if (RD1_bit) {
			++sample[6];
		}
		if (RD2_bit) {
			++sample[5];
		}
		if (RD3_bit) {
			++sample[4];
		}
		delay_ms(BTNSMPDELAY);
	}

	PORTD = 32;

	for (i=0; i < 4; ++i) {
		if (RD0_bit) {
			++sample[12];
		}
		if (RD1_bit) {
			++sample[9];
		}
		if (RD2_bit) {
			++sample[8];
		}
		if (RD3_bit) {
			++sample[7];
		}
		delay_ms(BTNSMPDELAY);
	}

	PORTD = 16;

	for (i=0; i < 4; ++i) {
		if (RD0_bit) {
			++sample[13];
		}
		if (RD1_bit) {
			++sample[14];
		}
		if (RD2_bit) {
			++sample[0];
		}
		if (RD3_bit) {
			++sample[15];
		}
		delay_ms(BTNSMPDELAY);
	}

	for (i=0; i < 16; ++i) {
		if (sample[i] > 2) {
			val = i;
			press = 0;
		}
	}

	return press;
}

void incrCursor() {
	++textCurX;
	if (textCurX > 16) {
		textCurX = (textCurX % 16);
		++textCurY;
	}
}

void main() {
	char number[8];
	int num=0;
	int i;

	int optionSelect=255;

	/**** PRELIM ****/
	OSCCON.IRCF0=1;
	OSCCON.IRCF1=0;
	OSCCON.IRCF2=1;

	ANSELA=0;
	ANSELB=0;
	ANSELC=0;
	ANSELD=0;
	ANSELE=0;

	TRISD = 0x0F;
	/**** END PRELIM ****/

	/**** TIMER CONFIG ****/
	TMR0H = 0xE1;
	TMR0L = 0x7A;
	T0CON = 0b10000111;
	GIE_bit = 1;
	TMR0IE_bit = 1;
	/**** TIMER CONFIG ****/

	UART1_Init(9600);
	//UART2_Init(4800);               // Initialize UART module at 9600 bps
	Delay_ms(100);                  // Wait for UART module to stabilize

/*
	UART1_Write_Text("Start");
	UART1_Write(10);
	UART1_Write(13);
*/

	Lcd_Init();
	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Cmd(_LCD_CURSOR_OFF);

	Lcd_Out(1,1,"PIC Messenger");
	Lcd_Out(2,6,"v 1.0");

	delay_ms(2000);

	while (1) {
		Lcd_Cmd(_LCD_CLEAR);
		Lcd_Out(1,1,"1. Send Message");
		Lcd_Out(2,1,"2. Send Location");

		while(readKeypad() || !(val==1 || val==2));
		optionSelect=val;

		Lcd_Cmd(_LCD_CLEAR);
		Lcd_Out(1,1,"Enter Number:");

		// READ THE NUMBER FROM THE USER
		numLen=0;
		while (numLen < 16) {
			while (readKeypad() || (val > 11));

			if (val < 10) {
				finalInput=finalInput_phoneNum(val);
				numText[numLen]=finalInput;
				++numLen;
				Lcd_Chr(2,numLen,finalInput);
			}
			else if (val==10){
				if (numLen > 0) {
					Lcd_Chr(2,numLen,' ');
					--numLen;
				}
			}
			else if (val==11){
				break;
			}
		}
		// END READ NUMBER

		if (optionSelect==1) {
			Lcd_Cmd(_LCD_CLEAR);
			Lcd_Out(1,1,"Type Message:");


			// START READING MESSAGE
			smsLen=0;
			while (smsLen < 32) { // keep running until user is done


				firstIter=1;
				while (1) { // keep running for one cell
					if (firstIter) {
						keyIndex=0;
						while(readKeypad()); // first read
						finalInput=finalInput_compose(val);
						smsText[smsLen]=finalInput;
						Lcd_Chr(textCurY,textCurX,finalInput);
					}
					firstIter=0;

					oldVal = val;
					resetTimer();

					while(readKeypad());

					if (!cellTimeout && oldVal==val) {
						finalInput=finalInput_compose(val);
						smsText[smsLen]=finalInput;

						Lcd_Chr(textCurY,textCurX,finalInput);
					}
					else {
						break;
					}

				}
				incrCursor();

				if (smsText[smsLen]=='@') {
					break;
				}

				++smsLen;
			}

			// END READING MESSAGE

			Lcd_Cmd(_LCD_CLEAR);
			Lcd_Out(1,1,"Sending Message . . .");

			sendSMS();

			Lcd_Cmd(_LCD_CLEAR);
			Lcd_Out(1,1,"Message Sent!");
		}
		else if (optionSelect==2) {
			Lcd_Cmd(_LCD_CLEAR);
			Lcd_Out(1,1,"Fetching GPS...");
		}

		delay_ms(3000);
	}

	while(1);
}
