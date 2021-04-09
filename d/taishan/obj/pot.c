// hotwater.c 热水
// by Zine
#include <ansi.h>
inherit "/d/yingtianfu/new_config/item.c";
inherit F_LIQUID;

void create()
{
	set_name("水壶", ({ "pot", "shui hu"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "组");
		set("long", "这是一组三只水壶。\n");
		set("value", 60);
		set("material", "iron");
        set("max_liquid", 50);
		
	}
    set("liquid", ([
		"type": "water",
		"name": "水",
		"remaining": 0,
		"drunk_apply": 10,
	]));
	setup();
}

void init()
{
	add_action("do_guan", "guan");
}

int do_guan()
{
    object ob=this_object();
    object me=this_player();
    object hw;
    int i;
    if (base_name(environment(me))!="/d/xinyang/tqc")
    {
        return 0;
    }
    else
    {
        for (i=0;i<3;i++)
        {
            hw=new("/d/taishan/obj/hotwater");
            hw->move(me);
        }
        message_vision("$N用水壶灌了三壶温泉水上来。\n",me);
        destruct(ob);
        return 1;
    }
}