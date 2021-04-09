// daodejing-i.c
//seagate@pkuxkx 2010/10/21 增加书籍阅读功能

inherit ITEM;
inherit "/newbiequest/book";

void create()
{
	set_name( "道德经「上卷」", ({ "jing", "daode jing" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一册道德经「上卷」，由体道第一始至去用第四十止。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"taoism",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost": 20, 	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	50,	// the maximum level you can learn
		]) );
	}
	set("pages",get_pages(query("name")));
	set("page",1);
}

#include "/newbiequest/wudang/quest_chanting.h"