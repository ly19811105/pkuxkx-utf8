
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name("胆南星", ({ "dan nanxing","drug" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片胆南星，可以入药。\n");
		set("value", 500);
		set("material", "grass");
		set("drugcode",26);
		
	}
	setup();
	call_out("DownPrice",1);
}
