//Created By Pal
//cometh@tom.com
//2003.10.12
//店小二模板
//last modify 2003.10.14
#pragma save_binary

#include <ansi.h>
#include <changecolor.h>
inherit NPC;
#include "/data/home/std_file/npc/stdwaiter.c"
void create()
{
	set_name("店小二", ({ "dian xiaoer","waiter" }) );
	set("long",
		"这是致远阁客栈总店的店小二。\n");
	set("attitude", "peaceful");
	set("age", 20+random(20));
	set("owner","pal");//所有者
	set("selfcreate",1);
	set("no_get",1);
/*	set("inquiry", ([//似乎存不进去，这样一restore立即出错
		"收入":(: give_money :),
		"装修":(: upgrade :),
		"修理":(: repaire :),
		"住店":(: put_up :),
		"休息":(: put_up :),
	]));
*/
	restore();
	setup();
}