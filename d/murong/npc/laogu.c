//laogu.c
//by hehe
//2003.3.13

inherit NPC;

void create()
{
	set_name("老顾", ({ "lao gu","gu" }));
	set("gender", "男性");
	set("age", 30);
	set("long", "他是他是姑苏慕容家的的厨师，长得倒是白白胖胖的，也许以前有过钱。\n");
	
	set("combat_exp", 1000);
	set("shen_type", -1);
        set("count",3);
        set("no_get",1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object(__DIR__"obj/shoes1")->wear();
    carry_object(__DIR__"obj/cloth")->wear(); 
}

void init()
{
	object ob=this_player();

    if (userp(ob) && !wizardp(ob) && ob->query("family/family_name") != "姑苏慕容") {
		message_vision("厨子喝道：“$N你不是我慕容家的人，怎么闯到这里来了？出去！\n",ob);
        remove_call_out("kickout");
        call_out("kickout", 1, ob);
	}
    add_action("do_serve", "serve");
}

int kickout(object ob)
{
        if (!present(ob,find_object("/d/murong/tchufang.c"))) {
		return 1;
    }
	message_vision("厨子把$N赶了出去。\n",ob);
     ob->move("/d/murong/tingxiang");
    message("vision","只见，"+ob->query("name")+"满脸羞愧地从里面走了出来。\n", environment(ob), ob);
    return 1;
}

int do_serve()
{
    object ob,me;
    me=this_player();
   if(me->is_busy()) return notify_fail("你正忙着呢，等一下再要吧。\n");
    message_vision("$N向厨子要些食物吃喝。\n", me);
        if (this_object()->query("count") < 1)
            return notify_fail("厨子说：上次做的点心已经吃光了，你等下次开饭再来吧。\n");

    if (!present("songzi gao", environment(me))
	    && !present("feicui tianbing", environment(me))
         && !present("oufen", environment(me)))
    {
		switch(random(3)) {
        case 0:
			ob=new("/d/murong/obj/tianbing");
            break;
        case 1:
            ob=new("/d/murong/obj/gao");
            break;
        case 2:
            ob=new("/d/murong/obj/oufen");
            break;
        }    
        ob->move(environment(me));
        message_vision("厨子端出"+ob->name()+"给$N。“您慢慢吃，不够还有。”\n", me);
	}
    else message_vision("厨子对$N说道：心这么黑，您还没吃完呢。\n", me);
        
    if (!present("liqueur", environment(me))
                && !present("lao baigan", environment(me))
                && !present("xiang cha", environment(me)))
	{
        switch(random(3)) {
			case 0:
                                  ob=new("/d/baituo/obj/liqueur");
				break;
            case 1:
                 ob=new("/d/city/npc/obj/lbg");
                break;
            case 2:
                 ob=new("/d/wudang/obj/xiangcha");
                break;
		}
        ob->move(environment(me));
        me->start_busy(2);
        message_vision("厨子端出"+ob->name()+"给$N。“您慢慢喝，不够还有。”\n", me);
	}
    else message_vision("厨子对$N说道：你还没喝完呢，喝完再说吧。\n", me);
        this_object()->add("count",-1);
    return 1;
}

