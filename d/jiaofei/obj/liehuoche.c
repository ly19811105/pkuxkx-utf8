inherit __DIR__"machine.c";

#include <ansi.h>

void attack_target(object target);

/*
    烈火车，攻击方式，随机挑选玩家攻击，玩家无躲避可能。
    被攻击后着火，就是一个condition，每个heart beat 掉
    血.掉血数：5*(level+5)*(level+5)+200，持续时间 100+random(100)
*/
void create()
{
	set_name("烈火车", ({ "liehuo che","che"}) );
	set("long","装满硝石硫磺和柴草的大车，一旦点燃，能将方圆数丈化作火海。\r\n");	
	set_weight(1000);
	set("no_get",1);
	set("unit","辆");
	set("value",10000);	
	setup();
}

void init()
{
	//add_action("do_break","break");
}

//进入战斗状态，每25s+random(8)爆发一次
void start()
{
	
	//第一次启动时间5 ~ 8s
	remove_call_out("attack");
    call_out("attack",5+random(4));
    stopped = 0;
}

void attack()
{
	int level = query("level");
	object* allob = all_inventory(environment(this_object()));
	object* targets;
	object target;
	string skill;
	int dodge;
	int damage;
	
	if(!present("tufei",environment()))
	{
		//没有土匪
		remove_call_out("attack");
		call_out("attack",20+random(10));		
		return;
	}
	
	message("vision",sprintf(HIR"%s上的硝石硫磺被点燃了！火焰疯狂的喷出，风助火势，越来越猛。\r\n"NOR,query("name")),environment(this_object()));
	if(!undefinedp(allob))
	{
		targets = filter_array(allob,"filter_enemy");
				
		for(int i =0;i<sizeof(targets);i++)
		{
            attack_target(targets[i]);
		}
		
	}
	//下次启动时间15s+random(8)
	remove_call_out("attack");
    call_out("attack",15+random(8));		
}

//某些机关可以在这里对关闭机关的奸细做出伤害
//比如烈火车
void stop(object player)
{	
    stopped = 1;
	remove_call_out("attack");
}
//暂时不可break
void do_break(int arg)
{
	
}

void attack_target(object target)
{
    
    int level = query("level");
    if(target->query("jiaofei/tmz/xinren") > 0 || target->query("mud_age") < 86400 || stopped == 1)
    {
        return;
    }    
    //概率不高
    if(random(target->query("kar")) < 35 && target->query_condition("jiaofei-fire") == 0)
    {
        target->set("jiaofei/fire_damage",15*(level+8)*(level+8)+500);
    	target->apply_condition("jiaofei-fire",80+level*10+random(50));		    	
    	message("vision",sprintf(HIY"%s被烈火车喷出的火焰烧着了！%s发出痛苦的嚎叫，啊，啊~，啊~~~~~\r\n"NOR,target->query("name"),target->query("name")),environment(this_object()));    	
    }
}