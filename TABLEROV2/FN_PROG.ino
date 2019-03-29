#include "header.h"


//uint16_t fn_prog_int[6][3]; //TRABAJO - DESCANSO - SERIES
//uint16_t fn_prog_var[6][3]; //REPETICIONES - NUM SERIES - CONFIG

bool recalcularDuracion = false;

void FN_PROG(uint8_t MEM) // 0 - 5
{
    if (!FN_PROG_START)
    {
        cargarVariablesProg();
        FN_PROG_START = true;
    }

    if (IR_NEWCOMMAND_NOTPOWER)
    {
        IR_NEWCOMMAND_NOTPOWER = false;

        switch (lastIRCommand)
        {
            case IRCMD_INICIO:  //Comenzar el timer si no esta andando
                CUENTA_3SEG();
                fn_prog_funcionando = true;
                break;
            case IRCMD_OK:  //Comenzar edicion si no esta andando
                program_index++;
                recalcularDuracion = true;
                break;
            case IRCMD_ESCAPE:  //Comenzar edicion si no esta andando
                program_index = 0;
                recalcularDuracion = true;
                break;
        }
    }

    if (recalcularDuracion == true)
    {
        calcularDuracion(MEM);
        recalcularDuracion = false;
    }

    switch (program_index)
    {
        case 0:
            INDICADOR_SEGUNDOS = 1;
            DISP1.dig1 = 15;
            DISP1.dig2 = 4 + MEM;


            DISP2.dig1 = decena(fn_prog_dur / 60);
            DISP2.dig2 = unidad(fn_prog_dur / 60);
            DISP3.dig1 = decena(fn_prog_dur % 60);
            DISP3.dig2 = unidad(fn_prog_dur % 60);
            updateLeds();
            break;
        case 1: //Programar intervalo de trabajo (H1)
            DISP1.dig1 = 16;
            DISP1.dig2 = 1;

            EDIT_4_DIGITS_NUMEROS.dig1 = decena(fn_prog_int[MEM][0] / 60);
            EDIT_4_DIGITS_NUMEROS.dig2 = unidad(fn_prog_int[MEM][0] / 60);
            EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_prog_int[MEM][0] % 60);
            EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_prog_int[MEM][0] % 60);

            EDIT_4_DIGITS(false);

            fn_prog_int[MEM][0] = ((EDIT_4_DIGITS_NUMEROS.dig1 * 10) + EDIT_4_DIGITS_NUMEROS.dig2) * 60 + (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

            grabarVariablesProg();
            program_index++;
            break;

        case 2:
            DISP1.dig1 = 16;
            DISP1.dig2 = 2;

            EDIT_4_DIGITS_NUMEROS.dig1 = decena(fn_prog_int[MEM][1] / 60);
            EDIT_4_DIGITS_NUMEROS.dig2 = unidad(fn_prog_int[MEM][1] / 60);
            EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_prog_int[MEM][1] % 60);
            EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_prog_int[MEM][1] % 60);

            EDIT_4_DIGITS(false);
            fn_prog_int[MEM][1] = ((EDIT_4_DIGITS_NUMEROS.dig1 * 10) + EDIT_4_DIGITS_NUMEROS.dig2) * 60 + (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

            grabarVariablesProg();
            program_index++;
            break;

        case 3:
            DISP1.dig1 = 16;
            DISP1.dig2 = 3;

            EDIT_4_DIGITS_NUMEROS.dig1 = decena(fn_prog_int[MEM][2] / 60);
            EDIT_4_DIGITS_NUMEROS.dig2 = unidad(fn_prog_int[MEM][2] / 60);
            EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_prog_int[MEM][2] % 60);
            EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_prog_int[MEM][2] % 60);

            EDIT_4_DIGITS(false);
            fn_prog_int[MEM][2] = ((EDIT_4_DIGITS_NUMEROS.dig1 * 10) + EDIT_4_DIGITS_NUMEROS.dig2) * 60 + (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

            grabarVariablesProg();
            program_index++;
            break;

        case 4:
            DISP1.dig1 = 16;
            DISP1.dig2 = 4;

            EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_prog_var[MEM][0]);
            EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_prog_var[MEM][0]);

            EDIT_4_DIGITS(true);
            fn_prog_var[MEM][0] = (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

            grabarVariablesProg();
            program_index++;
            break;

        case 5:
            DISP1.dig1 = 16;
            DISP1.dig2 = 5;

            EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_prog_var[MEM][1]);
            EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_prog_var[MEM][1]);

            EDIT_4_DIGITS(true);
            fn_prog_var[MEM][1] = (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

            grabarVariablesProg();
            program_index++;
            break;

        case 6:
            DISP1.dig1 = 16;
            DISP1.dig2 = 6;

            EDIT_4_DIGITS_NUMEROS.dig3 = decena(fn_prog_var[MEM][2]);
            EDIT_4_DIGITS_NUMEROS.dig4 = unidad(fn_prog_var[MEM][2]);

            EDIT_4_DIGITS(true);
            fn_prog_var[MEM][2] = (EDIT_4_DIGITS_NUMEROS.dig3 * 10) + EDIT_4_DIGITS_NUMEROS.dig4;

            grabarVariablesProg();
            program_index++;
            break;
    }

    if (program_index > 6)
    {
        program_index = 0;
    }


    if (unidad(fn_prog_var[MEM][2]) > 0)
        fn_prog_cent = true;
    else
        fn_prog_cent = false;

    if (decena(fn_prog_var[MEM][2]) > 0)
        fn_prog_asc = true;
    else
        fn_prog_asc = false;

    if (fn_prog_funcionando)
        fn_prog_interv(fn_prog_int[MEM][0], fn_prog_int[MEM][1], fn_prog_int[MEM][2], fn_prog_var[MEM][0], fn_prog_var[MEM][1], fn_prog_cent, fn_prog_asc);

    fn_prog_funcionando = false;
}

void calcularDuracion(uint8_t MEM)
{
    uint16_t dur_int_trabajo = fn_prog_int[MEM][0];
    uint16_t dur_int_descanso = fn_prog_int[MEM][1];
    uint16_t dur_int_descanso_series = fn_prog_int[MEM][2];

    uint8_t repeticiones = fn_prog_var[MEM][0];
    uint8_t series = fn_prog_var[MEM][1];

    uint8_t r, s;

    fn_prog_dur = 0;

    for (s = 0; s < series; s++)
    {
        for (r = 0; r < repeticiones; r++)
        {
            fn_prog_dur += dur_int_trabajo;

            if (r != repeticiones - 1) //SI NO ES EL ULTIMO INTERVALO DE TRABAJO
            {
                fn_prog_dur += dur_int_descanso;
            }
        }
        if (s != series - 1) //SI NO ES LA ULTIMA SERIE
        {
            fn_prog_dur += dur_int_descanso_series;
        }
    }
}

void fn_prog_interv(uint16_t intTrabajo, uint16_t intDescanso, uint16_t intDescansoSeries, uint8_t repeticiones, uint8_t series, bool cent, bool ascen)
{
    uint8_t r, s;

    for (s = 0; s < series; s++)
    {
        for (r = 0; r < repeticiones; r++)
        {
            if (r != repeticiones - 1 or s != series - 1) //SI NO ES EL ULTIMO INTERVALO DE TRABAJO
            {
                if (intervalo(intTrabajo, ascen, cent, PIT_FIN_REST)) //EL PITIDO AL TERMINAR ESTE INTERVALO!
                    return;
            }
            else
            {
                if (intervalo(intTrabajo, ascen, cent, PIT_FIN_END)) //EL PITIDO AL TERMINAR ESTE INTERVALO!
                    return;
            }

            if (r != repeticiones - 1) //SI NO ES EL ULTIMO INTERVALO DE TRABAJO
            {
                if (intervalo(intDescanso, ascen, cent, PIT_FIN_WORK)) //EL PITIDO AL TERMINAR ESTE INTERVALO!
                    return;
            }
        }
        if (s != series - 1) //SI NO ES LA ULTIMA SERIE
        {
            if (intervalo(intDescansoSeries, ascen, cent, PIT_FIN_WORK)) //EL PITIDO AL TERMINAR ESTE INTERVALO!
                return;
        }
    }
}
