
// the quest format is the following mapping:
 // exp :    type     name           id            objname  objid     time 

#include <ansi.h>
mapping quests_list = ([
   3202 : ({ "kill","翠花",              "cui hua",   "",  "", "120" }),
    802 : ({ "kill","野狗",              "dog" ,  "",  "", "120" }),
    1012 : ({ "kill","蜜蜂",              "bee",  "",  "", "120" }),
    222 : ({ "kill","麻雀",              "maque" ,  "",  "", "120" }),
    102 : ({ "kill","书生",              "shu sheng",  "",  "", "120" }),
    105 : ({ "kill","小孩",              "kid" ,  "",  "", "120" }),
    140 : ({ "kill","回族妇女",      "woman" ,  "",  "", "160" }), 
    230 : ({ "kill","穷汉",              "poor man",   "",  "", "160" }),
    232 : ({ "kill","药铺伙计",          "yaopu huoji", "", "", "160" }),
    740 : ({ "kill","挑夫",              "tiao fu",  "",  "", "160" }), 
    478 : ({ "kill","阿庆嫂",            "aqing sao", "", "", "160"}),
    802 : ({ "kill","小流氓",            "punk",  "",  "", "160" }),
3072 : ({ "kill","流氓",               "liu mang", "","","220" }),
   3082 : ({ "kill","屠夫",               "tu fu","","","220"}),
  60012 : ({ "kill","阿拉木罕",               "alamuhan", "","","230" }),
  70052 : ({ "kill","虚通",               "xu tong","","","230"}),
  80152 : ({ "kill","守寺僧兵",             "seng bing","","","230"}), 
  80182 : ({ "kill","趟子手",               "tangzi shou",  "",  "", "230" }),
  80212 : ({ "kill","官兵",               "guan bing","","","230"}),
 106002 : ({ "kill","刀客",               "dao ke",  "",  "", "300" }),
 108002 : ({ "kill","卖艺人",                 "maiyi ren","","","300"}),
 113002 : ({ "kill","虚明",               "xu ming","","","300"}),
 118002 : ({ "kill","崔莺莺",               "cui yingying","","","300" }),
 122012 : ({ "kill","剑客",               "jian ke",  "",  "", "300" }),
 128002 : ({ "kill","程药发",               "cheng yaofa","","","300"}),
 129302 : ({ "kill","武敦儒",               "wu dunru","","","300"}),
  10102 : ({ "kill","游客",               "youke","","","200" }),
  10202 : ({ "kill","地痞",               "dipi",  "",  "", "200" }), 
  30402 : ({ "kill",HIC"眼镜蛇"NOR,       "snake",  "",  "", "200" }),
  30502 : ({ "kill",GRN"竹青蛇"NOR,       "snake",  "",  "", "200" }),
  51202 : ({ "kill","金环蛇",             "jin she",  "",  "", "200" }), 
  51302 : ({ "kill",HBWHT+BLK"七寸子蛇"NOR,     "snake",   "",  "", "200" }),
 100032 : ({ "kill","土匪",               "tufei",  "",  "", "400" }),
 117002 : ({ "kill","土匪头",               "tufei tou",  "",  "", "400" }),
 148012 : ({ "kill","欧阳克",               "ouyang ke", "",  "", "400" }),
 312002 : ({ "kill",RED"巨蟒"NOR,               "ju mang", "",  "", "400" }),
 383002 : ({ "kill","李莫愁",               "li mochou","",  "", "400" }),
 394002 : ({ "kill","天狼子",               "tianlang zi", "",  "", "400"  }),
 610002 : ({ "kill","狮吼子",               "shihou zi","",  "", "400" }),
 615002 : ({ "kill","摘星子",               "zhaixing zi", "",  "", "400" }),
 617502 : ({ "kill","梅超风",                 "mei chaofeng","",  "", "400" }),
 721002 : ({ "kill","陈玄风",                 "chen xuanfeng","",  "", "400" }),
 722002 : ({ "kill","陆乘风",                 "lu chengfeng","",  "", "400" }),
1180022 : ({ "kill","鲍大楚",               "bao dachu", "",  "", "900" }),
1190022 : ({ "kill","上官云",               "shangguan yun", "",  "", "900"  }),
1200022 : ({ "kill","童百熊",               "tong baixiong","",  "", "900"  }),
1540002 : ({ "kill","黑冠巨蟒",               "snake",  "",  "", "900" }),
2230002 : ({ "kill","丁春秋",               "ding chunqiu","",  "", "900" }),
3500002 : ({ "kill","李秋水",               "li qiushui","",  "", "900" }),

    201 : ({ "give","小孩",              "kid" ,  "铜板",  "coin", "120" }),
    221 : ({ "give","男孩",              "boy" ,  "铜板",  "coin", "120" }),
   1101 : ({ "give","老农" ,              "lao nong","水壶","water bottle","120"}),
   1301 : ({ "give","老婆婆",            "old woman",  "白银",  "silver", "120" }), 
   1501 : ({ "give","老大娘",            "old woman",  "白银",  "silver", "120" }), 
   1701 : ({ "give","穷汉",              "poor man",   "白银",  "silver", "120" }),
   3001 : ({ "give","挑夫",              "tiao fu",  "麻鞋",  "gunny shoes", "200" }),
   3201 : ({ "give","民女",              "min nv", "粉红绸衫", "pink cloth", "200"}),
   3401 : ({ "give","回族妇女",      "woman" ,  "金项链", "golden necklace", "200" }),   
   3701 : ({ "give","赵狗儿",              "zhao gouer", "肥鸭","fei ya","200"}),
   5101 : ({ "give","阿庆嫂",            "aqing sao", "水蜜桃", "tao", "200"}),
  30001 : ({ "give","药铺伙计",          "yaopu huoji", "毒蛇胆", "shedan", "300" }),
  35001 : ({ "give","陆无双",               "lu wushuang",GRN"玉蜂针"NOR,"yufeng zhen", "300" }),  
  52001 : ({ "give","牧羊人",             "muyang ren", "长鞭","changbian","300" }),
  54001 : ({ "give","梁发",               "liang fa", "华山剑谱","sword book","300"}),  
  60001 : ({ "give","渔夫",               "yu fu","鱼","fish","300" }),
 110001 : ({ "give","管家",               "guan jia", "牢房钥匙","laofang key","500" }),
130001 : ({ "give","知客道长",               "zhike daozhang", "道德经「第一章」","jing","500" }),
 210001 : ({ "give","洪七公",              "hong qigong",GRN"玉竹杖"NOR,"yuzhu zhang", "500" }),  
 245001 : ({ "give","打铁僧",               "datie seng",   "烧红的铁锤",  "hot hammer", "500" }),
 305001 : ({ "give","游客",               "youke","野果","ye guo","500" }),

 320001 : ({ "give","波斯商人",               "bosi shangren","圣火令","shenghuo ling","500" }),
 330001 : ({ "give","道童",               "daotong", "拂尘","fuchen","500" }),
 332001 : ({ "give","小龙女",               "xiao longnu",HIW "白玫瑰" NOR,"flower", "500" }),
 334001 : ({ "give","本观大师",               "benguan dashi", "凌波微步图谱","lingbo-weibu", "500" }),
 520001 : ({ "give","慧修尊者",                "huixiu zunzhe","韦陀棍法",  "shaolin wuji", "800" }), 
 660001 : ({ "give","史青山",               "shi qingshan", "伏魔刀",  "fumo dao", "800"  }),
3150001 : ({ "give","渡厄",               "du e",HIR"日月神刀"NOR,"riyue dao", "800" }),

    200 : ({"find","珊瑚白菜",          "shanhu baicai",          "",       "",        " 60" }),
    240 : ({"find","清水葫芦",          "qingshui hulu",          "",       "",        " 60" }),
    280 : ({"find","铁背心",            "tie beixin",     "",       "",        " 60" }),
    330 : ({"find","夹心荸荠",          "jiaxin biji",    "",       "",        " 60" }),
    370 : ({"find","麻辣豆腐",          "mala doufu",     "",       "",        " 60" }),
    410 : ({"find","皮手套",            "pi shoutao",     "",       "",        " 60" }),
    450 : ({"find","铁手掌",            "iron hand",      "",       "",        " 60" }),
    560 : ({"find","牛皮酒袋",          "jiudai",         "",       "",        "120" }), 
    600 : ({"find","花雕酒袋",          "jiudai",         "",       "",        "120" }), 
   1030 : ({"find","铁棍",              "tiegun",         "",       "",        "120" }), 
   1130 : ({"find","铁甲",              "armor",          "",       "",        "120" }), 
   1310 : ({"find","长剑",              "changjian",      "",       "",        "120" }), 
   1610 : ({"find","好逑汤",            "haoqiu tang",    "",       "",        "120" }), 
   1700 : ({"find","甜点心",            "dianxin",        "",       "",        "120" }), 
   2100 : ({"find","粽子",              "zongzi",         "",       "",        "120" }), 
   2140 : ({"find","少林英雄令",        "yingxiong ling", "",       "",        "200" }), 
   2330 : ({"find","臭鸭蛋",            "chou yadan",     "",       "",        "200" }), 
   5200 : ({"find","红烧狗肉",          "gou rou",        "",       "",        "200" }), 
11000 : ({"find","道德经「下卷」",    "jing","",    "",        "300" }), //change
  52000 : ({"find","水靠",              "shui kao",       "",       "",        "300" }), // dex>25
  56000 : ({"find",YEL"黄布袈裟"NOR,          "jia sha",        "",       "",        "300" }), 
 101000 : ({"find","道德经「第二章」",  "jing","",    "",        "400" }), //change
 105000 : ({"find","道德经「第十八章」","jing","",    "",        "400" }), //change
 109000 : ({"find","华严经",            "shu",            "",       "",        "400" }), 
 113000 : ({"find","波罗蜜多心经",      "shu",          "",       "",        "400" }), 
 140000 : ({"find",MAG "马屁宝典" NOR,  "mapi baodian", "",   "",        "400" }),    
200000 : ({"find","钢剑",              "jian",          "",       "",        "450" }), 
 300000 : ({"find","北冥神功图谱",      "beiming shengong","",    "",        "450" }), //dodge>100
 308000 : ({"find","凌波微步图谱",      "lingbo-weibu", "",       "",        "450" }), //dodge>100
 303000 : ({"find",BBLK "黑郁金香" NOR,  "flower",   "",       "",        "450" }), //dodge>100
 307000 : ({"find",RED "睡芙蓉" NOR,    "flower",     "",       "",        "450" }), //dodge>100
 313000 : ({"find",HIG "翡翠绿" NOR,    "flower",     "",       "",        "450" }), //dodge>100
 352000 : ({"find",GRN "玉女心经" NOR,  "yunu xinjing", "",   "",        "450" }), 
 514000 : ({"find","无常杖法",          "shaolin wuji",     "",       "",        "800" }), 
 530000 : ({"find","伏魔刀",            "fumo dao",       "",       "",        "800" }), 
1010000 : ({"find","软猬甲",            "ruanwei jia",    "",       "",        "800" }),      //要求桃花岛
2010000 : ({"find",HIB "冰魄杖" NOR,    "bingpo zhang","",      "",        "800" }),      //  要求星宿派的
2100000 : ({"find", HIG "玄铁剑" NOR,   "xuantie sword",     "",    "",        "800" }), 
2120000 : ({"find", GRN "玉箫" NOR,     "yu xiao",     "",       "",        "800" }),      //要求桃花岛
2500000 : ({"find","铃索",          "lingsuo",        "",       "",        "800" }), 
3100000 : ({"find",HIR"日月神刀"NOR,    "riyue dao",          "",       "",        "800" }), 
3300000 : ({"find",RED"任我行的首级"NOR,"shou ji","",       "",        "800" }), 
5000000 : ({"find","菩提子",            "puti zi",        "",       "",        "800" }),  

    502 : ({ "win","书生",              "shu sheng",  "",  "", "120" }),
   3102 : ({ "win","农妇",              "woman" ,  "",  "", "120" }), 
   3502 : ({ "win","药铺伙计",          "yaopu huoji", "", "", "120" }),
  10102 : ({ "win","游客",               "youke","","","230" }),
  10502 : ({ "win","道童",               "daotong", "","","230" }),
  20302 : ({ "win","渔夫",               "yu fu","","","230" }),
  20702 : ({ "win","沙弥",               "sha mi", "","","230" }),
  30802 : ({ "win","练功弟子",           "liangong dizi","","","230"}),//归云庄的练功弟子
  40202 : ({ "win","李铁嘴",             "fortune teller",   "",  "", "230" }),
   3202 : ({ "win","翠花",              "cui hua",   "",  "", "120" }),
   5002 : ({ "win","小流氓",            "punk",  "",  "", "120" }),
  10102 : ({ "win","游客",               "youke","","","200" }),
  10202 : ({ "win","地痞",               "dipi",  "",  "", "200" }), 
  30402 : ({ "win",HIC"眼镜蛇"NOR,       "snake",  "",  "", "200" }),
  30502 : ({ "win",GRN"竹青蛇"NOR,       "snake",  "",  "", "200" }),
  51202 : ({ "win","金环蛇",             "jin she",  "",  "", "200" }), 
  51302 : ({ "win",HBWHT+BLK"七寸子蛇"NOR,     "snake",   "",  "", "200" }),
 100032 : ({ "win","土匪",               "tufei",  "",  "", "400" }),
 117002 : ({ "win","土匪头",               "tufei tou",  "",  "", "400" }),
 148012 : ({ "win","欧阳克",               "ouyang ke", "",  "", "400" }),
 312002 : ({ "win",RED"巨蟒"NOR,               "ju mang", "",  "", "400" }),
 383002 : ({ "win","李莫愁",               "li mochou","",  "", "400" }),
 394002 : ({ "win","天狼子",               "tianlang zi", "",  "", "400"  }),
 610002 : ({ "win","狮吼子",               "shihou zi","",  "", "400" }),
 615002 : ({ "win","摘星子",               "zhaixing zi", "",  "", "400" }),
 617502 : ({ "win","梅超风",                 "mei chaofeng","",  "", "400" }),
 721002 : ({ "win","陈玄风",                 "chen xuanfeng","",  "", "400" }),
 722002 : ({ "win","陆乘风",                 "lu chengfeng","",  "", "400" }),
1180022 : ({ "win","鲍大楚",               "bao dachu", "",  "", "900" }),
1190022 : ({ "win","上官云",               "shangguan yun", "",  "", "900"  }),
1200022 : ({ "win","童百熊",               "tong baixiong","",  "", "900"  }),
1540002 : ({ "kill","黑冠巨蟒",               "snake",  "",  "", "900" }),
2230002 : ({ "win","丁春秋",               "ding chunqiu","",  "", "900" }),
3500002 : ({ "win","王重阳",               "wang chongyang","",  "", "900" }),

 ]);

