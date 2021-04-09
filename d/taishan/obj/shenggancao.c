// shenggancao 生甘草
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name(HIG"生甘草"NOR, ({ "sheng gancao", "gancao","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片生甘草，可以入药。\n");
		set("value", 2500);
		set("material", "grass");
		set("drugcode",13);
	}
	setup();
	call_out("DownPrice",1);
}
