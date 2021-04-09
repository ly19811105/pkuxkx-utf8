//wang.c
//made by hacky
//王重阳
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "/new_quest/qquanzhen.h"
#include "/new_quest/quest.h"
void consider();
void heal();
void create()
{
	int err;
	set_name("王重阳",({"wang chongyang","wang"}));
	set("nickname",HIR"中神通"NOR);
	set("long",@LONG
他就是全真教的开山祖师，武林中号称中神通的王重阳，
他身材消瘦，精神矍铄，飘飘然仿佛神仙中人，
LONG
		);
    set("title",HIB"全真派"NOR+YEL"开山祖师"NOR);
    set("gender","男性");
    set("age",80);
    set("attitude","friendly");
    set("shen_type",1);
    set("str",30);
    set("int",30);
    set("con",30);
    set("dex",30);
      set("per",80);
    set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: consider() :)
	}) );
    set("chat_chance",100);
    set("chat_msg",({
		(:heal:),
    }));
    set("max_qi",5000);
    set("max_jing",5000);
	set("max_neili",5000);
	set("neili",5000);
    set("jiali",110);
    set("combat_exp",12000000);
	
    set_skill("parry",350);
    set_skill("dodge",300);
    set_skill("cuff",400);
    set_skill("force",350);
    set_skill("xiantian-gong",380);
    set_skill("qixing-xinfa",150);
    set_skill("literate",220);
    set_skill("daoxue-xinfa",300);
    set_skill("quanzhen-jian",380);
    set_skill("finger",400);
    set_skill("yiyang-zhi",400);
    set_skill("fx-step",380);
    set_skill("yangxin-quan",300);
    set_skill("kongming-quan",400);
    set_skill("sword",300);
	
    map_skill("force","xiantian-gong");
    map_skill("dodge","fx-step");
    map_skill("finger","yiyang-zhi");
    map_skill("sword","quanzhen-jian");
    map_skill("parry","yiyang-zhi");
    map_skill("cuff","kongming-quan");
	
    prepare_skill("finger","yiyang-zhi");
	set("inquiry", ([
        "quest":   (: ask_quest() :),
		]));
	
	
    setup();
    create_family("全真派",1,"开山祖师");
    set("class","taoist");
	
    carry_object(__DIR__"obj/robe")->wear();
    carry_object(__DIR__"obj/gangjian.c")->wield();
	
    
}

void attempt_apprentice (object ob)
{ 
	int exp;      
	object obj;
	
	if((string)ob->query("family/family_name")!="全真派")
	{
		command("say " + RANK_D->query_respect(ob) + "若想入我重阳宫，可先拜尹志平。\n");  
		return;
    }
	if((int)ob->query("score")<1500)
	{
		command ("say 你自问是否对本门尽力了?");
		return;
	}
	if((int)ob->query("shen")<50000)
	{
		command("say 学武之人，德义为先，希望" + RANK_D->query_respect(ob) + "多做些善事，\n");
		return;
	}
	if((int)ob->query_skill("xiantian-gong",1)<60)
	{
		command("say " + RANK_D->query_respect(ob) + "还应在先天功上多下些功夫!\n");
		return;
    }
	if((int)ob->query("betrayer")>=2)
	{
		command("say 学武之人最忌背信弃义，你多次判师，我怎么能够收你!\n");
		return;
    }
	if((int)ob->query("combat_exp")<100000)
    {
		command("say 你再练几年吧!");
		return;
    }
	
	command("say 好吧，我就收下你吧.\n");
	command("recruit " + ob->query("id"));
	command("say 我也没有什么好给你的，\n");
	command("say 这里有一吧长剑，我将它刻上你的名字送与你吧,\n");
	command ("say 希望你能用这把剑惩恶扬善.\n");
    
    message_vision("王重阳气沉丹田，指锋急转，抽出自己的佩剑，刻上了你的名字\n",this_player());
    message_vision("王重阳给你一把刻有你名字的长剑\n",this_player());
	obj = new(__DIR__"obj/jian");
	obj->move(this_player());
	
	
	exp = (int) ob->query("combat_exp");
	if( exp<=150000) {
		ob->set("title",HIB"全真派"NOR+RED"散仙"NOR);
	} else if (exp<=300000) {
		ob->set("title" ,HIB"全真派"NOR+RED"地仙"NOR);
	} else if (exp<=450000) {
		ob->set("title",HIB"全真派"NOR+RED"人仙"NOR);
	} else  {
		ob->set("title",HIB"全真派"NOR+RED"天仙"NOR);        
	}
}
void consider()
{
	object *enemy,target;
	enemy = query_enemy() - ({ 0 });
	target = enemy[random(sizeof(enemy))];
	switch( random(2) )
	{
	case 0:
		command("unwield jian");
                command("perform finger.fuxue " + target->query("id"));
		command("wield jian");
		break;
	case 1:
		command("unwield jian");
                command("perform finger.yizhi " +target->query("id"));
		command("wield jian");
		break;
	}
}
void heal()                                             
{                                                       
	object ob=this_player();                        
	
	if (ob->query("eff_qi") < ob->query("max_qi"))  
	{                                               
		command("exert heal");                  
		command("enforce 30");                 
		return;                                 
	}                                               
	
	if (ob->query("qi") < ob->query("eff_qi"))      
	{                                               
		command("exert recover");               
		return;                                 
	}                                               
	
	if (ob->query("jing") < ob->query("eff_jing"))  
	{	command("exert regenerate");            
	
	return;
	}                                         
}                                                       
