// sherou.c 蛇肉
inherit F_FOOD;
inherit ITEM;
void create()
{
        set_name("蛇肉", ({ "she rou", "rou" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一条蛇肉，看起来很新鲜，也许可以用来吃。\n");
                set("unit", "条");
                set("value", 50);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
    setup();
}
