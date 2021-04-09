//By Zine Dec 11 2010鄱阳湖任务
//MODIFIED by Zine 2012/11/08
inherit ROOM;
#include <ansi.h>
#include <localtime.h>
#include <login.h>
#include <math.h>
int port=query_ip_port();
int bonus(object me);
void create()
{
	set("short", HIC"小船"NOR);
	set("long", @LONG
这是一条小船，虽小却装备十分精良。船上帆(fan)、桨(jiang)一应齐全，
你可以停船(ting)，到了寻宝地点可以下锚(xiamao)并打捞(dalao)，还有机关
(jiguan)，只要(jie)开系在大青石上的绳索，小船就能顺流而下了。
LONG );
	set("outdoors", "jiangzhou");
    set("item_desc", ([
		"fan" : "船帆可以挂上(gua)，也可以下(xia)帆，船速会随之改变。如果希望进一步控制船速，可以升起(sheng)和收起(shouqi)逆风帆。\n", 
        "jiang" : "两支船桨，无风的时候也可以划动(hua)。\n",
        "jiguan" : "船上有明显的机关消息，却不知道有什么用处。\n",
	]));
	set("no_clean_up", 0);
	set("no_task",1);
    set("no_die",1);
    set("no_sleep_room",1);
    set("objects", ([
        "/d/jiangzhou/npc/mes" : 1,
        ]));
	setup();
    call_out("selfcheck",1);
	
}

void init()
{ 
    add_action("do_jie","jie");
    add_action("do_xia","xia");
    add_action("do_sheng","sheng");
    add_action("do_shouqi","shouqi");
    add_action("do_gua","gua");
    add_action("do_hua","hua");
    add_action("do_ting","ting");
    add_action("do_xiamao","xiamao");
	add_action("do_dalao","dalao");
    add_action("do_zhi","zhi");
    add_action("do_step","step");
    add_action("do_xiufu","xiufu");
    add_action("do_check","check");
}
int do_check()
{
    tell_object(this_player(),"小船上的机关还可以使用"+chinese_number(query("pyh/zhi"))+"次。\n");
	return 1;
}

int xiufu(object me)
{
    this_object()->add("pyh/zhi",1);
    if (me&&living(me))
    tell_object(me,"船上的机关被你修复了一些。\n");
    return 1;
}

int do_xiufu()
{
    object ob=this_object(),tool;
    object me=this_player();
    int neili=(int)me->query("neili"),flag=0,neili_require=5000,neili_loss=1000;
    if (me->is_fighting()||me->is_busy())
    {
        tell_object(me,"这样是来不及的。\n");
        return 1;
    }
    if (ob->query("pyh/zhi")>=6)
    {
        tell_object(me,"这里的机关已经完全被修复。\n");
        return 1;
    }
	if (!tool=present("gongju",me))
	{
		flag=0;
	}
	else
	{
		if (tool->query("owner")==me)
		flag=tool->query("is_boat_tool");
	}
	neili_require=neili_require*(3-flag)/3;
	neili_loss=neili_loss*(3-flag)/3;
	if (neili_require<=0)
	{
		neili_require=5000;
	}
	if (neili_loss<=0)
	{
		neili_loss=1000;
	}
    if (neili<neili_require)
    {
        tell_object(me,"修复机关极耗心力，你的内力并不够用。\n");
        return 1;
    }
    me->add("neili",-neili_loss);
    me->add_busy(3);
    ob->add("xiufu",1);
    if (ob->query("xiufu")>4)
    {
        me->add("neili",-neili_loss);
    }
    if (ob->query("xiufu")>8)
    {
        me->add("neili",-neili_loss);
    }
    if (ob->query("xiufu")>10)
    {
        tell_object(me,"机关损耗严重，只能修复到这个程度了。\n");
        return 1;
    }
    call_out("xiufu",3,me);
    message_vision("$N开始认真修复机关。\n",me);
    return 1;
}

int do_step()
{
    object me=this_player();
    object *all=all_inventory(this_object());
    if (time()-(int)me->query_temp("pyh/step_time")<90)
    {
        tell_object(me,"老玩这招就不灵了。\n");
        return 1;
    }
    message_vision(HIG"$N猛然一踩船舷，小船猛烈摇晃起来，所有人都立足不稳。\n",me);
    me->set_temp("pyh/step_time",time());
    for (int i=0;i<sizeof(all);i++)
    {
        if (userp(all[i])||!all[i]->is_character())
        {
            continue;
        }
        if (random(4))
        {
			if (random(2))
			{
				all[i]->add_busy(1+random(2)+random(2));
				message_vision("$N吓得面色苍白，久久回不过神来。\n",all[i]);
            }
            all[i]->remove_all_enemy();
        }
    }
    return 1;
}

int selfcheck()
{
    int i;
    object vic,rm;
    object * all=all_inventory(this_object());
    for (i=0;i<sizeof(all);i++)
    {
        if (all[i]->query("id")=="corpse"&&all[i]->query("victim_id"))
        {
            vic=find_player(all[i]->query("victim_id"));
            if (vic && userp(vic))
            {
                rm=load_object("/d/jiangzhou/hubian");
                all[i]->move(rm);
                tell_room(rm,"一具尸体被湖水冲上了岸！\n");
            }
        }
    }
    remove_call_out("selfcheck");
	call_out("selfcheck",60);
	return 1;
}
int win_back(object me)
{
	message_vision("$N高喊一声：返航！\n",me);
	message_vision("$N掉转船头，迅速的划回到了鄱阳湖边。\n",me);
	me->move("/d/jiangzhou/hubian");
	me->delete_temp("pyh/boatpermit");
}
int lose_back(object me)
{
	tell_object(me,"你掉转船头，沮丧的回到了鄱阳湖边。\n");
	me->delete_temp("pyh/boatpermit");
	me->move("/d/jiangzhou/hubian");
}
int jiecheck2(object target)
{
    if (!target->query_temp("pyh/jied"))
    {
        tell_object(target,"你半天没有反应，忘记了钓鱼人给的地点。\n");
        lose_back(target);
    }
    return 1;
}

int jiecheck()
{
	object target,* all=all_inventory(this_object());
	int i;
	for (i=0;i<sizeof(all);i++)
	{
		if (userp(all[i])&&all[i]->query("pyh/start"))
        target=all[i];
        break;
    }
    remove_call_out("jiecheck2");
    call_out("jiecheck2",180,target);
    return 1;
}

int do_zhi(string arg)
{
    object ob=this_object(),me=this_player(),tool,target;
    object * all=all_inventory(ob);
    int i,neili=(int)me->query("neili"),flag=0,neili_require=10000;
    if (ob->query("pyh/zhi")<1)
		return notify_fail("机关已经使用殆尽，不能再用了。\n");
    if (!arg)
    {
        if (ob->query("pyh/stop")&&ob->query("pyh/zhi")>=5&&!me->is_fighting())
        {
			if (!tool=present("gongju",me))
			{
				flag=0;
			}
			else
			{
				if (tool->query("owner")==me)
				flag=tool->query("is_boat_tool");
			}
			neili_require=neili_require*(3-flag)/3;
			if (neili_require<=0)
			{
				neili_require=10000;
			}
            if (neili<neili_require)
            {
                return notify_fail("此刻你的内力太弱，无法用机关重新推动小船。\n");
            }
            else
            {
                ob->delete("pyh/stop");
                ob->set("pyh/zhi",0);
                me->add("neili",-neili_require);
                message_vision("小船缓缓又动了起来，$N也消耗了大量内力。\n",me);
                call_out("distance",10,ob);
                return 1;
            }
        }
        tell_object(me,"你要用机关制住谁？\n");
        return 1;
    }
    if (time()-(int)me->query_temp("pyh/zhi_time")<25)
		return notify_fail("机关刚刚完全运转过一次，要稍等片刻，机簧才能回复原位。\n");
    if(!objectp(target = present(arg, environment(me))))
		return notify_fail("你想用机关对付谁？\n");
	if (!target->is_character())
		return notify_fail("你只能用机关对付活人！\n");
	if (userp(target))
		return notify_fail("你不能用船上机关来对付玩家！\n");
    if (time()-target->query("zhi")<4)
		return notify_fail("你刚刚才用机关害过他，估计他不会再上当了。\n");
	message_vision("$N猛然按动船上机关，制住了$n。\n",me,target);
	ob->add("pyh/zhi",-1);
	if (target->query("zhi")&&target->is_busy())
	{
		message_vision("机关继续推动，把$N生生挤下水去。\n",target);
		me->set_temp("pyh/zhi_time",time());
		destruct(target);
		return 1;
	}
	target->add_busy(8+random(3));
	target->set("zhi",time());
	return 1;
}
int get_box(object me)
{
	object box;
	if (me->query_temp("pyh/done"))
	return 1;
	box=new("/d/nanchang/obj/box");
	box->set("owner",me->query("id"));
	box->move(me);
	me->set_temp("pyh/done",1);
	me->delete_temp("pyh/boatpermit");
	tell_object(me,"也许你可以返航了。可以使用hua back命令。\n");
	return 1;
}
int do_dalao()
{
    object ob=this_object();
    object me=this_player();
    object box,*team;
	if (!ob->query("pyh/xiamao"))
	{
		return notify_fail("你必须要先下锚才能打捞，否则越漂越远，什么都捞不着的。\n");
	}
	if (me->is_busy())
	{
		return notify_fail("你正忙着呢。\n");
	}
	if (me->query_temp("pyh/done"))
	{
		return notify_fail("你已经找到了沉船的宝物，赶紧返回吧(hua back)。\n");
	}
	message_vision("$N开始仔细寻找沉船宝物的线索。\n",me);
    if (random(10)>8 || random(me->query("kar"))>29) //加入福源对打捞的影响,Zine
    {
		if (team=me->query_temp("pyh/team"))
		{
			message_vision("$N等一行人终于找到了鄱阳湖中沉船的宝物，觉得一分为"+chinese_number(sizeof(team))+"，各自保管！\n",me);
			for (int i=0;i<sizeof(team);i++)
			if (team[i]&&userp(team[i])&&living(team[i])&&present(team[i],this_object()))
			get_box(team[i]);
			return 1;
		}
		tell_object(me,HIG"你找到了沉船的宝物！\n"NOR);
        get_box(me);
        return 1;
    }
    else
    {
        message_vision(HIB"$N很沮丧的发现钓上来的都是水草。\n"NOR,me);
        tell_object(me,"你决定再接再厉，越挫越勇(dalao)。\n");
        me->add_busy(4);
        me->add("pyh/dalao",1);
        if (me->query("pyh/dalao")>60)
        me->set("pyh/dalao",60);
        return 1;
    }
}
int do_xiamao()
{
    object ob=this_object(),me=this_player(),*team;
    if (ob->query("pyh/xiamao"))
    {
        tell_object(me,"小船已经被下锚了！\n");
        return 1;
    }
    else if (!me->query_temp("pyh/couldstop"))
    {
        tell_object(me,"现在暂时不能下锚！\n");
        return 1;
    }
    else if ((int)ob->query_temp("pyh/stepcount")!=(int)me->query_temp("pyh/step"))
    {
        message_vision("$N没有按钓鱼人的指示方向划船，现在完全失去了方向。\n",me);
		if (team=me->query_temp("pyh/team"))
		{
			for (int i=0;i<sizeof(team);i++)
			if (team[i]&&present(team[i],this_object()))
			lose_back(team[i]);
		}
		else
        lose_back(me);
        return 1;
    }
    else
    {
        message_vision("$N把锚缓缓放下，立刻开始着手准备打捞(dalao)宝物。\n",me);
        ob->set("pyh/xiamao",1);
        me->add_busy(4);
        return 1;
    }
}

int check(object me)
{
    object ob=this_object(),*team;
    if (!me||me->query_temp("pyh/done")||base_name(environment(me))!="/d/jiangzhou/boat")
    {
        return 1;
    }
    else
    {
		if (time()-me->query_temp("pyh/checktime")>600)
		{
			message_vision("$N打捞用了太久时间，看看天色不早，准备赶紧回去了。\n",me);
			if (team=me->query_temp("pyh/team"))
			{
				for (int i=0;i<sizeof(team);i++)
				if (team[i]&&present(team[i],this_object()))
				lose_back(team[i]);
			}
			else
            lose_back(me);
		}
		else
		{
			remove_call_out("check");
			call_out("check",60,me);
        }
		return 1;
	}
}

int do_ting()
{
    object ob=this_object();
    object me=this_player();
    if (!me->query_temp("pyh/checktime"))
    me->set_temp("pyh/checktime",time());
    if (ob->query("pyh/stop"))
    {
		tell_object(me,"小船已经完全停稳。\n");
    }
    else if (!ob->query("pyh/jie"))
    {
		tell_object(me,"小船根本就没开，还怎么停？\n");
    }
    else
    {
        message_vision("$N手忙脚乱的把小船停了下来。\n",me);
        ob->set("pyh/stop",1);
        remove_call_out("distance");
		check(me);
    }
	return 1;
}
int gene_sz(object me,string type)
{
	object sz,ob=this_object(),*team;
	if (type!="leader")
	{
		sz=new(__DIR__"npc/sz"+(1+random(13)));
		tell_object(me,"一个鄱阳水贼爬上了你的小船。\n");
	}
	else
	{
		sz=new(__DIR__"npc/shuizei");
		tell_object(me,BLINK+HIR+"一个鄱阳水贼头目跳上了你的小船。\n"+NOR);
	}
	if (type=="hua")
	{
		sz->delete("no_pfm");
		sz->set("hua",1);
		sz->set("title",HIG+"鄱阳"+HIW+"内湖"+HIR+"水贼"+NOR);
	}
	if (type=="lishi")
	{
		sz->set("lishi",1);
		sz->set("title",HIB+"鄱阳水贼力士"+NOR);
	}
	if (type=="zhoushi")
	{
		sz->set("zhoushi",1);
		sz->set("title",WHT+"鄱阳水贼咒师"+NOR);
	}
	sz->set("killer",me);
    sz->do_copy(me);
	sz->move(ob);
	if (team=me->query_temp("pyh/team"))
	{
		sz->set("killers_team",team);
		for (int i=0;i<sizeof(team);i++)
		if (team[i]&&userp(team[i])&&present(team[i],this_object()))
		sz->kill_ob(team[i]);
	}
	else
	{
		sz->kill_ob(me);
	}
	if (!sz->query("lishi")&&!sz->query("zhoushi"))
    sz->exer();
    return 1;
}
int gene(object me)
{
	object ob=this_object();
	if (!me||environment(me)!=ob)
	return 1;
    if (random(12))
    {
        gene_sz(me,"normal");
    }
    if (ob->query("pyh/distance")>10)
    {
        if (!me->query("pyh/easytask")&&!me->query("pyh/simpletask")&&!random(40))
        {
            gene_sz(me,"leader");
        }
        else
        {
            gene_sz(me,"normal");
        }
    }
    if (ob->query("pyh/distance")>22)
    {
        if (!random(3))
        {
            gene_sz(me,"leader");
        }
        else
        {
            gene_sz(me,"normal");
        }
    }
	if (ob->query("pyh/team_member")&&!random(8))
	{
		gene_sz(me,"lishi");
	}
	if (ob->query("pyh/team_member")&&!random(12))
	{
		gene_sz(me,"zhoushi");
	}
    return 1;
}

int distance(object ob)
{
    object *team,me,*all_user=all_inventory(ob);
    int n,i,flag=0,flag2=0;
    string word;
	ob->add("pyh/distance",1);
	for (i=0;i<sizeof(all_user);i++)
	{
		if (userp(all_user[i]))
		flag2=1;
	}
	if (flag2==0)//船上无人
	return 1;
	tell_room(ob,BLINK+HIW+"小船已经顺流漂出了"+chinese_number(ob->query("pyh/distance"))+"里开外了。\n"+NOR);
    remove_call_out("gene");
	if (ob->query("pyh/distance")>ob->query("pyh/target_distance"))
	flag=1;
	if (ob->query("pyh/team_member"))
	{
		team=ob->query("pyh/team_member");
		for (i=0;i<sizeof(team);i++)
		{
			if (team[i]&&userp(team[i])&&present(team[i],this_object()))
			{
				if (flag)
				{
					tell_object(team[i],"你们一行人恍惚时间过长，过了钓鱼人跟你说的地点，茫茫鄱阳湖，完全无法找起。\n");
					lose_back(team[i]);
					team[i]->set_temp("pyh/humanerror",1);
				}
				else
				call_out("gene",1,team[i]);
			}
		}
	}
	else
	{
		me=ob->query("pyh/singer_user");
		if(!ANTIROBOT_D->stopped()&&ob->query("pyh/distance")>14
        &&!random(8)&&!me->query_temp("pyh/again") && 
        (int)me->query_temp("pyh/downflow")-(int)ob->query("pyh/distance")>=4
        &&!me->query_temp("pyh/canrobot")
        &&!me->query("pyh/simpletask")
		&&!me->query_temp("pyh/team")
		&&present(me,ob))
		{
			me->add_temp("pyh/again",1);
			n=1+random(3);
			ob->add("pyh/target_distance",n);
			me->add_temp("pyh/downflow",n);
			tell_object(me,"钓鱼人(diaoyu ren)告诉你：位置好像有变\n");
			tell_object(me,HIR+BLINK+"钓鱼人传音\n"NOR);
			word="多漂"+chinese_number(n)+"里";
			ANTIROBOT_D->mxpantirobot_ex(me,word);
		}
		if (flag&&me&&environment(me)==ob)
		{
			tell_object(me,"你恍惚时间过长，过了钓鱼人跟你说的地点，茫茫鄱阳湖，完全无法找起。\n");
			lose_back(me);
			me->set_temp("pyh/humanerror",1);
		}
		else
		call_out("gene",1,me);
	}
    call_out("distance",25-10*((int)ob->query("pyh/fan"))+20*((int)ob->query("pyh/ni")),ob);
    return 1;
}
int do_jie(string arg)
{
    object ob=this_object();
    object me=this_player();
    int distance=0;
    if (!arg||member_array(arg,({"绳索","绳","sheng","shengsuo"}))==-1)
		return notify_fail("你要解开什么？\n");
	else if (ob->query("pyh/jie"))
		return notify_fail("已经解开绳索了，你还要解什么？\n");
    else
    {
        message_vision(HIW"$N解开系在大石上的绳索，小船顺流而下。\n"NOR,me);
        ob->set("pyh/jie",1);
        me->set_temp("pyh/jied",1);
        me->delete_temp("pyh/boatpermit");
        remove_call_out("distance");
        call_out("distance",10,ob);
        return 1;
    }
}
int actions(object me,int act)
{
	object ob=this_object();
	mapping action,*actions=({
		(["succ_msg":HIC+"$N升起了船帆，船速明显提升起来了。\n","fail_msg":BLU+"船帆已经升到顶了，还怎么升？\n","mark":"pyh/fan","value":1,]),
		(["succ_msg":HIW+"$N收起了逆风帆，船速提高了一些。\n","fail_msg":WHT+"逆风帆已经收起了！\n","mark":"pyh/ni","value":0,]),
		(["succ_msg":HIW+"$N挂起了逆风帆，船速降到了最底。\n","fail_msg":WHT+"逆风帆已经挂起了！\n","mark":"pyh/ni","value":1,]),
		(["succ_msg":HIC+"$N降下了船帆，船速明显降了下来。\n","fail_msg":BLU+"船帆已经下到底了！\n","mark":"pyh/fan","value":0,]),
	});
	action=actions[act];
	if (ob->query(action["mark"])==action["value"])
		return notify_fail(action["fail_msg"]);
	else
	{
		ob->set(action["mark"],action["value"]);
		message_vision(action["succ_msg"]+NOR,me);
		return 1;
	}
}
int do_gua()
{
    object me=this_player();
	return actions(me,0);
}

int do_shouqi()
{
    object me=this_player();
	return actions(me,1);
}

int do_sheng()
{
    object me=this_player();
	return actions(me,2);
}

int do_xia()
{
    object me=this_player();
	return actions(me,3);
}

int huacheck(object me)
{
	object *team,ob=this_object();
    message_vision("小船被$N向"+me->query_temp("pyh/direction")+"划出了"+chinese_number(this_object()->query_temp("pyh/stepcount"))+"里了。\n",me);
    tell_object(me,"如果你觉得到了，就可以下锚(xiamao)了，如果还没到那就继续划(hua)吧。\n");
    me->set_temp("pyh/couldstop",1);
    if (!random(5)&&(int)me->query_temp("pyh/stepcount")<(int)me->query_temp("pyh/step")&&ob->query("pyh/distance")>18)
	{
		if (team=me->query_temp("pyh/team"))
		{
			for (int i=0;i<sizeof(team);i++)
			if (team[i]&&present(team[i],this_object()))
			gene_sz(team[i],"hua");
		}
		else
		gene_sz(me,"hua");
	}
    return 1;
}
int do_hua(string arg)
{
    object ob=this_object(),me=this_player(),shuizei;
    object *all=all_inventory(ob),*team;
    int i;
	string *legal_dirs=({"back","south","north","east","west"});
    me->set_temp("pyh/checktime",time());
    check(me);
    for (i=0;i<sizeof(all);i++)
    {
        if(all[i]->query("isshuizei"))
			return notify_fail("你还没杀光水贼呢，哪有空划桨？\n");
    }
    if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢，现在不能划桨！\n");
    if (!arg||member_array(arg,legal_dirs)==-1)
		return notify_fail("你要往哪个方向划桨？\n");
	if (time()-query_temp("pyh/hua_time")<2)
		return notify_fail("再划快一点船就要散架了！\n");
	if (arg=="back")
    {
		if (team=me->query_temp("pyh/team"))
		{
			for (i=0;i<sizeof(team);i++)
			if (team[i]&&userp(team[i])&&living(team[i])&&present(team[i],this_object()))
			{
				win_back(team[i]);
			}
		}
		else
		win_back(me);
        if (me->query("pyh/simpletask"))
        {
			bonus(me);
			me->delete("pyh/start");
			me->delete_temp("pyh");
        }
        ob->delete("pyh/using");
        return 1;
    }
    if ((int)ob->query("pyh/distance")!=(int)me->query_temp("pyh/downflow")||me->query_temp("pyh/direction")!=arg)
    {
		if (team=me->query_temp("pyh/team"))
		{
			message_vision("$N没有按钓鱼人的指示方向划船，现在完全失去了方向。\n",me);
			for (i=0;i<sizeof(team);i++)
			if (team[i]&&userp(team[i])&&living(team[i])&&present(team[i],this_object()))
			lose_back(team[i]);
		}
		else
		{
			tell_object(me,"你没有按钓鱼人的指示方向划船，现在完全失去了方向。\n");
			lose_back(me);
		}
        return 1;
    }
    me->add_busy(5);
	if (!me->query_temp("pyh/report_distance"))
	{
		if (team=me->query_temp("pyh/team"))
		{
			message( "channel:" + "baowei",HIG + "【鄱阳湖】" + me->query("name")+HIG+"一行人乘小船顺流而下，已经成功漂出了"+chinese_number(ob->query("pyh/distance"))+"里开外了。\n"NOR,users());
			for (i=0;i<sizeof(team);i++)
			if (team[i]&&userp(team[i])&&living(team[i])&&present(team[i],this_object()))
			team[i]->set_temp("pyh/report_distance",1);
		}
		else
		{
			message( "channel:" + "baowei",HIG + "【鄱阳湖】" + me->query("name")+HIG+"乘小船顺流而下，已经成功漂出了"+chinese_number(ob->query("pyh/distance"))+"里开外了。\n"NOR,users());
			me->set_temp("pyh/report_distance",1);
		}
	}
	message_vision("$N拿出船桨，把小船奋力向"+me->query_temp("pyh/direction")+"方向划去。\n",me);
	remove_call_out("distance");
	ob->add_temp("pyh/stepcount",1);
	ob->set_temp("pyh/hua_time",time());
    ANTIROBOT_D->same_as_fullme(me);
	call_out("huacheck",5,me);
	if (team=me->query_temp("pyh/team"))
	{
		for (i=0;i<sizeof(team);i++)
		if (team[i]&&userp(team[i])&&living(team[i])&&present(team[i],this_object()))
		{
			team[i]->delete_temp("pyh/couldstop");
            bonus(team[i]);
		}
	}
	else
	{
		me->delete_temp("pyh/couldstop");
		bonus(me);
	}
	return 1;
}
int check_team_bonus()
{
	object ob=this_object(),*team;
	if (team=ob->query("pyh/team_member"))
	{
		for (int i=0;i<sizeof(team);i++)
		{
			if (!team[i])
			return 0;
			if (!userp(team[i]))
			return 0;
			if (!present(team[i],ob))
			return 0;
		}
		return 1;
	}
	return 0;
}
int calc_bonus(int base_value,object me,int self_factor,int index)
{
	float factor;
	int exp,adjust;
	exp=base_value*((int)me->query_temp("pyh/count")+to_int(me->query_temp("pyh/extra_count")))*self_factor/3+(index+3)*me->query("kar")*me->query("kar") *4;
	if (exp>80000)
	exp=80000+(exp-80000)/20*16;
	if (exp>120000)
	exp=120000+(exp-120000)/20*13;
	if (exp>150000)
	exp=150000+(exp-150000)/20*11;
	if (exp>200000)
	exp=200000+(exp-200000)/10*3;
//每获得2m潘阳湖经验，掉1%奖励 by seagate@pkuxkx
    factor=1-to_float(me->query("exp/pyh"))/200000000;
    if (factor<0.5)
    	factor=0.5;
	if (!me->query("pyh/simpletask")&&!me->query("pyh/easytask")&&factor<0.8)//重宝奖励至少0.8
		factor=0.8;
	if (check_team_bonus()==1)//开船时候所有人员都在
		factor=0.75;
    exp=to_int(exp*factor);
    if (me->query_temp("pyh/canrobot"))
    exp=exp/3*2;
    if (me->query("pyh/simpletask"))
    exp=exp*(5+(random(3)))/10;
    if (me->query_temp("pyh/downflow")<=15)
    {
        adjust=(int)me->query_temp("pyh/downflow");
        if (adjust<8)
        adjust=8;
        exp=exp*(adjust+10)/30;
    }
    if (me->query_temp("pyh/downflow")>23)
    exp=exp*27/25;
    if (me->query_temp("pyh/downflow")>28)
	exp=exp*27/25;
    if (me->query_temp("pyh/downflow")>32)
    exp=exp*21/20;
	exp/=2;
	return exp;
}
int bonus(object me)
{
    mixed* timeinfos;
    object ob=this_object();
    object zihua,ren=find_object("d/jiangzhou/npc/diaoyuren");
    int old_f,old_exp,index, flag=0,exp, pot, rep, base_value,hour,self_f,adjust;
	float factor,inc_percent;
	int *team_number=({2,3,4,5}),no,adv_adjust=0,event_bonus=0,event_remain=0;
	float *reward_thresholds=({30.0,20.0,15.0,10.0}),threshold;
	if (me->query_temp("pyh/bonus"))
    return 1;
    timeinfos = localtime(time());
    hour = timeinfos[LT_HOUR];
	if (hour==0||hour==4||hour==8||hour==12||hour==16||hour==20)
	self_f=(int)me->query("int");
	if (hour==1||hour==5||hour==9||hour==13||hour==17||hour==21)
	self_f=(int)me->query("con");
	if (hour==2||hour==6||hour==10||hour==14||hour==18||hour==22)
	self_f=(int)me->query("dex");
	if (hour==3||hour==7||hour==11||hour==15||hour==19||hour==23)
	self_f=(int)me->query("str");
	if (self_f<10)
	self_f=10;
	old_f=self_f;
	if (ob->query("pyh/team_member"))//组队任务取属性最大值,Zine 2012/12/12
	{
		self_f=max(({me->query("int"),me->query("con"),me->query("dex"),me->query("str")}));
		tell_object(me,HIC"你仔细回忆了之前和鄱阳水贼战斗的经过，对战斗中武功的运用有了更深的理解！\n"NOR);
		switch (random(7))
		{
			case 0:
				adv_adjust=2;
				break;
			case 1:
				adv_adjust=1;
				break;
			default:
				adv_adjust=0;
		}
		event_remain="/adm/daemons/statisticd.c"->temp_digital("PYH_Team_Event_Bonus",1);
		if (event_remain>0)
		{
			event_bonus=1;
			if (event_remain>1)
			message("chat",HIG"【鄱阳湖】此时组队寻宝双倍奖励活动尚余"+chinese_number(event_remain-1)+"次，大家赶紧来参加。\n"NOR,users());
		}
	}
	else
	tell_object(me,HIG"你仔细回忆了之前和鄱阳水贼战斗的经过，觉得受益匪浅！\n"NOR);
	if (wizardp(me))
	tell_object(me,self_f+"\n");
	index=me->query("combat_exp")/100000000;
	base_value=300+(int)me->query("level")+random(200);
	if (index<1)
	index=1;
	if (index>8)
	index=8;

	exp=calc_bonus(base_value,me,self_f,index);
	exp=exp*(adv_adjust+10)/10;
	pot=(ob->query("pyh/team_member")?exp/4+random(exp/2):exp/3+random(exp/2));
	rep=random(exp/100)+exp/100;
	me->set("pyh/exp",exp);
	me->set("pyh/pot",pot);
	me->set("pyh/rep",rep);
	if (ob->query("pyh/member_number"))
	{
		no=member_array(ob->query("pyh/member_number"),team_number);
		if (no==-1)
		no=sizeof(team_number)-1;
		threshold=reward_thresholds[no];
		old_exp=calc_bonus(base_value,me,old_f,index);
		if (to_float(me->query_temp("pyh/mobs_kill"))/to_float(this_object()->query("pyh/total_mobs"))*100.0<threshold)
		{
			exp=1;
			pot=1;
			rep=1;
			tell_object(me,HIR+BLINK+"你在刚才的漂流中贡献太低，无法获得正常的奖励！\n");
			me->set_temp("pyh/low_contribute",1);
		}
		else if (old_exp<exp)
		{
			inc_percent=(to_float(exp)-to_float(old_exp))/to_float(old_exp)*100.0;
			tell_object(me,HIC+"因为这次寻宝任务由组队完成，你获得了比单人完成高出"+inc_percent+HIC+"%的奖励。\n"+NOR);
		}
    }
	if (adv_adjust)
	tell_object(me,HIC+"这次组队寻宝任务额外获得了"+chinese_number(adv_adjust)+"成的奖励。\n"+NOR);
	exp = REWARD_D->add_exp(me,exp);
    pot = REWARD_D->add_pot(me,pot);
    rep = REWARD_D->add_rep(me,rep);
    if (exp>75000)
	me->set("pyh/toohighbonus",1);
	if (exp>120000)
	me->set("pyh/toohighvalue",1);
	CHANNEL_D->do_channel(ren, "sys_misc",sprintf("%s在鄱阳湖寻宝任务中获得经验：%d、潜能：%d、声望：%d。", me->query("name"), exp, pot, rep));
	message("chat",HIG"【鄱阳湖】"+me->query("name")+HIG+"在鄱阳湖寻宝任务中获得经验"+ chinese_number(exp) +"点、"+
                      "潜能"+ chinese_number(pot) +"点、"+
                      "声望"+ chinese_number(rep) +"点。\n"NOR,users());
    tell_object(me,HIC "你觉得自己冥冥中增加了：\n"
                + chinese_number(exp) + "点实战经验，\n"
                + chinese_number(pot) + "点潜能，\n"
                + chinese_number(rep) + "点声望。\n"NOR);
                
    me->add("exp/pyh", exp);
    me->add("pot/pyh", pot);
    me->set_temp("pyh/bonus",1);
	if (me->query_temp("pyh/team"))
	{
		flag=1;
	}
	log_file("user/pyh",sprintf("%s于%s获得经验%d，总计漂流%d里，杀贼系数：%f。多人任务：%d\n",me->query("id"),ctime(time()),exp,me->query_temp("pyh/downflow"),to_float(me->query_temp("pyh/count"))+me->query_temp("pyh/extra_count"),flag));
    if ((int)me->query("newjobs/completed/pyh")%10==0)
    {
        zihua=new("/d/guiyunzhuang/obj/zihua");
        zihua->move(me);
        tell_object(me,HIC+"打扫刚才的战场，你却发现不知是谁遗留下了一幅字画，赶紧收入怀中。\n"+NOR);
    }
    return 1;
}