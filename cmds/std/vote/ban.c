// vote ban ip! 
// Only realuser can do it!

#include <vote.h> 
#include <ansi.h>

inherit F_CONDITION;

int clear_vote(object me);

int vote(object me, string victimid)
{
        int reason; // vote for what?
        int vv; // valid voter numbers
        int vc; // vote count;
        int df;
        int i;
        string *juror, my_id;
        object user;
        object* all_users;
        object victim;
        
        return notify_fail("此项投票暂时关闭。\n");
        
        if (me->query("id") == victimid)
        {
                if(random(2))
                        me->add("vote/abuse", 10);
                return notify_fail("你不是开玩笑吧？当心被剥夺表决权！\n");
        }

        if(!victimid)
        {
            return notify_fail("没有这个玩家 。\n");
        }
        
        if(file_size("/data/login/"+victimid[0..0]+"/"+victimid+".o") == -1)
        {
            return notify_fail("没有这个玩家。\n");
        }

        if(time() - me->query_temp("vote/last_vote") < 15)
        {
            return notify_fail("你不是开玩笑吧？当心被剥夺表决权！\n");
        }

        if(BAN_D->user_is_banned(victimid) != "")
        {
            return notify_fail("该玩家已经被封禁。\n");
        }
        if(SECURITY_D->get_wiz_level(victimid) > 0)
        {
            return notify_fail("对巫师和新手导师有意见请在论坛投诉。\n");
        }
        my_id = me->query("id");

        if(!me->is_realuser())
        {
                return notify_fail("只有实名制玩家才有权利投票ban id。申请实名用户，请访问pkuxkx.com,点击RealUser\n");
        }
        user=me->query_temp("link_ob");

        vc = BAN_D->vote_banuser_dict(victimid);

        df = 7 - vc;
        if (vc<7 )//&& !me->query("vote/special_judge"))
        {
                shout( HIG "【表决】"+me->name()+HIG+"("+me->query("id")+")"
                +"投票封禁" +"("+victimid+")"
                +"的ID，还差"+sprintf("%d", df)+"票。\n" NOR);

                log_file("static/vote_ban",sprintf("%s %s vote ban %s\n",ctime(time()),me->query("id"),victimid));
        }
        else 
        {
                shout( HIG "【表决】"+me->name()+HIG+"("+me->query("id")+")"
                +"投票封禁" +"("+victimid+")"
                +"的ID。"+victimid+"被封禁ID！\n" NOR);

                log_file("static/vote_ban",sprintf("%s %s vote ban %s\n",ctime(time()),me->query("id"),victimid));
                BAN_D->add_user(victimid + " " + (time() + 30*3600*24) + " " + "恶意刷屏");
                BAN_D->clear_banuser_dict(victimid);
                victim = find_player(victimid);
                if(objectp(victim) && userp(victim))
                {
                    LOGIN_D->kickout(victim);
                }
        }

        write(HIY"感谢你的投票。此投票已经记录系统日志。\n"NOR);

        me->set_temp("vote/last_vote",time());

        return 1;
}
