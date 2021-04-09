// 蒙古兵

#define GATE_BREAK 6
#define GATE "south"
#define SPEED 15
inherit NPC;
#include <ansi.h>
string *spot=({
       "/d/xiangyangnan/jingmen.c",
       "/d/xiangyang/mroad1.c",
       "/d/xiangyang/mroad2.c",
       "/d/xiangyang/mroad3.c",
       "/d/xiangyang/mroad4.c",
       "/d/xiangyang/sgate.c",
       "/d/xiangyang/xysouth3.c",
       "/d/xiangyang/tudimiao.c",
       "/d/xiangyang/xysouth3.c",
       "/d/xiangyang/xysouth2.c",
       "/d/xiangyang/chdzh.c",
       "/d/xiangyang/xysouth2.c",
       "/d/xiangyang/xysouth1.c",
       "/d/xiangyang/zhensuo.c",
       "/d/xiangyang/xysouth1.c",
       "/d/xiangyang/xycenter.c",
       "/d/xiangyang/xywest1.c",
       "/d/xiangyang/xywest2.c",
       "/d/xiangyang/sfgate.c",
       "/d/xiangyang/sfdating.c",
       "HALT"
});
#include "mgb.h"
