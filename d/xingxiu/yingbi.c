// 影壁
// edit: by zine Oct 19 2010

inherit __DIR__"xxconfig";
#include <ansi.h>
#include <weapon.h>;

void create()
{
	set("short", BLU"石壁"NOR);
	set("long", @LONG
一块大石壁，石壁上几个小人挥舞着杖法。
LONG
	);
    set("normaldesc", @LONG
一块大石壁，石壁上几个小人挥舞着杖法。
LONG
	);
	set("exits", ([ 
		"west" : __DIR__"neidian",
		
    ]));
	//set("objects", ([(__DIR__"npc/qinjun") : 1,
    //]));
  
  set("lingwu_family", "星宿派");
	setup();
	::create();
}

void init()
{
    add_action("do_watch","watch");
    add_action("do_lian",({ "lian", "practice" }));
}




int do_lian(string arg)
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
                    if (arg=="staff" && me->query_skill("tianshan-zhang",1)<150 && me->query("family/family_name") == "星宿派" && me->query("combat_exp")<500000 &&!me->query("newbiehongdou") && !me->query("newbiediaoyu"))
                    {
                        me->improve_skill(skillname, skill_basic/8 +1, skill_basic > skill? 0: 1);
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



int do_watch(string arg)
{
        object me;
        int times;
        me = this_player();
        if (me->query("family/family_name")!="星宿派")
        {
            return 0;
        }
        if(!arg)
                return notify_fail("你想读什么？\n");
        if (sscanf(arg, "石壁 %d", times) == 1 || arg == "石壁")
        {
        
            if(!times)
                    times = 1;
            if(times > 10)
                    return notify_fail("贪多嚼不烂，学习次数多过十次你记不住。\n");
            if (times <0)
                return notify_fail("你想干吗？\n");
            {
            }
            if(me->is_busy())
            {
                write("你正忙着呢。\n");
                return 1;
            } 
            if( (int)me->query("jing",) < 40 * times)
            {
                write("你精神不够集中，无法领悟石壁。\n");
                return 1;
            }

            message_vision("$N正专心观看石壁上的图画。\n", me);
            if( (int)me->query_skill("staff",20) < 1)
            {
                    write("你完全不会杖法，啥也没领悟到。\n");
                    return 1;
            }
            if( (int)me->query_skill("tianshan-zhang",1) < 1 && me->query("family/family_name")=="星宿派")
            {
                    me->improve_skill("tianshan-zhang",1);
            }
            if( (int)me->query_skill("literate",1) < 1)
            {
                    write("你根本就是一个文盲，啥也没学会。\n");
                    return 1;
            }
            if( (int)me->query_skill("staff",1) > 120)
            {
                    write("你看了半天，发觉石壁上的杖法对你而言太浅了。\n");
                    return 1;
            }
            else
            {
                message_vision("$N对着石壁研究了一会,似乎对杖法有些心得。\n", me);
                me->add("jing", -40 * times);
                me->improve_skill("staff",(int)(me->query_skill("staff")/2+random(me->query("int"))/3) * times);
                if (random(100)>95 && !me->query("xxpfm/readyingbi"))
                {
                    tell_object(me,BLINK HIR"你心念一闪，石壁上舞杖的小人似乎都是一个个文字(zi)组成的。\n"NOR);
                    me->set("xxpfm/readyingbi",1);
                }
                return 1;
            }
        }
        if (sscanf(arg, "zi %d", times) == 1 || arg == "zi")
        {
            if (!me->query("xxpfm/readyingbi"))
            return 0;
            if(!times)
                    times = 1;
            if(times > 10)
                    return notify_fail("贪多嚼不烂，学习次数多过十次你记不住。\n");
            if(me->is_busy())
            {
                write("你正忙着呢。\n");
                return 1;
            } 
            if( (int)me->query("jing",) < 25 * times)
            {
                write("你精神不够集中，无法学习石壁上的字。\n");
                return 1;
            }

            message_vision("$N正专心观看石壁上的文字。\n", me);
            
            if( (int)me->query_skill("literate",1) > 120)
            {
                    write("你看了半天，发觉石壁上的文字对你而言太浅了。\n");
                    return 1;
            }
            else
            {
                message_vision("$N对着石壁上的文字研究了一会,似乎对读书写字有些心得。\n", me);
                me->add("jing", -20 * times);
                me->improve_skill("literate",1+(int)(me->query_skill("staff")/2+random(me->query("int"))/3) * times);
                return 1;
            }
        }
}
