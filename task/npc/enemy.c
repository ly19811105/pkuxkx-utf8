// task 新模式一 by lordstar 2017/8/30

#include <ansi.h>
inherit NPC;

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
    setup();
    carry_object("/clone/armor/bianfuxuejia")->wear();
    carry_object("/d/wizard/npc/obj/sword.c")->wield();
    carry_object("/d/wizard/npc/obj/blade.c")->wield();
}

void init()
{
	add_action("do_arrest", "arrest");
	add_action("do_arrest", "daibu");
}

int do_arrest(string arg)
{
    object tar;
	object ob=this_object();
	object me=this_player();
	int rt=(int)me->query_temp("task/arrest_rate");
	if (ob->query("owner_id") != me->query("id"))
		return 0;
	tar = present( ob->query("npc_task_target"), environment(ob));
	if (!objectp(tar) || tar->query("is_tasknpc")!= 1)
	{
        message_vision(HIY"\n$N狠狠地瞪了$n一眼，凶巴巴地吼了一句：关你屁事！滚远一点！！\n"NOR, ob, me);
        message_vision(HIY"$N左右看了看，呸的一声吐了口唾沫，跃入路边草丛几个起纵就消失不见了。\n\n"NOR, ob);
		ob->destruct_npc();
		return 1;
	}
	if (wizardp(me))
		write(" Arrest Rate: "+(40+rt)+"%");
    if (ob->query("qi") > (40+rt) * ob->query("max_qi") /100
		&& ob->query("eff_qi") > (40+rt) * ob->query("max_qi") /100)
    {
        message_vision(HIM"\n$N扭头瞪了$n一眼，恶狠狠地吼道：看什么看？滚远一点！小心连你一块砍！\n"NOR, ob, me);
		write(HIM"你缩了缩脖子，再等等吧，现在还不是好时机。\n\n"NOR);
		return 1;
    }
    if (tar->query("qi") > (40+rt) * tar->query("max_qi") /100
		&& tar->query("eff_qi") > (40+rt) * tar->query("max_qi") /100)
    {
        message_vision(HIM"\n$N扭头瞪了$n一眼，恶狠狠地吼道：看什么看？滚远一点！小心连你一块砍！\n"NOR, tar, me);
		write(HIM"你缩了缩脖子，再等等吧，现在还不是好时机。\n\n"NOR);
		return 1;
    }
    message_vision(HIC"\n趁着两名恶贼打得精疲力竭的机会，$N"+HIC+"飞快地冲了上去，出手如电，在两人肋下分别一戳。\n两名恶贼被点中穴道，顿时浑身酸麻，倒在地上动弹不得！\n", me);
	message_vision(HIY"$N与$n对视一眼，无可奈何地叹了口气：我们认栽。\n四周早已埋伏多时的捕快们一拥而上，把两名恶贼押走了。\n"NOR, ob, tar);
	ob->set("task_done", 1);
	tar->set("task_done", 1);
	tar->give_reward(me, 1);
	tar->destruct_npc();
	ob->destruct_npc();
    return 1;
}

void auto_perform()
{
    object weapon;
    command("exert recover");
    weapon = this_object()->query_temp("weapon");
	if (!weapon)
		carry_object("/d/wizard/npc/obj/sword.c")->wield();
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
	ob->prepare_skill("strike", "taiyi-shengong");
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
    message("vision", HIC"\n" + this_object()->name() + HIC"把衣领塞进嘴里，死命一咬，把缝在衣领上的毒药咬了下来。\n"NOR, environment());
    die();
}

void die()
{
	object tar;
	object ob = this_object();
	if (ob->query("task_done"))
	{
		// destruct(ob);
		return;
	}
	message("vision", HIC"\n" + ob->name() + HIC"不甘心地怒吼了一声：可恶！我的宝物……一头载倒在地上，死了。\n"NOR, environment());
	if (ob->query("npc_task_target") && objectp(tar = present( ob->query("npc_task_target"), environment(ob)) ) 
			&& tar->query("is_tasknpc") )
	{
		message("vision", HIY + tar->name() + "迅速扑了过去，从"+ ob->name() + HIY"怀里抢过一件东西揣到自己怀中，大笑了三声，跳进路旁的草丛中不见了。\n"NOR, environment());
		tar->destruct_npc();
	}
	else
	{	
		message("vision", HIY"一件东西从" + ob->name() + HIY"怀里滚落，掉到草丛中不见了。\n"NOR, environment());
	}
	remove_call_out("leave");
	::die();
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