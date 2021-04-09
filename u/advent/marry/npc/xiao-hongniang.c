// Npc: /d/ruzhou/npc/xiao-hongniang.c 小红娘  专发结婚南需知
#include <ansi.h>
inherit NPC;
int ask_marry();
int ask_guest();
void create()
{
	set_name("小红娘", ({ "xiao hongniang", "hongniang" }));
   set("long","她是一个长得很好看的小姑娘。扎了两根直直向上的小辫子，显得愈发地可爱了。\n");
   set("gender", "女性");
   set("age", 16);
   set_skill("unarmed", 20);
   set_skill("dodge", 20);
   set_skill("parry", 20);
   set_temp("apply/attack", 30);
   set_temp("apply/defense", 30);
   set_temp("apply/damage", 5);
   set("combat_exp", 3000);
   set("shen_type", 1);
   set("inquiry", ([
		"结婚"    : (: ask_marry :),
      "婚礼": (: ask_marry :),
      "结婚需知"    : (: ask_marry :),
      "《结婚需知》"    : (: ask_marry :),
      "规则"    : (: ask_marry :),
      "请客"    : (: ask_guest :),
      "邀请"    : (: ask_guest :),
   ]));
   setup();
}
void init()
{
	object me, ob;
	me = this_object();
	ob = this_player();

	::init();
	if( !ob || environment(ob) != environment() ) return;
  	say("小红娘笑嘻嘻地说道：“到红娘庄来办喜事，可得要知道一些规距，如果你想知道的话，可以问我！”\n");
}
int ask_guest()
{
	object me;
	me = this_object();

	if (me->is_busy())
		return notify_fail("小红娘说道：“你忙完后再和我说话吧！”\n");
	if( this_object()->is_fighting()||me->is_fighting() )
		return notify_fail("小红娘说道：“现在没功夫！”\n");
	if( !living(this_object()) )
		return notify_fail("你还是先想办法把小红娘救醒吧。\n");
	if ( (string)me->query("gender") == "无性")
		return notify_fail("小红娘嘻嘻哈哈地肚子都笑痛了：“你要结婚？还要请客，哈哈哈！！！”\n");
	if (((int)me->query("age") < 18) && (me->query("gender") == "男性")
		||((int)me->query("age") < 16) && (me->query("gender") == "女性"))
		return notify_fail("小红娘嘻嘻一笑道：“你和我差不多大，就想结婚请客了？不行的！”\n");
	if( (string)me->query("class")=="bonze"||(string)me->query("jobname")=="taoist" )
		return notify_fail("小红娘抿嘴一笑道：“你可别拿我开玩笑，出家人怎么能结婚呢？”\n");
   if(me->query("couple/have_couple"))
   	return notify_fail("小红娘奇道：“您不是已经结过婚了吗？怎么还想......”\n");
	write( "小红娘说：“只有到媒婆那里交了钱后，就可以让媒婆帮你放喜鹊请客人了。”\n");
	return 1;
}
int ask_marry()
{
   object ob;
   if(this_player()->query_temp("marry-book"))
		return notify_fail("小红娘有些不高兴了：“你这个人怎么会这样，刚刚不是给过你一本了吗？\n");
   message_vision("小红娘点点头，拿出一本《结婚需知》交给$N，说道：“结婚可是一辈子的大事，\n"
   "你一定要仔细看看，不要在拜堂时出洋象，弄得钱也花了，婚也没结成。”\n",this_player());
   ob=new(__DIR__"obj/marry-book");
   ob->move(this_player());
	this_player()->add_temp("marry-book",1);
	return 1;
}
