/*
 * menu.c
 *
 * Created: 08.11.2013 12:39:55
 *  Author: �������������
 */ 

#include "menu.h"


char const _BURN_OK_[]			PROGMEM = "  Hello  world  ";

//****************************************************************************************
void Main_menu_i2c (unsigned char data)
{
	set_i2c_lcd_position(1,1);
	send_i2c_lcd_string_P(_BURN_OK_);
	set_i2c_lcd_position(2,1);
	detect_i2c_string(data);				// ������� �� �������
};			//Main_menu
//*****************************************************************************************
//*****************************************************************************************
//*****************************************************************************************