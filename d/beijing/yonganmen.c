//Cracked by Roath
// Room: /d/beijing/west/yonganmen.c
#include <ansi.h>
inherit ROOM;

string GATE_DESC_SHORT = HIY"永安门"NOR;
string GATE_DESC_LONG =
HIC"这是京城南面的门户，从南方经天津上京的人们多从这里进城。
这里的守卫还是很严的，城门边上许多人正围着看告示 (gaoshi)，
两边的土路通向左安门和右安门。\n"NOR;
mapping GATE_EXITS=([ /* sizeof() == 5 */
  "east"  : __DIR__"tulu_yongan_e",
  "west"  : __DIR__"tulu_yongan_w",
  "north" : __DIR__"qianmen1",
  "south" : __DIR__"dadao_yongan_s",
  "up" : __DIR__"yonganmenlou",
]);

mapping GATE_OBJECTS=([
	__DIR__"npc/bj_bing":4,
        __DIR__"npc/captain": 1,
]);

string GATE_ENTER_DIR="north";
#include "outer_gate.h"

void init()
{
     object me = this_player();
     if(me->query_temp("chaoting/xuncheng"))
     {
       me->set_temp("xc/yonganmen",1);
      }
    add_action("do_guard", "guarding");
    add_action("do_allow", "allow");
    add_action("do_climb", "climb");
}
