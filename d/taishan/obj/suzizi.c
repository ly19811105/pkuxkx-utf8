
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("紫苏子", ({ "zisu zi","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片紫苏子，可以入药。\n");
		set("value", 3500);
		set("material", "grass");
		set("drugcode",22);
		
	}
	setup();
	call_out("DownPrice",1);
}
