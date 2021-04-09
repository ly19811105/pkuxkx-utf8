// yhzzyahoo @2015.7.26 ,铜雀台
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW"冰蚕残篇"NOR, ({ "bingcan canpian","canpian","book"}));
	set_weight(500);
    set("value",100);
	if (clonep())
		set_default_object(__FILE__);
	else 
		{
			set("long", "这是来历不明的一些研究残篇，从上面似乎可以学到冰蚕毒掌的使用技巧。\n但是由于其记录不完整，即使学会了也会很快忘记……\n");
			set("unit", "本");
		}
}

void init()
{
	add_action("do_yanjiu", "yue");
	add_action("do_yanjiu", "du");
	add_action("do_yanjiu", "fan");
	add_action("do_yanjiu", "yanjiu");
	add_action("do_yanjiu", "study");
}

int do_yanjiu(string arg)
{
    object me=this_player();
	int lvl;
	string sk="";
	if (!arg)
		return 0;
	if (arg!="bingcan canpian" && arg!="canpian" && arg!="book")
		return 0;
    if (me->query_temp("bingcan_canpian"))
    {
        tell_object(me,"你已经研究过这本残篇了，要学到真正的冰蚕毒掌还是得另想办法。\n");
        return 1;
    }
	lvl = me->query_skill_limit();
    if (lvl<100)
    {
        tell_object(me,"也许是实战经验还不够，你感觉自己完全看不懂这本残篇里在说什么。\n");
        return 1;
    }
	
    message_vision("$N开始认真研读$n，初窥一些冰蚕毒掌的门径。\n"NOR, me, this_object());
    me->set_temp("bingcan_canpian",1);
	lvl -= me->query_skill("bingcan-duzhang", 1);
	if (lvl>0)
	{
		me->set_temp_skill("bingcan-duzhang", lvl, 3600, "");
		tell_object(me,HIC"你学会了一项临时技能：「"+to_chinese("bingcan-duzhang")+"」！\n"NOR);
		sk="冰蚕毒掌(lv:"+lvl+")";
	}
	lvl = me->query_skill_limit();
	lvl -= me->query_skill("poison", 1);
	if (lvl>0)
	{
		me->set_temp_skill("poison", lvl, 3600, "");
		tell_object(me,HIC"你学会了一项临时技能：「"+to_chinese("poison")+"」！\n"NOR);
		sk += "基本毒技(lv:"+lvl+")";
	}
	tell_object(me,"你翻到残篇最后一页，看到几个歪歪扭扭的字：「半个时辰……」再后面的字就看不清了。\n");
	log_file("static/temp_skill", sprintf("%s:%s(%s)从冰蚕残篇(bingcan canpian)学会了%s。\n",ctime(time()),me->query("name"),me->query("id"),sk)); 
    message_vision("$N很诡异地无风自燃起来了。\n",this_object());
    destruct(this_object());
    return 1;		
}