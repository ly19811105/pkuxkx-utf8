// jiaofei room
// more ideas:
// limit the space of room. some small room can only hold few players
// liehuoche, apply condition to player and deduce their hp
// last room in the baoku, accept fight with only one player
// fix by yhzzyahoo 优化了2个算法

inherit ROOM;

#include <ansi.h>
#include "npc_setup.h"



string* machine_types = ({
	__DIR__"obj/zhugenu",//诸葛弩
	//__DIR__"obj/xianjing",//陷阱
	__DIR__"obj/liehuoche"//烈火车
	});
	
int find_same_ip(object me);

object* machines = ({});
string short_name="";//房间的名字 string 
string long_describe="";//房间的一句长描述。系统会加上对机关的描写。
int doorstr = 0;//门的强度，0表示没有门，可以通过。范围从0到100
int backupdoorstr = doorstr;

string nextdirect;//下一个房间的方向
int islastroom = 0;//是否是最后一个房间。
int haskey = 1;//只对最后一个房间有效

int level = 1;//房间的等级,1~9
int intask = 0;//是否进入任务状态

void setup_npc();
void setup_machine();
string default_dirs(string dir); 
int islastroom()
{
	return islastroom;
}

int istaskroom()
{
    return 1;
}
int level()
{
	return level;
}
void setdoorstr(int str)
{
	doorstr = str;
}

void restoredoorstr()
{
	doorstr = backupdoorstr;
}

void jiaofei_init()
{
	//do nothing here. The derived class should init the values
}

void create() 
{ 
    
    string m_desc = "";
	
	jiaofei_init();
	
	backupdoorstr = doorstr;
	
	if(level < 1) level = 1;
	
	set("short", short_name);
	set("no_buzhen",1);// 不允许桃花布阵
	//避免严重刷屏
	set("least_msg",1);
	m_desc = long_describe+"。\r\n";
	
	setup_machine();
	
	if(sizeof(machines) > 0)
	{
		m_desc = m_desc + "    这里设置着重重机关。\r\n";
	}
	
	if(doorstr > 0)
	{
		m_desc = m_desc + "    有一扇大门(gate)通往"+default_dirs(nextdirect)+"。\r\n";
	}
	
	if(islastroom)
	{
	    m_desc = m_desc + "    路旁蹲着一头大石狮子(shizi)。\r\n";
	}
	
	set("long", m_desc);
	
	set("no_clean_up",1);
	set("no_reset",1);
	
	//for testing
	set("no_die",1);
	setup_npc();
	setup();
}

void task_clean_up()
{
    //清除地上的垃圾。只要不是玩家，全部清除。
    //包括机关和土匪。所以被搬过来的npc和丢下的物品都会被清除
    //这是为了减轻系统负担
    
	object* all = all_inventory(this_object());
	
	for(int i =0;i<sizeof(all);i++)
	{
		if(objectp(all[i]) && !userp(all[i]))
		{
			destruct(all[i]);
		}
	}    
}

void create_npc(int tufeilevel,string mode)
{
    object tufei;
    int skilllevel = 0;
	int limit_int=0;
    int property = 0;
    int difficulty = JIAOFEI_D->getdifficulty();
	mapping factors = (["normal":1,"strong":10]);
	int factor = factors[mode];
    
    tufei = new(__DIR__"npc/tufei.c");
	tufei->set("level",tufeilevel);
	if(tufeilevel > 9)
	{
		tufei->set_name(HIY"铁掌帮副帮主"NOR,({"durer npc","fubangzhu"}));
	}
	else
	{
	    tufei->set("name",npc_colors[tufeilevel-1]+"土匪"+NOR);
		tufeilevel = tufeilevel + 10;
    }
	if (tufeilevel<250)
	{
		tufei->set("combat_exp",factor*120000*tufeilevel+factor*2000000);
	}
	else
	{
		tufei->set("combat_exp",factor*180000*tufeilevel+factor*2000000);
	}
	if(undefinedp(npc_family_setup[npc_type])) 
	{
		npc_type = "xingxiu";
	}
    skilllevel = 7*factor*tufeilevel+100;
	limit_int = 3550+10*difficulty;
//    if(skilllevel > 2000 + 7*(difficulty+150)) skilllevel = 2000 + 7*(difficulty+150);
	if(skilllevel > limit_int) skilllevel = limit_int;
    
	evaluate(npc_family_setup[npc_type],tufei,skilllevel,1);

	tufei->set("str", 50);
	tufei->set("int", 50);
	tufei->set("con", 50);
	tufei->set("dex", 50);    
	property = 500*factor+30*factor*tufeilevel;
	limit_int = 15500 + 180*difficulty;
	//if(property > 22000 + 15000*(difficulty-50)/100) property = 22000 + 15000*(difficulty-50)/100;
  	if(property > limit_int) property = limit_int;
  
	tufei->set("neili", property);
	tufei->set("max_neili", property);
	tufei->set("jingli", property);
	tufei->set("max_jingli", property);
	tufei->set("jiali", property/20);		
	tufei->set("max_qi",property);
	tufei->set("eff_qi",property);	
	tufei->set("qi",property);    
	
	tufei->set("max_jing",property);
	tufei->set("eff_jing",property);
	tufei->set("jing",property);    
		
	tufei->wield_weapon();
	tufei->set("chat_chance_combat", tufeilevel*10>100?100:tufeilevel*10);
	tufei->set("intask",intask);	
    tufei->jiaofei_move(this_object());	     
}
//每个level产生 level*2+random(level*2)的一般土匪
//产生3*difficulty/100个强力土匪
//土匪的技能和level相关。

void setup_npc()
{
	int number = level*2+random(level);
	int tufeilevel = 1;
	object tufei;
	object first_tufei;
	
    int difficulty = JIAOFEI_D->getdifficulty();
	number = number*difficulty/100;
    number = number -2;
	if(number < 1) number = 1;
		
	for(int i=0;i<number;i++)
	{	
	    
		tufeilevel = level + (random(2)>0?1:-1)*random(3);
		tufeilevel = tufeilevel*difficulty/100;
		
		if(tufeilevel < 1) tufeilevel = 1;
		if(tufeilevel > 9) tufeilevel = 9;
		    
		if(tufeilevel > sizeof(npc_colors)) tufeilevel = sizeof(npc_colors);
        create_npc(tufeilevel,"normal");
   
    }
    if(level > 4)
    {
        //设置少量的强力土匪
        for(int i=0;i<difficulty/50;i++)
        {
            create_npc(difficulty*level*level/50,"strong");
        }
    }				      		    	
}

int test()
{
    printf("%d\r\n",sizeof(all_inventory()));
}

//初始化机关,根据level来设置：
//数量是 1+ random(level/2)
//类型随机
void setup_machine()
{
	object obj;
	int number = 1 + random(level/2);
	int machinelevel = 0;
	
    int difficulty = JIAOFEI_D->getdifficulty();
	number = number*difficulty/100;
	if (difficulty>150)
	{
		number += 3;
	}
	else
	{
		number += 1;
	}
	if(number < 1) number = 1;
	    		
	machines = allocate(number);
	for(int i=0;i<number;i++)
	{		
		obj = new(machine_types[random(sizeof(machine_types))]);
		if(objectp(obj))
		{
			machines[i] = obj;
			obj->move(this_object());
        	machinelevel = level*difficulty/100;
        	if(machinelevel < 1) machinelevel = 1;		
        	if(machinelevel > 9) machinelevel = 9;		
			obj->set("level",machinelevel);				
			if(intask)
			{					
				obj->start();
			}
		}
	}
}

//关闭所有机关
void stop_machine()
{
	for(int i=0;i<sizeof(machines);i++)
	{
		if(objectp(machines[i]))
		{
			machines[i]->stop();
		}
	}
}



void init()
{

	add_action("do_break_door","break");
	add_action("do_open_door","open");
	add_action("do_close_machine","close");
	add_action("do_kill","kill");
	add_action("do_kill","fight");
	add_action("do_kill","hit");
	add_action("do_killall","killall");
	add_action("do_killall","hitall");	
	add_action("do_exert","exert");
	
	if(islastroom)
	{
		add_action("do_get_key","get");		
		add_action("do_push_shizi","push");		
	}
	add_action("do_look","look");
	this_player()->listen_to_die(this_object());
}

//定时主动叫杀，以免有玩家闲着。
int kill_player()
{    
    object* allob,*alltufei,*allplayer;
    int index = 0;
    
    if(intask)
    {    
        //主动叫杀
       	allob = all_inventory(this_object());
       	alltufei = filter_array(allob,"filter_tufei");  
       	if(sizeof(alltufei) > 0) 
        {
           	allplayer = filter_array(allob,"filter_enemy");  
    
           	for(int i=0;i<sizeof(allplayer);i++)
           	{
                if(sizeof(allplayer[i]->query_enemy()) < 5)
                {
                    index = random(sizeof(alltufei));
                    tell_object(allplayer[i],alltufei[index]->query("name")+"恶狠狠的向你扑来！\r\n");
              	    alltufei[index]->kill_ob(allplayer[i]);
                }
           	}
        }
    	remove_call_out("kill_player");
    	call_out("kill_player",8+random(5));
    }    
}
//奸细可以开门
int do_open_door(string arg)
{
	object* allob;

	object me = this_player();
	
	object key;
	if(arg == "gate")
	{
	    if(intask != 1)
    	{	    
    	    return 0;    
    	}	
		if(islastroom && intask && !present("tufei",this_object()) && !present("fubangzhu",this_object()))
		{
			//开启最后一个通往宝库的大门
			key = present("yao shi",me);
			if(objectp(key) && key->query("jiaofei/key") == 1)
			{
				message("vision",sprintf("%s把钥匙插入锁孔，缓缓转动着。大门发出轰轰的声音，似乎有机关在转动。\r\n",me->query("name")),this_object());
				message("vision",sprintf("%s发现钥匙被锁在锁孔里，再也拔不出来了。\r\n",me->query("name")),this_object());				
				destruct(key);				
				JIAOFEI_D->opendoor();
			}
			return 1;
		}
		if(doorstr == 0)
		{
			write("门已经开了！\r\n");
		}
	  else if(me->query("jiaofei/tmz/xinren") > 0)
		{
			if(me->query("jiaofei/tmz/xinren") < level * 100)
			{
				write("守卫漠然的对你说：你的级别不够，无权打开这扇门。\r\n");
			}
			else
			{
				if(find_same_ip(me) == 1)
				{
					write("守卫对你冷哼一声，别以为你换件衣服我就不认得你！上次就是你潜入这里，偷偷开的门！\n");
				    me->delete("jiaofei/tmz/xinren");
				}
				else
				{
					message("vision",sprintf("%s转动机关，打开了沉重的石门！\r\n",me->query("name")),this_object());	
					setdoorstr(0);
					me->add("jiaofei/tmz/xinren",-level * 100);						
					if(me->query("jiaofei/tmz/xinren") <= 0)
					{
						write("你听到有人大喊：奸细！他是奸细！你的身份暴露了！\r\n");
						me->delete("jiaofei/tmz/xinren");
					}
					else
					{
						write("你发现有人向你投来怀疑的目光。小心一点吧。\r\n");
						//如果在场土匪多，还是可能暴露。所以一个土匪不杀就冲上去有危险
						allob = all_inventory(this_object());
						allob = filter_array(allob,"filter_tufei");  
						if((random(sizeof(allob)) > 5 || present("durer npc",this_object())) && random(me->query("kar")) < 5)
						{
							message("vision","土匪突然大声聒噪起来：这小子是奸细！关门，赶快关门！\n",this_object());
							me->delete("jiaofei/tmz/xinren");
							restoredoorstr();
						}

					}			
					set("sameip/"+query_ip_number(me),me->query("id"));
					write("你的武林声望提高了，更加受人尊重！\n");	
					me->add("repute",level * 100);
					me->add("shen",level * 200);
				}
		    
			}
		}
		else
		{
			write("大门上设有机关，你试了又试，就是打不开。\r\n");
		}
		return 1;
	}
	return 0;
}
//震开门，门的每一点强度需要消耗100点内力
//非任务状态不得震门
int do_break_door(string arg)
{
	int neili = 0;
	int busy = 0;
	object ob;
	object* allob;
  object me=this_player();
  
	

	if(!intask)
		{
			write("守卫厉声喝道：汝欲何为！？\n");
	    return 1;
		}
    if( me->query("jiaofei/tmz/xinren") > 0)
        {
			write("守卫疑惑的看着你：这位同志，好好的你为什么要破坏我们自己的门哪？\n");
	        return 1;            
        }
	//arg是使用的内力点数
	if (!arg || arg == "")
	{
	   write("指令格式：break 要使用的内力点数\n");
	   return 1;
	}

	neili = to_int(arg);
	if(neili < 100)
	{
		write("至少要使用100点内力。\r\n");
		return 1;
	}

	if(doorstr <= 0)
	{
		write("门已经被震开了。\r\n");
		return 1;
	}

	if (me->query("neili") < neili)
	{
		write("你的内力不够\r\n");
		return 1;
	}

	if(me->is_busy())
	{
		write("你正忙着呢！\r\n");
		return 1;		
	}
	
	if(islastroom)
	{
		write("这个石门至少有万钧之重，不可能震开的\r\n");
		return 1;
	}

	if(objectp(present("tufei",this_object())) || objectp(present("fubangzhu",this_object())))
	{
		write("土匪恶狠狠的冲过来，挡在大门前面！看来不杀掉他是过不去的。\r\n");
		return 1;
	}
	doorstr -= neili/100;
	me->add("neili",-neili);
	message("vision",sprintf("%s气沉丹田，运起内力，大喝一声向大门重重拍下。只见尘土飞扬，石屑横射！\r\n",me->query("name")),this_object());	  
 
  
  busy = neili/300;
  if(busy > 5)
  {
  	busy = 5 + busy/10;
  }
  if(busy < 1)
    {
        busy = 1;
    }
	me->add_busy(busy);
	
	if(doorstr <= 0)
	{
		doorstr = 0;
        message("vision",sprintf(HIR"石门被%s震开了！\r\n"NOR,me->query("name")),this_object());	  	 
    }
        if (!me->query("special_skill/lucky"))
        {
        	//产生一些随机效果，有lucky特技的免疫
        	switch(random(50))
        	{
        		case 0:
        		case 1:
        		case 2:
        		case 3:		
        		case 4:
        		case 5:
        		case 6:
        	    case 7:
        			//掉血
                    message("vision",sprintf(HIR"一块巨石轰隆一声掉了下来，%s闪避不及，吃了点亏。\r\n"NOR,me->query("name")),this_object());	  	         			
        			me->receive_damage("qi",random(level*300),"石门砸");
                    COMBAT_D->report_status(me);
        			break;
        		case 8:
        		case 9:
        		case 10:
                case 11:        		    
                    message("vision",sprintf(HIR"一块巨石轰隆一声掉了下来，%s闪避不及，吃了大亏。\r\n"NOR,me->query("name")),this_object());	  	         			            		
        			me->receive_damage("qi",random(level*300),"石门砸");
        			me->receive_wound("qi",random(level*300),"石门砸");
                    COMBAT_D->report_status(me);
        			break;
        		case 12:
        		case 13:
                case 14:        		    
        			//武器断掉
        			ob = me->query_temp("apply/weapon");
        			if(objectp(ob))
        			{
                        message("vision",sprintf("一块巨石轰隆一声掉了下来，%s急忙用%s格挡，%s顿时断裂。\n",me->query("name"),ob->query("name"),ob->query("name")),this_object()); 	    
        			    ob->unequip();
        			    destruct(ob);
        			}
        			else
        			{
        			    ob = me->query_temp("apply/secondary_weapon");
            			if(objectp(ob))
            			{
                            message("vision",sprintf("一块巨石轰隆一声掉了下来，%s急忙用%s格挡，%s顿时断裂。\n",me->query("name"),ob->query("name"),ob->query("name")),this_object()); 	                			                			    
            			    ob->unequip();
            			    destruct(ob);
            			}			    
        			}
        			break;
        		case 15:
        		case 16:
        			//盔甲破碎
        			break;
        		case 17:
        		case 18:
        			//触发机关攻击
        		//	break;
        		case 19:
        			//晕倒
                    message("vision",sprintf("大门轰隆一声倒了下来，%s闪避不及，当场昏死了过去\n",me->query("name")),this_object()); 	            			        			
        			me->unconcious();
        			break;
        	}	  
    	}
    	
	return 1;
}
//关闭机关，只有奸细可以。
int do_close_machine(string arg)
{
	object me,obj;
	object* allob;
	
	if(!arg || arg == "") return 0;
	me = this_player();
	
	if(intask != 1)
	{	    
	    return 0;    
	}	
	allob = all_inventory(this_object());
	for(int i =0;i<sizeof(allob);i++)
	{
	    obj = allob[i];
    	if(objectp(obj) && member_array(obj,machines) != -1 && 
    	    member_array(arg,obj->parse_command_id_list()) != -1)
    	{
    		if(me->query("jiaofei/tmz/xinren") > 0)
    		{
    		    if(obj->isstopped() == 1)
    		    {
    		        //已经被关闭了
    		        continue;
    		    }
    		    
    			if(me->query("jiaofei/tmz/xinren") >= level * 100)
    			{
					if(find_same_ip(me) == 1)
					{
						write("守卫对你冷哼一声，别以为你换件衣服我就不认得你！上次就是你潜入这里，偷偷关了我们的机关！\n");
						me->delete("jiaofei/tmz/xinren");
					}
					else
					{
						obj->stop(me);
						message("vision",me->query("name")+"关闭了"+obj->query("name")+"\n",this_object());								
						
						me->add("jiaofei/tmz/xinren",-level * 100);						
						if(me->query("jiaofei/tmz/xinren") <= 0)
						{
							write("你听到有人大喊：奸细！他是奸细！你的身份暴露了！\r\n");
							me->delete("jiaofei/tmz/xinren");
						}
						else
						{
							write("你发现有人向你投来怀疑的目光。小心一点吧。\r\n");
							//可以加上更多判断，如果在场土匪多，还是有可能暴露。
						}
						write("你的武林声望提高了，更加受人尊重！\n");	
						me->add("repute",level * 100);
						me->add("shen",level * 200);    			    
						set("sameip/"+query_ip_number(me),me->query("id"));
					}
    				
    			}	
    			else
    			{
    				write("你还不懂得如何关闭这个机关的秘诀！\r\n");
    			}			
    		}
    		else
    		{
    				write("你不懂得如何操作这个机关。\r\n");
    		}
    		return 1;
    	}	    
	}

	return 0;
}

//寻找所有敌人
int filter_enemy(object ob)
{
	if(userp(ob) && present(ob,this_object()))		
	{		
		if(ob->query("jiaofei/tmz/xinren") > 0)
			return 0;
		else
		{			
			return 1;		
		}
	}
	return 0;
}

int filter_tufei(object ob)
{
	if(!userp(ob) && (ob->query("id") == "tufei" || ob->query("id") == "durer npc"))		
	{
		return 1;
	}
	return 0;
}

//当有玩家下达kill,hit,fight指令时调用。如果任务尚未开始，简单的交给土匪去应战，如果任务已经开始，最多只能同时攻击5个土匪。
int do_kill(string arg)
{
	object* allob;
	object* alltufei;
	
	int n;
	
	object enemy;
  object me=this_player();
  	
	int tufeicount = 0;
	
	if(JIAOFEI_D->istaskstart() != 1)
	{
		return 0;
	}
	if(!arg || (strsrch(arg,"tufei") == -1 && strsrch(arg,"fubangzhu") == -1 && strsrch(arg,"durer npc") == -1)) return 0;
		
    if(me->query("jiaofei/tmz/xinren") > 0)
    {        
        command("ah");
        command("say 原来你是奸细！枉我把你当自己兄弟看！！");
        me->delete("jiaofei/tmz/xinren");        
    }
		
	if(intask)
	{				  
    	if(sizeof(me->query_enemy()) > 5)
		{
			//一次只能最多杀5个土匪
			write("你已经穷于应付了，让别人来！\r\n");
		  return 1;
		}			
	}	
	return 0;
}

int do_killall(string arg)
{
    write("你冷笑一声，正要对周围的人痛下杀手，结果一个土匪把一个婴儿举在身前，叫你犹豫不决。\n");
    return 1;
}

int do_exert(string arg)
{
    if(arg == "roar")
    {
        write("你正要施展内力猛吼，猛然发现对面的土匪抬出一面大鼓，赶紧收回内力作罢。\n");
        return 1;
    }
    else if(arg == "bhcs")
    {
        write("你正要施展碧海潮生的奇功，猛然发现对面的土匪抬出一面大鼓，赶紧收回内力作罢。\n");
        return 1;
    }
    return 0;
}

int do_push_shizi(string arg)
{    
    if(arg != "shizi" || !intask) return 0;
    
    message("vision",sprintf("%s用力推动狮子，在狮子的基座下发现一个盒子。\r\n",this_player()->query("name")),this_object());
    if(haskey)
    {
        message("vision",sprintf("%s打开盒子，里面发现一把钥匙(key)。\r\n",this_player()->query("name")),this_object());        
    }
    else
    {
        message("vision",sprintf("%s打开盒子，里面空无一物。\r\n",this_player()->query("name")),this_object());                
    }
    return 1;
}

//第一个获得key的人获得额外奖励
int do_get_key(string arg)
{
	int exp,pot;
	object key;
	int difficulty = JIAOFEI_D->getdifficulty();    			
	
	object me = this_player();
	if(arg != "key") return 0;
	
	if(intask && islastroom && haskey)
	{
		if(present("tufei",this_object()) || present("fubangzhu",this_object()))
		{
			write("土匪恶狠狠的扑过来，阻止了你去拿钥匙。\r\n");
			return 1;
		}
		haskey = 0;
		
	    message("vision",sprintf("%s从盒子里取出一枚钥匙！看起来可以打开面前的大门！\r\n",this_player()->query("name")),this_object());			
		if(JIAOFEI_D->addkey() == 1)
		{
			exp = level * 1000 * (random(10)+1);
			pot = level * 100 * (random(10)+1);
            exp = exp * difficulty /100;
            pot = pot * difficulty /100;
            
			me->add("combat_exp",exp);
			me->add("potential",pot);
			JIAOFEI_D->announce(sprintf(HIR"%s第一个获得大门钥匙，获得了%d点经验和%d点潜能奖励！",me->query("name"),exp,pot), "bd");
	  	}      			
		key = new(__DIR__"obj/key");
		if(!key->move(me))//以免玩家拿不动
		{
			key->move(this_object());
		}
	}
	else
	{
		write("你要拿什么？\r\n");
	}
	return 1;
}

//查看各种物品的函数，比如look gate
int do_look(string arg)
{
	if(arg == "gate")
		{
			write("一扇无比坚固的大门，你可以试着open它或者break它。\r\n");			
			return 1;
		}
	return 0;
}

//任务开始时调用。用来生成新的土匪，调用机关的初始化函数，回复门的强度。
void start_task()
{
    int difficulty = JIAOFEI_D->getdifficulty();    
    
    if(difficulty > 100 && JIAOFEI_D->no_die() != 1)
    {
        //100难度以上是真死
        delete("no_die");
    }
    else
    {
        set("no_die",1);
    }
	set("no_clean_up",1);
	set("no_reset",1);
	intask = 1;	
	haskey = 1;	

	task_clean_up();
	
	setup_npc();	
	
	setup_machine();
	
	
	//恢复门的强度
	doorstr = backupdoorstr;
	
    
	doorstr = (doorstr+2)*difficulty/100;
	if(doorstr < 10) doorstr = 10;	
	
	remove_call_out("kill_player");
	call_out("kill_player",8+random(5));
	
}

//任务停止时调用。
void stop_task()
{
	intask = 0;
	set("no_die",1);
	delete("no_clean_up");
	delete("no_reset");

	stop_machine();
	//清除同ip的记录
	delete("sameip");
}

//检查玩家是否可以进入下一个房间。检查条件包括：
//是否有门
//是否有土匪
//非任务状态下，非奸细不能入内。
int valid_leave(object me, string dir)
{	
	if(dir != nextdirect || wizardp(me)) 
	{
	        this_player()->remove_listen_to_die(this_object());
	        return ::valid_leave(me, dir);
	}

	if(islastroom)
	{
//		printf("%d/%d\r\n",JIAOFEI_D->querysortnumber("id"),JIAOFEI_D->querykillernumber());

		if(undefinedp(me->query_temp("jiaofei/score")) || JIAOFEI_D->querysortnumber(me->query("id")) < 0)
		{
			return notify_fail("你寸功未立，也想进宝库吗？\r\n");
		}
		if(JIAOFEI_D->querykillernumber() <= 0)
		{
			//bug，正常代码执行到这里，不可能<= 0，不过为了避免下面出现除0错，还是判断一下。
			return notify_fail("一个恶魔从天而降，抢走了所有的宝物！赶快告诉天神吧！\r\n");
		}		
		//杀人前40%才有资格进宝库。cut by yhzzyahoo
		if(100*JIAOFEI_D->querysortnumber(me->query("id"))/JIAOFEI_D->querykillernumber() > 40)
		{
			return notify_fail("你在剿匪中表现一般，进入宝库，恐怕别人不服啊。\r\n");
		}
		else
		{
		    me->set_temp("jiaofei/hero",1);
  		    me->set_temp("jiaofei/difficulty",JIAOFEI_D->getdifficulty());
		}
	}
	
	if(doorstr > 0 )
	{		
			if(me->query("jiaofei/tmz/xinren") > 0)
			{
                //修改为只要有信任度就可以畅行无阻
				//但任务开始后不行
			    if(islastroom)
			    {
			        return notify_fail("宝库乃是本帮禁地，任何人不得入内！\n");
			    }
				if(intask == 1)
				{
					return notify_fail("朝廷正在攻山，所有人必须坚守，不得随意走动！\n");
				}
			}
			else
			{
				return notify_fail("大门紧紧的锁着.\n");
			}
	}
	
    message("vision",sprintf("%s大踏步的通过大门向%s走去。\r\n",me->query("name"),default_dirs(nextdirect)),this_object());			    	
    
    this_player()->remove_listen_to_die(this_object());	
    
    //如果在场还有土匪，应该攻击一次
    if(present("tufei",this_object()) || present("fubangzhu",this_object()))
    {
        for(int i=0;i<sizeof(machines);i++)
        {
            if(objectp(machines[i]))
            {
                machines[i]->attack_target(me);
            }
        }
    }
	return ::valid_leave(me, dir);

}


//当有玩家在此死亡时调用
int die_notify(object victim)
{
    if(!objectp(victim) || environment(victim) != this_object()) return 0;
    if(intask)
    {
        if(victim->query_temp("jiaofei/score") > 0)
        {
            JIAOFEI_D->stat_user_score_reward(victim->query("id"),-(victim->query_temp("jiaofei/score") - victim->query_temp("jiaofei/score")/2));
            victim->set_temp("jiaofei/score",victim->query_temp("jiaofei/score")/2);            
        }
        tell_object(victim,BLU"出师未捷身先死，长使英雄泪满襟。你的功勋减半了！\n"NOR);
        victim->remove_listen_to_die(this_object());
    }
}

void dump()
{
    printf("===== room dump =====\n");
    printf("doorstr:%d,backupdoorstr:%d,nextdirect:%s,islastroom:%d,haskey:%d,level:%d,intask:%d\n\n",
    doorstr,backupdoorstr,nextdirect,islastroom,haskey,level,intask);
}
string default_dirs(string dir) 
{   
	  string str;    
	  switch (dir)
	  {
	    case "north":        str="北方";break;
	    case "south":        str="南方";break;
	    case "east":         str="东方";break;
	    case "west":         str="西方";break;
	    case "northup":      str="北边";break;
	    case "southup":      str="南边";break;
	    case "eastup":       str="东边";break;
	    case "westup":       str="西边";break;
	    case "northdown":    str="北边";break;
	    case "southdown":    str="南边";break;
	    case "eastdown":     str="东边";break;
	    case "westdown":     str="西边";break;
	    case "northeast":    str="东北";break;
	    case "northwest":    str="西北";break;
	    case "southeast":    str="东南";break;
	    case "southwest":    str="西南";break;
	    case "up":           str="上方";break;
	    case "down":         str="下方";break;
	    case "enter":        str="里边";break;
	    case "out":          str="外边";break;
	    default:             str="";break;
    }
    return str;
}  

int find_same_ip(object me)
{
	string ip = query_ip_number(me);
	if(query("sameip/"+ip) != me->query("id")) return 1;
	return 0;
}
