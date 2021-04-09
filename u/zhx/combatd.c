/*战斗系统COMBATD.C
  每一回合所耗的eval_cost只是原来的1/2。
  但是由于考虑到的因素过多，这就产生了频繁调用SKILL_D(skill)中的
  函数的问题<比如调用SKILL_D(skill)->query_parry_msg()等>，这也
  是使这个程序所耗资源相对较多的原因之一，在不牺牲程序的情况下，
  到目前为止，还找不到这方面的解决办法。
  
  有关与之相关的程序的修改：
  1、把F_ATTACK的函数reset_action()改为：
  void reset_action()
  {
  	return COMBAT_D->reset_action(this_object());
  }
  2、把F_DBASE的一句"nosave mapping tmp_dbase;"改为
  "nosave mapping tmp_dbase=([]);"
  3、把与COMBAT_D相关的一些文件，比如score.c 、look.c的look_living()
  等做相应的修改，它们主要是跟reset_action()有联系。
  4、有的系统中没有query("sen")(体力)，请在本程序中做相应地修改 
  5、一定要减弱兵器的作用，因为武学的最高境界就是放弃兵器，天地间万物都是
  兵器。
*/  
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_DBASE;
inherit F_SSERVER;
protected void strikeback_action(object,object,string,mapping,mapping,mapping,mapping,mapping);
protected void reward(object,object,string,int,int,mapping,mapping);
protected int can_hurt(int ap,int dp);
protected mapping damage_result(object ah,object ph,mapping,mapping);
protected void make_result(object,object,object,mapping,int,mapping,mapping,mapping,mapping);
protected mapping fanzhen_action(object,object,mapping,mapping,mapping);
varargs void report_status(object, int);
protected string replace_target( string);
string damage_msg(int, string);
protected int fight_type(object);
protected string replace_result(object,object,string,object);
string eff_status_msg(int);
string status_msg(int);
protected int can_attack(object,object,mapping,mapping);
varargs int do_attack(object, object, object, int,string,int);
varargs void reset_action(object,mapping,mapping);
varargs int make_defense_decide(object,object,int,mapping,mapping,mapping,mapping,mapping);                	
protected void fanji_action(object,object,object,string,mapping,mapping,mapping,mapping,mapping);

void create()
{
        seteuid(getuid());
        set("channel_id", "战斗精灵(Combatd)");
}
string *guard_msg = ({
	CYN "$N"CYN"凝神聚气，紧紧的盯着$n"CYN"，提防$n"CYN"出冷招。\n" NOR,
        CYN "$N"CYN"注视著$n"CYN"的行动，企图寻找机会出手。\n" NOR,
        CYN "$N"CYN"正盯著$n"CYN"的一举一动，随时准备发动攻势。\n" NOR,
        CYN "$N"CYN"缓缓地移动脚步，想要找出$n"CYN"的破绽。\n" NOR,
        CYN "$N"CYN"目不转睛地盯著$n"CYN"的动作，寻找进攻的最佳时机。\n" NOR,
        CYN "$N"CYN"慢慢地移动著脚步，伺机出手。\n" NOR,
});

string *catch_hunt_msg = ({
        HIW "$N"HIW"和$n"HIW"仇人相见分外眼红，立刻打了起来！\n" NOR,
        HIW "$N"HIW"对著$n"HIW"大喝：「可恶，又是你！　」\n" NOR,
        HIW "$N"HIW"和$n"HIW"一碰面，二话不说就打了起来！\n" NOR,
        HIW "$N"HIW"一眼瞥见$n"HIW"，「哼」的一声冲了过来！\n" NOR,
        HIW "$N"HIW"一见到$n"HIW"，愣了一愣，大叫：「我宰了你！　」\n" NOR,
        HIW "$N"HIW"喝道：「$n"HIW"，我们的帐还没算完，看招！　」\n" NOR,
        HIW "$N"HIW"喝道：「$n"HIW"，看招！　」\n" NOR,
});

string *winner_msg = ({
        CYN "\n$N"CYN"哈哈大笑，愉快地说道：承让了！\n\n" NOR,
        CYN "\n$N"CYN"双手一拱，笑著说道：知道我的厉害了吧！\n\n" NOR,
        CYN "\n$N"CYN"胜了这招，向后跃开三尺，叹道：真是拔剑四顾心茫然！\n\n" NOR,
        CYN "\n$n"CYN"向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！\n\n" NOR,
        CYN "\n$n"CYN"向后一纵，恨恨地说道：君子报仇，十年不晚！\n\n" NOR,
        CYN "\n$n"CYN"向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
});
mapping *verbs = ({
        ([      "verb": "hoof", "name":"踢", ]),
        ([      "verb": "bite", "name":"咬", ]),
        ([      "verb": "claw", "name":"抓", ]),
        ([      "verb": "poke", "name":"啄", ]),
        ([      "verb": "knock","name":"撞", ]),
});
void fight(object me, object victim)
{
	object ob,w,sw;
	string *key,skill,t1,t2,p,*kongshou=({"hand","unarmed","strike","claw","cuff","finger"});	
	int ratio,time,k,type,t,v;
	mapping ac;		
	mixed action;
	mapping my=me->query_entire_dbase();
	mapping your=victim->query_entire_dbase();
	mapping my1=me->query_entire_temp_dbase();
	mapping your1=victim->query_entire_temp_dbase();
	type=can_attack(me,victim,my1,your1);
	if(!environment(victim)||!me->visible(victim)) 
	{
		return;
	}	
	if(type==-1) 
	{
		/*有参数extend_time暂时不能出招*/	
		if( !my1["guarding"]&&living(me)&&me->visible(victim)) 
		{
			my1["guarding"]-=1;
			message_combatd("\n"+guard_msg[random(sizeof(guard_msg))], me, victim);
		}
		return;
	}
	action=my["actions"];	
	if(w=my1["weapon"])
	t1=w->query("skill_type");
	if(sw=my1["secondary_weapon"])
	t2=sw->query("skill_type");	
	if(mapp(ac=me->query_skill_prepare())&&sizeof(key=keys(ac))>0)
	{
		for(t=0;t<sizeof(key);t++)
		{
			if(me->query_skill_mapped(key[t])!=ac[key[t]])
			me->prepare_skill(key[t]);
			if(member_array(key[t],kongshou)==-1
			&&key[t]!=t1+""&&key[t]!=t2+"")
			map_delete(ac,key[t]);					
		}
	}	
	t=0;		
	/*有关互备有空手互备，武器互备、武器与空手互备三种*/				
	if(mapp(ac)&&sizeof(key=keys(ac))>1)
	{		
		if(w&&member_array(t1,key)!=-1)
		{
			skill=my1["fight"]["parry"];	
			p=me->query_skill_mapped(t1);		
			/*武器互备之一*/
			if(sw&&member_array(t2,key)!=-1)
			my1["weapon"]=sw;
			/*武器互备之二*/
			else if(p
			&&(member_array("parry",key)!=-1							
			&&SKILL_D(skill)->valid_enable(t1))
			&&ratio=1)			
			me->map_skill(t1,skill);
			/*武器与空手互备*/
			else if(!sw)
			my1["weapon"]=0;													
		}		
		do_attack(me, victim, my1["weapon"], TYPE_QUICK);
		k=1;	
		if(w) my1["weapon"]=w;
		if(ratio&&p) me->map_skill(t1,p);
	} else {
		/*快招参数--hunt_ratio(),具有这个参数的武功具有先发制人的特点*/	
		skill=my1["fight"]["martial_skill"];	
		ratio=SKILL_D(skill)->hunt_ratio(me);
		time=random(ratio)+1;		
		if(me->query_skill(skill,1)<100) time=1;	  
		if(time==2) {
			do_attack(me, victim, my1["weapon"], TYPE_QUICK);
			k=1;			 
		} else if(time>2) {
			skill=HIY"$N使出绝技"+to_chinese(skill)+"，身形遂然加快,竟似欲向$n"HIY"连发"+chinese_number(time)+"招！\n"NOR;
			t=1;
			/*表现出招次第增强的特点,攻击力和伤害力由1/2向4/3递增*/
			v=80/(time-1);
			my1["extend_time"]=1;
			while(time>1&&me->is_fighting(victim))
			{			
				if(time>5) time=5;
				time--;	
				if(t!=1) skill="";
				skill+=HIR"第"+chinese_number(t)+"招！"NOR;
				my1["power_level"]=(t-1)*v-50;
				p=your1["fight"]["martial_skill"];
				if(!p||!SKILL_D(p)->strikeback_ratio(victim,me))				
				do_attack(me, victim, my1["weapon"], TYPE_QUICK,skill,1);
				else 
				do_attack(me, victim, my1["weapon"], TYPE_RIPOSTE,skill,1);
				t++;						
			}
			my1["power_level"]=30;	
			skill=HIR"最后一招!"NOR;
		}
		
	}
	if(me->is_fighting(victim))		
	{			
		if(k>0) my1["action_flag"]=1;
		if(skill==HIR"最后一招!"NOR&&t>2)
		do_attack(me, victim, my1["weapon"], type,skill,1);	
		else
		do_attack(me, victim, my1["weapon"], type);
		my1["action_flag"]=0;
	}	
	return;
}
/*常有好半天不出招的现象，我觉得最好提高出招的机率,同时*/
/*在另一方面，适当的减低先行出招的优势*/
protected int can_attack(object me,object victim,mapping my1,mapping your1)
{
	object ob;	
	if( !living(me) ) 	
	return -1;			
	if( victim->is_busy() || !living(victim)||your1["extend_time"])
	return TYPE_QUICK;
	if(my1["extend_time"]||me->is_busy())
	return -1;	
	else if( random( (int)victim->query_dex() * 3 ) > (int)me->query_str()) 
	return TYPE_REGULAR;
	else if( random( (int)me->query_cor()) > random((int)victim->query_cor()))
	return TYPE_REGULAR;
	return -1;
}

varargs void reset_action(object who,mapping my,mapping my1)
{
	string attack_skill;
	object weapon=0;
	mapping action,prepare;	
	int t;
	string *key,*kongshou=({"hand","unarmed","strike","claw","cuff","finger"});
	int flag;
	if(!mapp(my)) my =who->query_entire_dbase();
	if(!mapp(my1)) my1=who->query_entire_temp_dbase();
	flag=my1["action_flag"];
	/*初始化*/
	attack_skill=action=weapon=0;
	prepare =who->query_skill_prepare();
	if(!prepare) prepare = ([]);		
	if(sizeof(prepare))
	key=keys(prepare);	
	if(weapon= my1["weapon"])	
	attack_skill= weapon->query("skill_type");	
	else if ( sizeof(prepare) == 1)	
	attack_skill= key[0];
	else if ( sizeof(prepare) == 2)	
	attack_skill= key[flag];		
	if(!stringp(attack_skill)||!weapon
	&&member_array(attack_skill,kongshou)==-1)
	attack_skill="unarmed";	
	prepare=who->query_skill_map();	
	if(!prepare||!sizeof(prepare)) prepare=([]);
	if(!mapp(my1["fight"])) my1["fight"]=([]);
	my1["fight"]["attack_skill"]=attack_skill;
	my1["fight"]["martial_skill"]=(prepare[attack_skill]?prepare[attack_skill]:attack_skill);
	my1["fight"]["force"]=(prepare["force"]?prepare["force"]:"force");
	my1["fight"]["parry"]=(prepare["parry"]?prepare["parry"]:"parry");
	my1["fight"]["dodge"]=(prepare["dodge"]?prepare["dodge"]:"dodge");
	if(my1["fight"]["martial_skill"]!=attack_skill)
	{
		if(weapon)
		action=SKILL_D(my1["fight"]["martial_skill"])->query_action(who, weapon);	
        	else
        	action=SKILL_D(my1["fight"]["martial_skill"])->query_action(who); 
        }
	if(!mapp(action))
	{
		if( weapon) action=weapon->query("actions");
                if(!mapp(action)) action=evaluate(my["default_actions"]);
                if(!mapp(action)||!sizeof(action)) 
                {
                	my["actions"]=0;
                	return;
                }
	}	
	/*这一步是很重要的*/	
	my["actions"]=action+([]);
	return;
}

/* 通过设定内功的等级，不仅仅对于内力修为有影响，而且对于攻击有影响*/
int get_level(int level)
{
	int grade,ppl;
	ppl=level/100;
	switch(ppl) {
		case 0: 
		grade=0;
		break;
		case 1:
		if(level>=175) grade=2;
		else if(level>=139) grade=1;
		else grade=0;
		break;
		case 2:		
	 	if(level>=290) grade=9;
		else if(level>=278) grade=8;
		else if(level>=266) grade=7;
		else if(level>=253) grade=6;
		else if(level>=238) grade=5;
		else if(level>=220) grade=4;
		else if(level>=201) grade=3;		
		else grade=2;
		break;
		case 3:
		if(level>=393) grade=19;
		else if(level>=386) grade=18;
		else if(level>=379) grade=17;
		else if(level>=371) grade=16;
		else if(level>=363) grade=15;
		else if(level>=356) grade=14;
		else if(level>=346) grade=13;
		else if(level>=337) grade=12;
		else if(level>=328) grade=11;
		else grade=10;
		break;
		default:grade=20;break;
	}
	return grade;
}
int force_level(object ob,mapping my)
{
	int enl,sk,grade;
	/*内功等级与内力的综合作用，基本的内功等级能够让人脱胎换骨*/
	sk=ob->query_skill("force");
	enl=(my["max_neili"]+my["eff_neili"]+my["neili"])/30;
	sk=(sk+enl)/3;
	grade=get_level(sk)+1;	
	return grade;
}
varargs int skill_power(object ob, string skill,int usage,mapping my,mapping my1)
{
        int status,level,power,ratio,enc,max,grade;
     	string skl;   
     	if(!mapp(my)) my=ob->query_entire_dbase();
     	if(!mapp(my1)) my1=ob->query_entire_temp_dbase();
        if( !living(ob) ) return 1;
        level = ob->query_skill(skill);
        if(skill)
        {
        	if(skill=="dodge"||skill=="parry")
        	usage=SKILL_USAGE_DEFENSE;
        	else usage=SKILL_USAGE_ATTACK;
        }
        if(mapp(my1["apply"]))
        switch(usage) {
                case SKILL_USAGE_ATTACK:
                        level += my1["apply"]["attack"];                                               
                        break;
                case SKILL_USAGE_DEFENSE:
                        level += my1["apply"]["defense"];
                        if (ob->is_fighting())                        
                        level = level * (1000+my1["fight"]["dodgep"]-my1["apply"]["parry"]) / 1000;                                
                        break;
        }	
        level/=3;        
        if( !level ) return 1+my["combat_exp"] / 2000;        
        power = 1+(level / 6)*(level/6)*level/83+my["combat_exp"]/ 1000;	
	switch(skill)
	{
		case "dodge":
		skl=my1["fight"]["dodge"];
		if(ratio=SKILL_D(skl)->dodge_ratio(ob)>70) ratio=70;						
		power=(10+ratio)*power/10;
		power=power*(100-my1["power_level"])/100;
		power=power*(my["dex"]/3+ob->query_dex()/8);	
		break;
		case "parry":
		skl=my1["fight"][skill];
		if(ratio=SKILL_D(skl)->parry_ratio(ob)>70) ratio=70;
		power=(10+ratio)*power/10;
		power=power*(100-my1["power_level"])/100;
		power=power*(my["cps"]/3+ob->query_cps()/8);
		break;
		default:
	        if(skill==my1["fight"]["attack_skill"])
                skl=my1["fight"]["martial_skill"];
                else if(!stringp(skl=ob->query_skill_mapped(skill)))
                skl=skill; 
		if(ratio=SKILL_D(skl)->attack_ratio(ob)>70) ratio=70;		
		power=(10+ratio)*power/10;
		power=power*(100+my1["power_level"])/100;
		power=power*(my["str"]/3+ob->query_str()/8);
		break;		
	}
	enc=my["age"]-40;
	/*年龄的影响:40岁达到颠峰,就是再老也要保持至少1/3的攻防*/
	if(enc=enc*enc*3/500>20)
	enc=20;
	power=power-power*enc/30;
	/*负重的影响：即使负重达到最大，也要保持1/3的攻防*/
	max=ob->query_max_encumbrance();
	enc=ob->query_encumbrance();	
	enc=100-enc*100/max;
	if(enc<0) enc=0;
	power=power/3+power*2*enc/300;		
	/*武器的影响：*/
	if(my1["weapon"]) power+=30;	
	/*内功的影响。我认为，内功对不论是攻防还是伤害，都起着举足轻重*/
	/*的作用。现行的内功中，同很多武功一样，只以exert,perform来判*/
	/*定优劣，这是一个很不好的误导*/
	skl=my1["fight"]["force"];
	/*有效等级70级方可初窥门径*/
	if(ob->query_skill("force")>80)
	{
		/*内功的影响之<一>*/		
		/*引入force_ratio()的作用,单位为百分比*/
		if(ratio=SKILL_D(skl)->force_ratio(ob))
		power=power*(10+ratio)/10;
		/*内功的影响之<二>*/
		/*内功等级与内力的综合作用*/		
		grade=force_level(ob,my)+1;
		power*=grade;
	}
	else power/=2;
	if(ob->is_busy()) power/=3;
	/*体力的影响*/
	power=power*(my["sen"]/10)/(1+my["max_sen"]/10);
	if(power<1) power=1;
	if(mapp(my1["pending"]))
	map_delete(my1["pending"],"power_level");
	if(power<2&&my["combat_exp"]>2000000)
	power=15000000+random(5000000);
	return power;       
}

varargs int do_attack(object me, object victim, object weapon, 
	int attack_type,string attack_msg,int flag)
{
        string result,attack_skill,defend_skill; 
        mapping action,ad=allocate_mapping(7),my,my1,your,your1;
        int wound;        
        mapping damage=allocate_mapping(10);                             
        if(!living(me)||!present(victim,environment(me))) return 1;
	my = me->query_entire_dbase();	
	my1 = me->query_entire_temp_dbase();
	your = victim->query_entire_dbase();
	your1 = victim->query_entire_temp_dbase();  	
	if(!userp(victim)&&!query_heart_beat(victim))
	victim->set_heart_beat(1);		
	if(!victim->is_fighting(me)) victim->fight_ob(me);
	if(!me->is_fighting(victim)) me->fight_ob(victim);
	reset_action(me,my,my1);
        action = my["actions"];        
        if(!mapp(action))
        {
                	CHANNEL_D->do_channel( this_object(), "sys",
                	sprintf("%s(%s): bad action = %O",
                	my["name"], my["id"], my["actions"]));
                	return 0;                        
        }
        if(!random(3)) {
        	if(userp(me)) my["sen"]-=1;
        	if(userp(victim)) your["sen"]-=random(2);
        }        
        if(action["parry"]) {
        	if(!mapp(your1["apply"])) your1["apply"]=([]);
        	your1["apply"]["parry"]=action["parry"];
        }
        if(action["dodge"])
	my1["fight"]["dodgep"]=action["dodge"];
	attack_skill=my1["fight"]["attack_skill"];
        if(stringp(attack_msg)) result = "\n" + attack_msg + "\n";
        else {
        	if(my1["action_flag"] == 0)
        	result = "\n" + action["action"] + "！\n";
        	else result = "\n" + "紧跟着"+action["action"] + "!\n";
        }
	if(flag) result+=action["action"]+"!\n";
	ad[0]=skill_power(me,attack_skill,1,my,my1);	
	ad[3]=skill_power(victim,"dodge",2,your,your1);		
	/*1、反震;2、防御;3、对掌；4、反击*/
	/*5(隐藏）、受伤中反击*/	
	switch(make_defense_decide(me,victim,attack_type,ad,my,my1,your,your1))
	{
		case 1:
			reset_action(victim,your,your1);  
			fanji_action(me,victim,weapon,result,ad,my,my1,your,your1);		
			return 1;
			break;
		case 2:	
			reset_action(victim,your,your1);  
                        strikeback_action(victim,me,result,ad,your,your1,my,my1);
			return 1;
			break;		
	}
        if(!can_hurt(ad[0],ad[3])) {
        	reward(me,victim,"dodge",ad[0],ad[3],my,your);  
                defend_skill = your1["fight"]["dodge"];
                if(!stringp(attack_skill= SKILL_D(defend_skill)->query_dodge_msg("",victim,me)))
                attack_skill=SKILL_D("dodge")->query_dodge_msg("");                                                             
                result+=attack_skill;
        } else {               
                ad[5]=skill_power(victim,"parry",2,your,your1); 
                reward(me,victim,"parry",ad[0],ad[5],my,your);                                              
                if(!can_hurt(ad[0],ad[5])) {
                        defend_skill = your1["fight"]["parry"];
                        if(!stringp(attack_skill= SKILL_D(defend_skill)->query_parry_msg(weapon,victim,me)))                                                              
                        attack_skill= SKILL_D("parry")->query_parry_msg(weapon);              
                        result+=attack_skill;                                           
		} else {						
			damage=damage_result(me,victim,my,my1);			
			damage=fanzhen_action(me,victim,damage,your,your1);                       
			if(stringp(damage[2]))
			result+=damage[2];
	        }
	}
	damage[2]=result;
	make_result(me,victim,weapon,damage,attack_type,my,my1,your,your1);
	return 1;
}	

/*是否能反击？*/
/*strikeback_ratio()表现了后发制人的特点。这以独孤九剑，太极剑为代表*/
/*另一种形式的反击是利用敌人自己的招式反击敌人。*/
/*明教的乾坤大挪移，移花宫的移花接木，暮容氏的“以彼之道，还彼之身”便属于这一种*/	
protected int can_strikeback(object me,object victim,mapping ad,mapping my1,mapping my)
{	
	int ratio,vp,p=0;
	string parry_skill;
	if(!stringp(parry_skill=my["fight"]["martial_skill"])
	||parry_skill==my["fight"]["attack_skill"]) 
	return 0;	
	ad[1]=skill_power(victim,my["fight"]["attack_skill"],1,my1,my);
	vp=ad[1];			
	if(!ratio=SKILL_D(parry_skill)->strikeback_ratio(victim,me))	
	ratio=SKILL_D(my["fight"]["parry"])->shift_ratio(victim,me);		
	if(ratio)
	{	
		p=1;
		if(ratio>10) ratio=10;if(ratio<0) ratio=0;						
	}
	if(can_hurt(vp,3*ad[0]/(1+ratio))) 
	{
		my["fight"]["attack_power"]=2*ad[1];
		return 2;	
	}	
	return p;	
}

/*这种反击方式比较特别，它一方面省略了原combatd系统中*/
/*不必要的信息，另一方面又同时具备了对掌和换招的功能*/
/*定力、勇气和后天环境培养有关，同时年龄起了一定的作用*/
/*定力可以通过练习各门派的心法增加，但是不能累加。*/
protected int can_fanji(object me,object victim,mapping my,mapping your)
{
        string *zt=({"jing","qi","sen"});		
    	int temp;    	    	
    	/*如果己方状态不好，还是以防御为佳*/ 	    
    	for(temp=0;temp<sizeof(zt);temp++)
    	if((1+your[zt[temp]]*100)/(1+your["max_"+zt[temp]])<30)    		
    	return 0;    	   
    	/*相关因素之一：定力（冷静）和勇气，*/
    	if(random(victim->query_cor()+victim->query_spi())>=
    	(me->query_cor()+me->query_spi())/3)
    	return 1;
     	/*如果攻击方状态不佳，这是个反击的好机会*/
     	for(temp=0;temp<sizeof(zt);temp++)
    	if((1+my[zt[temp]]*100)/(1+my["max_"+zt[temp]])<30)
    	return 1;    	    	
    	return 0;
}
varargs int make_defense_decide(object me,object victim,int attack_type,mapping ad,mapping my,mapping my1,mapping your,mapping your1)                				
{
	int v;
	string attack_skill=my1["fight"]["martial_skill"];
	if(SKILL_D(attack_skill)->no_fanji(me)) return 0;					
	if(victim->is_busy()||!living(victim)) return 0;
	switch(attack_type) {		
		case TYPE_QUICK:
			if(!random(3))
			return can_strikeback(me,victim,ad,your,your1);
			return 0;
			break;
		case TYPE_REGULAR:			
			if(v=can_strikeback(me,victim,ad,your,your1))
			return v;
			if(can_fanji(me,victim,my,your))
			return 1;			
			return 0;
			break;
		case TYPE_RIPOSTE:
			return can_strikeback(me,victim,ad,your,your1);								
			break;	
		default:return 0;							
	}	
}        
protected void strikeback_action(object me,object victim,string result,
	mapping ad,mapping my,mapping my1,mapping your,mapping your1)
{
	string *msg=({
		"$P随意挥洒，竟把$p的攻势化掉，紧接着",
		"$P轻轻化掉$p的攻势，然后",
		"$P凝立不动，待到$p攻近之时，才突然发招！只见",
		"$p招式用老，$l露出些许破绽，这时",
		"$P窥准$p的$l露出的一个空门，当即",
                "$P毫不迟疑，居然向$p招式最盛之处攻去！只见",
		"$p一不小心，$l间空门大露，$P毫不犹豫，转守为攻！却见",
	});
	mapping action,damage=allocate_mapping(10);
	string temp,attack_skill,defend_skill; 
	string skill=my1["fight"]["parry"];
	int ratio,at=my1["fight"]["attack_power"];
	map_delete(your1["fight"],"attack_power");			
	/*以敌之道,攻敌之身*/
	if(ratio=SKILL_D(skill)->shift_ratio(me,victim)
	&&skill==my1["fight"]["martial_skill"])	
	my["actions"]=your["actions"];					
	/*以自己的招式攻敌*/		
	action=my["actions"];
	temp=action["action"];
	temp+="!\n";			
	result=replace_target(result);
	result+=msg[random(sizeof(msg))];
	result+=temp;			
	ad[2]=skill_power(victim,"dodge",2,your,your1);			
        if(!can_hurt(at,ad[2])) {
		reward(me,victim,"dodge",at,ad[2],my,your);
                defend_skill=your1["fight"]["dodge"];
                if(!stringp(attack_skill= SKILL_D(defend_skill)->query_dodge_msg("",victim,me)))
                attack_skill= SKILL_D("dodge")->query_dodge_msg("");                                                             
                result+=attack_skill;
        } else {               
                ad[4]=skill_power(victim,"parry",2,your,your1);
                reward(me,victim,"parry",at,ad[4],my,your);     
                if(!can_hurt(at,ad[4])) {
                        defend_skill=your1["fight"]["parry"];
                        if(!stringp(attack_skill= SKILL_D(defend_skill)->query_parry_msg(my1["weapon"],victim,me)))                                                             
                        attack_skill= SKILL_D("parry")->query_parry_msg(my1["weapon"]);              
                        result+=attack_skill;                                           
		} else {						
			damage=damage_result(me,victim,my,my1);			
			damage=fanzhen_action(me,victim,damage,your,your1);                       
			if(stringp(damage[2]))
			result+=damage[2];
	        }		
	}	
	damage[2]=result;
	make_result(me,victim,my1["weapon"],damage,TYPE_QUICK,my,my1,your,your1);
	return;
}

protected void fanji_action(object me,object victim,object weapon,string result,
	mapping ad,mapping my,mapping my1,mapping your,mapping your1)
{
	string *fanji_msg=({
		"$p不退反进，只见",
		"$p不守反攻，却见",
		"$p无暇招架，当即转守为攻！紧随着",
		"就在这紧要关头，",
		"眼看$P的攻势堪堪接近，",
		"便在这千钧一发之际，",
		"$p同时出招，向$P对去！只见",
	});
	string temp,defend_skill,v;
	mapping your_action=your["actions"],my_action=my["actions"];
	mapping damage=allocate_mapping(10),damage1=allocate_mapping(10);
	result+=fanji_msg[random(sizeof(fanji_msg))];
	temp=your_action["action"]+"！\n";	
	ad[1]=skill_power(victim,your1["fight"]["attack_skill"],1,your,your1);
	ad[2]=skill_power(me,"dodge",2,my,my1);
	if(!can_hurt(ad[0],ad[3])) { 
		reward(me,victim,"dodge",ad[0],ad[3],my,your);			               
	} else {		
                ad[5]=skill_power(victim,"parry",2,your,your1);                                    
                reward(me,victim,"parry",ad[0],ad[5],my,your);  
                if(can_hurt(ad[0],ad[5])) {                       	                                              		
			damage=damage_result(me,victim,my,my1);				
			damage=fanzhen_action(me,victim,damage,your,your1);               			
			map_delete(my1["fight"],"be_fanzhened");
	        }
	}
	if(!can_hurt(ad[1],ad[2])) {    		            	
		reward(victim,me,"dodge",ad[1],ad[2],your,my);
		defend_skill=my1["fight"]["dodge"];
                if(stringp(v=SKILL_D(defend_skill)->query_dodge_msg("",me,victim)))
                temp+=v;                                                             
                else temp+=SKILL_D("dodge")->query_dodge_msg("");
        } else {        	        	
                ad[4]=skill_power(me,"parry",2,my,my1);
                reward(victim,me,"parry",ad[1],ad[4],your,my);           
                if(!can_hurt(ad[1],ad[4])) {
                        defend_skill=my1["fight"]["parry"];
                        if(!stringp(v= SKILL_D(defend_skill)->query_parry_msg(weapon,me,victim)))                                                             
                        temp+= SKILL_D("parry")->query_parry_msg(weapon);              
                        else temp+=v;
        	} else {                                                   		
			damage1=damage_result(victim,me,your,your1);					
			damage1=fanzhen_action(victim,me,damage1,my,my1);		               								
			if(stringp(damage1[2])&&damage[0]<1) temp+=damage1[2];
			map_delete(your1["fight"],"be_fanzhened");
	        }
	}
        temp=replace_target(temp);
        result+=temp;
        damage[0]+=damage1[3];
        damage[1]+=damage1[4];
	damage[2] =result;
	damage[3]+=damage1[0];	
	damage[4]+=damage1[1];
	make_result(me,victim,weapon,damage,TYPE_REGULAR,my,my1,your,your1);
	return;
}

/* 护体真气自然而发，一切都是内功等级的高作用的。*/
protected mapping fanzhen_action(object me,object victim,mapping damage,mapping your,mapping your1)
{	
	int bonus,v,absorb_vic,defense_factor;
	string base,skill,msg;	
	if(!living(victim)||!mapp(your1["apply"])) return damage;
	if(your1["apply"]["armor_vs_force"]
	&&v=victim->query_skill(your1["fight"]["force"],1)>100) 
	{ 
		msg="$n试图使用"+sprintf("%s",to_chinese(base)) 
		+"的护体真气来化解$N的攻击..."; 
		if( your["neili"]>damage[0]) 	
		{ 
			if( random(6)>0 ) 
			{ 
				your["neili"]-=damage[0]/2; 
				msg+="$n成功化解了$N的攻击。\n";  
				damage[0]=0;
				damage[1]=0;
				damage[2]=msg;
			} else {
				your["neili"]-=damage[0]/4; 
				damage[0]/=2; 
				damage[1]/=2;
				if(!damage[2])
				damage[2]="";
				msg+="$n的护体真气削弱了$N的凌厉攻势。\n";
				damage[2]=msg+damage[2];
			} 
		} else {
			if(!damage[2]) damage[2]="";
			damage[2]=msg+damage[2]+"\n";
		}
		return damage;
	}
	base="iron-cloth";
	if(!skill=victim->query_skill_mapped(base))
	{
		base="parry";
		skill=your1["fight"]["parry"];
	}	
	if(!v=SKILL_D(skill)->bounce_ratio(victim)) return damage;		
	absorb_vic=victim->query_skill(base);		
	absorb_vic+=your1["apply"]["fanzhen"] * 2;	
        msg= SKILL_D(skill)->query_absorb_msg();
        if(!msg) msg="";			        
	if( (damage[0] - absorb_vic*5/2) < 0 )
	{
                defense_factor = 0 - v * (damage[0]- absorb_vic*2)/10;                                                                                                                             
                damage[0]=0;
                damage[1]=0;
		if ( defense_factor < 0 ||fight_type(me)==1) 
		{
			msg+="但听卟的一声轻响，$P如击败革，$p成功地挡住了$P的攻势！\n";
			msg=replace_string(msg,"$z",to_chinese(skill));
			damage[2]=msg;
		} else {                
                	damage[3]=defense_factor;
                	me->set_temp("fight/be_fanzhened",1);
                	msg+= damage_msg(defense_factor, "反弹伤");
                	msg=replace_string(msg,"$z",to_chinese(skill));
                	damage[2]=msg;
                }                            
                return damage;
	} 
	if(!damage[2]) damage[2]="";
	damage[2]=msg+damage[2];
	return damage;
}
protected mapping damage_result(object ah,object ph,mapping my,mapping my1)
{
	int level,jiali,armor,damage,damage_bonus,fight_type;
	mapping damm=allocate_mapping(10),action;
	string dam,skill;
	mixed foo;
	object weapon=my1["weapon"];
	action=my["actions"];
	armor=ph->query_temp("apply/armor")+ph->query_fle()/3;
	fight_type=fight_type(ah);	
	/*如果是在喂招*/
	if(mapp(my1["pending"])&&my1["pending"]["duizhao"]==ph)
	{
		damm[0]=1;
		return damm;
	}	
	/*apply/damage的作用，XKX系统向来神兵利器过于霸道，还是削弱点好*/
	if(mapp(my1["apply"]))
	damage =my1["apply"]["damage"]/3;
	/*臂力的影响，强调先天的作用*/
	damage_bonus=my["str"]/3+ah->query_str()/8;		
	/*具体武功的影响。在这里，我认为有必要减低action([])中的各项keys对伤害力的*/
	/*影响，因为再平凡的武功，也能化腐朽为神奇。片面强调 action["damage"] 以及*/
	/*action["force"]的伤害，就会使它的其它方面黯然失色。*/
	/*第二：actiom["force"]*/
	if(action["force"])
	damage+=action["force"]/10;
	/*第三：武功等级的影响。只要精湛，再平凡的武功，也能化腐朽为神奇。*/	
	level=ah->query_skill(my1["fight"]["attack_skill"])*2/3+1;			
	level=get_level(level)*5;
	/*内功的影响*/
	level+=force_level(ah,my)*5;
	damage_bonus+=level;
	if(mapp(my1["apply"]))
	damage_bonus+=my1["apply"]["damage"]/3;	
	/*加力的作用*/
	dam=0;
	jiali=my["jiali"];	
	/*各类武功的hit_ob()函数的调用*/
	/*第一：force_skill*/
	if(jiali&&my["neili"]>jiali&&fight_type!=1)
	{
		damage_bonus+=jiali;
		skill=my1["fight"]["force"];
		/*只有在enforce时才调用force_skill的hit_ob函数，这是其特别之处*/
		if(foo=SKILL_D(skill)->hit_ob(ah,ph,damage_bonus))
		{
			if(stringp(foo)) dam=foo+"";
			else if(intp(foo)&&(int)foo>10) damage_bonus+=foo;
			else if(mapp(foo)) {
				if(stringp(foo["damage_msg"]))
				dam=foo["damage_msg"]+"";
				if(intp(foo["damage_bonus"]))
				damage_bonus+=foo["damage_bonus"];
			}
		}
		my["neili"]-=jiali/2;
	}
	/*第三：weapon_damage,武器的伤害应属于外伤*/	
	if(fight_type!=1&&weapon)
	{
		if(foo=weapon->hit_ob(ah,ph,damage_bonus))
		{			
			if(stringp(foo)) dam=foo+"";
			else if(intp(foo)) damage_bonus+=foo;
			else if(mapp(foo)) {
				if(stringp(foo["damage_msg"]))
				dam=foo["damage_msg"]+"";
				if(intp(foo["damage_bonus"]))
				damage_bonus+=foo["damage_bonus"];
			}
		}					
		/*这是以气御刃的时侯，凡铁亦可成利器*/
		if(my1["force_type"]==weapon->query("skill_type"))
		damage_bonus+=my1["force_damage"];
	
	}
	/*第二：martial_skill*/	
	if(fight_type!=1&&skill=my1["fight"]["martial_skill"])
	{
		/*这里加入武功的一个参数：damage_ratio(),单位百分比*/
		damage_bonus+=damage_bonus*SKILL_D(skill)->damage_ratio(ah)/10;
		if(foo=SKILL_D(skill)->hit_ob(ah,ph,damage_bonus))
		{
			if(stringp(foo)) dam=foo+"";
			else if(intp(foo)) damage_bonus+=foo;
			else if(mapp(foo)) {
				if(stringp(foo["damage_msg"]))
				dam=foo["damage_msg"]+"";
				if(intp(foo["damage_bonus"]))
				damage_bonus+=foo["damage_bonus"];
			}
		}
	}	
	/*第四：npc本身固有的*/
	else if(fight_type!=1)
	{		
		if(foo=ah->hit_ob(ah,ph,damage_bonus))
		{
			if(stringp(foo)) dam=foo+"";
			else if(intp(foo)) damage_bonus+=foo;
			else if(mapp(foo)) {
				if(stringp(foo["damage_msg"]))
				dam=foo["damage_msg"]+"";
				if(intp(foo["damage_bonus"]))
				damage_bonus+=foo["damage_bonus"];
			}
		}		
	}
	/*ph的护具的作用*/
	damage-=armor;
	damage_bonus-=armor;
	/*第一：action["damage"]*/
	if(action["damage"]) 
	damage=action["damage"]*(1000+damage)/1000;	
	if(damage<10) damage=10;
	if(damage_bonus<0) damage_bonus=0;
	damage+=damage_bonus;
	damm[0]=damage;	
	damm[1]=damage_bonus;
	if( functionp(action["post_action"]) )
        evaluate(action["post_action"], ah,ph, weapon, damage);  
	if(stringp(dam)&&dam!="")
	damm[2]=dam;
	return damm;
}
protected void make_result(object me,object victim,object weapon,mapping damage,
int attack_type,mapping my,mapping my1,mapping your,mapping your1)
{	
	int wound;	
	int k,v;
	string msg,skill;
	string result=damage[2];				
	string *dfm=({
		"就在这电火石光之时，",
		"血光迸溅之中，",		
		"在这快如闪电的交击中，",
		"倏的一声，人影交错！",
		"兔起鹘落之间，",
		"一方不及招架，另一方已然攻到！",
		"守方没能闪开，",
	});
	mapping action=my["actions"];		
	k=fight_type(me);
	if(mapp(your1["apply"]))	
	map_delete(your1["apply"],"parry");    
	/*鉴于杀力过大,现把杀伤力除以3*/
	if(k!=1)
	{
		damage[0]=damage[0]*k/3;
		damage[1]=damage[1]*k/3;
		damage[3]=damage[3]*k/3;
		damage[4]=damage[4]*k/3;		 
	} 
	if(damage[0]>0)
	{
		if(k==1)
		{
			damage[0]=1;
			damage[1]=0;
		}
		victim->receive_damage("qi",damage[0],me);
		if(damage[1]>0)
		{
			wound=1;
			victim->receive_wound("qi",damage[1],me);
		}
		v=(1+your["qi"]*100)/(1+your["max_qi"]);
		v=(v*3+damage[0])/4;
		if(!your1["fight"]["be_fanzhened"])
                result +=dfm[random(sizeof(dfm))]+damage_msg(v, action["damage_type"]);
                else map_delete(your1["fight"],"be_fanzhened");
	}			
	if(damage[3]>0)
	{
		wound=0;
		if(k==1)
		{
			damage[3]=1;
			damage[4]=0;
		}
		me->receive_damage("qi",damage[3],victim);
		if(damage[4]>0)
		{
			me->receive_wound("qi",damage[4],victim);
			wound=1;
		}	
		action=your["actions"];
		v=(1+my["qi"]*100)/(1+my["max_qi"]);
		v=(v*3+damage[3])/4;
		if(!my1["fight"]["be_fanzhened"])
		{
			if(damage[0]<1)
			result += replace_target(dfm[random(sizeof(dfm))]+damage_msg(v, action["damage_type"]));				
			else result+="与此同时，"+replace_target(damage_msg(v, action["damage_type"]));		
		}
		else map_delete(my1["fight"],"be_fanzhened");
	}			
	result=replace_result(me,victim,result,weapon);	
	message_combatd(result,me,victim);
	if( damage[0] > 0 ) {
               	report_status(victim, wound);
               	if(!userp(victim)&&k==1) your["qi"]+=1;
               	if(your["qi"]*2 <= your["max_qi"]&&
               	!me->is_killing(your["id"]) &&
               	!victim->is_killing(my["id"])) {
                    	me->remove_enemy(victim);
                       	victim->remove_enemy(me);                       	
                       	message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);                       	
/*                       	
                       	if(userp(me)&&my["family"]
			&&my["family"]["master_id"]==your["id"]
			&&my["family"]["master_name"]==your["name"]
                	&&my["combat_exp"]>1500000
                	&&me->query_temp("pending/出师")
			&&my["family"]["master_name"]==your["name"]) {
				me->delete_temp("pending/出师");
                        	me->set("chushi/"+my["family"]["family_name"],1);
				message("channel:chat",HIC"\n【江湖故事】"HIY+victim->query("name")+HIY"哈哈大笑道道：“果然是青出於蓝胜於蓝！"+me->query("name")+"从此脱离本门，由今日始，一切行为，与本门无涉！！！”\n"NOR,users());
				my["score"]=0;
				my["title"]="隐士";
				map_delete(my,"family");
			}
*/			
                } 
                else if(stringp(skill=your1["fight"]["martial_skill"])
                &&skill!=your1["fight"]["attack_skill"]
                &&attack_type==TYPE_REGULAR&&living(victim)
                &&your["qi"]>0
                &&SKILL_D(skill)->hurt_ratio(victim))
                {
                      	message_combatd(HIR"\n$N"HIR"怒吼一声，居然不顾伤势，挺身向$n"HIR"攻去!\n"NOR,victim,me);
                       	do_attack(victim, me, your1["weapon"], TYPE_QUICK);
                }
                
        }  if(damage[3]>0&&me->is_fighting(victim)&&victim->is_fighting(me)) {         	
               	report_status(me, wound);               		               	
               	if(!userp(me)&&k==1) my["qi"]+=1;
               	if(my["qi"]*2 <= my["max_qi"]&&
               	!me->is_killing(your["id"]) &&
               	!victim->is_killing(my["id"])) {
                     	me->remove_enemy(victim);
                      	victim->remove_enemy(me);
                     	message_vision( winner_msg[random(sizeof(winner_msg))], victim, me);
/*                     	
                     	if(userp(victim)&&your["family"]
			&&your["family"]["master_id"]==my["id"]
			&&your["family"]["master_name"]==my["name"]
                	&&your["combat_exp"]>1500000
                	&&victim->query_temp("pending/出师")
			&&your["family"]["master_name"]==my["name"]) {
				victim->delete_temp("pending/出师");
                        	victim->set("chushi/"+victim->query("family/family_name"),1);
				message("channel:chat",HIC"\n【江湖故事】"HIY+me->query("name")+HIY"哈哈大笑道道：“果然是青出於蓝胜於蓝！"+victim->query("name")+"从此脱离本门，由今日始，一切行为，与本门无涉！！！”\n"NOR,users());
				your["score"]=0;
				your["title"]="隐士";
				map_delete(your,"family");
			}
*/			
                     	return;
               	}                   
                else if(stringp(skill=my1["fight"]["martial_skill"])
                &&skill!=my1["fight"]["attack_skill"]
                &&attack_type==TYPE_REGULAR&&living(me)
                &&my["qi"]>0
                &&SKILL_D(skill)->hurt_ratio(me))
                {
                	attack_type=TYPE_QUICK;
                      	message_combatd(HIR"\n$N"HIR"怒吼一声，居然不顾伤势，挺身向$n"HIR"攻去!\n"NOR,me,victim);
                       	do_attack(me,victim,my1["weapon"], TYPE_QUICK);
                }
        }
        if(attack_type==TYPE_REGULAR
        &&damage[0] < 1
        &&your1["guarding"]
        &&me->is_fighting(victim)) {
                your1["guarding"]=0;
                if( random(my["dex"]) < 5 ) {
                        message_combatd("\n$P一击未中，露出些许破绽，$n毫不放过，立刻反击！\n", me,victim);
                        do_attack(victim, me, your1["weapon"], TYPE_QUICK);
                } else {
                        message_combatd("\n$N见$n攻击失误，趁机发动攻击！\n", victim, me);
                        do_attack(victim, me, your1["weapon"], TYPE_RIPOSTE);
                }
        }              
        return;
}
				
protected int fight_type(object me)
{
	object *env=all_inventory(environment(me));
	int i;
	if(me->query_temp("pending/duizhao"))
	return 1;
	if(sizeof(env))
	for(i=0;i<sizeof(env);i++)
	{
		if(!living(env[i])) continue;
		if(me->is_killing(env[i]->query("id")))
		{
			return 3;
			break;
		}
	}
	return 2;
}

protected int can_hurt(int ap,int dp)
{
	if(ap*(5+random(10))/10>dp*random(10)/5)
	return 1;
	return 0;
}
protected string replace_result(object me,object victim,string str,object weapon)
{
	string limb,*limbs;
	mapping action=me->query("actions");
	int k;
	limbs=victim->query("limbs");
	limb=limbs[random(sizeof(limbs))];
	str+="&_&";
	str=replace_string(str,",","，");
	str=replace_string(str,".","。");
	str=replace_string(str,"!","！");
	str=replace_string(str,"\n","\n　　");
	str=replace_string(str,"\n　　&_&","\n");
	str=replace_string(str,"$N","$P");
	str=replace_string(str,"$n","$p");
	str=replace_string(str,"$P","$N",1);
	str=replace_string(str,"$p","$n",1);	
	str=replace_string(str, "$l", limb);
	str=replace_string(str,"&_&","");
	if(strsrch(str,"$k")!=-1)
	{
		limbs=me->query("limbs");
		limb=limbs[random(sizeof(limbs))];	
		str= replace_string( str, "$k", limb);
	}
	if(strsrch(str,"$w")!=-1)
	{		
		if(objectp(weapon))
		str = replace_string( str, "$w", weapon->name() );
		else if( objectp(weapon=me->query_temp("weapon") ))
		str = replace_string( str, "$w", weapon->name() );
		else if( stringp(action["weapon"]) )
		str = replace_string( str, "$w", action["weapon"]);
		else
		str = replace_string( str, "$w", "手指" );
	} if(strsrch(str,"$v")!=-1) {
		if(objectp(weapon=victim->query_temp("weapon")))
		str=replace_string(str,"$v",weapon->name());			
		else str=replace_string(str,"$v","手指");
	}
	return str;
}

/*结束一根鸡腿打天下的局面*/
protected void reward(object me,object victim,string v,int ap,int dp,mapping my,mapping your)
{
	int amount,fight_type,i,j;
	object ob;
	string skill=me->query_temp("fight/attack_skill");
	if(!skill) return;
	if(userp(me)&&userp(victim)&&query_ip_name(me)==query_ip_name(victim)) 
        return;       
        if((userp(victim)||!your["can_raise"])&&(ap>dp*3/2||ap*3/2<dp)||your["no_raise"]) return;
        if(!userp(victim)&&your["can_raise"]&&your["combat_exp"]<my["combat_exp"]) return;
        if(!userp(ob=me)) ob=victim;
        else if(userp(victim)&&userp(me))        
        {
        	if(your["combat_exp"]>my["combat_exp"])
        	ob=victim;
        	else ob=me;
        }
        i=ob->query_skill(skill)*2/3;
        i=i*i*i/10;
	j=ob->query("combat_exp");
	if(j<20000) j=12;
        else j=i/(j/12);
        if(random(4)>j||!random(j+3)) return;
        if(userp(me)&&userp(victim)) fight_type=1;
        else fight_type=fight_type(me);
        if(!userp(victim)&&your["can_raise"]) fight_type=1;
        amount=1+fight_type;
        me->improve_skill(skill,amount);
        if(skill=me->query_skill_mapped(skill))
	me->improve_skill(skill,random(amount)+1);	
	victim->improve_skill(v,amount);
	if(skill=victim->query_skill_mapped(v))
	victim->improve_skill(skill,random(amount)+1);	
	my["combat_exp"]+=fight_type+random(3);
	your["combat_exp"]+=fight_type+random(3);	
	if(!random(2))
	{
		my["potential"]+=1;
		your["potential"]+=1;
	}
}

protected string replace_target( string result )
{
    result = replace_string( result, "$N", "$T" );
    result = replace_string( result, "$n", "$N" );
    result = replace_string( result, "$T", "$n" );
    result = replace_string( result, "$P", "$T" );
    result = replace_string( result, "$p", "$P" );
    result = replace_string( result, "$T", "$p" );    
    result = replace_string( result, "$w", "$v" );
    result = replace_string( result, "$l", "$k" );
    return result;
}
varargs void report_status(object ob, int effective)
{
	string msg,*m;
        if( effective )
        msg=eff_status_msg((int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi") );                        
        else
        msg=status_msg((int)ob->query("qi") * 100 / (int)ob->query("max_qi") );
        m=explode(msg,":");
        msg="　　「"NOR+m[0]+"$N"+NOR +m[0]+m[1]+"」\n"NOR;
        message_vision(msg,ob);            
}
/*这个函数用于自动进入fight状态！*/
void auto_fight(object me, object obj, string type)
{	
	if( !userp(me) && !userp(obj) ) return;
	if( me->query_temp("looking_for_trouble") ) return;
	me->set_temp("looking_for_trouble", 1);
	call_out( "start_" + type, 0, me, obj);
}
/*XKX系统一般没有杀气，我认为这不好。*/

void start_berserk(object me, object obj)
{
	int shen,bellicosity;
	mapping my=me->query_entire_dbase();
	mapping your=obj->query_entire_dbase();
	bellicosity=my["bellicosity"];
	
	if( !me || !obj ) return;	
	me->set_temp("looking_for_trouble", 0);
	
	if(	me->is_fighting(obj)		
	||	!living(me)		
	||	environment(me)!=environment(obj)	
	||	environment(me)->query("no_fight") 
	)	return;
	message_vision(HIR"$N"HIR"用一种异样的眼神扫视着在场的每一个人。\n"NOR, me);
	if((my["shen"]/5000==0||your["shen"]/5000==0
	||my["shen"]>your["shen"]&&my["shen"]-your["shen"]<10000
	||my["shen"]<your["shen"]&&my["shen"]-your["shen"]>-10000)
	&&bellicosity<me->query_cps()*50) return;	
	shen=my["shen"]; 
	if(shen>0&&shen<bellicosity||shen<0&&0-shen<bellicosity) shen=bellicosity;
	if( !userp(me) || (int)my["neili"] > (random(shen) + shen)/10 ) return;	
	if( shen > (int)my["score"] 
	&&!wizardp(obj) ) {
		message_vision("$N对著$n喝道：" + RANK_D->query_self_rude(me)
		+ "看你实在很不顺眼，去死吧。\n", me, obj);
		me->kill_ob(obj);
	} else {
		message_vision("$N对著$n喝道：喂！" + RANK_D->query_rude(obj)
		+ "，" + RANK_D->query_self_rude(me) + "正想找人打架，陪我玩两手吧！\n",
		me, obj);
		me->fight_ob(obj);
	}
	return;
}

void start_hatred(object me, object obj)
{
	if( !me || !obj ) return;		

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)	
	||	!living(me)		
	||	environment(me)!=environment(obj)
	||	environment(me)->query("no_fight") 	
	)	return;
	/*非人类也会说话？*/
	if(!random(2)&&me->can_speak())
	message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
	me->kill_ob(obj);
}

void start_vendetta(object me, object obj)
{
	if( !me || !obj ) return;	

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)		
	||	!living(me)			
	||	environment(me)!=environment(obj)	
	||	environment(me)->query("no_fight") 	
	)	return;

	me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
	if( !me || !obj ) return;	

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)	
	||	!living(me)	
	||	environment(me)!=environment(obj)
	||	environment(me)->query("no_fight") 
	)	return;

	me->kill_ob(obj);
}

void announce(object ob, string event)
{
	switch(event) {
		case "dead":
			message_vision(HIR"\n$N"+HIR"身躯晃了两晃，随即重重地倒在地上，撒手人寰而去了。\n"NOR, ob);
			break;
		case "unconcious":
			message_vision(RED"\n$N"+RED"头晕目眩，脚下踉踉跄跄，一个不稳，跌在地上一动也不动了。\n"NOR, ob);
			break;
		case "revive":
			message_vision(HIY"\n$N"+HIY"嘴角抽搐了几下，慢慢睁开眼睛，清醒了过来。\n"NOR, ob);
			break;
	}
}

void winner_reward(object killer, object victim)
{
	killer->defeated_enemy(victim);
}
int victim_lose(object killer,object victim,string killerid) 
{
	
        int lose,exp_k,exp_v;
        if((wizardp(victim)&&!wizardp(killer))
        ||(!wizardp(victim)&&wizardp(killer)))
	return 0;
        if(victim->query_temp("last_fainted_from")
        && victim->query_temp("last_fainted_from")!=
        killerid) 
        lose=0;
        else {        	        	
                exp_k=killer->query("combat_exp");
        	exp_v=victim->query("combat_exp");
        	if(userp(killer)&&exp_k>exp_v*3) return 0;
        	if (exp_k>exp_v) {        	 	        	    	        		
        	        lose=10*exp_v/(exp_k+1)*(4000+exp_v)/500;
               	} else lose=(4000+exp_v)/50;                 	
                if(lose<0) lose=0;
                if(lose>exp_v) lose=exp_v;
       }             
       return lose;
}
mapping *verbs = ({
       ([      "verb": "hoof", "name":"踢", ]),
       ([      "verb": "bite", "name":"咬", ]),
       ([      "verb": "claw", "name":"抓", ]),
       ([      "verb": "poke", "name":"啄", ]),
       ([      "verb": "knock","name":"撞", ]),
});
void killer_reward(object killer, object victim)
{
	int bls,i,j;
	string vmark,msg,cor=NOR +HIM,verbmsg,killerid;
	mapping quest,actions,verb;
	mapping my=killer->query_entire_dbase();
	mapping your=victim->query_entire_dbase();
	int exp, pot, score, bonus,factor,lose,gain;	
        msg=victim->name()+cor+"被"+killer->name()+cor;
        if( killer->beast() )
        {
          	verb = my["verbs"];          	
          	j = random(sizeof(verb)); 
          	for(i=0;i<sizeof(verbs);i++)
           	{
            		if( verb[j] == verbs[i]["verb"] )
            		verbmsg = verbs[i]["name"];
           	}
           	if(!verbmsg) verbmsg="杀";
           	msg+=verbmsg+"死了。";
        } else {        
		actions = my["actions"];
		switch(actions["damage_type"]) {
			case "擦伤":
	        	case "割伤":
				msg+="砍死了。";
				break;
			case "劈伤":	
			        msg+="劈死了。";
			        break;
			case "刺伤":
				msg+="刺死了。";
				break;
			case "瘀伤":
				msg+="击死了。";
				break;
			case "点穴":
			        msg+="戳死了。";
			        break;	
			case "内伤":
			case "反弹伤":
				msg+="震死了。";
				break;
			case "砸伤":
			        msg+="砸死了。";
			        break;	
			case "抓伤":
			        msg+="抓死了。";
			        break;
			case "抽伤":
			        msg+="抽死了。";                
			default:
				msg+="杀死了。";
		}
	}			
	lose=victim_lose(killer,victim,killerid);
	if( userp(victim) ) {	 	
		bls=10;
		victim->clear_condition();
		your["bellicosity"]=0;	
		map_delete(your,"vendetta");
		if (mapp(your["family"])&&your["family"]["master_id"] == "feng qingyang")
		{
			map_delete(your,"family");
			your["class"]="";
			your["title"]="普通百姓";
			your["feng_dietime"]=your["mud_age"];
			vmark = read_file("/data/FENG", 1, 1);
			i = atoi(vmark);
			i--;
			vmark=""+i+"";
			write_file("/data/FENG",vmark, 1);
		}
		if( your["thief"] )
                your["thief"] =your["thief"]/2;	
		my["shen"]-=your["shen"]/ 10;
                if(userp(killer)) {
                	write_file("/log/static/KILL_PLAYER",sprintf("%s(%s) killed by %s(%s) on %s\n",
                	your["name"], your["id"],
                	my["name"],my["id"],ctime(time()) ));
                	my["PKS"]+=1;
	     		killer->apply_condition("no_pk_time",120+
	       		killer->query_condition("no_pk_time"));	      
	     		killerid=my["id"];	     
	     		victim->delete_temp("last_fainted_from");	     		
	     		gain=killer->query("be_pked/"+victim->query("id"));
	     		/*当然不能无缘无故被人杀，吃亏怎么样还是得记住，有冤报冤，有仇报仇！*/
	     		if(gain>0&&query_ip_number(killer)!=query_ip_number(victim)) {
	     			killer->delete("be_pked/"+victim->query("id"));
	     			my["combat_exp"]+=gain;
	     			my["potential"]+=gain/5;
	     			tell_object(killer,HIC"你终于杀死了"+your["name"]+HIC"，报了昔日的一箭之仇！为此，\n"
	     			"你获得了：\n"+HIR+chinese_number(gain)+HIC"点实战经验、"+HIR+chinese_number(gain/5)
	     			+HIC"点潜能\n作为报偿，恭喜你心仇得雪！\n"NOR);
	     			your["combat_exp"]-=gain;
	     			your["potential"]-=gain/3;
	     			victim->skill_death_penalty();
	     			CHANNEL_D->do_channel(this_object(), "rumor",
		  		sprintf("%s亲手杀死了%s,报了昔日之仇！",my["name"], your["name"]));
		  		killer->save();victim->save();
		  		return; 
           		} else {/*无仇而杀，必有后报！*/
           			killerid=my["id"];
           			if(lose>0) {
           				if(!undefinedp(victim->query("be_pked/"+killerid))
           				||!intp(victim->query("be_pked/"+killerid)))
           				victim->set("be_pked/"+killerid,lose);    					
           				else victim->add("be_pked/"+killerid,lose);           																
           			}           			
               		}
               	}                	
               	CHANNEL_D->do_channel(this_object(), "rumor",msg);
               	if(lose>0) {               		               	             	
                	your["combat_exp"]-=lose;
                	if((your["potential"]-your["learned_points"])>lose/3)
			your["potential"]-=lose/3;           				
			else your["potential"]-=(your["potential"]-your["learned_points"])/2;											
	 		victim->skill_death_penalty();
		}
		victim->save();
	} else  {
		my["MKS"]+=1;		
		bls=1;
		if(userp(killer)&&mapp(my["family"])
		&&my["family"]["master_id"]==your["id"]
		&&my["family"]["master_name"]==your["name"]
                &&my["combat_exp"]>1500000) {
                        killer->set("chushi/"+my["family"]["family_name"],1);
			message("channel:chat",HIC"\n【江湖故事】"HIY+your["name"]
			+HIY"口中吐了一口鲜血，惨然道：“"+my["name"]+"从此脱离本门，由今日始，一切行为，与本门无涉！！！”\n"NOR,users());
			my["score"]=0;
			my["title"]="隐士";
			map_delete(my,"family");
		}			
		/*任务系统*/
        	if( objectp(killer)&&interactive(killer) && 
        	(quest = my["quest"])
                && (my["task_time"] >= time())
                &&(quest["quest"]==your["name"]))
        	{
           		message("channel:gab", HIC"【任务频道】"+your["name"]+"被"+my["name"]+"杀死了。\n"NOR,users());
                	tell_object(killer,"恭喜你！你又完成了一项任务！\n");
                	exp = (quest["exp_bonus"]*2) + random(quest["exp_bonus"]/2);
                	if(exp > 300) exp = 300;
                	pot = exp / 5 + 1;
                	score = (exp+pot)/2;
                	my["combat_exp"]+=exp;
                	my["potential"]+=pot;
                	my["score"]+=score;
                	tell_object(killer,HIW"你被奖励了：\n" +
                	chinese_number(exp) + "点实战经验\n"+
                	chinese_number(pot) + "点潜能\n" +
                	chinese_number(score)+"点忠诚。\n"NOR);
                	my["equest"]=quest;
                	map_delete(my,"quest");
        	}
        }        
	if (objectp(killer) && userp(killer) &&my["combat_exp"]<your["combat_exp"]) 
	my["shen"]-=your["shen"]/ 10;
	my["bellicosity"]+=bls * (userp(killer)? 1: 10);
	if( stringp(vmark = victim->query("vendetta_mark")) )
	killer->add("vendetta/" + vmark, 1);
	if(userp(killer)) killer->save();
	return;
}
	
string damage_msg(int damage, string type)
{
        string str;

        if( damage == 0 ) return "结果没有造成任何伤害。\n";

        switch( type ) {
	case "咬伤":
             	if( damage < 10 ) return "却见只是在$n的皮肉上碰了碰，好象只蹭破点皮。\n";
             	else if( damage < 40 ) return "这一下咬出一道不大的伤口。\n";
             	else if( damage < 80 ) return "只听得$P[哇！]的一声惨叫，咬出了一道血肉模糊的伤口。\n";
             	else return "只听得见$n一声惨哼，被咬得鲜血横流！\n";
             	break;        	
        case "劈伤":
		if( damage < 10) return "却见$N只碰到了$p的衣脚。\n";
		else if ( damage < 20) return "$N的$w只是轻轻的碰到$p的皮肉。\n";
		else if ( damage < 40) return "只听得「嗤」的一声$p被斩出一到口子。\n";
		else if ( damage < 80) return "只听得「嚓」的一声，$w竟斩入$p皮肉两分。\n";
		else if ( damage < 160) return "只听得「嚓」的一声，$w竟斩到了$p的骨头，鲜血直流。\n";
		else return "只听得见$n一声惨嚎，$w已在$p$l斩出一道血肉模糊的严重伤口！！\n";
        case "割伤":
                if( damage < 10 ) return "只见得$N的$w只是轻轻地划破$p的皮肉。\n";
                else if( damage < 20 ) return "$N的$w已经在$p$l划出一道细长的血痕。\n";
                else if( damage < 40 ) return "只听得「嗤」地一声$w在$p身上划出一道伤口！\n";
                else if( damage < 80 ) return "只听得「嗤」地一声$w划出$p一道血淋淋的伤口！\n";
                else if( damage < 160 ) return "只听得「嗤」地一声$w在$p身上划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
                else return "只听得见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！！\n";
                break;
        case "刺伤":
                if( damage < 10 ) return "却见$N只是轻轻地刺破了$p的皮肉。\n";
                else if( damage < 20 ) return "只见得$w在$p$l刺出一个创口。\n";
                else if( damage < 40 ) return "只听得「噗」地一声$w刺入了$n$l寸许！\n";
                else if( damage < 80 ) return "只听得「噗」地一声$w刺进$n的$l，使$p不由自主地退了几步！\n";
                else if( damage < 160 ) return "只听得「噗嗤」地一声，$w已在$p$l刺出一个血肉模糊的血窟窿！\n";
                else return "只听得见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！！\n";
                break;
        case "砸伤":
                if( damage < 10 ) return "$N只是轻轻地碰到，等于给$n搔了一下痒。\n";
                else if( damage < 20 ) return "$N的$w在$p的$l砸出一个小臌包。\n";
                else if( damage < 40 ) return "$N砸个正着，$n的$l登时肿了一块老高！\n";
                else if( damage < 80 ) return "这次砸个正着，$n闷哼一声显然吃了不小的亏！\n";
                else if( damage < 120 ) return "只听得「砰」地一声，$n疼得连腰都弯了！\n";
                else if( damage < 160 ) return "「轰」地一声$w砸得$n眼冒金星，差一点摔倒！\n";
                else if( damage < 240 ) return "$N手中的$w重重地砸中，$n眼前一黑，「哇」地一声吐出一口鲜血！\n";
                else return "只听得见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！\n";
                break;                
        case "瘀伤":
                if( damage < 10 ) return "$N只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
                else if( damage < 20 ) return "$N在$n的$l造成一处瘀青。\n";
                else if( damage < 40 ) return "$N一击命中，$n的$l登时肿了一块老高！\n";
                else if( damage < 80 ) return "$N一击命中，$n闷哼了一声显然吃了不小的亏！\n";
                else if( damage < 120 ) return "只听得「砰」地一声，$n退了两步！\n";
                else if( damage < 160 ) return "这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n";
                else if( damage < 240 ) return "$n被$N重重地击中,「哇」地一声吐出一口鲜血！\n";
                else return "只听得见「砰」地一声巨响，$n像一捆稻草般飞了出去！！\n";
                break;
        case "内伤":
                if( damage < 10 ) return "$N只是把$n打得退了半步，毫发无损。\n";
                else if( damage < 20 ) return "只听得$n痛哼一声，在$p的$l造成一处瘀伤。\n";
                else if( damage < 40 ) return "$N一击命中，把$n打得痛得弯下腰去！\n";
                else if( damage < 80 ) return "只听得$n闷哼了一声，脸上一阵青一阵白，显然受了点内伤！\n";
                else if( damage < 120 ) return "$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n";
                else if( damage < 160 ) return "$n被重重地击中，「哇」地一声吐出一口鲜血！\n";
                else if( damage < 240 ) return "只听得「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n";
                else return "只听得见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！！\n";
                break;
        case "点穴":
        	if( damage < 10 ) return "$N只是轻轻的碰到$n的$l根本没有点到穴道。\n";
                else if( damage < 20 ) return "只听得$n痛哼一声，在$p的$l造成一处淤青。\n";
                else if( damage < 40 ) return "$N一击命中，$w点中了$n$l上的穴道,$n只觉一阵麻木！\n";
                else if( damage < 80 ) return "只见得$n闷哼了一声，脸上一阵青一阵白，登时$l麻木！\n";
                else if( damage < 160 ) return "只见得$n脸色一下变得惨白，$w点中$n$l的穴道,一阵疼痛遍布整个$l！\n";
                else if( damage < 240 ) return "只听得$n一声大叫,$l的穴道被点中,疼痛直入心肺！\n";
                else return "只听得见$n一声惨叫,一阵剧痛夹杂着麻痒游遍全身,跟着直挺挺的倒了下去.\n";
                break;        
        case "抽伤":
                if( damage < 10 ) return "$N只是在$n的皮肉上碰了碰，好象只蹭破点皮。\n";
                else if( damage < 20 ) return "$N在$n$l抽出一道轻微的紫痕。\n";
                else if( damage < 40 ) return "只听得$w「啪」地一声在$n$l抽出一道长长的血痕！\n";
                else if( damage < 80 ) return "只听得「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n";
                else if( damage < 80 ) return "只听得「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n";
                else if( damage < 160 ) return "只听得「啪」地一声爆响！这一下好厉害，只抽得$n皮开肉绽，血花飞溅！\n";
                else return "只听得见$n一声惨嚎，$w重重地抽上了$p的$l，$n顿时血肉横飞，十命断了九条！\n";
                break;
        case "抓伤":
                if( damage < 10 ) return "这下只是轻轻地抓到，比抓痒稍微重了点。\n";
                else if( damage < 20 ) return "只见得在$p的$l抓出几条血痕。\n";
                else if( damage < 40 ) return "$N一抓命中，$n的$l被抓得鲜血飞溅！\n";
                else if( damage < 80 ) return "只听得「嗤」地一声，$l被抓得深可见骨！！\n";
                else if( damage < 120 ) return "$n被$N一抓命中，$l被抓得血肉横飞！！！\n";
                else if( damage < 160 ) return "这一下「嗤」地一声抓得$n连晃好几下，差一点摔倒！\n";
                else if( damage < 240 ) return "只听得$n哀号一声，$l被抓得筋断骨折！！\n";
                else return "只听得见$n一声惨嚎，$l被抓出五个血窟窿！鲜血溅得满地！！\n";
                break;
        case "反弹伤":
                if( damage < 5 ) return "$N受到$n$z的反震，闷哼一声。\n";
                else if( damage < 10 ) return  "$N被$n的$z震得气血翻腾，大惊失色。\n";
                else if( damage < 20 ) return "$N被$n的$z震得站立不稳，摇摇晃晃。\n";
                else if( damage < 40 ) return "$N被$n以$z反震，「嘿」地一声退了两步。\n";
                else if( damage < 80 ) return "$N被$n的$z反弹回来的力量震得半身发麻。\n";
                else if( damage < 120 ) return "$N被$n的$z反弹力一震，胸口有如受到一记重击，连退了五六步！\n";
                else if( damage < 160 ) return "$N被$n的$z一震，眼前一黑，身子向後飞出丈许！！\n";
                else return "$N被$n的$z一震，眼前一黑，狂吐鲜血，身子象断了线的风筝向後飞去！！\n";
                break;          
        default:
                if( !type ) type = "伤害";
                if( damage < 10 ) str =  "却见$N对$n只是勉强造成一处轻微";
                else if( damage < 20 ) str = "$n被$N击中,造成轻微的";
                else if( damage < 30 ) str = "$n被$N击中,$l造成一处";
                else if( damage < 50 ) str = "$n被$N击中,造成$l严重";
                else if( damage < 80 ) str = "$n被$N击中,造成$l颇为严重的";
                else if( damage < 120 ) str = "$n被$N击中,造成相当严重的";
                else if( damage < 170 ) str = "$n被$N击中,打得$l严重";
                else if( damage < 230 ) str = "这一下造成极其严重的";
                else str =  "只见得$n手中鲜血狂喷，身子摇摇欲坠，$l露出极为可怕的";
                return str + type + "！\n";
        }
}

string eff_status_msg(int ratio)
{
        if( ratio==100 ) return HIG ":看起来气血充盈，精神饱满，正处于巅峰状态。" NOR;
        if( ratio > 95 ) return HIG ":只受了点轻伤，但无伤大体。" NOR;
        if( ratio > 90 ) return HIY ":看起来可能受了几处皮肉伤。" NOR;
        if( ratio > 80 ) return HIY ":受了几处伤，不过似乎并不碍事。" NOR;
        if( ratio > 60 ) return HIY ":受伤不轻，创口正在流着血。" NOR;
        if( ratio > 40 ) return HIR ":气息粗重，动作散乱，已经在走下坡路了。" NOR;
        if( ratio > 30 ) return HIR ":已经伤痕累累，正在勉力支撑著不倒下去。" NOR;
        if( ratio > 20 ) return HIR ":遍体鳞伤，只剩下最后一口气了。" NOR;
        if( ratio > 10 ) return RED ":伤重之下已经难以支撑，眼看就要倒在地上。" NOR;
        if( ratio > 5  ) return RED ":瞳孔放大，已经奄奄一息，命在旦夕了。" NOR;
        return RED ":口角溢血，已经有如风中残烛，随时都可能断气。" NOR;
}

string status_msg(int ratio)
{
        if( ratio==100 ) return HIG ":看起来精神饱满，正处于巅峰状态。" NOR;
        if( ratio > 95 ) return HIG ":脸色似乎有些苍白，但是仍然颇为灵动。" NOR;
        if( ratio > 90 ) return HIY ":看起来可能有些不济了。" NOR;
        if( ratio > 80 ) return HIY ":动作似乎有点呆滞，但是身子仍然甚为平稳。" NOR;
        if( ratio > 60 ) return HIY ":气喘嘘嘘，脸色惨白，汗如雨下。" NOR;
        if( ratio > 40 ) return HIR ":动作已经紊乱，身子左形右绌，破绽渐增。" NOR;
        if( ratio > 30 ) return HIR ":已经一副头重脚轻的模样，正在勉力支撑著不倒下去。" NOR;
        if( ratio > 20 ) return HIR ":目光散乱，脸色惨白，已经力不从心了。" NOR;
        if( ratio > 10 ) return RED ":摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
        return RED ":已经陷入昏迷状态，随时都可能咽气。" NOR;
}

