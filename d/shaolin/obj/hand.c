// book3.c-iron.c
// Modified iszt@pkuxkx, 2007-04-08

#include <armor.h>

inherit HANDS;

void create()
{
        set_name("铁手掌", ({ "iron hand", "hand", "shu", "book" }));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("long",
                        "易筋经攻防篇\n"
                        "这是一块铁手掌，上面凹凹凸凸刻满了人形搏击的场面。\n");
                set("value", 500);
                set("material", "steel");
                set("armor_prop/armor", 3 );
                set("skill", ([
                        "name":         "parry",        
                        "exp_required": 0,      
                        "jing_cost":    10,     
                        "difficulty":   20,     
                        "max_skill":    29      
                ]) );
        }
}
void init()
{
        if( this_player() == environment() )
        {
                add_action("do_study", "du");
                add_action("do_study", "study");
        }
}
int do_study(string arg)
{
        object me = this_player();
        if ((int)me->query("jing")<20)
                return notify_fail("你现在太累了，无法专心研究新知。\n");
        if ( arg != "iron hand" && arg != "hand" )
                return notify_fail("你要学什么？\n");
        if ( me->is_fighting()
                && (int)me->query_skill("parry", 1) >= 30
                && (int)me->query_skill("parry", 1) <= 100)
        {
                me->receive_damage("jing", 20);
                me->improve_skill("parry", me->query("int"));
                message_vision("$N一边战斗，一边抽空急急忙忙地拿出铁手掌仔细研究。\n", me);
                return 1;
        }
        return 0;
}
