// Modified by iszt@pkuxkx, 2007-03-27

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

int find();

void create()
{
	set_name("西夏公主", ({ "princess", "gongzhu"}));
	set("title", HIM"梦姑"NOR);
	set("long", "西夏国的公主，是西夏国第一美女。然而不知道为什么，她眉间微微有幽怨之色。\n");
	set("gender", "女性");
	set("age", 20);
	set("attitude", "peaceful");
	set("str", 30);
	set("int", 40);
	set("spi", 50);
	set("per", 36);

	set("shen_type",1);set("score",500);setup();

	carry_object("/clone/cloth/female3-cloth.c")->wear();
}

void init()
{
	set("inquiry", ([
		"梦郎" : (: find :),
	]));
}

int find()
{
	object me = this_player();
	object she = this_object();
	object ob;
        if(file_name(environment(she)) != query("startroom"))
		return 0;
	if (!me->query_temp("lingjiu/find"))
	{
        if (base_name(environment(she))=="/d/lingzhou/gongzhu")
        {
            message_vision(CYN"$N对$n说道：「你说的什么呀，我听不懂！」\n"NOR, she, me);
            message_vision(CYN"\n$N对左右吩咐了几句。\n"NOR, she);
            message_vision(CYN"几位宫女极有礼貌地对$N一点头，说「请您出去吧」，拥着$N走出大殿。\n"NOR,me);
            me->move("/d/lingzhou/gongsquare");
            return 1;
        }
        else
        {
            command("blush");
            return 1;
        }
	}
	if (me->query_temp("/lingjiu/find")==1)
	{
		message_vision (CYN"$N对$n说道：「是梦郎哥哥让你来找我的？」\n"NOR,she,me);
		message_vision (CYN"\n$N喜不自胜：「终于有梦郎哥哥的消息了！」\n"NOR,she);
		command("jump "+me->query("id"));
		command("sing");
		command("thank "+me->query("id"));
		message_vision (CYN"$N对$n说道：「我这里写了一封信，麻烦你带给梦郎哥哥。」\n"NOR,she,me);
		message_vision (CYN"$N交给$n一封信。\n"NOR,she,me);
		ob=new("/d/lingjiu/obj/letter");
		ob->move(me);
		me->set_temp("lingjiu/find",2);
	}
	else if (me->query_temp("/lingjiu/find")==2)
		command("say 我不是给你信了吗，赶快帮我送过去吧！");
	return 1;
}
