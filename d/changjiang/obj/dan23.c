// yhzzyahoo @2015.4.22 ,铜雀台
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
	set_name(HIG"先天罡气谱-神罡篇"NOR, ({ "shengang pian","pian","book"}));
	set_weight(500);
    set("value",1);
	if (clonep())
		set_default_object(__FILE__);
	else 
		{
			set("long", "这是一本重阳祖师亲手所著的练功心得，记载着先天功先天神罡的进修方法，你可以研究(yanjiu)一下。\n");
			set("unit", "本");
		}
}

int do_yanjiu()
{
   
    object me=this_player();
    if (this_object()->query("owner")!=me->query("id"))
    {
        tell_object(me,"你翻了翻这本武功秘籍，却觉得过于晦涩难懂。\n");
        return 1;
    }
    if (me->query("safari_skill/qz2"))
    {
        tell_object(me,"你不是已经掌握了先天功先天神罡了吗？\n");
        return 1;
    }
    if ((int)me->query_skill("xiantian-gong")<500)
    {
        tell_object(me,"你的先天功境界太浅，先天神罡对于你过于艰难了。\n");
        return 1;
    }
    
    message_vision("$N开始认真研读$n，掌握了先天功先天神罡的运功方法！\n"NOR, me,this_object());
    me->set("safari_skill/qz2",1);
    message_vision("$N很诡异地无风自燃起来了。\n",this_object());
    destruct(this_object());
    return 1;		
}