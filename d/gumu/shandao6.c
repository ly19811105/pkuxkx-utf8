// Room: /d/gumu/shandao6.c 
 
inherit ROOM; 
 
void create() 
{ 
        set("short", "山道");
set("outdoors","gumu");
        set("long", @LONG
    这是一终南山山后中的一条小道，山势到了这儿渐趋平
缓。东边是一片平原，平原后隐隐是一群山峰。

LONG
        );
       set("exits", ([  
  "west" : __DIR__"shandao5.c",
 "eastdown" : __DIR__"pingyuan",
 
 
]));
 /* set("objects", ([
                __DIR__"npc/yangnu" : 1,
        ]));*/
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
