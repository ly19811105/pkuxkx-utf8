
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "襄阳南门");
set("outdoors","xiangyang");
	set("long", @LONG
	这里是襄阳的南门,几个月前刚刚打退了蒙古人的进攻.襄阳的
守军正在积极备战,往城里运物资.城门口有一队守军,对进出的行人盘查很严.
LONG
	);

        set("gate", 1);//保卫襄阳攻城门的判据．
        set("gatetype", 2);//保卫襄阳攻城门的判据．
	set("exits", ([
		"south" : __DIR__"mroad4",
		"north" : __DIR__"xysouth3"          
	]));

	set("objects", ([
		__DIR__"npc/shoujun" : 4,
	        __DIR__"npc/shjiang" : 1,
        ]));

	setup();
}


int valid_leave(object me, string dir)
{
    int i;
    object *ob;
    if ( dir != "north" || ( me->query_temp("shoujiang_asked") && present("yao pai",me) ) )
        me->delete_temp("killed");
        return ::valid_leave(me, dir);
    ob = all_inventory( environment( me ));
    for(i=0; i<sizeof(ob); i++) 
    {
        if( living(ob[i]) && ob[i]->query("id") == "shou jun" )
            return notify_fail("守军拦住了你的去路，大声喝到：干什么的？\n");
    }
    return ::valid_leave(me, dir);
}

void init()
{
if(!query("occupied")&&(load_object("/adm/daemons/xytaskd.c"))->query("begin")&&this_player()->query("id")=="menggu bing")
CHANNEL_D->do_channel( this_object(), "bd", query("short")+HIR"受到蒙古兵的攻击！", -1);
return ;
}
