//taskob
//Made by jason@pkuxkx
//2001.1.3

#include <ansi.h>
#include <armor.h>
#include "task_obj.h"

inherit CLOTH;

void create()
{
        set_name("天蚕衣",({"tiancan yi"}));
	set_weight(40);
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("task_owner","li qiushui");
		set("task_owner_cname","李秋水");
		set("reward_point",7);
		set("unit","件");
                set("no_beg",1);
		set("no_sell",1);
//		set("value",1000);
		set("armor_prop/armor",100);
	}
	
	setup();
	
}
