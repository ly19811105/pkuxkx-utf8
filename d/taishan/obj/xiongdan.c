
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("熊胆", ({ "xiong dan","drug" }));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		set("long", "这是一枚熊胆，可以入药。\n");
		set("value", 15000);
		set("material", "meat");
		set("drugcode",36);
		
	}
	setup();
	call_out("DownPrice",1);
}
