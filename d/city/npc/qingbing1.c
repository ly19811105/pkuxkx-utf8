// 清军细作

#include <ansi.h>

inherit __DIR__"qingbing_base.c";

void create()
{
	
	int i= random(2);

	set_name(surname[random(sizeof(surname))]+"."+givenname[random(sizeof(givenname))], ({ "xi zuo", "spy"}));
	set("title", title[random(sizeof(title))]+"细作");
	set("gender", i?"男性":"女性");
	set("age", 30+random(30));

	set("long","这是"+query("title")+"，不解决他，追兵会源源不断的跟上。\n");
	set("attitude", "peaceful");
	set("combat_exp", 5000000);
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
	set_temp("apply/armor", 100);
	set("jingli", 20000);
	set("max_jingli", 20000);
	set_skill("strike", 500);
	set_skill("cuff", 500);
	set_skill("hand", 500);
	set_skill("dodge", 500);
	set_skill("sword", 500);
	set_skill("force", 500);
	set_skill("parry", 500);
	set_skill("blade", 500);
	set_skill("hammer", 500);
	set_skill("axe", 500);
	set_skill("staff", 500);
	set_skill("literate", 500);
	set_skill("whip", 500);
	set("no_get", 1);
	set("random_npc",1);
	set("qingbing",1);
    setup();
	
	carry_object(__DIR__"items/cloth2")->wear();
	
	call_out("kill2", 1);
	call_out("dest", 180);
}

