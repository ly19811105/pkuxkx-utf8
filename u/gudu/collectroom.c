
// by gudu

inherit ROOM;

void create()
{
        set("short", "物件收集房");
        set("long", @LONG
这是司马长风家的收藏室。里边有很多名贵的宝物，江湖人人觊觎而得不到的宝物很多
都被司马大侠收藏到了此处，据说目的是为了消除江湖仇杀。
LONG );

        set("exits", ([ /* sizeof() == 1 */
        "out" : "/u/gudu/workroom.c" ]));
/*

	set("objects", ([
        "/d/shaolin/obj/puti-zi": 1,
        "/d/shaolin/obj/fumo-dao": 1,
        "/d/shaolin/obj/jingang-zhao": 1,       
        "/d/baituo/obj/shezhang": 1,
        "/d/yuewangmu/obj/wumuyishu": 1,
        "/d/quanzhou/obj/xuantiejian": 1,
        "/d/dali/obj/yxbj": 1,
        "/d/dali/obj/bmsg": 1,
        "/d/dali/obj/lbwb": 1,
        "/d/diaoyudao/obj/ruanjia": 1,
        "/d/emei/houshan/npc/obj/renshen": 5,
        "/d/emei/houshan/npc/obj/pilidan": 5,
        "/d/guiyunzhuang/obj/shanshen": 5,
        "/d/lingjiu/obj/tlbb": 2,
        "/d/mingjiao/npc/obj/jinhua": 50,
        "/d/mingjiao/npc/obj/shenghuo-ling": 1,
        "/d/pingxiwangfu/npc/obj/baojia": 1,
        "/d/pingxiwangfu/npc/obj/herobook": 1,
        "/d/pingxiwangfu/npc/obj/herosword": 1,
        "/d/pingxiwangfu/npc/obj/yangqiang": 1,
        "/d/yuewangmu/obj/dpqiang": 1,        
        "/d/taohuadao/obj/ruanwei-jia": 1,
        "/d/taohuadao/obj/yuxiao": 1,       
	]));
*/

        set("valid_startroom", 1);
        set("no_clean_up", 0);
        setup();

        replace_program(ROOM);

}


