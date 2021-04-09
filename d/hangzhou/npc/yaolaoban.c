inherit NPC;
inherit F_DEALER;
#include <ansi.h>
int ask_yaolu();
int ask_yaolu2();
int ask_yaogui(int flag);
int ask_subsidy();
int ask_job();
int ask_fail();
#define cost 1000000
#define cost2 1200000
#define COST 100000000
#define container 10000000
#define CONTAINER 100000000
#define DRUG "/d/taishan/obj/"
#define FurnaceLv 2//长租炉子的级别
void create()
{
	set_name("药铺老板", ({ "lao ban", "laoban" }));
	set("age", 52);
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
              DRUG+"dannanxing.c",
			  DRUG+"xuejie.c",
			  DRUG+"danggui.c",
			  DRUG+"yuanzhi.c",
			  DRUG+"zhusha.c",
			  DRUG+"dangshen.c",
			  DRUG+"hehuan.c",
			  DRUG+"sangzhi.c",
			  "/obj/remedy/special_formulae/ningyuanwan.c",
			  "/obj/remedy/special_formulae/ningzhendan.c",
			  "/obj/remedy/special_formulae/juqisan.c",
			  "/obj/remedy/special_formulae/heqisan.c",
			  "/obj/remedy/special_formulae/jujingji.c",
			  "/obj/remedy/special_formulae/mugucha.c",
			  "/obj/remedy/fire.c",
			 // "/obj/remedy/smallmap.c",
              
	}));
	set("CustomizedAskMode","job");
	set("job_id",1);//辨别不同药师任务
	set("inquiry", ([
			"药炉" : (: ask_yaolu :),
            "租用药炉" : (: ask_yaolu :),
			"长租药炉" : (: ask_yaolu2 :),
			"长租药柜" : (: ask_yaogui,1 :),
			"长租大药柜" : (: ask_yaogui,0 :),
			"补助" : (: ask_subsidy :),
			"subsidy" : (: ask_subsidy :),
			"job" :(:ask_job:),
			"fail" :(:ask_fail:),
			]));
	setup();
	carry_object("clone/cloth/ycloth")->wear();
	carry_object("clone/cloth/yshoe")->wear();
}
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
int Job_Limit(object me)
{
	int res;
	if (me->query_skill("alchemy",1)>120)
	res=8;
	else if (me->query_skill("alchemy",1)>90)
	res=6;
	else if (me->query_skill("alchemy",1)>60)
	res=5;
	else
	res=4;
	if (F_PRO->pro_class(me)=="alchemy")
	res+=1;
	return res;
}
int Gene_tmpPres(object me)
{
	string *pre=({"保","护","守","卫","利","静"}),*pre2=({"心","肝","脾","胃","胆","肺"}),*post=({"丹","丸","散","膏","剂","药"}),name;
	int drug_code,drug_code2;
	object target,where,where2,ob;
	drug_code="/obj/remedy/reference"->random_drug("herb",100)["id"];
	drug_code2="/obj/remedy/reference"->random_drug("herb",100)["id"];
	while (drug_code==drug_code2)
	drug_code2="/obj/remedy/reference"->random_drug("herb",100)["id"];
	name=pre[random(sizeof(pre))]+pre2[random(sizeof(pre2))]+post[random(sizeof(post))];
	command("whisper "+me->query("id")+" 我现在正缺一副"+name+"，你帮我炼出来。");
	target=new(__DIR__"yaonpc");
	where = TASK_D->random_place();
	while (!objectp(where) || 
         !where->isroom()||
         TASK_D->place_belong(where)=="不明区域"||
         TASK_D->place_belong(where)=="未知区域"||
		 where->query_location()=="/d/gaibang/"||
         base_name(where) == "/adm/daemons/taskd")
	where = TASK_D->random_place();
	target->set("owner",me);
	target->move(where);
	where2 = TASK_D->random_place();
	while (!objectp(where2) || 
         !where2->isroom()||
         TASK_D->place_belong(where2)=="不明区域"||
         TASK_D->place_belong(where2)=="未知区域"||
		 where->query_location()=="/d/gaibang/"||
         base_name(where2) == "/adm/daemons/taskd")
	where2 = TASK_D->random_place();
	command("whisper "+me->query("id")+" 它的主药是"+"/obj/remedy/reference"->interpret("*"+drug_code)+"，在我一个熟人"+target->query("name")+"手上，他现在在"+TASK_D->place_belong(where)+"一带，辅药是"+"/obj/remedy/reference"->interpret("*"+drug_code2)+"，你可以在"+TASK_D->place_belong(where2)+"挖到。");
	ob=new(__DIR__"obj/yaochu");
	ob->move(me);
	message_vision("$N给了$n一"+ob->query("unit")+ob->query("name")+"。\n",this_object(),me);
	me->set_temp("AlchemyJob/"+this_object()->query("job_id")+"/start",1);
	me->set_temp("AlchemyJob/"+this_object()->query("job_id")+"/name",name);
	me->set_temp("AlchemyJob/"+this_object()->query("job_id")+"/drug1",drug_code);
	me->set_temp("AlchemyJob/"+this_object()->query("job_id")+"/drug2",drug_code2);
	me->set_temp("AlchemyJob/"+this_object()->query("job_id")+"/where",where2);
	me->set_temp("myTempPrescription",(["name":name,"raws":(["*"+drug_code:1,"*"+drug_code2:1,]),"product":"/obj/remedy/fakedrug","product_no":1,"period":10+random(10),"maker_level":0,"improve_level":3000,"skill_points":Job_Limit(me)*10,"fail_possibility":0,"furnace_lv":0,"phase_color":({0,1,2}),"temp_prescription":1]));
	return 1;
}
int ask_fail()
{
	object me=this_player();
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	me->add_busy(1);
	if (!me->query_temp("AlchemyJob/"+this_object()->query("job_id")+"/start"))
	{
		command("say 我不记得给过你任务了。\n");
		return 1;
	}
	command("say 药医不死病，既然炼不出"+me->query_temp("AlchemyJob/"+this_object()->query("job_id")+"/name")?
	me->query_temp("AlchemyJob/"+this_object()->query("job_id")+"/name"):"这种药，那就算了吧。\n");
	me->delete_temp("AlchemyJob/"+this_object()->query("job_id"));
	return 1;
}
int ask_job()
{
	object me=this_player();
	mixed *tm=localtime(time());
    string date=sprintf("%d-%d-%d", tm[5], tm[4]+1, tm[3]);
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	message_vision(HIW"$N"+HIW+"看着$n"+HIW+"一脸凝重地神情，上前打听有什么可以帮忙。\n"NOR,me,this_object());
	me->add_busy(1);
	if (me->query_skill("alchemy",1)<25)
	{
		command("say 我的这个任务对药道需要一定认识，你暂时不能胜任。");
		return 1;
	}
	if (me->query("AlchemyJob/"+this_object()->query("job_id")+"/date")!=date)
	{
		me->set("AlchemyJob/"+this_object()->query("job_id")+"/date",date);
		me->set("AlchemyJob/"+this_object()->query("job_id")+"/times",0);
	}
	if (me->query("AlchemyJob/"+this_object()->query("job_id")+"/times")>Job_Limit(me))
	{
		command("say 我这暂时也没什么事了。");
		return 1;
	}
	if (me->query_temp("AlchemyJob/"+this_object()->query("job_id")+"/start"))
	{
		command("say 我不是给你过一个任务嘛？");
		return 1;
	}
	me->add("AlchemyJob/"+this_object()->query("job_id")+"/times",1);
	return Gene_tmpPres(me);
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
int ask_yaogui(int flag)
{
	object me=this_player();
	string size="medium",ob_name="大药柜";
	int payment=CONTAINER;
	if (flag)
	{
		size="small";
		ob_name="药柜";
		payment=container;
	}
	if (F_PRO->pro_class(me)!="alchemy")
	{
		command("say 我只能把药柜租给需要的药师。");
		return 1;
	}
	if (time()<me->query("RentCabinet/time"))
	{
		command("say 我不是已经租了药柜给你吗？");
		return 1;
	}
	if (me->query("balance")<payment)
	{
		command("say 如要要租用药柜，我要从你账上转走"+MONEY_D->money_str(payment)+"，你似乎没那么多钱。");
		return 1;
	}
	if (!me->query_temp("RentCabinet"))
	{
		me->set_temp("RentCabinet",1);
		command("say 如果确定要租，请再次ask laoban about 长租"+ob_name+"，我将从你账上扣款"+MONEY_D->money_str(payment)+"。");
	}
	else
	{
		me->delete_temp("RentCabinet");
		me->add("balance",-payment);
		me->set("RentCabinet/time",time()+1296000);
		me->set("RentCabinet/size",size);
		command("say 我已经让人把药柜送到你家了，可以使用15天。");
		tell_object(me,this_object()->query("name")+"从你账上扣款"+MONEY_D->money_str(container)+"。\n");
	}
	return 1;
}
int ask_yaolu2()
{
	object me=this_player();
	if (F_PRO->pro_class(me)!="alchemy")
	{
		command("say 我只能把药炉租给需要的药师。");
	}
	else if (time()>me->query("RentFurnace/time"))
	{
		command("say 你要给我"+MONEY_D->money_str(COST)+"，我才会把药炉长租给你。");
	}
	else
	{
		command("say 我已经让人把药炉送到你家了。");
	}
	return 1;
}
int ask_yaolu()
{
	object me=this_player();
	if (time()>me->query_temp("PermitAlchemy")&&time()>me->query_temp("PermitAlchemy2"))
	{
		command("say 你要给我"+MONEY_D->money_str(cost)+"，我才会把药炉租给你一小时。\n");
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
		if (ob->value() >= COST&&F_PRO->pro_class(who)=="alchemy")
		{	
			who->set("RentFurnace/time",time()+1296000);
			who->set("RentFurnace/FurnaceLv",FurnaceLv);
			command("say 既然你给了钱，那我就租给你十五天，让人送到你家了。");
		}
		else if (ob->value() >= cost2)
		{
			who->set_temp("PermitAlchemy2",time()+3600);
			command("say 既然你给了钱，那我就租给你一小时，进去(enter)吧。");
		}
		else
		{
			who->set_temp("PermitAlchemy",time()+3600);
			command("say 既然你给了钱，那我就租给你一小时，进去(enter)吧。");
		}
		ob->move(VOID_OB);
		destruct(ob);
		command("thanks");
		return 1;
	}
	if (who->query_temp("AlchemyJob/"+this_object()->query("job_id")+"/start")&&
	who->query_temp("AlchemyJob/"+this_object()->query("job_id")+"/name")&&
	ob->query("producer")==who->query("id"))
	{
		sk_pts=Job_Limit(who)*3+random(Job_Limit(who)*2);
		who->improve_skill("alchemy",sk_pts);
		message_vision(HIC+"$N"+HIC+"指点了$n"+HIC+"炼丹术方面的知识！\n"+NOR,this_object(),who);
		ob->move(VOID_OB);
		destruct(ob);
		who->delete_temp("AlchemyJob/"+this_object()->query("job_id"));
		return 1;
	}
	return notify_fail("除了租药炉的钱，药铺老板啥也不要。\n");
}