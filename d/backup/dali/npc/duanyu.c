// duanyu.c 段誉
// by paladin

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
inherit "/inherit/char/silver.c";

// int ask_me();

void create()
{
        set_name("段誉", ({ "duan yu", "duan" }));
        set("nickname", HIR "风流浪子" NOR);
        set("long",
                "他就是段誉\n");
	
        set("title",RED "大理" NOR + GRN  "王子" NOR);
        set("gender", "男性");
        set("age", 18);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("dex", 30);
        set("max_qi", 10000);
        set("max_jing", 10000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jiali", 100);
         set("combat_exp", 8000000 + random(4000000));
        set("score", 1000000);

        set("chat_chance", 100);

	set("inquiry", ([
//                "六脉神剑剑谱" : (: ask_me :),
		"俸禄" : (: ask_silver :),
	]));

	set("silver_name", "俸禄"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "lingbo-weibu"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "呵呵，父亲给我拨了一些银子，算是给门下弟子的俸禄，以后每月你就找我来领罢。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N朝你一拱手，笑了笑。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N低下头，不知道在沉思什么。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "俸禄也不是无限发的啊。"); //时间未到不能领取时说的话
        set("msg_silver_paid", "这是你的俸禄，加油！"); //领取成功时说的话
        set("msg_silver_score", "$N感动极了，饱含深情的拍了拍$n的头。\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N皱皱眉，转瞬间试了试$n的轻功，不禁眉开眼笑。\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N一拱手：「佩服！佩服！」\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "你还是先去练练功罢。"); //领取例银条件均不满足时说的话

//        set("book_count", 1);


        set_skill("force", 250);
        set_skill("dodge", 250);
        set_skill("finger", 250);
        set_skill("parry", 250);
        set_skill("liumai-shenjian", 250);
        set_skill("literate", 250);
        set_skill("yiyangzhi", 250);
          set_skill("beiming-shengong", 380);
        set_skill("lingbo-weibu", 250);

        map_skill("finger", "liumai-shenjian");
        map_skill("force", "beiming-shengong");
        map_skill("dodge","lingbo-weibu");
        map_skill("parry", "liumai-shenjian");
        prepare_skill("finger","liumai-shenjian");
        create_family("天龙寺", 1, "俗家第子");
//        set("class", "bonze");

        setup();

}


void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/master_name")!="枯荣大师" ) {

     command("say " + RANK_D->query_respect(ob) + "若想拜我派可先拜枯荣大师.\n");
                return;
        }


        if((int)ob->query("betrayer")>=1)
        {
command("say "+RANK_D->query_respect(ob)+"你多次叛师，背信弃义。我怎会收你。\n");
                return;
        }

        if ((int)ob->query("score")<1000){
        command("sigh"+ob->query("id"));
             command("say 你还是回去吧.我是不会收一个对大理国不忠之人的\n");
             return;
       }


        if ((int)ob->query("shen") < 20000) {
        command("say 学武之人，德义为先");
        command("say 在德行方面，" + RANK_D->query_respect(ob) +
                    "是否还做得不够？");
              return;
        }

        if ((int)this_player()->query_int() < 40 )
        {
   command("say 学习秘技要有好的悟性，"+RANK_D->query_respect(ob)+"资质不够\n");
                return;
        }

        command("chat 想不到我段誉又觅得一个可塑之才，真是可喜可贺。");
        command("recruit " + ob->query("id"));

        ob->set("title", GRN "天龙寺" NOR + YEL "使者" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, GRN "天龙寺" NOR + YEL "使者" NOR);
        
}

//string ask_me()
//{
//        mapping fam;
//        object ob;
//            if (!(fam = this_player()->query("family"))
//            || fam["family_name"] != "天龙寺")
//                return RANK_D->query_respect(this_player()) +
//                "与本派素无来往，不知此话从何谈起？";
//        if (query("book_count") < 1)
//                return "你来晚了，本派的「六脉神剑剑谱」不在此处。";
//        add("book_count", -1);
//        ob = new("/d/dali/obj/lmsj");
//        ob->move(this_player());
//        return "好吧，这本「六脉神剑剑谱」你拿回去好好钻研。";
//}

