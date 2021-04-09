// banker.c
// originally coded by xiang
// 96-02-16 YZC fixed some math problem
// last changed by bibi on 4,12 1998
// last changed for 去掉所有的busy，现在set_amount() (in /inherit/item/combined.c)   
// 已经改好，不必再有这些busy了

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("钱眼开", ({"qian yankai", "qian", "yankai"}));
	set("title", "钱庄老板");
	set("nickname", "铁公鸡");
set("start_room","/d/city/qianzhuang");
	set("gender", "男性");
	set("age", 34);

	set("str", 22);
	set("int", 24);
	set("dex", 18);
	set("con", 18);

	set("qi", 500); 
	set("max_qi", 500);
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
	"钱眼开笑着说道：在本店存钱无利息，取钱收十分之一的手续费，客官您看着办吧。\n"
	"钱眼开微微一笑，说道：本店还办理不同面额货币的兑换业务。\n"
	}));

	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 40);
	setup();
	add_money("silver", 10);
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_check", "check");
	add_action("do_check", "chazhang");
	add_action("do_convert", "convert");
	add_action("do_convert", "duihuan");
	add_action("do_deposit", "deposit");
	add_action("do_deposit", "cun");
	add_action("do_withdraw", "withdraw");
	add_action("do_withdraw", "qu");
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
		return notify_fail("你存的钱不够娶。\n");
	}

	me->add("balance",  -v);
	MONEY_D->pay_player(me, v = v * 9 / 10);
	
	message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)),
		me);
            seteuid(ROOT_UID);
            me->force_me("save");
	return 1;
}
