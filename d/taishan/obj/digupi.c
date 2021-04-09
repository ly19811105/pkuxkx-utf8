// digupi.c 地骨皮
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("地骨皮", ({ "digu pi", "pi","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片枸杞的根皮，可以入药。\n");
		set("value", 1500);
		set("material", "grass");
		set("drugcode",11);
	}
	setup();
	call_out("DownPrice",1);
}
