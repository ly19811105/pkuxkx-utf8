
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("朱砂", ({ "zhu sha","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "包");
		set("long", "这是一包朱砂，可以入药。\n");
		set("value", 500);
		set("material", "stone");
		set("drugcode",28);
		
	}
	setup();
	call_out("DownPrice",1);
}
