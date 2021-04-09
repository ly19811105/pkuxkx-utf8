// wang.c
// by paladin

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string answer_marr(object me);
int do_look(string arg);
void remove_look(object ob);

void create()
{
	set_name("王语嫣", ({ "wang yuyan", "wang" }) );

	set("long", @LONG
这位绝色美女看着你，你刹那间惊为天人，心中大呼：“我好福气呀！
如此俏佳人看了我一眼！。
LONG
);
	set("gender", "女性" );
	create_family("琅瑗福地", 1, "公主");
	set("rank_info/respect", "神仙姐姐");
	set("attitude", "friendly");

//	set("vendor_goods", ([
//		"名称":__DIR__"obj/something.c",
//		"名称":__DIR__"obj/anotherting.c",
//	]) );
	set("age", 16);
	set("str", 10);
	set("cor", 30);
	set("cps", 20);
	set("per", 50);
	set("int", 40);
	set("max_force", 100);
	set("force", 100);
	set("force_factor", 2);
	set("combat_exp",10000);
            create_family("天龙寺", 1, "贵宾");


	set("chat_chance_combat", 25);
	set("chat_msg_combat", ({
		(: command("hehe") :),
		"王语嫣秀眉微蹙，说道：喂！怎么如此不识好歹呀？
是不是见我美丽起了歹念呀？我可不好惹的噢！\n",
		"王语嫣不住地望著屋外：你还是快走吧，我没空陪你练功夫！\n",


	}) );

	set("chat_chance", 10);
            command("chat 慕容公子怎麽还不来, 唉。");

	set("chat_msg", ({
		(: random_move :),
		"一股若有若无的幽香飘来，让人心神荡漾。\n",
	}) );

	set("inquiry", ([
		"婚姻": (: answer_marr :),
		"姓名": "我就是王语嫣！\n",
	]));	

	set("dodge", 900);
	set_skill("literate", 300);
	set_skill("banruo-zhang", 200);
	set_skill("bc-zhang", 200);
	set_skill("chanchu-bufa", 200);
	set_skill("changhen-bian", 200);
	set_skill("cibei-dao", 200);
	set_skill("cuixin-zhang", 200);
	set_skill("dagou-bang", 200);
	set_skill("damo-jian", 200);
	set_skill("datengnuo-bufa", 200);
	set_skill("dugu-jiujian", 200);
	set_skill("fanliangyi-dao", 200);
	set_skill("feihua-shou", 200);
	set_skill("feihua-zhuyue", 200);
	set_skill("fengliu", 200);
	set_skill("fengyun-shou", 200);
	set_skill("fuliu-jian", 200);
	set_skill("fuxue-shou", 200);
	set_skill("fumo-jian", 200);
	set_skill("fx-step", 200);
	set_skill("halberd", 200);
	set_skill("hamagong", 200);
	set_skill("hanbing-zhang", 200);
	set_skill("huashan-jianfa", 200);
	set_skill("huashan-shenfa", 200);
	set_skill("hunyuan-zhang", 200);
	set_skill("jinding-mianzhang", 200);
	set_skill("jingang-quan", 200);
	set_skill("jinwu-dao", 200);
	set_skill("jiuyin-baiguzhao", 200);
	set_skill("kongming-quan", 200);
	set_skill("kuai-dao", 200);
	set_skill("lanhua-shou", 200);
	set_skill("lingbo-weibu", 200);
	set_skill("linji-zhuang", 200);
	set_skill("lingshe-zhangfa", 200);
	set_skill("liuhe-dao", 200);
	set_skill("liumai-shenjian", 200);
	set_skill("lujia-ji", 200);
	set_skill("luohan-quan", 200);
	set_skill("luoying-zhang", 200);
	set_skill("luoying-shenfa", 200);
	set_skill("mahayana", 200);
	set_skill("meinu-quan", 200);
	set_skill("medical-skill", 200);
	set_skill("mintian-jiushi", 200);
	set_skill("nianhua-zhi", 200);
	set_skill("poyu-quan", 200);
	set_skill("pudu-zhang", 200);
	set_skill("qiankun-danuoyi", 200);
	set_skill("qianmie-shou", 200);
	set_skill("qimen-bagua", 200);
	set_skill("qufengshu", 200);
	set_skill("riyue-bian", 200);
	set_skill("sanhua-zhang", 200);
	set_skill("shanjue", 200);
	set_skill("shaolin-shenfa", 200);
	set_skill("taiji-jian", 200);
	set_skill("taiji-quan", 200);
	set_skill("tiangang-zhi", 200);
	set_skill("tiangang-beidou", 200);
	set_skill("tianshan-zhang", 200);
	set_skill("tiyunzong", 200);
	set_skill("tonggui-jian", 200);
	set_skill("wanli-duxing", 200);
	set_skill("weituo-gun", 200);
	set_skill("xianglong-zhang", 200);
	set_skill("xianyun", 200);
	set_skill("xiaoyao-jian", 200);
	set_skill("xiaoyao-zhang", 200);
	set_skill("xiaoyaoyou", 200);
	set_skill("xiuluo-dao", 200);
	set_skill("yangxin-quan", 200);
	set_skill("yiyangzhi", 200);
	set_skill("yizhi-chan", 200);
	set_skill("yunu-jianfa", 200);
	set_skill("zhaixinggong", 200);
	set_skill("zhutian", 200);
	set_skill("zui-gun", 200);

	setup();
//	carry_object(__DIR__"obj/thin_sword")->wield();
	carry_object(__DIR__"obj/pink_cloth")->wear();
	carry_object(__DIR__"obj/shoe")->wear();
}



void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/master_name")!="段誉" ) {

     command("say " + RANK_D->query_respect(ob) + "若想拜我派可先段誉.\n");
                return;
        }


        if((int)ob->query("betrayer")>=1)
        {
command("say "+RANK_D->query_respect(ob)+"你多次叛师，背信弃义。我怎会收你。\n");
                return;
        }

        if ((int)ob->query("score")<2000){
        command("sigh"+ob->query("id"));
             command("say 你还是回去吧.我是不会收一个对大理国不忠之人的\n");
             return;
       }


        if ((int)ob->query("shen") < 50000) {
        command("say 学武之人，德义为先");
        command("say 在德行方面，" + RANK_D->query_respect(ob) +
                    "是否还做得不够？");
              return;
        }

        if ((int)this_player()->query_int() < 50 )
        {
   command("say 学习秘技要有好的悟性，"+RANK_D->query_respect(ob)+"资质不够\n");
                return;
        }

        command("chat 想不到我王语嫣也觅得一个可塑之才，真是可喜可贺。");
        command("recruit " + ob->query("id"));

        ob->set("title", GRN "天龙寺" NOR + YEL "特使" NOR);
}




void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}

// 要卖东西的话， 加上这一行
//	add_action("do_vendor_list", "list");
	add_action("do_look", "look");
}



// 加上这个系统的函数，坚决不和人打架
int accept_fight(object me)
{
	if( (string)me->query("gender") != "女性" )
	{
		command("say 我才不要和你们男子比武呢。");
	} else {
		command("say 女孩子不要整天想著练功嘛，我们去花园摘花儿玩去？");
	}
	return 0;
}

string answer_marr(object me)
{
	if( (string)me->query("gender") != "女性" )
	{
		command("blush");
		return "这位" + RANK_D->query_respect(me) +
			"说笑了，我还没有想过这件事情呢。";
	} else {
		return "这个。。。不太方便说吧。。。";
	}
}

// 覆盖系统的 look 函数
int do_look(string arg)
{
	object me;

// 如果不是看 yi yi 的话， 返回 0 让系统函数去处?	if( arg!="wang" )	return 0;

	me = this_player();
	if( me->query_temp("look_once") )
	{
		command("say 你老呆呆的看我干嘛？");
		write( name() + "瞪了你一眼\n");
		return 1;
	} else {
		me->set_temp("look_once",1);
		call_out("remove_look",20,me);
		return 0;
	}
}

void remove_look(object ob)
{
	ob->delete_temp("look_once");
}

// 加上这个系统函数可以接受东?int accept_object(object who, object ob)
{
	command("say 我不要的。\n");
	return 1;
}

