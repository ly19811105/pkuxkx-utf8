// kurong.c 枯荣大师
// by paladin

#include <ansi.h>
#include <title.h>
#include "/kungfu/class/tianlong/tianlong.h"
inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
    set_name("枯荣大师", ({ "kurong dashi", "kurong" }));
    set("nickname", HIR "枯荣大师" NOR);
    set("start_room","/d/tianlong/muwu");
    set("long",
            "他左边的一半脸色红润，皮光肉滑，有如婴儿,\n"
            "右边的一半却如枯骨，除了一张焦黄的面皮\n"
            "之外全无肌肉，骨头突了出来，宛然便是半个骷髅骨头。\n"
			"他在少商剑上有独到的造诣。\n");
    set("title",RED "天龙寺" NOR + GRN  "神僧" NOR);
    set("gender", "男性");
    set("age", 70);
    set("attitude", "friendly");
    set("shen_type", 1);
    set("str", 50);
    set("int", 30);
	set("con", 50);
    set("dex", 30);
    set("max_qi", 13000);
    set("max_jing", 11000);
    set("neili", 12000);
    set("max_neili", 12000);
    set("jiali", 380);
    set("combat_exp", 1500000);
    set("score", 500000);
    set("chat_chance", 100);
    set("inquiry", ([
                "六脉神剑剑谱" : (: ask_me :),
                ]));
    set("book_count", 1);

    set_skill("force", 150);
    set_skill("sword", 150);
    set_skill("duanjia-jian", 150);
    set_skill("dodge", 150);
        set_skill("duanshi-shenfa", 60);
    set_skill("finger", 150);
    set_skill("parry", 150);
    set_skill("literate", 150);
    set_skill("yiyang-zhi", 150);
    set_skill("kurong-shengong", 100);
    map_skill("force", "kurong-shengong");
    map_skill("dodge", "duanshi-shenfa");
    map_skill("sword", "duanjia-jian");
    map_skill("finger", "yiyang-zhi");
    prepare_skill("finger", "yiyang-zhi");
    create_family("天龙寺", 14, "神僧");
    set("class", "bonze");
    set_temp("apply/armor", 400);
    set_temp("apply/damage", 350);
    setup();

}


void attempt_apprentice(object ob)
{
	int index=3;
    if ((string)ob->query("family/family_name")!="天龙寺" ) {
        command("say " + RANK_D->query_respect(ob) + "若想拜我派可先拜本因方丈.\n");
        return;
    }

    if((int)ob->query("betrayer")>=2)
    {
        command("say "+RANK_D->query_respect(ob)+"你多次叛师，背信弃义。我怎会收你。\n");
        return;
    }

    if ((int)ob->query("score")<400){
        command("sigh"+ob->query("id"));
        command("say 你还是回去吧.我是不会收一个对不忠之人的\n");
        return;
    }
	 if((string)ob->query("gender")!="男性")
        {

			command ("say 本寺只收男弟子，佛门清净地，男女混住，成何体统？\n");
			return;
		}
    if ((int)ob->query("shen") < 10000) {
        command("say 学武之人，德义为先");
        command("say 在德行方面，" + RANK_D->query_respect(ob) +
                "是否还做得不够？");
        return;
    }

    /*command("chat 哈哈哈哈！！！！");
    command("chat 想不到在垂死之年，又觅得一个可塑之才，真是可喜可贺。");*///每个master说一样的话？既然没合适的话，不如不说不copy :)ZINE
	command("recruit " + ob->query("id"));
	tianlong(ob,index);
    ob->set("title", GRN "天龙寺" NOR + YEL "第十五代弟子" NOR);
//title系统记录玩家title by seagate@pkuxkx
	ob->set_title(TITLE_RANK, ob->query("title"));
}

string ask_me()
{
    mapping fam;
    object ob;
    if (!(fam = this_player()->query("family")) || fam["family_name"] != "天龙寺")
        return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
    if( this_player()->query("score") < 200 )
        return "你对本派贡献太小，本派的武学典籍还不能给你。";
    if (query("book_count") < 1)
        return "你来晚了，本派的「六脉神剑剑谱」不在此处。";
    add("book_count", -1);
    ob = new("/d/dalicheng/obj/lmsj");
    ob->move(this_player());
    return "好吧，这本「六脉神剑剑谱」你拿回去好好钻研。";
}


