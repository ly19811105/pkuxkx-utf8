inherit ROOM;
void create()
{
        set("short", "练武场");
        set("long", @LONG
杀手帮练武场，所有的低级弟子每日都必须在此练武，进步突出者方有可能晋级到更高的位置
LONG
        );
        set("outdoors", "pker");
        set("exits", ([
                
                "east" : __DIR__"wuchang1",
                
                
                ]));
          set("objects", ([
          __DIR__"npc/yun.c":4
         
           ]));
        setup();
       replace_program(ROOM);
}



