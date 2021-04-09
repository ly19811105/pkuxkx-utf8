// vote chblk
// Modified by iszt@pkuxkx, 2007-03-11

#include <vote.h> 
#include <ansi.h>

inherit F_CONDITION;

int clear_vote(object me);

int vote(object me, object victim)
{
        int reason; // vote for what?
        int vv; // valid voter numbers
        int vc; // vote count;
        int df;
        string *juror, my_id;
        object user;
        if (me == victim)
        {
                if(random(2))
                        me->add("vote/abuse", 10);
                return notify_fail("你不是开玩笑吧？当心被剥夺表决权！\n");
        }

        if ((reason = (int)victim->query("vote/reason"))>0 && (reason!=V_CHBLK))
        {
                return notify_fail("要把当前的表决完成以后才可以提新的动议。\n");
        }

        if( victim->query("chblk_on") ) 
        {
                return notify_fail(victim->name()+"的频道已经是关闭的了。\n");
        }

        if (reason <= 0)
        {
                victim->set("vote/reason", (int)V_CHBLK); 
        }
        
        my_id = me->query("id");

        // dont allow me to vote twice for the same issue
        juror = victim->query("vote/juror");

        if( !pointerp(juror) )
        {
                victim->set("vote/juror", ({ my_id }) );
        }
        else if( member_array(my_id, juror) == -1 ) 
        {
                victim->set("vote/juror", juror+({ my_id }) );
        }
        else
        {
                me->add("vote/abuse", 10);
                return notify_fail("一人一票！滥用表决权是要受惩罚的！\n");
        }
        user=me->query_temp("link_ob");
        vv = (int) ("/cmds/std/vote")->valid_voters(me)/3;  
        if(wizardp(me))
        {
            //不要在代码中加入任何ID判断 -- Jason
            vc = victim->add("vote/count", 50);
        }
        else if (user&&user->query("realuser_verified"))
            vc = victim->add("vote/count", 2);
        else
            vc = victim->add("vote/count", 1);
        
        df = vv - vc;
        if (vv < 4) df = 4 - vc;

        if (df>1)
        {
                shout( HIG "【表决】"+me->name()+HIG+"("+me->query("id")+")"
                +"投票关闭" +victim->name()+HIG+"("+victim->query("id")+")"
                +"的交谈频道，还差"+sprintf("%d", df)+"票。\n" NOR);
                victim->apply_condition("vote_clear", 10);
        }
        else 
        {
                shout( HIG "【表决】"+me->name()+HIG+"("+me->query("id")+")"
                +"投票关闭" +victim->name()+HIG+"("+victim->query("id")+")"
                +"的交谈频道。"+victim->name()+HIG+"的交谈频道被关闭了！\n" NOR);
                victim->apply_condition("vote_clear", -10);
                victim->set("chblk_on", 1);
                if (victim->query("chblk_rumor"))
                        victim->delete("chblk_rumor");
                if (victim->query("chblk_chat"))
                        victim->delete("chblk_chat");
        }

        return 1;
}
