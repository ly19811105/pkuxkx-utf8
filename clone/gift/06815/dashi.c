inherit NPC;
#include <ansi.h>;

int ask_gift();
void create()
{
        set_name(HIG"礼物大使"NOR, ({ "da shi", "dashi" }) );
        set("gender", "男性" );
        set("title",HIY"北大侠客行"NOR);
        set("nickname",HIY"ask da shi about 中秋礼物"NOR);
        set("age", 22);
        set("long",
                "他就是中秋节的礼物大使，给北大侠客行的玩家带来无限的欢乐！\n");
        set("combat_exp", 200000000);
        set("attitude", "friendly");
        set("rank_info/respect", HIG"大使"NOR);
        set("inquiry", ([
                "中秋礼物" : (: ask_gift :),
        ]));
        setup();
}
int ask_gift() //iszt@pkuxkx, 2006-10-01
{
        object me = this_player();
        object ob = new("/clone/gift/06815/cake.c");
        tell_object(me, HIG"礼物大使笑眯眯对你说道：“这是北大侠客行巫师精心烘烤的月饼，听说有神奇的效果！”\n"NOR);
        ob->move(me);
        return 1;
}
