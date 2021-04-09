//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "大道" );
	set("long", "这里是一平坦的大道，南面是一处小山坡。\n");
	set("exits", ([
		"north" : __DIR__"qing_qiao",
        //"northwest" : __DIR__"ming_shan1",
        //"northeast" : __DIR__"ming_lin1",
        "south": __DIR__"flag3",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","清");
    set("qibing_prefer",1);
    set("land_type","pingyuan");
    set("hardness",0);
	setup();
}

int buff(object me)
{
    int buff=(int)me->query("level")*3;
    object ob=this_object();
    if (me->query_temp("riding")&&present(me->query_temp("riding"),ob))
    {
        me->set_temp("guozhan/qibing_prefer",1);
        me->add_temp("apply/damage",buff);
    }
    return 1;
}

void init()
{
    object me=this_player();
    buff(me);
    ::init();
}

int valid_leave(object me,string dir)
{
    int buff=(int)me->query("level")*3;
    if (me->query_temp("guozhan/qibing_prefer"))
    {
        me->delete_temp("guozhan/qibing_prefer");
        me->add_temp("apply/damage",-buff);
    }
    return ::valid_leave(me,dir);
}
