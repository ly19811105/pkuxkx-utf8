// Room: /d/shaolin/dmyuan2.c
// Date: YZC 96/01/19

inherit ROOM;
#include <ansi.h>

void init();
int do_lin(string arg);
void create()
{
        set("short", "达摩院二楼");
        set("long", @LONG
这是一座古朴的殿堂。西首的墙上挂满了各类武功图谱，不
少白须白眉的老僧们正端坐在图谱画轴之前，似乎在苦苦思索。
南北山墙是高及屋顶的大书架，走近细看，它们是各门各派的武
功秘笈，屋正中摆着几张矮几诃和几个团，几位老僧正在入定中。
LONG
        );
        set("least_msg",1);

        set("exits", ([
                 "north" : __DIR__"chanyuan",
                "down" : __DIR__"dmyuan",
        ]));

        set("objects",([
                CLASS_D("shaolin") + "/xuan-bei" : 1,
                __DIR__"npc/xiao-bei" : 1,
        ]));
        set("no_fight",1);
		    set("no_sick_spread",1);
		    set("lingwu_family", "少林派");
        setup();
}

void init()
{
        object me=this_player();
        if(!me->query("luohan_winner") && userp(me))
        {
                me->move("/d/shaolin/dmyuan");
               message_vision("$N被赶了下去，没有破阵也来凑什么热闹呀。\n",me);
        }
        add_action("do_lian",({ "lian", "practice" }));
}

int do_lian(string arg) //加入高级兵器级别练习效率 by Zine
{
        object me=this_player();
        object where = environment(me);
        object weapon,weapon2;
        string skillname, sname;
        int skill, skill_basic,times,i,realtimes;
        //空手功夫
        string *kongshou_skill = ({"claw","finger","strike","cuff","unarmed","hand","leg","array"});

        seteuid(getuid());
        weapon = me->query_temp("weapon");
        weapon2 = me->query_temp("secondary_weapon");

        if(me->is_busy()) return notify_fail("你现在正忙着呢。\n");
        if(me->is_fighting() ) return notify_fail("临阵磨枪？来不及啦。\n");
        if(me->query("lingjiu/last_xiulian_time"))
                return notify_fail("你现在正在恢复武功，没有精力研究武功。\n");

        if(!arg || (sscanf(arg, "%s %d", arg, times)< 2 ))
                return notify_fail("指令格式：practice|lian <技能> <次数>\n");
        if(times <1 || times>50) return notify_fail("练习次数应该在 1-50 次！\n");

        if( !stringp(skillname = me->query_skill_mapped(arg)) )
                return notify_fail("你只能练习用 enable 指定的特殊技能。\n");
/*
//这个设定除了让full更有难度之外无任何实际意义
        if (arg == "parry" && me->query_skill(skillname, 1) > me->query_skill(arg, 1) / 5 * 4
                && skillname != "flatter" )
                return notify_fail("你的基本招架已经对练习"+to_chinese(skillname)+"无所助益了。\n");
*/

        if (member_array(arg, kongshou_skill) != -1) 
        {
                if ((weapon || weapon2)) 
                        return notify_fail("你必须空手才能练习"+to_chinese(skillname)+"。\n");
        }
        else if ( arg == "force" )
                return notify_fail("特殊内功无法练习，你可以通过(learn)或者(xiulian)来提高。\n");
        else if ( arg == "iron-cloth" )
                return notify_fail("特殊硬功无法练习，你可以通过(learn)来提高。\n");
        //暂时不限制dodge 和parry
        else if ( arg != "dodge" && arg != "parry" && arg != "throwing")
        {
                if (!weapon || ((string)weapon->query("skill_type") != arg)) 
                        if (!weapon2 || ((string)weapon2->query("skill_type") != arg)) 
                                return notify_fail("你要装备 "+arg+" 类武器才能练习"+to_chinese(skillname)+"。\n");
        }
        skill_basic = me->query_skill(arg, 1);
        skill = me->query_skill(skillname, 1);

        if( skill < 1 )
                return notify_fail("你好像还没有学过这项技能吧？最好先去请教别人。\n");
        if( skill_basic < 1 )
                return notify_fail("你对这方面的技能还是一窍不通，最好从先从基本学起。\n");

        if( skill_basic == skill )
                return notify_fail("你需要提高基本功，不然练得再多也没有用。\n");
        if( skill_basic <= skill )
                return notify_fail(sprintf("你的%s的级别还没有%s的级别高，不能通过练习来提高了。\n",
                        to_chinese(arg), to_chinese(skillname)));
                //判断是否是自创武功
        if( !find_object(SKILL_D(skillname)) && file_size(SKILL_D(skillname)+".c") < 0)
                return notify_fail("自创武功必须到闭关室用selfpractice和selfthinking练习。\n");
        if( !SKILL_D(skillname)->valid_learn(me) ) return 0;

        realtimes=0;
        for(i=0;i<times;i++)
        {
                if( SKILL_D(skillname)->practice_skill(me) )
                {
                    
                    if (arg=="sword" && me->query("adv_weapon/class/sword/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="blade" && me->query("adv_weapon/class/blade/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="staff" && me->query("adv_weapon/class/staff/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="whip" && me->query("adv_weapon/class/whip/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="axe" && me->query("adv_weapon/class/axe/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="halberd" && me->query("adv_weapon/class/halberd/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="dagger" && me->query("adv_weapon/class/dagger/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="spear" && me->query("adv_weapon/class/spear/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="hammer" && me->query("adv_weapon/class/hammer/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                    if (arg=="throwing" && me->query("adv_weapon/class/throwing/lv")>=10)//高级兵器级别大于4级，加25%效率 Zine
                    {
                        me->improve_skill(skillname, skill_basic/10 +1, skill_basic > skill? 0: 1);
                    }
                        me->improve_skill(skillname, skill_basic/5 +1, skill_basic > skill? 0: 1);
                        realtimes++;
                }
                else break;
        }
        if (realtimes)
        {
                if (!environment(me)->query("least_msg"))
                if (!random(3)) tell_room(environment(me),
                        me->name() +
                        "正在专心练习" +
                        to_chinese(skillname) + "。\n", ({ me }));
                write ("你" + ((realtimes == 1)?"试着":"反复") + "练习" + to_chinese(skillname));
                if (stringp(sname = SKILL_D(skillname)->query_skill_name(random(me->query_skill(skillname,1)))))
                        write ("中「" + sname + "」这一招");
                write( "，获得了" + ((realtimes == 1)?"少许":"不少") + "进步！\n");
        }
        else
        {
                if (SKILL_D(skillname)->practice_skill(me))
                {
                        write( HIR "你太累了，没有办法练习"+ to_chinese(skillname) +"。\n" NOR);
                }
                else return 0;
        }
        return 1;  
}                          