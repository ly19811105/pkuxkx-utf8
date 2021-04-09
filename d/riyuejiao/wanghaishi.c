//wanghaishi.c	望海石
//by bing
//modified by Zine
#include <ansi.h>
#include <room.h>
inherit ROOM;
string look_bei();
void create()
{
	set("short","望海石");
	set("long",@LONG 
这里是悬崖边上。奇特的是，这里有一块大石头斜斜地探出头去，有一小半在
悬崖之外。据说这里是观看云海的好去处。每当天阴或者初晨之时，这里云雾弥漫，
恰似波浪翻腾。坐在望海石上望去仿佛置身于云海之中，飘渺无比。有人在云海前
立了一面石碑(shibei)。
LONG
	);
	set("exits", ([
		"west"	: __DIR__"yading",
	]));
    set("item_desc",([
  	"shibei" : (:look_bei:),
        ]));
        
  set("lingwu_family", "日月神教");
	set("outdoors", "riyuejiao");
	setup();
}

string look_bei()
{
    object me=this_player();
    if (me->query("family/family_name")!="日月神教")
    {
        return "这是我踏月色而来吹嘘自己功绩，所立一块石碑。\n";
    }
    else
    {
        return HIY+"神教弟子见下：\n\t"+HIW+"今有日月闪电锤、日月剑法、日月刀法、判官笔法四种武功悟出新意，\n\t需要日夜在此处勤练不辍，方可有成。\n\t人心力或有穷尽，一生可悟出两种武功真谛已为人中龙凤，\n\t唯须结合入门任务，才能领会神教武功真意。\n\t我踏月色而来。某年某月某日。\n"+NOR;
    }
}

void init()
{
    add_action("do_lian",({"lian","practice",}));
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
        if (times>30
            &&me->query("family/family_name")=="日月神教"
            &&(random(10000)>9994||wizardp(me))
            &&me->query("riyuepfm/count")<2)
        {
            if (me->query("riyuepfm/count")==0&&me->query("exp/rynewbiejob")>20000
                &&arg=="hammer"&&me->query_skill_mapped("hammer") == "shandian-chui"
                &&!me->query("riyuepfm/chui")&&(int)me->query_skill("shandian-chui",1)>200)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/chui",1);
                tell_object(me,"你悟出日月闪电锤的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出日月闪电锤的真谛！\n"+NOR,users());
            }
            if (me->query("riyuepfm/count")==0&&me->query("exp/rynewbiejob")>20000
                &&arg=="sword"&&me->query_skill_mapped("sword") == "riyue-jian"
                &&!me->query("riyuepfm/jian")&&(int)me->query_skill("riyue-jian",1)>200)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/jian",1);
                tell_object(me,"你悟出日月剑法的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出日月剑法的真谛！\n"+NOR,users());
            }
            if (me->query("riyuepfm/count")==0&&me->query("exp/rynewbiejob")>20000
                &&arg=="blade"&&me->query_skill_mapped("blade") == "riyue-dao"
                &&!me->query("riyuepfm/dao")&&(int)me->query_skill("riyue-dao",1)>200)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/dao",1);
                tell_object(me,"你悟出日月刀法的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出日月刀法的真谛！\n"+NOR,users());
            }
            if (me->query("riyuepfm/count")==0&&me->query("exp/rynewbiejob")>20000
                &&arg=="sword"&&me->query_skill_mapped("sword") == "panguan-bifa"
                &&!me->query("riyuepfm/bi")&&(int)me->query_skill("panguan-bifa",1)>200)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/bi",1);
                tell_object(me,"你悟出快笔打穴的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出快笔打穴的真谛！\n"+NOR,users());
            }
            if (me->query("riyuepfm/count")==1&&me->query("exp/rynewbiejob")>50000
                &&arg=="hammer"&&me->query_skill_mapped("hammer") == "shandian-chui"
                &&!me->query("riyuepfm/chui")&&(int)me->query_skill("shandian-chui",1)>400)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/chui",1);
                tell_object(me,"你悟出日月闪电锤的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出日月闪电锤的真谛！\n"+NOR,users());
            }
            if (me->query("riyuepfm/count")==1&&me->query("exp/rynewbiejob")>50000
                &&arg=="sword"&&me->query_skill_mapped("sword") == "riyue-jian"
                &&!me->query("riyuepfm/jian")&&(int)me->query_skill("riyue-jian",1)>400)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/jian",1);
                tell_object(me,"你悟出日月剑法的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出日月剑法的真谛！\n"+NOR,users());
            }
            if (me->query("riyuepfm/count")==1&&me->query("exp/rynewbiejob")>50000
                &&arg=="blade"&&me->query_skill_mapped("blade") == "riyue-dao"
                &&!me->query("riyuepfm/dao")&&(int)me->query_skill("riyue-dao",1)>400)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/dao",1);
                tell_object(me,"你悟出日月刀法的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出日月刀法的真谛！\n"+NOR,users());
            }
            if (me->query("riyuepfm/count")==1&&me->query("exp/rynewbiejob")>50000
                &&arg=="sword"&&me->query_skill_mapped("sword") == "panguan-bifa"
                &&!me->query("riyuepfm/bi")&&(int)me->query_skill("panguan-bifa",1)>400)
            {
                me->add("riyuepfm/count",1);
                me->set("riyuepfm/bi",1);
                tell_object(me,"你悟出快笔打穴的真谛！\n");
                message("chat",HIM"【日月神教】"+me->query("name")+HIM+"在黑木崖顶悟出快笔打穴的真谛！\n"+NOR,users());
            }
        }
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