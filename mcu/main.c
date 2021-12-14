#include <fitkitlib.h>
#include <lcd/display.h>
#include <stdlib.h>
#include <string.h>

#define TICKS_PER_SECOND 32768 
#define SIN_SAMPLES 32    
#define SQUARE_SAMPLES 2
#define CONST_SAMPLES 1 

// Oktavy
#define C "1046"
#define D "1174"
#define E "1318"
#define F "1396"
#define G "1567"
#define A "1760"
#define H "1975"
#define B "2093"

enum SIG_ID {SIG_CONST, SIG_SQUARE} sig_type;

// pole se vzorky signalu
unsigned char arr_sin[SIN_SAMPLES] = {
   128, 153, 177, 199, 219, 234, 246, 254, 255, 254, 246, 234, 219, 199, 177,
   153, 128, 103, 79, 57, 37, 22, 10, 2, 0, 2, 10, 22, 37, 57, 79, 103
};
                 
unsigned char arr_square[SQUARE_SAMPLES] = {
  0, 255
};

unsigned char arr_const[CONST_SAMPLES] = {
  255
};

unsigned char *signal_arr = arr_sin;
int signal_arr_index = 0;   
int frequency = 100;  
unsigned char samples = SIN_SAMPLES; 
int ticks;               
unsigned char y_scale = 100;      
unsigned char char_tmp[MAX_COMMAND_LEN+1];
int defined = 1;

void set_ticks(void);

// Vypis uzivatelske napovedy (funkcia se vola pri vykonavani prikazu "help")
void print_user_help(void)
{
  term_send_str_crlf("Napoveda pro hrani melodie:");
  term_send_str_crlf("Pre zadanie tonu stisknete (C, D, E, F, G, A, H, B)");
  term_send_str_crlf("s prislusnou dlzkou tonu (1-4)");
  term_send_str_crlf("Na konci skladby pouzite flag e,");
  term_send_str_crlf("ktory sluzi na ukoncenie prehravania.");
  term_send_str_crlf("priklad (E2C2E2C2E1A1G1F1E2C2e)");
}

// Dekodovanie a vykonanie uzivatelskych prikazov
unsigned char decode_user_cmd(char *UString, char *String)
{	 
    unsigned char *msg;
    int i = 0;

    get_onechar(String, 0);
    if (strcmp1(char_tmp, "m"))  
    {
        defined = 0;
    } else {
        defined = 1;
    }

    while(1) {
        memset(char_tmp, 0, sizeof char_tmp);

        if (defined == 0) {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            // nastavenie frekvencie
            int freq_tmp = atoi(E);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(500);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(C);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(500);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(E);
            frequency = freq_tmp;
            set_ticks();

            
            delay_ms(500);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(C);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(500);

            
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(E);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(250);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(A);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(250);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(G);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(250);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(F);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(250);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(E);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(500);

            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;
            
            // nastavenie frekvencie
            freq_tmp = atoi(C);
            frequency = freq_tmp;
            set_ticks();

            delay_ms(500);
            sig_type = SIG_CONST;
            signal_arr = arr_const;
            signal_arr_index = 0;
            samples = CONST_SAMPLES;
            return USER_COMMAND;

        } else {
            get_onechar(String, i);
        }
        term_send_str_crlf("Aktualne prehrava ton");
        term_send_str_crlf(char_tmp);

        // Výber tónu
        if(strcmp1(char_tmp, "C"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            // nastavenie frekvencie
            int freq_tmp = atoi(C);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "D"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(D);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "C"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(C);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "D"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(D);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "E"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(E);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "F"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(F);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "G"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(G);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "A"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(A);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "H"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(H);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "B"))
        {
            sig_type = SIG_SQUARE;
            signal_arr = arr_square;
            signal_arr_index = 0;
            samples = SQUARE_SAMPLES;

            int freq_tmp = atoi(B);
            frequency = freq_tmp;
            set_ticks();
        }
        else if (strcmp1(char_tmp, "s")) 
        {
            sig_type = SIG_CONST;
            signal_arr = arr_const;
            signal_arr_index = 0;
            samples = CONST_SAMPLES;
        }
        else if (strcmp1(char_tmp, "e")) 
        {
            sig_type = SIG_CONST;
            signal_arr = arr_const;
            signal_arr_index = 0;
            samples = CONST_SAMPLES;
            return USER_COMMAND;
        } 
        else
        {
            term_send_str_crlf("Neznamy ton.");
            return USER_COMMAND;
        }
        get_onechar(String, i+1);

        // Nastavenie dĺžky tónu
        if (strcmp1(char_tmp, "1")) {
            delay_ms(250);
        }
        else if (strcmp1(char_tmp, "2")) {
            delay_ms(500);
        }
        else if (strcmp1(char_tmp, "3")) {
            delay_ms(750);
        }
        else if (strcmp1(char_tmp, "4")) {
            delay_ms(1000);
        } else {
        
        }
        i = i + 2;
    }
}

void fpga_initialized()
{
    LCD_init();
    LCD_append_string("Hudobny nastroj");
    LCD_send_cmd(LCD_DISPLAY_ON_OFF | LCD_DISPLAY_ON | LCD_CURSOR_OFF, 0);  // vypni kurzor

    term_send_str_crlf("Pre viac informacii (viz help).");
}

int main(void)
{
    initialize_hardware();
    WDTCTL = WDTPW + WDTHOLD;

    set_ticks();

    CCTL0 = CCIE; 
    CCR0 = ticks;
    TACTL = TASSEL_1 + MC_2; 

    ADC12CTL0 |= 0x0020;    
    DAC12_0CTL |= 0x1060; 
    DAC12_0CTL |= 0x100;    
    DAC12_0DAT = 0;        

    while (1) {
        terminal_idle(); 
    }
}

interrupt (TIMERA0_VECTOR) Timer_A (void)
{  
  if (++signal_arr_index >= samples){ signal_arr_index = 0; }
  unsigned int smpl = (signal_arr[signal_arr_index]*y_scale)/100;
  DAC12_0DAT = smpl; 
  
  CCR0 += ticks; 
}

void get_onechar(unsigned char *str, int from)
{
	int i, j = 0;
	for (i = from; i < strlen(str); i++) {
        	char_tmp[j++] = str[i]; 
            break;
    }
	char_tmp[j] = 0;
}

void set_ticks(void)
{
  ticks = TICKS_PER_SECOND / frequency / samples;
}

