#pragma once
#define P_BREAKAMOUNT 3
#define P_BREAKSPEED 1
#define P_BREAKTIME 0.8

#define E_BLANK Entity((char)32, 0x0,0	)
#define E_WALL Entity((char)219, 0x4,0)
#define E_GENERATOR Entity((char)234,0xD,0)
#define E_RIGHTTRAP Entity((char)195,0xC,0)
#define E_LEFTTRAP Entity((char)180,0xC,0)
#define E_UPTRAP Entity((char)193,0xC,0)
#define E_DOWNTRAP Entity((char)194,0xC,0)
#define E_PLAYERONE Entity((char)4,0x09,0)
#define E_PLAYERTWO Entity((char)6,0x0A,0)
#define E_AI Entity('A',0x0B,0)
#define E_KEYFRAGMENT Entity((char)232,0x09,0)
#define E_HEALTHPOTS Entity('H',0x0A,0)
#define E_GUN Entity('G',0x09,0)
#define E_GATE Entity('#',0x09,0)

