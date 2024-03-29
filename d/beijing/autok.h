
#ifndef _AUTO_K_H_
#define _AUTO_K_H_

int auto_kill(object player)
{
    object me = this_object();

    if (player->query("special_skill/sociability")) return 0;  //sociability不被追杀
    if (//interactive(player) &&
        player->query_condition("bjkiller"))
    {
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, player);
        if (me->query("follow_killer") && player->query("combat_exp") > 150000)
            command("follow "+player->query("id"));
        return 1;
    }
//在紫禁城内并且非朝廷官员，格杀勿论(排除天安门广场，端门，武门和神武门)
    if (interactive(player)
        && strsrch(base_name(environment(me)), "/d/beijing/zijin/") != -1   //自己要在紫禁城内
        && strsrch(base_name(environment(player)), "/d/beijing/zijin/") != -1
        && strsrch(base_name(environment(player)), "/d/beijing/zijin/tianansquare") == -1
        && strsrch(base_name(environment(player)), "/d/beijing/zijin/tiananmen") == -1
        && strsrch(base_name(environment(player)), "/d/beijing/zijin/duanmen") == -1
        && strsrch(base_name(environment(player)), "/d/beijing/zijin/wumen") == -1
        && strsrch(base_name(environment(player)), "/d/beijing/zijin/shenwumen") == -1
        && player->query("class") != "officer" 
        && player->query("class") != "eunuch" )
    {
    //如果不是朝廷官员没有通行令
        if (!present("hgtongxing ling",this_player())){
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, this_player());
      if (me->query("follow_killer") && player->query("combat_exp") > 150000)
            command("follow " + player->query("id"));
        return 1;
        }
            return 0;
    }
    return 0;
}

int accept_fight(object player)
{
        object me=this_object();
        if(living(me))
        {
        command("say " + RANK_D->query_self_rude(me) + "正想找人杀呐，今天算你倒霉。\n");
        player->apply_condition("bjkiller", 100 + player->query_condition("bjkiller"));
        me->kill_ob(player);
        }
        return 1;
}

int accept_kill(object player)
{
        object me=this_object();
        if(living(me))
        {
        command("say " + RANK_D->query_self_rude(me) + "正想找人杀呐，今天算你倒霉。\n");
        player->apply_condition("bjkiller", 100 + player->query_condition("bjkiller"));
        me->kill_ob(player);
        }
        return 1;
}

int accept_hit(object player)
{
		accept_kill(player);
    return 1;
}

void set_shiwei_status(int lvl)
{
        int exp;
        object me=this_object();

        me->set("gender", "男性");
        me->set("attitude", "heroism");
        me->set("shen_type",0);
        me->set("score", 100);
        me->set("str", 30);
        me->set("int", 30);
        me->set("con", 30);
        me->set("dex", 30);

        me->set("max_qi", lvl*10);
        me->set("eff_qi", lvl*10);
        me->set("qi", lvl*10);

        me->set("max_jing", lvl*10);
        me->set("eff_jing", lvl*10);
        me->set("jing", lvl*10);

        me->set("jingli", lvl*20);
        me->set("max_jingli", lvl*20);

        me->set("neili", lvl*20);
        me->set("max_neili", lvl*20);

        me->set("jiali", lvl);

        exp = lvl*lvl/10*lvl;

        me->set("combat_exp", exp+random(exp/4));

        me->set_skill("force", lvl);
        me->set_skill("dodge", lvl);
        me->set_skill("cuff", lvl);
        me->set_skill("strike",lvl);
        me->set_skill("hand",lvl);
        me->set_skill("parry", lvl);
        me->set_skill("blade",lvl);
        me->set_skill("sword",lvl);
        me->set_skill("staff",lvl);
        me->set_skill("whip",lvl);
        me->set_skill("axe",lvl);
        me->set_skill("halberd",lvl);
        me->set_skill("spear",lvl);
        me->set_skill("claw",lvl);

        me->set_skill("bixue-xinfa", lvl);
        me->set_skill("longfeng-xiang", lvl);
        me->set_skill("qingmang-jian", lvl);
        me->set_skill("juemen-gun", lvl);
        me->set_skill("fenglei-dao", lvl);
        me->set_skill("taizu-quan", lvl);
        me->set_skill("kuangfeng-dao", lvl);
        me->set_skill("kuangfeng-jian", lvl);
        me->set_skill("lujia-ji", lvl);
        me->set_skill("bainiao-qiangfa", lvl);
        me->set_skill("huzhua-shou", lvl);
        me->set_skill("juehu-zhang", lvl);
        me->set_skill("kuihua-zhua", lvl);
        me->set_skill("duanyun-bian", lvl);
        me->set_skill("leiting-axe", lvl);

        me->map_skill("force", "bixue-xinfa");
        me->map_skill("sword", "qingmang-jian");
        me->map_skill("blade", "fenglei-dao");
        me->map_skill("dodge", "longfeng-xiang");
        me->map_skill("strike", "juehu-zhang");
        me->map_skill("parry", "huzhua-shou");
        me->map_skill("hand", "huzhua-shou");
        me->map_skill("whip", "duanyun-bian");
        me->map_skill("halberd", "lujia-ji");
        me->map_skill("axe", "leiting-axe");
        me->map_skill("claw", "kuihua-zhua");
        me->map_skill("staff", "juemen-gun");
        me->map_skill("spear", "bainiao-qiangfa");
        me->map_skill("cuff", "taizu-quan");

        me->prepare_skill("strike", "juehu-zhang");
        me->prepare_skill("hand", "huzhua-shou");

        me->carry_object("/d/beijing/npc/obj/shiweicloth")->wear();
        if (random(2) == 1)
            me->carry_object("/d/city/obj/gangjian")->wield();
        else
            me->carry_object("/clone/weapon/gangdao")->wield();
}

#endif


