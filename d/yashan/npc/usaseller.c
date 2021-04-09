//醉汉
#include <ansi.h>

inherit NPC;
inherit F_DEALER;
int sellpaodan(object me);
void create()
{
        set_name(HIR"黄毛鬼"NOR, ({ "huangmao gui","gui"}) );
	set("gender", "男性" );
	set("age", 30);
	set("long",
                "他是一名美国投机商人，在战争中向各国兜售武器从而在其中大发其财,\n也许你可以从他那里买到武器!\n但是他好像只对眼熟的人卖武器。\n"
);
	set("combat_exp", 100000);
        set("inquiry", ([
                "美国" : "美国是我的家乡!" ,
                "USA" : "美国是我的家乡!" ,
                "美利坚" : "美国是我的家乡!" ,
                "美利坚合众国" : "美国是我的家乡!" ,
                "america" : "美国是我的家乡!" ,
				"炮弹" :(: sellpaodan :),
				"军火" : (: sellpaodan :),
				"武器" : (: sellpaodan :),
        ]) );
	set("attitude", "friendly");
    add_money("gold",1);
    set("seller",0);
	set("shen_type",-1);
set("score",500);
setup();
}

void init()
{	
	object ob;
object me;
me=this_player();

	::init();
        if( interactive(ob = this_player()) && !is_fighting() )
  {
if(ob->is_disable()) return;
        if( !ob || environment(ob) != environment() ) return;
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
		}
}
int sellpaodan(object me)
{
	object room;
	if(!this_player()->query_temp("cansell"))
	{
		command("look "+this_player()->query("id"));
		command("say 都不知道你说什么!");
		return 1;
	}
	if(query("seller")) return 1;
	set("seller",1);
	set("vendor_goods", ({
		"/d/jwhz/obj/paodan.c",
			}));
  message_vision(query("name")+HIW"见$N问到他炮弹的事情诡异的一笑：你要买军火？找我就对了，\n我们这里可有大量炮弹供应哟？要买赶快！嘿嘿。\n"+HIY"黄毛鬼连忙拿出炮弹来给你看。\n"NOR,this_player());
  add_action("do_list","list");
  add_action("do_buy","buy");
  remove_call_out("nosell");
  call_out("nosell",4,me);
   return 1;
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
    command("say 嘿嘿，要打仗了，要发财了！");
	if(random(3)<2)
	{
		ob->delete_temp("cansell");
		command("look "+ob->query("id"));
	}
	else
	{
		ob->set_temp("cansell",1);
		command("whisper "+ob->query("id")+" 要军火么？");
	}
	command("hehe");
	return ;
           
}
int nosell(object me)
{
	command("grin");
	message_vision(HIY"黄毛鬼又急急忙忙的把炮弹收了起来\n"NOR,this_player());
	delete ("vendor_goods");
	set("seller",0);
	return 1;
}
