// luppan.c   罗盘
// hongdou 98.10.04

#include <ansi.h>

inherit ITEM;

void init()
{
        add_action("do_use", "use");
}

void create()
{
   	set_name(WHT"罗盘"NOR,({"luo pan","luopan", "pan"}));
	set_weight(200);
	if(clonep() )
     		set_default_object(__FILE__);
   	else{
   	set("long","这是一个罗盘，远航时可以用(use)它来辨别方向。\n");
	set("unit","个");
	set("value", 8000);
       }
}

int do_use(string arg)
{
        object me = this_player();
	int i;

	if (!id(arg)) return notify_fail("你要使用什么？\n");
if(base_name(environment(me))!="/d/diaoyudao/x_chuan2"&&base_name(environment(me))!="/d/diaoyudao/x_chuan1")
        return notify_fail("只有在船上才用的上这个航海罗盘\n");
	if ((me->query_temp("航1")) || (me->query_temp("航2")))
	{
	    message_vision(HIY"\n$N开始使用罗盘航海......\n"NOR,me);
	    for(i=1;i<=3;i++)
	    {
                  me->move("/d/diaoyudao/dahai_"+(random(16)+1)+".c");
	        message_vision(HIC"\n你按着罗盘指引的方向继续航行......\n\n"NOR,me);
	    }
	    if (me->query_temp("航1") )
	    {
		me->move("/d/diaoyudao/duhaitan");
		me->delete_temp("航1");
	    }
	    if (me->query_temp("航2") )
	    {
		me->move("/d/diaoyudao/matou"+random(3));
		me->delete_temp("航2");
	    }
	}
	else return notify_fail("不航海罗盘对你没有作用！\n"); 
	tell_object(me,HIY"\n你安全抵达了目的地!\n"NOR);
	return 1;
	
}
