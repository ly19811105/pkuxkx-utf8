//Cracked by Roath
// Room: /d/beijing/chongwenmen.c
#include <ansi.h>
inherit ROOM;

string GATE_DESC_SHORT = HIY"崇文门"NOR;
string GATE_DESC_LONG = 
HIC"崇文门是京城内城九大城门中南三门之一。再往北就靠近紫禁
城了。往那里去的大都是军机要员，老百姓偶尔路过的都被严加查
问。门边上的告示 (gaoshi) 似乎写着些什么。\n"NOR
;
mapping GATE_EXITS_NIGHT=([ /* sizeof() == 3 */
  "north" : __DIR__"wangfudajie2",
  "south" : __DIR__"chongwendajie",
  "west"  : __DIR__"changanjie_e",
  "up"  : __DIR__"chongwenmenlou",
]);
mapping GATE_EXITS=([ /* sizeof() == 3 */
  "north" : __DIR__"wangfudajie2",
  "south" : __DIR__"chongwendajie",
  "east"  : __DIR__"dongbianmen",
  "west"  : __DIR__"changanjie_e",
  "up"  : __DIR__"chongwenmenlou",
]);
mapping GATE_OBJECTS=([
  __DIR__"npc/bj_bing":4,
]);

int fix_exits_for_night(int is_night) {
    if (is_night) {
	set("exits", GATE_EXITS_NIGHT);
    }else{
	set("exits", GATE_EXITS);
    }
}
#include "inner_gate.h"
