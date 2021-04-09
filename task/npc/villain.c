// task 新模式一 by lordstar 2017/8/30

#include <ansi.h>
inherit NPC;

int other_qi,other_jing;

int leave();
void auto_perform();
int do_arrest(string arg);
int destruct_npc();

void create()
{
	string nickname,name,*tmp,*pinying;
	name=NAME_D->create_name();
	nickname=NAME_D->create_color_nick();
	tmp=explode(name,"@");
	pinying=explode(tmp[1]," ");	
	
	set_name(tmp[0],({tmp[1],pinying[0],pinying[1]}));
	set("nickname",nickname);
	set("gender",random(3)>0?"男性":"女性");//male sadan is more..:)

    set("is_tasknpc", 1);
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({(: auto_perform :),}));
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);
    set("combat_exp", 3000);
	set("max_qi", 1000);
    set("max_jing", 1000);
    set("jingli", 1000);
    set("max_jingli", 1000);
    set("neili", 1000);
    set("max_neili", 1000);
    set("jiali", 0);
//	set("no_yizhaoyun", 1); 开放一招晕. by lordstar
	set("daoluan_perform", 1);
    setup();
    carry_object("/clone/armor/bianfuxuejia")->wear();
    carry_object("/d/wizard/npc/obj/sword.c")->wield();
    carry_object("/d/wizard/npc/obj/blade.c")->wield();
	call_out("try_leave", 10);
}

void init()
{
        add_action("do_gou", "gou");
}

int do_gou(string arg)
{
	object ob = this_object();
	object me = this_player();
	if (ob->query("siwang_wangou"))
		return notify_fail("对方已经中了你的死亡弯钩，不必再忙活了。\n");
    message_vision(RED"\n$N屈指一弹，一道若有若无的"BLU"暗线"RED"飞了出去，悄无声息地没入$n的腰间。\n\n"NOR, me, ob);
	ob->set("siwang_wangou", 1);
    return 1;
}

void auto_perform()
{
    object weapon, sweapon;
    command("exert recover");
    weapon = this_object()->query_temp("weapon");
	if (!weapon)
		carry_object("/d/wizard/npc/obj/sword.c")->wield();
    sweapon = this_object()->query_temp("secondary_weapon");
	if (!sweapon)
		carry_object("/d/wizard/npc/obj/blade.c")->wield();
	command("perform yinyang-daoluan.daoluan");
    command("exert recover");
}

void init_skills(int max)
{
	object ob=this_object();
	ob->set_skill("sword", max);
	ob->set_skill("blade", max);
	ob->set_skill("parry", max);
	ob->set_skill("dodge", max);
	ob->set_skill("strike", max);
	ob->set_skill("luoxuan-jiuying", max);
	ob->set_skill("taiyi-zhang", max);
	ob->set_skill("taiyi-shengong", max);
	ob->set_skill("yinyang-daoluan", max);
	ob->set_skill("literate", max);
    ob->map_skill("dodge", "luoxuan-jiuying");
    ob->map_skill("force", "taiyi-shengong");	
    ob->map_skill("sword", "yinyang-daoluan");
    ob->map_skill("blade", "yinyang-daoluan");
	ob->prepare_wskill("sword", "yinyang-daoluan");
	ob->prepare_wskill("blade", "yinyang-daoluan");
	ob->reset_action();
}

void copy_hp(object plyr)
{
	int qi,jing;
	object ob=this_object();
	if (!plyr) return;
    ob->set("str", plyr->query("str"));
    ob->set("int", plyr->query("int"));
    ob->set("con", plyr->query("con"));
    ob->set("dex", plyr->query("dex"));
    ob->set("kar", plyr->query("kar"));
    ob->set("combat_exp", 11*plyr->query("combat_exp")/10);
	qi = 11*plyr->query("max_qi")/10;
	jing = 11*plyr->query("max_jing")/10;
	ob->set("max_qi", qi);
    ob->set("max_jing", jing);
	ob->set("eff_qi", qi);
    ob->set("eff_jing", jing);
	ob->set("qi", qi);
    ob->set("jing", jing);
    ob->set("jingli", 2*plyr->query("max_jingli"));
    ob->set("max_jingli", plyr->query("max_jingli"));
    ob->set("neili", 2*plyr->query("max_neili"));
    ob->set("max_neili", plyr->query("max_neili"));
}

void unconcious()
{	
    die();
}

void die()
{
	object tar;
	object ob = this_object();
	object plyr;
	if (ob->query("task_done"))
	{
		return;
	}
	message("vision", HIC"\n" + ob->name() + HIC"哇地喷出一大口鲜血，翻着白眼，缓缓倒了下去。\n"NOR, environment());
	if (objectp(tar = present( ob->query("npc_task_target"), environment(ob))))
	{
		message("vision", HIC + tar->name() + HIC"一脸鄙夷，呸地一声吐了一口唾沫，恨恨地说道：狗贼，你也有今天！\n"NOR, environment());
		if (objectp(plyr = find_player(ob->query("owner_id"))) && environment(plyr) == environment(tar) )
		{
			message_vision(HIY "$N朝$n抱拳行了个礼，说道：多谢这位"+RANK_D->query_respect(plyr)+"仗义相助，在下感激不尽！咱们后会有期！\n" NOR, tar, plyr);
			message_vision(HIY "$N言罢，纵身一跃，消失在路旁的草丛中。\n\n" NOR, tar, plyr);
			ob->set("task_done", 1);
			tar->set("task_done", 1);
			tar->give_reward(plyr, 2);
		}
		else
		{
			message_vision(HIY "$N又朝四周看了看，叹了口气，低声嘀咕了一句：可惜了……言罢纵身一跃，消失在路旁的草丛中。\n\n" NOR, tar);
		}
		tar->destruct_npc();
	}
	remove_call_out("leave");
	::die();
}

int try_leave()
{
	object me=this_object();
	int i;
	if (me->is_fighting())
	{
		message_vision(HIM "\n$N虚晃一招，抽身欲走，却被拦了下来！\n$N嘿嘿笑道：你的动作不慢啊，这次是我大意了，下次，你就别想拦住我了！\n\n" NOR, me);
		me->add_busy(2);
		i = 5;
		if (me->query("leave_later")) i+= 5;
		if (random(me->query("kar"))>random(20)) i+= 2+random(3); //NPC的福源是复制自玩家福源数据的
		call_out("confirm_leave", i);
		return 1;
	}
	call_out("leave", 1);
	return 1;
}

int confirm_leave()
{
	object ob = this_object();
	object me = find_player(ob->query("owner_id"));
	if (ob->query("siwang_wangou") && objectp(me) && environment(ob)==environment(me))
	{
		message_vision(HIC "\n$N长笑一声，正待拔地而起，忽然腰间一痛，就像是被一只无形的手狠狠地揪了一吧，险些一头栽倒在地。\n" NOR, ob);
		message_vision(HIY "「这是什么？」$N惊叫了一声，马上醒悟了过来：「夺魂弯钩？」\n" NOR, ob);
		message_vision(HIY "「别以为只有你会夺魂弯钩！」$N扭头望向$n，怒喝道：「看招！」\n" NOR, ob, me);
		message_vision(HIM "$N曲指一弹，一道"BLU"黑影"HIM"激射而出。$n躲闪不及，"BLU"黑影"HIM"没入了$n的腰间！\n\n" NOR, ob, me);
		ob->fight_ob(me);
		me->fight_ob(ob);
		call_out("apply_wangou", 1, me);
	}
	else
		call_out("escape_leave", 1);
	return 1;
}

int apply_wangou(object me)
{
	object ob = this_object();
	int dmg, qi;
	qi = me->query("max_qi") / 2;
	if (!objectp(me)) return 1;
	if (!living(me) || me->query("eff_qi")<=qi || me->query("qi")<= qi)
	{
		tell_object(me, HIY"\n" + ob->query("name")+ HIY"得意地伸指弹了弹衣袍，朝你做了个「再见」的手势。\n\n"NOR);
		call_out("escape_leave", 1);
		return 1;
	}
	if (environment(ob)!= environment(me))
	{
		tell_object(me, HIG"你忽然感觉浑身一阵轻松，似乎某种羁绊已经失效了。\n"NOR);
		ob->delete("siwang_wangou");
		call_out("escape_leave", 1);
		return 1;		
	}
	message_vision(HIW "\n$N的身体晃了两晃，仿佛是被什么东西牵制住了，虽然在使劲挣扎，但一时之间还无法脱开身。\n" NOR, ob);
	tell_object(me, HIR + ob->query("name")+ HIR"这一挣扎，你便觉得自己的腰间也随之一痛，就像是有什么东西狠狠地勾住了你的腰肋，痛不可当。\n"NOR);
	dmg = me->query("max_qi")/20;
	F_KUNGFU->hit_wound("qi", dmg, dmg, ob, me);
	COMBAT_D->report_status(me);
	call_out("apply_wangou", 1, me);
	return 1;
}

int escape_leave()
{
	object me = this_object();
	object tar;
	object plyr = find_player(me->query("owner_id"));
	message_vision(CYN "\n$N长笑一声，拔地而起，像只大蝙蝠般随风而行，转眼就已在数丈之外，再一晃就消失不见了，只有怪笑声还在耳边回荡！\n" NOR, me);
	if (objectp(tar = present( me->query("npc_task_target"), environment(me))))
	{
		message_vision(HIM "$N追之不及，只能喟然长叹一声，失望地离开了！\n\n" NOR, tar);
		tar->destruct_npc();
	}
	if (me->query("siwang_wangou") && objectp(plyr) && (environment(plyr)== environment(me)))
	{
		tell_object(plyr, HIG + me->query("name")+ HIG"以传音入密对你悄悄说道：「就你这点身手也敢使夺魂弯钩，指不定是谁夺谁的魂呢……」\n\n"NOR);
		plyr->unconcious();
	}
	me->destruct_npc();
	return 1;
}

int leave()
{
    destruct(this_object());
    return 1;
}

int destruct_npc()
{
	remove_call_out("leave");
	this_object()->move(VOID_OB);
	call_out("leave", 1);
}

