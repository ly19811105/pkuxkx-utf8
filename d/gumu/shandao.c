// Room: /d/gumu/shandao.c 
 
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
  "west" : __DIR__"duanlongshi.c",
 "northeast" : __DIR__"shandao2",
 
 
]));
   set("objects",([
                CLASS_D("gumu")+"/yangnu" : 1,
      ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
