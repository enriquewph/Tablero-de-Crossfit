#include "header.h"



uint8_t buscarNumPresionado(uint8_t tecla)    //retorna 10 si no se presiono un numero
{
    switch (tecla)
    {
        case IRCMD_NUM0:    return  0;
        case IRCMD_NUM1:    return  1;
        case IRCMD_NUM2:    return  2;
        case IRCMD_NUM3:    return  3;
        case IRCMD_NUM4:    return  4;
        case IRCMD_NUM5:    return  5;
        case IRCMD_NUM6:    return  6;
        case IRCMD_NUM7:    return  7;
        case IRCMD_NUM8:    return  8;
        case IRCMD_NUM9:    return  9;
        default:            return 10;
    }
}


void CUENTA_3SEG()
{
    INDICADOR_SEGUNDOS = 0;
    DISP1.dig1 = 21;
    DISP1.dig2 = 21;
    DISP2.dig1 = 21;
    DISP2.dig2 = 21;
    DISP3.dig1 = 21;


    DISP3.dig2 = 5;
    updateLeds();

    delay(1000);

    DISP3.dig2 = 4;
    updateLeds();

    delay(1000);

    DISP3.dig2 = 3;
    updateLeds();

    tone(SPEAKER_PIN, FREQ_TONO);
    delay(DUR_TONO);
    noTone(SPEAKER_PIN);

    delay(1000 - DUR_TONO);

    DISP3.dig2 = 2;
    updateLeds();

    tone(SPEAKER_PIN, FREQ_TONO);
    delay(DUR_TONO);
    noTone(SPEAKER_PIN);

    delay(1000 - DUR_TONO);

    DISP3.dig2 = 1;
    updateLeds();

    tone(SPEAKER_PIN, FREQ_TONO);
    delay(DUR_TONO);
    noTone(SPEAKER_PIN);

    delay(1000 - DUR_TONO);


    DISP1.dig1 = 0;
    DISP1.dig2 = 0;
    DISP2.dig1 = 0;
    DISP2.dig2 = 0;
    DISP3.dig1 = 0;
    DISP3.dig2 = 0;
    INDICADOR_SEGUNDOS = 1;
    updateLeds();

    tone(SPEAKER_PIN, FREQ_TONO);
    delay(DUR_TONO_F);
    noTone(SPEAKER_PIN);
}



void tono_finalizo(uint8_t pitido_final)
{

    if (pitido_final == PIT_FIN_WORK)
    {
        DISP1.dig1 = 22;
        DISP1.dig2 = 22;
        DISP2.dig1 = 22;
        DISP2.dig2 = 22;
        DISP3.dig1 = 22;
        DISP3.dig2 = 22;
        INDICADOR_SEGUNDOS = 0;
        updateLeds();
        tone(SPEAKER_PIN, FREQ_TONO);
        delay(200);
        noTone(SPEAKER_PIN);
        delay(100);
        tone(SPEAKER_PIN, FREQ_TONO);
        delay(200);
        noTone(SPEAKER_PIN);
    }
    else if (pitido_final == PIT_FIN_REST)
    {
        DISP1.dig1 = 23;
        DISP1.dig2 = 24;
        DISP2.dig1 = 24;
        DISP2.dig2 = 24;
        DISP3.dig1 = 24;
        DISP3.dig2 = 25;
        INDICADOR_SEGUNDOS = 0;
        updateLeds();
        tone(SPEAKER_PIN, FREQ_TONO);
        delay(200);
        noTone(SPEAKER_PIN);
        delay(100);
        tone(SPEAKER_PIN, FREQ_TONO);
        delay(600);
        noTone(SPEAKER_PIN);
    }
    else if (pitido_final == PIT_FIN_END)
    {
        DISP1.dig1 = 21;
        DISP1.dig2 = 21;
        DISP2.dig1 = 21;
        DISP2.dig2 = 14;
        DISP3.dig1 = 19;
        DISP3.dig2 = 13;
        INDICADOR_SEGUNDOS = 0;
        updateLeds();
        tone(SPEAKER_PIN, FREQ_TONO);
        delay(200);
        noTone(SPEAKER_PIN);
        delay(100);
        tone(SPEAKER_PIN, FREQ_TONO);
        delay(200);
        noTone(SPEAKER_PIN);
        delay(100);
        tone(SPEAKER_PIN, FREQ_TONO);
        delay(500);
        noTone(SPEAKER_PIN);
    }
}

void system_init()
{
    pinMode(DHT11_DATA_PIN, INPUT);
    pinMode(IR_RECEIVER_DATA_PIN, INPUT);
    pinMode(INDICADOR_SEGUNDOS_PIN, OUTPUT);
    pinMode(SPEAKER_PIN, OUTPUT);
    pinMode(SPI_LATCH_PIN, OUTPUT);
    pinMode(SPI_SCK_PIN, OUTPUT);
    pinMode(SPI_MOSI_PIN, OUTPUT);

    digitalWrite(INDICADOR_SEGUNDOS_PIN, LOW);
    digitalWrite(SPEAKER_PIN, LOW);
    digitalWrite(SPI_LATCH_PIN, LOW);
    digitalWrite(SPI_SCK_PIN, LOW);
    digitalWrite(SPI_MOSI_PIN, LOW);
}

void apagarParlante()
{
    noTone(SPEAKER_PIN);
}

uint8_t unidad(uint8_t variable)
{
    uint8_t a = variable % 10;
    return (a);
}

uint8_t decena(uint8_t variable)
{
    uint8_t a = (variable % 100) / 10;
    return (a);
}

uint8_t minutos(uint16_t variable)
{
    uint8_t a = variable / 60;
    return (a);
}

uint8_t segundos(uint16_t variable)
{
    uint8_t a = variable % 60;
    return (a);
}



void TIMER1_SET_1HZ()
{
    TIMER1MODE = TIMER1MODE_1HZ;
    // TIMER 1 for interrupt frequency 1 Hz:
    cli(); // stop interrupts
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 1 Hz increments
    OCR1A = 62499; // = 16000000 / (256 * 1) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 256 prescaler
    TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts
}
void TIMER1_SET_10HZ()
{
    TIMER1MODE = TIMER1MODE_10HZ;
    // TIMER 1 for interrupt frequency 10 Hz:
    cli(); // stop interrupts
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 10 Hz increments
    OCR1A = 24999; // = 16000000 / (64 * 10) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 64 prescaler
    TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts
}


void TIMER1_SET_100HZ()
{
    TIMER1MODE = TIMER1MODE_100HZ;
    // TIMER 1 for interrupt frequency 100 Hz:
    cli(); // stop interrupts
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 100 Hz increments
    OCR1A = 19999; // = 16000000 / (8 * 100) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 8 prescaler
    TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts
}
