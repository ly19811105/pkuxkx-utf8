//1999.6.3
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

int return_normal(object ppl,object ob);
void create()
{
	set_name(HIR"归魂剑"NOR, ({ "guihun sword", "sword" }));
	set_weight(10000);
	set("value",1000000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把散发着奇异力量的剑，任何拿起它的人心中都会涌起无穷的仇恨和绝望!\n");
                set("value", 0);
		set("material", "steel");
		set("weapon_prop/strength", 3);
		set("wield_msg", HIY"一片阴森的气霭从$N身后缓缓升起，只见一道白光从剑鞘之中锵然飞出，"NOR
			+HIR"\n这就是武林传说中的\n.........\n..............\n...................\n.............................\n"NOR+HIR"归魂剑，            归魂剑!!!\n" NOR);
		set("unwield_msg", HIY "$N小心的将归魂剑收入鞘中\n" NOR);
	}
	init_sword(200);
	setup();
}

void init()
{
        object me = this_player();
       if (userp(me)==1 || environment()->query("id")!="chapion" )
	{
		message_vision(query("name")+"从$N的身上掉了下来，在地上滚了滚，不见了。\n",this_player());
		destruct(this_object());
		return;
	}
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if(me->query("shaqi")>280)
	{
        me->add_temp("apply/attack",30);
        me->add_temp("apply/dodge", 30);
		me->add("shaqi",1);
		return HIR "$N感到杀气上涌,顿时失去心神,与【归魂剑】的邪恶力量合为一体!!" NOR;
	}
	return HIR ">\n" NOR;
}

