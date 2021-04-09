// combatd.c
//Leon Modified 97-12-1
//对年龄在15岁以下的player,被杀只降很少exp,potential
//#pragma optimize all
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;
string  absorb_skill;
string msg;
int absorb_vic;
int qdamage;
int jibie;
int randnum;

void bijiao(object killer,object victim);

string *guard_msg = ({
	CYN "$N注视著$n的行动，企图寻找机会出手。\n" NOR,
	CYN "$N正盯著$n的一举一动，随时准备发动攻势。\n" NOR,
	CYN "$N缓缓地移动脚步，想要找出$n的破绽。\n" NOR,
	CYN "$N目不转睛地盯著$n的动作，寻找进攻的最佳时机。\n" NOR,
	CYN "$N慢慢地移动著脚步，伺机出手。\n" NOR,
});

string *catch_hunt_msg = ({
	HIW "$N和$n仇人相见分外眼红，立刻打了起来！\n" NOR,
	HIW "$N对著$n大喝：「可恶，又是你！」\n" NOR,
	HIW "$N和$n一碰面，二话不说就打了起来！\n" NOR,
	HIW "$N一眼瞥见$n，「哼」的一声冲了过来！\n" NOR,
	HIW "$N一见到$n，愣了一愣，大叫：「我宰了你！」\n" NOR,
	HIW "$N喝道：「$n，我们的帐还没算完，看招！」\n" NOR,
	HIW "$N喝道：「$n，看招！」\n" NOR,});

string *winner_msg = ({
	CYN "\n$N哈哈大笑，说道：承让了！\n\n" NOR,
	CYN "\n$N双手一拱，笑著说道：承让！\n\n" NOR,
	CYN "\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR,
	CYN "\n$n脸色微变，说道：佩服，佩服！\n\n" NOR,
	CYN "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR,
	CYN "\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
});
string *diamond_effect_msg = ({
	HIW "$n盔甲上镶嵌的钻石发挥了作用，抵挡住了$N的部分攻击！\n" NOR,
	HIW "只见白光闪过，$N的攻击力似乎有所减弱。\n" NOR,
	HIW "$N的攻击落在$n身上显得软弱无力，无甚威胁！\n" NOR,
});
void create()
{
	seteuid(getuid());
	set("name", "战斗精灵");
	set("id", "combatd");
}
//造成伤害的信息
string damage_msg(int damage, string type)
{
	string str;

	if( damage == 0 ) return "结果没有造成任何伤害。\n";

	switch( type )
	{
	case "擦伤":
	case "割伤":
		if( damage < 10 ) return "结果只是轻轻地划破$p的皮肉。\n";
		else if( damage < 20 ) return "结果在$p$l划出一道细长的血痕。\n";
		else if( damage < 40 ) return "结果「嗤」地一声划出一道伤口！\n";
		else if( damage < 80 ) return "结果「嗤」地一声划出一道血淋淋的伤口！\n";
		else if( damage < 160 ) return "结果「嗤」地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
                else return "结果只听见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！！\n";
		break;
	case "刺伤":
		if( damage < 10 ) return "结果只是轻轻地刺破$p的皮肉。\n";
		else if( damage < 20 ) return "结果在$p$l刺出一个创口。\n";
		else if( damage < 40 ) return "结果「噗」地一声刺入了$n$l寸许！\n";
		else if( damage < 80 ) return "结果「噗」地一声刺进$n的$l，使$p不由自主地退了几步！\n";
                else if( damage < 160 ) return "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉□糊的血窟窿！\n";
                else return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！！\n";
		break;
	case "瘀伤":
		if( damage < 10 ) return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
		else if( damage < 20 ) return "结果在$p的$l造成一处瘀青。\n";
		else if( damage < 40 ) return "结果一击命中，$n的$l登时肿了一块老高！\n";
		else if( damage < 80 ) return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n";
		else if( damage < 120 ) return "结果「砰」地一声，$n退了两步！\n";
		else if( damage < 160 ) return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n";
		else if( damage < 240 ) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
		else return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！！\n";
		break;
	case "内伤":
		if( damage < 10 ) return "只是把$n打得退了半步，毫发无损。\n";
		else if( damage < 20 ) return "$n痛哼一声，在$p的$l造成一处瘀伤。\n";
		else if( damage < 30 ) return "一击命中，把$n打得痛得弯下腰去！\n";
		else if( damage < 40 ) return "$n闷哼了一声，脸上一阵青一阵白，显然受了点内伤！\n";
		else if( damage < 60 ) return "$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n";
		else if( damage < 70 ) return "重重地击中，$n「哇」地一声吐出一口鲜血！\n";
		else if( damage < 80 ) return "「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n";
		else return "只听见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！！\n";
		break;
	case "点穴"://增加点穴伤害pal
       		if( damage < 10 ) return "结果只是轻轻的碰到$n的$l根本没有点到穴道。\n";
        	else if( damage < 20 ) return "结果$n痛哼一声，在$p的$l造成一处淤青。\n";
        	else if( damage < 40 ) return "结果一击命中，$w点中了$n$l上的穴道,$n只觉一阵麻木！\n";
        	else if( damage < 80 ) return "结果$n闷哼了一声，脸上一阵青一阵白，登时$l麻木！\n";
         	else if( damage < 160 ) return "结果$n脸色一下变得惨白，$w点中$n$l的穴道,一阵疼痛遍布整个$l！\n";
        	else if( damage < 240 ) return "结果$n一声大叫,$l的穴道被点中,疼痛直入心肺！\n";
        	else return "结果只听见$n一声惨叫,一阵剧痛夹杂着麻痒游遍全身,跟着直挺挺的倒了下去.\n";
        	break;
	case "抓伤":
        	if( damage < 10 ) return "结果只是轻轻地抓到，比抓痒稍微重了点。\n";
        	else if( damage < 20 ) return "结果在$p的$l抓出几条血痕。\n";
        	else if( damage < 40 ) return "结果一抓命中，$n的$l被抓得鲜血飞溅！\n";
        	else if( damage < 80 ) return "结果「嗤」地一声，$l被抓得深可见骨！！\n";
        	else if( damage < 120 ) return "结果一抓命中，$n的$l被抓得血肉横飞！！！\n";
        	else if( damage < 160 ) return "结果这一下「嗤」地一声抓得$n连晃好几下，差一点摔倒！\n";
        	else if( damage < 240 ) return "结果$n哀号一声，$l被抓得筋断骨折！！\n";
        	else return "结果只听见$n一声惨嚎，$l被抓出五个血窟窿！鲜血溅得满地！！\n";
		break;
        case "反弹伤":
                if( damage < 5 ) return "$N受到$n奋力反震，闷哼一声。\n";
                else if( damage < 10 ) return "$N被$n的胸膛震得气血翻腾，大惊失色。\n";
                else if( damage < 20 ) return "$N被$n的小腹震得站立不稳，摇摇晃晃。\n";
                else if( damage < 40 ) return "$N被$n以内力反震，「嘿」地一声退了两步。\n";
                else if( damage < 80 ) return "$N被$n的小腹反弹回来的力量震得半身发麻。\n";
                else if( damage < 120 ) return "$N被$n的反弹力一震，胸口有如受到一记重击，连退了五六步！\n";
                else if( damage < 160 ) return "$N被$n的内力劲风一震，眼前一黑，身子向後飞出丈许！！\n";
                else return "$N被$n的内力劲风一震，眼前一黑，狂吐鲜血，身子象断了线的风筝向後飞去！！\n";
                break;
    	default:
		if( !type ) type = "伤害";
		if( damage < 10 ) str =  "结果只是勉强造成一处轻微";
		else if( damage < 20 ) str = "结果造成轻微的";
		else if( damage < 30 ) str = "结果造成一处";
		else if( damage < 50 ) str = "结果造成一处严重";
		else if( damage < 80 ) str = "结果造成颇为严重的";
		else if( damage < 120 ) str = "结果造成相当严重的";
		else if( damage < 170 ) str = "结果造成十分严重的";
		else if( damage < 230 ) str = "结果造成极其严重的";
		else str =  "结果造成非常可怕的严重";
		return str + type + "！\n";
	}
}

//受攻击者看到的自己的状态
string eff_status_msg(int ratio)
{
	if( ratio==100 ) return HIG "看起来气血充盈，并没有受伤。" NOR;
	if( ratio > 95 ) return HIG "似乎受了点轻伤，不过光从外表看不大出来。" NOR;
	if( ratio > 90 ) return HIY "看起来可能受了点轻伤。" NOR;
	if( ratio > 80 ) return HIY "受了几处伤，不过似乎并不碍事。" NOR;
	if( ratio > 60 ) return HIY "受伤不轻，看起来状况并不太好。" NOR;
	if( ratio > 40 ) return HIR "气息粗重，动作开始散乱，看来所受的伤著实不轻。" NOR;
	if( ratio > 30 ) return HIR "已经伤痕累累，正在勉力支撑著不倒下去。" NOR;
	if( ratio > 20 ) return HIR "受了相当重的伤，只怕会有生命危险。" NOR;
	if( ratio > 10 ) return RED "伤重之下已经难以支撑，眼看就要倒在地上。" NOR;
	if( ratio > 5  ) return RED "受伤过重，已经奄奄一息，命在旦夕了。" NOR;
	return RED "受伤过重，已经有如风中残烛，随时都可能断气。" NOR;
}

//他人看到的受攻击者的状态
string status_msg(int ratio)
{
	if( ratio==100 ) return HIG "看起来充满活力，一点也不累。" NOR;
	if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
	if( ratio > 90 ) return HIY "看起来可能有些累了。" NOR;
	if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
	if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
	if( ratio > 40 ) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
	if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑著不倒下去。" NOR;
	if( ratio > 20 ) return HIR "看起来已经力不从心了。" NOR;
	if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
	return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}

//报告状态的函数，由effective控制消息发给谁
varargs void report_status(object ob, int effective)
{
	if( effective )
		combat_msg( "( $N" + eff_status_msg(
			(int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi") )
			+ " )\n",2, ob);
	else
		combat_msg( "( $N" + status_msg(
			(int)ob->query("qi") * 100 / (int)ob->query("max_qi") )
			+ " )\n",2, ob);
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
//这里修改经验等对ap,dp的影响
varargs int skill_power(object ob, string skill, int usage)
{
	int status, level, power,value,ratio,enemy_num;

	if( !living(ob) ) return 0;

	level = ob->query_skill(skill);

//Pal Add for env set attack
	if (!intp(ratio=ob->query("env/attack"))) ratio=50;
	if (ratio<1) ratio=1;
	if (ratio>99) ratio=100;

	switch(usage)
	{
	case SKILL_USAGE_ATTACK:
		level += ob->query_temp("apply/attack");
//这里是set attack 后的算法，讨论后再决定
//		level += level*(ratio-50)/150;
		break;
	case SKILL_USAGE_DEFENSE:
		level += ob->query_temp("apply/defense");
		if (ob->is_fighting())
			//dodge 100的话就翻倍，是不是太高了？
			level = level * (100 + ob->query_temp("fight/dodge")) / 100;
//		level += level*(50-ratio)/150;
		break;
	}
/****************************************************************************

	if( !level ) return (int)ob->query("combat_exp") / 2;

	// here need a modification later
     	power = (level/3)*level*level;

	if (usage == SKILL_USAGE_ATTACK)
		return ((power+ob->query("combat_exp"))/30)*ob->query_str();
	else
		return ((power+ob->query("combat_exp"))/30)*ob->query_dex();

modified by icer
考虑到轻功为负值时，dp应该降低；经验为0时，应由先天属性决定skill_power，修改返回值如下:
（此公式可能需要修改，以防溢出）
*****************************************************************************/
 	if( !level ) return (int)ob->query("combat_exp") / 50;

    power = (int)(level/300)*level*level;
    power = power + (int)ob->query("combat_exp")/300;

	if (power <= 0) power = 1;


//避免溢出规定上限。mudy
	if (usage == SKILL_USAGE_ATTACK)
	{
		value=(int)power*ob->query_str()/5;
		if(value<0||value>2100000000) value=2100000000;
		return value;
	}
	else
	{
		value=(int)power*ob->query_dex()/5;
		//一打多的时候降自己dp。Pal
		enemy_num=(int)sizeof(ob->query_enemy());
//		printf("enemy_num:%d\n",enemy_num);
       		value=to_int(value/(0.95+(enemy_num*enemy_num)/20.0));

		if(value<0||value>2100000000) value=2100000000;
		return value;
	}
}

void winner_reward(object killer, object victim)
{
	object owner;
	mapping your,wsquest;
	int exp,pot,bonus,score;
	your = victim->query_entire_dbase();

        if ( killer->query_temp("killing") != victim->query("id") )
		{
			killer->remove_enemy(victim);
//			victim->remove_enemy(me);
//			message_vision( winner_msg[random(sizeof(winner_msg))], killer, victim);
			tell_object(killer,"\n你战胜了"+victim->query("name")+"!\n");
                        if(killer->query("quest/type") == "win"
                           && killer->query("quest/name") == victim->name(1)
	        	   && !userp(victim))
                        killer->set("quest/finish",1);
		}
		if(owner=killer->query_temp("owner")) killer = owner;
		killer->defeated_enemy(victim);


		if( interactive(killer) && (wsquest = killer->query("wsquest"))
			&& ( (int)killer->query("task_time") >= time())
			&& (victim->name() == wsquest["quest"])
			&& (wsquest["quest_type"] == "胜")
			&& !userp(victim)
			&& (!killer->query("over_time")))
		{
//			tell_object(killer,"你战胜了"+victim->name()+"!\n");
			exp = wsquest["exp_bonus"] + random(wsquest["exp_bonus"]);
			pot = wsquest["pot_bonus"] + random(wsquest["pot_bonus"]);
			if (killer->query("wsquest_number")/4<5)
			{
				exp += exp*killer->query("wsquest_number")/2;
				pot += pot*killer->query("wsquest_number")/2;
			}
			else
			{
				exp += exp*10;
				pot += pot*10;
			}
			killer->set("task_time", (int) time());
			score = 1;
			tell_object(killer,"恭喜你！你又完成了一项任务！\n");
			bonus = (int) killer->query("combat_exp");
			bonus += exp;
			killer->set("combat_exp", bonus);
			bonus = (int) killer->query("potential");
			bonus = bonus - (int) killer->query("learned_points");
			bonus = bonus + pot;
//			if( bonus > 500) bonus = 500;
			bonus += (int) killer->query("learned_points");
			killer->set("potential", bonus );
			bonus = (int) killer->query("score");
			bonus += score;
			killer->set("score", bonus);
			tell_object(killer,HIW"你被奖励了：\n" + chinese_number(exp) + "点实战经验\n"+chinese_number(pot) + "点潜能\n" NOR);
                        killer->set("wsquest", 0 );
		}
}

void killer_reward(object killer, object victim)
{ 
    object where,where2;
    int bls,check,score,badscore;
    string vmark;
    object killer_ob,victim_ob;
    object owner,jujing,feilong,mengzhu;
    int bonus, exp, i, msize, pot,shen,kill_ya;
    object *mem;
    mapping wsquest;

    float shaqi;
    string name1,name2,name3;
    where = environment(killer);
    where2= environment(victim);
    if(owner=killer->query_temp("owner")) killer = owner;

    killer->set_temp("killer_ok",1);
    // Call the mudlib killer apply.
    killer->killed_enemy(victim);
    if(!( jujing = find_living("jujing")) )
        jujing = load_object("/clone/npc/jujing");
    name1 = jujing->query("winner");
    if(!( feilong = find_living("feilong")) )
        feilong = load_object("/clone/npc/feilong");
    name2 = feilong->query("winner");
    if(!( mengzhu = find_living("mengzhu")) )
        mengzhu = load_object("/clone/npc/meng-zhu");
    name3 = mengzhu->query("winner");

    if( userp(victim) ) {
        write_file("/log/static/kill_player",sprintf("%s(%s) killed by %s(%s) on %s\n",
                    victim->name(1), victim->query("id"),
                    killer->name(1),killer->query("id"),ctime(time()) ));

    if( killer->query("pker")
        && killer->query("deathname")==victim->query("id")
        && !killer->query("accomplish1")&&!killer->query("accomplish2")
        && !where->query("no_die")
        && !where2->query("no_die")
        && !where->query("no_death")
        && !where2->query("no_death"))
    {
         if(victim->query("id")==name1||victim->query("id")==name2||victim->query("id")==name3)
            message("vision",YEL ""+victim->query("name")+"目前尚有帮主之位，你的任务尚未完成!\n" NOR,killer);
         else
         {
             message("vision",HIR "看着"+victim->query("name")+"在你面前慢慢的倒下，慢慢的流血,慢慢的抽搐\n"+
             "慢慢的死去，你知道自己终于完成了楚帮主的任务!\n在这个弱肉强食的世界上，你成为了胜利者.....\n" NOR,killer);
             victim->set("pked/be_pked","pker");
             if(killer->query("pk_level")==1)
                 killer->set("accomplish1",1);
             else
                 killer->set("accomplish2",1);
         }
    }
    if( victim->query_leader() != killer ) killer->add("PKS", 1);
    if (userp(killer) && (killer->query_temp("killing") == victim->query("id")) && (victim->query_leader() != killer) )
        {
            killer->add_temp("kill_amount",1);
            shaqi = killer->query("combat_exp")/(victim->query("combat_exp") + 1);
            if( shaqi < 1 )         shaqi = 1;
            shaqi = exp( log(shaqi) / 3 ) * 10;
            shaqi = shaqi * (killer->query_temp("kill_amount") + 5) / 5;
            if (shaqi > 100)        shaqi = 100;
            if (shaqi < 10)         shaqi = 10;
            if (victim->query_leader() == killer) shaqi = 0;
            killer->add("shaqi", (int)(shaqi / 5));
        }

        if (!environment(victim)->query("no_die") && !environment(victim)->query("no_death") ) victim->clear_condition();
        // Give the death penalty to the dying user.
        victim->add("shen", -(int)victim->query("shen") / 10);
        victim->delete("vendetta");
        victim->set("eff_qi", victim->query("max_qi"));
        victim->set("qi", 1);
        victim->set("eff_jing", victim->query("max_jing"));
        victim->set("jing", 1);
        victim->set("neili", 0);
        //icer added to avoid killing in biwuchang adding PKS
        if(environment(victim)->query("no_die") || environment(victim)->query("no_death")) 
        {  
            killer->add("PKS",-1);
        }
        else if( victim->query("mud_age") > 86400 )
        {
            victim->add("combat_exp", -(int)victim->query("combat_exp") / 50);
            if( (int)victim->query("potential") > (int)victim->query("learned_points"))
                victim->add("potential",
                    ((int)victim->query("learned_points") - (int)victim->query("potential"))/2 );
            victim->skill_death_penalty();
        }
        else 
        {
            victim->add("combat_exp",-random(20));
            if(victim->query("combat_exp")<0) victim->set("combat_exp",0);
            if( (int)victim->query("potential") > (int)victim->query("learned_points"))
                victim->add("potential",-random(6));
            if( (int)victim->query("potential") <=(int)victim->query("learned_points"))
                victim->set("potential",victim->query("learned_points"));
        }
        if( victim->query("thief") )
            victim->set("thief", (int)victim->query("thief") / 2);
        victim->delete_temp("pk_exp");
        bls = 10;
        if( killer->query_temp("apply/name") )
        {
            CHANNEL_D->do_channel(this_object(), "rumor",
                    sprintf("%s被" + killer->query_temp("apply/name")[0] + "杀死了。",victim->name(1)));
            write_file("/log/static/player_dead",sprintf("%s(%s) killed by %s on %s\n",
                        victim->name(1), victim->query("id"),
                        killer->name(1),ctime(time()) ));
        }
        else if (userp(killer))
        {
            write_file("/log/static/pk_log",sprintf("%s(%s) killed by %s(%s) on %s\n",
                victim->name(1), victim->query("id"),
                killer->name(1),killer->query("id"),ctime(time()) ));
                //加入门派追杀
            if (!environment(killer)->query("no_die") && !environment(killer)->query("no_death"))
                bijiao(killer,victim);
                // add by chui
                victim->add("fhost",1);
            }

        // End of apprendence
        if (!killer->query_temp("apply/name"))
            CHANNEL_D->do_channel(this_object(), "rumor",
                    sprintf("%s被%s杀死了。", victim->name(1), killer->name(1)));

        if( victim->query_temp("apply/name") )
        {
            victim->delete_temp("apply/name");
            victim->delete_temp("apply/id");
            victim->delete_temp("apply/short");
            victim->delete_temp("apply/long");
            killer->add("shen",2000);
            return;
        }
    } else {
        killer->add("MKS", 1);
        // add by chui
        victim->add("ghost",1);
        if ( killer->query_temp("killing") == victim->query("id") )
            killer->add("shaqi", 2);
        F_NEWQUEST->quest_kill(victim,killer);
        //write(killer->query("quest/name"));write(victim->query("name"));write(killer->query("quest/id"));write(victim->query("id"));
        if(victim->query("kill_id")==killer->query("id"))
            killer->delete_temp("pk_exp");
        bls = 1;
        if(killer->query("quest/type") == "kill"
                && killer->query("quest/name") == victim->name(1)
                && !userp(victim))
            killer->set("quest/finish",1);
    }
    if ( killer->query_temp("killing") == victim->query("id") )
    {
        if (killer->query("shaqi") < 400)
            tell_object(killer, HIR"你的杀气增加了！\n"NOR);
        //                write("3\n");
        if ((killer->query("shaqi") >= 400) && (killer->query("shaqi") < 500))
            tell_object(killer, HIR"你心中充满了杀气，只想再找几个人杀杀！\n"NOR);
    }
    if(userp(killer) && killer->query("family") &&
            killer->query("family/family_name") == victim->query("family/family_name"))
    {        score =killer->query("score");
        check = -victim->query("combat_exp")/(1+killer->query("combat_exp"))*50;
        if ((score<-100000) || (check<-100000))
        {
            killer->add("score",check);
        };
        if(victim->query("combat_exp")/(1+killer->query("combat_exp"))*50>0)
            tell_object(killer,HIR"由于你残害同门，你的师门忠诚度降低了！！\n"NOR);
    }
    else if (!wizardp(killer) && !wizardp(victim) &&
            killer->query("family") && victim->query("family") )
        write("2\n");
    if (userp(killer) && killer->query("combat_exp") < victim->query("combat_exp"))
        killer->add("shen", -(int)victim->query("shen") / 10);
    if( stringp(vmark = victim->query("vendetta_mark")) )
        killer->add("vendetta/" + vmark, 1);
    if (userp(victim))
    {
        victim->save();
    }


    // for quest --pal
    if( interactive(killer) && (wsquest = killer->query("wsquest")) && ( (int)killer->query("task_time") >= time()) && (victim->name() == wsquest["quest"]) && !userp(victim)&& (wsquest["quest_type"] == "杀"))
    {
        exp = wsquest["exp_bonus"] + random(wsquest["exp_bonus"]);
        pot = wsquest["pot_bonus"] + random(wsquest["pot_bonus"]);
        if (killer->query("wsquest_number")/4 < 5)
        {
            exp += exp*killer->query("wsquest_number")/2;
            pot += pot*killer->query("wsquest_number")/2;
        }
        else
        {
            exp += exp*10;
            pot += pot*10;
        }
        killer->set("wsquest", 0 );
        score = 1;
        killer->set("task_time", (int) time());
        tell_object(killer,"恭喜你！你又完成了一项任务！\n");
        bonus = (int) killer->query("combat_exp");
        bonus += exp;
        killer->set("combat_exp", bonus);
        bonus = (int) killer->query("potential");
        bonus = bonus - (int) killer->query("learned_points");
        bonus = bonus + pot;
        //                  if( bonus > 1000) bonus = 1000;
        bonus += (int) killer->query("learned_points");
        killer->set("potential", bonus );
        bonus = (int) killer->query("score");
        bonus += score;
        killer->set("score", bonus);
        tell_object(killer,HIW"你被奖励了：\n" + chinese_number(exp) + "点实战经验\n"+chinese_number(pot) + "点潜能\n" NOR);
    }

}


// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type, string attack_msg)
{
	mapping my, your, prepare, action;
	string limb, *limbs, result;
	string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
	mixed foo;
	object report_ob, ob, armor;
        int ap, dp, pp;
        int damage, damage_bonus;
        int defense_factor;
	int cost, magic, kar;
	int wounded = 0;
//取消此限制	//战斗获得经验的几率，按random(ExpTopChance)>expchance计算，即1 - expchance/ExpTopChance
//取消此限制	//去掉了战斗涨经验上限的限制，当经验>ExpTopChance*ExpTopChance*10时，涨经验几率为1/EXTOPCHANCE
//	int expchance;	//sqrt(combat_exp/10)
//	int expnow;
//	int ExpTopChance = 500;
//取消此限制	//战斗方式最大可以达到的潜能
	int MaxCombatPot = 600;

	if(!me
	|| !victim
	||  environment(me) != environment(victim))
		return 1;
	my = me->query_entire_dbase();
	your = victim->query_entire_dbase();
	//
	// (0) Choose skills.
	//
	prepare = me->query_skill_prepare();
	if (!prepare) prepare = ([]);
	if( objectp(weapon) )	attack_skill = weapon->query("skill_type");
	else if ( sizeof(prepare) == 0)	attack_skill = "unarmed";
	else if ( sizeof(prepare) == 1)	attack_skill = (keys(prepare))[0];
	else if ( sizeof(prepare) == 2)	attack_skill = (keys(prepare))[me->query_temp("action_flag")];
	martial_skill = me->query_skill_mapped(attack_skill);
	if(martial_skill)
	{
	action=me->query("actions");
	//加入暗器，在工夫里把action写成skip_action就会忽略原来的战斗系统，调用功夫里的hit_ob,加入新暗器可以参照/kungfu/skill/guishoushe.c。
	if (action)
	if(action["action"]=="skip_action")
	{
		if(my["neili"]>=my["jiali"])
		{
			me->add("neili",0-my["jiali"]);
			SKILL_D(martial_skill)->hit_ob(me, victim, my["jiali"]);
		}
		else
		{
			me->set("neili",0);
			SKILL_D(martial_skill)->hit_ob(me, victim, my["neili"]);
		}

 		if(random(2)>0)
 		{
                	if( random(my["dex"]) < 5 )
                	{
				combat_msg("$N瞅准$n一个破绽，发动反击！\n",1,victim, me);
				do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
			}
			else
			{
				combat_msg("$N以攻为守，向$n使出看家本领！\n",1, victim, me);
				do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
			}
		}
		return 1;
	}
	}




	//
	// (1) Find out what action the offenser will take.
	//
        me->reset_action();
	action = me->query("actions");
	if( !mapp(action) ) {
	//      me->reset_action();
		action = me->query("actions");
		if( !mapp(action) ) {
			CHANNEL_D->do_channel( this_object(), "sys",
				sprintf("%s(%s): bad action = %O",
					me->name(1), me->query("id"), me->query("actions", 1)));
			return 0;
		}
	}

	if (me->query_temp("action_flag") == 0)
		result = "\n" + action["action"] + "！\n" + NOR;
	else
		result = "\n" + "紧跟着"+action["action"] + "!\n";

       if(stringp(attack_msg)) result = "\n" + attack_msg + "\n";

	//
	// (2) Prepare AP, DP for checking if hit.
	//
	limbs = victim->query("limbs");
	limb = limbs[random(sizeof(limbs))];

	ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
	//经过修改后skill_power()返回的ap已经不可能小于1，但仍保留此句，dp,pp同理
	if( ap < 1) ap = 1;
	if( victim->query_temp("combat_factor") )
		ap = to_int(ap * victim->query_temp("combat_factor"));

	if (userp(me) && intp(action["dodge"]))
		me->set_temp("fight/dodge", action["dodge"]);

	dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
	if( dp < 1 ) dp = 1;
//取消此限制	//计算expchance
//取消此限制	//只以user的exp为标准，如果双方都为npc，则取victim的exp
//	if (userp(me))
//		expnow = my["combat_exp"];
//	else	expnow = your["combat_exp"];
//	if (expnow < 0) expnow = 0;
//	expchance = to_int(sqrt(to_float(expnow/10)));
//	if (expchance >= ExpTopChance) expchance = ExpTopChance - 1;
	//
	// (3) Fight!
	//     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
	//     AP and DP are greater than zero, so we always have chance to hit
	//     or be hit.
	//
	if( random(ap + dp) < dp ) { 		// Does the victim dodge this hit?
		dodge_skill = victim->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		result += SKILL_D(dodge_skill)->query_dodge_msg(limb);

//		if( dp < ap && random(ExpTopChance) >= expchance && (!userp(victim) || !userp(me))
		if( dp < ap && (!userp(victim) || !userp(me))
		&&	random(your["jing"]*100/your["max_jing"] + your["int"]) > 50 ) {
			your["combat_exp"] += 1;
			victim->improve_skill("dodge", 1);
		}

		// This is for NPC only. NPC have chance to get exp when fail to hit.
//		if( (ap < dp) && random(ExpTopChance) >= expchance && !userp(me) ) {
		if( (ap < dp) && !userp(me) ) {
			if( random(my["int"]) > 15 ) my["combat_exp"] += 1;
			me->improve_skill(attack_skill, random(my["int"]));
		}
		damage = RESULT_DODGE;

	} else {

		//
		//	(4) Check if the victim can parry this attack.
		//
		if( victim->query_temp("weapon") ) {
			pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
			if( !weapon ) pp *= 2;
		} else {
			if( weapon ) pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE) / 10;
			else
			{
				pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
				pp = pp * 2 / 3;
			}
		}

		if( victim->is_busy() ) pp /= 3;
		if( pp < 1 ) pp = 1;

		if( random(ap + pp)< pp ) {

			//Vast增加武器的相互碰撞损耗(武器对武器时的格挡)
			if(weapon && ob = victim->query_temp("weapon"))
			{
        			ob->add("rigidity", -1);
        			weapon->add("rigidity", -1);
        			if(ob->query("rigidity") < 1 || weapon->query("rigidity") < 1)
        			{
        			if(ob->query("rigidity") < 1)
        			{
        			result += HIW "（只听见「啪」地一声，$n手中的" + ob->name() + "已经断为两截！）\n" NOR;
        			ob->unequip();
        			ob->move(environment(victim));
        			ob->set("name", "断掉的" + ob->query("name"));
        			ob->set("value", 0);
        			ob->set("weapon_prop", 0);
        			victim->reset_action();
        			}
        			if(weapon->query("rigidity") < 1)
        			{
        			result += HIW "（只听见「啪」地一声，$N手中的" + weapon->name() + "已经断为两截！）\n" NOR;
        			weapon->unequip();
        			weapon->move(environment(me));
        			weapon->set("name", "断掉的" + weapon->query("name"));
        			weapon->set("value", 0);
        			weapon->set("weapon_prop", 0);
        			me->reset_action();
        			}
				}
				else
				result += WHT"（$N的" + weapon->name() + "和$n的" + ob->name() + "相击，冒出点点的火星。）\n"NOR;
			}


			parry_skill = victim->query_skill_mapped("parry");
			if( !parry_skill ) parry_skill = "parry";
			// change to SKILL_D(parry_skill) after added parry msg to those
			// martial arts that can parry.
       	if( !find_object(SKILL_D(parry_skill)) && file_size(SKILL_D(parry_skill)+".c") < 0)//判断是否是自创武功
		{
			result += PLAYER_SKILL_D(parry_skill)->query_parry_msg(victim->query_temp("weapon"));
		}
        else
			result += SKILL_D(parry_skill)->query_parry_msg(victim->query_temp("weapon"));

//			if( dp < ap && random(ExpTopChance) >= expchance && (!userp(victim) || !userp(me))
			if( dp < ap && (!userp(victim) || !userp(me))
			&&	random(your["jing"]*100/your["max_jing"] + your["int"]) > 50 ) {
					your["combat_exp"] += 1;
				victim->improve_skill("parry", 1);
			}
			damage = RESULT_PARRY;

		} else {

			//
			//	(5) We hit the victim and the victim failed to parry
			//

			damage = me->query_temp("apply/damage");
			damage = (damage + random(damage)) / 2;
			if( action["damage"] )
				damage += action["damage"] * damage / 100;

			damage_bonus = me->query_str();

			// Let force skill take effect.
			if( my["jiali"] && (my["neili"] > my["jiali"]) ) {
				if( force_skill = me->query_skill_mapped("force") ) {
					foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["jiali"]);
					if( stringp(foo) ) result += foo;
					else if( intp(foo) ) damage_bonus += foo;
				}
			}

			if( action["force"] )
				damage_bonus += action["force"] * damage_bonus / 100;

			if( martial_skill = me->query_skill_mapped(attack_skill) ) {
       		if( !find_object(SKILL_D(martial_skill)) && file_size(SKILL_D(martial_skill)+".c") < 0)//判断是否是自创武功
				 foo = PLAYER_SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
			else foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}

			// Let weapon or monster have their special damage.
			if( weapon ) {
				foo = weapon->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			} else {
				foo = me->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}

			//身上的盔甲要起作用哦，嘿嘿(damage修正,不是damage_bonus)---for Gems System
			if (armor = victim->query_temp("armor/armor")) {
				foo = armor->ob_hit(me, victim, damage);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage += foo;
			}

			if( damage_bonus > 0 )
				damage += (damage_bonus + random(damage_bonus))/2;

			//增加设置一个参数 here for Gems System  -----   Vast
                	//成功率(可能设定简单了一点)
                	magic = victim->query_temp("apply/magic");
                	kar = victim->query_kar();
                	if (kar > 40) kar = 40;
			if(victim->query_temp("apply/armor_vs_weapon") && (random(100) + kar / 5 + kar * magic / 1000 > 90) )
			{
				damage -= victim->query_temp("apply/armor_vs_weapon");
				result += diamond_effect_msg[random(sizeof(diamond_effect_msg))];
			}

			if( damage < 0 ) damage = 0;

			// Let combat exp take effect
			defense_factor = your["combat_exp"];
			while( random(defense_factor) > my["combat_exp"] ) {
				damage -= damage / 3;
				defense_factor /= 2;
			}

			//qiankun-danuoyi's damage

	                absorb_skill = victim->query_skill_mapped("parry");

			if(absorb_skill == "qiankun-danuoyi" && !me->query("no_use/qiankun-danuoyi"))
			{
	                	jibie =(int)victim->query_skill("qiankun-danuoyi",1);
                                jibie = jibie * 4 /5;
                                randnum = (int)random(victim->query("combat_exp"))/100*jibie;
	                        qdamage = damage*(jibie/150) + jibie/2;//这个是否有些夸张？--vast
	                        if (qdamage > 2000) qdamage = 2000; //vast暂时设置上限
			   	if( randnum > (int)me->query("combat_exp") )
			  	{
	                                if (victim->query("neili") > qdamage/10)
	                                {
		                                //以下暂时用于监视挪移的伤害力，测试无误可以删除---vast
	        				if( (wizardp(victim) || wizardp(me))
	        				&& ( (string)me->query("env/combat")=="verbose"
	        				|| (string)victim->query("env/combat")=="verbose" ))
	        				{
		                                	wizardp(me)?report_ob = me : report_ob = victim;
		                                	tell_object(report_ob, "nuoyi damage : " + qdamage + "。\n");
		                                }
	
						me->receive_damage("qi", qdamage,victim);
		      	          		me->receive_wound("qi", qdamage/3,victim);
						victim->add("neili", -qdamage/10);
						result += HIR "$n的乾坤大挪移自然激发而出，将$N的攻势反击了回去。\n" NOR;
					        result += damage_msg(qdamage, "反弹伤");
		                               	qdamage=0;
						damage = 0;
					        victim->set_temp("反震成功",1);
					}
				}
	   		       	else if( randnum > (int)me->query("combat_exp")/2 )
				{
	                                if (victim->query("neili") > qdamage/15)
	                                {
						victim->add("neili", -qdamage/15);
						damage = 0;
					        result += HIC "$n的乾坤大挪移自然激发而出，将$N的攻势移了开去。\n" NOR;
					}
				}
		               	else if( randnum > (int)me->query("combat_exp")/4 )
	                        {
	                                if (victim->query("neili") > qdamage/15)
	                                {
						victim->add("neili", -qdamage/15);
						damage = damage/2;
					        result += GRN "$n的乾坤大挪移自然激发而出，将$N的攻势大半移了开去。\n" NOR;
					}
				}
			}
			else	//挪移与铁布衫不能同时生效
			{
		                //
				//	(5.5) Check if victim can absorb the damage
				//
				absorb_vic = 0;
		                if( victim->query_skill("iron-cloth") && !me->query("no_use/iron-cloth"))
				{
					absorb_vic = victim->query_skill("iron-cloth");
	                		absorb_skill = victim->query_skill_mapped("iron-cloth");
	                		if( !absorb_skill ) absorb_skill = "iron-cloth";
	                		result += SKILL_D(absorb_skill)->query_absorb_msg();
	                        }
	                        if ((damage - absorb_vic * 1.3 - random(absorb_vic) )< 0 )
				{
					damage = damage - absorb_vic * 1.3 - random(absorb_vic);
					qdamage = absorb_vic * 1.3 + random(absorb_vic);
					if (victim->query("neili") > qdamage/15)
					{
		                        	if ( damage < 0 ) damage = 0 - damage;
		                        	me->receive_damage("qi", damage, victim );
						result += damage_msg(damage, "反弹伤");
		                        	victim->set_temp("反震成功",1);
		                        	damage=0;
		                        	victim->add("neili",-qdamage/15);
		                        }
	                       	}
	                }
	                if (!victim->query_temp("反震成功"))
			{
				//
				//	(6) Inflict the damage.
				//
				damage = victim->receive_damage("qi", damage, me );
				if( random(damage) > (int)victim->query_temp("apply/armor")
					&& ( (me->is_killing(victim->query("id")))
					&& ((!weapon) && !random(4) || weapon && !random(2) )
			    		|| ( (!weapon) && !random(7) || weapon && !random(4) ) )  )
				{
					// We are sure that damage is greater than victim's armor here.
					victim->receive_wound("qi",damage - (int)victim->query_temp("apply/armor"), me);
					wounded = 1;
				}
				result += damage_msg(damage, action["damage_type"]);
                         }
			//
			//	(7) Give experience,when exp is higher then 400M,limit it
			//
			if( (!userp(me) || !userp(victim)))
			{
//				if( (ap < dp) && random(ExpTopChance) >= expchance
				if( (ap < dp)
				&&	(random(my["jing"]*100/my["max_jing"] + my["int"]) > 30) )
				{
                                        my["combat_exp"] += 1;
					if( my["potential"] - my["learned_points"] < MaxCombatPot )
                                                my["potential"] += 1;
					me->improve_skill(attack_skill, 1);
				}
//				if( random(your["max_qi"] + your["qi"]) <damage&& random(ExpTopChance) >= expchance ) {
				if( random(your["max_qi"] + your["qi"]) <damage ){
                                        your["combat_exp"] += 1;
					if( your["potential"] - your["learned_points"] < MaxCombatPot )
                                                your["potential"] += 1;
				}
			}
		}
	}

	result = replace_string( result, "$l", limb );

	if( victim->query_temp("weapon"))
	result = replace_string( result, "$v", victim->query_temp("weapon")->name() );

	if( objectp(weapon) )
		result = replace_string( result, "$w", weapon->name() );
	else if( stringp(action["weapon"]) )
		result = replace_string( result, "$w", action["weapon"] );
	else if( attack_skill == "finger" )
		result = replace_string( result, "$w", "手指" );
	else if( attack_skill == "strike" )
		result = replace_string( result, "$w", "手掌" );
	else result = replace_string( result, "$w", "拳头" );

	combat_msg(result,0, me, victim);
        if (victim->query_temp("反震成功"))
        {
        	report_status(me , 0);
         	victim->set_temp("反震成功",0);
        }
        if( (wizardp(victim) || wizardp(me)) && ( (string)me->query("env/combat")=="verbose"  ||(string)victim->query("env/combat")=="verbose" )) {
        	wizardp(victim)?report_ob=victim:report_ob=me;
		if( damage > 0 )
			tell_object(report_ob, sprintf( GRN "AP：%d，DP：%d，PP：%d，伤害力：%d\n" NOR,
				ap/100, dp/100, pp/100, damage));
		else
			tell_object(report_ob, sprintf( GRN "AP：%d，DP：%d，PP：%d\n" NOR,
				ap/100, dp/100, pp/100));
	}
	if( damage > 0 ) {
		report_status(victim, wounded);
		if( victim->is_busy() ) victim->interrupt_me(me);
		if( (!me->is_killing(your["id"])) &&
			(!victim->is_killing(my["id"])) &&
			victim->query("qi")*2 <= victim->query("max_qi"))
		{
			me->remove_enemy(victim);
			victim->remove_enemy(me);
			message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);
//			tell_object(me,"你战胜了"+victim->query("name")+"!\n\n");
                	if(me->query("quest/type") == "win"
                           && me->query("quest/name") == victim->name(1)
			   && !userp(victim))
                         me->set("quest/finish",1);
			winner_reward(me, victim);
		}
	}

	if( functionp(action["post_action"]) )
		evaluate( action["post_action"], me, victim, weapon, damage);

	// See if the victim can make a riposte.
	if( attack_type==TYPE_REGULAR
	&&	damage < 1
	&&	victim->query_temp("guarding") ) {
		victim->set_temp("guarding", 0);
		if( random(my["dex"]) < 5 ) {
			combat_msg("$N一击不中，露出了破绽！\n",1, me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
		} else {
			combat_msg("$N见$n攻击失误，趁机发动攻击！\n",1, victim, me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
		}
	}
}

//	fight()
//
//	This is called in the attack() defined in F_ATTACK, which handles fighting
//	in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
	object ob;
	object weapon;
        int n,i;
        n = 1;

  if( !living(me) || me->query_temp("combat_yield"))
	  return;

        if( !me->visible(victim)
		&& (random(100 + (int)me->query_skill("perception")) < 100) )
		return;

         if (me->query("zyhb")) 
            n = 2;
        for (i=0;i<n;i++)
        {
         if (me->query("zyhb")&& i==1) 
                  combat_msg(HIR "$N使出「左右互搏」的绝技，左手一晃又准备出一招！\n" NOR,1, me,victim);

	// If victim is busy or unconcious, always take the chance to make an attack.
	if( victim->is_busy() || !living(victim) ) {
		me->set_temp("guarding", 0);
		if( !victim->is_fighting(me) ) victim->fight_ob(me);
		if (i == 1)
		{
			weapon = me->query_temp("secondary_weapon");
			me->set_temp("secondary_weapon",me->query_temp("weapon"));
			me->set_temp("weapon",weapon);
			me->set_temp("action_flag",1);
			do_attack(me,victim,weapon,TYPE_QUICK);
			weapon = me->query_temp("secondary_weapon");
			me->set_temp("secondary_weapon",me->query_temp("weapon"));
			me->set_temp("weapon",weapon);
			me->set_temp("action_flag",0);
		}
		else
			do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);

		if( me->is_fighting(victim) && victim->is_fighting(me))
		//互备了空手功夫，或者使用的是辟邪剑法的时候
		if((!objectp(me->query_temp("weapon"))
		   && sizeof(me->query_skill_prepare()) > 1)
		||  ( objectp(me->query_temp("weapon"))
		   &&(me->query_temp("weapon"))->query("skill_type") == "sword"
		   && me->query_skill("pixie-jian", 1) >= 60
		   && me->query_skill_mapped("sword") == "pixie-jian") )
		{

                   me->set_temp("action_flag",1);
		   do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
		   me->set_temp("action_flag",0);
	     	}
	     	//互备了兵器功夫时（以下分具体的情况）
		else if((me->query_temp("weapon"))&&(me->query_temp("secondary_weapon")))
		{
			//刀剑互备
		  if((sizeof(me->query_wprepare())>1)
                    	&&( ( ((me->query_temp("weapon"))->query("skill_type")=="blade")
                        &&((me->query_temp("secondary_weapon"))->query("skill_type")=="sword"))
                      	||(((me->query_temp("weapon"))->query("skill_type")=="sword")
                        &&((me->query_temp("secondary_weapon"))->query("skill_type")=="blade") ) ))
                          if ( (keys(me->query_wprepare())[0]=="blade") || (keys(me->query_wprepare())[1] == "blade") )
                {
                  	weapon = me->query_temp("secondary_weapon");
                   	me->set_temp("secondary_weapon",me->query_temp("weapon"));
                   	me->set_temp("weapon",weapon);
                   	me->set_temp("action_flag",1);
                   	do_attack(me,victim,weapon,TYPE_QUICK);
                   	me->set_temp("action_flag",0);
                   	weapon = me->query_temp("secondary_weapon");
	                me->set_temp("secondary_weapon",me->query_temp("weapon"));
	                me->set_temp("weapon",weapon);
                  }
                  //鞭剑互备
		  if((sizeof(me->query_wprepare())>1)
                    	&&( ( ((me->query_temp("weapon"))->query("skill_type")=="whip")
                        &&((me->query_temp("secondary_weapon"))->query("skill_type")=="sword"))
                      	||(((me->query_temp("weapon"))->query("skill_type")=="sword")
                        &&((me->query_temp("secondary_weapon"))->query("skill_type")=="whip") ) ))
                        if ( (keys(me->query_wprepare())[0]=="whip") || (keys(me->query_wprepare())[1] == "whip") )
                  {
                  	weapon = me->query_temp("secondary_weapon");
                   	me->set_temp("secondary_weapon",me->query_temp("weapon"));
                   	me->set_temp("weapon",weapon);
                   	me->set_temp("action_flag",1);
                   	do_attack(me,victim,weapon,TYPE_QUICK);
                   	me->set_temp("action_flag",0);
                   	weapon = me->query_temp("secondary_weapon");
	                me->set_temp("secondary_weapon",me->query_temp("weapon"));
	                me->set_temp("weapon",weapon);
                  }
		}
	// Else, see if we are brave enough to make an aggressive action.
	} else if( random( (int)victim->query_dex() * 3 ) > (int)me->query_str()) {
		me->set_temp("guarding", 0);
		if( !victim->is_fighting(me) ) victim->fight_ob(me);
		if (i == 1)
		{
			weapon = me->query_temp("secondary_weapon");
			me->set_temp("secondary_weapon",me->query_temp("weapon"));
			me->set_temp("weapon",weapon);
			me->set_temp("action_flag",1);
			do_attack(me,victim,weapon,TYPE_QUICK);
			weapon = me->query_temp("secondary_weapon");
			me->set_temp("secondary_weapon",me->query_temp("weapon"));
			me->set_temp("weapon",weapon);
			me->set_temp("action_flag",0);
		}
		else
			do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);

		if( me->is_fighting(victim) && victim->is_fighting(me))
		if( (!objectp(me->query_temp("weapon"))
		   && sizeof(me->query_skill_prepare()) > 1)
		   || ( objectp(me->query_temp("weapon"))
		   && (me->query_temp("weapon"))->query("skill_type") == "sword"
		   && me->query_skill("pixie-jian", 1) >= 60
		   && me->query_skill_mapped("sword") == "pixie-jian") )
		{
		   me->set_temp("action_flag",1);
		   do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
		   me->set_temp("action_flag",0);
	     	}
                else if ((me->query_temp("weapon"))&&(me->query_temp("secondary_weapon")))
	       	{
			if((sizeof(me->query_wprepare())>1)
                    		&&( ( ((me->query_temp("weapon"))->query("skill_type")=="blade")
                        	&&((me->query_temp("secondary_weapon"))->query("skill_type")=="sword"))
                      		||(((me->query_temp("weapon"))->query("skill_type")=="sword")
                        	&&((me->query_temp("secondary_weapon"))->query("skill_type")=="blade") ) ))
                          if ( (keys(me->query_wprepare())[0]=="blade") || (keys(me->query_wprepare())[1] == "blade") )
                 	{
                   		weapon = me->query_temp("secondary_weapon");
                   		me->set_temp("secondary_weapon",me->query_temp("weapon"));
                   		me->set_temp("weapon",weapon);
                   		me->set_temp("action_flag",1);
                   		do_attack(me,victim,weapon,TYPE_QUICK);
                   		me->set_temp("action_flag",0);
                   		weapon = me->query_temp("secondary_weapon");
                   		me->set_temp("secondary_weapon",me->query_temp("weapon"));
                   		me->set_temp("weapon",weapon);
                 	}
		  if((sizeof(me->query_wprepare())>1)
                    	&&( ( ((me->query_temp("weapon"))->query("skill_type")=="whip")
                        &&((me->query_temp("secondary_weapon"))->query("skill_type")=="sword"))
                      	||(((me->query_temp("weapon"))->query("skill_type")=="sword")
                        &&((me->query_temp("secondary_weapon"))->query("skill_type")=="whip") ) ))
                        if ( (keys(me->query_wprepare())[0]=="whip") || (keys(me->query_wprepare())[1] == "whip") )
                  {
                  	weapon = me->query_temp("secondary_weapon");
                   	me->set_temp("secondary_weapon",me->query_temp("weapon"));
                   	me->set_temp("weapon",weapon);
                   	me->set_temp("action_flag",1);
                   	do_attack(me,victim,weapon,TYPE_QUICK);
                   	me->set_temp("action_flag",0);
                   	weapon = me->query_temp("secondary_weapon");
	                me->set_temp("secondary_weapon",me->query_temp("weapon"));
	                me->set_temp("weapon",weapon);
                  }
		}
		// Else, we just start guarding.
	} else if( !me->query_temp("guarding") ) {
		me->set_temp("guarding", 1);
		combat_msg( guard_msg[random(sizeof(guard_msg))],1, me, victim);
		return;
	} else return;
        } // enclose of hubo
}

//	auto_fight()
//
//	This function is to start an automatically fight. Currently this is
//	used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
	// Don't let NPC autofight NPC.
	if( !userp(me) && !userp(obj) ) return;

	// Because most of the cases that we cannot start a fight cannot be checked
	// before we really call the kill_ob(), so we just make sure we have no
	// aggressive callout wating here.
	if( me->query_temp("looking_for_trouble") ) return;
	me->set_temp("looking_for_trouble", 1);

	// This call_out gives victim a chance to slip trough the fierce guys.
	call_out( "start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
	int shen;

	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	shen = 0 - (int)me->query("shen");
	message_vision("$N用一种异样的眼神扫视著在场的每一个人。\n", me);

	if( !userp(me) || (int)me->query("neili") > (random(shen) + shen)/10 ) return;

	if( shen > (int)me->query("score")
	&&	!wizardp(obj) ) {
		message_vision("$N对著$n喝道：" + RANK_D->query_self_rude(me)
			+ "看你实在很不顺眼，去死吧。\n", me, obj);
		me->kill_ob(obj);
	} else {
		message_vision("$N对著$n喝道：喂！" + RANK_D->query_rude(obj)
			+ "，" + RANK_D->query_self_rude(me) + "正想找人打架，陪我玩两手吧！\n",
			me, obj);
		me->fight_ob(obj);
	}
}

void start_hatred(object me, object obj)
{
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We found our hatred! Charge!
	message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
	me->kill_ob(obj);
}

void start_vendetta(object me, object obj)
{
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We found our vendetta opponent! Charge!
	me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We got a nice victim! Kill him/her/it!!!
	me->kill_ob(obj);
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
	switch(event) {
		case "dead":
			message_vision("\n$N死了。\n\n", ob);
			break;
		case "unconcious":
			message_vision("\n$N脚下一个不稳，跌在地上一动也不动了。\n\n", ob);
			break;
		case "revive":
			message_vision("\n$N慢慢睁开眼睛，清醒了过来。\n\n", ob);
			break;
	}
}

void bijiao(object killer,object victim)
{
        int score,mp_num;
		object *user_list;
		string *killers;
	string allstr;
        string str,pai,pai2,pai3;
        int i,j,k;
		/*********该为直接进行门派追杀，不记录hate了，否则难以维护
        if (victim->query("family/family_name") == "杀手帮"
             || !userp(victim))
             return;
//                       write("1");
        if(!(score=victim->query("score")))
           score=victim->query("combat_exp")/200+1;
        if(score<100)return;
        pai  = killer->query("family/family_name");
        pai2 = victim->query("family/family_name");
if(!pai2) {pai2="普通百姓";}
if(!pai) {pai="普通百姓";}
        str=read_file("/hate/mp_mun",1,1);
        sscanf(str,"%d",mp_num);
        str = "";
        for(i=0;i<mp_num-1;i++)
            { allstr = "";
              pai3 = "";
              allstr = read_file("/hate/"+pai2,i+1,1);
              sscanf(allstr,"%s %d",pai3,k);
              if ( pai3 == pai)
                 {
                   if(k>-1000)
                    {if(score>5000)
                       score=5000;
                     k-=score/200+1;
                     }
                   allstr = "";
                   allstr= pai3+" "+k+"\n";
                 }
             str += allstr;
            }
	write_file("/hate/"+pai2, str, 1);
	********/
	/*
	if (!victim->query("family"))
		return;
	if (victim->query("family/family_name") == killer->query("family/family_name"))
		return;
	if (killer->query_temp("zhuisha/" + victim->query("id")))	//追杀引起的pk不会引起连环追杀
	{
		killer->delete_temp("zhuisha/" + victim->query("id"));
		return;
	}
	pai = victim->query("family/family_name");
	user_list = users();
	for (i=0;i<sizeof(user_list);i++)
	{
		if ((user_list[i]->query("family/family_name") == pai)&&(user_list[i]->query("score")>500))
		{
			user_list[i]->kill_ob(killer);
			tell_object(user_list[i],HIR"你开始追杀杀害" + victim->query("name") + "的凶手" + killer->query("name") + "！\n"NOR);
			user_list[i]->set_temp("zhuisha/" + killer->query("id"),1);
		}
	}
    tell_object(killer,HIR"由于你残害"+victim->query("name")+
               "，"+victim->query("family/family_name")+"开始了对你的追杀！\n"NOR);
			   */
	return;
}
