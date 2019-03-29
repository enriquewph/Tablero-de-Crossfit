#include "header.h"

/*  Ejecuta un intervalo de X segundos
    de manera ascendente o descendente
    Pitidos durante los ultimos 3 seg.
    Pitido doble al terminar la cuenta
    Retorna true si se cancelo con boton stop
    si centesimas = true, trabaja hasta 60seg unicamente, mostrando centesimas en el segundero y los segundos en los minutos.
*/



bool intervalo(uint16_t segundos, bool ascendente, bool centesimas, uint8_t pitido_final)
{
    TIMER1_SET_100HZ();

    uint16_t segs_transc = 0;

    uint16_t intervalo_segs_goal = segundos;
    uint16_t intervalo_segs_restante = 0;
    uint16_t intervalo_segs_restante_last = 0;

    bool funcionando = true;

    DISP1.dig1 = 21;
    DISP1.dig2 = 21;
    INDICADOR_SEGUNDOS = true;

    timerGoing = true;
    timerVal = 0; //Almacena la cuenta actual

    while (funcionando)
    {
        //Leer comandos
        if (IR_NewCommand())
        {
            switch (lastIRCommand)
            {
                case IRCMD_STOP:    //Detener el timer si esta andando
                    if (timerGoing)
                    {
                        timerGoing = false;
                        timerVal = 0;
                        segs_transc = 0;
                        funcionando = false;
                        return true;
                    }
                    break;
                case IRCMD_PLAYPAUSA:
                    timerGoing = !timerGoing;
                    break;
            }
        }

        //DISPLAY

        if (timerVal >= 100)
        {
            segs_transc++;
            timerVal = 0;
        }

        intervalo_segs_restante = intervalo_segs_goal - segs_transc;

        if (centesimas)
        {
            if (segundos > 60)
            {
                if (ascendente)
                {
                    DISP1.dig1 = decena(segs_transc / 60);
                    DISP1.dig2 = unidad(segs_transc / 60); 
                    DISP2.dig1 = decena(segs_transc % 60);
                    DISP2.dig2 = unidad(segs_transc % 60);
                    DISP3.dig1 = decena(timerVal);
                    DISP3.dig2 = unidad(timerVal);
                }
                else
                {
                    DISP1.dig1 = decena((intervalo_segs_restante - 1) / 60);
                    DISP1.dig2 = unidad((intervalo_segs_restante - 1) / 60);
                    DISP2.dig1 = decena((intervalo_segs_restante - 1) % 60);
                    DISP2.dig2 = unidad((intervalo_segs_restante - 1) % 60);
                    DISP3.dig1 = decena(99 - timerVal);
                    DISP3.dig2 = unidad(99 - timerVal);
                }
            }
            else
            {
                if (ascendente)
                {
                    DISP2.dig1 = decena(segs_transc);
                    DISP2.dig2 = unidad(segs_transc);
                    DISP3.dig1 = decena(timerVal);
                    DISP3.dig2 = unidad(timerVal);
                }
                else
                {
                    DISP2.dig1 = decena(intervalo_segs_restante - 1);
                    DISP2.dig2 = unidad(intervalo_segs_restante - 1);
                    DISP3.dig1 = decena(99 - timerVal);
                    DISP3.dig2 = unidad(99 - timerVal);
                }
            }
        }
        else
        {
            if (ascendente)
            {
                DISP2.dig1 = decena(segs_transc / 60);
                DISP2.dig2 = unidad(segs_transc / 60);

                DISP3.dig1 = decena(segs_transc % 60);
                DISP3.dig2 = unidad(segs_transc % 60);
            }
            else
            {
                DISP2.dig1 = decena(intervalo_segs_restante / 60);
                DISP2.dig2 = unidad(intervalo_segs_restante / 60);

                DISP3.dig1 = decena(intervalo_segs_restante % 60);
                DISP3.dig2 = unidad(intervalo_segs_restante % 60);
            }
        }

        updateLeds();

        //CONTROLAR

        if (timerGoing and intervalo_segs_restante != intervalo_segs_restante_last)
        {
            intervalo_segs_restante_last = intervalo_segs_restante;

            if (intervalo_segs_restante <= 3 and intervalo_segs_restante > 0)
            {
                tone(SPEAKER_PIN, FREQ_TONO, DUR_TONO);
            }
            else if (intervalo_segs_restante == 0) //llegó a 0
            {
                timerGoing = false;
                timerVal = 0;
                segs_transc = 0;
                funcionando = false;
                tono_finalizo(pitido_final);
            }
        }
    }

    return false; //Se ejecuto correctamente
}

void EDIT_4_DIGITS(bool dosDigitos) //si retorna TRUE, se editaron los 4 digitos y se almacenaron en las variables, si retorna FAlSE, se aborto edicion por boton power
{
    INDICADOR_SEGUNDOS = 0;
    bool EDITANDO = true;
    uint8_t numEnEdicion; // 0 NINGUNO 1 = dig1, 2 = dig2, 3 = dig3, 4 = dig4;
    if (dosDigitos)
        numEnEdicion = 3;
    else
        numEnEdicion = 1;

    while (EDITANDO)
    {
        if (IR_NewCommand())
        {
            //Leer si se presiono algun numero y guardar el digito
            uint8_t numPresionado = buscarNumPresionado(lastIRCommand);
            if (numPresionado != 10) //Ver si se presiono algun numero
            {
                switch (numEnEdicion)
                {
                    case 1:
                        if (numPresionado <= 5)
                        {
                            EDIT_4_DIGITS_NUMEROS.dig1 = numPresionado;
                            numEnEdicion++;
                        }
                        else
                            tone(SPEAKER_PIN, 1000, 50); //Tono de error
                        break;

                    case 2:
                        EDIT_4_DIGITS_NUMEROS.dig2 = numPresionado;
                        numEnEdicion++;
                        break;

                    case 3:
                        if (!dosDigitos)
                        {
                            if (numPresionado <= 5)
                            {
                                EDIT_4_DIGITS_NUMEROS.dig3 = numPresionado;
                                numEnEdicion++;
                            }
                            else
                                tone(SPEAKER_PIN, 1000, 50); //Tono de error
                        }
                        else
                        {
                            EDIT_4_DIGITS_NUMEROS.dig3 = numPresionado;
                            numEnEdicion = 4;
                        }
                        break;

                    case 4:
                        EDIT_4_DIGITS_NUMEROS.dig4 = numPresionado;
                        if (!dosDigitos)
                            numEnEdicion++;
                        else
                            numEnEdicion = 3;
                        break;

                }
            }

            //Leer por si se cambio de digito a editar
            switch (lastIRCommand)
            {
                case IRCMD_LEFT:
                    numEnEdicion--;
                    break;
                case IRCMD_RIGHT:
                    numEnEdicion++;
                    break;
            }

            if (!dosDigitos)
            {
                if (numEnEdicion > 4)
                    numEnEdicion = 1;

                if (numEnEdicion < 1)
                    numEnEdicion = 4;
            }
            else
            {
                if (numEnEdicion > 4)
                    numEnEdicion = 3;

                if (numEnEdicion < 3)
                    numEnEdicion = 4;
            }


            if (lastIRCommand == IRCMD_OK) //Se termino la edicion
            {
                EDITANDO = false;
            }
        }


        //Actualizar displays.
        DISP3_Parpadeando = false;
        DISP4_Parpadeando = false;
        DISP5_Parpadeando = false;
        DISP6_Parpadeando = false;

        switch (numEnEdicion)
        {
            case 1:
                DISP3_Parpadeando = true;
                break;
            case 2:
                DISP4_Parpadeando = true;
                break;
            case 3:
                DISP5_Parpadeando = true;
                break;
            case 4:
                DISP6_Parpadeando = true;
                break;
        }

        INDICADOR_SEGUNDOS = 0;
        if (dosDigitos)
        {
            DISP2.dig1 = 21;
            DISP2.dig2 = 21;
        }
        else
        {
            DISP2.dig1 = EDIT_4_DIGITS_NUMEROS.dig1;
            DISP2.dig2 = EDIT_4_DIGITS_NUMEROS.dig2;
        }

        DISP3.dig1 = EDIT_4_DIGITS_NUMEROS.dig3;
        DISP3.dig2 = EDIT_4_DIGITS_NUMEROS.dig4;
        updateLeds();
    }

    DISP_noBlink();
}

void FUNCION_CRONOMETRO()
{
    if (TIMER1MODE != TIMER1MODE_100HZ)
        TIMER1_SET_100HZ();

    cronometro.centesimas = timerVal;

    if (cronometro.centesimas >= 100)
    {
        cronometro.centesimas = 0;
        timerVal = 0;
        cronometro.segundos++;

        if (cronometro.segundos >= 60)
        {
            cronometro.segundos = 0;
            cronometro.minutos++;

            if (cronometro.minutos >= 99)
            {
                timerGoing = false;
            }
        }
    }

    if (IR_NEWCOMMAND_NOTPOWER)
    {
        IR_NEWCOMMAND_NOTPOWER = false;

        switch (lastIRCommand)
        {
            case IRCMD_INICIO:
                if (!timerGoing)
                {

                    cronometro.minutos = 0;
                    cronometro.segundos = 0;
                    cronometro.centesimas = 0;
                    timerVal = 0;
                    CUENTA_3SEG();
                    timerGoing = true;
                    ENPAUSA = false;
                }

                break;
            case IRCMD_STOP:
                timerGoing = false;
                ENPAUSA = false;
                break;
            case IRCMD_PLAYPAUSA:
                timerGoing = !timerGoing;
                ENPAUSA = !timerGoing;

                break;
        }
    }

    if (timerGoing or ENPAUSA)
    {
        DISP1.dig1 = decena(cronometro.minutos);
        DISP1.dig2 = unidad(cronometro.minutos);
    }
    else
    {
        DISP1.dig1 = 15;
        DISP1.dig2 = 3;
    }
    DISP2.dig1 = decena(cronometro.segundos);
    DISP2.dig2 = unidad(cronometro.segundos);
    DISP3.dig1 = decena(cronometro.centesimas);
    DISP3.dig2 = unidad(cronometro.centesimas);

    INDICADOR_SEGUNDOS = true;

    updateLeds();

}

//uint8_t RELOJ_NUMERO_EN_EDICION 0; // 0 = ninguno 1 = horas 2 = minutos 3 = segundos
void edit_hora(uint16_t IRCMD)
{
    switch (IRCMD)
    {
        case IRCMD_UP:
            RTC_updateVar(RELOJ_NUMERO_EN_EDICION, 1);
            break;
        case IRCMD_DOWN:
            RTC_updateVar(RELOJ_NUMERO_EN_EDICION, 0);
            break;
        case IRCMD_LEFT:
            if (RELOJ_NUMERO_EN_EDICION > 1)
                RELOJ_NUMERO_EN_EDICION--;
            else
                RELOJ_NUMERO_EN_EDICION = 3;
            break;
        case IRCMD_RIGHT:
            if (RELOJ_NUMERO_EN_EDICION < 3)
                RELOJ_NUMERO_EN_EDICION++;
            else
                RELOJ_NUMERO_EN_EDICION = 1;
            break;
    }

    DISP_noBlink();

    switch (RELOJ_NUMERO_EN_EDICION)
    {
        case 1:
            DISP1_Parpadeando = true;
            DISP2_Parpadeando = true;
            break;
        case 2:
            DISP3_Parpadeando = true;
            DISP4_Parpadeando = true;
            break;
        case 3:
            DISP5_Parpadeando = true;
            DISP6_Parpadeando = true;
            break;
    }
}
