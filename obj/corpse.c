#pragma save_binary
// corpse.c
#include <weapon.h>
inherit STAFF;

int decayed;

void create()
{
	set_name("无名尸体", ({ "corpse" }) );
	if (clonep())
		set_default_object(__FILE__);
	else {
        set("long", "这是一具无名尸体。\n");
        set("unit", "具" );
        set("env/can_get",1);
		set("wield_msg", "$N扛起$n准备战斗。\n");
		set("unwield_msg", "$N把$n重新背在肩上。\n");
}
        decayed = 0;
      if( clonep(this_object()) ) call_out("decay", 600, 1);
	init_staff(10);
	setup();
}

int is_corpse() { return decayed < 2; }
int is_character() { return decayed < 1; }
int is_container() { return 1; }

string short() { return name() + "(" + capitalize(query("id")) + ")"; }

void decay(int phase)
{
        decayed = phase;
        switch(phase) {
                case 1:
                        say( query("name") + "开始腐烂了，发出一股难闻的恶臭。\n" );
                        switch(query("gender")) {
                                case "男性":
                                        set_name("腐烂的男尸", ({ "corpse", "尸体" }) );
                                case "女性":
                                        set_name("腐烂的女尸", ({ "corpse", "尸体" }) );
                                default:
                                        set_name("腐烂的尸体", ({ "corpse", "尸体" }) );
                        }
                        set("long", "这具尸体显然已经躺在这里有一段时间了，正散发著一股腐尸的味道。\n");
                        call_out("decay", 120, phase + 1);
                        break;
                case 2:
                        say( query("name") + "被风吹乾了，变成一具骸骨。\n" );
                        set_name("一具枯乾的骸骨", ({ "skeleton", "骸骨" }) );
                        set("long", "这副骸骨已经躺在这里很久了。\n");
                        call_out("decay", 60, phase + 1);
                        break;
                case 3:
                        say( "一阵风吹过，把" + query("name") + "化成骨灰吹散了。\n" );
                        if( environment() ) {
                                object *inv;
                                int i;
                                
                                inv = all_inventory(this_object());
                                for(i=0; i<sizeof(inv); i++) 
                                       inv[i]->move(environment());
                        }
                        destruct(this_object());
                        break;
        }
}

object animate(object who, int time)
{
        object zombie;

        if( !environment() ) return 0;

        seteuid(getuid());
        zombie = new("/obj/npc/zombie");
        zombie->set_name( (string)query("victim_name") + "的僵尸", ({ "zombie" }) );
        zombie->move(environment());
        zombie->animate(who, time);

        destruct(this_object());
        return zombie;
}
 
