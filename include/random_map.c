inherit ROOM; 
#include <ansi.h>
#include <random_clone.h>

void create() 
{ 
        set("short", "古战场遗址");
        set("long", @LONG
这里一处古战场遗址，到处都是散落的骨骸。
LONG
        );
	
        set("exits", ([ ]));
        set("outdoors", "random");
        set("no_clean_up", 1);
        set("no_reset", 1);
		setup();
}