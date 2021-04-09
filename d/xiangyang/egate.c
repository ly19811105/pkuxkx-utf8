
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "襄阳东门");
set("outdoors","xiangyang");
	set("long", @LONG
	这里是襄阳的东门,几个月前刚刚打退了蒙古人的进攻.襄阳的
守军正在积极备战,往城里运物资.城门口有一队守军,对进出的行人盘查很严.
LONG
	);

        set("gate", 1);//保卫襄阳攻城门的判据．
        set("gatetype", 4);//保卫襄阳攻城门的判据．
	set("exits", ([
		"east" : __DIR__"eroad1",
		"west" : __DIR__"xyeast3"          
	]));

	set("objects", ([
		__DIR__"npc/shoujun" : 4,
	        __DIR__"npc/shjiang2" : 1,
        ]));

	setup();
}

void init()
{
if(!query("occupied")&&(load_object("/adm/daemons/xytaskd.c"))->query("begin")&&this_player()->query("id")=="menggu bing")
CHANNEL_D->do_channel( this_object(), "bd", query("short")+HIR"受到蒙古兵的攻击！", -1);
return ;
}

/*int valid_leave(object me, string dir)
{        
         if (dir=="east" && !me->query_temp("东门") && !(me->query("id")=="cheng lingsu"))
           {   me->set_temp("东门",1);
              return notify_fail("此去往东是荒郊野岭，盗贼出没之地，我劝" + RANK_D->query_respect(me) +"\n还是不要去了,如果" + RANK_D->query_respect(me) + "一心想去，我也不阻拦，多加小心！\n");
           }
          return ::valid_leave(me, dir);
}*/
