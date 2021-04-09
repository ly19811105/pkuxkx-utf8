// prepare.c

inherit F_CLEAN_UP;

mapping valid_types = 
([
	"blade":   "刀法",
	"sword":   "剑法",
"whip":"鞭法",
"dagger":"匕法",
]);

int main(object me, string arg)
{
	mapping smap, pmap;
	string *skill, basic1, basic2, arg1, arg2, arg3;
	int i, count;

	seteuid(getuid());

	smap = me->query_skill_map();

	if( !mapp(smap) || sizeof(smap)==0 )
		return notify_fail("你现在没有使用任何有效特殊技能。\n");

	pmap = me->query_wprepare();
	if (!pmap) pmap = ([]);

	if( !arg ) 
	{
		if( !mapp(pmap) || sizeof(pmap)==0 )
			return notify_fail("你现在没有组合任何特殊技能。\n");

		skill = keys(valid_types);
		write("以下是你目前组合中的特殊兵器技能。\n");
		for (i=0; i<sizeof(skill); i++) 
                       {
			if( !me->query_skill(skill[i]) 
			|| !pmap[skill[i]] ) continue;
			write(	valid_types[skill[i]] + " (" + skill[i] + ")" 
				+ "   " + to_chinese(pmap[skill[i]]) + "\n");
                       }
		return 1;
	}
        

	if( arg=="none" ) 
	{
		if( !mapp(pmap) || sizeof(pmap)==0 )
			return notify_fail("你现在没有组合任何特殊兵器技能。\n");

		skill = keys(pmap);
		for (i=0; i<sizeof(skill); i++) 
                {
			me->prepare_wskill(skill[i]);
		}

		me->reset_action();
		write("取消全部技能准备。\n");
		return 1;
	}

        
        if ( sscanf(arg, "%s %s", arg1, arg2) !=2 )
            return notify_fail("wbei 兵器一 兵器二\n"); 
        

	if ( sscanf(arg, "%s %s", arg1, arg2) ==2 ) 
	{
		if ( sizeof(pmap) >= 2 ) 
			return notify_fail("你已组合有至少两种兵器技能了。\n");
		else
		{
			if( !me->query_skill(arg1, 1) || !me->query_skill(arg2, 1) )
				return notify_fail("你至少不会这两种技能其中之一。\n");

       	if( !find_object(SKILL_D(arg1)) && file_size(SKILL_D(arg1)+".c") < 0)//判断是否是自创武功
				return notify_fail("自创武功暂时不提供互备的功能。\n");

       	if( !find_object(SKILL_D(arg2)) && file_size(SKILL_D(arg2)+".c") < 0)//判断是否是自创武功
				return notify_fail("自创武功暂时不提供互备的功能。\n");

			if( !SKILL_D(arg1)->valid_combine(arg2) )
				return notify_fail("这两种兵器技能不能组合。\n");

			skill = keys(valid_types);

			basic1 = "";
			basic2 = "";
			for (i=0; i<sizeof(skill); i++) 
            {
				if( smap[skill[i]] == arg1 && basic1 == "") basic1 = skill[i];
				if( smap[skill[i]] == arg2 ) basic2 = skill[i];
			}

			if ( !basic1 || !basic2 || basic1 == "" || basic2 == "" ) 
				return notify_fail("这两种兵器技能尚未激发或目前不能准备。\n");

			me->prepare_wskill(basic1, arg1);
			me->prepare_wskill(basic2, arg2);

			me->reset_action();
			write("完成技能准备。\n");
			return 1;
		}		
	}
}
