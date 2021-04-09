#include <ansi.h>
inherit NPC;

string ask_yaoxiao();

void create()
{
        set_name("山中老人", ({"shanzhong laoren", "laoren"}));
        set("title", HIW"深不可测"NOR);
        set("long",
			"他是一位风霜满面的异族老人，蓄着一丛大胡子，双目开阖之际，流露出两道深邃的目光。\n"
        );
        set("gender", "男性");
        set("inquiry", ([
			"drug" : "只要你能找来药材，我就能制作出一种天下无双的神药！",
			"炼药" : "只要你能找来药材，我就能制作出一种天下无双的神药！",
			"神药" : "只要你能找来药材，我就能制作出「无常造化丹」！",
			"无常造化丹" : "你也知道「无常造化丹」这种天下无双的神药？",
            "药效" : (: ask_yaoxiao : ),
        ]));
        set("attitude", "friendly");
		set("shen_type",1);
		set("wuchangzaohua_maker", 1);
		set("age", 100);
        set("per", 20);
        set("str", 50);
        set("int", 35);
        set("con", 50);
        set("dex", 30);
        set("max_qi", 500000);
        set("max_jing", 500000);
        set("neili", 500000);
        set("max_neili", 500000);
        set("jiali", 1000);
        set("combat_exp", 2000000000);
		set("env/jindou", 2);
		set("chat_chance_combat", 100);
		set("chat_msg_combat", ({
			(: perform_action, "dagger.duo" :),
			(: perform_action, "dagger.yinfeng" :),
			(: perform_action, "dagger.jindou" :),
			(: perform_action, "dagger.miaofeng" :),
			(: perform_action, "dagger.shenghuo" :),
		}) );
		set_skill("force",3800);
        set_skill("guangming-shenghuogong",3500);
		set_skill("claw",3000);
		set_skill("dodge",3000);
		set_skill("datengnuo-bufa",3000);
		set_skill("shenghuo-lingfa",3800);
		set_skill("parry",3500);
		set_skill("dagger",3000);
		set_skill("qiankun-danuoyi", 3300);
        set_skill("myingzhua-gong", 3300);
        map_skill("claw", "myingzhua-gong");
        map_skill("force", "guangming-shenghuogong");
        map_skill("dodge", "datengnuo-bufa");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dagger", "shenghuo-lingfa");
        prepare_skill("claw", "myingzhua-gong");
		prepare_wskill("dagger", "shenghuo-lingfa");
		set_temp("apply/armor", 5000);
		set_temp("apply/damage", 1000);
		setup();
		// 身上带的无常造化丹，因为没mark，谁也吃不了
		carry_object("/obj/remedy/drug/wuchang-zaohua");  
		carry_object("/clone/weapon/bishou")->wield();
}

string ask_yaoxiao()
{
	object me, ob;
	int dd;
	me = this_player();
	ob = this_object();
	dd = (int)me->query("death_decrease");
	if (dd<=0) 
	{
		tell_object(me, HIY + ob->query("name")+ "抬起头来冷冷地瞥了你一眼。\n" NOR );
		return "屁的药效！什么都没有！走走走，少来打扰我！";
	}
	message_vision(HIC "$N瞥了$n一眼，然后伸出手来，飞快地在$n身上捏了几下。\n" NOR, ob, me);
	return "你体内药效已经累积了百分之"+chinese_number(dd)+"，但关键时刻能发挥出几成，那就只有天知道了。";
}

int confirm_wuchangzaohua(object me)
{
	object ob = this_object();
	message_vision(HIC "$N点了点头，说道：「等着！」转身翻出了药炉和一堆瓶瓶罐罐，埋头忙活起来。\n" NOR, ob, me);
	ob->start_busy(8);
	call_out("give_wuchangzaohua", 5, me);
	return 1;
}

void give_wuchangzaohua(object me)
{
	object drug;
	object ob = this_object();
	if (!objectp(ob)) return;
	if (!objectp(me) || environment(me) != environment(ob))
	{
		message_vision(HIY "$N愕然道：「人呢？不要神药了？那正好归我了……」把一颗丹药丢进自己嘴里大嚼起来。\n" NOR, ob);
		return;
	}
	message_vision(HIY "$N轻吁了一口气，说道：「好了，拿去吧。」把一个小药瓶抛给了$n。\n" NOR, ob, me);
	drug=new("/obj/remedy/drug/wuchang-zaohua");
	if (objectp(drug))
	{
		drug->set("owner", me->query("id"));
		drug->move(me);
		tell_object(me, "你得到了一颗"+drug->query("name")+NOR+"！\n");
		CHANNEL_D->do_channel(ob, "rumor", "听说" + me->name(1) + "得到了一颗无常造化丹！");
		log_file("static/wuchang_zaohua", sprintf("%s:%s(%s)从山中老人处获得一颗无常造化丹！\n",ctime(time()),me->query("name"),me->query("id"))); 
	}
}

void unconcious()
{
    die();
}

void die()
{
    set("eff_qi",this_object()->query("max_qi"));
    set("qi",this_object()->query("max_qi"));
    set("eff_jing",this_object()->query("max_jing"));
    set("jing",this_object()->query("max_jing"));
    return;
}

int accept_object(object me, object ob)
{
    int val, nd_val;
	if (!ob->query("money_id")) return 0;
	if (!me->query_temp("wuchang_zaohua/material")) 
	{
		message_vision("山中老人冷哼了一声，道：「没有材料，光给钱有什么用？」\n", me);
		return 0;
	}
	nd_val = (int)me->query_temp("wuchang_zaohua/need_money");
	if (nd_val<1000000)
	{
		nd_val = me->query("combat_exp")/100000 + 1000;
		nd_val *= 10000;
		me->set_temp("wuchang_zaohua/need_money", nd_val);
	}
	me->add_temp("wuchang_zaohua/give_money", ob->value());
	val = (int)me->query_temp("wuchang_zaohua/give_money");
	log_file("static/wuchang_zaohua", sprintf("%s:%s(%s)交付山中老人制作费%d（累计%d/共需%d）。\n",
		ctime(time()),me->query("name"),me->query("id"),ob->value(),val,nd_val)); 
	if (val >= nd_val)
	{
		me->delete_temp("wuchang_zaohua");
		confirm_wuchangzaohua(me);
	}
	else
	{
		val = nd_val - val;
		val /= 10000;
		if (val<1) val=1;
		message_vision("山中老人摇头道：「这些钱不够，你还要再给我"+chinese_number(val)+"两黄金。」\n", me);
	}
	return 1;
}

