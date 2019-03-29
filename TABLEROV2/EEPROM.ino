#include "header.h"

//uint16_t fn_prog_var[6][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

//EEPROM ADDRESSES



void grabarVariablesProg()
{
    uint16_t addressActual = EEPROM_ADDRESS_PROG1;

    uint8_t i, k, minut,segs;

    for (i = 0; i < 5; i++)
    {
        for (k = 0; k < 3; k++)
        {
            addressActual++;
            minut =   fn_prog_int[i][k] / 60;       EEPROM.write(addressActual, minut);
            addressActual++;
            segs =  fn_prog_int[i][k] % 60;  EEPROM.write(addressActual, segs);
        }
    }

    for (i = 0; i < 5; i++)
    {
        for (k = 0; k < 3; k++)
        {
            addressActual++;
            EEPROM.write(addressActual, fn_prog_var[i][k]);
        }
    }

}
void EEPROM_CLEAR()
{
    for (int i = 0 ; i < EEPROM.length() ; i++)
    {
        EEPROM.write(i, 0);
    }
}

void cargarVariablesProg()
{
    uint16_t addressActual = EEPROM_ADDRESS_PROG1;

    uint8_t i, k, minut,segs;

    for (i = 0; i < 5; i++)
    {
        for (k = 0; k < 3; k++)
        {
            addressActual++;
            minut =   EEPROM.read(addressActual);
            addressActual++;
            segs =  EEPROM.read(addressActual);
            fn_prog_int[i][k] = minut * 60 + segs;
        }
    }

    for (i = 0; i < 5; i++)
    {
        for (k = 0; k < 3; k++)
        {
            addressActual++;
            fn_prog_var[i][k] =  EEPROM.read(addressActual);
        }
    }
}
