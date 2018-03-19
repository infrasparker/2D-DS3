#include "stand.h"

#include "atk1.h"
#include "atk2.h"
#include "atk3.h"
#include "atk4.h"
#include "atk5.h"
#include "atk6.h"
#include "atk7.h"
#include "atk8.h"
#include "atk9.h"
#include "atk10.h"

#include "roll1.h"
#include "roll2.h"
#include "roll3.h"
#include "roll4.h"
#include "roll5.h"

#include "run1.h"
#include "run2.h"
#include "run3.h"

#include "fatk1.h"
#include "fatk2.h"
#include "fatk3.h"
#include "fatk4.h"
#include "fatk5.h"
#include "fatk6.h"

#include "fstance1.h"
#include "fstance2.h"
#include "fstance3.h"
#include "fstance4.h"

#include "fstand.h"

#include "fwalk1.h"

#include "youdied.h"
#include "start.h"
#include "bg.h"
#include "bgbot.h"
#include "win.h"

#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>

unsigned short *videoBuffer = (unsigned short *) 0x6000000;
unsigned short buttontracker = 0;

// struct bubble bubbles[1];

enum GState gamestate = START;

player p = {(const unsigned short *)stand, 0, 0, 0, 0, SCREENH - STAND_HEIGHT, STAND_WIDTH,
	STAND_HEIGHT, STAND_fx, STAND_fy, 0, 0, STAND, 20, 20, 0, 0, 0};

friede f = {(const unsigned short *)fstand, 0, 0, 0, SCREENW - FSTAND_WIDTH, SCREENH - FSTAND_HEIGHT, FSTAND_WIDTH,
	FSTAND_HEIGHT, FSTAND_fx, FSTAND_fy, 0, 0, FSTAND, 50, 50, 0, 0};

// change enemy state and update image
void change_f_state(enum FState s) {
	f.timer = 0;
	switch(s) {
		case FSTAND:
			f.state = FSTAND;
			change_fimage(FSTAND_WIDTH, FSTAND_HEIGHT, FSTAND_fx, FSTAND_fy, fstand);
			f.nexttime = 0;
			break;
		case FWALK1:
			f.state = FWALK1;
			change_fimage(FWALK1_WIDTH, FWALK1_HEIGHT, FWALK1_fx, FWALK1_fy, fwalk1);
			f.nexttime = 50;
			break;
		case FWALK2:
			f.state = FWALK2;
			change_fimage(FSTAND_WIDTH, FSTAND_HEIGHT, FSTAND_fx, FSTAND_fy, fstand);
			f.nexttime = 50;
			break;
		case FSTANCE1:
			f.state = FSTANCE1;
			change_fimage(FSTANCE1_WIDTH, FSTANCE1_HEIGHT, FSTANCE1_fx, FSTANCE1_fy, fstance1);
			f.nexttime = 10;
			break;
		case FSTANCE2:
			f.state = FSTANCE2;
			change_fimage(FSTANCE2_WIDTH, FSTANCE2_HEIGHT, FSTANCE2_fx, FSTANCE2_fy, fstance2);
			f.nexttime = 10;
			break;
		case FSTANCE3:
			f.state = FSTANCE3;
			change_fimage(FSTANCE3_WIDTH, FSTANCE3_HEIGHT, FSTANCE3_fx, FSTANCE3_fy, fstance3);
			f.nexttime = 10;
			break;
		case FSTANCE4:
			f.state = FSTANCE4;
			change_fimage(FSTANCE4_WIDTH, FSTANCE4_HEIGHT, FSTANCE4_fx, FSTANCE4_fy, fstance4);
			f.nexttime = 50;
			break;
		case FATK1:
			f.state = FATK1;
			change_fimage(FATK1_WIDTH, FATK1_HEIGHT, FATK1_fx, FATK1_fy, fatk1);
			f.nexttime = 10;
			break;
		case FATK2:
			f.state = FATK2;
			f.attacking = 1;
			change_fimage(FATK2_WIDTH, FATK2_HEIGHT, FATK2_fx, FATK2_fy, fatk2);
			f.nexttime = 5;
			f.x -= 10;
			break;
		case FATK3:
			f.state = FATK3;
			change_fimage(FATK3_WIDTH, FATK3_HEIGHT, FATK3_fx, FATK3_fy, fatk3);
			f.nexttime = 4;
			f.x -= 20;
			break;
		case FATK4:
			f.state = FATK4;
			change_fimage(FATK4_WIDTH, FATK4_HEIGHT, FATK4_fx, FATK4_fy, fatk4);
			f.nexttime = 2;
			f.x += 20;
			break;
		case FATK5:
			f.state = FATK5;
			f.attacking = 0;
			change_fimage(FATK5_WIDTH, FATK5_HEIGHT, FATK5_fx, FATK5_fy, fatk5);
			f.nexttime = 4;
			f.x += 10;
			break;
		case FATK6:
			f.state = FATK6;
			change_fimage(FATK6_WIDTH, FATK6_HEIGHT, FATK6_fx, FATK6_fy, fatk6);
			f.nexttime = 5;
			break;
	}
}

// change player state and update image. Commented bubbles are for hitbubble implementation
void change_player_state(enum PState s) {
	p.timer = 0;
	switch(s) {
		case STAND:
			p.locked = 0;
			p.state = STAND;
			change_pimage(STAND_WIDTH, STAND_HEIGHT, STAND_fx, STAND_fy, stand);
			// struct bubble standhurtbubbles[2];
			// bubbles[0].x = 35;
			// bubbles[0].y = 12;
			// bubbles[0].r = 12;
			// bubbles[1].x = 33;
			// bubbles[1].y = 33;
			// bubbles[1].r = 13;
			// p.hurtbubbles = standhurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 0;
			break;
		case RUN1:
			p.state = RUN1;
			change_pimage(RUN1_WIDTH, RUN1_HEIGHT, RUN1_fx, RUN1_fy, run1);
			// struct bubble run1hurtbubbles[2];
			// bubbles[0].x = 34;
			// bubbles[0].y = 11;
			// bubbles[0].r = 10;
			// bubbles[1].x = 34;
			// bubbles[1].y = 30;
			// bubbles[1].r = 12;
			// p.hurtbubbles = run1hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 10;
			break;
		case RUN2:
			p.state = RUN2;
			change_pimage(RUN2_WIDTH, RUN2_HEIGHT, RUN2_fx, RUN2_fy, run2);
			// struct bubble run2hurtbubbles[2];
			// bubbles[0].x = 35;
			// bubbles[0].y = 15;
			// bubbles[0].r = 11;
			// bubbles[1].x = 33;
			// bubbles[1].y = 30;
			// bubbles[1].r = 13;
			// p.hurtbubbles = run2hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 5;
			break;
		case RUN3:
			p.state = RUN3;
			change_pimage(RUN3_WIDTH, RUN3_HEIGHT, RUN2_fx, RUN2_fy, run3);
			// struct bubble run3hurtbubbles[2];
			// bubbles[0].x = 35;
			// bubbles[0].y = 12;
			// bubbles[0].r = 12;
			// bubbles[1].x = 33;
			// bubbles[1].y = 31;
			// bubbles[1].r = 12;
			// p.hurtbubbles = run3hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 10;
			break;
		case RUN4:
			p.state = RUN4;
			change_pimage(RUN2_WIDTH, RUN2_HEIGHT, RUN2_fx, RUN2_fy, run2);
			// struct bubble run4hurtbubbles[2];
			// bubbles[0].x = 35;
			// bubbles[0].y = 15;
			// bubbles[0].r = 11;
			// bubbles[1].x = 33;
			// bubbles[1].y = 30;
			// bubbles[1].r = 13;
			// p.hurtbubbles = run4hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 5;
			break;
		case ATK1:
			p.state = ATK1;
			change_pimage(ATK1_WIDTH, ATK1_HEIGHT, ATK1_fx, ATK1_fy, atk1);
			// struct bubble atk1hurtbubbles[3];
			// bubbles[0].x = 34;
			// bubbles[0].y = 10;
			// bubbles[0].r = 9;
			// bubbles[1].x = 37;
			// bubbles[1].y = 21;
			// bubbles[1].r = 10;
			// bubbles[2].x = 38;
			// bubbles[2].y = 36;
			// bubbles[2].r = 11;
			// p.hurtbubbles = atk1hurtbubbles;
			// p.amthurts = 3;
			// p.amthits = 0;
			p.nexttime = 10;
			break;
		case ATK2:
			p.state = ATK2;
			change_pimage(ATK2_WIDTH, ATK2_HEIGHT, ATK2_fx, ATK2_fy, atk2);
			// struct bubble atk2hurtbubbles[2];
			// bubbles[0].x = 33;
			// bubbles[0].y = 26;
			// bubbles[0].r = 9;
			// bubbles[1].x = 29;
			// bubbles[1].y = 47;
			// bubbles[1].r = 12;
			// p.hurtbubbles = atk2hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 5;
			break;
		case ATK3:
			p.state = ATK3;
			change_pimage(ATK3_WIDTH, ATK3_HEIGHT, ATK3_fx, ATK3_fy, atk3);
			p.attacking = 1;
			// struct bubble atk3hurtbubbles[2];
			// bubbles[0].x = 21;
			// bubbles[0].y = 44;
			// bubbles[0].r = 10;
			// bubbles[1].x = 15;
			// bubbles[1].y = 64;
			// bubbles[1].r = 11;
			// p.hurtbubbles = atk3hurtbubbles;
			// struct bubble atk3hitbubbles[2];
			// bubbles[0].x = 46;
			// bubbles[0].y = 12;
			// bubbles[0].r = 14;
			// bubbles[1].x = 40;
			// bubbles[1].y = 38;
			// bubbles[1].r = 14;
			// p.hitbubbles = atk3hitbubbles;
			// p.amthurts = 2;
			// p.amthits = 2;
			p.nexttime = 4;
			break;
		case ATK4:
			p.state = ATK4;
			change_pimage(ATK4_WIDTH, ATK4_HEIGHT, ATK4_fx, ATK4_fy, atk4);
			// struct bubble atk4hurtbubbles[2];
			// bubbles[0].x = 20;
			// bubbles[0].y = 13;
			// bubbles[0].r = 11;
			// bubbles[1].x = 14;
			// bubbles[1].y = 34;
			// bubbles[1].r = 13;
			// p.hurtbubbles = atk4hurtbubbles;
			// struct bubble atk4hitbubbles[2];
			// bubbles[0].x = 65;
			// bubbles[0].y = 13;
			// bubbles[0].r = 14;
			// bubbles[1].x = 43;
			// bubbles[1].y = 20;
			// bubbles[1].r = 15;
			// p.hitbubbles = atk4hitbubbles;
			// p.amthurts = 2;
			// p.amthits = 2;
			p.nexttime = 3;
			break;
		case ATK5:
			p.state = ATK5;
			change_pimage(ATK5_WIDTH, ATK5_HEIGHT, ATK5_fx, ATK5_fy, atk5);
			// struct bubble atk5hurtbubbles[2];
			// bubbles[0].x = 18;
			// bubbles[0].y = 9;
			// bubbles[0].r = 11;
			// bubbles[1].x = 14;
			// bubbles[1].y = 26;
			// bubbles[1].r = 12;
			// p.hurtbubbles = atk5hurtbubbles;
			// struct bubble atk5hitbubbles[2];
			// bubbles[0].x = 61;
			// bubbles[0].y = 29;
			// bubbles[0].r = 15;
			// bubbles[1].x = 35;
			// bubbles[1].y = 27;
			// bubbles[1].r = 15;
			// p.hitbubbles = atk5hitbubbles;
			// p.amthurts = 2;
			// p.amthits = 2;
			p.nexttime = 4;
			break;
		case ATK6:
			p.state = ATK6;
			change_pimage(ATK6_WIDTH, ATK6_HEIGHT, ATK6_fx, ATK6_fy, atk6);
			// struct bubble atk6hurtbubbles[2];
			// bubbles[0].x = 18;
			// bubbles[0].y = 10;
			// bubbles[0].r = 11;
			// bubbles[1].x = 13;
			// bubbles[1].y = 26;
			// bubbles[1].r = 13;
			// p.hurtbubbles = atk6hurtbubbles;
			// struct bubble atk6hitbubbles[2];
			// bubbles[0].x = 63;
			// bubbles[0].y = 29;
			// bubbles[0].r = 15;
			// bubbles[1].x = 35;
			// bubbles[1].y = 28;
			// bubbles[1].r = 15;
			// p.hitbubbles = atk6hitbubbles;
			// p.amthurts = 2;
			// p.amthits = 2;
			p.nexttime = 5;
			break;
		case ATK7:
			p.state = ATK7;
			change_pimage(ATK7_WIDTH, ATK7_HEIGHT, ATK7_fx, ATK7_fy, atk7);
			// struct bubble atk7hurtbubbles[2];
			// bubbles[0].x = 18;
			// bubbles[0].y = 10;
			// bubbles[0].r = 11;
			// bubbles[1].x = 14;
			// bubbles[1].y = 26;
			// bubbles[1].r = 13;
			// p.hurtbubbles = atk7hurtbubbles;
			// struct bubble atk7hitbubbles[2];
			// bubbles[0].x = 61;
			// bubbles[0].y = 26;
			// bubbles[0].r = 14;
			// bubbles[1].x = 36;
			// bubbles[1].y = 27;
			// bubbles[1].r = 15;
			// p.hitbubbles = atk7hitbubbles;
			// p.amthurts = 2;
			// p.amthits = 2;
			p.nexttime = 5;
			break;
		case ATK8:
			p.state = ATK8;
			change_pimage(ATK8_WIDTH, ATK8_HEIGHT, ATK8_fx, ATK8_fy, atk8);
			p.nexttime = 5;
			p.attacking = 0;
			// struct bubble atk8hurtbubbles[2];
			// bubbles[0].x = 19;
			// bubbles[0].y = 10;
			// bubbles[0].r = 10;
			// bubbles[1].x = 15;
			// bubbles[1].y = 24;
			// bubbles[1].r = 12;
			// p.hurtbubbles = atk8hurtbubbles;
			// bubbles[1].r = 15;
			// p.amthurts = 2;
			// p.amthits = 0;
			break;
		case ATK9:
			p.state = ATK9;
			change_pimage(ATK9_WIDTH, ATK9_HEIGHT, ATK9_fx, ATK9_fy, atk9);
			p.nexttime = 5;
			// struct bubble atk9hurtbubbles[2];
			// bubbles[0].x = 19;
			// bubbles[0].y = 34;
			// bubbles[0].r = 10;
			// bubbles[1].x = 13;
			// bubbles[1].y = 49;
			// bubbles[1].r = 14;
			// p.hurtbubbles = atk9hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			break;
		case ATK10:
			p.state = ATK10;
			change_pimage(ATK10_WIDTH, ATK10_HEIGHT, ATK10_fx, ATK10_fy, atk10);
			// struct bubble atk10hurtbubbles[2];
			// bubbles[0].x = 33;
			// bubbles[0].y = 27;
			// bubbles[0].r = 11;
			// bubbles[1].x = 32;
			// bubbles[1].y = 48;
			// bubbles[1].r = 13;
			// p.hurtbubbles = atk10hurtbubbles;
			// p.amthurts = 2;
			// p.nexttime = 5;
			break;
		case ROLL1:
			if (p.xvel < 0) {
				p.xvel = -.1;
			} else {
				p.xvel = .1;
			}

			p.state = ROLL1;
			p.invinc = 1;
			change_pimage(ROLL1_WIDTH, ROLL1_HEIGHT, ROLL1_fx, ROLL1_fy, roll1);
			// struct bubble roll1hurtbubbles[2];
			// bubbles[0].x = 18;
			// bubbles[0].y = 9;
			// bubbles[0].r = 12;
			// bubbles[1].x = 12;
			// bubbles[1].y = 28;
			// bubbles[1].r = 14;
			// p.hurtbubbles = roll1hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 5;
			break;
		case ROLL2:
			if (p.xvel < 0) {
				p.xvel = -1;
			} else {
				p.xvel = 1;
			}
			p.state = ROLL2;
			// p.invinc = 1;
			change_pimage(ROLL2_WIDTH, ROLL2_HEIGHT, ROLL2_fx, ROLL2_fy, roll2);
			// struct bubble roll2hurtbubbles[2];
			// bubbles[0].x = 25;
			// bubbles[0].y = 8;
			// bubbles[0].r = 11;
			// bubbles[1].x = 14;
			// bubbles[1].y = 21;
			// bubbles[1].r = 13;
			// p.hurtbubbles = roll2hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 5;
			break;
		case ROLL3:
			p.state = ROLL3;
			// p.invinc = 1;
			if (p.xvel < 0) {
				p.xvel = -2;
			} else {
				p.xvel = 2;
			}
			change_pimage(ROLL3_WIDTH, ROLL3_HEIGHT, ROLL3_fx, ROLL3_fy, roll3);
			// struct bubble roll3hurtbubbles[2];
			// bubbles[0].x = 34;
			// bubbles[0].y = 9;
			// bubbles[0].r = 13;
			// bubbles[1].x = 13;
			// bubbles[1].y = 8;
			// bubbles[1].r = 13;
			// p.hurtbubbles = roll3hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 5;
			break;
		case ROLL4:
			p.state = ROLL4;
			if (p.xvel < 0) {
				p.xvel = -4;
			} else {
				p.xvel = 4;
			}
			change_pimage(ROLL4_WIDTH, ROLL4_HEIGHT, ROLL4_fx, ROLL4_fy, roll4);
			// struct bubble roll4hurtbubbles[2];
			// // bubbles[0].x = 12;
			// bubbles[0].y = 28;
			// bubbles[0].r = 10;
			// bubbles[1].x = 6;
			// bubbles[1].y = 10;
			// bubbles[1].r = 12;
			// p.hurtbubbles = roll4hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 5;
			break;
		case ROLL5:
			if (p.xvel < 0) {
				p.xvel = -2;
			} else {
				p.xvel = 2;
			}
			p.state = ROLL5;
			change_pimage(ROLL5_WIDTH, ROLL5_HEIGHT, ROLL5_fx, ROLL5_fy, roll5);
			// struct bubble roll5hurtbubbles[2];
			// bubbles[0].x = 12;
			// bubbles[0].y = 7;
			// bubbles[0].r = 10;
			// bubbles[1].x = 33;
			// bubbles[1].y = 7;
			// bubbles[1].r = 12;
			// p.hurtbubbles = roll5hurtbubbles;
			// p.amthurts = 2;
			// p.amthits = 0;
			p.nexttime = 10;
			break;
		case STUN:
			p.state = STUN;
			p.attacking = 0;
			change_pimage(ATK1_WIDTH, ATK1_HEIGHT, ATK1_fx, ATK1_fy, atk1);
			p.nexttime = 20;
			p.invinc = 1;
			p.xvel = -.5;
			buttontracker = buttontracker & 0xFFF7; // Set 4th bit (LEFT) to 0 (0111)
			buttontracker = buttontracker & 0xFFFB; // Set 3rd bit (RIGHT) to 0 (1011)
			p.locked = 1;
			break;
	}
}

// handle inputs
void check_events() {
	if (KEY_DOWN_NOW(BUTTON_RIGHT) && ((buttontracker >> 2) & 0x1) == 0 &&
			p.locked == 0) {
		buttontracker = buttontracker | 0x4; // Set 3rd bit (RIGHT) to 1 (0100)
		p.xvel += 1;
		change_player_state(RUN1);
	} else if (!KEY_DOWN_NOW(BUTTON_RIGHT) && ((buttontracker >> 2) & 0x1) > 0 &&
			p.locked == 0) {
		buttontracker = buttontracker & 0xFFFB; // Set 3rd bit (RIGHT) to 0 (1011)
		p.xvel -= 1;
		if (p.xvel == 0) {
			change_player_state(STAND);
		}
	}

	if (KEY_DOWN_NOW(BUTTON_LEFT) && ((buttontracker >> 3) & 0x1) == 0 &&
			p.locked == 0) {
		buttontracker = buttontracker | 0x8; // Set 4th bit (LEFT) to 1 (1000)
		p.xvel -= 1;
		change_player_state(RUN1);
	} else if (!KEY_DOWN_NOW(BUTTON_LEFT) && ((buttontracker >> 3) & 0x1) > 0 &&
			p.locked == 0) {
		buttontracker = buttontracker & 0xFFF7; // Set 4th bit (LEFT) to 0 (0111)
		p.xvel += 1;
		if (p.xvel == 0) {
			change_player_state(STAND);
		}
	}

	if (KEY_DOWN_NOW(BUTTON_UP) && ((buttontracker >> 4) & 0x1) == 0 &&
			p.locked == 0) {
		buttontracker = buttontracker | 0x10; // Set 5th bit (UP) to 1 (00010000)
		p.jump = 1;
		p.yvel = -5;
	} else if (!KEY_DOWN_NOW(BUTTON_UP) && ((buttontracker >> 4) & 0x1) > 0 &&
			p.locked == 0) {
		buttontracker = buttontracker & 0xFFEF; // Set 5th bit (UP) to 0 (11101111)
	}

	if (KEY_DOWN_NOW(BUTTON_A) && (buttontracker & 0x1) == 0 && p.locked == 0) {
		p.xvel = 0;
		p.locked = 1;
		buttontracker = buttontracker | 0x1; // Set 1st bit (A) to 1 (0001)
		buttontracker = buttontracker & 0xFFFB; // Set 3rd bit (RIGHT) to 0 (1011)
		buttontracker = buttontracker & 0xFFF7; // Set 4th bit (LEFT) to 0 (0111)
		change_player_state(ATK1);
	} else if (!KEY_DOWN_NOW(BUTTON_A) && (buttontracker & 0x1) == 1) {
		buttontracker = buttontracker & 0xFFFE; // Set 1st bit (A) to 0 (1110)
	}

	if (KEY_DOWN_NOW(BUTTON_B) && ((buttontracker >> 1) & 0x1) == 0 &&
			p.locked == 0) {
		p.locked = 1;
		buttontracker = buttontracker | 0x2; // Set 3rd bit (RIGHT) to 1 (0010)
		buttontracker = buttontracker & 0xFFFB; // Set 3rd bit (RIGHT) to 0 (1011)
		buttontracker = buttontracker & 0xFFF7; // Set 4th bit (LEFT) to 0 (0111)
		change_player_state(ROLL1);
	} else if (!KEY_DOWN_NOW(BUTTON_B) && ((buttontracker >> 1) & 0x1) > 0) {
		buttontracker = buttontracker & 0xFFFD; // Set 3rd bit (RIGHT) to 0 (1101)
	}
}


// handle battle logic
void update() {
	if (p.health <= 0) {
		gamestate = DEAD;
	}
	if (f.health <= 0) {
		gamestate = WIN;
	}
	if (f.hittimer > 0) {
		f.hittimer--;
	}
	p.x += p.xvel;
	p.y += p.yvel;
	f.x += f.xvel;
	f.y += f.yvel;
	p.yvel += .5;
	if (f.nexttime > 0 && f.timer <= f.nexttime) {
		f.timer++;
	} else if (f.nexttime > 0 && f.timer > f.nexttime) {
		switch (f.state) {
			case FSTAND:
				break;
			case FWALK1:
				change_f_state(FWALK2);
				break;
			case FWALK2:
				f.xvel = 0;
				change_f_state(FSTAND);
				break;
			case FSTANCE1:
				change_f_state(FSTANCE2);
				break;
			case FSTANCE2:
				change_f_state(FSTANCE3);
				break;
			case FSTANCE3:
				change_f_state(FSTANCE4);
				break;
			case FSTANCE4:
				change_f_state(FATK1);
				break;
			case FATK1:
				change_f_state(FATK2);
				break;
			case FATK2:
				change_f_state(FATK3);
				break;
			case FATK3:
				change_f_state(FATK4);
				break;
			case FATK4:
				change_f_state(FATK5);
				break;
			case FATK5:
				change_f_state(FATK6);
				break;
			case FATK6:
				change_f_state(FSTAND);
				break;
		}
	}
	if (f.state == FSTAND || f.state == FWALK1 || f.state == FWALK2) {
		if (f.x - (p.x + p.w) > 50) {
			if (f.state == FSTAND) {
				f.xvel = -.2;
				change_f_state(FWALK1);
			}
		} else if (f.x - (p.x + p.w) < 10) {
			if (f.state == FSTAND) {
				f.xvel = .2;
				change_f_state(FWALK1);
			}
		} else {
			f.xvel = 0;
			change_f_state(FSTANCE1);
		}
	}
	if (f.state == FSTANCE1 || f.state == FSTANCE2 || f.state == FSTANCE3
			|| f.state == FSTANCE4) {
		if (f.x - (p.x + p.w) >  60) {
			change_f_state(FSTAND);
		} else if (f.x - (p.x + p.w) < 20) {
			change_f_state(FATK1);
		}
	}

	if (p.nexttime > 0 && p.timer <= p.nexttime) {
		p.timer++;
	} else if (p.nexttime > 0 && p.timer > p.nexttime) {
		switch(p.state) {
			case STAND:
				break;
			case RUN1:
				change_player_state(RUN2);
				break;
			case RUN2:
				change_player_state(RUN3);
				break;
			case RUN3:
				change_player_state(RUN4);
				break;
			case RUN4:
				change_player_state(RUN1);
				break;
			case ATK1:
				change_player_state(ATK2);
				break;
			case ATK2:
				change_player_state(ATK3);
				break;
			case ATK3:
				change_player_state(ATK4);
				break;
			case ATK4:
				change_player_state(ATK5);
				break;
			case ATK5:
				change_player_state(ATK6);
				break;
			case ATK6:
				change_player_state(ATK7);
				break;
			case ATK7:
				change_player_state(ATK8);
				break;
			case ATK8:
				change_player_state(ATK9);
				break;
			case ATK9:
				change_player_state(ATK10);
				break;
			case ATK10:
				change_player_state(STAND);
				break;
			case ROLL1:
				change_player_state(ROLL2);
				break;
			case ROLL2:
				change_player_state(ROLL3);
				break;
			case ROLL3:
				change_player_state(ROLL4);
				break;
			case ROLL4:
				change_player_state(ROLL5);
				break;
			case ROLL5:
				p.xvel = 0;
				p.invinc = 0;
				change_player_state(STAND);
				break;
			case STUN:
				p.xvel = 0;
				p.invinc = 0;
				change_player_state(STAND);
				p.locked = 0;
				break;
			// case ROLL6:
			// 	p.xvel = 0;
			// 	change_player_state(STAND);
			// 	break;
		}
	}
	
}

// detect colliding objects and boundaries
void check_collisions() {
	if (p.x < 0) {
		p.x = 0;
	}
	if (p.x + p.w > 240) {
		p.x = 240 - p.w;
	}
	if (p.y + p.h >= 160) {
		p.y = 160 - p.h;
		p.yvel = 0;
	}
	if (f.x < 0) {
		f.x = 0;
	}
	if (f.x + f.w > 240) {
		f.x = 240 - f.w;
	}
	if (f.attacking > 0 && p.invinc == 0) {
		if ((f.x < p.x + p.w) && (f.x + f.w > p.x) && (f.y < p.y + p.h)
			&& (f.h + f.y > p.y)) {
			p.health -= 6;
			p.invinc = 1;
			change_player_state(STUN);
			drawRect(20, 30, 100, 10, BLACK);
			char buffer2[9];
			sprintf(buffer2, "Exile: %d / %d", p.health, p.maxhealth);
			drawString(30, 20, buffer2, WHITE);
		}
	}
	if (p.attacking > 0 && f.hittimer == 0) {
		if ((f.x < p.x + p.w) && (f.x + f.w > p.x) && (f.y < p.y + p.h)
			&& (f.h + f.y > p.y)) {
			f.health -= 7;
			f.hittimer = 40;
			drawRect(20, 0, 100, 10, BLACK);
			char buffer[9];
			sprintf(buffer, "Friede: %d / %d", f.health, f.maxhealth);
			drawString(0, 20, buffer, WHITE);
		}
	}
	
	
}
// Draw stuff during battle
void render() {
	// fillScreen(GREY);
	// drawRect(0, 0, 240, 160, GREY);
	drawImage(0, 160 - BGBOT_HEIGHT, 240, BGBOT_HEIGHT, bgbot);
	drawImage(p.x, p.y, p.w, p.h, p.image);
	drawImage(f.x, f.y, f.w, f.h, f.image);
	drawRect(20, 10, 200, 10, BLACK);
	if (f.health > 0) {
		drawRect(22, 12, (int)(((double) f.health / (double) f.maxhealth) * 196), 6, RED);
	}
	drawRect(20, 40, 100, 10, BLACK);
	if (p.health > 0) {
		drawRect(22, 42, (int)(((double) p.health / (double) p.maxhealth) * 96), 6, RED);
	}
}

// game loop
int main() {
	REG_DISPCNT = MODE_3 | BG2_EN;
	while(1) {
		if (KEY_DOWN_NOW(BUTTON_SELECT) && ((buttontracker >> 6) & 0x1) == 0) {
			buttontracker = buttontracker | 0x20; // Set 6th bit (SELECT) to 1 (00100000)
			gamestate = START;
			change_f_state(FSTAND);
			f.x = 240 - f.w;
			f.y = 160 - f.h;
			f.xvel = 0;
			f.yvel = 0;
			f.health = f.maxhealth;
			f.attacking = 0;
			f.hittimer = 0;
			change_player_state(STAND);
			p.x = 0;
			p.y = 160 - p.h;
			p.xvel = 0;
			p.yvel = 0;
			p.locked = 0;
			p.health = p.maxhealth;
			p.attacking = 0;
			p.invinc = 0;
			p.jump = 0;
			buttontracker = 0x0020;
		} else if (!KEY_DOWN_NOW(BUTTON_SELECT) && ((buttontracker >> 6) & 0x1) > 0) {
			buttontracker = buttontracker & 0xFFDF; // Set 6th bit (SELECT) to 0 (11011111)
		}
		if (gamestate == START) {
			drawImage(0, 0, START_WIDTH, START_HEIGHT, start);
			if (KEY_DOWN_NOW(BUTTON_A) && (buttontracker & 0x1) == 0 && p.locked == 0) {
				buttontracker = buttontracker | 0x1; // Set 1st bit (A) to 1 (0001)
				gamestate = BATTLE;
				drawImage(0, 0, BG_WIDTH, BG_HEIGHT, bg);
				drawRect(20, 0, 100, 10, BLACK);
				char buffer[9];
				sprintf(buffer, "Friede: %d / %d", f.health, f.maxhealth);
				drawString(0, 20, buffer, WHITE);
				drawRect(20, 30, 100, 10, BLACK);
				char buffer2[9];
				sprintf(buffer2, "Exile: %d / %d", p.health, p.maxhealth);
				drawString(30, 20, buffer2, WHITE);
			}
			
		} else if (gamestate == BATTLE) {
			check_events();
			update();
			check_collisions();
			render();
		} else if (gamestate == DEAD) {
			drawImage(0, 0, YOUDIED_WIDTH, YOUDIED_HEIGHT, youdied);
		} else if (gamestate == WIN) {
			drawImage(0, 0, WIN_WIDTH, WIN_HEIGHT, win);
		}
		waitForVBlank();
	}
	return 0;
}

