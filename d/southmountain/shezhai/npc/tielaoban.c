#include <ansi.h>
inherit NPC;
inherit F_DEALER;
int ask_join();
void create()
{
	set_name("华正德",({"hua zhengde","hua","zhengde"}));
    set("title", "打铁铺老板"+NOR);
    set("gender", "男性");
    set("age", 40);
    set("long", "他是在打铁铺的老板，现在正值盛年，不过已经很少亲自出手了。\n他也收购玩家锻造的装备。\n");
    set("attitude","heroism");
    set("generation",0);
    set("max_qi",600);
    set("eff_qi",600);
    set("qi",600);
    set("max_jing",480);
    set("jing",480);
    set("shen_type",1);
    set("no_clean_up",1);
    set("combat_exp",80000);
	set("vendor_goods", ({
			  "/obj/smith/materials/fuel",
			  "/obj/smith/tools/tiechui",
			  "/obj/remedy/fire",
			  "/obj/smith/books/material_enhance5",
			  "/obj/smith/books/material_enhance6",
			  "/obj/smith/books/disassemble_book.c"
			  
              
	}));
	set("inquiry", ([
	"入职" : (:ask_join:),
    	]));
	set("NoBusyAsking",1);
    setup();
    carry_object(__DIR__"obj/pcloth")->wear();
}
int ask_join()
{
	object me=this_player();
	if (me->query("ProfessionalClass/smithing"))
	{
		command("say 你已经是一位锻造师了啊。");
		return 1;
	}
	if (me->query_skill("smithing",1)<50)
	{
		command("say 等你锻造术知识达到一定程度再来也不迟。");
		return 1;
	}
	if (!me->query_temp("attemptsmith"))
	{
		command("say 你真的想成为一名锻造师吗？如果确定，请再次ask hua about 入职。");
		me->set_temp("attemptsmith",1);
		return 1;
	}
	me->delete_temp("attemptsmith");
	F_PRO->register_me(me,"smithing");//set职业就是核心职业技能,skills有的,注意小写
	return 1;
}
void init()
{
	add_action("do_sell","sell");
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
void pay_player(object who, int amount)
{
	object ob;

	if( amount < 1 ) amount = 1;
	if( amount/100 ) {
		ob = new(SILVER_OB);
		ob->set_amount(amount/100);
		ob->move(who);
		amount %= 100;
	}
	if( amount ) {
		ob = new(COIN_OB);
		ob->set_amount(amount);
		ob->move(who);
	}
}
int do_sell(string arg)
{
	object ob;
	int value;

	if( !arg || !(ob = present(arg, this_player())) )
		return notify_fail("你要卖什么装备？\n");
            if (!ob->query("PlayerMade"))
			{
				command("say 我只帮忙代销一些装备，其他东西不收。\n");
				return 1;
			}
	message_vision("$N把身上的" + ob->query("name") + "卖给了$n。\n",this_player(),this_object());
	value=ob->query("value");
	pay_player(this_player(),value*2);
	destruct(ob);

	return 1;
}