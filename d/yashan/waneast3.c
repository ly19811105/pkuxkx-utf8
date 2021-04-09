//模板
//modified by Zine 限制老玩家刷大米，每250K给一次海战机会。
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "海边基地");
	set("long", @LONG
这里已经到了海边了，你可以看到济远和广乙两艘
军舰静静的躺在这里。有几个清兵在这里看守，如果日
军要侵略我们，这里的济远和广乙就会最前出动对日军
作出反击。但是最让舰长头疼的还是炮弹不够的问题，
朝廷已经无法再拨款下来购买炮弹，但是要打起来，靠
朝廷买的那一点点炮弹肯定不够，这该如何是好呢？
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : 2,
		]));
	set("exits", ([ 
		  "west" : __DIR__"waneast2.c",
//                  "济远" : "/d/jwhz/paocang1.c",
//                  "广乙" : "/d/jwhz/paocang1_1.c",
		]));
	set("no_clean_up", 1);
	setup();
}

 
/*void init()
{
	add_action("do_test","test");
	add_action("do_st","st",);
}

int do_st()
{
	object me=this_player();
	if (time()-(int)me->query("甲午海战/last_time")>3600)
				{
					me->set("甲午海战/last_time",time());
					me->set("甲午海战/last_exp",me->query("combat_exp"));
				}
				return 1;
}

int do_test()
{
	object me=this_player();
	int last_exp,current_exp,phase,old_phase,last_time,i;
	last_exp=(int)me->query("甲午海战/last_exp");
		current_exp=(int)me->query("combat_exp");
		last_time=(int)me->query("甲午海战/last_time");
		i=1;
		while (current_exp<3000000&&current_exp>i*250000)
			{
				i++;
			}
		phase=i;
		i=1;
		while (last_exp<3000000&&last_exp>i*250000)
			{
				i++;
			}
		old_phase=i;
		if (time()-last_time>3600&&phase-old_phase<1)
		{
			return notify_fail("每250K阶段只有一次海战机会，你已经用掉了。\n");
		}
		else
		{
			tell_object(me,"ok"+phase+old_phase+"\n");
			return 1;
		}
}
*/
int valid_leave(object me,string dir)
{
	object jwhz;
    object *all;
	int last_exp,current_exp,phase,old_phase,last_time,i,j;
	if(dir=="济远"||dir=="广乙")
	{
		jwhz=load_object("/adm/daemons/jwhz.c");
		last_exp=(int)me->query("甲午海战/last_exp");
		current_exp=(int)me->query("combat_exp");
		last_time=(int)me->query("甲午海战/last_time");
		i=1;
		while (current_exp<3000000&&current_exp>i*250000)
			{
				i++;
			}
		phase=i;
		i=1;
		while (last_exp<3000000&&last_exp>i*250000)
			{
				i++;
			}
		old_phase=i;
		if (time()-last_time>3600&&phase-old_phase<1&&current_exp<3000000)
		{
			return notify_fail("每250K阶段只有一次海战机会，你已经用掉了。\n");
		}
		if (me->query("combat_exp")<250000)
		{
			return notify_fail("你的经验太低，这时候上去不是爱国，而是添乱！\n");
		}
		all=all_inventory(me);
        for (j=0;j<sizeof(all);j++)
        {
            if (userp(all[j]))
            {
                return notify_fail("背人上船？你想贩奴吗？\n");
            }
        }
        if(!jwhz->query("begin"))
		{
			return notify_fail("军舰岂是能够随便上去的？\n");
		}
        
		else //根据日本发兵前进入军舰的人数计算参加海战的人数
		{
			if (!me->query_temp("jwhz/taskid") || me->query_temp("jwhz/taskid")!=jwhz->query("taskid"))
			{
				if (!me->query("biography/jobs/jwhz"))
				{
					me->set("biography/jobs/jwhz",time());//个人传记记录第一次完成任务时间ZINE
				}
				me->set_temp("jwhz/taskid",jwhz->query("taskid"));
				if (time()-(int)me->query("甲午海战/last_time")>3600)
				{
					me->set("甲午海战/last_time",time());
					me->set("甲午海战/last_exp",me->query("combat_exp"));
				}
				
				jwhz->add("player_count",1);
			}
		}
	}
	return ::valid_leave(me,dir);
}

