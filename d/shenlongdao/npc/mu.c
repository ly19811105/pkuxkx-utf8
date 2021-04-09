#include <ansi.h>
// mu jianping
inherit NPC;
//inherit F_MASTER;
#include "/new_quest/qxiepai.h"
#include "/new_quest/quest.h"
string ask_me();
int ask_wxb();
string ask2();
string ask3();
//void heal();
void create()
{
        set_name("沐剑屏", ({ "mu jianping", "mu" }));
        set("title",MAG "神龙教" NOR + HIC +"圣女" NOR);
        set("long",
                "她是云南沐王府的郡主。\n"
                "不知道怎么回事，她就来到了神龙岛，深得教主和夫人宠爱。\n");
        set("gender", "女性");
        set("age", 18);
        set("attitude", "peaceful");
        set("shen_type", 1);
      
       
        set("shen_type", 1);
        set("str", 18);
        set("int", 28);
        set("con", 20);
        set("dex", 24);
        set("per", 25);
        set("chat_chance", 100);
        
        set("chat_chance_combat", 100);
        
         set("max_qi", 1000);

        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);
        set("combat_exp", 50000);
        set("score", 10000);
        set("jiu_count", 5+random(5));
        set_skill("force", 60);
        set_skill("shenlong-xinfa", 60);
        set_skill("dodge", 60);
        set_skill("yixingbu", 60); 
        set_skill("shenlong-bian", 60); 
        set_skill("whip", 60); 
        set_skill("cuff", 60);
        set_skill("meinu-quan", 60);
        set_skill("parry", 60);
        set_skill("kuai-dao",60);
        set_skill("blade", 60);
        set_skill("literate", 60);
         map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixingbu");
        map_skill("cuff", "meinu-quan");
        map_skill("parry", "kuai-dao");
        map_skill("whip","shenlong-bian");
        create_family("神龙教", 3, "弟子");
        setup();
        carry_object("/clone/weapon/changbian")->wield();
 
        set("inquiry", ([
        "韦小宝":   (: ask_wxb() :),
        "方怡":"她是我的师姐。\n",
        "沐王府":"嗯，那是我家。\n",
        "quest":   (: ask_quest() :),
        "cancelquest":   (: ask_cancel() :),
        "取消任务":   (: ask_cancel() :),
        "雄黄酒":   (: ask_me() :),
        ]));
        set("book_count", 1);
        setup();

        carry_object("/d/gumu/obj/white")->wear();
}

string ask_me()
{
        mapping fam;
        object ob;
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "神龙教" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
        if (this_player()->query("shenlong/antisnake") == 1)
                return RANK_D->query_respect(this_player()) + "已经饮过雄黄酒了阿！？";
        if (query("jiu_count") < 1)
                return "你来晚了，今天的雄黄酒已经被人要完了。";
        add("jiu_count", -1);
        ob = new("/d/shenlongdao/obj/xionghuangjiu.c");
        ob->move(this_player());
        return "好吧，你喝了这杯雄黄酒就不怕岛上神龙了。";
}
int ask_wxb()
{
        object ob,letter,me;
        me=this_object();
        ob=this_player();
        if((int)ob->query_temp("shenlong/findwxb_mu")==1)
        {
        command("touch");  
        command("say 终于有相公的消息了！"); 
        letter = new("/d/shenlongdao/obj/letter_mujianping");
        letter->move(ob);
        command("say 烦劳你把这封信带给我相公，告诉他我一切都好！"); 
        command("waiting");
        return 1;
        }
        command("say 我家相公自从离岛之后，一直渺无音讯，你有他的消息吗?");
        command("cry "+ob->query("id"));    
        return 1;
}
