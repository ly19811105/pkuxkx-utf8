// Room: /d/shaolin/jlyuan.c
// Date: YZC 96/01/19
#include <ansi.h>
#include <login.h>
inherit ROOM;
void create()
{
        set("short", "戒律院");
        set("long", @LONG
整个大殿门户紧闭，密不透风。即便是在白昼，也犹如黑
夜一般，每隔几步的墙上，点燃着几枝牛油巨烛。下方摆着一
排排烙铁、水牛皮鞭、穿孔竹板及狼牙棒等刑具。四周站满了
手持兵刃的执法僧兵。他们正用冷酷的眼神打量着你，令你不
禁浑身哆嗦起来。
LONG
        );
        set("no_fight", "1");
        set("no_sleep_room", "1");
        set("exits", ([
                "southdown" : __DIR__"guangchang3",
        ]));
        set("valid_startroom",1);
        set("objects",([
                CLASS_D("shaolin") + "/xuan-tong" : 1,
                __DIR__"npc/seng-bing2" : 3,
                __DIR__"npc/xiao-tong" : 1
        ]));
        set("no_task",1);
        setup();
}
void init()
{
        mapping fam;
        object ob;
        if( interactive(ob = this_player()) )
        {
           if( (mapp(fam = ob->query("family"))
                &&  fam["family_name"] == "少林派"
                &&  fam["generation"] <= 37
                &&  ob->query("guilty") == 0 )
				        || (SECURITY_D->get_status(this_player()) != "(player)"&&ob->query("env/sl_jyy_no_faint")) )//加个set才不晕，否则巫师编制的新手导师没法任务。ZINE
	              {
	              	return;
                }
          else
           {
			         message_vision(HIY "$N一进戒律院，...只听几声大喝，如同炸雷般在大殿里回响。\n"
			               "$N不禁浑身发抖，再也站立不住，腿一软，扑通一声跪了下来。\n\n" NOR, ob);
               ob->set("startroom", "/d/shaolin/jlyuan");
//               remove_call_out("processing");
               call_out("processing", 3, ob);
                }
        }
}
void processing(object ob)
{
        mapping fam;
        if (!ob) return;
        write(HIW "\n你定了定神，抬头细看，只见数十名持刀僧人将你团团围起来，\n"
                "一片雪亮的刀光逼得你眼都睁不开。正前方的高台上放着一把\n"
                "太师椅，居中高坐着位白须白眉的老僧，脸色铁青，目射精光，\n"
                "狠狠地瞪着你。\n\n\n" NOR);
        if ( !(fam = ob->query("family")) || fam["family_name"] != "少林派" )
        message_vision(HIY "玄痛一声大喝：尔等大胆狂徒，擅闯本寺护法松林，\n"
		"意在不轨，该当何罪！\n"
        "堂堂少林寺，岂能容你等宵小如此胡作非为！执法僧兵何在！\n\n" NOR, ob);
        if ( (fam = ob->query("family")) && fam["family_name"] == "少林派" )
        {
                if (ob->query("guilty") == 1)
                message_vision(HIY "玄痛一声大喝：$N！你离寺仅有数日，\n"
				"却在外杀人越货，胡作非为，"
                "累犯大戒，败坏本寺千载清誉！  你该当何罪？！执法僧兵何在！\n\n"
		NOR, ob);
				if (ob->query("guilty") == 3)
		        message_vision(HIY "玄痛一声大喝：$N！本寺护法松林历代向来\n"
				"不许门人弟子擅入，"
		        "你擅闯此地，意在不轨，该当何罪！执法僧兵何在！\n\n" NOR, ob);
		        if (ob->query("guilty") == 2)
			    {
                        message_vision(HIY "玄痛盯着$N看了半饷，说道：$N，\n"
						"你惩恶扬善，锄暴安良，当得表彰，"
                        "但出家人首戒杀生，你伤害人命，乃是僧家的重罪！ "
                        "你去罢，下次定不轻饶！\n\n" NOR, ob);
                        ob->set("guilty",0);
                        ob->set("startroom", START_ROOM);
                        ob->move("/d/shaolin/guangchang3");
                        return;
                }
        }
        call_out("responsing", 3, ob, 3);
}
void responsing(object ob, int i)
{
        int j;
        if( !ob ) return;
        message_vision(HIR "僧兵大声应道：弟子在！\n" NOR, ob);
        i--;
        j = random(3);
        if (i == 0)
        {
//                remove_call_out("beating");
                call_out("beating", 3, ob);
                return;
        }
        call_out("responsing", j, ob, i);
}
void beating(object ob)
{
        if( !ob ) return;
        message_vision(HIY "\n\n玄痛喝道：杖责三百，将$N打入僧监拘押三月，非洗心悔改，"
        "不得释放！意图越狱者罪加一等！\n\n" NOR, ob);
        message_vision(HIR "僧兵们一涌而上，乱棒齐下，$N痛得昏了过去......\n" NOR, ob);
        if ( ob->query("guilty") > 0 ) ob->set("guilty", 0);

        if (living(ob)) ob->move("/d/shaolin/jianyu");
        ob->unconcious();
}
int valid_leave(object me, string dir)
{
        mapping fam;
        if ( userp(me) && dir == "southdown" )
        {
                if((mapp(fam = me->query("family"))
                &&  fam["family_name"] == "少林派"
                &&  fam["generation"] <= 37 )
				|| SECURITY_D->get_status(this_player()) != "(player)")
                        return ::valid_leave(me, dir);
                else
                        return notify_fail("玄痛说道: 大胆，你还敢逃跑！执法僧兵何在！\n");
        }
        return ::valid_leave(me, dir);
}

