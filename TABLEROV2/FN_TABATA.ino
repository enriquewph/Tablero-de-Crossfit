#include "header.h"


bool ftb_funcionando = false;

uint16_t duracion_ejerc_tabata = 0;
void FUNCION_TABATA()
{
    INDICADOR_SEGUNDOS = 0;
    DISP1.dig1 = 15;
    DISP1.dig2 = 2;
    DISP2.dig1 = decena(duracion_ejerc_tabata / 60);
    DISP2.dig2 = unidad(duracion_ejerc_tabata / 60);
    DISP3.dig1 = decena(duracion_ejerc_tabata % 60);
    DISP3.dig2 = unidad(duracion_ejerc_tabata % 60);
    
    fn_tb_tabatas = EEPROM.read(EEPROM_ADDRESS_TABATAS);
    
    updateLeds();

    if (IR_NEWCOMMAND_NOTPOWER)
    {
        IR_NEWCOMMAND_NOTPOWER = false;

        switch (lastIRCommand)
        {
            case IRCMD_INICIO:  //Comenzar el timer si no esta andando
                CUENTA_3SEG();
                ftb_funcionando = true;
                break;

            case IRCMD_OK:  //Comenzar edicion si no esta andando
                if (!timerGoing)
                {
                    INDICADOR_SEGUNDOS = 0;
                    DISP1.dig1 = 16;
                    DISP1.dig2 = 1;

                    EDIT_4_DIGITS(true);

                    fn_tb_tabatas = (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;
                    
                    EEPROM.write(EEPROM_ADDRESS_TABATAS, fn_tb_tabatas);
                    
                }
                break;
        }
    }

    if (fn_tb_tabatas == 0)
    {
        fn_tb_tabatas = 1;
    }

    duracion_ejerc_tabata = 230 * fn_tb_tabatas + (fn_tb_tabatas - 1) * 60;

    if (ftb_funcionando)
        ftb_interv();

    ftb_funcionando = false;
}

void ftb_interv()
{
    uint8_t i, t;

    for (t = 0; t < fn_tb_tabatas; t++)
    {
        for (i = 0; i < 8; i++)
        {
            if (t != fn_tb_tabatas - 1)
            {
                if (intervalo(20, true, true, PIT_FIN_REST))
                    return;
            }
            else
            {
                if (intervalo(20, true, true, PIT_FIN_END))
                    return;
            }
            
            if (i != 7)
            {
                if (intervalo(10, true, true, PIT_FIN_WORK))
                    return;
            }
        }
        if (t != fn_tb_tabatas - 1)
            if (intervalo(60, true, true, PIT_FIN_WORK))
                return;
    }
}
