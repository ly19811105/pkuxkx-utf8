
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "襄阳北门");
  set("outdoors","xiangyang");
	set("long", @LONG
	这里是襄阳北门,几个月前刚刚打退了蒙古人的进攻.襄阳的
守军正在积极备战,往城里运物资.城门口有一队守军,对进出的行人盘查很严.
LONG
	);

        set("gatetype", 1);//保卫襄阳攻城门的判据．
        set("gate", 1);//保卫襄阳攻城门的判据．
	set("exits", ([
		"south" : __DIR__"xynorth3",
		"north" : __DIR__"caoyuan1"          
	]));

	set("objects", ([
		__DIR__"npc/shoujun" : 4,
	        __DIR__"npc/shjiangn" : 1,
        ]));

	setup();
}
void init()
{
if(!query("occupied")&&(load_object("/adm/daemons/xytaskd.c"))->query("begin")&&this_player()->query("id")=="menggu bing")
CHANNEL_D->do_channel( this_object(), "bd", query("short")+HIR"受到蒙古兵的攻击！", -1);
return ;
}
  int valid_leave(object me, string dir)
{        
object xytaskd;
xytaskd=load_object("/adm/daemons/xytaskd.c");
if (xytaskd->query("begin"))  return ::valid_leave(me, dir);
if(me->query_temp("citan")) return ::valid_leave(me, dir);
         /*if ( (dir == "north") &&
              (!me->query_temp("bye")) 
            )
	return notify_fail("守将拦住了你的去路,对你说到:此处往北,\n是蒙古鞑子的领地英雄此去,定是凶多吉少啊.\n");*/
	return ::valid_leave(me, dir);
}

