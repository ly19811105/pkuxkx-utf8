// jianxi.c Zine 明教新手任务


#include <ansi.h>
inherit NPC;

int ask_fight();
void create()
{
        string name,*tmp,*pinying;
        string* color=({HIR,RED,HIY,YEL,HIB,BLU,HIG,GRN,HIC,CYN,MAG,HIM,HIW,WHT});
	    string color1=color[random(sizeof(color))];
        name=NAME_D->create_name();
        tmp=explode(name,"@");
        pinying=explode(tmp[1]," ");
        set_name(tmp[0],({tmp[1],pinying[0],pinying[1]}));
        set("title",color1+"奸细"+NOR);
        set("long","这是一位来明教打探消息的六大派奸细。\n");

  
        set("gender", "男性");
        set("attitude", "peaceful");
        
        set("random_npc",1);
        set("age", 38);
        set("shen_type", 1);
        set("per", random(20)+10);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 10);
        set("combat_exp", 5000);
        set("score", 8);

        set_skill("force", 30);
        set_skill("dodge", 20);
        set_skill("finger", 30);
        set_skill("parry", 20);
        
        
       set("inquiry", ([
            "fight" : (: ask_fight :),
			"奸细" : (: ask_fight :),
       	]) );
        setup();

        carry_object("d/mingjiao/npc/obj/baipao.c")->wear();
        call_out("dest",600);
}

int ask_fight()
{
        if (this_object()->query("owner")==this_player()->query("id")) {
        	if (environment(this_object())->query("no_fight")) 
        	{
        		command("say 被你发现了？我闪！");
        		random_move();
        	}
        	else command("say 哼！");
        } else command("say 不打不打就不打！");
        return 1;
}

int dest()
{
    if (this_object())
    {
        destruct(this_object());
    }
}


void die()
{
        object ob, me,where;
        ob = this_object();
        me = ob->get_damage_origin_object();
	if (ob->query("owner") != me->query("id"))
	{
		message_vision(WHT"$N无辜地喊到：见鬼了，才卧底就被人干掉！\n"NOR,ob);
		message_vision("$N一口鲜血喷出，倒在地上，死了。\n",ob);
		destruct(ob);
		return;
	}
    if (ob->query("killed")<2)
    {
        while (!objectp(where) || 
          !where->isroom()||
          TASK_D->place_belong(where)=="不明区域"||
          base_name(where) == "/adm/daemons/taskd")
        {where=TASK_D->random_room("/d/mingjiao/");}
        ob->add("killed",1);
        message_vision("$N往"+where->query("short")+"离开。\n",ob);
        ob->set("eff_jing", query("max_jing"));
        ob->set("eff_qi", query("max_qi"));
        ob->set("qi", query("max_qi"));
        ob->set("neili", query("max_neili"));
        ob->move(where);
        return;
    }
    message_vision("$N惨叫一声，转眼不能活了。\n",ob);
    me->set_temp("mingjiao/tasks/task3suc",1);
    tell_object(me,"你用利刃在"+ob->query("name")+"身上放血，可以回蝠王那里复命了。\n");
	CHANNEL_D->do_channel(this_object(), "bd", "hero", 1);
    ::die();
}

void unconcious()
{
	die();
}


