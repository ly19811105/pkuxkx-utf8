// xiantian-gong.c 先天功
// Made by hacky (1997.10.18)
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("xiantian-gong", 1);
	if ( me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，如何领会先天功？\n");
	if ( me->query("class") == "bonze" )
		return notify_fail("先天功追求的乃是自然之道，于佛家六根清净之意有碍，"
			+RANK_D->query_respect(me)+"欲修此功，如何堪破世间百情？\n");
	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("你的基本内功火候还不够。\n");
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("先天功只能用学(learn)来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"xiantian-gong/" + func;
}

int force_character(string char_type)
{
	int recv;
	recv=::force_character(char_type);
	switch(char_type)
	{
	  case "TYPE_DEC_SPD":        //TYPE_DEC_SPD
	  	return 80;
	  case "TYPE_FORCE":        //TYPE_FORCE
	  	return 250;
    case "TYPE_SHIELD_NEILI":
      return 3;
	  default:
	  	return recv;
	}
}