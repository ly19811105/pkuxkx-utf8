#include <ansi.h>

inherit ITEM;

void create()
{

       set_name(HIR"火焰"NOR, ({ "huo yan"}) );
       set("weight", 30000);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("long", HIR"火焰高约尺，色作纯碧，鬼气森森，和寻常火焰大异。\n"NOR );
               set("no_get", 1);
               set("value", 1);
               set("unit", "堆");
               set("fire_name", "火焰");
               set("location", 1);
       }
       setup();
}

string *fire_msg = ({
        BLU"火焰"NOR, RED"火焰"NOR, WHT"火焰"NOR, GRN"火焰"NOR, MAG"火焰"NOR,
        HIB"火焰"NOR, HIR"火焰"NOR, HIW"火焰"NOR, HIG"火焰"NOR, HIM"火焰"NOR,
        YEL"火焰"NOR, HIY"火焰"NOR,
});

void init()
{
        if (base_name(environment())!="/d/xingxiu/riyuedong" && find_call_out("dest") < 0)
                call_out("dest", 300);   
        this_object()->set("name", fire_msg[random(sizeof(fire_msg))]);    
        remove_call_out("change");
        call_out("change", 50); 
}

void change()
{
        tell_room(environment(this_object()),this_object()->name()+HIR"豁然一暗，接着火光爆长，竟然变了颜色，看起来怪异无比！\n"NOR);    
        this_object()->set("name", fire_msg[random(sizeof(fire_msg))]);    
        remove_call_out("change");
        call_out("change", 50);  
}
 
void dest()
{
        tell_room(environment(this_object()),HIR"火焰渐渐地熄灭了。\n"NOR);
        destruct(this_object());
}

