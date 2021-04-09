inherit ROOM;
#include <ansi.h>
void create()
{	
set("short", "发呆的工作室");
set("long", @LONG	
这里是发呆的工作室。温馨的音乐在房间里飘荡，一台超级电脑正在嗡嗡地工作。
屋里有一大片空地，据说是为安放音响而预留的。书架(shelf) 上全是小说，其中一本
是天神自己的作品。墙上有一副对联(duilian).抽屉(box)里面放了些乱七八糟的东西。
LONG	);	
set("valid_startroom",1);
set("no_steal", "1");
	set("exits", ([
                  "bw" : "/u/vast/biwuchang",
		"tls" : "/d/dali/dadian",
		"tai" : "/d/taishan/yuhuang",
		"sl" : "/d/shaolin/guangchang1",
		"dyd" : "/d/diaoyudao/duhaitan",
		"em" : "/d/emei/shanmen",
		"wg" : "/d/wudang/sanqingdian",
		"xx" : "/d/xingxiu/xxgate",
		"thd" : "/d/taohuadao/dating",
		"gy" : "/d/guiyunzhuang/guiyunting",
		"gm" : "/d/gumu/dating",
		"wz" : "/d/wizard/wizard_room",
		"ct" : "/d/city/guangchang",
		"qz" : "/d/quanzhen/gongmen",
		"quan" : "/d/quanzhou/zhongxin",
		"hs" : "/d/huashan/shufang",
                  "lj" : "/d/lingjiu/zhengting",
		"mj" : "/d/mingjiao/guangchang",
		"px" : "/d/pingxiwangfu/shu_fang",
		"pker" : "/d/pker/zonghengfu",
		"ry" : "/d/riyuejiao/dadian1",
              "xy" : "/d/xiangyang/xycenter",
              "xkd": "/d/xiakedao/shishi1",
              "east": "/u/vast/biwuchang",
              "up": "/u/idle/house.c",
              "bj": "/d/beijing/kedian",
	]));

set("item_desc", ([
		"shelf" : HIC "\n酒盈杯，书满架，名利不将心挂。\n" NOR,
		"duilian" : HIG "\n春夏秋冬行桃运\n" NOR + HIC "东南西北遇美人\n" NOR,
              "box"   : "里面放了一堆破烂，不知道能不能搜出什么好东东。\n"
	]));
setup();
}
void init()
{
    object me;
//    me = this_player();
    add_action("do_search", "search");
   
}

int do_search(string arg)
{
    int n;
    object me=this_player();
//    n = this_player()->query("neili");
    if( !arg || arg!="box")
   {
        write("不要到处乱翻别人的东西！\n");
        return 1;
    }

  if( me->is_busy() )
  return notify_fail("你上一个动作还没有完成呢。\n");                       
  message_vision("$N在抽屉中仔细搜索，希望能发现什么宝贝。\n", this_player());
  me->start_busy(9); 
  call_out("end",10,me);
  return 1;
}
void end(object me)
{
 object ob;              
 object obj = environment(me);
ob=new(__DIR__"cloth");
 ob->move(me);
          message_vision("$N找到了一件圣衣，得意洋洋地放在自己的身上。\n",me);
          return;                            
}
