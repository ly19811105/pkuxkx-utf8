#include <ansi.h>
inherit ROOM;




void create()
{
	set("short", HIC"荆西镖局"NOR);
	set("long", @LONG
这是一家镖局，上面一个牌匾草书，“荆西镖局”四字，年代比较久远了。
LONG
	);

    set("exits", ([
                
                "south" : __DIR__"wdroad2",
                
                
        ]));
    set("objects", ([
		
        __DIR__"npc/biaojunpc" : 1,
		
	    ]));
	//set("outdoors", "jinyang");
	setup();
	
}



