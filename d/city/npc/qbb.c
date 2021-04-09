// 清军细作

#include <ansi.h>


inherit __DIR__"qingbing_base2.c";

void create()
{	
	int i= random(2);
	int lv=300;
	set_name(surname[random(sizeof(surname))]+"."+givenname[random(sizeof(givenname))], ({ "niulu ezhen", "ezhen"}));
	set("title", HIG+title[random(sizeof(title))]+" 固山额真"NOR);
	set("gender", i?"男性":"女性");
	set("age", 30+random(30));

	set("long","这是"+query("title")+"，武功不同凡响。\n");
	set("attitude", "peaceful");
	set("combat_exp", 2000000);
	set("str", 20+random(5));
	set("int", 20+random(5));
	set("con", 20+random(5));
	set("dex", 20+random(5));
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 5000);
	set("max_neili", 20000);
	set("neili", 5000);
	set("neili", 20000);
	set("skfxiang",1);
	set_temp("apply/armor", 100);
	set("jingli", 20000);
	set("max_jingli", 20000);
	set_skill("dodge",lv);
	set_skill("parry",lv);
	set_skill("force",lv);
	set_skill("strike",lv);
	set_skill("longfeng-xiang",lv);
	set_skill("bixue-xinfa",lv);
	set_skill("juehu-zhang",lv);
	set_skill("fenglei-dao",lv);
	set_skill("blade",lv);
	map_skill("force", "bixue-xinfa");
	map_skill("dodge", "longfeng-xiang");
	map_skill("strike", "juehu-zhang");
	map_skill("parry", "juehu-zhang");
	map_skill("blade", "fenglei-dao");
	prepare_skill("strike", "juehu-zhang");
	set("no_get", 1);
	
	setup();
	
	
	carry_object(__DIR__"items/cloth2")->wear();
	carry_object(__DIR__"items/blade")->wield();
	
}

void init()
{
	call_out("kill",1);
	return;
}