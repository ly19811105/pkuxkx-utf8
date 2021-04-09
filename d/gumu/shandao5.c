// Room: /d/gumu/shandao5.c 
 
inherit ROOM; 
 
void create() 
{ 
        set("short", "山道");
set("outdoors","gumu");
        set("long", @LONG
    这是一终南山山后中的一条小道，小道的北边是一
处峭壁，南边是一片荆棘。不时从树丛中传来声声虫叫。

LONG
        );
       set("exits", ([  
  "northwest" : __DIR__"shandao4.c",
 "east" : __DIR__"shandao6",
 
 
]));
 /* set("objects", ([
                __DIR__"npc/yangnu" : 1,
        ]));*/
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
