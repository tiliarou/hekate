/*
 * Touch driver for Nintendo Switch's STMicroelectronics FingerTip S touch controller
 *
 * Copyright (c) 2018 langerhans
 * Copyright (c) 2018 CTCaer
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TOUCH_H_
#define __TOUCH_H_

#include "../utils/types.h"

#define STMFTS_I2C_ADDR 0x49

/* I2C commands */
#define STMFTS_READ_INFO               0x80
#define STMFTS_READ_STATUS             0x84
#define STMFTS_READ_ONE_EVENT          0x85
#define STMFTS_READ_ALL_EVENT          0x86
#define STMFTS_LATEST_EVENT            0x87
#define STMFTS_SLEEP_IN                0x90
#define STMFTS_SLEEP_OUT               0x91
#define STMFTS_MS_MT_SENSE_OFF         0x92
#define STMFTS_MS_MT_SENSE_ON          0x93
#define STMFTS_SS_HOVER_SENSE_OFF      0x94
#define STMFTS_SS_HOVER_SENSE_ON       0x95
#define STMFTS_MS_KEY_SENSE_OFF        0x9A
#define STMFTS_MS_KEY_SENSE_ON         0x9B
#define STMFTS_SYSTEM_RESET            0xA0
#define STMFTS_CLEAR_EVENT_STACK       0xA1
#define STMFTS_FULL_FORCE_CALIBRATION  0xA2
#define STMFTS_MS_CX_TUNING            0xA3
#define STMFTS_SS_CX_TUNING            0xA4
#define STMFTS_RELEASEINFO             0xAA
#define STMFTS_WRITE_REG               0xB6
#define STMFTS_RW_FB_REG               0xD0 // read data

#define STMFTS_UNK0 0xB8 //Request compensation
#define STMFTS_UNK1 0xCF
#define STMFTS_UNK2 0xF7
#define STMFTS_UNK3 0xFA
#define STMFTS_UNK4 0xF9
#define STMFTS_UNK5 0x62


/* events */
#define STMFTS_EV_NO_EVENT             0x00
#define STMFTS_EV_MULTI_TOUCH_DETECTED 0x02
#define STMFTS_EV_MULTI_TOUCH_ENTER    0x03
#define STMFTS_EV_MULTI_TOUCH_LEAVE    0x04
#define STMFTS_EV_MULTI_TOUCH_MOTION   0x05
#define STMFTS_EV_HOVER_ENTER          0x07
#define STMFTS_EV_HOVER_LEAVE          0x08
#define STMFTS_EV_HOVER_MOTION         0x09
#define STMFTS_EV_KEY_STATUS           0x0e
#define STMFTS_EV_ERROR                0x0f

#define STMFTS_EV_CONTROLLER_READY     0x10
#define STMFTS_EV_SLEEP_OUT_CONTROLLER_READY 0x11
#define STMFTS_EV_STATUS               0x16
#define STMFTS_EV_DEBUG                0xDB

/* multi touch related event masks */
#define STMFTS_MASK_EVENT_ID   0x0F
#define STMFTS_MASK_TOUCH_ID   0xF0
#define STMFTS_MASK_LEFT_EVENT 0x0F
#define STMFTS_MASK_X_MSB      0x0F
#define STMFTS_MASK_Y_LSB      0xF0

/* key related event masks */
#define STMFTS_MASK_KEY_NO_TOUCH 0x00
#define STMFTS_MASK_KEY_MENU     0x01
#define STMFTS_MASK_KEY_BACK     0x02

#define STMFTS_EVENT_SIZE     8
#define STMFTS_STACK_DEPTH   32
#define STMFTS_DATA_MAX_SIZE (STMFTS_EVENT_SIZE * STMFTS_STACK_DEPTH)
#define STMFTS_MAX_FINGERS   10

typedef struct _touch_event {
	u8   raw[8];
	u16  type; // Event type.
	u16  x;    // Horizontal coordinates.
	u16  y;    // Vertical coordinates.
	u8   z;
	u8   fingers;
	bool touch;
} touch_event;

typedef struct _touch_info {
	u16 chip_id;
	u16 fw_ver;
	u16 config_id;
	u16 config_ver;
} touch_info;

int touch_power_on();
void touch_power_off();
void touch_poll(touch_event *event);
touch_event touch_poll_wait();
touch_info touch_get_info();

#endif /* __TOUCH_H_ */