// damage.c

#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <move.h>

int ghost = 0;

int is_ghost() { return ghost; }

varargs int receive_damage(string type, int damage, object who)
{
	int val;

	if( damage < 0 ) error("F_DAMAGE: 伤害值为负值。\n");
	if( type!="jing" && type!="qi" )
		error("F_DAMAGE: 伤害种类错误( 只能是 jing, qi 其中之一 )。\n");

	if( objectp(who) ) set_temp("last_damage_from", who);
	val = (int)query(type) - damage;

	if( val >= 0 ) set(type, val);
	else set( type, -1 );

	set_heart_beat(1);

	return damage;
}

varargs int receive_wound(string type, int damage, object who)
{
	int val;

	if( damage < 0 ) error("F_DAMAGE: 伤害值为负值。\n");
	if( type!="jing" && type!="qi" )
		error("F_DAMAGE: 伤害种类错误( 只能是 jing, qi 其中之一 )。\n");

	if( objectp(who) ) set_temp("last_damage_from", who);
	val = (int)query("eff_" + type) - damage;

	if( val >= 0 ) set("eff_" + type, val);
	else {
		set( "eff_" + type, -1 );
		val = -1;
	}

	if( (int)query(type) > val ) set(type, val);

	set_heart_beat(1);

	return damage;
}

int receive_heal(string type, int heal)
{
	int val;

	if( heal < 0 ) error("F_DAMAGE: 恢复值为负值。\n");
	if( type!="jing" && type!="qi" )
		error("F_DAMAGE: 恢复种类错误( 只能是 jing, qi 其中之一 )。\n");

	val = (int)query(type) + heal;

	if( val > (int)query("eff_" + type) ) set(type, (int)query("eff_" + type));
	else set( type, val );

	return heal;
}

int receive_curing(string type, int heal)
{
	int max, val;

	if( heal < 0 ) error("F_DAMAGE: 恢复值为负值。\n");
	if( type!="jing" && type!="qi" )
		error("F_DAMAGE: 恢复种类错误( 只能是 jing, qi 其中之一 )。\n");

	val = (int)query("eff_" + type);
	max = (int)query("max_" + type);

	if( val + heal > max ) {
		set("eff_" + type, max);
		return max - val;
	} else {
		set( "eff_" + type, val + heal);
		return heal;
	}
}

void unconcious()
{
	object defeater,room,*inv;
        int i;

	if( !living(this_object()) ) return;
	if( query("env/immortal") ) return;

	if( objectp(defeater = query_temp("last_damage_from")) )
		COMBAT_D->winner_reward(defeater, this_object());

	this_object()->remove_all_enemy();

	message("system", HIR "\n你的眼前一黑，接著什么也不知道了....\n\n" NOR,
		this_object());
        
        if(userp(this_object()))
          { 
           room=new("/adm/single/temproom");
           inv=all_inventory(this_object());
           for(i=0;i<sizeof(inv);i++)
             inv[i]->move(room);
        
	   this_object()->disable_player(" <昏迷不醒>");

           inv=all_inventory(room);
           for(i=0;i<sizeof(inv);i++)
             inv[i]->move(this_object());
          }

        else 
           this_object()->disable_player(" <昏迷不醒>");
         
	set("jing", 0);
	set("qi", 0);
	set_temp("block_msg/all", 1);
	COMBAT_D->announce(this_object(), "unconcious");
	call_out("revive", random(100 - query("con")) + 30);
}

varargs void revive(int quiet)
{
	object room,obj,*inv;
        int i;
        
        if(userp(this_object()))
          { 
           room=new("/adm/single/temproom");
           inv=all_inventory(this_object());
           for(i=0;i<sizeof(inv);i++)
             inv[i]->move(room);
        
	   this_object()->enable_player();

           inv=all_inventory(room);
           for(i=0;i<sizeof(inv);i++)
             inv[i]->move(this_object());
          }
        else 
           this_object()->enable_player();

	if( !quiet ) 
        {
            if (userp(this_object()))
            {
                      COMBAT_D->announce(this_object(), "revive");
		      this_object() -> set_temp("block_msg/all", 0);
		      message("system", HIY "\n慢慢地你终于又有了知觉....\n\n" NOR,this_object());
            }
            else
		set_temp("block_msg/all", 0);
       }
}

void die()
{
	object corpse, killer,room,obj,*inv;
	int i;
       
	if( !living(this_object()) ) revive(1);
	if( query("env/immortal") ) return;

	// Clear all the conditions by death.
	this_object()->clear_condition();

	COMBAT_D->announce(this_object(), "dead");
	if( objectp(killer = query_temp("last_damage_from")) ) {
		set_temp("my_killer", killer->query("id"));
		COMBAT_D->killer_reward(killer, this_object());
	}

	if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
		corpse->move(environment());

	this_object()->remove_all_killer();
	all_inventory(environment())->remove_killer(this_object());

	this_object()->dismiss_team();
	if( userp(this_object()) ) {
		if (this_object()->is_busy())
			this_object()->interrupt_me();
		set("jing", 1);	set("eff_jing", 1);
		set("qi", 1);	set("eff_qi", 1);
		ghost = 1;
		this_object()->move(DEATH_ROOM);
		DEATH_ROOM->start_death(this_object());
	} else
		destruct(this_object());
}

void reincarnate()
{
	ghost = 0;
	set("eff_jing", query("max_jing"));
	set("eff_qi", query("max_qi"));
}

int max_food_capacity() { return query_weight() / 200; }

int max_water_capacity() { return query_weight() / 200; }

int heal_up()
{
	int update_flag, i;
	mapping my;

//	if( this_object()->is_fighting() ) return -1;

	update_flag = 0;

	my = query_entire_dbase();

	if( my["water"] > 0 ) { my["water"] -= 1; update_flag++; }
	if( my["food"] > 0 ) { my["food"] -= 1; update_flag++; }

	if( my["water"] < 1 && userp(this_object()) ) return update_flag;
	
	my["jing"] += my["con"] / 3 + my["max_jingli"] / 10;
	if( my["jing"] >= my["eff_jing"] ) {
		my["jing"] = my["eff_jing"];
		if( my["eff_jing"] < my["max_jing"] ) { my["eff_jing"] ++; update_flag++; }
	} else update_flag++;

	my["qi"] += my["con"] / 3 + my["max_neili"] / 10;
	if( my["qi"] >= my["eff_qi"] ) {
		my["qi"] = my["eff_qi"];
		if( my["eff_qi"] < my["max_qi"] ) { my["eff_qi"] ++; update_flag++; }
	} else update_flag++;

	if( my["food"] < 1 && userp(this_object()) ) return update_flag;

	if( my["max_jingli"] && my["jingli"] < my["max_jingli"] ) {
		my["jingli"] += (int)this_object()->query_skill("magic", 1) / 2;
		if( my["jingli"] > my["max_jingli"] ) my["jingli"] = my["max_jingli"];
		update_flag++;
	}

	if( my["max_neili"] && my["neili"] < my["max_neili"] ) {
		my["neili"] += (int)this_object()->query_skill("force", 1) / 2;
		if( my["neili"] > my["max_neili"] ) my["neili"] = my["max_neili"];
		update_flag++;
	}

	return update_flag;
}
