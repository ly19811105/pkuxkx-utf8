#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIR"地狱"NOR);
	set("long","你完了...\n");
	set("valid_startroom",1);
	setup();
}

void init()
{
	if (!wizardp(this_player()))
	add_action("block_cmd","",1);
}

int block_cmd()
{
	return 1;
}
