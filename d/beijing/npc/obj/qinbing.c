// qinbing.c
//亲兵, used for ct people.

#include <ansi.h>

inherit NPC;

void create()
{
    	object ob1, ob2;

	set_name("亲兵", ({ "qinbing" }) );
	set("long", "一个膀大腰圆，面目凶恶的朝廷亲兵。\n");
	set("attitude", "heroism");
	set("class", "officer");

	set("max_qi", 500);
	set("max_jing", 500);
	set("max_neili", 300);
	set("max_jingli", 300);
	
	set("str", 40);
	set("con", 30);
	set("dex", 25);
	set("int", 25);
	set("per", 10+random(10));

	set("combat_exp", 100000);
	set_skill("parry", 50);
	set_skill("dodge", 50);
	set_skill("cuff", 50);
	set_skill("taizu-quan", 50);
	set_skill("sword", 50);
	set_skill("qingmang-jian", 50);
	map_skill("cuff", "taizu-quan");
	map_skill("sword", "qingmang-jian");

	setup();

	ob2=carry_object("/d/beijing/npc/obj/gangjian.c");
	ob2->wield();
	ob2->set("no_sell", 1);
	ob2->set("no_store", 1);
	ob2->set("no_pawn", 1);
}

void leave()
{
	message("vision", name() + "四周张望了一下，一溜烟地跑了。\n", environment(), this_object() );
	destruct(this_object());
}

void show(object who)
{
	string *cname = ({"亲兵甲", "亲兵乙", "亲兵丙", "亲兵丁"});
	string *ename = ({"-jia", "-yi", "-bing", "-ding"});

	int current = 0;
	current = (int)who->query_temp("jjf_current_bing");

	if(current < 1 || current > 4 )
	{
		destruct(this_object());
		return;
	}

	this_object()->set_name(cname[current-1], ({ (string)who->query("id")+ename[current-1] }) );	
	message_vision("不知道从哪里跑过来一位亲兵，站到$N身后。\n", who);

	 //set the leader of this bing.
	set("owner_id", (string)who->query("id")); 
	set_leader(who);
}

void relay_whisper(object me, string msg)
{
	if (query("owner_id") != me->query("id"))
	{
		message_vision((string)this_object()->query("name") 
			+ "对着$N冷哼了一声。\n", me);
		return;
	}
	
	//note, do not allow the order contain "chat", "tell"...
	//may need disable more later...
	if( strsrch(msg, "chat") != -1 ||
	    strsrch(msg, "hslj") != -1 ||
	    strsrch(msg, "es") != -1 ||
	    strsrch(msg, "new") != -1 ||
	    strsrch(msg, "rumor") != -1 ||
	    strsrch(msg, "tell") != -1 ||
	    strsrch(msg, "apprentice") != -1 ||
	    strsrch(msg, "recruit") != -1 || 
            strsrch(msg, "mount") != -1 ||
            strsrch(msg, "vote") != -1 )

		return;

	message_vision((string)this_object()->query("name") + "对着$N点了点头。\n", me);
	if (msg)
	{
		remove_call_out ("relaying");
		call_out ("relaying", 1+random(3), msg);
	}
}

void relaying (string msg)
{//execute the order.
	command (msg);
}

void init()
{       
	object me=this_player();
	object owner;

	::init();

	//make sure this bing always follow his owner.
	if ( (string)this_object()->query("owner_id") == (string)me->query("id") )
	{
		this_object()->set_leader(me);
	}

	//if owner leaves, let this bing have chance to disappear.
	if( this_object()->query("owner_id") != 0 )
	{
		owner = find_player( (string)this_object()->query("owner_id") );
		if( !owner ) owner=find_living( (string)this_object()->query("owner_id") );
		if( !owner )
		{
			remove_call_out ("leave");
			call_out ("leave", 1);
		}
	}
		
}



