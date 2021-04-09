// story:bizhen 玄铁令——学习碧针清掌

#include <ansi.h>

nosave string char_id;
nosave string char_name;

int give_gift();
object select_character();

mixed *story = ({
"东方雨游历江湖，某日，登华山...                                       ",
"自古华山一条路，既陡且险，东方雨虽轻功卓绝，却也不免有些气喘。        ",
"一路景色宜人，然非常人走常人路，东方雨有些兴致索然...                 ",
"东方雨决定攀崖而上，取险境以求美景...                                 ",
"...                                                                   ",
"......                                                                ",
"山崖的一棵古松上，一暗红色的疑似绸状物映入东方雨的眼帘。              ",
"『葵 ! 花 !! 宝 !!! 典 !!!! 』                                        ",
"东方雨欣喜若狂！                                                      ",
"『这回，该我发达了！』                                                ",
"『小倩儿啊小倩儿，这回你死定了，我东方雨的武林排名很快就要越过你了！』",
"东方雨展开袈裟...                                                     ",
"『欲练神功，可先自宫...』                                             ",
"东方雨一咬牙，抽出『破风刀』，手一挥，只听惨叫一声，似乎有一物飞出... ",
"东方雨运气练功...                                                     ",
"东方雨展开袈裟往下看...                                               ",
"『若不自宫，亦能成功...』                                             ",
"东方雨口瞪目呆，没头没脑的叫道：我...kao~!                            ",
"东方雨接着往下看...                                                   ",
"『即便自宫，未必成功...』                                             ",
"东方雨愤懑难当，体内真气乱串，鲜血从口中狂喷而出...                   ",
"东方雨发狂了！                                                        ",
"东方雨挥刀狂砍，华山山崖一时飞沙走石，金石相撞碰出的火花四溅...       ",
"突然，东方雨脚底一绊，向前扑倒，手中宝刀脱手而出...                   ",
"『啊』～～～                                                          ",
        (: give_gift :),
});

string prompt() { return HIG "【江湖逸事】" NOR; }

void create()
{
        seteuid(getuid());
}



mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}


int give_gift()
{

        int i;
        object env,ob;
        object *players;
                object gob;
        string msg;

        players = users();
        if (sizeof(players) >= 10)
        {
                for (i = 0; i < 10; i++)
                {
                        ob = players[random(sizeof(players))];
                        if (wizardp(ob)) continue;
                        if (ob->is_fighting()) continue;
                        if (!environment(ob)) continue;
                        if (ob->query_temp("netdead")) continue;

                }
        if(!ob) return 1;
        ob->set("max_qi",10);
        ob->set("max_jing",10);
        tell_object(ob, HIC "一件不明物体从天而降，你眼前一黑，被砸晕了过去！\n" NOR);
        if (!random(10))
        ob->unconcious();
        gob = new("/clone/story/obj/pofeng-dao.c");
        gob->move(ob, 1);
if (ob)
{
        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + ob->name(1)+"被来历不明的物体砸晕了！");
}
        STORY_D->remove_story("pofeng");
      }
        return 1;
}
