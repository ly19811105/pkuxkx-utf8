// shandong.c
#include <ansi.h>
inherit ROOM;
#include <room.h>

void create()
{
        set("short", "山洞");
        set("long", @LONG
对面石壁上斜倚着一副骷髅骨，身上衣服已烂了七八成，那骷髅
骨宛然尚可见到是个人形。见石室中别无其他可怖事物。骷髅前面横
七竖八的放着十几把金蛇锥，石壁上有几百幅用利器刻成的简陋人形
(map) 。图形尽处，石壁上出现了十六个字(word)，也是以利器所刻。
十六字之旁，有个剑柄凸出在石壁之上，似是一把剑插入了石壁，直
至剑柄。
LONG );
        set("outdoors", "jinshe");
        set("sword_count", 1-random(4));
        set("exits", ([ /* sizeof() == 2 */
            "south" : __DIR__"yongdao2",
        ]));
        set("objects", ([
            __DIR__"obj/jinshe-zhui" : 1+random(5),
            __DIR__"obj/skeleton" : 1,
        ]));
        set("item_desc", ([
            "map"  : "石壁每个人形均不相同，举手踢足，似在练武。\n",
            "word" : "“重宝秘术，付与有缘，入我门来，遇祸莫怨。”\n",
        ]) );
        setup();
}
void init()
{
        add_action("do_think", "think");
        add_action("do_think", "lingwu");
        add_action("do_think", "watch");
        add_action("do_pull", "pull");
}
int do_pull(string arg)
{
        object ob, me= this_player();
        if (arg != "sword") return 0;
        if (query("sword_count") < 1)
                return notify_fail("剑好象已经被人拔走了。\n");
        if (this_player()->query("neili") < 1000)
        {
                message_vision(
"$N好奇心起，握住剑柄向外一拔，却是纹丝不动，竟似铸在石里一般。\n", me);
                me->set("neili", 10);
                return 0;
        }
        ob = new(__DIR__"obj/jinshe-jian");
        ob->set("weapon_prop/damage",150 + random(101));
        ob->move(me);
                message_vision(
"$N紧紧握住剑柄，潜运内力，嗤的一声响，拔了出来，剑柄下果然连有剑身。\n", me);
        me->add("neili",-1000);
        add("sword_count", -1);
        return 1;
}
int do_think(string arg)
{
        object ob;
        int c_exp,c_skill;
        ob = this_player();

        if (arg != "map") return 0;
        c_skill=(int)ob->query_skill("jinshe-jian", 1);
        c_exp=ob->query("combat_exp");

        if ((c_skill*c_skill*c_skill/10)> c_exp)
        {
                message_vision("$N的实战经验不足，无法领悟石壁内容。\n",ob);
                return 1; 
        }
        if (ob->query("jing")<20)
        {
                message_vision("$N太累了，现在无法领悟石壁内容。\n",ob);
                return 1; 
        }
        if (c_skill> 50)
        {
                message_vision("$N觉得石壁内容太肤浅了。\n",ob);
                return 1; 
        }

        message_vision("$N面对着石壁静思良久，对金蛇剑法似有所悟。\n",ob);
        ob->improve_skill("jinshe-jian", random(10*ob->query("int")));
        ob->receive_damage("jing", 5);
        return 1;
}


int valid_leave(object me, string dir)
{       
        int i;
        object *inv;
        object inv1;
        object inv2;
        inv = deep_inventory(me);

        for( i = 0; i<sizeof(inv); i++)
        {
                inv1 = inv[i];
                if( inv1->query("id") == "jinshe book1"||inv1->query("id") == "jinshe book2"||inv1->query("id") == "jinshe book3") 
                {
                return notify_fail(HIY"金蛇秘籍重现江湖会给你带来杀身之祸，你还是想清楚吧！\n"NOR);  
                }
        }      
        return ::valid_leave(me, dir);
}
/*
int clean_up()
{
       if (random(8))
       return 0;
        return 1;
}
*/
