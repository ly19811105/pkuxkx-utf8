
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("灵脂", ({ "ling zhi","drug" }));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片灵脂，可以入药。\n");
		set("value", 500);
		set("material", "grass");
		set("drugcode",37);
		
	}
	setup();
	call_out("DownPrice",1);
}
