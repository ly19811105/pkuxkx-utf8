
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("合欢", ({ "he huan","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片合欢，可以入药。\n");
		set("value", 1500);
		set("material", "grass");
		set("drugcode",9);
	}
	setup();
	call_out("DownPrice",1);
}
