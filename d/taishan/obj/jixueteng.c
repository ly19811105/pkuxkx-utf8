
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name(RED"鸡血藤"NOR, ({ "jixue teng","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片鸡血藤，可以入药。\n");
		set("value", 2500);
        set("drugcode",1);
		set("material", "grass");
		
	}
	setup();
	call_out("DownPrice",1);
}
