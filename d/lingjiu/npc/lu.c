//lu.c
inherit NPC;

void create()
{
        set_name("梅花鹿", ({ "meihua lu", "lu" }) );
        set("race", "野兽");
        set("age", 2);
        set("long", "一只可爱的梅花鹿，它的血是大补之物。\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "头部", "身体", "爪子", "尾巴" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 3000);

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 10);
	set_temp("apply/defence",30);
	set_temp("apply/armor",10);

	set("shen_type",1);set("score",200);setup();
}

void die()
{
	message_vision("$N两腿一蹬，$N死了。\n", this_object());
	destruct(this_object());
}
