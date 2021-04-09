// attack.c
// From ES2
// Modified by Xiang for XKX (12/15/95)
// Modified by iszt@pkuxkx, 2007-03-14, fixed a color bug

#include <ansi.h>
#include <dbase.h>
#include <origin.h>
#include <skill.h>
#include <combat.h>

#define MAX_OPPONENT	4

void clean_up_enemy();
int hate(object me,object ob);
void meet(string str,object ob);
nosave object *enemy = ({});
nosave string *killer = ({});

// prototypes

object *query_enemy()
{
	clean_up_enemy();
	return enemy;
}

string *query_killer() { return killer; }

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_fighting(object ob)
{
	if( !ob ) return sizeof(enemy) > 0;

	return member_array(ob, enemy)!=-1;
}

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_killing(string id)
{
	if( !id ) return sizeof(killer) > 0;

	return member_array(id, killer)!=-1;
}

//This function starts fight between this_object() and ob
// 战斗开始的时候记录对方的战斗信息（攻击力，格挡能力，躲闪能力）
void fight_ob(object ob)
{
	mapping prepare;
  int attack_points, dodge_points, parry_points;
  object weapon;
  string skill_type;
  
	if(!ob || ob==this_object()) return;

	set_heart_beat(1);
	//if(sizeof(enemy)>=30) {
	//	write("你突然觉得有些厌倦了这世界上无休无止的打杀,不想再和"+ob->name()+"比试了\n");
	//	return;
	
	if( member_array(ob, enemy)==-1 ) 
		enemy += ({ ob });
  
  if ( ob->is_character() &&
  	   living(ob) )
  {
    prepare = ob->query_skill_prepare();
	  if (!mapp(prepare)) 
		  prepare = ([]);
	  if( objectp(weapon = ob->query_temp("weapon")) )
		  skill_type = weapon->query("skill_type");
	  else if (!sizeof(prepare))
		  skill_type = "unarmed";
	  else if ( sizeof(prepare))
		  skill_type = (keys(prepare))[0];

	  attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	  parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	  dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
	  set("last_attack_info/id", ob->query("id") );
	  set("last_attack_info/name", ob->query("name") );
	  set("last_attack_info/attack", attack_points );
	  set("last_attack_info/parry", parry_points );
	  set("last_attack_info/dodge", dodge_points );
	  set("last_attack_info/time", time());
	  if ( ob->query("zyhb") || ob->query_temp("can_zyhb") )
	  	set("last_attack_info/hubo" , 1);
	  else
	  	set("last_attack_info/hubo" , 0);

	  if ( ob->query_skill("qiankun-danuoyi", 1 )>=200 )
	  {
	  	set("last_attack_info/absorb/skill" , "qiankun-danuoyi");
	  	set("last_attack_info/absorb/level" , ob->query_skill("qiankun-danuoyi", 1 ) );
	  }
	  else if ( ob->query_skill("iron-cloth") >= 300 )
	  {
	  	set("last_attack_info/absorb/skill" , "iron-cloth");
	  	set("last_attack_info/absorb/level" , ob->query_skill("iron-cloth") );
	  }
	  else if ( ob->query_skill("douzhuan-xingyi") >= 400 )
	  {
	  	set("last_attack_info/absorb/skill" , "douzhuan-xingyi");
	  	set("last_attack_info/absorb/level" , ob->query_skill("douzhuan-xingyi") );
	  }
	}
//通知被攻击者。可以给npc实现一些智能。
  if ( member_array(ob->query("id"),killer) != -1)
    ob->got_fight(this_object(),"kill");
  else
    ob->got_fight(this_object(),"fight");
}

// This function starts killing between this_object() and ob
void kill_ob(object ob)
{       
        int i; 
        object *inv, *team;
        object me = this_object();

        if( me->query_temp("guards/living")==ob)   
        {
                tell_object(me, HIR "不能杀你要保护的人！\n" NOR);
                return;
        } 

	if( member_array(ob->query("id"), killer)==-1 )
		killer += ({ ob->query("id") });

	tell_object(ob, HIR "看起来" + this_object()->name() + HIR"想杀死你！\n" NOR);
        if (!me->query("uni_target"))
        {
        inv = all_inventory(environment(me));  
        team = ob->query_team();
        for( i=0; i<sizeof(inv); i++ )
        { 
                if( !living(inv[i]) ) continue;
                if( inv[i]!=me && inv[i]->query_temp("guards/living")==ob )
                { 
                        message_vision( HIR "$N受到攻击，$n挺身而出，加入战团！\n" NOR, ob, inv[i] );
                        inv[i]->fight_ob(me);
                        me->fight_ob(inv[i]);
                }
                else if ( arrayp(team) && member_array(inv[i], team)!=-1 && inv[i]!=ob )
                {
                        message_vision( HIR "$N受到攻击，$n挺身而出，加入战团！\n" NOR, ob, inv[i] );
                        inv[i]->fight_ob(me);
                        me->fight_ob(inv[i]);
                }
        }
        }
	fight_ob(ob);
}

void clean_up_enemy()
{
	if( sizeof(enemy) > 0 ) {
		for(int i=0; i<sizeof(enemy); i++) {
			if( !objectp(enemy[i])
			||	environment(enemy[i])!=environment()
			||	(!living(enemy[i]) && !is_killing(enemy[i]->query("id"))) )
				enemy[i] = 0;
		}
		enemy -= ({ 0 });
	}
}

// This function checks if the current opponent is available or
// select a new one.
object select_opponent()
{
	int which;
	object focus;

	if( !sizeof(enemy) ) return 0;

	focus = this_object()->query_temp("focus_target");
	if ( focus && objectp(focus) && member_array(focus, enemy)>=0 )
		return focus;
	
	which = random(MAX_OPPONENT);

	return which < sizeof(enemy) ? enemy[which] : enemy[0];
}

// Stop fighting ob.
int remove_enemy(object ob)
{
	if( is_killing(ob->query("id")) ) return 0;

	enemy -= ({ ob });
	
	ob->enemy_removed(this_object());
	
	return 1;
}

// Stop killing ob.
int remove_killer(object ob)
{
	if( is_killing(ob->query("id")) ) {
		killer -= ({ ob->query("id") });
		remove_enemy(ob);
		return 1;
	}    
	return remove_enemy(ob);
}

// Stop all fighting, but killer remains.
void remove_all_enemy()
{
	for(int i=0; i<sizeof(enemy); i++) {
		// We ask our enemy to stop fight, but not nessessary to confirm
		// if the fight is succeffully stopped, bcz the fight will start
		// again if our enemy keeping call COMBAT_D->fight() on us.
		if( objectp(enemy[i]) ) enemy[i]->remove_enemy(this_object());
		enemy[i] = 0;;
	}

	enemy = ({});
}

// Stop all fighting and killing.
void remove_all_killer()
{
	killer = ({});
	enemy -= ({ 0 });

	for(int i=0; i<sizeof(enemy); i++)
		if( enemy[i]->remove_killer(this_object()) )
			enemy[i] = 0;;

	enemy -= ({ 0 });
}

// reset_action()
//
// This function serves as a interface of F_ATTACK and wielded, worn objects.
// When the living's fighting action need update, call this function.
//
void reset_action()
{
	object me,ob;
	mapping prepare;
	string type, skill;

	me = this_object();
	prepare = query_skill_prepare();
	
	if( ob = query_temp("weapon") ) type = ob->query("skill_type");
	else if ( sizeof(prepare) == 0)	type = "unarmed";
	else if ( sizeof(prepare) == 1)	type = (keys(prepare))[0];
	else if ( sizeof(prepare) == 2)	
	type = (keys(prepare))[query_temp("action_flag")];

	if( stringp(skill = query_skill_mapped(type)) && !query_skill(skill, 1) )
	{
		map_skill(type);
	}

	if( stringp(skill = query_skill_mapped(type)) ) {
		// If using a mapped skill, call the skill daemon.
       	if( !find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") < 0)//判断是否是自创武功
		{
			if ( ob )
			         	set("actions", (: call_other, PLAYER_SKILL_D(skill), "query_action", me, ob :) );
                else
                        set("actions", (: call_other, PLAYER_SKILL_D(skill), "query_action" :) );
		}
        else 
		{
			if ( ob )
			         	set("actions", (: call_other, SKILL_D(skill), "query_action", me, ob :) );
                else
                        set("actions", (: call_other, SKILL_D(skill), "query_action" :) );
		}
	} else {
		// Else, let weapon handle it.
		if( ob ) 
		{
		  if ( mapp( ob->query("actions") ) )
		    set("actions", ob->query("actions",1) );
		  else
		    set("actions", ob->query_action());
		}
		else set("actions", query("default_actions",1) );
	}
}

// This is called in heart_beat() to perform attack action.
int attack()
{
	object opponent;
	int exp, max_exp, this_exp;
	float combat_factor;

	clean_up_enemy();

	exp = max_exp = 0;
	combat_factor = 1.0;
	enemy = query_enemy();
	if (sizeof(enemy) > 1)
	{
		for (int i=0;i<sizeof(enemy);i++)
		{
			//系数降低1000倍，否则当exp之和>1000M的时候将溢出变负  by icer
			this_exp = enemy[i]->query("combat_exp")/1000 + 1;
			exp += this_exp;
			if (max_exp < this_exp)
				max_exp = this_exp;
		}
		if (max_exp)
		{
			combat_factor = (exp + 0.0) / max_exp;
			combat_factor = log(combat_factor);
			combat_factor /= 3;
			combat_factor = exp(combat_factor);
		}
	}
	set_temp("combat_factor", combat_factor);

	opponent = select_opponent();
        if( opponent ) {
		set_temp("last_opponent", opponent);
		COMBAT_D->fight(this_object(), opponent);
		return 1;
	} else
		return 0;
}

//
// init() - called by MudOS when another object is moved to us.
//
void init()
{
	object ob;
	string vendetta_mark;
	// We check these conditions here prior to handle auto fights. Although
	// most of these conditions are checked again in COMBAT_D's auto_fight()
	// function, these check reduces lots of possible failure in the call_out
	// launched by auto_fight() and saves some overhead.
	if(	is_fighting()
	||	!living(this_object())
	||	!(ob = this_player()) 
	||	environment(ob)!=environment()
	||	!living(ob)
	||	ob->query("linkdead")
        ||      (!userp(ob) && !userp(this_object() ) ) )
		return;   
        
        if(!undefinedp(this_object()->query("friends/"+ob->query("id"))))
                return; 
        
        if(!undefinedp(this_object()->query("marry/lover"))
             && this_object()->query("marry/lover") == ob->query("id") )
                return;
 
        if(random(ob->query("kar")+ob->query("per"))> 30)
                return; 

	// Now start check the auto fight cases.
	if( userp(ob) && is_killing(ob->query("id")) ) {
		COMBAT_D->auto_fight(this_object(), ob, "hatred");
		return;
	} else if( stringp(vendetta_mark = query("vendetta_mark"))
	&& ob->query("vendetta/" + vendetta_mark) ) {
		COMBAT_D->auto_fight(this_object(), ob, "vendetta");
		return;
	} else if( userp(ob) && (string)query("attitude")=="aggressive" ) {
		COMBAT_D->auto_fight(this_object(), ob, "aggressive");
		return;
	}               
/***********************既然combatd里面已经注释叼了，这里也一并注释掉
          else if(hate(this_object(),ob)>200)
               {
                COMBAT_D->auto_fight(this_object(), ob, "aggressive");
		return; 
               }   
 **************************/
        return;
}   

void meet(string str,object ob)
{ 
  if( !ob->visible(this_object()) ) return;
  if( environment(this_object()) == environment(ob) ) 
  command(str);
}

int hate(object me,object ob)
{
        string str,pai,pai2,temp;
        int i,j,degree,score1,score2,mp_num; 
        if( !(pai = me->query("family/family_name")))
              return 1;   
        if( !(pai2 = ob->query("family/family_name")))
             return 1;  
        if(userp(me))score1=me->query("score");
        else score1 = me->query("combat_exp")/200+1;
        score2 = ob->query("score");
        if(score2 <= 0)score2=1;
        str = read_file("/hate/mp_mun",1,1);
        sscanf(str,"%d",mp_num);
        for(i=0;i<mp_num-1;i++)
        {
        str = "";
        temp = "";
        str = read_file("/hate/"+pai,i+1,1);
        sscanf(str,"%s %d",temp,degree);
        if(temp == pai2)
                break;
        }          
       if(degree>-200)return 1;
        if(wizardp(ob)||wizardp(me)) return 1;
        degree = -(((score1/10)*(score2/10))/10)*degree/100; 
        if(degree<=0)degree = 1;
        if(degree > 100)
          {
             if(me->query("combat_exp")>50*ob->query("combat_exp"))
               {call_out("meet",0,"say 虽然你派与我有仇，但念你年幼无知，放你一条生路。",ob); 
                return 1;
               }     

             if(ob->query("combat_exp")>50*me->query("combat_exp"))
                return 1;   
             call_out("meet",0,"say 我与你派势不两立，今日不能放过你了!",ob);  
          }   
	return degree;
return 0;
}
