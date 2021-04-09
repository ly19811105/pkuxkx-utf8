//D:\xkx\d\liuxiu-shanzhuang\npc\youkunyi.c游鲲翼
// labaz 2012/10/22

#include <ansi.h>
inherit NPC;
#include "../newbie_village.h"

int do_changegift(string);

void create()
{
	set_name(RED"游鲲翼"NOR, ({ "you kunyi", "you" }));
	set("title", "柳秀山庄庄主");
	set("nickname", "英雄迟暮");
	set("shen_type", 0);

	set("gender", "男性");
	set_max_encumbrance(100000000);
	set("age", 35);
	set("long",
		"他就是柳秀山庄的主人。\n");
	set("no_get_from", 1);
	
	set("dex", 80);
	set("str", 80);
	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set("qi", 100000);
	set("max_qi", 100000);
	set("jing", 100000);
	set("max_jing", 100000);
	set_temp("apply/attack", 30);
	set_temp("apply/attack", 30);
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	
	setup();
}

void init()
{
    object me = this_player();

    ::init();

    if( interactive(me) )
    {
        remove_call_out("greeting");
        call_out("greeting", 1, me);
    }
    add_action("do_changegift","changegift");
}


int do_changegift(string arg)
{
     int str, ints, con, dex, kar, per;
     object me;
     me = this_player();
     if (me->query("marks/changegift"))
          return notify_fail(RANK_D->query_respect(me)+"，每个人一生只有一次这样的机会！\n");
     
     if ( !arg || sscanf(arg, "%d %d %d %d %d %d", str, ints, con, dex, kar, per) != 6)
     return notify_fail("指令格式：changegift <膂力> <悟性> <根骨> <身法> <福缘> <容貌>。\n");

     if(str+ints+con+dex !=80)
     return notify_fail("你的前四项属性值不等于80，请重新输入！\n");

     if(str>30 || ints>30 || con>30 || dex>30 || kar>30 || per>30)
     return notify_fail("各项属性均不能超过30！\n");
     
     if(str<10 || ints<10 || con<10 || dex<10 || kar<10 || per<10)
     return notify_fail("各项属性均不能低于10！\n");
     
     
     me->set("str",str);
     me->set("int",ints);
     me->set("con",con);
     me->set("dex",dex);
     me->set("kar", kar);
     me->set("per", per);
     me->set("marks/changegift",1);
     log_file("static/changegift", sprintf("%s(%s)于%s调整先天属性，调整后膂力%d，悟性%d，根骨%d，身法%d，福缘%d，容貌%d。\n",me->query("name"),me->query("id"),ctime(time()),me->query("str"),me->query("int"),me->query("con"),me->query("dex"),me->query("kar"),me->query("per")));
     me->save();
     write(HIM"恭喜你，游庄主成功为你改善先天资质！\n"NOR);
     return 1;
}

void greeting(object me)
{
	if (!objectp(me)) return;
    command("say 游某有幸，承"+RANK_D->query_respect(me)+"光临敝庄数日，令敝庄蓬荜生辉，"+RANK_D->query_respect(me)+"又帮忙找回……找回了葫芦，本应好好答谢才是……”\n");
    command("sigh\n");
    tell_object(me,CYN"游鲲翼又看了看你，接着道：“奈何阁下是胸怀抱负之人，在下也强留不住，今日就此别过，江湖浮沉，你我再见已难，望阁下好自珍重。“。\n南边就是车马行，我吩咐了家丁备了马车送你去扬州。\n\n"NOR);
    tell_object(me,HIR"在你临走之前，如果你需要的话，输入changegift命令，我可以尝试改善下你的先天资质。
命令格式：changegift <膂力> <悟性> <根骨> <身法> <福缘> <容貌>
例如      changegift 20 20 20 20 20 20
记住，我只能帮你这一次，一定要考虑好了再告诉我。你可以请教下武林中的前辈，或者阅读他们的经验之著。
http://wiki.pkuxkx.com/\n"NOR);
    command("bye "+me->query("id"));
}

