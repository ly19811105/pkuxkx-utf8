//taskd.c
//Made by jason@pkuxkx
//2001.1.3
//last modified 2001/1/16
// Modified by iszt@pkuxkx, 2007-04-16, changed id for random_carrier
//增加门派争胜模式,2010-9-30, jason@pkuxkx
//将地点分配部分移到mapd.c里，进行重构。这部分代码已经被所有任务使用了，不适合继续放在taskd.c里 2011-10-25 jason@pkuxkx

inherit F_DBASE;

#include <ansi.h>
#define MAX_TIMES 20

protected nosave mapping task_list=([]);
protected nosave object *task_ob=({});


void update_task();
void task_finish1();
void task_finish2();
void task_finish3();

object random_room(string,int);
object random_place();
object random_place_ex(object);
object random_carrier();
object random_npc(object);
string place_belong(object);
object* usrs;
int move_to(object,object);
string query_task_list();
void task_done(object,string);
int task_give(object,object,object);
object do_clone(object,object);
void give_reward(object,object);
mixed query_location(string);
mixed query_location_where(string arg);
void pre_destruct();

int family_race_mode = 0; 
int last_family_task_time = 0;
mapping family_task_completed_count = ([]);

void create()
{
	seteuid(getuid());
	set("channel_id",HIW"北大侠客行任务榜"NOR);
	update_task();
}

void pre_destruct()
{
	for(int j=0;j<sizeof(task_ob);j++)
	{
		if(!undefinedp(task_ob[j])&&objectp(task_ob[j]))
		destruct(task_ob[j]);
	}
	task_ob=({});
}

void update_each_task(string task,mapping tmp,string *key)
{
	int num;
	string err;
	object npc,room;
	object ob,where;
    object dum;
	reset_eval_cost();
	err=catch(ob=new(task));
	if(err) {
		log_file("task","cannt new ob:"+task+"\n");
		return;
	}
	for(int kk=0;kk<10;kk++)
	{
	where=random_place();
	if(where==this_object()) continue;
	if((num=member_array(ob->query("task_owner"),key))!=-1)	
	{
		if(!objectp(room=load_object(tmp[key[num]]))) continue;
		if(!objectp(npc=present(key[num],room))) continue;

	}
	
    if(!move_to(ob,where)) {continue;}
	task_list[ob->query("task_owner_cname")+"的"+ob->query("name")]=HIY"(未完成)"NOR;
	task_ob+=({ob});
	break;
	}	
}

void update_task()
{
	string file, *key, *task=({}),file2,npc_s,room_s,*npc_list=({});
	int i = 0;
	int max_complete_count = 0;
	string win_family = "";
	string* familys;
		
	mapping tmp=([]);
	task_list=([]);
	
	if(time()-last_family_task_time > 3600*4)
	{
		family_race_mode = 1;
		family_task_completed_count = ([]);
		last_family_task_time = time();
		CHANNEL_D->do_channel(this_object(), "rw", HIR"本轮侠客榜任务为门派争胜模式，完成任务最多的门派在接下来的四小时内所有主流任务奖励提升两成!掉宝率提高两成。");
	}
	else
	{
		family_race_mode = 0;
	}
		
  CHANNEL_D->do_channel(this_object(), "rw", HIR"开始重新分配侠客榜任务....");
	for(int j=sizeof(task_ob)-1;j>=0;j--)
	{
		if(!undefinedp(task_ob[j])&&objectp(task_ob[j]))
		destruct(task_ob[j]);
	}
	task_ob=({});
	if(!file=read_file("/task/task_list")) return;
	if(!file2=read_file("/task/npc_list")) return;
	task=explode(file,"\n");
	npc_list=explode(file2,"\n");
	for(int j=0;j<sizeof(npc_list);j++)
	{
		
		if(sscanf(npc_list[j],"%s:%s",npc_s,room_s)!=2) continue;
		tmp[npc_s]=room_s;
	}
	key=keys(tmp);
	usrs = users();
	for(i=0;i<sizeof(task);i++)
	{
		call_out("update_each_task",i,task[i],tmp,key);
	}
    call_out("task_finish0",30);
	remove_call_out("task_finish1");
    call_out("task_finish1",1020);//17 mins
}

void task_finish0()
{
		if(family_race_mode == 2)
		{
			family_race_mode = 1;
		}
        CHANNEL_D->do_channel(this_object(), "rw", HIR"侠客榜任务分配完成！");
}

void task_finish1()
{
	CHANNEL_D->do_channel(this_object(), "rw", HIR"侠客榜任务还有三分钟重新分配！");
	remove_call_out("task_finish2");
	call_out("task_finish2",60);
	return;
}

void task_finish2()
{
	CHANNEL_D->do_channel(this_object(), "rw", HIR"侠客榜任务还有二分钟重新分配！");
	remove_call_out("task_finish3");
	call_out("task_finish3",60);
	return;
}

void task_finish3()
{
	string* familys;
	int i;
	string win_family="";
	int max_complete_count=0;
	
	CHANNEL_D->do_channel(this_object(), "rw", HIR"侠客榜任务还有一分钟重新分配！");
	
	//处理上一次门派争胜任务的结果
	if(family_race_mode == 1)
	{
		familys = keys(family_task_completed_count);
		if(arrayp(familys))
		{
			for(i=0;i<sizeof(familys);i++)
			{
				if(family_task_completed_count[familys[i]] > max_complete_count)
				{
					max_complete_count = family_task_completed_count[familys[i]];
					win_family = familys[i];
				}
			}
		}
		if(max_complete_count > 5 && win_family != "")
		{
			CHANNEL_D->do_channel(this_object(), "rw", HIR"本次侠客榜门派争胜的胜利者是:"+win_family+"!!");
			CHANNEL_D->do_channel(this_object(), "rw", HIR+win_family+"所有弟子在接下来四小时内所有主流任务奖励增加两成!!掉宝率提高两成。");
			CHANNEL_D->do_channel(this_object(), "rw", HIR+win_family+"门派威望提高五点。");
			FAMILY_D->set_task_winner_family(win_family);
			FAMILY_D->add_repute(win_family,5);
		}
		else
		{
			FAMILY_D->set_task_winner_family("INVALID");
		}
	}
	family_race_mode = 0;
	
	remove_call_out("update_task");
	call_out("update_task",60);
	return;
}



int move_to(object source,object target)
{
	object *inv,*ls=({});
	mapping ob;
	object npc;
	string *key;
         if(!objectp(source)||!objectp(target)) return 0;
	inv=all_inventory(target);
	ob=target->query("objects");
        if (!target->query("exits"))
                 log_file("task","no exits:" + base_name(target) + ".c(" + target->query("short") + ")\n");

	source->set("no_clean_up",1);

	if(sizeof(ob)>0)
	{
		key=keys(ob);
		for(int i=0;i<sizeof(inv);i++)
		{
			if(member_array(base_name(inv[i]),key)!=-1||
			member_array(base_name(inv[i])+".c",key)!=-1)
			if(living(inv[i])&&
                                function_exists("die",inv[i])=="/feature/damage")
				ls+=({inv[i]});
		}
		
	}
	if(sizeof(ls)<=0) return 0;
	if(source->move(ls[random(sizeof(ls))]))
        {
/******************* 去掉random_npc设置
			npc = random_carrier();
			npc->move(target);
        	if (random(2)==0)
        	{
				npc->set("task_ob",source->query("id"));
				npc->set("no_clean_up",1);
				source->move(npc);
			}
*********************/			
           return 1;
        }
        else {
                 log_file("task","cannot move:random(inv) of " + base_name(target) + ".c(" + target->query("short") + "\n");
                return 0;
        }

}

string query_task_list()
{
	string output="",*key;
	key=keys(task_list);
	for(int i=0;i<sizeof(key);i++)
	{
		output+=sprintf("	%-25s%s\n",key[i],task_list[key[i]]);
	}
	return output;
}

void task_done(object ob,string username)
{
	string *key;
	int num;
	key=keys(task_list);
	if(num=member_array(ob->query("task_owner_cname")+"的"+ob->query("name"),key)!=-1
	&&member_array(ob,task_ob)!=-1) 
	{
		string index=ob->query("task_owner_cname")+"的"+ob->query("name");
		task_list[index]=HIG"(已由" + username + "完成)"NOR;
		task_ob-=({ob});
	}
	
	return;
}

void task_lost(object ob,string username)
{
        string *key;
        int num;
        key=keys(task_list);
        if(num=member_array(ob->query("task_owner_cname")+"的"+ob->query("name"),key)!=-1
	        &&member_array(ob,task_ob)!=-1)
       {
                string index=ob->query("task_owner_cname")+"的"+ob->query("name");
                task_list[index]=HIR"(已被" + username + "丢失)"NOR;
                task_ob-=({ob});
       }
        return;
}


int task_give(object me,object who,object ob)
{
	object target,where;
	string tmp;
	int timer=0;
	if(!who->query("startroom"))
		return 0;
	if(ob->query("task_owner")==who->query("id")&&userp(me))
//	&&task_list[ob->query("task_owner_cname")+"的"+ob->query("name")][0..4]!=HIG"(已完成)"NOR)
	{
	task_done(ob,me->name() + "(" + me->query("id") + ")");
	who->delete("task_ob");
	who->delete("no_clean_up");
	give_reward(me,ob);
	destruct(ob);
	who->command("smile");
	me->add_temp("get_taskob",1);
	if(me->query_temp("get_taskob")>9) me->set_temp("get_taskob",4);
	target=random_npc(me);
	message("vision",HIW+who->name()+"说道："+RANK_D->query_self(who)+"已经查到偷走此宝的恶贼,"+RANK_D->query_respect(me)
	+"若是能将其诛杀，"+RANK_D->query_self(who)+
	"感激不尽，武林中人也必定对阁下刮目相看。\n"+NOR,me);
	where=this_object();
	while(where==this_object()&&++timer<10)
	{
		where=random_place_ex(me);
	}
	if(!objectp(where))
	{
		message("vision","不过目前他一点儿消息也没有。\n",me);
		return 1;
	}
	//write(where->query("main_dir")+"\n"+ok_dir[where->query("main_dir")]+"\n"+
//	base_name(where)+"\n");
	tmp=MAP_D->place_belong(where);
	message("vision",HIW+who->name()+"说道：前几天江湖出现此贼消息，我这里也有一份线报，你拿去看看吧。\n"+NOR,me);
    if(!ANTIROBOT_D->stopped())
    {
        ANTIROBOT_D->mxpantirobot_ex(me,target->query("name")+","+target->query("id")+","+tmp);
    }
    else
    {
        tell_object(me,target->query("name")+","+target->query("id")+","+tmp);
    }
	target->set("task_bekill",me->query("id"));
    target->set("uni_target",me);
	target->set("wait_time",900-50*random(me->query_temp("task_level")));
	target->set("task_level",me->query_temp("task_level"));
	me->set_temp("task_target",target->query("id"));
	me->set_temp("task_target_name",target->query("name"));
	me->set_temp("task_where",tmp);
	target->goto_leave();
	target->move(where);
	
	//加入任务统计系统 by icer
	me->set_temp("task_stat/task/task_starttime",time());
	
	return 1;
	}
	return 0;
	
}
	
object random_npc(object me)
{
	object output;
	string nickname,name,*tmp,*pinying;
	mapping skill;
	name=NAME_D->create_name();
        nickname=NAME_D->create_color_nick();
	tmp=explode(name,"@");
	pinying=explode(tmp[1]," ");
	output=new("/task/npc/target");
	output->set_name(tmp[0],({tmp[1],pinying[0],pinying[1]}));
	output->set("nickname",nickname);
	output->set("gender",random(3)>0?"男性":"女性");//male sadan is more..:)
	output->setup();
	output=do_clone(output,me);
	return output;
}
object random_carrier()
{
	object output;
	object user;
	string nickname,name,*tmp,*pinying;
	mapping skill;
	output=new("/task/npc/carrier");
	name=NAME_D->create_name();
	tmp=explode(name,"@");
	pinying=explode(tmp[1]," ");
	output->set_name(tmp[0],({tmp[1],pinying[0],pinying[1]}));
	output->set("gender",random(3)>0?"男性":"女性");//male sadan is more..:)
	if (sizeof(usrs)>0)
	{
		user = usrs[random(sizeof(usrs))];
		if (objectp(user))
		{
			output->set("title",user->query("title"));
                        if (!user->query("nickname"))
                        output->set("nickname","我不是NPC");
                        else
                        output->set("nickname",user->query("nickname"));
		}
	}
	return output;
}

object do_clone(object output,object me)
{
    object *inv, newob;
    mapping hp_status, skill_status, map_status, prepare_status;
    string *sname, *mname, *pname;
    int i, temp,lvl,exp,exp_reward,pot_reward;

    seteuid( geteuid(output) );
    lvl=me->query_temp("task_level");

/* copy entire dbase values */


    hp_status = me->query_entire_dbase();


        output->set("str", hp_status["str"]);
        output->set("int", hp_status["int"]);
        output->set("con", hp_status["con"]);
	output->set("dex", hp_status["dex"]);
        output->set("age", hp_status["age"]);


        output->set("max_qi",    hp_status["max_qi"]*(lvl+1)/4);
        output->set("eff_qi",    output->query("max_qi"));
        output->set("qi",        output->query("max_qi"));
        output->set("max_jing",  hp_status["max_jing"]*(lvl+1)/4);
        output->set("eff_jing",  output->query("max_jing"));
        output->set("jing",      output->query("max_jing"));
        output->set("max_neili", hp_status["max_neili"]*(lvl+1)/4);
        output->set("neili",     output->query("max_neili"));
        output->set("max_jingli",hp_status["max_jingli"]*(lvl+1)/4);
        output->set("jingli",    output->query("max_jingli"));
        output->set("jiali",     to_int(sqrt(to_float(output->query("max_neili"))))/6);
        output->set("gender",    hp_status["gender"]);
        output->set("combat_exp",hp_status["combat_exp"]/10*(lvl+3));
		//icer added to avoid short jing damage bug
		if (output->query("jing") < 2000)
		{
			output->set("eff_jing",2000);
			output->set("max_jing",2000);
			output->set("jing",2000);
		}
        
        exp=me->query("combat_exp");
	if(exp<30000) {
	    exp_reward=300+exp/60;
	    pot_reward=300+exp/180;
	} else if(exp<300000) {
	    exp_reward=600+exp/600;
	    pot_reward=600+exp/1800;
	    
	} else if(exp<3000000) {
	    exp_reward=2000+exp/6000;
	    pot_reward=2000+exp/18000;
	    
        } else if(exp<30000000){
           exp_reward=3500+exp/30000;
          pot_reward=3500+exp/90000;
	    
       } else if(exp<300000000){
          exp_reward=5000+exp/300000;
          pot_reward=5000+exp/900000;
        } else {
          exp_reward=6500+random(500);
          pot_reward=6000+random(500);
          }
	pot_reward=pot_reward*(lvl+1)/10;
	exp_reward=exp_reward*(lvl+1)/5;
	output->set("kill_reward/pot",pot_reward);
	output->set("kill_reward/exp",exp_reward);
	return output;
}

void give_reward(object me,object ob)
{
	int exp_r,pot_r,rpoint;
	if (userp(me)&&!me->query("biography/jobs/task"))
	{
		me->set("biography/jobs/task",time());//个人传记记录第一次完成任务时间ZINE
	}
	rpoint=ob->query("reward_point");
	exp_r=35*(rpoint+1)*(me->query_temp("get_taskob")+1)/3;
	pot_r=5*(rpoint+1)*(me->query_temp("get_taskob")+1)/3;
  exp_r=exp_r*SPEWEEK_D->query_task_bonus()/100;
  pot_r=pot_r*SPEWEEK_D->query_task_bonus()/100;

  //改为图片形式后，奖励提高一点
  exp_r = exp_r * 10 / 9;
  pot_r = pot_r * 10 / 9;
  	exp_r = REWARD_D->add_exp(me,exp_r);
        me->add("exp/task",exp_r);
	pot_r = REWARD_D->add_pot(me,pot_r);
        me->add("pot/task",pot_r);
	message("vision","你被奖励了"+chinese_number(exp_r)+"点经验和"+
	chinese_number(pot_r)+"点潜能！\n",me);
        me->add("jobs/completed/task", 1);        //任务平衡系统，统计所有任务完成的次数  by boost  2008.09.19
	return;
}

mixed query_location(string arg)
{
	string *biaodian=({
		"，",
		"。",
		"“",
		"”",
		"！",
		"？",
		"（",
		"）",
		"：",
		"；",
		"、",
		"《",
		"》",
		"〉",
		"〈",
		"’",
		"‘",
	});
	
	string *key,*owner,*name,ow,na,des,*ch=({});
	string output=arg+"在一个有着";
	object ob,where;
	mapping exits;
	int tmp;
	key=keys(task_list);
	if(member_array(arg,key)!=-1&&task_list[arg]!=HIR"(已完成)"NOR)
	{
		int flag=0,index;
		for(int i=0;i<sizeof(task_ob);i++)
		{
			if(undefinedp(task_ob[i])||!objectp(task_ob[i])) continue;
			if(arg==task_ob[i]->query("task_owner_cname")+"的"+
			task_ob[i]->query("name")) 
			{
				index=i;
				flag=1;
				break;
			}
			
			
		}
		if(flag)
		{
			ob=task_ob[index];
			where=ob;
			while(1)
			{
				where=environment(where);
				if(!where) return -1;
				if(!where->is_character()&&!clonep(where)) break;
			}
			
			exits=where->query("exits");
			if(sizeof(exits)>0)
			{
				key=keys(exits);
				for(int i=0;i<sizeof(key);i++)
				{
					output+=HIY+key[i]+NOR+(i==(sizeof(key)-1)?"":",");
				}
				output+="的出口的地方。\n";
			}
			else
			{
				output=arg+"在一个没有出口的地方。\n";
			}
			des=where->query("long");
			if(sizeof(des)==0) return output;
			for(int i=0;i<sizeof(des);i++)
			{
				if(des[i]>160&&des[i]<255)
				{
					if(member_array(des[i..i+1],biaodian)==-1)
					{
						ch+=({des[i..i+1]});
					}
					i++;
					
				}
				
			}
			if(sizeof(ch)==0) return output;
			if(sizeof(ch)==1) {
				output+="这个地方的描述只有一个字："+ch[0]+"\n";
				return output;
			}
			
			tmp=random(sizeof(ch));
			if(tmp+1==sizeof(ch)) tmp=0;
			output+="这个地方的描述中含有这样的字眼："+ch[tmp]+ch[tmp+1];
			tmp+=random(5)+1;
			if(tmp>=sizeof(ch)-1) tmp=0;
			output+=","+ch[tmp]+ch[tmp+1]+"\n";
			return output;
		}
		
		return -2;
	}
}

			
			
			
			
			
			
		





//查询task所在详细地址
mixed query_location_where(string arg)
{
	string *key,*owner,*name,ow,na,des,*ch=({});
	string region;//地区
	string output=arg+"在";
        string exit="";//出口描述，如south,west
	object ob,where;
	mapping exits;
	int tmp;
	key=keys(task_list);
	if(member_array(arg,key)!=-1&&task_list[arg]!=HIR"(已完成)"NOR)
	{
		int flag=0,index;
		for(int i=0;i<sizeof(task_ob);i++)
		{
			if(undefinedp(task_ob[i])||!objectp(task_ob[i])) continue;
			if(arg==task_ob[i]->query("task_owner_cname")+"的"+
			task_ob[i]->query("name")) 
			{
				index=i;
				flag=1;
				break;
			}
			
			
		}
		if(flag)
		{
			ob=task_ob[index];
			where=ob;
			while(1)
			{
				where=environment(where);
				if(!where) return -1;
				if(!where->is_character()&&!clonep(where)) break;
			}
			//判断大地区
			region=place_belong(where);
			exits=where->query("exits");
			na=where->query("short");
                        output =output +HIY+ region+NOR"的"HIY+na+NOR"。";
			if(sizeof(exits)>0)
			{
				key=keys(exits);
				for(int i=0;i<sizeof(key);i++)
				{
                                        exit +=HIY+key[i]+NOR+(i==(sizeof(key)-1)?"":",");
				}
				exit="这里的出口是："+exit+"。\n"NOR;
			}
			else
			{
				exit="这里"+HIR+"没有出口。\n"NOR;
			}
			output +=exit; 
			return output;
		}
		return -2;
	}
}			

int task_step2_done(object me)
{
	string family;
	int count;
	if(family_race_mode == 1 && objectp(me))
	{
		family = me->query("family/family_name");
		if(stringp(family) && family != "")
		{
			if(family == FAMILY_D->get_task_winner_family())
			{
				//当前已经享受胜利的不能参加。
				tell_object(me,"由于贵派是上轮比赛的优胜者，成绩不计入本轮比赛\n");
				return 0;
			}            
			if(undefinedp(family_task_completed_count[family]))
			{
				family_task_completed_count[family] = 1;
			}
			else
			{
				count = family_task_completed_count[family];
				family_task_completed_count[family] = count + 1;
			}
		}
        else
        {
            tell_object(me,"由于您无门无派，不能参与门派争胜。\n");
        }
	}
	return 1;
}

int get_next_family_task_time()
{
    return last_family_task_time + 3600*4;
}

int is_family_race_mode()
{
    return family_race_mode;
}


object random_room(string main_dir,int newbie)
{
    return MAP_D->random_room(main_dir,newbie);
}

object random_place()
{
    return MAP_D->random_place();
}

object random_place_ex(object user)
{
    return MAP_D->random_place_ex(user);
}

string place_belong(object place)
{
    return MAP_D->place_belong(place);
}
