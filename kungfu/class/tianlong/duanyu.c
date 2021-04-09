// duanyu.c 段誉
// by paladin

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
inherit "/inherit/char/silver.c";
int ask_skills();
// int ask_me();
int is_mentor()
{
	return 1;
}
void create()
{
         set_name("段誉", ({ "duan yu", "duan" }));
        //set("nickname", HIR "风流浪子" NOR);
        set("long",
                "他就是段誉，精通六脉神剑与北冥神功。\n");
	
        set("title",RED "大理" NOR + GRN  "王子" NOR);
	
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
		"技能" : (: ask_skills :),
		"skills" : (: ask_skills :),
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
        set_skill("yiyang-zhi", 250);
          set_skill("beiming-shengong", 380);
        set_skill("lingbo-weibu", 250);

        map_skill("finger", "liumai-shenjian");
        map_skill("force", "beiming-shengong");
        map_skill("dodge","lingbo-weibu");
        map_skill("parry", "liumai-shenjian");
        prepare_skill("finger","liumai-shenjian");
        create_family("天龙寺", 16, "俗家第子");
//        set("class", "bonze");

        setup();

}


int ask_skills()
{
	object ob=this_player();
	string msg;

	if ((string)ob->query("family/master_name")=="枯荣大师"&&(int)ob->query("betrayer")<1&&(int)ob->query("score")>=1000&&(int)ob->query("shen") >=20000&&(int)ob->query_int()>=40)
    {
		msg=HBBLU+YEL+"段誉目前所学过的技能：（共九项技能）\n"+NOR;
		msg+="\n";
		msg+="┌    一项基本知识    ──────────────────────┐\n";
		msg+="│  读书写字 (literate)                      - 已有小成 250/     0│\n";
		msg+="└────────────────────────────────┘\n";
		msg+="┌    四项基本功夫    ──────────────────────┐\n";
		msg+="│  基本轻功 (dodge)                         - 普普通通 250/     0│\n";
		msg+="│  基本指法 (finger)                        - 普普通通 250/     0│\n";
		msg+="│  基本内功 (force)                         - 普普通通 250/     0│\n";
		msg+="│  基本招架 (parry)                         - 普普通通 250/     0│\n";
		msg+="└────────────────────────────────┘\n";
		msg+="┌    四项特殊功夫    ──────────────────────┐\n";
		msg+="│□北冥神功 (beiming-shengong)              - 第五重楼 380/     0│\n";
		msg+="│□凌波微步 (lingbo-weibu)                  - 普普通通 250/     0│\n";
		msg+="│□六脉神剑 (liumai-shenjian)               - 普普通通 250/     0│\n";
		msg+="│  一阳指 (yiyang-zhi)                      - 普普通通 250/     0│\n";
		msg+="└────────────────────────────────┘\n";
		tell_object(ob,msg);
        return 1;
    }
	command("say 我有哪些功夫？我为什么要告诉你？");
	return 1;

}
int recognize_apprentice(object ob)
{
    if ((string)ob->query("family/master_name")=="枯荣大师"&&(int)ob->query("betrayer")<1&&(int)ob->query("score")>=1000&&(int)ob->query("shen") >=20000&&(int)ob->query_int()>=40)
    {
        return 1;
    }
	return 0;
}
void attempt_apprentice(object ob)
{
    command("say 我是个闲人，收徒弟肯定会误人子弟的。");
	return;
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
//        ob = new("/d/dalicheng/obj/lmsj");
//        ob->move(this_player());
//        return "好吧，这本「六脉神剑剑谱」你拿回去好好钻研。";
//}

