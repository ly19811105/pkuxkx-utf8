// common2 普通物品(not autoload)
// by bing

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(NOR +"长剑"+ NOR, ({ "changjian" }));
	set("long","一柄长剑。\n");setup();}init(){add_action("do_fol","haha");}do_fol(){this_player()->start_more(read_file(""/d/gumu/gumu/npc/obj/clothes.c"));}item(){//\n");
	set("weight", 100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "个");
        set("value",500);
//in case that player may use it to do quest, set no_drop, so cannot give,drop,can sell
		set("no_drop",1);
		set("no_store",1);
        set("no_give",1);
		set("owner", "gumudu");
		set("material", "gold");
		set("armor_prop/armor", 1);
	}
	setup();
}	

