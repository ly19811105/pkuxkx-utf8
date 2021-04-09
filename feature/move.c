// move.c
// 每个房间除了自定义设定可以容纳的物品数再设一个上限，对应此次卡顿的源头。Zine 2014/5/26
#pragma optimize

#include <dbase.h>
#include <ansi.h>
#include <room.h>
#include <color.h>

#define TotalLimit 10000 //一个容器能容纳的总items,因为玩家可携带400件，所以这个值不能太小。
#define CurrentLayerLimit 1000//容器第一层能容纳的items数，即sizeof(all_inventory())+1
#define PlayerHoldLimit 400//玩家可携带的items数。
nosave int weight = 0;
nosave int encumb = 0, max_encumb = 0;

nomask int query_encumbrance() { return encumb; }
nomask int over_encumbranced() { return encumb > max_encumb; }

nomask int query_max_encumbrance() { return max_encumb; }
nomask void set_max_encumbrance(int e) { max_encumb = e; }
nomask void add_encumbrance(int w)
{
	encumb += w;
	if( encumb < 0 )
		log_file("move.bug", sprintf("%O encumbrance underflow.\n", this_object()));
	if( encumb > max_encumb ) this_object()->over_encumbrance();
	if( environment() ) environment()->add_encumbrance(w);
}

void over_encumbrance()
{
	if( !interactive(this_object()) ) return;
	tell_object(this_object(), "你的负荷过重了！\n");
}

nomask int query_weight() { return weight; }
nomask void set_weight(int w)
{
	if( !environment() ) {
		weight = w;
		return;
	}
	if( w!=weight ) environment()->add_encumbrance( w - weight );
	weight = w;
}


// This is the "current" weight of an object, which is used on weight
// checking in move().
nomask int weight() { return weight + encumb; }

string ride_suffix (object me)
{
	string ridemsg = 0;
	object ridee = 0;
	
	ridee = me->ride();
	if (ridee)
		ridemsg = ridee->query("ride/msg")+"在"+ridee->name()+"上";
	return ridemsg;
}

int dest_no_get_object(object obj,object room)
{
	if(objectp(obj) && objectp(room))
	{
		tell_room(room,sprintf("%s落地不久，慢慢地变得透明，最终消失得无影无踪，仿佛根本不曾存在过一样。\n",obj->query("name")));
		destruct(obj);
	}
	return 1;
}
string show_objects()
{
	object *inv,*inv1;
	int *count,i,j;
	string str="";
	inv = all_inventory(environment());
	for (i = 0; i < sizeof(inv); i++) 
	{
		if(!this_object()->visible(inv[i])) continue;                
			if (!arrayp(inv1))
			{
				inv1=({inv[i]});
				count=({1});
			}
			else
			{
				for (j = 0; j < sizeof(inv1); j++)
				if  ( (base_name(inv[i])==base_name(inv1[j])) && (inv[i]->query("name") == inv1[j]->query("name")) )
				break;
				if (j == sizeof(inv1) || userp(inv[i]))
				{
					inv1+=({inv[i]});
					count+=({1});
				}
				else
				count[j]+=1;
			}                
	}
	for(i=0; i<sizeof(inv1); i++) 
	{
		// if( inv1[i]==this_player() ) continue;
        if( inv1[i]==this_object() ) continue;
		if( !userp(inv1[i]) && inv1[i]->query("no_show") ) continue;
		if( !this_object()->visible(inv1[i]) ) continue;
		if(count[i]==1)
		if (this_object()->query("position") == "zmuduser")
		str += "    "+inv1[i]->short()+"\n";
		else
		str += sprintf("<a target=nothing href=\"../Command/look %s\">%s</a><br>",
		inv1[i]->query("id"), inv1[i]->short());
		else
		if (this_object()->query("position") == "zmuduser")
		str +="    "+chinese_number(count[i]) +"" + inv1[i]->query("unit") +""+ inv1[i]->short()+"\n";
		else
		str +="    "+chinese_number(count[i]) +"" + inv1[i]->query("unit") +""+ sprintf("<a target=nothing href=\"../Command/look %s\">%s</a><br>",
		inv1[i]->query("id"), inv1[i]->short());
	}
	return str;
}
void RecursiveCalculate(object ob,object env,int flag)
{
	if (env)
	{
		if (flag<0)
		{
			env->add_temp("current_item_num",-1);
			if(env->query_temp("current_item_num") < 0) env->set_temp("current_item_num",0);
			while (objectp(env))
			{
				env->add_temp("item_num",ob->query_temp("item_num")>=1?-(ob->query_temp("item_num")+1):-1);
				if(env->query_temp("item_num") < 0) env->set_temp("item_num",0);
				env=environment(env);
			}
		}
		if (flag>0)
		{
			env->add_temp("current_item_num",1);
			if(env->query_temp("current_item_num") < 0) env->set_temp("current_item_num",0);
			while (objectp(env))
			{
				env->add_temp("item_num",ob->query_temp("item_num")>=1?(ob->query_temp("item_num")+1):1);
				if(env->query_temp("item_num") < 0) env->set_temp("item_num",0);
				env=environment(env);
			}
		}
	}
}
void pre_destruct()
{
	object env=environment();
	RecursiveCalculate(this_object(),env,-1);
}
varargs int move(mixed dest, int silently)
{
	object ob, from, env;
	object *inv;
	string str,*dirs;
	string exit;
	int i, depth;
	mapping exits;
	object *inv1;
	int *count;
	int j,iexits;
    object* contain_items;
	int contain_number=0,CurContNum;

	// If we are equipped, unequip first.
	if( query("equipped") && !this_object()->unequip() )
		return notify_fail("你没有办法取下这样东西。\n");
	
	// Find the destination ob for moving.
	if( objectp(dest) )
		ob = dest;
	else if( stringp(dest) ) {
		call_other(dest, "???");
		ob = load_object(dest);
		if(!ob) return notify_fail("move: destination unavailable.\n");
	} else
		return notify_fail(sprintf("move: invalid destination %O.\n", dest));
	
	// Check if the destination ob can hold this object.
	// Beforce checking it, we check if the destination is environment of
	// this_object() (or environment of its environment). If it is, then
	// this could be like get something from a bag carried by the player.
	// Since the player can carry the bag, we assume he can carry the this
	// object in the bag and encumbrance checking is unessessary.
	env = this_object();
	from = environment(env);
	while(env = environment(env)) if( env==ob ) break;
	if( !env && (int)ob->query_encumbrance() + weight()
		> (int)ob->query_max_encumbrance() ) {
		if( ob==this_player() )
			return notify_fail( this_object()->name() + "对你而言太重了。\n");
		else
			return notify_fail( this_object()->name() + "对" + ob->name() + "而言太重了。\n");
	}
	
	//icer added to limit maximum number of objects one player can hold
	if ( living(ob) && (!ob->query("container")) )  //user or npc，if want to hold more things,just set container = 1
	{
		if (ob->query_temp("item_num") >= PlayerHoldLimit)
		{
			if (ob == this_player())
			return notify_fail("你身上的物品数量已经到了极限，拿不了更多的东西了。\n");
			else
			return notify_fail(ob->name() + "身上的物品数量已经到了极限，拿不了更多的东西了。\n");
		}
	}

    env = ob;
    while(environment(env))
    {
        if (objectp(env) && userp(env)) break;
        env = environment(env);
    }
    
    if (!userp(this_object()) )//will check all the containers instead of only rooms to avoid bug. Zine
    {
        /*contain_items=filter_array(all_inventory(env), (: !userp($1) :) );
        reset_eval_cost();
        for (i=0;i<sizeof(contain_items);i++)
        {
            contain_number += 1+sizeof(deep_inventory(contain_items[i]));
        }*/
		//contain_number has been calculated at every single time when MOVE function is used, the calculation above is thus no longer required. Zine
		contain_number=env->query_temp("item_num");
		CurContNum=env->query_temp("current_item_num");
        if ((contain_number+this_object()->query_temp("item_num")+env->query("player_num") > env->query("max_contain_items")&&env->query("max_contain_items"))
		||contain_number+this_object()->query_temp("item_num")>TotalLimit
		||CurContNum>CurrentLayerLimit)
        {
            if (this_object()->is_character())
            {
                //this_object()->move(MAP_D->random_place());
                tell_room(env, "前面人太多走不过去了!\n");
                return 0;
            }
            else
            {
                return notify_fail(env->query("short")+"已经放不下更多东西了!\n");
            }
        }
    }
	if(userp(this_object()) && (time() - query("killer/time") < 15*60) && ( ob->query("no_fight") || ob->query("is_xinfang")))
	{
		return notify_fail("人在江湖，杀了人岂能一躲了之?\n");
	}
	// Move the object and update encumbrance
	if( environment() )
	{
		environment()->add_encumbrance( - weight());
		RecursiveCalculate(this_object(),environment(),-1);
		if(userp(this_object()))
		{
			environment()->add("player_num",-1);
			if(environment()->query("player_num") < 0) environment()->set("player_num",0);
		}
	}
	move_object(ob);
	ob->add_encumbrance(weight());
	if( !this_object() ) return 0;
	if(userp(this_object()))
	{
		ob->add("player_num",1);
	}
	RecursiveCalculate(this_object(),ob,1);
	// If we are players, try look where we are.
	if( interactive(this_object())		// are we linkdead?
		&&	living(this_object())			// are we still concious?
		&&	!silently ) {
		if( query("env/brief")|| query("env/brief")== "YES" )
		{
			str = environment()->query("short") + "\n";
         if (query("env/brief") != "YES" && query("env/brief") > 1)
                                   "/cmds/std/look"->realtime_map(this_object(),environment(this_object())); // brief 2帮助机器人实现遍历，realtime_map帮助定位 去掉 by Zine@pkuxkx 2013/4/15对活人影响大，恢复
			if (query("env/brief")!= "YES" && query("env/brief") > 1)
			{
		
				if( mapp(exits = environment()->query("exits")) ) 
				{
					dirs = keys(exits);
					for(i=0; i<sizeof(dirs); i++)
						if( (int)environment()->query_door(dirs[i], "status") & DOOR_CLOSED )
							dirs[i] = 0;
						dirs -= ({ 0 });
						/*if(random(10) == 0 && sizeof(dirs) > 0)
						{
							dirs -= ({dirs[random(sizeof(dirs))]});
						}*/			
		
						if( sizeof(dirs)==0 )
							str += "    这里没有任何明显的出路。\n";
						else if( sizeof(dirs)==1 )
							if (this_object()->query("position") == "zmuduser")
								str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
							else
								str += "    这里唯一的出口是 <a target=nothing href=\"../Command/go "  + dirs[0] + "\"" + WEBRED + dirs[0]  + "</a>" + WEBNOR + "。";
						else
							if (this_object()->query("position") == "zmuduser")
								str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
								implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
							else{
								str += "    这里明显的出口是 ";
	                   					for (iexits = 0; iexits < sizeof(dirs) - 2; iexits++)
	                  		 				str += sprintf("<a target=nothing href=\"../Command/go %s\">%s</a>、", dirs[iexits], dirs[iexits]);
	          							str += sprintf("<a target=nothing href=\"../Command/go %s\">%s</a>和", dirs[sizeof(dirs) - 2], dirs[sizeof(dirs) - 2]);
	          							str += sprintf("<a target=nothing href=\"../Command/go %s\">%s</a>", dirs[sizeof(dirs) - 1], dirs[sizeof(dirs) - 1]);
	          						}
				}
			}
			str+=show_objects();
			if (this_object()->query("position") == "zmuduser")
				tell_object(this_object(), str);
			else         
				printf(str);  

                        
/*
				if (this_object()->query("position") == "zmuduser")
					tell_object(this_object(), str);
				else         
				{
					"/cmds/std/look.c"->realtime_map(this_object(),environment());
		          		str += "\n";
				        printf(str);
				}*/
		
		}
		else
		    {		        
			if( this_object()->query("position") == "zmuduser" ) 
			{
				command("look +frommove");
			}
			else
			{
				command("look");
			}
			
		}
	}
	"/cmds/std/look"->Examine_Surroundings(this_object());
	if( this_object()->is_character() && (depth = (int)environment()->query_temp("depth")) ) {
		this_object()->start_busy(depth);
		message_vision("$N一不小心跌进了陷坑里，连忙手忙脚乱地往上爬。\n", this_object());
		environment()->add_temp("depth", -1);
	}
	if ((this_object()->query("is_monitored") || file_name(this_object())[0..2]=="/u/") && userp(ob) && (!this_object()->query_temp("no_monitor")))
		MONITOR_D->report_system_object_msg (ob,"得到了"+
		this_object()->query("name")
		+"("+file_name(this_object())+")。");
        if(file_name(this_object())[0..11]!="/u/canexpand"&&file_name(this_object())[0..2]=="/u/" && userp(ob)&&!wizardp(ob)) 
		{
			MONITOR_D->report_system_object_msg(ob,"刚的到的"
				+this_object()->query("name",1)+"不翼而飞了！\n");
			destruct(this_object());
			//jason add, return immediately, to avoid bug
			return 1;
//                        return notify_fail("玩家不能使用超级物件！\n");
		}
		
	//icer added to avoid the bug of cloning on reboot
	if (objectp(ob) && objectp(from))
	if (ob->is_character() || from->is_character())
	{
		if (ob->is_character()) 
			if (!(interactive(ob) && living(ob)))
				ob->save();
		if (from->is_character())
			if (!(interactive(from) && living(from)))
				from->save();
	}
	//jason add to destruct some no_get object, if they are moved to room.
	//to save resource. for example, the robber's weapon
	if (objectp(ob) && !this_object()->is_character() && ob->isroom() == 1 && this_object()->query("startroom") != base_name(ob))
	{
		if(this_object()->query("no_drop_to_room") != 0)
		{
			call_out("dest_no_get_object",1,this_object(),ob);
		}
	}
	return 1;
}

void remove(string euid)
{
	object default_ob;
	
	if( !previous_object()
		||	base_name(previous_object()) != SIMUL_EFUN_OB )
		error("move: remove() can only be called by destruct() simul efun.\n");
	
	if( userp(this_object()) && euid!=ROOT_UID ) {
		log_file("destruct", sprintf("%s attempt to destruct user object %s (%s)\n",
			euid, this_object()->query("id"), ctime(time())));
		error("你(" + euid + ")不能摧毁其他的使用者。\n");
	} else if( this_object()->query("equipped")) {
		if(	!this_object()->unequip() )
			log_file("destruct", sprintf("Failed to unequip %s when destructed.\n",file_name(this_object())));
	}
	
	// We only care about our own weight here, since remove() is called once
	// on each destruct(), so our inventory (encumbrance) will be counted as
	// well.
	if( environment() )	environment()->add_encumbrance( - weight );
	if( default_ob = this_object()->query_default_object() )
		default_ob->add("no_clean_up", -1);
}

int move_or_destruct( object dest )
{
	if( userp(this_object()) ) {
		tell_object(this_object(), "一阵时空的扭曲将你传送到另一个地方....\n");
		move(VOID_OB);
	}
}

object ride()
{
	object me = this_object();
	string ridemsg = "";
	object ridee;
	
/*
	if (ridee = me->query_temp("ridee")) { 
		if ((environment(ridee) != environment(me) &&
			environment(ridee) != me) ||
			(ridee->is_character() && ! living(ridee))) {
			me->set_temp("ridee",0);
			ridee->set_temp("rider",0);
			ridee = 0;
		}
	}
	if (! ridee) {
		me->add_temp("apply/dodge",-me->query_temp("ride/dodge"));
		me->set_temp("ride/dodge",0);
	}
*/
	if (objectp(ridee = me->query_temp("riding")) )
{
		if  (environment(ridee) != environment(me)
			|| (ridee->is_character() && !living(ridee)) )
		{
			me->delete_temp("riding");
			ridee->delete_temp("rider");
			ridee = 0;
		}
}
	else ridee = 0;
	return ridee;
}

