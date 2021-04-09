// wang.c
// by paladin

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
inherit F_DEALER;

int waiting(object me);
int checking(object me);
int do_chase(object me);
int do_kill(object me, object dest);
int do_look(string arg);
void remove_look(object ob);

//string ask_bf();
varargs void drool(string msg, string who);
string *rnd_say = ({
	"今天我心情不大好, 大家可要小心了.",
	"谁想讲个故事？",
	"为什么不说话呢?",
	"为什么不回去睡觉呢?",
	"谁想去看电影?",
	"我好象很苯耶.",
	"今晚有人请客吗?",
	"谁要开报告会啊？",
	});

string answer_marr(object me);


void create()
{
	set_name("王语嫣", ({ "wang yuyan", "wang" }) );
	set("title",HIM"曼陀罗山庄小姐"NOR);
	set("rank_info/respect", "神仙姐姐");

	set("long", @LONG
这位绝色美女看着你，你刹那间惊为天人，心中大呼：“我好福气呀！
如此俏佳人看了我一眼！。
LONG
);
	set("gender", "女性" );
	create_family("琅瑗福地", 1, "公主");
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
	set("combat_exp",10000000);
            create_family("天龙寺", 1, "贵宾");


	set("say_chance_combat", 25);
	set("say_msg_combat", ({
		(: command("hehe") :),
		"王语嫣秀眉微蹙，说道：喂！怎么如此不识好歹呀？
是不是见我美丽起了歹念呀？我可不好惹的噢！\n",
		"王语嫣不住地望著屋外：你还是快走吧，我没空陪你练功夫！\n",
		"王语嫣自言自语到：“什么时候才能见到表哥哪！”\n",
        "王语嫣道：“谁又能帮我找到表哥哪？”\n",


	}) );


 set("say_chance",({
  YEL"王语嫣嫣然一笑,唱道：红尘多可笑，痴情最无聊......!\n"NOR,
  YEL"王语嫣看着你,笑道:看你的样子,你怎么这么苯啊!\n"NOR,
  }));

 set("env/wimpy",10);

 set_temp("apply/attacka",20);
 set_temp("apply/defense",30);
 set_temp("apply/damage",30);


	set("say_msg", ({
		(: random_move :),
		"一股若有若无的幽香飘来，让人心神荡漾。\n",
"王语嫣脸上一红，道：“我既没受伤，又不是给人点中穴道，我……我自己会走……”\n",
"王语嫣双目紧闭，呼吸微弱，已然晕去。\n",
"王语嫣哇的一声，哭了出来，双手捧着脸，低声道：“你们别来管我，我...我...我不想活啦。”\n",

	}) );


// set("vendor_goods",({

// "/d/dali/obj/rose",

//   }));


	set("inquiry", ([
                "慕容复" : "我表哥……嘻嘻……",
		"婚姻": (: answer_marr :),
		"姓名": "我就是王语嫣！\n",
//		"段公子"     : (: ask_bf :),

	]));

	set_skill("literate", 300);
        set_skill("training", 300);
	set_skill("banruo-zhang", 300);
	set_skill("bc-zhang", 300);
	set_skill("chanchu-bufa", 300);
	set_skill("changhen-bian", 300);
	set_skill("cibei-dao", 300);
	set_skill("cuixin-zhang", 300);
	set_skill("dagou-bang", 300);
	set_skill("damo-jian", 300);
	set_skill("datengnuo-bufa", 300);
	set_skill("fanliangyi-dao", 300);
	set_skill("feihua-shou", 300);
	set_skill("feihua-zhuyue", 300);
	set_skill("fengliu", 300);
	set_skill("fengyun-shou", 300);
	set_skill("fuliu-jian", 300);
	set_skill("fuxue-shou", 300);
       set_skill("dodge", 300);
	set_skill("fumo-jian", 300);
	set_skill("fx-step", 300);
	set_skill("halberd", 300);
	set_skill("hamagong", 300);
	set_skill("hanbing-zhang", 300);
	set_skill("huashan-jianfa", 300);
	set_skill("huashan-shenfa", 300);
	set_skill("hunyuan-zhang", 300);
	set_skill("jinding-mianzhang", 300);
	set_skill("jingang-quan", 300);
	set_skill("jiuyin-baiguzhao", 300);
	set_skill("kongming-quan", 300);
	set_skill("kuai-dao", 300);
	set_skill("lingbo-weibu", 300);
	set_skill("lingshe-zhangfa", 300);
	set_skill("liuhe-dao", 300);
	set_skill("liumai-shenjian", 300);
	set_skill("lujia-ji", 300);
	set_skill("luohan-quan", 300);
	set_skill("luoying-zhang", 300);
	set_skill("luoying-shenfa", 300);
	set_skill("mahayana", 300);
	set_skill("meinu-quan", 300);
	set_skill("medical-skill", 300);
	set_skill("mintian-jiushi", 300);
	set_skill("nianhua-zhi", 300);
	set_skill("pixie-jian", 300);
	set_skill("poyu-quan", 300);
	set_skill("pudu-zhang", 300);
	set_skill("qianmie-shou", 300);
        set_skill("qimen-dunjia", 300);
	set_skill("qufengshu", 300);
	set_skill("riyue-bian", 300);
	set_skill("sanhua-zhang", 300);
	set_skill("shanjue", 300);
	set_skill("shaolin-shenfa", 300);
	set_skill("taiji-jian", 300);
	set_skill("taiji-quan", 300);
	set_skill("tiangang-zhi", 300);
	set_skill("tiangang-beidou", 300);
	set_skill("tianshan-zhang", 300);
	set_skill("tiyunzong", 300);
	set_skill("tonggui-jian", 300);
	set_skill("wanli-duxing", 300);
	set_skill("weituo-gun", 300);
	set_skill("xianglong-zhang", 300);
	set_skill("xianyun", 300);
	set_skill("xiaoyao-jian", 300);
	set_skill("xiaoyao-zhang", 300);
	set_skill("xiaoyaoyou", 300);
	set_skill("xiuluo-dao", 300);
	set_skill("yangxin-quan", 300);
	set_skill("yiyangzhi", 300);
	set_skill("yizhi-chan", 300);
	set_skill("yunu-jianfa", 300);
	set_skill("zhaixinggong", 300);
	set_skill("zhutian", 300);
	set_skill("zui-gun", 300);

        map_skill("dodge","lingbo-weibu");
        map_skill("cuff","meinu-quan");
	map_skill("force","yunu-xinfa");
        map_skill("parry","meinu-quan");


//	carry_object(__DIR__"obj/thin_sword")->wield();
//	carry_object(__DIR__"obj/pink_cloth")->wear();
//	carry_object(__DIR__"obj/shoe")->wear();


        set("say_chance", 1);
	set("say_msg", ({
		"王语嫣抬起头来，抽抽噎噎的道：“你再胡说八道的欺侮我，我......我就一
头撞死在这里。”。\n",
		(: command("sing2") :),
		(: command("angry") :),
		(: command("yawn") :),
		(: command("lazy") :),
		(: command("laughproud") :),
		"王语嫣伸出白玉雕成一般的小手，托着下巴说: 谁想和我说说话?\n",
		"王语嫣打了个呵欠，左手轻轻掩住樱桃小口，柔声道：我困了。\n",
		(: drool :),
		(: command("reclaim") :),
	}) );

	set("say_chance_combat", 20);
	set("say_msg_combat", ({
		"王语嫣幽幽叹道：唉，你这又是何苦呢?\n",
		(: command("!!!") :),
		(: command("smile") :),
		(: command("poem") :),
		(: command("yawn") :),
		(: command("giggle") :),
		(: command("waggle") :),
		(: command("nomatch") :),
		(: command("xixi") :),
		(: command("say 你这" + RANK_D->query_rude(this_player())+"怎生如此执迷不悟?\n"):),
	}) );
	setup();

//        if( clonep() ) CHANNEL_D->register_relay_channel("say");


}



void init()
{
  object ob;

  ob=this_player();

  ::init();
  remove_call_out("greeting");
  call_out("greeting",1,ob);
//  add_action("do_list","list");
//  add_action("do_buy","buy");
  add_action("do_look", "look");

}

void greeting(object ob)
{
  if(!ob||environment(ob)!=environment() )  return;
  switch(random(2)) {
   case 0 : say("王语嫣说:欢迎来到琅瑗福地,不知这位"+RANK_D->query_respect(ob)+"是如何知到此地的?\n");
     break;
   case 1 : say("王语嫣笑说:这位"+RANK_D->query_respect(ob)+"快坐。\n");
     break;
}
}



void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/master_name")!="段誉" ) {

     command("say " + RANK_D->query_respect(ob) + "若想拜我派可先拜段誉.\n");
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

        command("say 想不到我王语嫣也觅得一个可塑之才，真是可喜可贺。");
        command("recruit " + ob->query("id"));

        ob->set("title", GRN "天龙寺" NOR + YEL "特使" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, GRN "天龙寺" NOR + YEL "特使" NOR);
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

// 加上这个系统函数可以接受东?int accept_object(object me, object ob)
{
	object obb;
	me=this_player();

	if(ob->query("name")=="情书")
	{
		if(me->query_temp("murong/qing"))
		{
    		command("wa");
			command("say 是表哥给我的信啊，多谢你了 !");
			command("say 既然你来到这里，就再麻烦你帮我把这个送给表哥吧!\n");
			obb=new("/d/murong/npc/obj/juan");
			obb->move(me);
			me->set_temp("murong/juan",1);
			me->delete_temp("murong/qing");
			return 1;
		}else
		{
			command("say 是表哥给我的信啊，多谢你了 !");
			command("say 既然你来到这里，就再麻烦你帮我把这个送给表哥吧!\n");
			return 1;
		}
	}
	else if(ob->query("name")=="扇子")
	{
		if(me->query_temp("murong/shan"))
		{
			command("kiss");
			command("say 表哥平安我就放心了。\n");
			command("say 表哥那里有一本斗转星移秘籍，你这么辛苦他一定会送给你的。\n");
//			me->improve_skill("wuhu-duanmendao",10);
			//加一点描述
			me->set_temp("murong/dzxy",1);
			return 1;
		}
		else
		{
			command("kiss");
			command("say 表哥平安我就放心了。\n");
			return 1;
		}
	}
	else
	{
		command("?");
		command("say 给我这个干嘛啊？\n");
		return 1;
	}
}






string make_reply()
{
}

int add_phrase(string who, string msg)
{
	msg = replace_string(msg, "?", "");
	msg = replace_string(msg, "？", "");
	msg = replace_string(msg, "？", "");
	msg = replace_string(msg, "!", "");
	msg = replace_string(msg, "！", "");
	msg = replace_string(msg, "啊", "");
	msg = replace_string(msg, "吗", "");
	msg = replace_string(msg, "耶", "");
	msg = replace_string(msg, "吧", "");

	if( msg!="" ) {
		add("memory/" + who, ({ msg }));
		return 1;
	} else return 0;
}


void relay_channel(object ob, string channel, string msg)
{
	string who, phrase;

	if( !userp(ob) || (channel != "say") ) return;
	who = ob->query("name");

	if( ob==this_object() ) return;

	if( add_phrase(who, msg) &&	random(10) > 3 )
		drool(msg, ob->query("name"));
}

void relay_say(object ob, string msg)
{
	string who, phrase;

	if( !userp(ob) ) return;
	who = ob->query("name");

	if( ob==this_object() ) return;

	if( add_phrase(who, msg) &&	random(10) > 3 )
		drool(msg, ob->query("name"));
}

void relay_emote(object ob, string verb)
{
       if( !userp(ob) ) return;
	switch(verb) {

//	case "fang":
	case "hug":
	case "kiss":
	case "mo":
	case "18mo":
	case "nocloth":

	if ( (string) ob -> query ("gender") == "男性"||(string) ob -> query ("gender") == "无性" )
	{
	command ("say 救命啊，"+ ob->query("name") + "想要非礼我！\n") ;
	command("say 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个好色之徒 。");
	}
	else
	{
	message_vision("\n王语嫣对$N笑道：“你我同为女儿身，再怎么喜欢也不要这样啊。”\n", ob);
	command("giggle");
	command("say 想不到"+ ob->query("name") +"这" + RANK_D->query_rude(ob)+"，竟然是一个变态！");
	}
	message_vision("$N摇了摇头，对$n幽幽叹道：唉，你这又是何苦呢?\n",this_object(),this_player());

	this_object()->kill_ob(ob);
	break;
       default:
       if( random(10)<2 )
       {
	command(verb + " " + ob->query("id"));
	return;
       }
       else
	{
	switch(verb)
	{
	case  "zhuyi":
	case  "jia":
	case  "cuo":
	case  "rou":
	case  "cu":
	case  "kan":
	case  "bi":
	case  "die":
	case  "kick":
	case  "taste":
	case  "hate":
	case  "brag":
	case  "showscar":
	case  "callname":
	case  "slap":
	case  "rascal":
	case  "slapsb":
	case  "bite":
	case  "knife":
	case  "drug":
	case  "cook":
	case  "stuff":
	case  "shit":
	case  "shutup":
	case  "stare":
	case  "praisemapi":
	case  "anniversary":
	case  "heng":
   switch(random(50))
   {
    case 0:
    command ("kick "+ ob->query("id"));
    command ("xixi");
    break;
    case 1:
    command ("slap "+ ob->query("id"));
    command ("xixi");
    break;
    case 2:
    command ("drug "+ ob->query("id"));
    break;
    case 3:
    command ("smell");
    command ("cook "+ ob->query("id"));
    break;
    case 4:
    command ("trip "+ ob->query("id"));
    break;
    case 5:
    command ("knife "+ ob->query("id"));
    command ("doubt "+ ob->query("id"));
    break;
    case 6:
    command("cry");
    command("say 啊，"+ob->query("name")+"这"+RANK_D->query_rude(ob)+"，真坏！\n");
    break;
    case 7:
    command ("shutup ");
    command ("shutup "+ ob->query("id"));
    break;
    case 8:
    command("cry");
   command ("say 谁来救我啊，"+ ob->query("name") + "想要羞辱我！\n") ;
   command ("die "+ ob->query("id"));
    break;
    case 9:
    command ("callname "+ ob->query("id"));
    break;
    case 10:
    command ("corpse "+ ob->query("id"));
    break;
    case 11:
    command ("hero");
    command ("shout "+ ob->query("id"));
    break;
    case 12:
    command ("shake");
    command ("nomatch "+ ob->query("id"));
    break;
    case 13:
    command ("stare "+ob->query("id"));
    command ("hit "+ ob->query("id"));
    break;
    case 14:
    command ("sneer");
    break;
    case 15:
    command("say 哎哟，"+ob->query("name")+"这个" + RANK_D->query_rude(ob)+"真不要脸。\n");
    command ("faint");
    break;
    case 16:
    command ("shrug");
    break;
    case 17:
    command ("puke "+ob->query("id"));
    command ("hehe");
    break;
    case 18:
    command ("blush");
    break;
    case 19:
    command ("heng");
    write(HIM "王语嫣一下子羞红了脸，急道：你，你。。。\n" NOR);
    break;
    case 20:
    command("cry");
    command("say 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
    break;
    case 21:
    command ("blush");
    break;
    case 22:
    command ("sob");
    command ("cry");
    break;
    case 23:
    command ("hate");
    command ("die "+ob->query("id"));
    break;
    case 24:
    command ("careful");
    break;
    case 25:
    command ("rascal "+ob->query("id"));
    break;
    case 26:
    command ("kick");
    command ("faint");
    break;
    case 27:
    command ("grpfight "+ob->query("id"));
    break;
    case 28:
    command ("rascal "+ob->query("id"));
    command("say 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟然是一个臭流氓！\n");
    break;
    case 29:
    command ("rascal "+ob->query("id"));
    command ("die "+ob->query("id"));
    break;
    case 30:
    command("waggle "+ob->query("id"));
    break;
    case 31:
    command("waggle");
    command ("callname "+ ob->query("id"));
    break;
    case 32:
    command ("say 段公子快来啊，帮我打"+ ob->query("name") + "这个大色魔！\n") ;
    break;
    case 33:
    command("say 哎哟，哎哟，"+ ob->query("name")+"这" + RANK_D->query_rude(ob)+"不老实！\n");
    command ("shit "+ ob->query("id"));
    break;
    case 34:
    command ("say 段公子快来啊，"+ ob->query("name") + "想要羞辱我！\n") ;
    command("say 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
    command("faint "+ob->query("id"));
    break;
    case 35:
    command ("kick "+ ob->query("id"));
    command ("grin");
    break;
    case 36:
    command ("slap "+ ob->query("id"));
    command ("hehe");
    break;
    case 37:
    command("faint");
    break;
    case 38:
    command("say 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
    command ("callname "+ ob->query("id"));
    break;
    case 39:
    command("!!!");
    break;
    default:
       if( random(10)<3 )
       {
	command(verb + " " + ob->query("id"));
	return;
       }
	else
	{
	command ("say 来人啊，"+ ob->query("name") + "想要羞辱我！\n") ;
	  command("say 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
	  command("cry");
	  command("faint "+ob->query("id"));
	}
       break;
   return;
   }
	case "wanfu":
	case "sister":
	case "jump":
	case "love":
	case "lovelook":
	case "praise":
	case "visite":
	case "drinkcup":
	case "goodkid":
	case "pat":
	case "addoil":
	case "laughproud":
	case "smile":
	case "xixi":
	case "hehe":
	case "giggle":
	case "thumb":
	case "admire":
	case "applaud":
	case "hi":
	case "qmarry":
	case "lov":
	case "ai":
	case "yi":
   switch(random(35))
   {
    case 0:
    command ("pat "+ ob->query("id"));
    break;
    case 1:
    command ("humble");
    break;
    case 2:
    command ("praise "+ ob->query("id"));
    break;
    case 3:
    command ("xixi");
    break;
    case 4:
    command("say "+ob->query("name")+"是天下第一大好人！\n");
    command ("giggle "+ ob->query("id"));
    break;
    case 5:
    command ("goodkid "+ ob->query("id"));
    break;
    case 6:
    command ("pat "+ ob->query("id"));
    break;
    case 7:
    command("say "+ob->query("name")+"是天底下最好的人了！\n");
    command ("giggle");
    break;
    case 8:
    command ("praisemapi "+ ob->query("id"));
    break;
    case 9:
    command ("laughproud "+ ob->query("id"));
    break;
    case 10:
    command("say 嗯，"+ob->query("name")+"继续努力啊！\n");
    command ("thank");
    break;
    case 11:
    command ("nod");
    command ("xixi");
    break;
    case 12:
    command ("shake");
    break;
    case 13:
    command("say 嗯，"+ob->query("name")+"继续努力啊！\n");
    command ("courage "+ob->query("id"));
    break;
    case 14:
    command ("xixi");
    break;
    case 15:
    command ("lovelook "+ob->query("id"));
    break;
    case 16:
    command ("smile "+ob->query("id"));
    break;
    case 17:
    command("say 嗯，我好喜欢"+ob->query("name")+"耶！\n");
    command ("kiss "+ob->query("id"));
    break;
    case 18:
    command ("addoil "+ob->query("id"));
    break;
    case 19:
    command ("xixi");
    break;
    case 20:
    command ("shakehand "+ob->query("id"));
    break;
    case 21:
    command ("courage "+ob->query("id"));
    break;
    case 22:
    command ("touch "+ob->query("id"));
    break;
    case 23:
    command ("humble");
    break;
    case 24:
    command ("protect "+ob->query("id"));
    break;
    case 25:
    command ("thumb "+ob->query("id"));
    break;
    case 26:
    command ("applaud ");
    command ("giggle ");
    break;
    case 27:
    command ("hi");
    break;
    case 28:
    command ("hi "+ob->query("id"));
    break;
    case 29:
    command("say 你怎么这样？\n");
    command("angry");
    break;
    default:
    command(verb + " " + ob->query("id"));
    command("smile");
    break;
   return;
   }
  return;
  }
}
}
return;
}

varargs void drool(string msg, string who)
{
	mapping mem;
	string *ob;

	mem = query("memory");
	if( !mapp(mem) )
	{
		if (random(10)<7)
			command("say 怎么大家都不说话了？都是机器人吗？\n");
                else if (random(10)<8)
                        command("say " +  rnd_say[random(sizeof(rnd_say))]);
                return;
	}

	if( !msg || !who) {
		ob = keys(mem);
		who = ob[random(sizeof(ob))];
		msg = mem[who][random(sizeof(mem[who]))];
	}
	if(random(5)<2)
    {
	if(this_object()->query("killed")!=who)
	this_object()->set("killed",who);
	}
	while (this_object()->query("killed")==this_object()->query("killer"))
    {
	if(random(10)<6)
    {
		if(this_object()->query("killer")!=this_object()->query("killed"))
		this_object()->set("killer",who);
	}
	else switch(random(15))
    {
        case 1:	this_object()->set("killer","张三");break;
	case 2:	this_object()->set("killer","守寺僧兵");break;
	case 3:	this_object()->set("killer","马钰");break;
	case 4:	this_object()->set("killer","观众乙");break;
	case 5:	this_object()->set("killer","土匪");break;
	case 6:	this_object()->set("killer","李四");break;
	case 7:	this_object()->set("killer","王语嫣");break;
	case 8:	this_object()->set("killer","出尘子");break;
	case 9:	this_object()->set("killer","侍卫");break;
	case 10:this_object()->set("killer","张三丰");break;
	case 11:this_object()->set("killer","王重阳");break;
	}
    }
	if( (strsrch(msg, "yueru") >= 0)||(strsrch(msg, "王语嫣") >= 0))
	{
	if((strsrch(msg, "别过") >= 0)||(strsrch(msg, "bye") >= 0)|| (strsrch(msg, "散") >= 0)|| (strsrch(msg, "离") >= 0))
	{
		if( sscanf(msg, "%*sbye%s", msg) == 2 ) msg = "bye" + msg;
		if( sscanf(msg, "%*s离%s", msg) == 2 ) msg = "离" + msg;
		if( sscanf(msg, "%*s散%s", msg) == 2 ) msg = "散" + msg;
		if( sscanf(msg, "%*s别过%s", msg) == 2 ) msg = "别过" + msg;
		switch(random(13)) {
		case 0:	command("say "+who+",你真的要走吗？\n"); break;
		case 1:	command("say 你不是开玩笑吧?\n");	break;
		case 2:	command("say 是该走了,MUD玩多了没好处.\n"); break;
		case 3:	command("say 王语嫣点了点头.\n");	break;
		case 4:command("say 王语嫣嚎啕大哭起来.\n"); break;
		case 5:command("say 王语嫣揉了揉哭红的眼睛道： "+who+",你真要走了就别再回来.\n"); break;
		case 6:	command("say 王语嫣深深地叹了一口气 。\n");	break;
		case 7:	command("say "+who+",再玩一会儿好不好?\n");	break;
		case 8:	command("say "+msg);	break;
		case 9:command("say 噢，"+who+"是天底下最好的人了!\n"); break;
		}
		return;
	}
	if( (strsrch(msg, "kiss") >= 0)|| (strsrch(msg, "love") >= 0)|| (strsrch(msg, "吻") >= 0)
		|| (strsrch(msg, "mo") >= 0)|| (strsrch(msg, "抱") >= 0)|| (strsrch(msg, "hug") >= 0))
		{
		if( sscanf(msg, "%*skiss%s", msg) == 2 ) msg = "kiss" + msg;
		if( sscanf(msg, "%*smo%s", msg) == 2 ) msg = "mo" + msg;
		if( sscanf(msg, "%*shug%s", msg) == 2 ) msg = "hug" + msg;
		if( sscanf(msg, "%*slove%s", msg) == 2 ) msg = "love" + msg;
		if( sscanf(msg, "%*s吻%s", msg) == 2 ) msg = "吻" + msg;
		if( sscanf(msg, "%*s抱%s", msg) == 2 ) msg = "抱" + msg;
		if( sscanf(msg, "%*s摸", msg) == 2 ) msg = "摸"+ msg;
		switch(random(20)) {
		case 0:	command("say "+who+",你。。。\n"); break;
		case 1:	command("say 你不是开玩笑吧?\n");	break;
		case 2:	command("say 我不同意！\n");break;
		case 3:command("say 王语嫣被"+who+"气得晕了过去。\n"); break;
		case 4:command("say 王语嫣嚎啕大哭起来.\n"); break;
		case 5:command("say 不要这样子嘛！\n"); break;
		case 6:command("say 非礼啊非礼！"+who+"这小流氓又来啦！\n"); break;
		case 7:command ("say 段公子快来啊，"+ who + "想要羞辱我！\n") ;
		case 8:	command("say 王语嫣嘻嘻地笑了几声.\n"); break;
		case 9:	command("say 王语嫣很生气地撅了撅嘴。\n");	break;
		case 10:command("say 王语嫣无奈的耸了耸肩.\n");	break;
		case 11:command("say 你对女孩子总是这样吗？\n"); break;
		case 12:command("say 大哥你怎么这样？\n"); break;
		case 13:command("say 王语嫣嫣然一笑，说：够了够了!\n"); break;
		case 14:command("say 王语嫣满脸胀得通红，急道：你。。。 。\n");	break;
		case 15:command("say 嗯，"+who+"是天底下最好的人了！\n"); break;
	                case 16:command ("say 段公子快来啊，"+ who + "欺负我！\n") ; break;
		}
		return;
	}
	if( (strsrch(msg, "猪") >= 0)||(strsrch(msg, "shit") >= 0)||(strsrch(msg, "pig") >= 0))
	{
		if( sscanf(msg, "%*spig%s", msg) == 2 ) msg = "pig" + msg;
		if( sscanf(msg, "%*s猪%s", msg) == 2 ) msg = "猪" + msg;
		if( sscanf(msg, "%*sshit%s", msg) == 2 ) msg = "shit" + msg;
		switch(random(15)) {
		case 0:	command("say 你是说" + msg + "吗？\n"); break;
		case 1:	command("say 难道你说我是....？\n");	break;
		case 2:	command("say 就算“" + msg + "”，你又能怎么样呢？\n"); break;
		case 3:	command("say 王语嫣很生气地撅了撅嘴。\n");	break;
		case 4:	command("say 你真的认为“" + msg + "”？\n"); break;
		case 5:	command("say 我觉得你有点儿缠杂不清。\n"); break;
		case 6:	command("say 你再说可别怪我不客气。\n"); break;
		case 7:	command("say 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
		case 8:	command("say "+ who+",我想和你决斗！有胆子你就放马过来！\n"); break;
		case 9:	command("say 王语嫣鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
		case 10:command("say 王语嫣被"+who+"气得晕了过去。\n"); break;
		case 11:command("say 王语嫣忽然大声说：打倒臭泥潭，打倒风！\n"); break;
		case 12:command("say 王语嫣揉了揉哭红的眼睛，跺脚道： "+who+",我恨死你了！\n"); break;
		case 13:command ("say 段公子快来啊，"+ who + "又想要羞辱我！\n") ; break;
		}
	}
	if(  (strsrch(msg, "fool") >= 0)||(strsrch(msg, "笨") >= 0)|| (strsrch(msg, "fuck") >= 0))
	{
		if( sscanf(msg, "%*s笨%s", msg) == 2 ) msg = "笨" + msg;
		if( sscanf(msg, "%*sfool%s", msg) == 2 ) msg = "fool" + msg;
		if( sscanf(msg, "%*sfuck%s", msg) == 2 ) msg = "fuck" + msg;
		switch(random(15)) {
		case 0:	command("say 大哥你怎么这样？\n"); break;
		case 1:	command("say 我看你是气急败坏。\n");	break;
		case 2:	command("say "+ who +",你这个臭流氓！\n"); break;
		case 3:	command("say 王语嫣用手捂住鼻子，说“"+who+"说话好臭!\n");	break;
		case 4:	command("say 你真的认为“" + msg + "”？\n"); break;
		case 5:	command("say 我觉得你有点儿缠杂不清。\n"); break;
		case 6: command("say 呸!\n"); break;
		case 7:	command("say 王语嫣怒道:你怎么知道“" + msg + "”？\n"); break;
		case 8:	command("say "+ who+"滚出来!我要和你决斗！有胆子你就放马过来！\n"); break;
		case 9:	command("say 王语嫣鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
		case 10:command("say 王语嫣嚎啕大哭起来.\n"); break;
		case 11:command("say 王语嫣揉了揉哭红的眼睛，跺脚道： "+who+"王八蛋给我滚出去！\n"); break;
		case 12:command("say 非礼啊非礼！"+who+"是个王八蛋！\n"); break;
		}
		return;
	}
	if(  (strsrch(msg, "cool") >= 0)||(strsrch(msg, "thumb") >= 0)||(strsrch(msg, "praise") >= 0)|| (strsrch(msg, "admire") >= 0))
	{
		if(random(5)<3)
        {
		switch(random(15)) {
		case 0:	command("say 大哥你怎么这样？\n"); break;
		case 1:	command("say 你是在说我吗？\n"); break;
		case 2:	command("say "+who+",没想到你也这么。。。\n"); break;
		case 3:	command("say 王语嫣嫣然一笑，说：够了!\n"); break;
		case 4:	command("say 你真的认为“" + msg + "”？\n"); break;
		case 5: command("say 王语嫣忽然莞尔一笑道: 你这是不是有点儿。。。？\n");break;
		case 6:    command("say 王语嫣回头看了"+who+"一眼，没吭声。\n");break;
		case 7: command("say 嗯,"+who+"是一个好孩子.\n"); break;
		case 8:command("say "+who+",你不会是想讨好我吧?\n"); break;
		case 9:command("say 王语嫣拱了拱手道：过奖，过奖 !\n");break;
		case 10:command("say 王语嫣指着"+who+"赞叹道：“"+who+"是武林第一高手！”\n");break;
		case 11:command("say 一朵红云飞上了王语嫣的面颊.\n");break;
		}
		return;
        }
	}
	switch(random(80)) {
		case 0:	command("say 你真的是说" + msg + "吗？\n"); break;
		case 1:	command("say 你为什么对我这么感兴趣？\n");	break;
		case 2:	command("say 就算“" + msg + "”，你又能怎么样呢？\n"); break;
		case 3:	command("say 嗯,“" + msg + "”，那也没关系.\n"); break;
		case 4:	command("say "+who+",你这个臭流氓！\n"); break;
		case 5:	command("say 我想说的是，"+"其实"+who+"不是个好东西。\n"); break;
		case 6:	command("say 关于你说的「" + msg + "」，我暂时不想表态。\n"); break;
		case 7:	command("say 我认为你的态度不大好耶.\n"); break;
		case 8:	command("say 请注意，我只是机器人耶!\n"); break;
		case 9:	command("say 你对女孩子总是这样吗？\n"); break;
		case 10:	command("say 不要这样对我好不好？\n");	break;
		case 11:	command("say 我想我可以理解你的心情。\n");	break;
		case 12:	command("say 王语嫣深深地叹了一口气 。\n");	break;
		case 13:	command("say 王语嫣被"+who+"气得晕了过去 。\n");	break;
		case 14:	command("say 王语嫣满脸胀得通红，急道：你。。。 。\n");	break;
		case 15:    command("say 王语嫣咬了咬牙，怒道: 嗯，谁要再敢欺负我，我就宰了他！\n");break;
		case 16:    command("say 王语嫣忽然莞尔一笑道: 你这又是何苦呢？\n");break;
		case 17:    command("say 王语嫣打了个呵欠，左手轻轻掩住樱桃小口，柔声道：我困了。\n"); break;
		case 18:    command("say 王语嫣回头看了"+who+"一眼，没吭声。\n");break;
		case 19:    command("say 王语嫣一甩头，说：哼，我都懒得理你。\n");break;
		case 20:	command("say 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
		case 21:	command("say 我觉得"+who+"这厮简直不可理喻。\n"); break;
		case 22:	command("say 你是在说我吗？\n"); break;
		case 23:	command("say "+who+",没想到你也。。。\n"); break;
		case 24:	command("say 王语嫣嫣然一笑，说：够了!\n"); break;
		case 25:	command("say 居然有人骂我是猪!\n");
		 	command("say 王语嫣嚎啕大哭起来.\n"); break;
        case 26:	command ("say 段公子快来啊，"+ who + "又来欺侮我！\n") ; break;
      	case 27:	command ("say 我简直受不了了!\n") ; break;
        case 28:	command ("say 我恨不得"+who+"去死!\n") ; break;
        case 29:	command ("say 就你老和我过不去!\n") ; break;
        case 30:	command ("say 请不要打扰我好不好?\n") ; break;
   		case 31:	command ("say 王语嫣终于忍不住哭了起来。\n") ; break;
		case 32:	command("say 王语嫣鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
		case 33:    command("say 王语嫣咬了咬牙，怒道: 嗯，谁要敢欺负我，我就宰了他！\n");break;
		case 34:    command("say 王语嫣忽然莞尔一笑道: 你这是不是有点儿。。。？\n");break;
		case 35:    command("say 王语嫣打了个呵欠，左手轻轻掩住樱桃小口，柔声道：我有点儿困了。\n"); break;
		case 36:    command("say 王语嫣回头看了"+who+"一眼，没吭声。\n");break;
		case 37:    command("say 王语嫣一甩头，说：哼，我都懒得理你。\n");break;
		case 38:    command("say “" + msg + "”,是真的吗？\n"); break;
		case 39:    command("say 我觉得"+who+"的名字还不错.\n"); break;
		case 40:    command("say 我想去死了算了.\n"); break;
		case 41:    command("say 我觉得最佳表情奖应该授予"+who+".\n"); break;
		case 42: command("say 王语嫣笑嘻嘻的看着"+who+"\n"); break;
		case 43: command("say 烦着哪，别理我!\n"); break;
		case 44: command("say 哼！\n"); break;
		case 45: command("say 王语嫣打了"+who+"一个耳光.\n"); break;
		case 46: command("say 哼，谁理你啊!\n");break;
		case 47: command("say 嗯,"+who+"是一个好孩子.\n"); break;
		case 48:command("say 王语嫣露出迷惑的表情.\n"); break;
		case 49:command("say 是吗?\n"); break;
		case 50:command("say "+who+",你是不是想讨好我啊?\n"); break;
		case 51:command("say 哼,谁敢说我坏话?!\n");break;
		case 52:command("say 你不是开玩笑吧?\n");	break;
		case 53:command("say 我不同意！\n");break;
		case 54:command("say 王语嫣对"+who+"表示衷心的感谢.\n");break;
		case 55:command("say 不要这样子嘛！\n"); break;
		case 56:command("say 王语嫣拱了拱手道：过奖，过奖 !\n");break;
		case 57:command("say 王语嫣怒道:你怎么知道“" + msg + "”？\n"); break;
		case 58:command("say 王语嫣指着"+who+"赞叹道：“"+who+"是武林第一高手！”\n");break;
		case 59:command("say 王语嫣笑嘻嘻的看着"+who+"\n");break;
		case 60:command("say 为什么呢?\n");break;
		case 61:command("say 你是在说我吗？\n"); break;
		case 62:command("say 无聊!\n");break;
		case 63:command("say 一朵红云飞上了王语嫣的面颊.\n");break;
		case 64:command("say 王语嫣是个自恋狂。\n");break;
		default:
	    if (random(10)<3) command("say 王语嫣很生气地撅了撅嘴.\n");
	    else if(random(10)<3) command("say 王语嫣嘻嘻地笑了几声.\n");
	    break;
		}
	return;
	}
	if( (strsrch(msg, "哭") >= 0))
	{
	   if(random(5)<3)
        {
		if( sscanf(msg, "%*s哭%s", msg) == 2 ) msg = "哭" + msg;
		switch(random(15)) {
		case 0:	command("say "+who+",你真的哭了?\n"); break;
		case 1:	command("say 我不信耶.\n");	break;
		case 2:	command("say 王语嫣嘻嘻的笑了几声.\n"); break;
		case 3:command("say 王语嫣露出迷惑的表情.\n"); break;
		case 4:command("say 王语嫣嚎啕大哭起来.\n"); break;
		case 5:command("say 王语嫣安慰"+who+",别难过了.\n"); break;
		case 6:	command("say 王语嫣深深地叹了一口气 。\n");	break;
		case 7:	command("say 王语嫣无奈的耸了耸肩.\n");	break;
		case 8: command("say 王语嫣轻轻拍了拍"+who+"的头.\n"); break;
		}
		return;
        }
	}
	if( (strsrch(msg, "别过") >= 0)||(strsrch(msg, "bye") >= 0)|| (strsrch(msg, "散") >= 0)|| (strsrch(msg, "离") >= 0))
	{
		if( sscanf(msg, "%*sbye%s", msg) == 2 ) msg = "bye" + msg;
		if( sscanf(msg, "%*s离%s", msg) == 2 ) msg = "离" + msg;
		if( sscanf(msg, "%*s散%s", msg) == 2 ) msg = "散" + msg;
		if( sscanf(msg, "%*s别过%s", msg) == 2 ) msg = "别过" + msg;
		switch(random(20)) {
		case 0:	command("say "+who+",你真的要走吗？\n"); break;
		case 1:	command("say "+who+"你不是开玩笑吧?\n");	break;
		case 2:	command("say 是该走了,MUD玩多了没好处.\n"); break;
		case 3:	command("say 王语嫣点了点头.\n");	break;
		case 4:command("say 王语嫣嚎啕大哭起来.\n"); break;
		case 5:command("say 王语嫣揉了揉哭红的眼睛，跺脚道： "+who+",你真要走了就别再回来！\n"); break;
		case 6:	command("say 王语嫣深深地叹了一口气 。\n");	break;
		case 7:	command("say "+who+",再玩一会儿好不好?\n");	break;
		case 8:	command("say "+msg+"\n");	break;
		case 9:	command("say 王语嫣无奈的耸了耸肩.\n");	break;
		}
		return;
	}
	if( (strsrch(msg, "猪") >= 0)||(strsrch(msg, "shit") >= 0)||(strsrch(msg, "pig") >= 0))
	{
		if( sscanf(msg, "%*spig%s", msg) == 2 ) msg = "pig" + msg;
		if( sscanf(msg, "%*s猪%s", msg) == 2 ) msg = "猪" + msg;
		if( sscanf(msg, "%*sshit%s", msg) == 2 ) msg = "shit" + msg;
		if(random(5)<3)
        {
		switch(random(25)) {
		case 0:	command("say 你是说" + msg + "吗?\n"); break;
		case 1:	command("say 为什么啊?\n");	break;
		case 2:	command("say " + who + ",你好猪喔 !!\n"); break;
		case 3:	command("say 王语嫣很生气地撅了撅嘴。\n");	break;
		case 4:	command("say 你真的认为“" + msg + "”?\n"); break;
		case 5:	command("say 我觉得这个。。好象有点儿。。。\n"); break;
		case 6:	command("say 关于你说的「" + msg + "」，我暂时不想表态。\n"); break;
		case 7:	command("say 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
		case 8:	command("say "+who+",你说谁是猪？\n");	break;
		case 9:	command("say 就算“" + msg + "”，你又打算怎么样呢？\n"); break;
		case 10:	command("say 我不信耶.\n");	break;
		case 11:	command("say 王语嫣嘻嘻的笑了几声.\n"); break;
		case 12:	command("say 王语嫣把把头摇得跟拨浪鼓似的.\n");	break;
		case 13:	command("say 王语嫣哈哈大笑起来.\n"); break;
		}
		return ;
        }
	}
	else if( (strsrch(msg, "为什麽") >= 0)|| (strsrch(msg, "why") >= 0)
		|| (strsrch(msg, "help") >= 0)|| (strsrch(msg, "how to") >= 0)|| (strsrch(msg, "how to") >= 0)) {
		if( sscanf(msg, "%*s为什麽%s", msg)==2 ) msg = "为什麽" + msg;
		if( sscanf(msg, "%*swhy%s", msg)==2 ) msg = "why" + msg;
		if( sscanf(msg, "%*show to%s", msg)==2 ) msg = "how to" + msg;
		if( sscanf(msg, "%*swho%s", msg)==2 ) msg = "who" + msg;
		if( sscanf(msg, "%*shelp%s", msg)==2 ) msg = "help" + msg;
		switch(random(25)) {
		case 0: command("say " + who + "，你是在问我吗?\n"); break;
		case 1: command("say 关於“" + msg + "” ... \n"); break;
		case 2: command("say 呃 ... \n"); drool(); break;
		case 3: command("say 这个问题嘛 ....\n"); break;
		case 4: command("say " + who + "，知道这个问题的答案对你那麽重要吗？\n"); break;
		case 5: command("say “" + msg + "”?\n"); break;
		case 6: command("say " + who + "你能不能说清楚一点？\n"); break;
		case 7: command("say " + who + "，我不懂你问的问题。\n"); break;
		case 8: command("say " + who + "，我没听错吧?\n"); break;
		case 9: command("say 嗯，这个问题嘛，我看还是留给你自己解决。\n"); break;
		case 10: command("say 谁想给"+who+"一点儿钱?\n"); break;
		case 11: command("say 你在哪儿?\n"); break;
		case 12: command("say 王语嫣轻轻拍了拍"+who+"的头.\n"); break;
		case 13: command("say 与其求人,不如求己!\n"); break;
		}
 	return;
               }
	else if( (strsrch(msg, "你") >= 0)
	||	(strsrch(msg, "you") >= 0)) {
		if( sscanf(msg, "%*s你%s", msg) == 2 ) msg = "你" + msg;
		switch(random(25)) {
		case 0:	command("say " + who + "，你真的是说" + msg + "吗?\n");	break;
		case 1:	command("say 你确定" + msg + "?\n");	break;
		case 2:	command("say " + msg + "跟你有什麽关系？\n");	break;
		case 3:	command("say 嗯 ... " + who + "说得好！\n"); break;
		case 4:	command("say " + who + "你为什麽对" + msg + "这麽有兴趣?\n"); break;
		case 5:	command("say 为什麽你会认为[" + msg + "]?\n"); break;
		case 6:	command("say 换个话题好不好?\n"); drool(); break;
		case 7:	command("say 才怪!\n"); break;
		case 8:	command("say 不一定吧?\n"); break;
		case 9:	command("say 好象有这个可能 ....\n"); break;
		case 10:	command("say 我不信 ....\n"); break;
		case 11:	command("say 我对此深表怀疑.\n"); break;
		case 12:	command("say 王语嫣深深地叹了一口气. \n");	break;
		case 13:	command("say 王语嫣哈哈大笑起来.\n"); break;
		case 14:	command("say who?\n"); break;
		}
	return;
	}
	if( (strsrch(msg, "笑") >= 0))
	{
		if( sscanf(msg, "%*s笑%s", msg)==2 ) msg = "笑" + msg;
		if(random(5)<4)
        switch(random(25)) {
		case 0:	command("say 很好笑吗？\n"); break;
		case 1:	command("say "+who+",你很喜欢笑是不是？\n");	break;
		case 2:	command("say 我看不出有什么好笑.\n");	break;
		case 3:	command("say "+who+"笑起来真丑。\n");
			if(random(10)<2) command("say 王语嫣嘻嘻地笑了几声.\n");break;
		case 4:	command("say 王语嫣咯咯地笑了起来.\n");break;
		case 5:	command("say 王语嫣高兴地拍了拍手.\n");break;
		case 6: command("say 王语嫣轻轻拍了拍"+who+"的头.\n"); break;
		case 7:	command("say 王语嫣哈哈大笑起来.\n"); break;
		case 8: command("say 王语嫣说道:同喜,同喜!!!\n" );break;
		case 9: command("say 不准笑！\n" );break;
	}
	}
	else if( (strsrch(msg, "我") >= 0)|| (strsrch(msg, "I") >= 0)||(strsrch(msg, "i") >= 0)) {
		if( sscanf(msg, "%*s我%s", msg) == 2 ) msg = "我" + msg;
		if( sscanf(msg, "%*s i %s", msg) == 2 ) msg = " i " + msg;
		if( sscanf(msg, "%*s I %s", msg) == 2 ) msg = " I " + msg;
		msg = replace_string(msg, "我", "你");
		msg = replace_string(msg, " i ", " you ");
		msg = replace_string(msg, " I ", " you ");
		msg = replace_string(msg, "?", "");
		switch(random(30)) {
		case 0:	command("say 你是说" + msg + "吗?\n"); break;
		case 1:	command("say 真的?" + msg + "?\n");	break;
		case 2:	command("say 如果" + msg + "，我能帮你什麽忙吗?\n");	break;
		case 3:	command("say "+msg+" ?我看未必.\n");	break;
		case 4:	command("say 你认为" + msg + "?\n"); break;
		case 5:	command("say 我有同感.\n"); break;
		case 6:	command("say 你说的「" + msg + "」我实在不能苟同.\n"); break;
		case 7:	command("say 有关「" + msg + "」的话题到此为止好吗?\n"); break;
		case 8:	command("say 不一定吧？\n"); break;
		case 9:	command("say 有这个可能 ....\n"); break;
		case 10:command("say 我不信 ....\n"); break;
		case 11:drool(); break;
		case 12:drool(); break;
		case 13:command("say 王语嫣嘻嘻地笑了几声.\n"); break;
		case 14:command("say 王语嫣摇了摇头，叹道：唉，真是世风日下，人心不古啊！\n"); break;
		case 15:command("say 我对此表示怀疑.\n"); break;
		case 16:command("say 王语嫣深深地叹了一口气 。\n");	break;
		case 17:command("say 王语嫣露出迷惑的表情.\n"); break;
		case 18:command("say 是吗?\n"); break;
		case 19:command("say 变态！\n"); break;
 		}
	}
else {
		switch(random(250)) {
			case 0: command("say 我不喜欢你说“" + msg+"”.\n"); break;
			case 1: command("say 「" + msg + "」是什麽意思？\n"); break;
			case 2: command("say 王语嫣「哼」地冷笑一声。\n"); break;
			case 3: command("say 王语嫣懒懒地伸了伸腰。\n"); break;
			case 4: command("say 王语嫣气得晕了过去.\n"); break;
			case 5: command("say  哼！\n"); break;
			case 6: command("say 王语嫣露出迷惑的表情.\n"); break;
			case 7: command("say 王语嫣忽然作了个鬼脸,说：真想出去玩会儿.\n"); break;
			case 8: command("say " + rnd_say[random(sizeof(rnd_say))]); break;
			case 9: command("say 你怎麽知道" + msg + "?\n"); break;
			case 10: command("say 刚刚" + who + "不是说了，" + msg); break;
			case 11: command("say 王语嫣很生气地噘了噘嘴。\n"); break;
			case 12: command("say 然後呢？\n"); break;
			case 13: command("say 真的吗？\n"); break;
			case 14: command("say 我不这麽认为。\n"); break;
			case 15: command("say 对不起,我不同意你的观点。\n"); break;
			case 16: command("say 我觉得最佳表情奖应该授予"+who+".\n"); break;
			case 17: command("say 我真讨厌这鬼地方!\n"); break;
			case 18: command("say 王语嫣摇头叹道：这世道，还是各人自扫门前雪，休管他人瓦上霜.\n");break;
			case 19: command("say 王语嫣作了一个揖，说道：“各位姐妹们，大家好！”\n");break;
			case 20: command("say 我知道了，" + msg+"\n"); break;
			case 21:command("say 王语嫣露出迷惑的表情.\n"); break;
			case 22: command("say " + rnd_say[random(sizeof(rnd_say))]); break;
			case 23: command("say " + rnd_say[random(sizeof(rnd_say))]); break;
			case 24: command("say " + rnd_say[random(sizeof(rnd_say))]); break;
			case 25: command("say 王语嫣无聊地绕着手绢，说：一个人，真没意思。\n"); break;
			case 26: command("say 王语嫣露出迷惑的表情.\n"); break;
			case 27: command("say 王语嫣用怀疑的眼光看了看"+who+"\n"); break;
			case 28: command("say  我看未必.\n"); break;
			case 29: command("say 王语嫣奇道：是吗？\n"); break;
			case 30: command("say  老师来啦，"+who+"你还不赶快去？\n"); break;
			case 31: command("say "+who+",你今天怎么又逃课?\n"); break;
			case 32: command("say 王语嫣对所有在场的人表示感谢。\n"); break;
			case 33: command("say 王语嫣嘻嘻地笑了几声.\n");break;
			case 34: command("say "+who+"说得好!\n"); break;
			case 35: command("say 王语嫣好奇地看着"+who+"\n"); break;
			case 36: command("say "+who+",没想到你也会这样.\n"); break;
			case 37: command("say 王语嫣白了"+who+"一眼,说:你无聊不无聊啊?"); break;
			case 38:  command("say 王语嫣回头看了"+who+"一眼，没吭声。\n");break;
			case 39:command("say 王语嫣摇了摇头，叹道：唉，真是世风日下，人心不古啊！\n"); break;
			case 40:command("say 嗯 ... " + who + "说得好！\n"); break;
			case 41:command("say 王语嫣无奈的耸了耸肩.\n");	break;
			case 42:command("say 嗯，"+who+"是天底下最好的人了！\n"); break;
			case 43:command("say 王语嫣把把头摇得跟拨浪鼓似的.\n");	break;
			case 44:command("say 我对此表示怀疑.\n"); break;
			case 45: command("say 我觉得最佳表情奖应该授予"+who+".\n"); break;
			case 46: command("say 王语嫣轻轻拍了拍"+who+"的头.\n"); break;
                        case 47: command("say 王语嫣笑嘻嘻的看着"+who+"\n"); break;
                        case 48: command("rumor "+this_object()->query("killed")+"被大狼狗杀死了。\n"); break;
                        case 49: command("rumor "+this_object()->query("killed")+"被段誉杀死了。\n"); break;
                        case 50: command("rumor "+this_object()->query("killed")+"被丁春秋杀死了。\n"); break;
			case 51: command("say 我觉得"+who+"的名字还不错.\n"); break;
			case 52: command("say "+who+",你这个臭流氓!\n"); break;
			case 53: command("say 嗯，"+who+"看来不是个好人.\n"); break;
			case 54: command("say 哼！\n"); break;
			case 55: command("say 王语嫣打了"+who+"一个耳光.\n"); break;
			case 56:command("say 王语嫣给大家盈盈的福了一福.\n"); break;
			case 57:command("say 不要这样嘛!\n"); break;
			case 58:command("say 要死啊你!"+who+"!\n"); break;
			case 59:command("say 王语嫣忽然大声说：打倒臭泥潭，打倒风！\n"); break;
			case 60:command("say 王语嫣露出迷惑的表情.\n"); break;
			case 61:command("say 王语嫣振臂高呼：“我们热爱侠客行，侠客行万岁！”\n");break;
			case 62:command("say 王语嫣对大家摇摇头，叹道：“你们都太不要脸了。”\n");break;
			case 63:command("say 王语嫣点了点头.\n");	break;
			case 64:command("say 王语嫣哈哈大笑起来.\n"); break;
			case 65: command("say 与其求人,不如求己!\n"); break;
			case 66:command("say 王语嫣失望极了!\n");break;
			case 67:command("say 无聊!\n");break;
			case 68:command("say 是吗?\n"); break;
		        case 69:command("say 变态！\n"); break;
			case 70:command("say 王语嫣是个自恋狂。\n");break;
			case 71:command("say 为什么？\n");break;
			case 72:command("say 你烦不烦啊？\n");break;
			default:
	    if (random(10)<1) command("say 王语嫣皱了皱眉，似乎想说什么。\n");
		else if (random(10)<1) command("say 王语嫣嘻嘻地笑了几声.\n");
	    else if (random(10)<1) command("say 王语嫣懒懒的伸了伸腰.\n");
				break;
		}
	}
}

void reset()
{
	delete("memory");
}

