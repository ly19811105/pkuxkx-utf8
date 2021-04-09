inherit ROOM;

void create ()
  {
    set("short","行云居");
    set("long", @LONG
    这就是小学徒行云的住处，只见一条清溪旁结着七、八间茅屋，茅屋
    前后左右都是花圃，种满了诸般花草。
LONG);

        set("exits",([
//           "beijing":"/d/beijing/changanjie",
//           "wz": "/d/wizard/wizard_room",
           "north" : "/u/advent/studyroom",
//           "mengge" : "/d/xiangyang/jinzhang",
//           "xiangyang":"/d/xiangyang/xycenter.c",
//           "emei":"/d/emei/dadian",
           "south":"/d/wizard/wizard_room_advent",
//           "shenlong":"/d/shenlongdao/fengding",
//           "ruzhou":"/d/shaolin/ruzhou",
//           "taishan":"/d/taishan/fengchan",
//           "gumu":"/d/gumu/dating",
//           "west":__DIR__"zhanchang/entry",
//           "shaolin":"/d/shaolin/dxbdian",
//           "huashan":"/d/huashan/houhuayuan1",
//           "mingjiao":"/d/mingjiao/dadian",
//           "guiyun":"/d/guiyunzhuang/guiyunting",
//           "quanzhen":"/d/quanzhen/gongmen",
        ]));
        set("no_fight", 1);
        set("valid_startroom",1);
        set("no_kill", 1);
        set("sleep_room", 1);
        set("no_steal", 1);
        setup();
        replace_program(ROOM);
  }

