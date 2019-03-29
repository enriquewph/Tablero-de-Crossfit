#include "header.h"




void FUNCION_UP()
{

    if (setup_funcion) //solo se ejecuta una vez
    {
        if (TIMER1MODE != TIMER1MODE_1HZ)
            TIMER1_SET_1HZ();

        timerGoing = false;
        timerVal = 0; //Almacena la cuenta actual

        EDIT_4_DIGITS_NUMEROS.dig1 = 0;
        EDIT_4_DIGITS_NUMEROS.dig2 = 0;
        EDIT_4_DIGITS_NUMEROS.dig3 = 0;
        EDIT_4_DIGITS_NUMEROS.dig4 = 0;
        
        fn_up_minutos =   EEPROM.read(EEPROM_ADDRESS_UPTIME);
        fn_up_segundos =  EEPROM.read(EEPROM_ADDRESS_UPTIME + 1);
        
        fn_up_cuenta_goal_seg = fn_up_minutos * 60 + fn_up_segundos;

        setup_funcion = false;
    }

    if (IR_NEWCOMMAND_NOTPOWER)
    {
        IR_NEWCOMMAND_NOTPOWER = false;

        switch (lastIRCommand)
        {
            case IRCMD_INICIO:  //Comenzar el timer si no esta andando
                if (!timerGoing)
                {
                    if (fn_up_cuenta_goal_seg < 10)
                        fn_up_cuenta_goal_seg = 10;
                    CUENTA_3SEG();
                    timerVal = 0;
                    timerGoing = true;
                    ENPAUSA = false;
                }
                break;
            case IRCMD_STOP:    //Detener el timer si esta andando
                if (timerGoing)
                {
                    timerGoing = false;
                    ENPAUSA = false;
                    timerVal = 0;
                }
                break;

            case IRCMD_PLAYPAUSA:
                if (!timerGoing)
                {
                    CUENTA_3SEG();
                    timerGoing = true;
                    ENPAUSA = false;
                }
                else
                {
                    timerGoing = false;
                    ENPAUSA = true;
                }
                break;

            case IRCMD_ESCAPE:  //Reiniciar config
                setup_funcion = true;
                break;
            case IRCMD_OK:  //Comenzar edicion si no esta andando
                if (!timerGoing)
                {
                    EDIT_4_DIGITS_NUMEROS.dig1 = decena(fn_up_minutos);
                    EDIT_4_DIGITS_NUMEROS.dig2 = unidad(fn_up_minutos);
                    EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_up_segundos);
                    EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_up_segundos);
                    
                    EDIT_4_DIGITS(false);
                    
                    fn_up_minutos = (EDIT_4_DIGITS_NUMEROS.dig1 * 10) + EDIT_4_DIGITS_NUMEROS.dig2;
                    fn_up_segundos = (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

                    fn_up_cuenta_goal_seg = fn_up_minutos * 60 + fn_up_segundos;

                    EEPROM.write(EEPROM_ADDRESS_UPTIME, fn_up_minutos);
                    EEPROM.write(EEPROM_ADDRESS_UPTIME + 1, fn_up_segundos);

                }
                break;
        }
    }

    //DISPLAY

    INDICADOR_SEGUNDOS = true;
    if (timerGoing or ENPAUSA)
    {
        DISP1.dig1 = 21;
        DISP1.dig2 = 21;
        DISP2.dig1 = decena(minutos(timerVal));
        DISP2.dig2 = unidad(minutos(timerVal));
        DISP3.dig1 = decena(segundos(timerVal));
        DISP3.dig2 = unidad(segundos(timerVal));
    }
    else
    {
        DISP1.dig1 = 17;
        DISP1.dig2 = 18;
        DISP2.dig1 = decena(fn_up_minutos);
        DISP2.dig2 = unidad(fn_up_minutos);
        DISP3.dig1 = decena(fn_up_segundos);
        DISP3.dig2 = unidad(fn_up_segundos);
    }

    updateLeds();


    //CONTROLAR
    segRestantes = fn_up_cuenta_goal_seg - timerVal;

    if (timerGoing and segRestantes != segRestantes_last)
    {
        segRestantes_last = segRestantes;

        if (segRestantes <= 3 and segRestantes > 0)
        {
            tone(SPEAKER_PIN, FREQ_TONO, DUR_TONO);
        }
        else if (segRestantes == 0) //llegó a 0
        {
            timerGoing = false;
            timerVal = 0;
            tono_finalizo(PIT_FIN_END);
        }
    }

}





void FUNCION_DOWN()
{

    if (setup_funcion) //solo se ejecuta una vez
    {
        if (TIMER1MODE != TIMER1MODE_1HZ)
            TIMER1_SET_1HZ();

        timerGoing = false;
        timerVal = 0; //Almacena la cuenta actual

        EDIT_4_DIGITS_NUMEROS.dig1 = 0;
        EDIT_4_DIGITS_NUMEROS.dig2 = 0;
        EDIT_4_DIGITS_NUMEROS.dig3 = 0;
        EDIT_4_DIGITS_NUMEROS.dig4 = 0;
        
        fn_down_minutos =   EEPROM.read(EEPROM_ADDRESS_DNTIME);
        fn_down_segundos =  EEPROM.read(EEPROM_ADDRESS_DNTIME + 1);
        
        fn_down_cuenta_goal_seg = fn_down_minutos * 60 + fn_down_segundos;

        setup_funcion = false;
    }

    if (IR_NEWCOMMAND_NOTPOWER)
    {
        IR_NEWCOMMAND_NOTPOWER = false;

        switch (lastIRCommand)
        {
            case IRCMD_INICIO:  //Comenzar el timer si no esta andando
                if (!timerGoing)
                {
                    if (fn_down_cuenta_goal_seg < 10)
                        fn_down_cuenta_goal_seg = 10;
                    CUENTA_3SEG();
                    timerVal = 0;
                    timerGoing = true;
                    ENPAUSA = false;
                }
                break;
            case IRCMD_STOP:    //Detener el timer si esta andando
                if (timerGoing)
                {
                    timerGoing = false;
                    ENPAUSA = false;
                    timerVal = 0;
                }
                break;

            case IRCMD_PLAYPAUSA:
                if (!timerGoing)
                {
                    CUENTA_3SEG();
                    timerGoing = true;
                    ENPAUSA = false;
                }
                else
                {
                    timerGoing = false;
                    ENPAUSA = true;
                }
                break;

            case IRCMD_ESCAPE:  //Reiniciar config
                setup_funcion = true;
                break;
            case IRCMD_OK:  //Comenzar edicion si no esta andando
                if (!timerGoing)
                {
                    EDIT_4_DIGITS_NUMEROS.dig1 = decena(fn_down_minutos);
                    EDIT_4_DIGITS_NUMEROS.dig2 = unidad(fn_down_minutos);
                    EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_down_segundos);
                    EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_down_segundos);
                    
                    EDIT_4_DIGITS(false);
                    
                    fn_down_minutos = (EDIT_4_DIGITS_NUMEROS.dig1 * 10) + EDIT_4_DIGITS_NUMEROS.dig2;
                    fn_down_segundos = (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

                    fn_down_cuenta_goal_seg = fn_down_minutos * 60 + fn_down_segundos;

                    EEPROM.write(EEPROM_ADDRESS_DNTIME, fn_down_minutos);
                    EEPROM.write(EEPROM_ADDRESS_DNTIME + 1, fn_down_segundos);
                }
                break;
        }
    }

    segRestantes = fn_down_cuenta_goal_seg - timerVal;

    //DISPLAY

    INDICADOR_SEGUNDOS = true;
    if (timerGoing or ENPAUSA)
    {
        DISP1.dig1 = 21;
        DISP1.dig2 = 21;
        DISP2.dig1 = decena(minutos(segRestantes));
        DISP2.dig2 = unidad(minutos(segRestantes));
        DISP3.dig1 = decena(segundos(segRestantes));
        DISP3.dig2 = unidad(segundos(segRestantes));
    }
    else
    {
        DISP1.dig1 = 13;
        DISP1.dig2 = 19;
        DISP2.dig1 = decena(fn_down_minutos);
        DISP2.dig2 = unidad(fn_down_minutos);
        DISP3.dig1 = decena(fn_down_segundos);
        DISP3.dig2 = unidad(fn_down_segundos);
    }

    updateLeds();


    //CONTROLAR


    if (timerGoing and segRestantes != segRestantes_last)
    {
        segRestantes_last = segRestantes;

        if (segRestantes <= 3 and segRestantes > 0)
        {
            tone(SPEAKER_PIN, FREQ_TONO, DUR_TONO);
        }
        else if (segRestantes == 0) //llegó a 0
        {
            timerGoing = false;
            timerVal = 0;
            tono_finalizo(PIT_FIN_END);
        }
    }

}
