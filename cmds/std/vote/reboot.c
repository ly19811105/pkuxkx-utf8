// vote reboot
#include <vote.h> 
#include <ansi.h>

inherit F_CONDITION;

int clear_vote(object me);

int vote(object me, object victim)
{
        object *usr;
        int i,vote_num;
        string myip;
        object npc;

        if (me != victim)
        {
              me->add("vote/abuse", 10);
              return notify_fail("你怎么可以冒充别人呢？当心被剥夺表决权！\n");
        }
        
        if (me->query_temp("vote/reboot"))
                return notify_fail("你已经投过票了呀！\n");

        vote_num = 0;
        usr = users();
        me->set_temp("vote/reboot",1);
         if ( sizeof(usr)>=20 )
        {
                i = sizeof(usr);
                myip = query_ip_number(me);
                while (i--)
                {
                        // 断线，非正常玩家除外
                        if( environment(usr[i]) && ( usr[i]->query_temp("netdead")==0 ) )
                        {
                                if ( (usr[i]->query_temp("vote/reboot")) && ( query_ip_number(usr[i]) == myip ) && ( (usr[i]->query("id") != me->query("id")) ) )


                                {
                                              message_vision("由于$N双登投票，$N的投票权被剥夺了！\n",me);
                                              shout( HIR "【注意】"+me->name()+HIG+"由于双登投票，投票权被无限期剥夺！\n"NOR);
                                        return 1;
                                }
                                else
                                {
                                        if (usr[i]->query_temp("vote/reboot"))
                                                vote_num++;
                                }
                        }
                }
                i = sizeof(usr);
                if (vote_num >= i * 1/2) 
                {
                        shout ( HIC "【投票】"+me->name()+HIG+"投票要求重起，系统将重新启动！\n"NOR);
                        seteuid(getuid());
                        npc = new("/d/wizard/npc/god.c");
                        npc->move("/d/city/kedian");
                        npc->shut_down();
                        return 1;
                }
                else
                {
                        shout (HIC "【投票】"+me->name()+HIG+"投票要求重起，还差" + sprintf("%d", i * 1 /2 - vote_num) + "票。\n"NOR);
                        return 1;
                }
        }
        else
        {
                write("现在在线玩家少于20人，不能对此进行投票。\n");
        }
        return 1;
}


