#include "header.h"

bool fgb_funcionando = false;

void FUNCION_FIGHT_GONE_BAD()
{
    INDICADOR_SEGUNDOS = 0;
    DISP1.dig1 = 15;
    DISP1.dig2 = 1;
    DISP2.dig1 = 1;
    DISP2.dig2 = 8;
    DISP3.dig1 = 0;
    DISP3.dig2 = 0;
    updateLeds();

    if (IR_NEWCOMMAND_NOTPOWER && lastIRCommand == IRCMD_INICIO)
    {
        IR_NEWCOMMAND_NOTPOWER = false;
        CUENTA_3SEG();
        fgb_funcionando = true;
    }

    if (fgb_funcionando)
        fgb_interv();

    fgb_funcionando = false;
}

void fgb_interv() //Si retorna true, se paro la ejecucion
{
    //bool intervalo(uint16_t segundos, bool ascendente, bool centesimas)
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_END))
        return;
    if (intervalo(60, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_END))
        return;
    if (intervalo(60, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_REST))
        return;
    if (intervalo(5, false, true, PIT_FIN_WORK))
        return;
    if (intervalo(60, false, true, PIT_FIN_END))
        return;


}
