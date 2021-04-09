#include <ansi.h>
//inherit "/inherit/char/silver.c";
inherit NPC;

void create()
{
        set_name("索额图", ({"suo etu", "suo", "etu"}));
        set("gender", "男性");
        set("age", 55);
              set("title", HIR"大学士"+HIY" 侍卫内大臣"NOR);
        set("str", 25);
              set("int", 30);
        set("long", "索额图很早就是康熙帝的亲信，很受重用。\n");
        set("combat_exp", 300000);
        set("attitude", "friendly");
        set("class", "officer");
        set_skill("unarmed", 50);
        set_skill("dodge",50);
              set_skill("literate", 390);
        set_skill("parry", 50);

        set("neili", 500); 
        set("max_neili", 500);
        create_family("朝廷", 2, "官员");
        set("inquiry", ([
        //"读书识字": "凡朝廷弟子，我都会指点一二的！\n",
        //"军饷" : (: ask_silver :),  
        //"salary" : (: ask_silver :),  
        ]));
        set("silver_name", "军饷"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "bixue-xinfa"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "你只需要努力练功，报效朝廷，至于军饷嘛，你就来找我好了。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N沉吟着，记下了些什么。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N翻了翻记录，抬起头来。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "上回给你的军饷这么快就花完了吗？"); //时间未到不能领取时说的话
        set("msg_silver_paid", "拿着，这是你这次的军饷。"); //领取成功时说的话
        set("msg_silver_score", "$N笑着说：「为朝廷做了这么多贡献，真是辛苦你了。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N打量了你一番，笑着说：「你的功夫又有长进了。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N竖起了大拇指：「你将来一定是国家的栋梁。」\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "你还是在多做点事情吧，别老想着军饷。"); //领取例银条件均不满足时说的话        
        setup();
        carry_object(__DIR__"obj/guanfu")->wear();
}
/*int recognize_apprentice(object ob, object who)
{
        if((string)ob->query("family/family_name") != "朝廷")
//return notify_fail("看起来索额图不愿意教你！\n");
return 0;
 
      return 1;
}*/
