// furen.c
inherit NPC;
#include <ansi.h>

void create()
{
	set_name("庄夫人", ({ "san furen", "san","furen"}));
	set("title", "庄家三少奶奶" );
	set("nickname", HIW "未亡人" NOR);
	set("long",  "\n只见她约莫二十六七年纪,全身缟素,不施脂粉,脸色苍白.\n");
	set("gender", "女性");
	set("age", 25);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 30);
	set("no_get", 1);

	set("max_qi", 1000);
	set("max_jing", 400);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 100);
	set("combat_exp", 100000);
	set("score", 50000);

	set_skill("force", 90);
	set_skill("dodge", 90);
	set_skill("unarmed", 90);
	set_skill("sword", 90);
	set_skill("taiji-jian", 80);
	set_skill("tiyunzong",90);
	map_skill("dodge", "tiyunzong");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");

	set_temp("apply/attack", 35);
	set_temp("apply/attack", 35);
	set_temp("apply/damage", 35);
        set("inquiry", ([
		"鳌拜" : "鳌拜是我家的大仇人。",
		"吴之荣" :"我一定要手刃了这个奸贼。",
		"礼物" :  "这样礼物可不一般,她就是我的好丫环双儿。",
		"双儿" :  "这小丫头跟随我多年,做事也还妥当。",
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
	object ob;
	ob = this_player();

	if( interactive(ob) && !is_fighting() )
	say( "庄夫人说道：很久没有人来了,这位" + RANK_D->query_respect(ob)
				+ "，可知道我相公的下落吗?\n");
}

int accept_object(object me, object ob)
{
	int i;
	if( !me || environment(me) != environment() ) return 0;
	if ( !objectp(ob) ) return 0;
	if ( !present(ob, me) ) return notify_fail("你没有这件东西。");
	if ( (string)ob->query("id") == "wu zhirong")
	{
	write(HIC "庄夫人大喜道：狗贼,看打!想不到你也有今天！！！\n");
	write(HIC "庄夫人一刀就砍下了吴之荣的狗头！！\n");
        call_out("destroying", 1, this_object(), ob);
	write(HIC "\n庄夫人说道：这位" + RANK_D->query_respect(me)+",如此大恩大德,妾身实不知何以为报。\n");
	write(HIC "我想送恩公一件礼物,务请勿却是幸。\n"NOR);
	//set一个mark，以供合并地图使用
	me->set_temp("luding/wu", 1);
	return 1;
        }
	if ( (string)ob->query("name") == "「明书辑略」")
	{
	 write(HIC "\n庄夫人说道：这位" + RANK_D->query_respect(me)+",多谢了。\n");
	 write(HIC "唉,你要能帮我找到吴之荣这狗贼就好了。\n"NOR);
	return 1;
        }

	 return 0;
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
