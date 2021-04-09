// File         : dianhuo.c

#include <ansi.h>

int exert(object me)
{
        object ob;

        if( objectp(me->query_temp("weapon")) && objectp(me->query_temp("secondary_weapon")))
                return notify_fail("你双手不空，怎么点火？\n");                

        if( (int)me->query_skill("huagong-dafa",1) < 90 )
                return notify_fail("你的化功大法修为还不够，无法点火。\n");

        if( (int)me->query("neili",1) < 200 )
                return notify_fail("你的真气太弱，还无法点火。\n");

        if(objectp(ob = present("huo yan", environment(me))) && ob->query_temp("seeme")==me->query("id"))
                return notify_fail("地上已经有一堆火焰！\n");

        message_vision(
                HIR "$N阴笑一声，双手一搓一放，真气激射而出，点起了一堆火焰！\n" NOR,
                me);

        ob = new("/d/xingxiu/obj/huoyan.c");
		ob->set_temp("seeme",me->query("id"));  //picewolf修改，for wananta
        ob->move(environment(me));
        //考虑使用毒粉make fire，使用exert dianhuo好像不合理，因为很多时候是禁止exert的。
        //取消busy。
        //if( me->is_fighting() ) me->start_busy(2);
        me->add("neili",-100);

        return 1;
}
