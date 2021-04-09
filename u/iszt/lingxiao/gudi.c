// File		: gudi.c
// Created By	: iszt@pkuxkx, 2007-02-26

#include <ansi.h>
#include "snow.h"

inherit ROOM;

void create()
{
        set("short", HIW"谷底"NOR);
	set("long", @LONG
你睁开双眼，发现自己身处深谷之中。
LONG);

	set("outdoors", "凌霄城");

	set("item_desc", ([
		"snow": (: snow :),
	]));

	set("exits", ([
		"southeast" : __DIR__"xueguan.c",
	]));

	setup();
}
