// Xiakedao NPC
// modified by aiai on 6/28/1999
// 侠客岛之 "张三"

#include <ansi.h>

#define TOP_LST "/log/doc/top_lst"
#define TOP_SIZE 15
inherit NPC;

void consider();
string ask_me();
void heal();
int FaLing();
int FaLingToUser(string user);
int observe(object ob1,object ob2);
void fighting(object ob1, object ob2);
void check(object ob1, object ob2);
void destroy();

void create()
{
	set_name("张 三", ({"zhang san", "zhang", "san"}));
	seteuid( getuid());
	set("nickname", RED"赏善使者"NOR);
	set("title",GRN "侠客岛" NOR + YEL "赏善使者" NOR);
	set("gender", "男性");
	set("age", 40);
	set("long","侠客岛赏善使者。\n");
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str",50);
	set("dex",50);
	set("int", 30);
	set("con", 30);
	set("chat_chance", 10);
	set("chat_msg", ({
		(: heal :),
	}));
	
	
	set("max_qi", 5000);
	set("max_jing",5000);
	set("neili", 5000);
	set("max_neili", 5000);
	set("jiali", 200);
	
	set("combat_exp",4000000);
	set("score", 50000);
	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: consider() :)
	}) );
	set("count",3);
	set("inquiry", ([
		"" : (: ask_me :),
        ]) );
	
	set_skill("force", 300);
	set_skill("parry",300);
	set_skill("strike", 200);
	set_skill("xiake-strike", 300);
	set_skill("dodge", 300);
	set_skill("xiake-shenfa", 300);
	set_skill("xiake-shengong",300);
	set_skill("xiake-jianfa",300);
	set_skill("sword",300);
	set_skill("throwing",300);
	map_skill("strike", "xiake-strike");
	map_skill("dodge", "xiake-shenfa");
	map_skill("force","xiake-shengong");
	map_skill("sword","xiake-jianfa");
	map_skill("parry","xiake-jianfa");
	prepare_skill("strike", "xiake-strike");
	
	create_family("侠客岛",3,"使者");
	
	setup();
	carry_object("/d/xiakedao/npc/obj/xguang")->wield();
	carry_object("/d/xiakedao/npc/obj/xgjia")->wear();
}

void init()
{
	::init();
	add_action("do_none", "bihua");
	add_action("do_none", "fight");
	add_action("do_none",  "hit");
  add_action("do_none",  "hitall");
  add_action("do_none",  "killall");
	add_action("do_biwu", "biwu");
	add_action("do_biwu", "accept");
	add_action("do_none",  "kill");
	add_action("do_none",  "steal");
	add_action("do_none",  "yun");
  add_action("do_exert",  "exert");
	add_action("do_none", "perform");
	add_action("do_none", "yong");
	add_action("do_halt",  "halt");
  add_action("do_alert",  "alert");
}

int do_none(string arg)
{
	object ob;
	ob = this_player();
	if (!userp(ob) || !arg)
		return 0;
	if (present(arg, environment(ob)) != this_object())
		return 0;
	if (!this_object()->is_fighting())
	{
		tell_object(ob,"你需要先接受张三的挑战(accept zhang)\n");
		
		return 1;
	}
	
	if ( (!(ob->query_temp("marks/bihua")==1)) && (this_object()->is_fighting()) )
	{
		tell_object(ob,"侠客岛使者正在与人比武，其武功出神入化，你竟然一点也插不上手。\n");
		
		return 1;
	}
        if ( (!(ob->query_temp("marks/bihua")==1)) && !(this_object()->is_fighting()) )
	{
                tell_object(ob,"看来侠客岛使者不屑与你比武。\n");
		
		return 1;
	}
        if (this_object()->query("opponent") )
        if (this_object()->query("opponent") != ob)
	{
                tell_object(ob,"看来侠客岛使者不屑与你比武。\n");
		
		return 1;
	}
	else return 0;
}

/*
int do_close()
{
object ob;
ob = this_player();
if ( ! userp(ob) )
return 0;
tell_object(ob,"侠客岛使者的武功出神入化，你的袭击始终无法奏效。\n");
return 1;

  }
*/
void consider()
{
	object *enemy,target;
	enemy = query_enemy() - ({ 0 });
	target = enemy[random(sizeof(enemy))];
	switch( random(2) )
	{
	case 0:
		command("perform sword.feijian "+target->query("id"));
		break;
	case 1:
    command("exert powerup");
		break;
	case 2:
		command("yun recover");
	}
}

void heal()
{
	object ob=this_object();
	if (ob->query("eff_qi") < ob->query("max_qi"))
	{
		command("exert heal");
		command("enforce 200");
		return;
	}
	if (ob->query("qi") < ob->query("eff_qi"))
	{
		command("exert recover");
		return;
	}
	if (ob->query("jing") < ob->query("eff_jing"))
		command("exert regenerate");
	return;
}


int sort_user(object a, object b)
{
	return a->query("combat_exp") - b->query("combat_exp");
}

int select_user(object a)
{
    if(!wizardp(a)&&((int)a->query("no_fight")!=1)&&(int)a->query("combat_exp")>5000000&&
		interactive(a) && a->query("antirobot/deactivity") < 3) return 1;
	else return 0;
}
int FaLingToUser(string user)
{
	mapping *top_lst;
	object  top_one,me,ob;
	int i;
	
	if (!objectp(ob=find_player(user)))
		return notify_fail("没有这个玩家在线。\n");
        ob->set_temp("selected", 1);
        log_file("faling",ob->name()+" ("+ob->query("id")+")is select by Zhang San at "+ctime(time())+"\n");
	me = this_object();
	remove_call_out("is_start");
	call_out("is_start",900);   
	
	move( environment(ob) );
	if (ob->is_fighting() ){
		tell_object(ob, HIY"你忽然间眼前一花，一个身影出现在你的面前，你急忙停止了打斗。\n"NOR);
		ob->remove_all_enemy();
	}
	else {
		tell_object(ob, HIY"你忽然间眼前一花，一个身影出现在你的面前。\n"NOR);
	}
	
	CHANNEL_D->do_channel(this_object(), "jh", "hi "+ob->query("id"), 1);
    CHANNEL_D->do_channel(this_object(), "jh", "听说"+ob->query("name")+"阁下武功不错，在下想与您较量一下。?");
	tell_object(ob, YEL "如果你愿意和对方进行比试请你也对" + me
		->name() + "("+(string)me->query("id")+")"+ "下一次 biwu(accept) zhang指令。\n" NOR);
	ob->set_temp("marks/bihua",1);
	me->set("opponent",ob);
	return 1;
}
int FaLing()
{
	mapping *top_lst;
	object  top_one,me,ob;
	object* nowuser,*fit_user;
	int i;
	nowuser = sort_array(users(),"sort_user",this_object() );
	write(nowuser[2]->query("id")+"\n");
	fit_user=filter_array(nowuser,"select_user");
	i=random(sizeof(fit_user));
//        if(!query("mark")) 
//        set("count", sizeof(fit_user));
        if(!query("mark")) set("mark", 1);
        if(query("count") <= 0) call_out("destroy", 1);
        if(fit_user[i]->query_temp("selected")) { FaLing();return 1;}
        if( query("count")<=2 && fit_user[i]->query("xkdling") && random(20)) { FaLing();return 1;} //优先找没有mark的
        fit_user[i]->set_temp("selected", 1);
        log_file("faling",fit_user[i]->name()+" ("+fit_user[i]->query("id")+")is select by Zhang San at "+ctime(time())+"\n");
	me = this_object();
	if ( !objectp( nowuser[i] ) )
		return 0;
	remove_call_out("is_start");
	call_out("is_start",900);   
	
	move( environment(fit_user[i]) );
	if (fit_user[i]->is_fighting() ){
		tell_object(fit_user[i], HIY"你忽然间眼前一花，一个身影出现在你的面前，你急忙停止了打斗。\n"NOR);
		fit_user[i]->remove_all_enemy();
	}
	else {
		tell_object(fit_user[i], HIY"你忽然间眼前一花，一个身影出现在你的面前。\n"NOR);
	}
	
    CHANNEL_D->do_channel(this_object(), "jh", "hi "+fit_user[i]->query("id"), 1);
    CHANNEL_D->do_channel(this_object(), "jh", "听说"+fit_user[i]->query("name")+"阁下武功不错，在下想与您较量一下。");
	tell_object(fit_user[i], YEL "如果你愿意和对方进行比试请你也对" + me
		->name() + "("+(string)me->query("id")+")"+ "下一次 biwu(accept) zhang指令。\n" NOR);
	fit_user[i]->set_temp("marks/bihua",1);
	me->set("opponent",fit_user[i]);
	return 1;
}

void is_start()
{
	if ( this_object()->query_temp("marks/start") )
		return;
	else {
		command("sigh");
		CHANNEL_D->do_channel(this_object(), "jh", "唉！！！");
		CHANNEL_D->do_channel(this_object(), "jh", "看来岛主这次是选错了人了。");
		CHANNEL_D->do_channel(this_object(), "jh", "再会！");
        add("count", - 1);
        if(query("count") >= 1)
			call_out("FaLing",0);
		else call_out("destroy", 1);
		return;
	}
	
}
int do_biwu(string arg)
{
	object ob1, ob2;
	ob1 = this_player();
	ob2 = this_object();
	
	if ( ! ob1->query_temp("marks/bihua") )
	{
		tell_object(ob1,HIC"你功力未到，想和侠客岛的使者比武，那不是找死吗？\n"NOR);
		return 1;
	}
        if (this_object()->query("opponent") )
        if (this_object()->query("opponent") != ob1)
	{
                tell_object(ob1,"看来侠客岛使者不屑与你比武。\n");
		
		return 1;
	}
	
	if( !arg || arg=="" ) return 0;
	
	if ( arg != "zhang san" && arg != "zhang" && arg != "san" )
	{
		command("say " + "有我在此,你怎敢还与他人比武?！\n");
		return 1;
	}
        if(!living(this_object()))
        {
                write("你还是等张三醒了再比武吧。\n");
                return 1;
        }
        // added by iszt@pkuxkx, 2007-03-01
          if ( ob1->query_temp("xkd/winzhangsan") > 3)
	{
		command("say 我已经跟你比武多次，均无法取胜，在下甘拜下风！\n");
		return 1;
	}
	if ( this_object()->query_temp("busy") || this_object()->is_fighting() )
		return notify_fail("我正忙着呢，没空和你比武。\n");
	
	ob1->delete_temp("halted");
	ob2->delete_temp("halted");
//	ob1->delete_temp("marks/bihua");
	ob2->set_temp("marks/start",1);
	remove_call_out("check");
	remove_call_out("fighting");
	call_out("fighting",0, ob1, ob2);
	call_out("check",1, ob1, ob2);
	return 1;
}
void fighting(object ob1, object ob2)
{
	ob1->fight_ob(ob2);
	ob2->fight_ob(ob1);
}
void check(object ob1, object ob2)
{
	this_object()->set_temp("busy",1);	
	CHANNEL_D->do_channel(this_object(), "jh", ob1->query("name")+"接受了侠客岛使者的挑战！！！", -1);
	CHANNEL_D->do_channel(this_object(), "jh", ob1->query("name")+"与" + ob2->query("name") + "，现在在"+environment(ob2)->query("short")+"开始比武！", -1);
	call_out("observe",1,ob1,ob2);
}

void destroy()
{
	remove_call_out("is_start");	
	destruct(this_object() );
	return;
}

int observe(object ob1,object ob2)
{
	object ob;
	if(ob1->is_fighting())
	{
		call_out("observe",1,ob1,ob2);
		return 1;
	}
	this_object()->delete_temp("busy");
	if ( !present(ob1, environment()) )
	{
		CHANNEL_D->do_channel(this_object(), "jh", ob1->query("name") + "落荒而逃了！", -1);
		CHANNEL_D->do_channel(this_object(), "jh", "sigh", 1);
		CHANNEL_D->do_channel(this_object(), "jh", "看来"+ob1->query("name")+"无缘到侠客岛一游了。");
		command("bye");
		call_out("destroy",0);
		ob1->delete_temp("marks/bihua");
		return 1;
	}
	if (ob1->query_temp("halted"))
	{
		ob1->delete_temp("halted");
		CHANNEL_D->do_channel(this_object(), "jh", ob1->query("name") + "中途放弃比武！", -1);
		CHANNEL_D->do_channel(this_object(), "jh", "sigh", 1);
		CHANNEL_D->do_channel(this_object(), "jh", "看来"+ob1->query("name")+"无缘到侠客岛一游了。");
		command("bye");
		ob1->delete_temp("marks/bihua");
		call_out("destroy",0);
		return 1;
	}
	if ( ob1->query("qi")*2 > ob1->query("max_qi"))
	{
		CHANNEL_D->do_channel(this_object(), "jh", ob1->query("name") + "比武战胜" + ob2->query("name") + "！", -1);
		CHANNEL_D->do_channel(this_object(), "jh", "admire "+ob1->query("id"), 1);
		command("say "+RANK_D->query_respect(ob1)+"果然武功出凡超圣。侠客岛主有令，请您凭此赏善罚恶令到侠客岛一游。\n");
		message_vision(HIY"$N将手一甩，只见一道金光射向$n。\n"NOR,ob2,ob1);
		ob = new("/d/xiakedao/obj/shangshanfae-ling");
		ob->move(ob1);
		ob1->set("xkdling",1);
		ob1->add_temp("xkd/winzhangsan",1);
	}
	else
	{
		CHANNEL_D->do_channel(this_object(), "jh", ob2->query("name") + "比武战胜" + ob1->query("name") + "！", -1);
        CHANNEL_D->do_channel(this_object(), "jh", "sigh", 1);
		CHANNEL_D->do_channel(this_object(), "jh", "看来"+ob1->query("name")+"无缘到侠客岛一游了。");
		ob1->delete_temp("marks/bihua");
	}
	command("bye");
	call_out("destroy",0);
	return 1;
}
int do_halt()
{
	object me = this_player();
	if (me->is_fighting())
		me->set_temp("halted",1);
	return 0;
}
int do_alert()
{
	  if (this_player()->query("family/family_name")!="朝廷") return 0;
	  tell_object(this_player(),"和侠客岛使者比试需要真材实料，怎么可以让别人帮忙呢？\n");
    return 1;
}
int do_exert(string arg)  //whuan 除了roar和bhcs其他的exert可以
{
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2);	
    if(  arg=="roar" || arg=="bhcs"){
         tell_object(this_player(),"你张大了嘴巴结结巴巴的喊了一声，却发现张三根本没有理会你。\n");
         return 1;
    }
    return 0;
}
