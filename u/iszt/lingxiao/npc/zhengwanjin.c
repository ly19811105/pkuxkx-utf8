// Created by iszt@pkuxkx, 2007-02-15

#include "setdizi.h"

inherit "/inherit/char/banker.c";

void create()
{
	setcreate(120);
	set_name("郑万金", ({"zheng wanjin", "zheng", "wanjin"}));
	set("title", "钱庄掌柜");
	set("nickname", HIY"日挣万金"NOR);
	set("gender", "男性");
	set("age", 34);
	set("long", "这是一位胖胖的钱庄掌柜，正拿着算盘噼里啪啦的拨着。\n");

	set("rank_info/respect", "掌柜的");
	set("rank_info/rude", "奸商");
	add("inquiry", ([
		"name" : "在下郑万金，呵呵，呵呵。",
		"here" : "这里是凌霄城中唯一的钱庄，呵呵，呵呵。",
	]) );
	setfamily(6);

	setup();
	setequip();
}

void init()
{
	npc::init();
	banker::init();
}

void attempt_apprentice(object ob)
{
	setapp(ob);
}