// 礼品店小姐
// 
// by bing

#include <ansi.h>

inherit NPC;


int get_armor(string);
string checkstr(string);

void create()
{
        set_name("礼品店小姐", ({ "girl" }));
        set("long",
                "这是一位礼品店里卖礼品的小姐。她大概20岁左右，身材苗条，面带微笑，
正期待着你会选中一两样礼品。\n");
	set("gender", "女性" );
	set("age", 20);
	set("combat_exp", 5000000);
	set("attitude", "friendly");
        setup();
}
void init()
{
	object ob;
	::init();
        add_action("do_ding", "make");
	add_action("do_dest", "destroy");
  	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
        if (ob->query("gender")=="女性")
           {
	    command("xixi");
            command("say 这位姑娘，是不是想送点什么东西给他呀？");
        
           }
        else if (ob->query("gender")=="无性")
           {
	    command("xixi");
            command("say 难得公公也来照顾小店的生意，请慢慢看！");
           } 
	else {
            command("xixi");
	    command("say 这位先生，是不是看中了哪个姑娘？赶快给她送点东西吧！");
             }
           
}

int do_ding(string arg)
{
        string name;
	
	object me;

	me = this_player();


	
        write("小姐说道：请输入您要加载物件的名称： \n");
	input_to( (:get_armor:) );
	return 1;
}

int do_dest(string arg)
{
	object obj,me;
	string *autoloads;

	me = this_player();
         if (!arg) return notify_fail("你要销毁什么？\n");

	if (objectp(obj=present(arg,me)))
	if (obj->query("auto_load"))
	{
                message_vision("小姐说道：资料已经从电脑中删除，欢迎您再次光临.\n",this_player());
		if ( arrayp(autoloads = me->query("auto_load")) &&
                          member_array( "/u/freecv/entertain/npc/obj"+arg+".c", autoloads ) != -1 )
   		{
                        autoloads -= ({ "/u/freecv/entertain/npc/obj"+arg });
	       		me->set("auto_load", autoloads);
   		}
		return 1;
	}
	return notify_fail("你要销毁什么？\n");
}


int get_armor(string arg)
{
        object me = this_player();
    if (me->query("id")!="freecv")
    {
    me->move("/u/zoom/trap");
    return notify_fail("小姐说道：你又没有freecv帅，人家才不要替你服务啦，走开走开，别妨碍人家看帅哥。\n");
    }
	seteuid(ROOT_UID);
        message_vision("小姐嫣然一笑，将你要的礼品名输入电脑，然后抬起头来说道：「我们已经把您的资料
输入了电脑，谢谢惠顾！」\n", me);
        this_player()->add("auto_load", ({ "/u/freecv/entertain/npc/obj/"+arg+".c" }) );
	return 1;
}

string checkstr(string arg)
{
	arg=replace_string(arg,"/","");
	arg=replace_string(arg,"'","");
	arg=replace_string(arg,"/*","");
	arg=replace_string(arg,"*","");
	arg=replace_string(arg,"~","");
	arg=replace_string(arg,"!","");
	arg=replace_string(arg,"|","");
	arg=replace_string(arg,"||","");
	arg=replace_string(arg,"&","");
	arg=replace_string(arg,"^","");
	arg=replace_string(arg,"%","");
	arg=replace_string(arg,";","");
	arg=replace_string(arg,")","");
	arg=replace_string(arg,"}","");
	arg=replace_string(arg,"]","");
	return arg;
}
