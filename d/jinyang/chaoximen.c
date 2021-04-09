//朝曦门 /d/jinyang/chaoximen
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>
string look_gaoshi();
void create()
{
        set("short", "朝曦门");
        set("long", 
"这里是晋阳的东门朝曦门。城墙上贴着告示(gaoshi)。\n"

        );
        set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));
        set("exits", ([
                "west" : __DIR__"eastavenue1",
                "northeast" : __DIR__"citywall1",
                "southwest" : __DIR__"citywall2",
                "east" : __DIR__"guandaoe1",
                
        ]));
        set("objects", ([
		"/d/city/npc/wujiang1"+random(2) : 1,
        "/d/city/npc/bing" : 2,
        ]));
        set("outdoors", "jinyang");
        setup();
   
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n晋阳知府谕\n";
}

int valid_leave(object me,string dir)
{  
	if (dir=="east")
    {
        if (me->query("id")=="xun bu")
        {
            return notify_fail("你老兄哪能出去呀？\n");
        }
        
    }
    if (dir=="west" && me->query_condition("killer"))
    {
        return notify_fail("你已被全城通缉，快去避避风头！\n");
    }
	return ::valid_leave(me, dir);
}