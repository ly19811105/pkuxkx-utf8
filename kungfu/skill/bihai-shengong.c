// bihai-shengong.c 碧海神功

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
// need more limit here
{
        int lvl = (int)me->query_skill("bihai-shengong", 1);
	int t = 1, j;
	for (j = 1; j < lvl / 10; j++) t *= 2;

//	if ( me->query("gender") == "无性" )
//              return notify_fail("碧海神功讲的是阴阳调和，以公公之无性之身，如何修得。 \n");

	if ( me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，无法领悟高深的碧海神功. \n");

	if ( me->query("class") == "bonze" )
               return notify_fail("碧海神功讲究阴阳调和，有违佛家六根清净之意. "                                                                                               + RANK_D->query_respect(me) + "欲修此功，实在罪过。 \n");

	if((int)me->query_skill("force",1)<10)
		return notify_fail("你的基本内功火候还不够。\n");


	return 1;
}

int practice_skill(object me)
{
        return notify_fail("碧海神功只能通过(learn)来提高熟练度. \n");
}

string exert_function_file(string func)
{
        return __DIR__"bihai-shengong/" + func;
}

int force_character(string char_type)
{
	int recv;
	recv=::force_character(char_type);
	switch(char_type)
	{
    case "TYPE_ENFORCE":
      return 12;
    case "TYPE_SHIELD_DEF":
      return 9;
    case "TYPE_SHIELD_NEILI":
      return 8;
	  default:
	  	return recv;
	}
}