// Room: /d/gumu/shandao3.c 
 
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
  "southwest" : __DIR__"shandao2.c",
 "east" : __DIR__"xiaoxi",
 "northdown" : "/d/changan/guandaos3",
 
 
]));
 /* set("objects", ([
                __DIR__"npc/yangnu" : 1,
        ]));*/
        set("no_clean_up", 0);

        setup();
        
}

int valid_leave(object me,string dir)
{  
	if (dir=="northdown")
    {
        if (!userp(me))
        {
            return notify_fail("你老兄哪能出去呀？\n");
        }
        
    }
	return ::valid_leave(me, dir);
}
