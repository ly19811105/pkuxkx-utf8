
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("三七", ({ "san qi","drug" }));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片三七，可以入药。\n");
		set("value", 100);
		set("material", "grass");
		set("drugcode",38);
		
	}
	setup();
	call_out("DownPrice",1);
}
