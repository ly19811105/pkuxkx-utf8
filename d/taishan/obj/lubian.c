
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("鹿鞭", ({ "lu bian","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "根");
		set("long", "这是一根鹿鞭，可以入药。\n");
		set("value", 4500);
		set("material", "meat");
		set("drugcode",16);
		
	}
	setup();
	call_out("DownPrice",1);
}
