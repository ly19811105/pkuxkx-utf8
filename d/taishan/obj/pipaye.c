
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("枇杷叶", ({ "pipa ye","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片枇杷叶，可以入药。\n");
		set("value", 100);
		set("material", "grass");
		set("drugcode",18);
		
	}
	setup();
	call_out("DownPrice",1);
}
