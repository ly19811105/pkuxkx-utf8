// roomgirl.c 房产小姐
// CLEANSWORD 1996/2/2
// fix by yhzzyahoo

inherit NPC;
inherit F_DEALER;
string ask_retrieve();

void create()
{
	set_name("推销小姐", ({ "girl" }));
	set("long", "一位打扮得花枝招展的小姐！\n");
	set("gender", "女性");
	set("start_room","/d/city/fangchan");
	set("age", 20);
	set("hooker", 1);

	set_skill("literate", 100);

	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 400000);
//	set("shen_type", 1);
	set("inquiry",([
                "回收":(:ask_retrieve:),
                "买房":"想买房是吧？很简单。给我100 gold就可以了。",
		]));
	set("shen_type",1);set("score",200);setup();

	set("chat_chance", 5);
	set("chat_msg", ({
		"销售小姐说：您是来买房的吧？我们这里的服务包您满意。\n"
		"销售小姐微微一笑，令你神魂颠倒！\n",
		"销售小姐高兴的看了你一眼！\n",
			}) );
}

void init()
{

}

int accept_object(object who, object ob)
{
        object money;
       if (this_player()->query("age")<18) 
        {      write("你太小，过些日子再来买房吧！\n");
               return 0;
        } 
        if (!undefinedp(this_player()->query("myroom")))
        {     write("销售小姐不解的说，您已经买过房了呀！\n");
              return 0;
        }
	if (ob->query("money_id") && ob->value() >= 1000000) 
	{
		message_vision("销售小姐高兴的对$N说：好吧，请到花园别墅区看看您的新房吧。\n", this_player());
        this_player()->set("myroom/time",time());
	      log_file("user/xinfang", sprintf("%s, %s的%s(%s)卖出了他自己的房间，他mud_age为%f天，他的存款为%d金子\n",
                  ctime(time()), this_player()->query("family/family_name"), this_player()->query("name"), this_player()->query("id"),
                  (float)(this_player()->query("mud_age")*1.0/3600/24), (int)(this_player()->query("advance_balance")*100+ this_player()->query("balance")/10000) ) );
        /*if(FAMILY_D->get_repute_top1() == this_player()->query("family/family_name"))
        {
            message_vision("销售小姐崇拜的看着$N说：原来你是天下第一派"+FAMILY_D->get_repute_top1()+"的弟子呀，我好崇拜你哦！这套房子给你八折！\n", this_player());
            command("love");            	    
        	money=new("/clone/money/thousand-cash.c");
        	money->set_amount(2);
        	money->move(this_player());
            tell_object(this_player(),"销售小姐还给了你二张银票。\n");	        
        }   */     
		return 1;
	}
	return 1;

}

string ask_retrieve()
{
	object me=this_player(),money;
        if (undefinedp(this_player()->query("myroom")))     
		return "销售小姐不解的说，您根本没有买过房，要我们回收什么呀？\n";
	return "销售小姐微笑说：我们这里的住房一经售出，概不回收。\n";
/*	message_vision("销售小姐对$N说：好吧，我们按原价的75%回收您的住房。\n", me);
	money=new(GOLD_OB);
	money->set_amount(75);
	money->move(me);
	log_file("user/xinfang", sprintf("%s, %s的%s(%s)卖出了他自己的房间，他mud_age为%f天，他的存款为%d金子\n",
                  ctime(time()), this_player()->query("family/family_name"), this_player()->query("name"), this_player()->query("id"),
                  (float)(this_player()->query("mud_age")*1.0/3600/24), (int)(this_player()->query("advance_balance")*100+ this_player()->query("balance")/10000) ) );
	me->delete("myroom");
	me->delete("store_ob");
	return "销售小姐给了你一些黄金。\n";*/
}
