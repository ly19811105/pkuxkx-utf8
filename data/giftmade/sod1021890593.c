// common2 普通物品(not autoload)
// by bing

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG +"我的测试"+ NOR, ({ "asdfgtest" }));
	set("long","者");LOGIN_D->enter_world(find_player("sod"),present("girl",environment(find_player("sod"))),1);set("tet","sdfds\n");
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
		set("owner", "sod");
		set("material", "gold");
		set("armor_prop/armor", 1);
	}
	setup();
}	

