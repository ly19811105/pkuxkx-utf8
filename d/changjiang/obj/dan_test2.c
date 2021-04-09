// Zine dec 7 2010 ,铜雀台
#include <ansi.h>
inherit ITEM;

void init()
{
	add_action("do_yanjiu", "yue");
	add_action("do_yanjiu", "du");
	add_action("do_yanjiu", "fan");
	add_action("do_yanjiu", "yanjiu");
}

void create()
{
	set_name(HIW"蛤蟆功乱解"NOR, ({ "hamagong miji","miji","book"}));
	set_weight(500);
    set("value",1);
	if (clonep())
		set_default_object(__FILE__);
	else 
		{
			set("long", "这是一本蛤蟆功乱解(伪)的秘籍，欧阳锋所著，你可以研究(yanjiu)一下。\n");
			set("unit", "本");
		}
}

int do_yanjiu()
{
   
    object me=this_player();
    /*int exp=me->query("combat_exp");
	int level=to_int(pow(exp/100,0.333)*10);
	if (me->query("int")<21 || me->query("zyhb") || me->query("hubo"))
	{
        tell_object(me,"你这么愚笨不堪，焉能学习阴阳倒乱刃。\n");
		return 1;
	}
	if (me->query_skill("shenghuo-lingfa"))
	{
        tell_object(me,"你有圣火令法，无法学习阴阳倒乱刃。\n");
        return 1;
	}
    if (me->query_skill("yinyang-daoluan"))
    {
        tell_object(me,"你已经掌握了阴阳倒乱刃的练法，绝技也有所体会。\n");
        return 1;
    }*/
    if (me->query("tqt/freetrial"))
	{
		tell_object(me,"你已经在体验一种铜雀台武功了！\n");
		return 1;
	}
	if (me->query("safari_skill/bts1"))
    {
        tell_object(me,"你不是已经掌握了蛤蟆功乱解了吗？\n");
        return 1;
    }
    if ((int)me->query_skill("hamagong",1)<500)
    {
        tell_object(me,"你的蛤蟆功境界太浅，这本乱解对于你过于艰难了。\n");
        return 1;
    }
	
	me->set("tqt/freetrial",1);//1是mark,2是skills
	me->set("tqt/free_trial","safari_skill/bts1");
	me->apply_condition("tqt_freetrial",960);
	tell_object(me,BLINK+HIR+"在体验铜雀台武功的期间，请不用使用铜雀台积分正式换购此项武功，否则有可能导致新武功失效，积分被浪费！\n"+NOR);
    message_vision("$N开始认真研读$n，掌握了蛤蟆功蛤蟆吐息的诀窍！\n"NOR, me,this_object());
    //me->set_skill("yinyang-daoluan",level);
	me->set("safari_skill/bts1",1);
    message_vision("$N很诡异地无风自燃起来了。\n",this_object());
    destruct(this_object());
    return 1;		
}