//yangn.c 扬女
#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
/*string ask_me();
void consider();*/
void create()
{
        set_name("扬女", ({ "yangnu","yang" }));
        
         set("title",GRN "古墓派" NOR + MAG +"圣女" NOR);
        set("long",
                "她是神雕大侠夫妇的养女。\n"
                "她看起来十多岁，天生丽质，只是脸色略显白色。\
n");
        set("gender", "女性");
        set("age", 19);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 18);
        set("int", 32);
        set("con", 20);
        set("dex", 30);
        set("per", 50);
        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 80);
        set("combat_exp", 500000);
        set("score", 20000);
/*set("inquiry", ([
                "冰魄杖" : (: ask_me :),
                "name"   : "我就是阿紫呀！！",
        ]) );
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: consider :)
        }) );
  */   
	 set_skill("force", 120);
        set_skill("jiuyin-shengong", 120);
	set_skill("yunu-xinfa",100);
	set_skill("strike", 120);
	set_skill("xiaohun-zhang", 130);
        set_skill("dodge", 130);
        set_skill("xianyun", 130);
        set_skill("parry", 120);
        set_skill("claw", 150);
        set_skill("jiuyin-baiguzhao", 150);
	set_skill("sword",120);
	set_skill("yunu-jianfa",120);
        set_skill("literate", 80);

       

        map_skill("force", "jiuyin-shengong");
	map_skill("claw", "jiuyin-baiguzhao");
        map_skill("dodge", "xianyun");
//      map_skill("unarmed", "taiji-quan");
        map_skill("parry", "jiuyin-baiguzhao");
        map_skill("sword", "yunu-jianfa");
	map_skill("strike","xiaohun-zhang");
	prepare_skill("claw", "jiuyin-baiguzhao");

       

        create_family("古墓派" , 4, "弟子");
        setup();
       
       	//carry_object("/u/lianxing/gumu/obj/huang.c")->wear();
}
void attempt_apprentice(object ob)
{
	if((string)ob->query("family/family_name")!="古墓派")
		{
		 command("say " + RANK_D->query_respect(ob) + "若想拜我派可先拜小虹小玲。"); 
                return;
        	}
	 if ((int)ob->query("max_neili") < 300)
		 {
		 command("say " + RANK_D->query_respect(ob) + "内力太低，再回去好好努力吧。"); 
                return;
        	}
        else
          {
        command("say 好吧，"+RANK_D->query_respect(ob)+"，我就收下你了！");
        command("recruit "+ob->query("id"));
           }
       
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
	        ob->set("title",GRN "古墓派" NOR + YEL +"女使" NOR);
//title系统记录玩家title by seagate@pkuxkx
	        ob->set_title(TITLE_RANK, GRN "古墓派" NOR + MAG +"女使" NOR);
	      }
	      
			  return;
}

void re_rank(object student)
{        
        student->set("title",GRN "古墓派" NOR + YEL +"女使" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      student->set_title(TITLE_RANK, GRN "古墓派" NOR + MAG +"女使" NOR);
	      
			  return;
}


