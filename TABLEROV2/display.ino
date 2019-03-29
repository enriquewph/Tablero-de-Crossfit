#include "header.h"

void DISP_noBlink()
{
    DISP1_Parpadeando = false;
    DISP2_Parpadeando = false;
    DISP3_Parpadeando = false;
    DISP4_Parpadeando = false;
    DISP5_Parpadeando = false;
    DISP6_Parpadeando = false;
}

uint8_t codBCD[] = { 63,  6, 91, 79, 102, 109, 125,  7, 127, 103, 119, 124, 57, 94, 121, 113, 118, 62, 115, 84, 99, 0,  64, 57, 9, 15};

//                    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  A,  b,  C,  d,  E,  F,  H,  U,  P,  n,  º, blank, -, [, _, ]
//                    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25

void updateLeds()   //SIEMPRE ACTUALIZAR DISP1,2,3 ANTES DE LLAMAR!
{
    if (millis() - lastMillis_hora_blink >= 500U)
    {
        lastMillis_hora_blink = millis();
        DISP_Parpadeando_onOff = !DISP_Parpadeando_onOff;
    }

    
    if (!DISP_Parpadeando_onOff)
    {
        if (DISP1_Parpadeando)
            DISP1.dig1 = 21;
        if (DISP2_Parpadeando)
            DISP1.dig2 = 21;
        if (DISP3_Parpadeando)
            DISP2.dig1 = 21;
        if (DISP4_Parpadeando)
            DISP2.dig2 = 21;
        if (DISP5_Parpadeando)
            DISP3.dig1 = 21;
        if (DISP6_Parpadeando)
            DISP3.dig2 = 21;
    }

    digitalWrite(SPI_LATCH_PIN, LOW);
    sfOut(codBCD[DISP1.dig1]);
    sfOut(codBCD[DISP1.dig2]);
    sfOut(codBCD[DISP2.dig1]);
    sfOut(codBCD[DISP2.dig2]);
    sfOut(codBCD[DISP3.dig1]);
    sfOut(codBCD[DISP3.dig2]);

    digitalWrite(SPI_LATCH_PIN, HIGH);
    delay(5);

    digitalWrite(INDICADOR_SEGUNDOS_PIN, INDICADOR_SEGUNDOS);
}


void sfOut(uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        digitalWrite(SPI_MOSI_PIN, !!(val & (1 << (7 - i))));
        delayMicroseconds(1);
        digitalWrite(SPI_SCK_PIN, HIGH);
        delayMicroseconds(1);
        digitalWrite(SPI_SCK_PIN, LOW);
    }
}
