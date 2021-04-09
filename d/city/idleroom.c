inherit ROOM;

#include <ansi.h>
void create()
{
	set("short","发呆室");
	set("long",@LONG
这里是北大侠客行发呆室，平时在这里发呆聊天的人可真不少。大家没什么
事情别老呆中央广场，到这里发呆吧，这里还比较安全。
LONG);

        set("least_msg",1);
        set("repair_room",1);
	set("objects", ([
		"/new_quest/xiaobao/manbudong" :1,
		"/d/wizard/npc/xunbu.c":1,
                "/d/wizard/npc/vast":1,
                "/d/wizard/npc/aiai":1,
	]));
	set("exits", ([
		"enter" : __DIR__"xiaojinku",
	]));
	set("no_sleep_room",1);
	set("cant_drop",1);
	set("no_fight", 1);
           setup();
	"/clone/board/idle_b"->foo();
}
void init()
{
	add_action("do_exert", "yun");
	add_action("do_none", "hitall");
	add_action("do_none", "killall");
	add_action("do_none", "kill");
	add_action("do_exert", "exert");
	add_action("do_none", "attack");
	add_action("do_none", "qiecuo");
	add_action("do_none", "xiulian");
	add_action("do_none", "perform");	
    add_action("do_fadai", "fadai");
}
int do_exert(string arg)
{
	string verb,target;
	if(arg!="roar" && arg!="bhcs") return 0;
  if(sscanf(arg, "%s %s", verb, target)==2)
  	if(verb!="roar" && verb!="bhcs" )
  		return 0;
	return 1;
}

int do_fadai(string arg)
{
        object me;
//        string family;
//        string *familys=({"丐帮","全真派","天龙寺","古墓派","日月神教","桃花岛","峨嵋派","明教","华山派","少林派","武当派","星宿派","雪山派","天地会","白驼山","朝廷","神龙教"});
        int i;
        me=this_player();
//        family=me->query("family/family_name");
        
        if(me->is_busy())  return notify_fail("瞧你忙的？\n");
/*        if (member_array(family,familys)<0)
        {
            tell_object(me,HIW"你做起了白日梦来……\n"NOR); 
            tell_object(me,HIW"在你的梦里，不用努力练功，只要随便发发呆就能成为武功高手。\n"NOR);
            return 1;
        } */
        if (me->query("age")>17)
        {
             return notify_fail("这么大了，回家发呆去吧！\n");
          }
        else if(me->query("max_neili")>1000||me->query("max_jingli")>1000||me->query("combat_exp")>110000){
             return notify_fail("这么大了，回家发呆去吧！\n");
          }
        else{
                me->set("qi",me->query("max_qi")/2+random(me->query("max_qi")/2));
                me->set("jing",me->query("max_jing")/2+random(me->query("max_jing")/2));
                tell_object(me,HIW"你做起了白日梦来……\n"NOR); 
				tell_object(me,HIW"在你的梦里，不用努力练功，只要随便发发呆就能成为武功高手。\n"NOR);
                me->set("idleapply",1); //add by Zine 12/2/2011 给不用发呆室的玩家增加了福利quest,做个判断
                me->start_busy(10);
                return 1;
                if (me->query("max_neili")>950||me->query("max_jingli")>950||me->query("combat_exp")>109000)
                	tell_object(me,HIR"18岁以前，最大内力1000以上或最大精力1000以上或经验110000以上将不能使用发呆室，\n"
                		+"你的状态已经接近此上限，请多加注意！\n"NOR);
                
                return 1;
            }
}
