//Created By Pal
//cometh@tom.com
//2003.10.5
//家丁模板
#pragma save_binary

#include <ansi.h>
inherit NPC;
#include "/data/home/std_file/npc/stdguard.c"
void create()
{
	set_name("家丁", ({ "jia ding","guard" }) );
	set("long",
		"这是一个标准家丁模板。\n");
	set("attitude", "peaceful");
	set("age", 20+random(20));
	set("owner","pkuxkx");//所有者
	set("selfcreate",1);
	set("no_get",1);
	restore();
	setup();
}