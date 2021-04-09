#include <ansi.h>
inherit NPC;
inherit F_DEALER;
int ask_upgrade();
void create()
{
	string name,*tmp,*pinying;
	name=NAME_D->create_name();
	tmp=explode(name,"@");
	pinying=explode(tmp[1]," ");
	set_name(tmp[0],({tmp[1],pinying[0],pinying[1]}));
    set("title", "药材商"+NOR);
    set("gender", "男性");
    set("age", 40);
    set("long", "他是在东天目山收购药材的药材商。\n早年也是采药人，现在跌断了腿，不能进山了。\n");
    set("attitude","heroism");
    set("generation",0);
    set("max_qi",180);
    set("eff_qi",180);
    set("qi",280);
    set("max_jing",80);
    set("jing",80);
    set("shen_type",1);
    set("no_clean_up",1);
    set("combat_exp",20000);
	set("random_npc", 1);
	set("vendor_goods", ({
			  "/d/southmountain/dongtianmu/obj/yaochu.c",
              
	}));
	set("inquiry", ([
	"升级药篓" : (:ask_upgrade:),
	"upgrade" : (:ask_upgrade:),
    	]));
	set("NoBusyAsking",1);
    setup();
    carry_object("/clone/cloth/cloth")->wear();
}
int ask_upgrade()
{
	object me=this_player();
	int lv,cost;
	if (!me->query("ProfessionalClass/herbalism")) 
	{
		command("say 只有职业采药师才能有自己的药篓。\n");
		return 1;
	}
	lv=me->query("Myherb/Container");
	if (lv>=8)
	{
		command("say 你已经拥有八级药篓，是目前的最高级别了。");
		return 1;
	}
	lv+=1;
	cost=lv*lv*10000000;
	if (me->query("balance")<cost)
	{
		command("say 升级到"+chinese_number(lv)+"级药篓，需要"+MONEY_D->money_str(cost)+"，可惜你账上不够啊。");
		return 1;
	}
	me->add("balance",-cost);
	me->add("Myherb/Container",1);
	command("say 好吧，我从你账上扣了"+MONEY_D->money_str(cost)+"，现在你可以使用"+chinese_number(me->query("Myherb/Container"))+"级药篓了。\n");
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
		return notify_fail("你要卖什么药？\n");
            if (!ob->query("drugcode"))
			{
				command("say 我只收购药材。\n");
				return 1;
			}
	message_vision("$N把身上的" + ob->query("name") + "卖给了$n。\n",this_player(),this_object());
	value=ob->query("value");
	pay_player(this_player(), value/2);
	destruct(ob);

	return 1;
}