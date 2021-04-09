//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "武库" );
	set("long", "这里明军的武器库，每个上战场的战士可以在这里领(ling)取称手的兵刃。\n");
	set("exits", ([
		
        "west" : __DIR__"ming_yingwai",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("land_type","pingyuan");
    set("hardness",1);
	setup();
}

int buff(object me)
{
    int buff=(int)me->query("level")*3;
    if (me->query_temp("guozhan/side")==this_object()->query("side"))
    {
        me->add_temp("apply/damage",buff);
    }
    else
    {
        me->add_temp("apply/damage",-buff);
    }
    return 1;
}

void init()
{
    object me=this_player();
    add_action("do_ling","ling");
    buff(me);
    ::init();
}

int do_ling(string arg)
{
    object ob=this_object();
    object me=this_player();
    object new_weapon;
    string *weapon=({"sword","blade","staff","whip","axe","spear","hammer","halberd","dagger"});
    if (me->query_temp("guozhan/side")!=ob->query("side"))
    {
        tell_object(me,"你不是大"+ob->query("side")+"军士，不能在这领取兵刃。\n");
        return 1;
    }
    if (me->query_temp("guozhan/weapon_obtain"))
    {
        tell_object(me,"这里的兵器被别人领空了，你自己去战场上获得吧。\n");
        return 1;
    }
    if (!arg||member_array(arg,weapon)<0)
    {
        tell_object(me,"你要领取兵器类型只能是sword,blade,staff,whip,axe,spear,hammer,halberd或者是dagger。\n");
        return 1;
    }
    me->set_temp("guozhan/weapon_obtain",1);
    new_weapon=new(__DIR__"obj/weapon");
    new_weapon->gen_weapon(arg);
    new_weapon->move(me);
    message_vision("武库的小校递给$N一柄"+new_weapon->query("name")+"。\n",me);
    return 1;
}

int valid_leave(object me,string dir)
{
    int buff=(int)me->query("level")*3;
    if (me->query_temp("guozhan/side")==this_object()->query("side"))
    {
        me->add_temp("apply/damage",-buff);
    }
    else
    {
        me->add_temp("apply/damage",buff);
    }
    return ::valid_leave(me,dir);
}