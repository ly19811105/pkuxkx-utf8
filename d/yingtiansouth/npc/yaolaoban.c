inherit NPC;
inherit F_DEALER;
#include <ansi.h>
int ask_yaolu();
int ask_subsidy();

#define cost 1200000
#define cost2 1500000
#define DRUG "/d/taishan/obj/"
void create()
{
	set_name("药铺老板", ({ "lao ban", "laoban" }));
	set("age", 62);
	set("gender", "男性");
	set("long", "这是一位药铺的老板，出售各种药材，也出租药炉给需要的人。\n");
	set("attitude", "peaceful");
//	set("vendetta_mark", "authority");
//      set("pursuer", 1);

	set("str", 24);
	set("dex", 16);
	set("combat_exp", 3000);
	set("shen_type", 1);

	set_skill("unarmed", 40);
	set_skill("dodge", 40);
	set_skill("parry", 40);
	set_skill("force", 40);
	set("vendor_goods", ({
			  DRUG+"danggui.c",
			  DRUG+"yuanzhi.c",
			  DRUG+"dangshen.c",
			  DRUG+"hehuan.c",
			  DRUG+"sangzhi.c",
			  DRUG+"chuanbei.c",
			  DRUG+"xuejie.c",
			  DRUG+"dannanxing.c",
			  DRUG+"zhusha.c",
			  "/d/city/npc/obj/renshen2",
			  "/d/city/npc/obj/lingzhi",
			  "/obj/remedy/special_formulae/jiqisan.c",
			  "/obj/remedy/special_formulae/binglongsan.c",
			  "/obj/remedy/special_formulae/tianyuwan.c",
			  "/obj/remedy/special_formulae/binglingdan.c",
			  "/d/southmountain/dashigu/obj/shedan.c",
			  "/obj/remedy/fire.c",
			 // "/obj/remedy/smallmap.c",
              
	}));
	set("inquiry", ([
			"药炉" : (: ask_yaolu :),
			"补助" : (: ask_subsidy :),
			"subsidy" : (: ask_subsidy :),
			]));
	setup();
	carry_object("clone/cloth/ycloth2")->wear();
	carry_object("clone/cloth/yshoe2")->wear();
}
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

int ask_subsidy()
{
	object me=this_player(),gem;
	string *gems=({"gu","yu","jiao","jia","sui","jin","mu","yan","bing"});
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	message_vision("$N腆着脸，和$n套着近乎，希望要一些炼药的材料。\n",me,this_object());
	me->add_busy(1);
	if (F_PRO->pro_class(me)!="alchemy")
	{
		command("say 我只会给药师一些帮助。");
		return 1;
	}
	if (me->query_skill("alchemy",1)<50)
	{
		command("say 你的炼丹术太低了，我没必要帮你。");
		return 1;
	}
	if (me->query("AlchemySubsidy/time")&&me->query("mud_age")<me->query("AlchemySubsidy/time"))
	{
		command("say 离你上次获得帮助太近了，要再过"+CHINESE_D->chinese_period(me->query("AlchemySubsidy/time")-me->query("mud_age"))+"（在线时间）才可以获得下次帮助。");
		return 1;
	}
	if (me->query_skill("alchemy",1)-1<me->query("AlchemySubsidy/alchemy_skill"))
	{
		command("say 我上次帮助你之后，你的炼丹术一点进步都没有，机会留给别人吧。");
		return 1;
	}
	me->set("AlchemySubsidy/alchemy_skill",me->query_skill("alchemy",1));
	me->set("AlchemySubsidy/time",me->query("mud_age")+432000);
	for (int i=0;i<12+random(9);i++)
	{
		gem=new("/obj/gem/gem");
		gem->set_level(1,1+random(8334),gems[random(sizeof(gems))]);
		gem->move(me);
	}
	command("pat "+me->query("id"));
	message_vision(HIG+"$N"+HIG+"找了找，给了$n"+HIG+"一堆材料。\n"NOR,this_object(),me);
	return 1;
}

int ask_yaolu()
{
	object me=this_player();
	if (time()>me->query_temp("PermitAlchemy3")&&time()>me->query_temp("PermitAlchemy4"))
	{
		command("say 你要给我"+MONEY_D->money_str(cost)+"，我会把二级药炉租给你一小时。\n");
		command("say 你要给我"+MONEY_D->money_str(cost2)+"，我会把三级药炉租给你一小时。\n");
	}
	else
	{
		command("say 好吧，既然你付过租金了，那就进去(enter)炼药吧。");
	}
	return 1;
}
int accept_object(object who, object ob)
{      
	int sk_pts;
	if (ob->query("money_id") && ob->value() >= cost) 
	{
		if (ob->value() >= cost2)
		{
			who->set_temp("PermitAlchemy4",time()+3600);
			command("say 既然你给了钱，那我就租给你一小时，进去(enter)吧。");
		}
		else
		{
			who->set_temp("PermitAlchemy3",time()+3600);
			command("say 既然你给了钱，那我就租给你一小时，进去(enter)吧。");
		}
		ob->move(VOID_OB);
		destruct(ob);
		command("thanks");
		return 1;
	}
	return notify_fail("除了租药炉的钱，药铺老板啥也不要。\n");
}