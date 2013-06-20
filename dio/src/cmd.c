/*
 * This file is part of the mps430-ioexp project.
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <msp430.h>
#include <legacymsp430.h>

#include "cmd.h"

/* Commands */
#define CMD_SET_PDIR    0x00
#define CMD_SET_POUT    0x01
#define CMD_GET_PIN     0x02
#define CMD_SET_PIR     0x03
#define CMD_GET_PIR     0x04
#define CMD_SET_REN     0x05
#define CMD_GET_PIRC    0x06
#define CMD_RESET       0xA0
#define CMD_FW_TYPE		0xF0
#define CMD_FW_VERSION	0xF1

static i2c_cmds cmds = {
     .count = 10,
     .cmds	= {
          {
               .cmd		= CMD_SET_PDIR,
			   .args	= 1,
               .func 	= cmd_set_pdir,
          },
          {
               .cmd		= CMD_SET_POUT,
			   .args	= 1,
               .func 	= cmd_set_pout,
          },
          {
               .cmd		= CMD_GET_PIN,
			   .args	= 0,
               .func 	= cmd_get_pin,
          },
          {
               .cmd		= CMD_SET_PIR,
			   .args	= 1,
               .func 	= cmd_set_pir,
          },
          {
               .cmd		= CMD_GET_PIR,
			   .args	= 0,
               .func 	= cmd_get_pir,
          },
          {
               .cmd		= CMD_GET_PIRC,
			   .args	= 1,
               .func 	= cmd_get_pirc,
          },
          {
               .cmd		= CMD_SET_REN,
			   .args	= 1,
               .func 	= cmd_set_ren,
          },
          {
               .cmd		= CMD_RESET,
			   .args	= 0,
               .func 	= cmd_reset,
          },
          {
               .cmd		= CMD_FW_TYPE,
			   .args	= 0,
               .func 	= cmd_get_fwtype,
          },
          {
               .cmd		= CMD_FW_VERSION,
			   .args	= 0,
               .func 	= cmd_get_fwversion,
          },
 	},
};

static unsigned char interrupt_flags = 0;

static unsigned int	 interrupt_cnt[] = {0, 0, 0, 0, 0, 0, 0, 0};

void i2c_cmd_init()
{
	i2cslave_cmdproc_init(I2C_ADDR, &cmds);
}

void cmd_set_pdir(i2c_cmd_args *args)
{
	unsigned char p1 =  (args->args[0] & 0b00111111);
	unsigned char p2 = ((args->args[0] & 0b11000000) >> 6); 

	P1DIR = (0b11000000 & P1DIR) | p1;
	P2DIR = (0b11111100 & P2DIR) | p2;
}

void cmd_set_pout(i2c_cmd_args *args)
{
	unsigned char p1 =  (args->args[0] & 0b00111111);
	unsigned char p2 = ((args->args[0] & 0b11000000) >> 6); 

	P1OUT = (0b11000000 & P1OUT) | p1;
	P2OUT = (0b11111100 & P2OUT) | p2;
}

void cmd_get_pin(i2c_cmd_args *args)
{
	unsigned char p1 =  0b00111111 & P1IN & ~P1DIR; 
	unsigned char p2 = (0b00000011 & P2IN & ~P2DIR) << 6; 

	i2cslave_cmdproc_clrres();
	i2cslave_cmdproc_addres(p1 | p2);
}

void cmd_set_pir(i2c_cmd_args *args)
{
	unsigned char p1 =  (args->args[0] & 0b00111111);
	unsigned char p2 = ((args->args[0] & 0b11000000) >> 6); 

	P1IE = (0b11000000 & P1OUT) | p1;
	P2IE = (0b11111100 & P2OUT) | p2;
}

void cmd_get_pir(i2c_cmd_args *args)
{
	i2cslave_cmdproc_clrres();
	i2cslave_cmdproc_addres(interrupt_flags);
	interrupt_flags = 0;
}

void cmd_get_pirc(i2c_cmd_args *args)
{
	unsigned char low = 0xff;
	unsigned char hi  = 0xff;

	if(args->args[0] <= 7) {
		low = (unsigned char)(interrupt_cnt[args->args[0]]);
		hi  = (unsigned char)(interrupt_cnt[args->args[0]] >> 8);
	}

	i2cslave_cmdproc_clrres();
	i2cslave_cmdproc_addres(hi);
	i2cslave_cmdproc_addres(low);
}

void cmd_set_ren(i2c_cmd_args *args)
{
	unsigned char p1 =  (args->args[0] & 0b00111111);
	unsigned char p2 = ((args->args[0] & 0b11000000) >> 6); 

	P1REN = (0b11000000 & P1REN) | p1;
	P2REN = (0b11111100 & P2REN) | p2;
}

void cmd_reset(i2c_cmd_args *args)
{
	P1DIR &= 0b11111111;
	P2DIR &= 0b11111111;

	P1OUT &= 0b11000000;
	P2OUT &= 0b11111100;

	P1REN &= 0b11000000;
	P2REN &= 0b11111100;

	P1SEL &= 0b11000100;
	P2SEL &= 0b11111100;

	P1IE &= 0b11000000;
	P2IE &= 0b11111100;

	interrupt_flags = 0;

	interrupt_cnt[0] = 0;
	interrupt_cnt[1] = 0;
	interrupt_cnt[2] = 0;
	interrupt_cnt[3] = 0;
	interrupt_cnt[4] = 0;
	interrupt_cnt[5] = 0;
	interrupt_cnt[6] = 0;
	interrupt_cnt[7] = 0;
}

void cmd_get_fwtype(i2c_cmd_args *args)
{
	// FIXME: add to global defines
	// 0x01 = DIO
	i2cslave_cmdproc_clrres();
	i2cslave_cmdproc_addres(0x01);
}

void cmd_get_fwversion(i2c_cmd_args *args)
{
	// FIXME: add to global defines
	// current fw-version
	i2cslave_cmdproc_clrres();
	i2cslave_cmdproc_addres(0x01);
}

interrupt(PORT1_VECTOR) PORT1_ISR(void)
{
	unsigned char p1 = (0b00111111 & P1IFG & P1IE); 

	interrupt_flags = (interrupt_flags & 0b11000000) | p1;

	if(p1 & 0b00000001) {
		interrupt_cnt[0]++;
	}
	if(p1 & 0b00000010) {
		interrupt_cnt[1]++;
	}
	if(p1 & 0b00000100) {
		interrupt_cnt[2]++;
	}
	if(p1 & 0b00001000) {
		interrupt_cnt[3]++;
	}
	if(p1 & 0b00010000) {
		interrupt_cnt[4]++;
	}
	if(p1 & 0b00100000) {
		interrupt_cnt[5]++;
	}

	P1IFG = 0;
}

interrupt(PORT2_VECTOR) PORT2_ISR(void)
{
	unsigned char p2 = (0b00000011 & P2IFG & P2IE) << 6; 

	interrupt_flags = (interrupt_flags & 0b00111111) | p2;

	if(p2 & 0b01000000) {
		interrupt_cnt[6]++;
	}
	if(p2 & 0b10000000) {
		interrupt_cnt[7]++;
	}

	P2IFG = 0;
}

