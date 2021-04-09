#include <ansi.h>

inherit __DIR__"machine.c";

int str = 100;
int do_dissamble(string arg);
void dissamble_nu(object p);
void attack_target(object target);

void create()
{
	set_name("诸葛弩", ({ "zhuge nu","nu"}) );
	set("long",
		"诸葛孔明创制的连弩，能一次齐射数箭至数十箭，威力惊人。\r\n"
	);
		
	set_weight(1000);
	set("no_get",1);
	set("unit","张");
	set("value",10000);
	setup();
}

void init()
{
	//add_action("do_break","break");
	//有奇门八卦，并且解密过的玩家可以拆掉诸葛弩
	add_action("do_dissamble","chai");
}

//进入战斗状态，每12s+random(8)发射一轮，每轮发射level*2支箭
void start()
{
	
	//第一次启动时间5 ~ 8s
	remove_call_out("attack");
  call_out("attack",5+random(4));
  stopped = 0;
}

//寻找所有敌人
int filter_enemy(object ob)
{
	if(userp(ob) && present(ob,environment()))		
	{		
		if(ob->query("jiaofei/tmz/xinren") > 0 || ob->query("mud_age") < 86400)
			return 0;
		else
		{	
			if(random(ob->query("combat_exp")/1000000 + ob->query("level")) < 10) 
			{
				//新手被选中的几率降低
				return 0;
			}
			else
			{
				return 1;		
			}

		}
	}
	return 0;
}

void attack()
{
	int shotnum = query("level")*3;
	object* allob = all_inventory(environment(this_object()));
	object* targets;
	object target;
	string skill;
	object tengjia;
	int dodge;
	int damage;
	
	if(!present("tufei",environment()) && !present("durer npc",environment()))
	{
		//没有土匪了
		remove_call_out("attack");
  	    call_out("attack",12+random(8));		
		return;
	}

	message("vision",sprintf(HIR"%s上的机械已经全部就绪，%d支利箭同时呼啸而出！空气中弥漫着箭头破空的锐响！\r\n"NOR,query("name"),shotnum),environment(this_object()));
	if(!undefinedp(allob))
	{
		targets = filter_array(allob,"filter_enemy");
		
		
		while(shotnum > 0 && sizeof(targets) > 0)
		{
            target = targets[random(sizeof(targets))];
            attack_target(target);
			shotnum--;	
			targets = filter_array(allob,"filter_enemy");            
		}
		
	}
	//下次启动时间15s+random(10)
	remove_call_out("attack");
  call_out("attack",12+random(10));		
}

//某些机关可以在这里对关闭机关的奸细做出伤害
//比如烈火车
void stop(object player)
{	
	remove_call_out("attack");
	stopped = 1;
}
//暂时不可break
void do_break(int arg)
{
	
}

int do_dissamble(string arg)
{
    object p = this_player();
    object o = this_object();
    int exp,pot,neili,jing,timecost;
    
    if(!arg || (arg != "zhuge nu" && arg != "nu"))
    {
        return 0;
    }
    if(stopped == 1)
    {
        return notify_fail("这台诸葛弩并没有发动，不用去管它。\n");
    }
    if(p->query_skill("qimen-bagua",1) <= 0)
    {
        return notify_fail("你对机关之术一无所知，小心拆不成反倒丢了小命。\n");
    }
    if(p->query("qimen-bagua/jiemi") != 1)
    {
        return notify_fail("虽然你的奇门八卦之术学的不错，但是面对眼前诸葛孔明创制的精妙连弩，完全不知道何如下手拆卸。\n");
    }
    if(JIAOFEI_D->istaskstart() != 1)
    {
        return notify_fail("朝廷的剿匪大军还没开拔，不能打草惊蛇。\n");
    }
    
    if(time() - p->query("jiaofei/nu/last_time_dissamble_machine") < 60)
    {
        return notify_fail("你太累了，休息一下再来吧。\n");
    }
    
    if(p->is_busy() || p->query_temp("jiaofei/nu/dissamble_exp") != 0)
    {
        return notify_fail("你正忙着呢。\n");
    }
    
    //开始拆卸，消耗时间为:
    // (nulevel - qimen-bagua/100) * 60
    // 最少要15s,cooltime 是 1 min
    // 消耗内力,精力: nulevel*500
    // 有直接奖励，qimen-bagua nulevel*100
    // exp nulevel*200
    // pot nulevel*200
    neili = query("level") * 500;
    jing  = query("level") * 500;
    if(p->query("neili") < neili) 
    {
        return notify_fail("你的内力不够。\n");
    }
    if(p->query("jing") < neili) 
    {
        return notify_fail("你的精力不够。\n");
    }    
    timecost = (query("level") - p->query_skill("qimen-bagua",1)/100)*60;
    if(timecost < 15) timecost = 15;
    p->set_temp("jiaofei/nu/dissamble_exp",query("level") * 200);
    p->set_temp("jiaofei/nu/dissamble_pot",query("level") * 200);
    p->set_temp("jiaofei/nu/dissamble_skill",query("level") * 100);
    p->set_temp("jiaofei/nu/neili_cost",query("level") * 500);
    p->set_temp("jiaofei/nu/jing_cost",query("level") * 500);
    p->set("jiaofei/nu/last_time_dissamble_machine",time());
    call_out("dissamble_nu",timecost,p);
    
    message("vision",sprintf("%s蹲了下来，仔细研究如何破坏掉这诸葛弩中的机巧。\n",p->query("name")),p);   
    
    p->add_busy(timecost/2);
    
    return 1;
}

void dissamble_nu(object p)
{
    if(!objectp(p) || !userp(p) || !living(p) || environment(p) != environment(this_object()))
    {
        return;
    }
    message("vision",sprintf("%s终于找到了诸葛弩的机巧所在，轻轻一拨，诸葛弩停止了射击！%s累的满头大汗。\n",p->query("name"),p->query("name")),p); 
    p->add("combat_exp",p->query_temp("jiaofei/nu/dissamble_exp"));
    p->add("exp/jiaofei",p->query_temp("jiaofei/nu/dissamble_exp"));    
    p->add("potential",p->query_temp("jiaofei/nu/dissamble_pot"));
    p->add("pot/jiaofei",p->query_temp("jiaofei/nu/dissamble_pot"));
        
    p->improve_skill("qimen-bagua",p->query_temp("jiaofei/nu/dissamble_skill"));
    
    p->receive_damage("jing",p->query_temp("jiaofei/nu/jing_cost"));
    p->add("neili",-p->query_temp("jiaofei/nu/neili_cost"));
    
    
    tell_object(p,sprintf("你获得了%d点经验，%d潜能。你的奇门八卦之术有所精进！\n",
    p->query_temp("jiaofei/nu/dissamble_exp"),
    p->query_temp("jiaofei/nu/dissamble_pot")
    ));
    
    p->delete_temp("jiaofei/nu"); 
    
    stop(p);
}


void attack_target(object target)
{
    string skill;
    int dodge;
    object tengjia;
    int damage;
    if(target->query("jiaofei/tmz/xinren") > 0 || target->query("mud_age") < 86400 || stopped == 1)
    {
        return;
    }
	message("vision",query("name")+"发出的一支箭正向你急速飞来！\r\n",target);
	//对目标射击！躲闪算法: random(有效dodge等级) > level*20+50+target->query_temp("jiaofei/score")/4，躲闪成功			
	//正在busy的人中的概率更高
	skill=target->query_skill_mapped("dodge");
	dodge = target->query_skill("dodge")/2 + target->query_skill(skill);
	if(random(dodge) > query("level")*150+50+target->query_temp("jiaofei/score")/2 || random(10) < (int)target->query_busy())
	{
		message("vision",HIG"你急忙闪躲，箭擦着你的衣角飞过！好险。\r\n"NOR,target);
		//target->add_busy(1);
	}
	else
	{
		message("vision",RED"你急忙闪躲，但是太慢了，箭已经到了你的跟前。\r\n"NOR,target);
		//如果身上穿有硬藤甲，有一半机会躲避
		tengjia = target->query_temp("armor/armor");
		if(objectp(tengjia) && tengjia->query("id") == "ying tengjia" && random(2) == 1)
		{
			message("vision",HIG"箭矢射在硬藤甲，顿时被滑到了一边。你毫发无损。\r\n"NOR,target);
			tengjia->add("naijiu",-1);
			if(tengjia->query("naijiu") <= 0)
			{
				message("vision",HIG"硬藤甲受损太重，完全无法使用了。\r\n"NOR,target);
				tengjia->unequip();
				destruct(tengjia);
			}
		}
		else
		{
			//目标进行防御，算法：random(query_temp("apply/armor")) > level*20+50+target->query_temp("jiaofei/score")/3
			//杀的土匪越多，伤害越大，这是为了平衡胡一刀
			damage = query("level")*180+50+target->query_temp("jiaofei/score")*2 - random(target->query_temp("apply/armor")) ;
			if(damage <= 0)
			{
				message("vision",HIG"幸好你身穿的盔甲够厚，挡住了这支箭\r\n"NOR,target);
				if(intp(target->query_busy()) && target->query_busy()<10)
				{
					target->add_busy(1);
				}
			}				
			else
			{
				message("vision",HIR"结果箭穿透你的盔甲，扎进了你的身体里！顿时血流如注！\r\n"NOR,target);
				target->receive_wound("qi",damage/2,"被诸葛连弩射");
				target->receive_damage("qi",damage,"被诸葛连弩射");
                COMBAT_D->report_status(target);
				
				if(target->query("qi") <= 0 || target->query("eff_qi") <= 0)
				{
					message("vision",sprintf(HIR"%s被诸葛弩发出的锐箭一箭穿心，直接钉死在地上！\r\n"NOR,target->query("name")),environment(this_object()));
					target->die();						
				}
				
				if(intp(target->query_busy()) && target->query_busy()<10)
				{
					target->add_busy(2);
				}
			}
		}
	}
}			