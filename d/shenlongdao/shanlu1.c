// Room: /shenlongjiao/shanlu.c
// kiden 06/08/25

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
此路沿山溪而行，沿途溪水淙淙，草木清新，颇感心旷神怡。
但见大树长草，便使人栗栗危惧，唯恐有毒蛇窜将出来。
LONG
        );
        set("outdoors", "shenlongdao");

        set("exits", ([
                "south" : __DIR__"shanlu.c",        
                "northup" : __DIR__"shanlu2.c",        
               
        ]));

   set("objects", ([
//         __DIR__"npc/liumang":1,
//        __DIR__"npc/rascal":1,
       ]));
        setup();
        replace_program(ROOM);
}

