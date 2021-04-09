// Npc: /kungfu/class/shaolin/qing-fa.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_for_join();
string ask_for_join();
string ask_for_leave();

void create()
{
        set_name("清法比丘", ({
                "qingfa biqiu",
                "qingfa",
                "biqiu",
        }));
        set("long",
                "他是一位体格强健的壮年僧人，他生得虎背熊腰，全身似乎蕴含\n"
                "着无穷劲力。他身穿一袭白布黑边袈裟，似乎身怀武艺。\n"
        );

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "还俗"  : (: ask_for_leave :),
        ]));

        set("age", 30);
        set("shen_type", 1);
        set("str", 25);
        set("int", 17);
        set("con", 50);
        set("dex", 21);
        set("max_qi", 450);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 50000);
        set("score", 500);

        set_skill("force", 50);
        set_skill("tongzi-gong", 50);
        set_skill("dodge", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("cuff", 50);
        set_skill("jingang-quan", 50);
        set_skill("parry", 50);
        set_skill("buddhism", 50);
        set_skill("literate", 50);

        map_skill("force", "tongzi-gong");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");

        prepare_skill("cuff", "jingang-quan");

        create_family("少林派", 40, "弟子");

        setup();
        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}


void init()
{
        add_action("do_kneel", "kneel");
        add_action("do_decide", "decide");
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( (string)me->query("class")=="bonze" )
                return "阿弥陀佛！你我同是出家人，何故跟贫僧开这等玩笑？\n";

        if(!undefinedp(me->query("marry/lover")))
                return "阿弥陀佛！施主尘缘未了，还是罢了吧。\n";
                        if( (string)me->query("gender") != "男性" )

                return "阿弥陀佛！善哉！善哉！女施主若真心皈依我佛，可去后山庵里受戒。\n";

        me->set_temp("pending/join_bonze", 1);
        return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，请跪下(kneel)受戒。\n";
}
string ask_for_leave()
{
        object me;

        me = this_player();

        if( (string)me->query("class")!="bonze" )
                return "阿弥陀佛！施主并未出家，何故跟贫僧开这等玩笑？\n";

        if( (string)me->query("family/family_name") != "少林派")
                return "阿弥陀佛！施主非我少林弟子，还俗的事情贫僧作不得主。\n";

        me->set_temp("pending/leave_bonze", 1);
                return "阿弥陀佛！如果" + RANK_D->query_respect(me) + "真想离我佛门而去，就请下决心(decide)吧！。\n";
}

int do_decide()
{
        string* skillname;
        int lev;
        mapping skills;
        int i;
        object me = this_player();
        object body;
        
        if (me->query_temp("pending/leave_bonze") != 1)
        {
                tell_object(me,"什么?\n");
                return 1;
        }
        message_vision("清法比丘对$N说道：「阿弥陀佛！从此施主就不再是我少林门下了，请好自为之！」\n",me);
        tell_object(me,HIR "你决定判出少林门下！\n" NOR);
        me->delete_temp("pending/leave_bonze");
        me->delete("task_time");
        me->delete("quest");
        me->set("score",0);
        me->delete("family");
        me->delete("class");
        me->delete_skill("buddhism");
        body = me->query_temp("link_ob");
        me->set("title","平民百姓");
        me->set("name",body->query("name"));
        me->delete("shaolin/old_name");
          if (me->query("combat_exp") >= 1000)
                me->add("betrayer",1);
        return 1;
}
                
int do_kneel()
{
        object me = this_player();

        string *prename =
         ({ "虚", "空", "明", "净" });
//       ({ "虚", "空", "明", "圆", "净", "悟", "法" });
        string name, new_name;

        if( !me->query_temp("pending/join_bonze") )
                return 0;

        message_vision(
                "$N双手合十，恭恭敬敬地跪了下来。\n\n"
                "$n伸出手掌，在$N头顶轻轻地摩挲了几下，将$N的头发尽数剃去。\n\n",
                me, this_object() );
        name = me->query("name");
        new_name = prename[random(sizeof(prename))] + name[0..0];
        command("say 从今以后你的法名叫做" + new_name + "。");
        command("smile");
        me->set("shaolin/old_name",name);
        me->delete_temp("pending/join_bonze");
        me->set("name", new_name);
        me->set("class", "bonze");
        if(me->query("family/family_name")=="少林派")
                me->set("title",HIR "少林" NOR + CYN "小沙弥" NOR);
        me->set("K_record", me->query("PKS") + me->query("MKS"));
        me->set("shen_record", me->query("shen"));
        me->set("shen", 0);

        return 1;
}

void attempt_apprentice(object ob)
{
        if( (string)ob->query("gender") != "男性" )
        {
                command ("say 阿弥陀佛！女施主呀，贫僧可不敢开这等玩笑啊。");
                return;
        }
        if( (string)ob->query("family/family_name") != "少林派" && ob->query("is_shaolin"))
        {
                command ("say 阿弥陀佛！" + RANK_D->query_respect(ob) +"既然已经叛出少林，那又何必回少林。");
                return;
        }
        
        if( (string)ob->query("class")!="bonze" )
        {
                command ("say 阿弥陀佛！贫僧就收下你做『俗家弟子』了。");
        }
        command("say 阿弥陀佛，善哉！善哉！");
        command("recruit " + ob->query("id"));
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("is_shaolin", 1);
                if (this_player()->query("class")=="bonze")
                {
                        ob->set("title",HIR "少林" NOR + CYN "小沙弥" NOR);
                        return;
                }
                else
                {
                        ob->set("title",HIR "少林" NOR + CYN "俗家弟子" NOR);
                        return;
                }

}

void re_rank(object student)
{
                if (this_player()->query("class")=="bonze")
                {
                        student->set("title",HIR "少林" NOR + CYN "小沙弥" NOR);
                        return;
                }
                else
                {
                        student->set("title",HIR "少林" NOR + CYN "俗家弟子" NOR);
                        return;
                }
}

