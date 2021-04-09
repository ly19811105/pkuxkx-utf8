// jianxi.c Zine 明教新手任务


#include <ansi.h>
inherit NPC;

int ask_fight();
void create()
{
        set_name("山贼",({"shan zei","zei"}));
        set("title",HIR+"旷世猛男"+NOR);
        set("long","这是一位荆南地区的山贼。\n");

  
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

        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 10);
        set("combat_exp", 3000000);
        set("score", 8);

        set_skill("force", 300);
        set_skill("dodge", 320);
        set_skill("cuff", 330);
        set_skill("parry", 320);
        
        
       
        setup();

        carry_object("d/xiangyangnan/npc/obj/pao.c")->wear();
        call_out("dest",600);
}

int keep_moving()
{
    object ob=this_object();
    ob->random_move();
    call_out("keep_moving",18+random(3));
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
        object ob,obj,me,where;
        int i,num;
	    string gem;
        ob = this_object();
        me = ob->get_damage_origin_object();
	if (ob->query("owner") != me->query("id"))
	{
		message_vision(WHT"$N无辜地喊到：见鬼了，这年头牛人太多，真不该随便出来的！\n"NOR,ob);
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
        {where=TASK_D->random_place();}
        ob->add("killed",1);
        message_vision("$N往"+TASK_D->place_belong(where)+"的"+where->query("short")+"附近逃离。\n",ob);
        ob->set("eff_jing", query("max_jing"));
        ob->set("eff_qi", query("max_qi"));
        ob->set("qi", query("max_qi"));
        ob->set("neili", query("max_neili"));
        ob->move(where);
        ob->keep_moving();
        return;
    }
    if (!ob->query("rewarded"))//防止各种情况导致npc失去心跳而不断刷奖励 Zine
    {
        message_vision("$N惨叫一声，转眼不能活了。手却死死按住怀里，似乎藏了什么。\n",ob);
        obj = new("/obj/gem/gem");
	      
	    i = random(20);
	      if (i < 3) gem = "yan";
        else if (i < 6) gem = "mu";
        else if (i < 9) gem = "sui";
        else if (i < 12) gem = "jin";
        else if (i < 15) gem = "bing";
        else if (i < 16) gem = "gu";
        else if (i < 17) gem = "yu";
        else if (i < 18) gem = "jiao";
        else gem = "jia";
	    obj->set_level(5000,10000,gem);    
	    obj->move(ob);
        ob->set("rewarded",1);
        num=5000+random(5000);
        me->add("combat_exp",num);
        tell_object(me,"你为民除害，被奖励经验"+chinese_number(num)+"点。\n");
    }
    CHANNEL_D->do_channel(this_object(), "jh", HIW + me->query("name") +HIW "路见不平，铲除了山贼。", -1);
	CHANNEL_D->do_channel(ob, "bd", "hate", 1);
    ::die();
}

void unconcious()
{
	die();
}


