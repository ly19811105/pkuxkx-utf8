// File         : xieyanke.c
// Created By   : iszt@pkuxkx, 2006-09-20

#include <ansi.h>

inherit NPC;

int ask_name();
int ask_me();
int ask_ling();
int ask_dushi();
int ask_skill();

void create()
{
        set_name(HIB"青袍客"NOR, ({ "qingpao ke", "qingpao", "ke" }));
        set("long","这人青袍短须，容貌清癯，脸上隐隐有一层青气，负手而立，显得极为傲慢。\n"NOR);
        set("age", 41);
        set("combat_exp", 6400000);
        set("gender","男性");
        set("attitude","heroism");
        add_money("gold", 4);
        set("str", 20);
        set("dex", 20);
        set("con", 22);
        set("int", 24);
        set("per", 25);

        set_skill("literate", 150);
        set_skill("parry", 300);
        set_skill("force", 400);
        set_skill("strike", 400);
        set_skill("dodge", 300);

        set_skill("xiaowuxiang-gong", 400);
        set_skill("bizhen-qingzhang", 400);
        set_skill("tiyunzong", 400);

        map_skill("force", "xiaowuxiang-gong");
        map_skill("strike", "bizhen-qingzhang");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "bizhen-qingzhang");
        prepare_skill("strike", "bizhen-qingzhang");

        set("max_jing",2000);
        set("eff_jingli",2000);
        set("jiali",200);
        set("neili",18000);
        set("max_neili",10000);
        set("max_qi",5000);
        set("inquiry", ([
                "name" : (: ask_name :),
                "谢烟客" : (: ask_me :),
                "武功" : (: ask_skill :),
                "习武" : (: ask_skill :),
                "掌法" : (: ask_skill :),
                "here" : "少跟我罗嗦！\n",
                "rumors" : "少跟我罗嗦！\n",
        ]));

        setup();
        carry_object("/clone/cloth/male2-cloth.c")->wear();

}

int ask_name()
{
        object ob = this_object();
        object me = this_player();
        if(me->query("marks/xieyanke") >= 2)
        {
                message_vision(HIR"$N"HIR"大怒，头也不回的离开了，一时间竟无人敢于阻拦。\n"NOR, ob);
                me->set("marks/xieyanke", -1);
                destruct(ob);
                log_file("static/xieyanke",sprintf(" %s(%s)于%s惹怒谢烟客并错失机缘。\n", me->query("name"),me->query("id"),ctime(time()))); 
                return 1;
        }
        message_vision(HIC"$N"HIC"冷笑一声：「你也配知道谢某人的名字？」。\n"NOR, ob);  
        if(random(4) != 1)
                ob->fight_ob(me);
        else
                ob->kill_ob(me);
        return 1;
}

int ask_me()
{
        object ob = this_object();
        object me = this_player();
        if(me->query("marks/xieyanke") != 1)
                return 0;
        message_vision("$N脸色微微一变，道：「好，难得你还知道谢某人的名字！」\n"NOR, ob);      
        ob->set_name("谢烟客", ({"xie yanke", "xie", "yanke"}));
        ob->set("title", HIC"摩天居士"NOR);
        ob->add("inquiry", ([
                "玄铁令" : (: ask_ling :),
        ]));
        me->set("marks/xieyanke", 2);
        return 1;
}

int ask_ling()
{
        object ob = this_object();
        object me = this_player();
        if(me->query("marks/xieyanke") != 2)
                return 0;
        message_vision("$N对着$n哼了一声：「这块令本就是老夫之物，此次收回乃是物归原主！」\n"NOR, ob, this_player());
        ob->add("inquiry", ([
                "毒誓" : (: ask_dushi :),
                "誓言" : (: ask_dushi :),
        ]));
        me->set("marks/xieyanke", 3);
        return 1;
}

int ask_dushi()
{
        object ob = this_object();
        object me = this_player();
        string msg;
        if(me->query("marks/xieyanke") != 3)
                return 0;
        msg = HIG"只见$N脸上陡然青气一现，高举"HIB"铁片"HIG"，朗声念道：「玄铁之令，有求必应。」\n";
        msg += "$N转身对$n道：「我谢某当年的确发下这毒誓，不论从谁手中接过此令，都可依其所求办一件事，\n";
        msg += "                  就算是我谢某七世的冤家，也不会伸一指加害于他！」\n";
        msg += "说到这里，谢烟客不由地脸色一变，厉声说道：「今日从你手中取到此令，我自然会遵守我的诺言！」\n"NOR;
        message_vision(msg, ob, this_player());
        me->set("marks/xieyanke", 4);
        return 1;
}

int ask_skill()
{
        object ob = this_object();
        object me = this_player();
        if(me->query("marks/xieyanke") != 4)
                return 0;
        if(me->query("family/family_name") == "少林派")
        {
                message_vision("$N打量了$n半天，摇头道：「大师武功高强，我谢某人可没甚么武功。」", ob, me);
                return 0;
        }
        message_vision(CYN"$N"CYN"低头沉思，不知道在想些什么。\n"NOR, ob);

        remove_call_out("teach_skill");
        call_out("teach_skill", 4, ob, me);
        me->set("marks/xieyanke", 5);
        return 1;
}

void teach_skill(object teacher, object learner)
{
        string msg;
        if(learner->query("marks/xieyanke") != 5)
                return 0;
        msg = "$N低头考虑了一会，抬起头一声不发的给$n演示了一套掌法。低声解释了其中的运气方法。\n";
        message_vision(msg, teacher, learner);
        learner->improve_skill("bizhen-qingzhang", 2);
        msg = "$N哈哈哈大笑三声，倏忽远逝。\n";
        message_vision(msg, teacher, learner);
        learner->set("marks/xieyanke", 6);
        log_file("static/xieyanke",sprintf(" %s(%s)于%s遇见谢烟客并习得碧针清掌。\n", learner->query("name"),learner->query("id"),ctime(time()))); 
        message("channel:baowei", HIM"【江湖传闻】听说"+learner->query("name")+HIM"凭"HIB"玄铁令"HIM"向谢烟客习得「碧针清掌」！\n"NOR, users());
        destruct(teacher);
        return;
}
