// Room: /d/gumu/pingyuan.c 
 
inherit ROOM; 
 
void create() 
{ 
        set("short", "平原");
set("outdoors","gumu");
        set("long", @LONG
    这是黄河河畔的一小片平原，西边是一片大山，东边
就是也是一片山，好象是河南的嵩山。

LONG
        );
       set("exits", ([  
  "westup" : __DIR__"shandao6.c",
 "eastup" : __DIR__"shanpo",
 
 
]));
 /* set("objects", ([
                __DIR__"npc/yangnu" : 1,
        ]));*/
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
