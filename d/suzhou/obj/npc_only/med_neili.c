#include <ansi.h>
inherit __DIR__"npc_item";
#include "/d/suzhou/obj/npc_only/drug.h"
void create()
{
	set_name("中级内力丹", ({ "normal neili dan","neili dan", "dan"}) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		set("long", "这是一枚中级内力丹<NPC专用>。\n");
		set("value", 5000);
		set("material", "herb");
		set("drug_type","neili");
		set("effect",2000);
		set("anti_job",({"jobs/completed/huyidao"}));
	}
	setup();
}

