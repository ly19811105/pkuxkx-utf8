// banker.c
// Each banker should support do_ + check, convert, deposit, withdraw 4 commands
// Updated by iszt@pkuxkx, 2007-02-16

#include <dbase.h>
#include <ansi.h>

int greeting(object pl)
{
    if(!objectp(pl) || !userp(pl) || environment(pl) != environment())
    {
        return 1;
    }        
    message_vision("$N面色一凛，作了一个深揖，道，不知天下第一派的"+pl->query("name")+"大驾光临，有失远迎。\n",this_object(),pl);    
}

void init()
{
    object pl = this_player();
	  add_action("do_check", ({"check", "chazhang", "查帐"}));
	  add_action("do_transfer",({"zhuan","transfer","转账"}));
	  add_action("do_convert", ({"convert", "duihuan", "兑换"}));
	  add_action("do_deposit", ({"deposit", "cun", "存"}));
	  add_action("do_withdraw", ({"withdraw", "qu", "取"}));
	
    if(FAMILY_D->get_repute_top1() != "" && FAMILY_D->get_repute_top1() == pl->query("family/family_name"))
    {	
    	call_out("greeting",1,this_player());
	  }
}

int do_check()
{
	int sklvl = 0;
	object me = this_player();
	int total = me->query("balance");
	int limit;
        int exp;
        exp=(int)me->query("combat_exp");

	if (!living(this_object()))
	{
		write("还是等对方醒来再说吧。\n");
		return 1;
	}

	if (base_name(environment()) != query("startroom"))
	{
		write(this_object()->name()+"道：「这……我尚有要事在身，你下次来钱庄吧。」\n");
		return 1;
	}

	if (query_temp("busy") || this_object()->is_busy())
	{
		write(this_object()->name()+"说道：「哟，抱歉啊，我这儿正忙着呢……您请稍候。」\n");
		return 1;
	}

	if (total <= 0)
	{
		me->set("balance", 0);
		write(this_object()->name()+"翻了翻帐簿，告诉你：「您在敝商号没有存钱。」\n");
		return 1;
	}

        if (exp>=80000000) limit=2000000000;
        else limit=exp*25;
	if(limit > 2000000000 || limit < 0)
		limit = 2000000000;
	if(limit < 500000)
		limit = 500000;
	
	write(this_object()->name()+"翻了翻帐簿，告诉你：“您在敝商号共存有"+MONEY_D->money_str(total)+"，\n"
		"\t敝商号的存款上限是："+MONEY_D->money_str(limit)+"。”\n");
	return 1;
}

int do_convert(string arg)
{
	string from, to;
	int amount, bv1, bv2, exp;
	object from_ob, to_ob;
	object me = this_player();

	if (!living(this_object()))
	{
		write("还是等对方醒来再说吧。\n");
		return 1;
	}

	if (base_name(environment()) != query("startroom"))
	{
		write(this_object()->name()+"道：「这……我尚有要事在身，你下次来钱庄吧。」\n");
		return 1;
	}

	if (query_temp("busy") || this_object()->is_busy())
	{
		write(this_object()->name()+"说道：「哟，抱歉啊，我这儿正忙着呢……您请稍候。」\n");
		return 1;
	}

	exp = me->query("combat_exp");
	if (!arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
		return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");

    if(to == "coin")
        return notify_fail("对不起，我们没有足够的铜板。\n");
	if (from == "cash")
		from = "thousand-cash";

	from_ob = present(from + "_money", me);
	if (!from_ob)
		return notify_fail("你身上没有带这种钱。\n");

	if (exp < 15000 && from_ob->query("id") == "thousand-cash")
		return notify_fail("你功夫还未入流，那里来的这么多钱？\n");

	if (to == "cash")
		to = "thousand-cash";

	to_ob = present(to + "_money", me);
	if (!to_ob && file_size("/clone/money/" + to + ".c") < 0)
		return notify_fail("你想兑换成什么？\n");

	if (amount < 1)
		return notify_fail("你想白赚啊？\n");

	if ((int)from_ob->query_amount() < amount)
		return notify_fail("你带的" + from_ob->name() + "不够。\n");

	bv1 = from_ob->query("base_value");
	bv2 = to_ob ? to_ob->query("base_value") : call_other("/clone/money/" + to, "query", "base_value" );

	if (bv1 < bv2) amount -= amount % (bv2 / bv1);

	if (amount == 0)
		return notify_fail("这些" + from_ob->name() + "不够换。\n");

	exp = amount * bv1 / bv2;

	if (exp < 1)
		return notify_fail(this_object()->name()+"脸色一变，道：“这位"
			+RANK_D->query_respect(me)+"，小店目前没有这么多现金，是否少换一点？”\n");

	// allowed to convert now
	to_ob = new("/clone/money/" + to);
	to_ob->set_amount(exp);
	if (!to_ob->move(me)) {
		destruct(to_ob);
		return notify_fail("你带不了那么多钱。\n");
	}

	set_temp("busy", 1);

	from_ob = present(from + "_money", me);

	message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
		chinese_number(amount), from_ob->query("base_unit"), from_ob->name(),
		chinese_number(amount * bv1 / bv2), to_ob->query("base_unit"),
		to_ob->name()), me);
	from_ob->add_amount(-amount);

	call_out("delete_temp", 1, "busy");

	return 1;
}

int do_deposit(string arg)
{
	string what,samount;
	int amount, limit;
	object what_ob, me;

	if (!living(this_object()))
	{
		write("还是等对方醒来再说吧。\n");
		return 1;
	}

	if (base_name(environment()) != query("startroom"))
	{
		write(this_object()->name()+"道：「这……我尚有要事在身，你下次来钱庄吧。」\n");
		return 1;
	}

	if (query_temp("busy") || this_object()->is_busy())
	{
		write(this_object()->name()+"说道：「哟，抱歉啊，我这儿正忙着呢……您请稍候。」\n");
		return 1;
	}

	me = this_player();

	if (!arg || sscanf(arg, "%s %s", samount, what) != 2)
		if ( (samount!="all") && (samount="" || sscanf(samount,"%d",amount)!=1) )
			return notify_fail("命令格式：deposit|cun <数量|all> <货币单位>\n");

	if (what == "cash")
		what = "thousand-cash";
	
	if (!what_ob = present(what + "_money", me))
		return notify_fail("您身上没有带这种钱。\n");

	if (samount == "all")
			amount = (int)what_ob->query_amount();
	else sscanf(samount,"%d",amount);

	if (amount < 1)
		return notify_fail("您想存多少" + what_ob->name() + "？\n");

	if ((int)what_ob->query_amount() < amount)
		return notify_fail("您带的" + what_ob->name() + "不够。\n");

        if (me->query("combat_exp")>=80000000) limit=2000000000;
        else limit = me->query("combat_exp") * 25;
	if(limit > 2000000000 || limit < 0)
		limit = 2000000000;
	if(limit < 500000)
		limit = 500000;

	limit -= me->query("balance");
	if (limit < what_ob->query("base_value") * amount)
		return notify_fail("您目前已有存款"+MONEY_D->money_str(me->query("balance"))+"，再存那么多的钱，我们小号可难保管了。\n");

	set_temp("busy", 1);
	limit = amount;
	amount *= what_ob->query("base_value");
	if (amount < 1) return notify_fail(this_object()->name()+"难堪地笑笑：「这位"
		+RANK_D->query_respect(me)+"，这么多现金我算不过来了，是否能另外给个数量？」\n");

	message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n", chinese_number(limit), what_ob->query("base_unit"), what_ob->name()), me);

	what_ob->add_amount(-limit);
	write(query("name")+"记完帐，点了点头：“您在敝商号现有"+MONEY_D->money_str(me->add("balance", amount))+"。”\n");
	call_out("delete_temp", 1, "busy");
	return 1;
}

int do_withdraw(string arg)
{
	int amount, v;
	string what;
	object me, money;
	int limit;

	if (!living(this_object()))
	{
		write("还是等对方醒来再说吧。\n");
		return 1;
	}

	if (base_name(environment()) != query("startroom"))
	{
		write(this_object()->name()+"道：「这……我尚有要事在身，你下次来钱庄吧。」\n");
		return 1;
	}

	if (query_temp("busy") || this_object()->is_busy())
	{
		write(this_object()->name()+"说道：「哟，抱歉啊，我这儿正忙着呢……您请稍候。」\n");
		return 1;
	}

	me = this_player();

	if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
		return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");

    if(what == "coin")
		return notify_fail("对不起，我们没有这么多铜板了。\n");

	if (what == "cash")
		what = "thousand-cash";
	
	if (what == "ten-thousand-cash")
		return notify_fail("本钱庄不允许取大面额支票。\n");
		
	if (what == "hundred-thousand-cash")
		return notify_fail("本钱庄不允许取大面额支票。\n");
	
	if (what == "million-cash")
		return notify_fail("本钱庄不允许取大面额支票。\n");

	if (file_size("/clone/money/" + what + ".c") < 0)
		return notify_fail("你想取出什么钱？\n");

	if (amount < 1)
		return notify_fail(this_object()->name()+"一脸的茫然，问道：「这位"
		+RANK_D->query_respect(me)+"到底想要提取多少钱款？」\n");

  if (amount > 10000)
		return notify_fail(this_object()->name()+"说道：「这位"
		+RANK_D->query_respect(me)+"一次取那么多不怕被抢吗？」\n");

	what = "/clone/money/" + what;

        if (me->query("combat_exp")>=80000000) limit=2000000000;
        else limit = me->query("combat_exp") * 25;
	if(limit > 2000000000 || limit < 0)
		limit = 2000000000;
	if(limit < 500000)
		limit = 500000;

	if (me->query("balance") > limit )
	{
//		log_file("balance", sprintf("%-19s本来有 %10d 存款，现减为：%10d。\n",
//			me->name()+"("+me->query("id")+")", me->query("balance"), limit));
//		me->set("balance", limit);
		tell_object(me, "您在敝商号的存款超出上限，请尽快转移。\n");
	}

	if ((v = amount * what->query("base_value")) > me->query("balance"))
		return notify_fail("你没有存那么多的钱。\n");

//	if ((v += (v+19) / 20) > me->query("balance"))
//		return notify_fail("你的存款不够支付手续费，少取点吧。\n");

	if (v < 1)
		return notify_fail(this_object()->name()+"脸色一变，道：「这位"
			+RANK_D->query_respect(me)+"，是否能另外给个数量？」\n");

	message_vision(sprintf("$N从银号里取出%s%s%s。\n", chinese_number(amount), what->query("base_unit"), what->name()), me);
	(money = new(what))->set_amount(amount);
	if(!money->move(me))
	{
		tell_object(me,HIR+BNK+"由于你拿不动这许多钱，钱庄伙计把钱都给你放在了地上。\n"+NOR);
		money->move(environment(me));
	}
	me->add("balance", -v);
	if (me->query("balance")<=0)
		write(query("name")+"记完帐，告诉你：「您在敝商号没有一文钱了。」\n");
	else write(query("name")+"记完帐，告诉你：「您在敝商号现还有"+MONEY_D->money_str(me->query("balance"))+"。」\n");

	seteuid(ROOT_UID);
	me->force_me("save");

	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");
	return 1;
}

int do_transfer(string arg)
{
	int amount, v;
	string receiverid,what;
	object me, money, receiver;
	int limit;

	if (!living(this_object()))
	{
		write("还是等对方醒来再说吧。\n");
		return 1;
	}

	if (base_name(environment()) != query("startroom"))
	{
		write(this_object()->name()+"道：「这……我尚有要事在身，你下次来钱庄吧。」\n");
		return 1;
	}

	if (query_temp("busy") || this_object()->is_busy())
	{
		write(this_object()->name()+"说道：「哟，抱歉啊，我这儿正忙着呢……您请稍候。」\n");
		return 1;
	}

	me = this_player();

	if (!arg || sscanf(arg, "%s %d %s", receiverid, amount, what) != 3)
		return notify_fail("命令格式：transfer|zhuan 对方id <数量> <货币单位>\n");

	if (!receiver=find_living(receiverid))
		return notify_fail(receiverid + "不在线上，无法转账。\n");
	if (!userp(receiver))
	{
		return notify_fail(receiverid + "不是玩家，无法转账。\n");
	}
	if (receiver->query("env/no_transfer"))
		return notify_fail(receiverid + "目前不愿意接受转账。\n");	
	if(!me->visible(receiver))
	{
		return notify_fail(receiverid + "不在线上，无法转账。\n");
	}
	if (what == "cash")
		what = "thousand-cash";
	
	if (what == "ten-thousand-cash")
		return notify_fail("本钱庄不允许转大面额支票。\n");
		
	if (what == "hundred-thousand-cash")
		return notify_fail("本钱庄不允许转大面额支票。\n");
	
	if (what == "million-cash")
		return notify_fail("本钱庄不允许转大面额支票。\n");


	if (file_size("/clone/money/" + what + ".c") < 0)
		return notify_fail("你想转账什么钱？\n");

	if (amount < 1)
		return notify_fail(this_object()->name()+"一脸的茫然，问道：「这位"
		+RANK_D->query_respect(me)+"到底想要转账多少钱款？」\n");
	
	if (amount > 10000)
		return notify_fail(this_object()->name()+"说道：「这位"
		+RANK_D->query_respect(me)+"一次转账不要转太多么？」\n");

	what = "/clone/money/" + what;

        if (me->query("combat_exp")>=80000000) limit=2000000000;
        else limit = me->query("combat_exp") * 25;
	if(limit > 2000000000 || limit < 0)
		limit = 2000000000;
	if(limit < 500000)
		limit = 500000;

	if (me->query("balance") > limit )
	{
//		log_file("balance", sprintf("%-19s本来有 %10d 存款，现减为：%10d。\n",
//			me->name()+"("+me->query("id")+")", me->query("balance"), limit));
//		me->set("balance", limit);
		tell_object(me, "您在敝商号的存款超出上限，请尽快转移。\n");
	}

	if ((v = amount * what->query("base_value")) > me->query("balance"))
		return notify_fail("你没有存那么多的钱。\n");

//	if ((v += (v+19) / 20) > me->query("balance"))
//		return notify_fail("你的存款不够支付手续费，少取点吧。\n");

	if (v < 1)
		return notify_fail(this_object()->name()+"脸色一变，道：「这位"
			+RANK_D->query_respect(me)+"，是否能另外给个数量？」\n");

	message_vision(sprintf("$N从银号里转账%s%s%s给%s。\n", chinese_number(amount), what->query("base_unit"), what->name(), receiver->query("name")), me);
	(money = new(what))->set_amount(amount);
	write(query("name")+"记完帐，告诉你：「您在敝商号现还有"+MONEY_D->money_str(me->add("balance", -v))+"。」\n");
	tell_object(receiver,me->query("name") + sprintf("从银号转账%s%s%s给你，银号伙计把钱给你送了过来。\n",chinese_number(amount), what->query("base_unit"), what->name()));
	if(!money->move(receiver))
	{
		tell_object(receiver,HIR+BNK+"由于你拿不动这许多钱，银号伙计把钱都给你放在了地上。\n"+NOR);
		money->move(environment(receiver));
	}

	seteuid(ROOT_UID);
	me->force_me("save");

	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");
	return 1;
}
