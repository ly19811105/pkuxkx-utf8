
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("首乌", ({ "shou wu","drug" }));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "节");
		set("long", "这是一节首乌，可以入药。\n");
		set("value", 500);
		set("material", "grass");
		set("drugcode",34);
		
	}
	setup();
	call_out("DownPrice",1);
}
