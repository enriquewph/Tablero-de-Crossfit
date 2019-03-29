#ifndef HEADER
#define HEADER

#include <EEPROM.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#include <DHT.h>
#include <DHT_U.h>

#include <PinChangeInterrupt.h>
#include <IRLremote.h>

#include <TimeLib.h>
#include <DS1307RTC.h>

#define EEPROM_ADDRESS_UPTIME   0
#define EEPROM_ADDRESS_DNTIME   100
#define EEPROM_ADDRESS_TABATAS  200
#define EEPROM_ADDRESS_PROG1    300

//Definicion de pines
//Digital I/O
#define INDICADOR_SEGUNDOS_PIN  5
#define DHT11_DATA_PIN          6
#define IR_RECEIVER_DATA_PIN    7
#define SPEAKER_PIN             9


//Communication I/O
//uart
#define RX_PIN                  0
#define TX_PIN                  1
//spi
#define SPI_LATCH_PIN           10
#define SPI_MOSI_PIN            11
#define SPI_SCK_PIN             13
//i2c
#define SDA_PIN                 A4
#define SCL_PIN                 A5


bool INDICADOR_SEGUNDOS = 0;

struct DISPLAY_type
{
    uint8_t dig1;
    uint8_t dig2;
};

struct DISPLAY_type DISP1;
struct DISPLAY_type DISP2;
struct DISPLAY_type DISP3;

bool DISP_Parpadeando_onOff = 0;

bool DISP1_Parpadeando = false;
bool DISP2_Parpadeando = false;
bool DISP3_Parpadeando = false;
bool DISP4_Parpadeando = false;
bool DISP5_Parpadeando = false;
bool DISP6_Parpadeando = false;


#define RTC_UP_VAR_hour     1
#define RTC_UP_VAR_minute   2
#define RTC_UP_VAR_second   3



uint16_t lastIRCommand = 0x00;
//Direccion del control remoto
#define IR_REMOTE_ADDRESS   0xFF00
//Botones del control
#define IRCMD_POWER         0x84

#define IRCMD_NUM0          0x92
#define IRCMD_NUM1          0x87
#define IRCMD_NUM2          0x86
#define IRCMD_NUM3          0x85
#define IRCMD_NUM4          0x8B
#define IRCMD_NUM5          0x8A
#define IRCMD_NUM6          0x89
#define IRCMD_NUM7          0x8F
#define IRCMD_NUM8          0x8E
#define IRCMD_NUM9          0x8D

#define IRCMD_ESCAPE        0X96
#define IRCMD_UP            0x95
#define IRCMD_DOWN          0x9A
#define IRCMD_LEFT          0X9B
#define IRCMD_RIGHT         0x99
#define IRCMD_OK            0x9E
#define IRCMD_FN            0x91
#define IRCMD_EDITHORA      0x94
#define IRCMD_INICIO        0x8C
#define IRCMD_STOP          0x93
#define IRCMD_PLAYPAUSA     0x82


#define TIEMPO_MOSTRAR_HORA 20000U
#define TIEMPO_MOSTRAR_TEMP 7000U


tmElements_t tm;

/*
       tm.Hour
       tm.Minute
       tm.Second
       tm.Day
       tm.Month
       tm.Year
       tmYearToCalendar(tm.Year) //usar este para display
*/

uint8_t TIMER_NUMERO_EN_EDICION = 0; // 0 = ninguno
uint8_t RELOJ_NUMERO_EN_EDICION = 1; // 0 = ninguno 1 = horas 2 = minutos 3 = segundos

bool IR_NEWCOMMAND_NOTPOWER = false;


//CRONOMETRO

struct
{
    uint8_t minutos;
    uint8_t segundos;
    uint8_t centesimas;
} cronometro;

bool cronometro_funcionando = false;

#define TIMER1MODE_1HZ 0
#define TIMER1MODE_10HZ 1
#define TIMER1MODE_100HZ 2

uint8_t TIMER1MODE;


#define FREQ_TONO 2200
#define DUR_TONO  200
#define DUR_TONO_F 500

struct{
    uint8_t dig1;
    uint8_t dig2;
    uint8_t dig3;
    uint8_t dig4;
}EDIT_4_DIGITS_NUMEROS;


//funcion up
bool timerGoing = false;
bool setup_funcion = true;
uint16_t timerVal = 0;


#define PIT_FIN_WORK    0
#define PIT_FIN_REST    1
#define PIT_FIN_END     2

uint8_t fn_tb_tabatas = 0;

bool ENPAUSA = false;

uint8_t fn_up_minutos = 0;
uint8_t fn_up_segundos = 0;

uint16_t fn_up_cuenta_goal_seg = 0;
uint16_t segRestantes;
uint16_t segRestantes_last;

uint8_t fn_down_minutos = 0;
uint8_t fn_down_segundos = 0;

uint16_t fn_down_cuenta_goal_seg = 0;

bool fn_prog_funcionando = false;
uint8_t program_index = 0;

uint16_t fn_prog_int[6][3]; //TRABAJO - DESCANSO - SERIES
uint8_t fn_prog_var[6][3]; //REPETICIONES - NUM SERIES - CONFIG

bool fn_prog_cent;
bool fn_prog_asc;
uint16_t fn_prog_dur;

bool FN_PROG_START = false;

#endif
