// Room: /u/hacky/quanzhen/tianzd.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;
string look_notice();
string look_wall();
void create()
{
	set("short", HIW"天尊殿"NOR);
	set("long", @LONG
这是一座古朴的殿堂。西首的墙(wall)上挂满了各类武功图谱，不少白须白
眉的老道长们正端坐在图谱画轴之前，似乎在苦苦思索。东首的墙上贴了几张纸
条(notice)。南北山墙是高及屋顶的大书架，走近细看，它们是各种各样的道家
心法，屋正中摆着几张矮几诃和几个团，几位老道长正在入定中。正南边是玄虚
堂，西边是门楼。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"zoulang10.c",
  "south" : __DIR__"chongxt.c",
  "west" : __DIR__"menlou.c",
]));
  set("item_desc",([
  	"wall" : (:look_wall:),   
    "notice": (:look_notice:)]));
	set("objects", ([ /* sizeof() == 1 */
CLASS_D("quanzhen")+"/qiu" : 1,
]));
	set("no_clean_up", 0);

	setup();
}
string look_wall()
{
    object me=this_player();
    if (me->query("family/family_name") != "全真派")
    {
        return "这里似乎绘着一些全真入门功夫。\n";
    }
    if (me->is_busy())
    {
        return "你正忙着呢。\n";
    }
    if (me->query("exp/qznewbiejob")<10000)
    {
        return "这里似乎绘着一些全真入门功夫。\n";
    }
    if (!me->query_skill("sanhua-judingzhang"))
    {
        if (me->query("exp/qznewbiejob")>me->query("str")*me->query("con")*me->query("int"))
        {
            me->set_skill("sanhua-judingzhang",10);
            tell_object(me,HIC"你的『三花聚顶掌法』进步了！\n"NOR);
            return "你从墙上的武功图谱悟出了全真派失传绝技——三花聚顶掌法！\n";
        }
        return "墙上的武功似乎是一种极厉害的掌法，可惜你还无法参透，也许多去劳作，放松身心，可以有助于其。\n";
    }
    else 
    {
        if (me->query("jing")>100&&me->query("neili")>20)
        {
            me->improve_skill("sanhua-judingzhang",1+random((int)me->query("int")));
            me->add("jing",-50);
            me->add("neili",-10);
            me->add_busy(1);
            return "你仔细研究墙上的图谱，三花聚顶掌法获得些许进步。\n";
        }
        else
        {
            return "你精神太差，无法领会深奥武功。\n";
        }
    }
    
}

string look_notice()
{
    object me=this_player();
    string *task_list=({"药圃帮忙","校经房"});
    int n;
    string msg;
    if (me->query("family/family_name") != "全真派")
    {
        return "纸条上的字全用道家典故写就，虽然每个字都认识，但连起来就不知道是什么意思了。\n";
    }
    if (me->query("combat_exp")<(int)me->query("int")*500)
    {
        return "纸条上是全真弟子需要做的工作，可是上面并没有你的名字。\n";
    }
    if (time()-me->query("qznewbiejob_time")<90-random(10))
    {
        return "纸条上是全真弟子需要做的工作，可是上面并没有你的名字。\n";
    }
	if (me->query("exp/qznewbiejob")>=200000)
	{
		return "纸条上是全真入门弟子需要做的工作，再也不会出现你的名字了。\n";
	}
    me->set("qznewbiejob_time",time());
    n=random(sizeof(task_list));
    msg="\n\n";
    msg+=HIM"\t全真弟子任务\n"NOR;
    msg+="\t"+me->query("name")+"("+me->query("id")+")听令：\n";
    if (n==0)
    {
        me->set_temp("qznewbiejob/task2/start",1);
        msg+=HIM"\t速去药圃帮助老者，不得有误。\n"NOR;
        return msg;
    }
    if (n==1)
    {
        me->set_temp("qznewbiejob/task3/start",1);
        msg+=HIM"\t速去校经房帮助道童，不得有误。\n"NOR;
        return msg;
    }
}

void init()
{
    object me=this_player();
    if (me->query_skill("fx-step"))
    {
        me->set_skill("jinyan-gong",me->query_skill("fx-step",1));
        me->delete_skill("fx-step");
        me->set_skill_mapped("dodge","jinyan-gong");
        tell_object(me,HIM+BLINK+"你的飞仙步已经被自动转化成金雁功。\n"NOR);
    }
}