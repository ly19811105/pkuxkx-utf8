// perform.c

#include <weapon.h>;
inherit F_SSERVER;

int main(object me, string arg)
{
	object weapon,weapon2;
    object target_ob;
	int ret, is_user_skill;
	string martial, action, target;
    string skill, force_skill, perform_file;
	//空手功夫，判断perform与持兵器状态是否相符用，如果加入新的空手功夫，需要在下面列表中添加
         string *kongshou_skill = ({"claw","finger","strike","cuff","unarmed","hand","throwing","spells"});
	//可以在parry上使用perform的功夫，暂时只有flatter的qiurao和慕容的xingyi
	string *parry_skill = ({"qiurao","xingyi"});
    //可以用在非战斗对象上的perform
    string *perform_nofighting =  ({
        "tan","fuxue","cuiming","shoot","shuai","zhong","lianzhong","liao"
        });
    //必须激发对应内功的 武功-内功 对照
	mapping skill_force_map = ([
        "murong-jianfa"     : "shenyuan-gong",
        "yiyang-zhi"        : "xiantian-gong",
        "pixie-jian"        : "kuihua-shengong",
        "xianglong-zhang"   : "huntian-qigong",
        "yunlong-zhua"      : "yunlong-shengong",
        "wuying-jian"       : "yijin-jing",
        "taiji-zhao"        : "taiji-shengong",
        "xingxiu-duzhang"   : "huagong-dafa",
    ]);
	//判断bei的 mapping
	mapping prepare_skill_map;

	seteuid(getuid());

    if( environment(me)->query("no_perform") ) return notify_fail("这里禁止使用 perform 。\n");
	if( me->is_busy() ) return notify_fail("( 你上一个动作还没有完成，不能施用外功。)\n");
    if( !arg ) return notify_fail("指令格式 perofrm martial.action [target]\n");
    //blind 的效果暂时没有使用
    //if( me->query_temp("blind"))
	//	return notify_fail("你什么也看不清，无法施展特殊功夫!\n");

	weapon = me->query_temp("weapon");
	weapon2 = me->query_temp("secondary_weapon");
    // 必须使用 perform martial.action [target] 的格式
	if( sscanf(arg, "%s.%s", martial, arg)!=2 ) 
        return notify_fail("指令格式 perofrm martial.action [target]\n");
        
	if( sscanf(arg, "%s %s", action, target)==2 ) 
    {
        if( me->query("id")==target ) return notify_fail("你要自杀吗？\n");
		target_ob = present(target, environment(me));
	}
    else
    {
		action = arg;
        target_ob = offensive_target(me);
	}
    if( !target_ob ) 
        return notify_fail("这里没有你要攻击的对象。\n");
    if( !target_ob->is_character()) 
        return notify_fail("你想要攻击"+target_ob->name()+"吗？这可不是个活物。\n");
	
    if (target_ob->query("uni_target"))
        if (target_ob->query("uni_target") != me)
            return notify_fail(target_ob->name()+"不想与你较量。\n");

	if( !stringp(skill = me->query_skill_mapped(martial)) ) 
        return notify_fail("你请先用 enable 指令选择你要使用的外功。\n");

    //判定使用的内功是否符合
    if (member_array(skill,keys(skill_force_map)) != -1)
    {
        if (skill_force_map[skill] != me->query_skill_mapped("force"))
            return notify_fail(sprintf("使用%s必须激发%s才能使出这个绝招。\n",
                to_chinese(skill), to_chinese(skill_force_map[skill]) ));
    }
	
	// 是否自创武功
	if(file_size(SKILL_D(skill)+".c") < 1)
		if (file_size(PLAYER_SKILL_D(skill)+".c") < 1)
			return notify_fail("错误！你要查对技能文件已经消失，请通知巫师。\n");
		else
			is_user_skill = 1;
	else
		is_user_skill = 0;
		
    //判断perform是否存在            
	if (!is_user_skill)
	{
		if( !stringp(perform_file = SKILL_D(skill)->perform_action_file(action) ) 
			||	file_size(perform_file + ".c") <= 0 )
			return notify_fail(to_chinese(skill)+"没有 "+action+" 这个武功招式。\n");
	}
	else
	{
		if( !stringp(perform_file = PLAYER_SKILL_D(skill)+"/"+action ) 
			||	file_size(perform_file + ".c") <= 0 )
			return notify_fail(to_chinese(skill)+"没有 "+action+" 这个武功招式。\n");
	}
        
    if( !me->is_fighting(target_ob) )
        if (member_array(action,perform_nofighting) == -1)
            return notify_fail(to_chinese(skill) +"的 "+action+" 只能对战斗中的对手使用。\n");


	//判断所用perform与持兵器状态、种类是否相符
    //使用空手功夫perform，至少需要空一只手
	if (member_array(martial,kongshou_skill) != -1) 
	{
		if ((weapon && weapon2) || (weapon && weapon->query("flag") & TWO_HANDED))	
			return notify_fail("你必须空出一只手才能使出"+to_chinese(skill)+"的绝技。\n");
		//必须bei空手功夫才能使出空手perform，否则可能引起打task等copy skill npc时的bug
		//by icer 20050608
		prepare_skill_map = me->query_skill_prepare();
		if ( !prepare_skill_map || member_array(skill,values(prepare_skill_map)) == -1)
			return notify_fail("你必须先prepare " + skill + "才能使出" + to_chinese(skill) + "的绝技。\n");
		if (weapon && !weapon2)
		{	//某些空手连击perform中没判断是否空手，使用兵器连击，如六脉
			weapon2 = weapon;
			me->delete_temp("weapon");
			me->set_temp("secondary_weapon",weapon2);
			me->set_temp("weapon_changed_for_perform",1);
			weapon = 0;
			me->reset_action();
		}
	}
    //判断parry.xxx是否满足要求
    else if (martial == "parry")
    {
        if (member_array(action,parry_skill) == -1)
            return notify_fail(to_chinese(skill)+"激发成招架后不能使用 "+ action +" 这个绝技。\n");
    }
    //兵器perform，需判断兵器种类和功夫种类是否相符
    else if ( martial != "dodge" )
    {
        if (!weapon || ((string)weapon->query("skill_type") != martial)) 
            if (!weapon2 || ((string)weapon2->query("skill_type") != martial)) 
                return notify_fail("你要拿着 "+martial+" 类武器才能使出这种绝技。\n");
    }

        
    ret = perform_file->perform(me,target_ob);	
	if (me->query_temp("weapon_changed_for_perform"))
	{
		weapon2=me->query_temp("secondary_weapon");
		weapon = me->query_temp("weapon");
		if (weapon2 && !weapon)
		{	//换回兵器
			weapon = weapon2;
			me->delete_temp("secondary_weapon");
			me->set_temp("weapon",weapon);
			me->delete_temp("weapon_changed_for_perform",1);
			weapon2 = 0;
			me->reset_action();
		}
	}
	return ret;
}

int help (object me)
{
    write(@HELP
指令格式：perfrom <武功种类>.<招式名称> [<施用对象>]

如果你所学的外功(拳脚、剑法、刀法....)有一些特殊的攻击方式或招式，可以
用这个指令来使用，你必须先用 enable 指令指定你使用的武功。例如太极剑法
的缠字决可以用：
perform sword.chan
HELP
    );
    return 1;
}
