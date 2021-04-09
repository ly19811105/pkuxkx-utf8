//qizhong1厚土旗 the last
#include <ansi.h>
inherit NPC;
void create()
{
        set_name(HIW"厚土旗众"NOR, ({ "qi zhong","zhong" }));
        set("long",
                "他是明教厚土旗的旗众。\n"
                "他身穿黄衣，脸露狞笑，一付凶神恶煞的样子\n");
        set("gender", "男性");
        set("age", 23);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 16);
        set("int", 16);
        set("con", 20);
        set("dex", 22);
        set("max_qi", 200);
        set("max_jing", 100);
        set("neili", 200);
        set("max_neili", 200);
        set("jiali", 5);
        set("combat_exp", 1500);
        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_skill("parry", 20);
        create_family("明教",22,"教徒");
        setup();
        set("chat_chance", 2);
        set("chat_msg", ({
"明教厚土旗旗众唱道：“焚我残躯，熊熊圣火，生亦何欢，死亦何苦！！”\n",
"明教厚土旗旗众唱道：“为善除恶，唯光明故，喜乐悲愁，皆归尘土！！”\n",
        }) );
        carry_object("/d/mingjiao/obj/huangyi.c")->wear();
}
