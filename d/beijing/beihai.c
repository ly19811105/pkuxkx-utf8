// Room: /d/beijing/beihai.c
#include <ansi.h>
inherit ROOM;
string GATE_DESC_SHORT= HIY"北海西门"NOR;
string GATE_DESC_LONG =
HIC"这是北海的西侧门。从这里往里就是老百姓禁足的了。
偶尔可以看到有朝廷要员坐着轿子经过。门口贴了一张
告示 (gaoshi)。\n"NOR;

mapping GATE_EXITS = ([
  "west" : __DIR__"fuchengdajie",
//  "east" : "/d/beijing/beihai/ximen",
]);

mapping GATE_OBJECTS = ([
  __DIR__"npc/bj_bing":4,
]);

#include "inner_gate.h"
