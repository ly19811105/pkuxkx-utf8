
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "一苇渡江" NOR; }
void go_cross(object me, int pa);

int pos_availble(string pos)
{
	string *allpos = ({ "/d/changjiang/", "/d/changjiangnorth/", "/d/huanghe/", "/d/huanghenorth/" });
	for (int i=0; i<sizeof(allpos); i++)
	{
		if ( strwidth(pos) >= strwidth(allpos[i]) 
			&& pos[0..strwidth(allpos[i])-1] == allpos[i] )
			return i;
	}
	return -1;
}

int perform(object me, string skill)
{
	int pa, dodge, cd;
	string pos;
	
	if(me->query("age")<18)
		return notify_fail("你还未成年，不能使用特殊技能。\n");
	
	pos = base_name(environment(me));

	pa = pos_availble(pos);
	if (pa<0)
		return notify_fail("想要施展「一苇渡江」，很明显，你得先找到那条江……或者是河也行！\n");

	if (me->query("qi") < 100)
		return notify_fail("你的体力不支，无法使用「一苇渡江」。\n");

	if (me->query("neili")< 500)
		return notify_fail("你的内力不足，无法使用「一苇渡江」。\n");
	
	dodge = me->query_skill("dodge", 1);
	if (dodge < 300)
		return notify_fail("你的轻功修为不足，这样恐怕会掉到水里去。\n");

	if (me->is_fighting())
		return notify_fail("你还在战斗中，腾不出功夫来使用「一苇渡江」。\n");
	
	if (me->is_busy())
		return notify_fail("你还在忙着呢，没空使用「一苇渡江」。\n");
	
	cd = 30 - (dodge - 300) / 50;
	if (cd<5) cd = 5;
	if ((time()-(int)me->query_temp("special_skill/cross")) < cd )
		return notify_fail("你现在气血翻涌尚未平复，还不能再次使用「一苇渡江」。\n");
	
	if (me->query_encumbrance() * 100 / me->query_max_encumbrance() > 50)
		return notify_fail("你背着这么重的东西施展「一苇渡江」，就不怕淹死在水里？\n");

	me->start_busy(10);
	
	message_vision(HIW"$N漫步走到水边，随手折下一根芦苇，屈指一弹，那芦苇如箭般射出，落在水面，飞快地向对岸冲去。\n"NOR, me);
	me->set_temp("special_skill/cross", time());
	
	call_out("go_cross", 2, me, pa); 
    return 1;
}

void go_cross(object me, int pa)
{
	int tpa = -1;
	string *allpos = ({ "/d/changjiang/", "/d/changjiangnorth/", "/d/huanghe/", "/d/huanghenorth/" });
	string *rooms = ({ "cjn", "cjb", "hhn", "hhb" });
	int *roomnum = ({23, 23, 21, 21});
	object room;
	switch (pa)
	{
		case 0:
		case 2: tpa = pa + 1; break;
		case 1: 
		case 3: tpa = pa - 1; break;
	}
	me->start_busy(0);
	if (pos_availble(base_name(environment(me)))<0)	
	{
		// 意外离开了区域房间？可以增加信息提示
		message_vision(HIY"$N忽然改变主意，不过江了。\n"NOR, me);
		return ;
	}
	if ( tpa<0 || tpa > (sizeof(allpos)-1))
	{
		// 无效的对岸？
		message_vision(HIY"$N看着芦苇在水面飘远，忽然感觉对岸地形陌生，决定还是不过江了。\n"NOR, me);
		return ;
	}
	while (1)
	{
		room = find_object(allpos[tpa] + rooms[tpa] + (random(roomnum[tpa])+1) + ".c" );
		if (objectp(room))
		{
			message_vision(HIC"眼看着芦苇在水面飘过半程，$N忽然纵身飞起，踏在芦苇上，逐浪而行，须臾间渡过了水面。\n"NOR, me);
			me->add("qi", -50);
			me->add("neili", -100);			
			me->move(room);
			message_vision(HIC"$N脚踩着一竿芦苇渡水而来，大袖飘飘，随浪起伏，潇洒无比地跳上了岸。\n"NOR, me);
			if (random(me->query("kar")) == 0) // 小概率事件，增加挂机难度
			{
				message_vision(HIY"踏上岸石的瞬间，$N忽然脚下一滑，「啪叽」摔了个嘴啃泥，周围掉了一地的眼珠子……\n"NOR, me);
				me->add("qi", -50);
				me->start_busy(3);
			}
			return;
		}
	}
}

