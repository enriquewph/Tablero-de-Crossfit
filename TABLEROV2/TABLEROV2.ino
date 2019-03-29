#include "header.h"
//Iniciar lcd
//LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
    // put your setup code here, to run once:
    system_init();
    Wire.begin();

    DHT_init();
    IR_init();

    //Serial.begin(9600);
    //lcd.begin(20, 4);
    TIMER1_SET_100HZ();
    cargarVariablesProg();

}

void loop()
{
    mainMenu();
}

ISR(TIMER1_COMPA_vect)
{
    if (timerGoing)
        timerVal++;
}

uint8_t index_1 = 0;
uint8_t index_2 = 0;
uint8_t index_3 = 0;
unsigned long lastMillis_hora = 0;
unsigned long lastMillis_hora_read = 0;
unsigned long lastMillis_hora_blink = 0;
uint16_t siguienteIntervalo = TIEMPO_MOSTRAR_HORA;

void mainMenu()
{
    switch (index_1)
    {
        case 0:
            modoApagado();
            break;
        case 1:
            modoReloj();
            break;
        case 2:
            modoTimer();
            break;
    }
}

void modoTimer()
{
    if (IR_NewCommand() == 1)
    {
        if (lastIRCommand == IRCMD_POWER) //Si el comando es el boton de power, index_1++
        {
            index_1 = 0;
            index_2 = 0;
            cronometro_funcionando = false;
            cronometro.minutos = 0;
            cronometro.segundos = 0;
            cronometro.centesimas = 0;
        }
        else if (lastIRCommand == IRCMD_FN) //Cambiar de funcion
        {
            FN_PROG_START = false;
            index_2++;
            setup_funcion = true;
            if (index_2 > 10)
                index_2 = 0;
        }
        else
        {
            IR_NEWCOMMAND_NOTPOWER = true; //setear a false al atender
        }
    }
    //Modo timer
    switch (index_2)
    {
        case 0:
            //Funcion UP
            FUNCION_UP();
            break;
        case 1:
            //Funcion DOWN
            FUNCION_DOWN();
            break;
        case 2:
            //Funcion FIGHT GONE BAD F1
            FUNCION_FIGHT_GONE_BAD();
            break;
        case 3:
            //Funcion TABATA F2
            FUNCION_TABATA();
            break;
        case 4:
            //Funcion CRONOMETRO F3
            FUNCION_CRONOMETRO();
            break;
        case 5:
            //Funcion PROGRAMABLE #1 F4
            FN_PROG(0);
            break;
        case 6:
            //Funcion PROGRAMABLE #2 F5
            FN_PROG(1);
            break;
        case 7:
            //Funcion PROGRAMABLE #3 F6
            FN_PROG(2);
            break;
        case 8:
            //Funcion PROGRAMABLE #4 F7
            FN_PROG(3);
            break;
        case 9:
            //Funcion PROGRAMABLE #4 F8
            FN_PROG(4);
            break;
        case 10:
            //Funcion PROGRAMABLE #4 F9
            FN_PROG(5);
            break;
    }
}

void modoApagado()
{
    //Sistema apagado
    /*
        Apagar displays
        Apagar parlantes
    */
    //Apagar todo
    apagarParlante();
    INDICADOR_SEGUNDOS = false;
    DISP1.dig1 = 21;
    DISP1.dig2 = 21;
    DISP2.dig1 = 21;
    DISP2.dig2 = 21;
    DISP3.dig1 = 21;
    DISP3.dig2 = 21;
    updateLeds();

    //Poner el sistema en espera

    if (IR_NewCommand() == 1)
    {
        if (lastIRCommand == IRCMD_POWER) //Si el comando es el boton de power, index_1++
        {
            index_1 = 1;
            lastMillis_hora = millis();
        }
    }
}

void modoReloj()
{
    //Modo reloj
    /*
        Mostrar HORA
        Mostrar TEMPERATURA
    */

    if (millis() - lastMillis_hora_read >= 1000U)
    {
        lastMillis_hora_read = millis();
        readDHT();
        RTC_read();
    }

    if (millis() - lastMillis_hora >= siguienteIntervalo)
    {
        lastMillis_hora = millis();
        switch (index_2)
        {
            case 0:
                index_2 = 1;
                siguienteIntervalo = TIEMPO_MOSTRAR_TEMP;
                break;
            case 1:
                index_2 = 0;
                siguienteIntervalo = TIEMPO_MOSTRAR_HORA;
                break;
        }
    }

    //Leer por comando para editar hora / apagar

    if (IR_NewCommand() == 1)
    {
        if (lastIRCommand == IRCMD_POWER) //Si el comando es el boton de power, index_1++
        {
            index_1 = 2;
            index_2 = 0;
        }

        if (lastIRCommand == IRCMD_EDITHORA)
        {
            switch (index_2)
            {
                case 0:
                    index_2 = 2;
                    break;
                case 1:
                    index_2 = 2;
                    break;
                case 2:
                    index_2 = 0;
                    RELOJ_NUMERO_EN_EDICION = 1;
                    lastMillis_hora = millis();
                    break;
            }
        }

        if (index_2 == 2)
        {
            edit_hora(lastIRCommand);
        }

    }

    switch (index_2)
    {
        case 0:
            //MOSTRAR HORA
            INDICADOR_SEGUNDOS = true;
            DISP_noBlink();
            DISP1.dig1 = decena(tm.Hour);
            DISP1.dig2 = unidad(tm.Hour);
            DISP2.dig1 = decena(tm.Minute);
            DISP2.dig2 = unidad(tm.Minute);
            DISP3.dig1 = decena(tm.Second);
            DISP3.dig2 = unidad(tm.Second);
            break;
        case 1:
            //MOSTRAR TEMPERATURA
            DISP_noBlink();
            INDICADOR_SEGUNDOS = false;
            DISP1.dig1 = 21;
            DISP1.dig2 = 21;
            DISP2.dig1 = decena(DHT_get_temperatura());
            DISP2.dig2 = unidad(DHT_get_temperatura());
            DISP3.dig1 = 20;
            DISP3.dig2 = 12;
            break;
        case 2:
            //EDICION DE HORA

            INDICADOR_SEGUNDOS = true;
            DISP1.dig1 = decena(tm.Hour);
            DISP1.dig2 = unidad(tm.Hour);
            DISP2.dig1 = decena(tm.Minute);
            DISP2.dig2 = unidad(tm.Minute);
            DISP3.dig1 = decena(tm.Second);
            DISP3.dig2 = unidad(tm.Second);
            break;
    }
    updateLeds();

}
