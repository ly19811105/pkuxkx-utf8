#include <room.h>
#include <ansi.h>

inherit ROOM;
string look_dummy();
void create()
{
        set("short", CYN+"静室"+NOR);
        set("long", @LONG
这是铜雀台的静室，房内零散放着一些木人(muren)。

LONG
        );
        set("exits", ([
			"southwest" : __DIR__"dating",
			"up" : __DIR__"liangong2",
            
        ]));
        set("item_desc",
        ([
        "muren":(:look_dummy:),
        ]));
        set("no_sleep_room",1);
        setup();
      
}
void init()
{
	add_action("do_liangong","liangong");
	add_action("do_yanxi","yanxi");
}

int do_liangong(string arg)
{
	object me=this_player();
	string *basic=({"cuff","hand","claw","finger","strike","leg","sword","blade","hammer","axe","spear","halberd","whip","fork","dagger"});
	if (me->query("newjobs/completed/safari")<4)
	{
		return 0;
	}
	if (me->is_busy()||me->is_fighting())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	if (!arg||member_array(arg,basic)==-1)
	{
		write(RED"你要练习哪种基本功夫？\n"NOR);
		return 1;
	}
	if (me->query_skill(arg,1)>500)
	{
		write("你的"+arg+"已经足够高了，在这里学不到什么了。\n");
		return 1;
	}
	if (me->query("qi")<100)
	{
		write("你的气血不足，不能继续练习了！\n");
		return 1;
	}
	me->add("qi",-80);
	me->add_temp("tqt/liangong_dummy",1);
	if (me->query_temp("tqt/liangong_dummy")%100==50)
	{
		me->add_busy(2);
	}
	me->improve_skill(arg, 30+random(30));
	tell_object(me,HIC+"你对着木人，反复练习"+arg+"，取得些许进步！\n"+NOR);
	return 1;
}

string look_dummy()
{
	object me=this_player();
	string msg;
	if (me->query("newjobs/completed/safari")<4)
	msg="这些木人造型奇特，不知道作何用途！\n";
	else
	msg="这些形态不一的木人似乎可以练功(liangong)，也有许多高手来这里研习(yanxi)特技。\n";
	return msg;
}

int valid_leave(object me,string dir)
{  
    int i;
    object *all,room;
	all=deep_inventory(me);
	if (dir=="up")
	{
		for (i=0;i<sizeof(all);i++)
		{
			if (userp(all[i]))
			{
				return notify_fail(HIY"不许背人进入静室二层。\n"NOR);
			}
		}
		if (objectp(me->query_temp("tqt/liangong2/place"))&&me->query_temp("tqt/liangong2/place")->isroom())
		room=me->query_temp("tqt/liangong2/place");
		else
		room=new(__DIR__"liangong2");
		message_vision("$N向"+room->query("short")+"走了上去！\n",me);
		if (room)
		{
			tell_room(room,me->name()+"从"+this_object()->query("short")+"走了上来。\n");
			me->move(room);
			me->set_temp("tqt/liangong2/place",room);
			return notify_fail("\n");
		}
		else
		return notify_fail("似乎有什么奇怪的东西阻止你走上静室二层！\n");
	}
	return ::valid_leave(me,dir);
}

int full_level(string sk, int lv)
{
	int max;
	if (file_size(SPECIAL_D(sk) + ".c") <0)
		max = 4;
	else
		max = SPECIAL_D(sk)->max_level();
	if (lv>=max)
		return 1;
	else
		return 0;
}

int do_yanxi()
{
	object me=this_player();
	string sk = "confuse";
	string skn = HIR "「飞龙乘云」" NOR;
	int lv;
	if (me->is_busy())
		return notify_fail("你还是把手上的事情忙完了再说吧！\n");
	if (!me->query("special_skill/confuse") && !me->query("special_skill/devastate"))
		return notify_fail(HIY"你对木人看了半天，也弄不明白这对修炼特技有什么帮助。\n"NOR);
	if (me->query("special_skill/confuse"))
	{
		sk = "confuse";
		lv = me->query("special_level/confuse");
		if (full_level(sk,lv))
		{
			if (me->query("special_skill/devastate"))
			{
				sk = "devastate";
				skn = HIR "「龙葬八荒」" NOR;
				lv = me->query("special_level/devastate");
				tell_object(me, HIY"你的" HIR "「飞龙乘云」" HIY "已经提升至最高级了。\n"NOR);
			}
			else
				return notify_fail(HIY"你的" HIR "「飞龙乘云」" HIY "已经提升至最高级了。\n"NOR);
		}
	}
	else {
		sk = "devastate";
		skn = HIR "「龙葬八荒」" NOR;
		lv = me->query("special_level/devastate");
	}
	if (full_level(sk,lv))
		return notify_fail(HIY"你的"+skn+HIY"已经提升至最高级了。\n"NOR);
	
    if(me->query("special/levelup_point") < 1)  
        return notify_fail("你的特技升级点不足，无法继续提升" + skn +"等级！\n");
    if(me->query("safari_credit") < 10)  
        return notify_fail("你的铜雀台积分不足，无法继续提升" + skn +"等级！\n");
    if(me->query("balance") < 1000000000)  
        return notify_fail("你的黄金存款不足，无法继续提升" + skn +"等级！\n");
    if(me->query("combat_exp") < 1000000000)  
        return notify_fail("你的实战经验不足，无法继续提升" + skn +"等级！\n");
    if(( me->query("potential") - me->query("learned_points") )< 20000000 )  
        return notify_fail("你的潜能不足，无法继续提升" + skn +"等级！\n");
	
	tell_object(me, HIC"你凝神细看木人的关节构造，无意识地随意拍击木人，陷入了对真龙特技的沉思之中。\n\n"NOR);
	
	if (!me->query_temp("xiulian_confuse_devastate"))
	{
		tell_object(me, HIW"提升特技需要付出很大的代价，包括：\n"NOR
						+"    一点特技升级点\n"
						+"    十点铜雀台积分\n"
						+"    十万两黄金\n"
						+"    一亿点经验\n"
						+"    二千万点潜能\n"
						+HIC"你确定要继续研习(yanxi)提升" + skn + HIC"等级吗？\n"NOR);
		me->set_temp("xiulian_confuse_devastate", 1);
		return 1;
	}
	me->delete_temp("xiulian_confuse_devastate");
    me->add("special/levelup_point", -1);
    me->add("safari_credit", -10);
    me->add("balance", -1000000000);
    me->add("combat_exp", -100000000);
    me->add("potential", -20000000);
	me->add("special_level/"+sk, 1);
	
	tell_object(me, HIY"片刻之后，你从沉思中回过神来，点了点头，似乎心有所感。\n"NOR);

    CHANNEL_D->do_channel(this_object(), "jh", 
		"铜雀台："+me->query("name")+"("+capitalize(me->query("id"))+")的" +skn+ HIW "提升到等级"+chinese_number(lv+1)+"！\n",-1);
	log_file("user/safari_info", ""+me->query("id")+"在"+ctime(time())
		+"消耗1特技升级点、10铜雀积分、10万黄金、100m经验、20m潜能，提升"+sk+"特技等级到"+chinese_number(lv+1)+"。\n");
	
	me->start_busy(5);
	return 1;
}
