//Zine 艄公，长江边收钱的，钱多船就快

inherit "/d/huanghe/npc/shaogong.c";
#include <ansi.h>
#include "change.h";
#include "die.h"

int accept_object(object me, object obj)
{            
        int i;
        
        if (!obj->query("money_id"))
                return 0;
                
        if(i = obj->value() >= 120 )
        {
                command("nod " + me->query("id"));
                command("say 大爷，你老快请上船。\n");
                me->set_temp("hhallowed", "1");
                i=obj->value();
                i=i-120;
                change(i,me);
                call_out("destroy", 1, obj);
                return 1;
        }
        else {
                command("say 这点？可不够哦。");
                return 0;
        }
        
}



