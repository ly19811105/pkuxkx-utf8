
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("鹿茸", ({ "lu rong","drug" }));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "块");
		set("long", "这是一块鹿茸，可以入药。\n");
		set("value", 20000);
		set("material", "meat");
		set("drugcode",35);
		
	}
	setup();
	call_out("DownPrice",1);
}
