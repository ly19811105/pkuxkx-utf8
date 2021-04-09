#include <ansi.h>
inherit "/inherit/char/silver.c";
inherit NPC;

void create()
{
        set_name("余玠", ({"yu jie", "yu", "jie"}));
        set("gender", "男性");
        set("age", 45);
              set("title", HIR"大宋 "+HIC+"右丞相"+NOR+"兼"+HIC"枢密使"NOR);
        set("str", 25);
              set("int", 30);
        set("long", "余玠总领川蜀防务，抗击蒙元多年。\n");
        set("combat_exp", 300000);
        set("attitude", "friendly");
        set("class", "officer");
        set_skill("unarmed", 50);
        set_skill("dodge",50);
		set_skill("literate", 390);
        set_skill("parry", 50);

        set("neili", 500); 
        set("max_neili", 500);
		create_family("朝廷", 2, "官员");
		set("inquiry", ([
		"读书识字": "凡我大宋官员，愿意跟老夫学习的，老夫自当尽心教授。\n",
        "军饷" : (: ask_silver :),  
        "salary" : (: ask_silver :),  
        ]));
        set("silver_name", "军饷"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "bixue-xinfa"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "你只需要努力练功，报效朝廷，至于军饷嘛，你就来找我好了。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N沉吟着，记下了些什么。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N翻了翻记录，抬起头来。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "上回给你的军饷这么快就花完了吗？"); //时间未到不能领取时说的话
        set("msg_silver_paid", "拿着，这是你这次的军饷。"); //领取成功时说的话
        set("msg_silver_score", "$N笑着说：「为朝廷做了这么多贡献，真是辛苦你了。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N打量了你一番，笑着说：「你的功夫又有长进了。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N竖起了大拇指：「你将来一定是国家的栋梁。」\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "你还是在多做点事情吧，别老想着军饷。"); //领取例银条件均不满足时说的话        
        setup();
        carry_object("/d/song/npc/obj/cloth1")->wear();
}
int recognize_apprentice(object ob, object who)
{
        if((string)ob->query("family/family_name") != "朝廷")
//return notify_fail("看起来索额图不愿意教你！\n");
return 0;
 
      return 1;
}
int thank(object me,string ob_name)
{
	message_vision("$N接过$n呈上的"+ob_name+"，赞许不已。\n",this_object(),me);
}
int accept_object(object me,object ob)
{
	string ob_name=ob->query("name");
	if (this_object()->is_busy())
	{
		return notify_fail(this_object()->query("name")+"正忙着什么事务，你暂时不要打搅。\n");
	}
	if (ob->query("Strategy_Book_Series"))
	{
		if (me->query_temp("strategy_book_quest/"+ob->query("Strategy_Book_Series")))
		{
			command("say 你怎么有两本"+ob->query("name")+"的？");
			return 1;
		}
		me->set_temp("strategy_book_quest/"+ob->query("Strategy_Book_Series"),1);
		message_vision("$N道：“听说余相在搜寻兵书，在下不才，愿先上此书。”\n",me);
		this_object()->add_busy(3);
		call_out("thank",2,me,ob_name);
		ob->move(VOID_OB);
		destruct(ob);
		if (me->query_temp("strategy_book_quest/1")&&
			me->query_temp("strategy_book_quest/2")&&
			me->query_temp("strategy_book_quest/3")&&
			me->query_temp("strategy_book_quest/4")&&
			me->query_temp("strategy_book_quest/5")&&
			me->query_temp("strategy_book_quest/6")&&
			me->query_temp("strategy_book_quest/7")&&
			me->query_temp("strategy_book_quest/8"))
		{
			me->set("strategy_books",1);
			command("say 你居然集齐了我这里暂缺的所有八本兵书？");
			command("ah");
			command("whisper "+me->query("id")+" 这里要教给你，在临安府景灵宫可以尝试start命令。");
			tell_object(me,HIR+"你被告知了开启双倍奖励的方法，一周一次，每次开启后将有两小时的双倍奖励状态。\n"+NOR);
		}
		return 1;
	}
	return notify_fail(this_object()->name()+"不想要"+ob->query("name")+"。\n");
}