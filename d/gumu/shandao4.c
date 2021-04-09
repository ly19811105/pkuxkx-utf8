// Room: /d/gumu/shandao4.c 
#include <ansi.h>
inherit ROOM; 
 
void create() 
{ 
        set("short", "山道");
set("outdoors","gumu");
        set("long", @LONG
    这是一终南山山后中的一条小道，小道的东边是一
处峭壁，西边是一片荆棘。不时从树丛中传来声声虫叫。

LONG
        );
       set("exits", ([  
  "north" : __DIR__"xiaoxi.c",
 "southeast" : __DIR__"shandao5",
 
 
]));
 /* set("objects", ([
                __DIR__"npc/yangnu" : 1,
        ]));*/
        set("no_clean_up", 0);

        setup();
        //replace_program(ROOM);
}

void init()
{
	object me=this_player();
	if(present("shenmu wangding",me) )
	{
		write(RED"这里毒物甚多,神木王鼎如在此处使用想必效果不错。\n"NOR);
		me->set_temp("bingcan/bingcan",1);
	}
}
int valid_leave(object me, string dir)
{
	if(dir == "north" || dir == "southeast")
	me->delete_temp("bingcan/bingcan");
	return ::valid_leave(me, dir);
}