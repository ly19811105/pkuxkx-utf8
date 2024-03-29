// shangguan.c 上官云
//by bing
#include "riyuenpc.h"
#include "riyuenpc2.h"
#include <title.h>
inherit NPC;
//inherit F_QUESTMASTER;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("上官云", ({ "shangguan yun", "shangguan","yun" }));
        set("title",GRN "日月神教" NOR + HIR "白虎堂" NOR + HIY "长老" NOR);
        set("long","他长手长脚，双目精光烂然，甚有威势，他在教中资历也不甚深，
只是近数年教中变迁甚大，他在教中已是极有权势、极有头脸的第一流人物。
他乃是日月神教白虎堂长老。\n");
        set("gender", "男性");
	      set("nickname", HIC "雕侠" NOR);
        set("age", 43);
        set("attitude","heroism");
        set("shen_type", -1);
	      set("shen",-30000);
        set("str", 30);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        set("max_qi", 1200);
        set("max_jing", 1000);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 100);
        set("combat_exp", 500000);
	      set("score",2000);
        set("chat_chance", 20);
        set("chat_msg", ({
                (: heal :),
        }));
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "blade.lianhuan" :),
        }) );
        set("inquiry", ([
            "东方不败" : (: ask_df :),
            "东方教主" : (: ask_df :),
	          "任我行" : (: ask_ren :),
	          "任教主" : (: ask_ren :),
	          "任盈盈" : "她是任教主的女儿，一般不住在黑木崖上，圣教主对她很尊重。",
	          "圣药" : "那是圣教主对有功之人的赏赐，吃了以后对教主更加忠心。在风雷堂童堂主处领取。",
	          "三尸脑神丹" : "那是圣教主对有功之人的赏赐，吃了以后对教主更加忠心。在风雷堂童堂主处领取。",
	          "上崖":"想上黑木崖，嘿嘿，得给我点好处，这样吧，你给我拿个金蛇锥。",
	          "上黑木崖":"想上黑木崖，嘿嘿，得给我点好处，这样吧，你给我拿个金蛇锥。",
	          "黑木崖":"想上黑木崖，嘿嘿，得给我点好处，这样吧，你给我拿个金蛇锥。",
	          "金蛇锥":"听说在华山某处，具体我也不清楚。",
       ]) );

        set_skill("force", 150);
        set_skill("riyue-shengong", 150);
        set_skill("dodge", 180);
        set_skill("parry", 150);
        set_skill("ryingzhua-gong", 120);
	      set_skill("blade",120);
	      set_skill("riyue-dao",120);
        set_skill("feitian-shenfa", 120);
        set_skill("claw", 150);
        set_skill("literate",100);
	      set_skill("flatter",120);
        map_skill("force", "riyue-shengong");
        map_skill("parry", "riyue-dao");
        map_skill("dodge", "feitian-shenfa");
        map_skill("claw", "ryingzhua-gong");
        map_skill("blade","riyue-dao");
        prepare_skill("claw", "ryingzhua-gong");
        create_family("日月神教", 20, "弟子");
        setup();
        carry_object("/d/riyuejiao/obj/heiyi")->wear();
        carry_object("/d/riyuejiao/obj/yaodai")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
       }
void init()
{
	object ob;
	mapping fam;
        ::init();
	ob = this_player();
	if (interactive(ob) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
        if ( ((int)ob->query("score") < 0 || (int)ob->query("shen") >0 )
		&& ((fam = ob->query("family")) && fam["master_id"] == "shangguan yun"))
        {
                command("say 你不去杀那些所谓的正教大侠,反而多次残害同道中人，我岂能仍是你的师傅。\n");
                command("expell "+ ob->query("id"));
        }


}

void attempt_apprentice(object ob)
{
	if ( ((int)ob->query("riyue_drug") != 0) && (ob->query("family/family_name") != "日月神教" ))
	{
	   command("say 大胆叛逆，竟敢反出神教，我今天就为教除逆！\n");
	   command("kill "+ob->query("id"));
	   return;
	}

        if ((int)ob->query("family/generation") == 20 && ob->query("family/family_name") == "日月神教")
	{
	   command("say 您开什么玩笑？有圣教主作您师傅还不够吗？");
	   return;
	}

	if (ob->query("family/family_name") != "日月神教")
	{
	   command("say 我们日月神教拜师要从堂主拜起，" + RANK_D->query_respect(ob) + "先去拜堂主吧！\n");
	   return;
	}

	if (ob->query("riyue_drug") == 0)
	{
	   command("say " + RANK_D->query_respect(ob) + "吃了我教的圣药了吗？\n");
	   return;
	}
	
	if (ob->query("riyue_drug") == 999)
	{
	   command("say " + RANK_D->query_respect(ob) + "还没吃今年的圣药，我不能收你。\n");
	}

	if ((int)ob->query("score") < 400)
	{
	   command("say " + RANK_D->query_respect(ob) + "对本教的贡献还不够，我不能收你。\n");
	   return;
	}

	if ((int)ob->query_skill("flatter",1) < 30)
	{
	   command("say " + RANK_D->query_respect(ob) + "还没学会黑木崖上流行的切口，还是先回去好好学习一下吧！\n");
	   return;
	}

	if ((int)ob->query_skill("riyue-shengong",1) < 30)
	{
	   command("say " + RANK_D->query_respect(ob) + "的日月神功好象还没学好，再回去好好学学吧！\n");
	   return;
	}
	
	if ((int)ob->query("shen") > -5000)
	{
	   command("say 我最痛恨那些所谓正教中的伪君子，" + RANK_D->query_respect(ob) + "若是能杀他几个，我一定收你。\n");
	   return;
	}

        command("say 好吧，"+RANK_D->query_respect(ob)+"！我就收下你了！\n");
        command("recruit "+ob->query("id"));

}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
	        if((string)ob->query("gender")=="女性")
		        ob->set("title",MAG "日月神教" NOR + HIR +"女坛主" NOR);
	        else	
	        	ob->set("title",MAG "日月神教" NOR + HIG +"坛主" NOR);
//title系统记录玩家title by seagate@pkuxkx
	        ob->set_title(TITLE_RANK, ob->query("title"));
	      }
}

int accept_object(object me, object ob)                                         
{                                                                                                                                           
    me=this_player();                                                                                                                                          
    this_object()->start_busy(1);                                               
    if(ob->query("id") == "jinshe zhui")                                       
    {                                                                           
        command("haha "+(string)me->query("id"));                                
        command("say 既然你给我找到的金蛇锥，这次你就可以自由上下黑木崖了！\n");
        me->set_temp("allow_hmy",1);
        call_out("destroy",1,ob);                                               
        return 1;                                                               
    }                                                                           
}                                                                               
void destroy(object ob)                                                         
{                                                                               
    if (ob) destruct(ob);       
    return;                                                                     
}                                                                               