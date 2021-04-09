//修改了下ask 上柱国的提示信息，by yhzzyahoo
#include <ansi.h>
inherit "/inherit/char/silver.c";
inherit NPC;
#include <title.h>
string ask_leadership();
int ask_wang();
void create()
{
        set_name("乔行简", ({"qiao xingjian", "qiao", "xingjian"}));
        set("gender", "男性");
        set("age", 55);
              set("title", HIR"大宋"+HIY" 鲁国公 "+HIC+"平章军国重事"+NOR);
        set("str", 25);
              set("int", 70);
        set("long", "乔行简是光宗绍熙进士。\n历任参知政事、同知樞密院事、知樞密院事、右丞相、左丞相。\n");
        set("combat_exp", 600000);
        set("attitude", "friendly");
        set("class", "officer");
        set_skill("unarmed", 50);
        set_skill("dodge",50);
		set_skill("literate", 390);
        set_skill("parry", 50);
		set("book_count", 1);
        set("neili", 500); 
        set("max_neili", 500);
        create_family("朝廷", 2, "官员");
        set("inquiry", ([
		"晋升上柱国": (: ask_wang :),
		"五经" : (: ask_leadership :),
        "读书识字": "凡朝廷弟子，我都会指点一二的！\n",
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
return 0;
 
      return 1;
}
string ask_leadership()
{
	object ob;
	if (this_player()->query("class") != "officer")
	return this_object()->query("name")+"转过身去，忙别的事去了。\n";
	if (this_player()->query("pin") > 3)
	return "你官阶尚低，以后再来问我吧。";
	if (query("book_count") < 1)
	return "「春秋」已经被借走了。";
	add("book_count", -1);
	ob = new("/d/hangzhou/obj/books/book_leadership_5");

	ob->move(this_player());

	return "五经是做官的基础，这本「春秋」你拿回去读读吧。";
}
int check_shangzhuguo(object me)
{
	if (me->query("exp/biwu")-me->query("chaoting/SZG/biwu")<100000)//比武增加10万经验
	{
		command("say 你在比武中并没有为朝廷争得足够荣誉。到目前为止，你共额外完成了"+(me->query("exp/biwu")-me->query("chaoting/SZG/biwu"))+"点比武经验，共需10万！");
		return 0;
	}
	if (me->query("newjobs/completed/mzj")-me->query("chaoting/SZG/mzj")<200)//mzj增加200
	{
		command("say 你没有做够足够次数的都府刺杀任务。到目前为止，你共额外完成了"+(me->query("newjobs/completed/mzj")-me->query("chaoting/SZG/mzj"))+"次刺杀任务，共需200次！");
		return 0;
	}
	if (me->query("exp/xytask")-me->query("chaoting/SZG/xytask")<500000)//xytask增加50万经验
	{
		command("say 你在襄阳没有立下足够功勋。到目前为止，你共额外完成了"+(me->query("exp/xytask")-me->query("chaoting/SZG/xytask"))+"点襄阳功勋，共需50万！");
		return 0;
	}
	if (me->query("score")-me->query("chaoting/SZG/score")<400)//scorek增加400
	{
		command("say 你的贡献度没有提升足够。到目前为止，你共额外增加了"+(me->query("score")-me->query("chaoting/SZG/score"))+"点朝廷功勋，共需400点！");
		return 0;
	}
	return 1;
}
int ask_wang()
{
	object me=this_player();
	if (me->query("class") != "officer")
	{
		command ("say 你不是朝廷官员，问这个干吗？");
		return 1;
	}
	if (me->query("family/family_name")!="朝廷")
	{
		command ("say 你不是朝廷官员，问这个干吗？");
		return 1;
	}
	if (me->query("pin")!=1)
	{
		command ("say 等你到了一品再来问这个吧。");
		return 1;
	}
	if (me->query("chaoting/wang")||me->query("chaoting/jiawang"))
	{
		command("say 你已经是上柱国了。");
		return 1;
	}
	if (!me->query("chaoting/SZG"))
	{
		me->set("chaoting/SZG/biwu",me->query("exp/biwu"));
		me->set("chaoting/SZG/mzj",me->query("newjobs/completed/mzj"));
		me->set("chaoting/SZG/xytask",me->query("exp/xytask"));
		me->set("chaoting/SZG/score",me->query("score"));
		command("whisper "+me->query("id")+" 比武中再获得十万点经验，保卫襄阳再获得五十万点经验，再完成都府行刺任务两百次，贡献度增加四百点后，");
		command("whisper "+me->query("id")+" 朝廷将赠予你上柱国，"+HIY+"骠骑大将军"+NOR+"。");
		return 1;
	}
	if (check_shangzhuguo(me)!=1)
	return 1;
	me->set("chaoting/wang",1);
	me->set("title", HIR+"大宋 "+HIY+"骠骑大将军"NOR);
	me->set_title(TITLE_RANK, me->query("title"));
	command("say 恭喜"+me->query("name")+"晋升上柱国了。");
	return 1;
}