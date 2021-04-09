// huodu.c
// by cleansword
// 96-02-16 YZC disabled NPC killing, & "unknown" problem when revealed

#include <ansi.h>

inherit NPC;

string ask_me(object who);

void create()
{
        set_name("何师我", ({ "he shiwo", "he" }) );
        set("title", MAG "丐帮" NOR + YEL "五袋" NOR + MAG "弟子" NOR);
        set("gender", "男性" );
        set("shen_type", -1);
		set("shen",-10000);
        set("age", 28);
        set("str", 25);
        set("con", 25);
        set("dex", 29);
        set("int", 29);
	set("per", 10);
        set("long",
                "他是丐帮新近加入的弟子，可也一步步升到了五袋。\n他长的极其丑陋，脸上坑坑洼洼。\n" );

        set("inquiry", ([
                "霍都"   : (: ask_me :),
        ]) );

        set_skill("blade", 50);
	set_skill("liuhe-dao", 40);
        set_skill("dodge", 40);
	set_skill("xiaoyaoyou", 40);
        set_skill("hand", 30);
	set_skill("shexing-shou", 30);
        set_skill("parry", 50);

	map_skill("blade", "liuhe-dao");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("hand", "shexing-shou");
	map_skill("parry", "liuhe-dao");

	prepare_skill("hand", "shexing-shou");

        setup();

        carry_object("/d/city/obj/gangdao")->wield();
}

string ask_me(object who)
{
        int i;
        object *ob;

        if( query("revealed") ) {
                if( is_killing(who->query("id")) ) return "你既然知道了我的身分，今日休想活命！\n";
                else {
                        kill_ob(who);
                        who->fight_ob(this_object());
                        return "老子就是霍都，霍都就是你老子！纳命来吧！\n";
                }
        }

        if( (random(10) < 5) || is_fighting() )
                return "我…不知道。\n";

        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",  20);
        message("vision",
                HIY "何师我眼中突然放出异样的光芒，颤声说道，看来...你都知道了？\n"
                "何师我大喝一声，叫道，既然如此，老子今天反正豁出去，跟你拼了。\n"
 NOR,
                environment(), this_object() );

        set("pursuer", 1);
        set_name("霍都", ({ "huo du", "huo" }) );
        set("title", MAG "金轮法王的前弟子" NOR);
        set("long",
                "他曾是金轮法王的二弟子，可他为了自己活命曾于老师的生命于不顾。\n");
        set("attitude", "aggressive");
        set("vendetta/authority", 1);
	set("per", 25);
        set("chat_msg_combat", ({
                (: random_move :)
        }) );
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );
        set("bellicosity", 10000);
        set("combat_exp", 40000);
        set("shen", - 10000);
  	ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
                if( !userp(ob[i]) ) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
//      carry_object("/d/city/obj/mianju.c");
        set("revealed", 1);
        carry_object("/kungfu/class/gaibang/yuzhu_zhang");
        return "老子就是霍都，霍都就是你老子！纳命来吧！\n";
}
