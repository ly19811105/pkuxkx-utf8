// Modified by iszt@pkuxkx, 2007-02-21
#include <ansi.h>
#include <title.h>
// song.c 宋远桥
inherit NPC;
inherit F_MASTER;
inherit "/inherit/char/silver.c";

string ask_me();
string ask2();
string ask3();
void heal();
string ask_work();

void create()
{
        set_name("宋远桥", ({ "song yuanqiao", "song" }));
        set("nickname", RED "武当首侠" NOR);
        set("long",
                "他就是张三丰的大弟子、武当七侠之首的宋远桥。\n"
                "身穿一件干干净净的灰色道袍。\n"
                "他已年过六十，身材瘦长，满脸红光。恬淡冲和，沉默寡言。\n");
        set("title",RED "武当派" NOR + GRN +"真人" NOR);
        set("gender", "男性");
        set("age", 61);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        set("chat_chance", 100);
        set("chat_msg", ({
                (: heal :),
        }));
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.zhen" :),
                (: exert_function , "powerup" :)
        }) );
        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 80);
          set("combat_exp", 600000);
        set("score", 60000);
        set_skill("force", 160);
        set_skill("taiji-shengong", 160);
        set_skill("dodge", 120);
        set_skill("tiyunzong", 120);
        set_skill("cuff", 150);
        set_skill("taiji-quan", 150);
        set_skill("parry", 150);
        set_skill("sword", 150);
//      set_skill("taiji-jian", 60);
        set_skill("literate", 100);
        set_skill("taoism",150);
        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
//      map_skill("sword", "taiji-jian");
        prepare_skill("cuff", "taiji-quan");
        create_family("武当派", 2, "弟子");
        set("inquiry", ([
                "秘籍" : (: ask_me :),
                "下山" : (: ask3 :),
                "宋青书" : (: ask2 :),
                "例银" : (: ask_silver :),
        ]));
        set("silver_family_skill", "taiji-shengong"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "好吧，只要你勤于修道，仗义行侠，就在我这里领一份例银吧。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N取出一本小册子，写下了些什么。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N取出一本小册子翻了翻。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "一月未到，还不是发例银的时候。"); //时间未到不能领取时说的话

        set("book_count", 1);
        setup();
//      carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}
void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name")!="武当派" || (string)ob->query("class")!="taoist") {
                command("say 我武当乃是道家门派。");
                command("say " + RANK_D->query_respect(ob) + "若想拜我派可先拜谷虚师侄。");
                return;
        }
        if ((int)ob->query("shen") < 5000) {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
                command("say " + RANK_D->query_respect(ob) + "若能做出" +
                        "几件侠义之事，我一定收你。");
                return;
        }
        command("say 好吧，贫道就收下你了。");
        command("recruit " + ob->query("id"));
        if ((string)ob->query("gender")!="女性")
          ob->set("title" ,RED "武当派" NOR + GRN "道长" NOR);
        else
          ob->set("title" ,RED "武当派" NOR + GRN "女道长" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, ob->query("title"));
}
string ask_me()
{
        mapping fam;
        object ob;
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "武当派" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
        if (query("book_count") < 1)
                return "你来晚了，本派的内功心法不在此处。";
        add("book_count", -1);
        ob = new(__DIR__"force_book");
        ob->move(this_player());
        return "好吧，这本「太极十三式」你拿回去好好钻研。";
}
void init()
{
        object ob;
        mapping fam;
        ::init();
        ob = this_player();
        if ( (int)ob->query("shen") <0 && ((fam = ob->query("family")) && fam["master_id"] == "song yuanqiao"))
        {
                command("say 你多次杀人越货，胡作非为，我岂能仍是你的师傅。\n");
                command("expell "+ ob->query("id"));
        }
}
void heal()
{
        object ob=this_object();
        if (ob->query("eff_qi") < ob->query("max_qi"))
        {
                command("exert heal");
                command("enforce 50");
                return;
        }
        if (ob->query("qi") < ob->query("eff_qi"))
        {
                command("exert recover");
                return;
        }
        if (ob->query("jing") < ob->query("eff_jing"))
                command("exert regenerate");
        return;
}
string ask3()
{       if ((int)this_player()->query_temp("下山"))
                return "趁着天色还早，快些上路吧。";
        this_player()->set_temp("下山",1);
        command ("nod");
        return "好吧，但是切记下山后不可为非做歹。";
}
string ask2()
{
        command ("sigh");
        return "青书这个大逆不道的畜生，竟然害死七弟，我绝不会放过他。";
}
int accept_object(object me,object ob)
{       if (!present(ob,me))
        return notify_fail("你没有这件东西。");
        if ((string)ob->query("id")=="pei jian")
        {       command("sigh");
                command("say 多谢这位" + RANK_D->query_respect(this_player()) +
                        "替武当清除了这个败类。\n");
                this_player()->add("shen",5000);
         call_out("destroy",1,ob);
        }
if ((string)ob->query("id")!="pei jian")
{
    command("faint");
    command("say 贫道不认识此物，施主自便吧！\n");
      return 0;
}
    return 1;
}
        
void destroy(object ob)
{
     destruct(ob);
     return;
}
string ask_work()
{
        object me = this_player();
        string respect = RANK_D->query_respect(me);
        int reward;
        object ob;

        if(query("startroom") != file_name(environment(this_object())))
                return "我现在身有要事，还望"+respect+"见谅。";
        if(me->is_busy())
                return respect+"还是先忙完了吧。";
        if(me->query_temp("apply/constitution") < 30)
                return "好吧，"+respect+"就在此地劳动(work)吧。";
        if(me->query("gift/20070501"))
                return respect+"辛苦了，不用劳动了。";
        if(me->query("20070501/con"))
                return respect+"不妨去别处看看有没有需要帮忙劳动的。";
        command("thank " + query("id"));
        command("say 多谢"+respect+"，请下去休息休息吧。");
        write(HIW"你被奖励了：\n");
        reward = me->query_skill("force") + me->query_skill("parry");
        reward *= 5;
        write("\t"+chinese_number(reward)+"点经验；\n");
        me->add("combat_exp", reward);
        write("\t"+chinese_number(reward/5)+"点潜能。\n"NOR);
        me->add("potential", reward/5);

        me->set("20070501/con", 1);
        if(sizeof(me->query("20070501")) >= 4)
                me->set("gift/20070501", 1);
        if(me->query("gift/20070501"))
        {
                ob = new("/d/wizard/obj/xiandou2");
                ob->set("no_store", 1);
                ob->set("no_sell", 1);
                ob->set("no_pawn", 1);
                message_vision(HIM"$N交给$n一颗仙豆。\n"NOR, this_object(), me);
                ob->move(me);
                me->delete("20070501");
                command("chat* patfy "+me->query("id"));
                return "这是你用辛勤劳动换来的五一礼物，祝你五一快乐！劳动光荣！";
        }
        else
                return respect+"不妨去别处看看有没有需要帮忙劳动的。";
}
