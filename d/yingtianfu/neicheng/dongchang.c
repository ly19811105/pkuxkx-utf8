//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "东厂胡同");
        set("long", 
"这里是东厂胡同，到处昏昏暗暗的，充满了阴气，顿时感觉一股阴风吹过，\n你提高了警觉。前面就是东厂的根据地，大门紧紧的关着，有一个守卫看守着，\n他看起来阴阳怪气的，应该是一个太监。\n"

        );
        set("exits", ([
                
              
                "east" : __DIR__"z_street2",
                "enter" : __DIR__"dongchang2",
                "west" : __DIR__"dongchang-prison",
                
        ]));
        set("objects", ([
		__DIR__"npc/dongchang-shouwei" : 2,
        
	    ]));
        set("outdoors", "yingtianfu");
        setup();
   
}


int valid_leave(object me,string dir)
{
    object* inv;    
    int i;
    inv = deep_inventory(me);
	if (dir=="enter"||dir=="west")
    {
        if (!me->query_temp("东厂进入"))
        {
            return notify_fail("要进东厂，似乎要和守卫打个招呼。\n");
        }
        for(i=sizeof(inv)-1; i>=0; i--)
            {
                if(userp(inv[i]))
                {
                    me->unconcious();
                    return notify_fail(HIR"竟敢带外人入内，下次再犯，定斩不赦！”\n"NOR);
                }
            }
    }
    me->delete_temp("东厂进入");
	return ::valid_leave(me, dir);
}

