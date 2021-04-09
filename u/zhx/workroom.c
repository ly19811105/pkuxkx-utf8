// 第1次修改
// 制作人:advent
// 2000-1-24
// 文件类型  房间 

inherit ROOM;

void create ()
  {
    set("short","行云居");
set("long", @LONG
这就是小学徒行云的住处，只见一条清溪旁结着七、八间茅屋，茅屋
前后左右都是花圃，种满了诸般花草。

LONG);

        set("exits",([
       "xiakedao" : "/d/xiakedao/shatan1",
      "wudang" : "/d/wudang2/sanqing",
      "armor":"/u/aiai/room/armorroom",
               "wz": "/d/wizard/wizard_room",
                 "xiangyang":"/d/xiangyang/xycenter.c",
            "wc":"/u/advent/biwuchang",
       "emei":"/d/emei/dadian",
"down":"/u/advent/happyroom",
            "city":"/d/city/guangchang",
         "fumo":"/d/shaolin/fumoquan",
          "ruzhou":"/d/shaolin/ruzhou",
          "taishan":"/d/taishan/fengchan",
           "gumu":"/d/gumu/dating",
      "shaolin":"/d/shaolin/dxbdian",
          "huashan":"/d/huashan/houhuayuan1",
      "mingjiao":"/d/mingjiao/dadian",
      "guiyun":"/d/guiyunzhuang/guiyunting",
     "quanzhen":"/d/quanzhen/gongmen",
        ]));
      set("objects",([
"/u/advent/hong":1,
]));
     set("no_fight", 1);
set("valid_startroom",1);
     set("no_kill", 1);
     set("sleep_room", 1);
     set("no_steal", 1);

setup();
replace_program(ROOM);
   }

