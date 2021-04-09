// banker.c
// originally coded by xiang
// 96-02-16 YZC fixed some math problem
// last changed by bibi on 4,12 1998
// last changed for 去掉所有的busy，现在set_amount() (in /inherit/item/combined.c)   
// 已经改好，不必再有这些busy了

//modified to baituo master by jas 2003.2
#include <ansi.h>
inherit F_MASTER;
inherit NPC;
string ask_me();
string ask_camel();
string ask_baituo();
void do_answer(string);

void create()
{
	set_name("钱眼开", ({"qian yankai", "qian", "yankai"}));
       set("long", "他一脸奸诈，十分精明，据说是白驼山在扬州安排的接头人。\n");
	set("title", "钱庄老板");
	set("nickname", "铁公鸡");
	set("gender", "男性");
	set("age", 34);
       set("start_room","/d/city/qianzhuang");

	set("str", 22);
	set("int", 24);
	set("dex", 18);
	set("con", 18);

	set("qi", 800); 
	set("max_qi", 800);
	set("jing", 100);
	set("max_jing", 100);
	set("shen", 0);

	set("combat_exp", 50000);
	set("shen_type", 1);
	set("attitude", "friendly");
	set("env/wimpy", 50);
	set("chat_chance", 2);
	set("chat_msg", ({
	"钱眼开骄傲的说道：本银号已经有上百年的历史，在江南可以说是第一家。\n",
        "钱眼开笑着说道：在本店存钱无利息，客官您看着办吧。\n"
        "钱眼开哭丧着脸说道：巫师为了体谅玩家，连取钱手续费都不收了，让本店赔了一大笔。\n"
	"钱眼开微微一笑，说道：本店还办理不同面额货币的兑换业务。\n"
	}));

	set_skill("hand", 50);
	set_skill("strike", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("force", 50);
        set_skill("training", 30);
 	    set_skill("poison", 30);
            set_skill("literate", 50);
        
		set_skill("hamagong",50);
        set_skill("chanchu-bufa", 50);
        set_skill("shexing-diaoshou", 60);
        set_skill("shentuo-zhang", 60);
 
        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("hand", "shexing-diaoshou");
 	 map_skill("strike", "shentuo-zhang");
          map_skill("parry", "shentuo-zhang");
        
         prepare_skill("strike","shentuo-zhang");
        set("inquiry", ([ 
                "骆驼" : (: ask_camel :),
              "白骆驼" : (: ask_camel :),
                "坐骑" : (: ask_camel :),
               "camel" : (: ask_camel :),
	        "白驼山" : (: ask_baituo :),
                "欧阳锋":(: ask_me() :),
        ]) );

        create_family("白驼山",3,"弟子");


	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 40);
	setup();
	add_money("silver", 10);
	carry_object("/clone/misc/cloth")->wear();
}



void init()
{
	add_action("do_answer","answer");
	add_action("do_check", "check");
	add_action("do_check", "chazhang");
	add_action("do_convert", "convert");
	add_action("do_convert", "duihuan");
	add_action("do_deposit", "deposit");
	add_action("do_deposit", "cun");
	add_action("do_withdraw", "withdraw");
	add_action("do_withdraw", "qu");
}
int destroying(object ob,object who)
{
	who->move("/d/baituo/gebi");
        destruct(ob);
        return 1;
}
int accept_object(object who, object ob)
{
	int MoneyValue;
	if (who->query("family/family_name") == "白驼山")
		MoneyValue = 2000;
	else
		MoneyValue = 10000;
        if (who->query_temp("baituo/go_bt"))
        {
                if (ob->query("money_id") && ob->value() >= MoneyValue) {
						if (base_name(environment(this_object())) != this_object()->query("start_room"))
						{
							tell_object(who,"钱眼开一脸茫然：“我在哪？？在哪？？我是谁？？是谁？？”\n");
							return 1;
						}
                        tell_object(who,"钱眼开一见有钱，喜笑颜开，双手捧过来，揣在怀里，偷偷左右看了看，低声道：我给你指引一条小路，可以直达白驼山！打铁铺的张二楞是我的拜把子兄弟，你回来时可以问他『扬州』！\n");
                        tell_object(who,"你沿着钱眼开指点的途径，很快来到白驼山下。\n");
                        who->delete_temp("baituo/go_bt");
                        who->set_temp("baituo/go_yz",1);
                        call_out("destroying",1,ob,who);
                        return 1;
                }
        }
	command("say 这种东西鬼才要 ! 滚一边去 !");
        return 0;
}

void enough_rest()
{
	delete_temp("busy");
}

int do_check()
{
	int total = (int)this_player()->query("balance");
	if (total>2000000000) 
        {
		this_player()->set("balance", 2000000000);
		write ("钱眼开悄悄告诉你：您在敝商号存钱二十万两黄金。\n");
                return 1;
	}
	if (!total || total < 0) 
        {
		this_player()->set("balance", 0);
		write ("钱眼开悄悄告诉你：您在敝商号没有存钱。\n");
                return 1;
	}
	write("钱眼开悄悄告诉你：您在弊商号共存有" + 
		MONEY_D->money_str(total) + "\n");

	return 1;
}

int do_convert(string arg)
{
	string from, to;
	int amount, bv1, bv2;
	object from_ob, to_ob;
	object me;
	
	me = this_player();

	if (!arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
	{
		return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");
	}

	from_ob = present(from + "_money", me);
	to_ob = present(to + "_money", me);

	if (!to_ob && file_size("/clone/money/" + to + ".c") < 0)
	{
		return notify_fail("你想兑换成什么？\n");
	}
	if (!from_ob)
	{
		return notify_fail("你身上没有带这种钱。\n");
	}
	if (amount < 1)
	{
		return notify_fail("你想白赚啊？\n");
	}
	if ((int)from_ob->query_amount() < amount)
	{
		return notify_fail("你带的" + from_ob->query("name") + "不够。\n");
	}
	
	bv1 = from_ob->query("base_value");
	if (!bv1)
	{
		return notify_fail("这样东西不值钱。\n");
	}

	bv2 = to_ob ? to_ob->query("base_value") : call_other("/clone/money/" + to, "query", "base_value" );
	
	if (bv1 < bv2)
		amount -= amount % (bv2 / bv1);	

	if (amount == 0)
	{
		return notify_fail("这些" + from_ob->query("name") + "不够换。\n");
	}

	// allowed to convert now


	if (!to_ob) {
		to_ob = new("/clone/money/" + to);
		to_ob->set_amount(amount * bv1  / bv2 );
		to_ob->move(me);
	}
	else
		to_ob->add_amount(amount * bv1  / bv2 );
        
        message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
	chinese_number(amount), from_ob->query("base_unit"), from_ob->query("name"),
	chinese_number(amount * bv1 / bv2), to_ob->query("base_unit"), 
	to_ob->query("name")), me);
 

	from_ob->add_amount(-amount);

	return 1;
}

int do_deposit(string arg)
{
	string what;
	int amount;
	object what_ob, me;

	me = this_player();

	if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
	{
		return notify_fail("命令格式：deposit:cun <数量> <货币单位>\n");
	}

	what_ob = present(what + "_money", me);
	if (!what_ob)
	{
		return notify_fail("你身上没有带这种钱。\n");
	}
	if (amount < 1)
	{
		return notify_fail("你想存多少" + what_ob->query("name") + "？\n");
	}
	if ((int)what_ob->query_amount() < amount)
	{
		return notify_fail("你带的" + what_ob->query("name") + "不够。\n");
	}

	me->add("balance", what_ob->query("base_value") * amount);
        message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n", 
	chinese_number(amount), what_ob->query("base_unit"), 
	what_ob->query("name")), me);
	what_ob->add_amount(-amount);
            seteuid(ROOT_UID);
            me->force_me("save");
	return 1;
}

int do_withdraw(string arg)
{
	int amount, v;
	string what;
	object me;

	me = this_player();

	
	if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
	{
		return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");
	}
	if (amount < 1)
	{
		return notify_fail("你想取出多少钱？\n");
	}
//        if ( ! (amount < 1000) )
//        {
//          return notify_fail("别吓我了!\n");
//        }

	if (file_size("/clone/money/" + what + ".c") < 0)
	{
		return notify_fail("你想取出什么钱？\n");
	}
	what = "/clone/money/" + what;

//	if ((v = amount * what->query("base_value")) > me->query("balance"))
        v = amount *what->query("base_value");
        if ( v<0 || v>me->query("balance") )

	{
		return notify_fail("你存的钱不够取。\n");
	}

	me->add("balance",  -v);
//去掉手续费 by advent 2006-7-29
        MONEY_D->pay_player(me, v);
	
	message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)),
		me);
            seteuid(ROOT_UID);
            me->force_me("save");
	return 1;
}
string ask_me()
{
    object me=this_player();
    if (   ((string)me->query("family/family_name")=="白驼山") 
		|| me->query_temp("baituo_asked") ) 
 	return "庄主现在应该在白驼山内。\n";
    else  return ("不该知道的事还是不问为好。\n");
}
string ask_baituo()
{
          object me=this_player();
          tell_object(me,"钱眼开左右看了看，偷偷对着你做了个数钱的手势。\n");
          me->set_temp("baituo/go_bt",1);
          if ((string)me->query("family/family_name")=="白驼山") 
              return "从这里一直向西方走很久就到了，记着过沙漠时要骑骆驼。\n";
          else if (me->query_temp("baituo_asked"))
               return ("你不是刚问过了么？\n");         
         
               me->set_temp("baituo_asked",1);
               command("ah " + me->query("id"));
               return ("你是怎么知道这个秘密的,莫非你想拜入我白驼山门中？\n");
               
}
string ask_camel()
{
        object ob, me=this_player();

        if (me->query("family/family_name")!="白驼山") {
                command("say 你是哪里来的" + RANK_D->query_rude(me) +
                        "到我们庄来混食？快给我滚！");
                command("kick " + me->query("id"));
                return ("小心我宰了你！");
        }

        if (me->query_temp("白骆驼") || present("camel",me) || me->query_temp("mark/驼")){
                return("你不是有坐骑了吗？");
        }

	if (query("camel_count") > 1)
                return("骆驼都让你师兄弟们骑走了，"+ RANK_D->query_respect(me)+
                       "要回山，等他们回来在说吧。");

        ob=new("/d/baituo/npc/camel");
        ob->move(environment(me));
        ob->set_lord(me);
	 add("camel_count", 1);
        me->set_temp("mark/驼", 1);
                command("nod");
                say("钱眼开从钱庄后院里牵出一匹骆驼来交给你。\n");
		return(RANK_D->query_respect(me) + "路上小心，早去早归！");
}

void attempt_apprentice(object ob)
{
       if((string)this_player()->query("family/master_id") == "ouyang feng" || (string)this_player()->query("family/master_id") == "ouyang ke")
       {
		   command ("say 不敢当,不敢当!");
           return;
	   }
	   else if ((string)this_player()->query("family/master_id") == "qian yankai")
       { 
		   command("say 你可要好好练功呀!");
           return;
	   }
       if (!this_player()->query_temp("baituo_asked"))
          {
          command ("say 老夫不会武功，我可不收什么徒弟!");
          return;
          }
	if ( ob->query("class")=="bonze" ) {
             if (ob->query("gender")=="女性")
		command ("say 小师太练蛤蟆功，不怕别人叫你秃头蛤蟆吗？");
	     else
		command ("say 大师傅练蛤蟆功，不怕别人叫你秃头蛤蟆吗？");
	     return;
	}
        if( ob->query("family/family_name") == "丐帮") {
		command ("say 庄主平生最恨叫化子，我可不想收你。");
		return;
	}
        if ( ob->query("family/family_name") == "武当派" 
             || ob->query("family/family_name") == "全真派") {
		command ("say 老道练蛤蟆功，不怕别人叫你牛鼻子蛤蟆吗？");
		return;
	}
      if((int)ob->query("betrayer")>=2)
   {
   command("say 你多次判师，我怎么能够收你!\n");
   return;
    }
   if((int)ob->query("shen")>10000)
   {
    command("say 我不收行事不狠毒的人。\n");
   return;
      }
		if ((string)ob->query("family/family_name") == "灵鹫宫" 
			&& ob->query("lingjiu/xiulian"))
		{
			ob->set_temp("bai/ask",1);
        		command("say "+RANK_D->query_respect(ob)+"，你现在拜我似乎会有很大损失，你能拿定主意吗？(answer)");
			
		}
		else
		{
       this_player()->delete_temp("baituo_asked");
       command("say 好吧，"+RANK_D->query_respect(ob)+"！我就收下你了！\n");
       command("recruit "+ob->query("id"));
		}
}       
void do_answer(string arg)
{
	object me=this_player();
	if (!me->query_temp("bai/ask")) return;
	if (!arg || (arg != "是" && arg != "能" && arg != "yes"))
        	command("say 你说的什么乱七八糟的，看来你是没有诚心，算了！");
	else
	{
        	command("say 好吧，"+RANK_D->query_respect(me)+"，我就收下你了！");
		me->set("mud_age",me->query("lingjiu/mud_age"));
		me->set("age",14+me->query("mud_age")/3600/24);
		me->delete("lingjiu/skill_status");
		me->delete("lingjiu/qi");
		me->delete("lingjiu/eff_qi");
		me->delete("lingjiu/max_qi");
		me->delete("lingjiu/jing");
		me->delete("lingjiu/eff_jing");
		me->delete("lingjiu/max_jing");
		me->delete("lingjiu/jingli");
		me->delete("lingjiu/neili");
		me->delete("lingjiu/max_jingli");
		me->delete("lingjiu/max_neili");
		me->delete("lingjiu/combat_exp");
		me->delete("lingjiu/need_xiulian");
		me->delete("lingjiu/mud_age");
		me->delete("lingjiu/xiulian");
		me->delete("lingjiu/last_xiulian_time");
		me->delete_temp("bai/ask");
	       command("recruit "+me->query("id"));
	}
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
	 if (ob->query("gender")=="女性")
                ob->set("title", HIG "白驼山" NOR + YEL "婢女" NOR);
        else
                ob->set("title", HIG "白驼山" NOR + YEL "家丁" NOR);
        }
}
void re_rank(object student)
{
if( ::recruit_apprentice(student) )
{
	 if (student->query("gender")=="女性")
                student->set("title", HIG "白驼山" NOR + YEL "婢女" NOR);
        else
                student->set("title", HIG "白驼山" NOR + YEL "家丁" NOR);
}
}
