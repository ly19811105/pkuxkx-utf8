//manbudong.c 北大侠客行帮助NPC。 by all。
#include <ansi.h>


inherit NPC;

int do_look(string);
int ask_me();
int ask();
int time_period(int timep,object me);

void create()
{
        set_name("满不懂", ({ "man budong", "budong" }));
        set("long", "他生得很是平常，但不要以貌取人啊，也许他知道好些事情呢。你是否需要他帮助呢？\n");
         set("title", "无所不知");
           set("nickname", HIG"北侠帮助NPC"NOR);
        set("gender", "男性");
         set("rank_info/respect", RED"猪头"NOR);
        set("age", 60);
        set("attitude","friendly");
        set("str", 30);
        set("dex", 30);
        set("con", 30);
         set("int", 30);
         set("kar", 30);
         set("per", 60);
        set("shen_type", 0);
        set_skill("strike", 150);
        set_skill("sword",180);
        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("literate",200);
        set_skill("parry",200);
        set_skill("xiake-shenfa",150);
        set_skill("xiake-jianfa",150);
        set_skill("xiake-strike",150);
        set_skill("jiuyin-shengong",200);
        map_skill("force", "jiuyin-shengong");
        map_skill("sword","xiake-jianfa");
        map_skill("dodge","xiake-shenfa");
        map_skill("parry","xiake-jianfa");
        map_skill("strike","xiake-strike");
        prepare_skill("strike","xiake-strike");
        set("jiali",50);
        set("combat_exp", 1000000);
        set("max_qi", 1500);
        set("max_jing", 1500);
        set("max_jingli", 3000);
        set("neili", 3000);
        set("jingli", 3000);
        set("max_neili", 3000);

        set("inquiry", ([
            "name" : "我是谁？不值一提。",
            "here" : "这里就是北大侠客行啊。", 
              "北大侠客行" : "北大侠客行可算是发展最完善的侠客行了，你想玩么？",
        "猪头" : "你用title或者score命令可以知道谁是最笨的猪头了。",
           "门派" : "北大侠客行有少林，武当，丐帮，明教，全真，峨嵋，桃花岛，大理天龙，华山，日月神教，
星宿，古墓，灵鹫宫，侠客岛，杀手帮等门派，不知你想玩哪一派呢？有些地方没有什么门派，如泉州，
襄阳，钓鱼岛，也是很好玩的。\n",
            "帮助" : "你算问对人了。我虽然没玩过侠客行，但对怎么玩可是有一翻研究。\n你是想知道有关门派方面的有关信息呢，还是想了解其它方面，比如读书，赚钱，\n涨经验，涨道德等等？\n",

            "武当" :  "\n武当可是明门正派，你要投奔武当真是对极了。现在武当除了太极拳和太极剑外，
又新增加了太极爪和太极刀，有了互备功夫。太极神功和道学心法配合可以涨气。
太极剑的缠及其厉害，不过叛师后威力可就大打折扣了。不过武当下山须向宋远桥
请示才行。武当掌门张三丰平时不见客，想见张三丰须费一番周折。
武当还有书可读，什么太极十三势啦，道德经啦。
你如果不是武当的，宋远桥是不会让你进门的。不过你也可以从后山绕进去。",            "见张三丰" : "要见张真人，从张翠山五侠往西，w,sw,s,se,e,ne,n,nw,sw,s,e,open 
door,n,就能见到张真人了。",
            "太极十三势" : "找宋远桥要，可以读force到31级。",
            "道德经" : "武当的道德经可以读道学心法，下卷须向谷虚道长要，可以读taoism到101级。",
            "丐帮" : "\n丐帮是江湖第一帮派，丐帮的好处可多，可以随时随地睡觉，还可以乞讨和打探别
人的武功。不过你可要想好了，一旦叛出丐帮就永远也不能再回来了。洪帮主可是
厉害得很，但他却很嘴馋，如果你能给他找到蓉儿的叫化鸡，说不定他会教你一招
雷霆降龙，能够一招毙敌于掌下。丐帮还有棒法秘籍可读。",
            "棒法秘籍" : "找鲁有脚长老去要，需要大概100的师忠，可以读staff到111级。",
            "秘道" : "从中央广场enter shudong，say 天堂有路你不走呀，down，只要速度快，就
可以走1-5条秘道了。",
            "大理天龙" : "\n  天龙寺是一个好去处，六脉神剑、一阳指、北冥神功，最厉害的王语嫣。天龙入
门比较难，没有高级轻功和兵器功夫，但不要紧，因为在这里经验小于5000不算叛
师，可以在别派学了刀剑和轻功在去天龙。入师门后kurong-shengong就不要学了，
以后学beiming时要放弃的。会北冥后玩起来就游刃有余了。
  天龙寺有六脉神剑剑谱，凌波微步图谱，北冥神功图谱可读。无量山还可以读残
局和无量玉壁。",
            "无量山" : "要去无量山，需要dodge 80以上，不过回来时要过铁索桥，需要更高的轻
功才行，大概90到100吧。",
            "六脉神剑剑谱" : "向枯荣大师去要，可以读finger到151级。",
            "凌波微步图谱" : "在无量山洞中得到，可以读凌波微步到100级。",
            "北冥神功图谱" : "在无量山洞石室中磕头，只要心诚，就能得到，可读到120级。",
            "无量玉壁" : "去无量玉壁要 过迷魂阵，走法是s,e,n,w,n。如果身法足够高，还可以
爬上去拿到游侠宝剑。",
            "少林" : "\n少林可以说是最完备的一个门派。少林升级条件是各项技能大于30级，ask 清乐比
丘 about 达摩令，give ling to 自己的师父那一辈的弟子，打赢他。拜少林后要
想升到慧字辈，只要找人帮忙很容易的，过罗汉阵才是真正的挑战。 
少林派有大量的书籍可读，比较重要的有达摩心经，洗髓经等。
少林对叛师者极为痛恨，一旦叛出少林，则永世不得进入少林，哪怕是经验5000
之前叛的，等经验超过5000后照样不让进，这点需要特别注意。
少林对其他门派来说是不可缺少的。可以通过读少林的易筋经使多项基本技能达到
101级而不消耗潜能。 木人是涨经验的好帮手。其他门派的人要进少林，需要少林英雄令。
如果你已经是高手了，可以去少林的伏魔圈，五行洞，藏经阁去看看。",            "罗汉阵" : "\n过阵的要求是各项技能都超过 80级，ask 玄难大师 about 罗汉
大阵， ask 玄苦大师 about 罗汉大阵，然后到练武场等着。过了罗汉阵，增加经
验15000，并可以到达摩院二层由特殊功夫领悟基本功夫。",
     "少林英雄令" : "找扬州的托钵僧去要，给他1 gold就行了。",
          "达摩洞" : "从千佛殿open door，n，然后按下面顺序可以到达摩洞:sw,se,n,s,w,e,w,e,e,s,w,n,nw,n。",
     "菩提子" : "需要到少林的伏魔圈中走一趟。",
     "金刚罩" : "需要到少林的伏魔圈中走一趟。",
     "伏魔刀" : "需要到少林的伏魔圈中走一趟。",
            "伏魔圈" : "\n伏魔圈：从少林山门，往左、往右均可进入松林，要求 dodge大于20或30，具体
不大清楚了，然后从黄金处，w，e，s，e，n，n，e，w，s，到了青云坪，enter进
入金刚伏魔圈，如能挨三位渡字辈的长老每人一鞭不死，就有了要宝物的资格，如
果达到一定水平，便可ask 渡难 about 菩提子，ask 渡厄 about 伏魔刀，ask 渡劫
 about 金刚罩。不过要想从松林出来，必须走五行洞。",
            "五行洞" : "\n从伏魔圈出来后是不能走出松林的，必须经过五行洞。在松林里乱走，
会掉进陷阱，然后被送进监狱，醒来后give yu zu 10 silver，do 3 s，进入五行
洞，look一下第一个是什么洞，按照金生水、水生木、木生火、火生土、土生金的
顺序走五步，即可出洞（即金->水，etc)，五行方位是东方甲乙木、西方庚辛金、
南方丙丁火、北方壬癸水、中央戊己土。",
            "易筋经" : "少林的易筋经博大精深，仅其中的几篇就可以使玩者受益匪浅。比如易筋经轻功篇，
攻防篇，修行篇，拳法篇等。听说还有易筋经文学篇，不知是真是假。",
            "易筋经轻功篇" : "\n从千佛殿open door，n，然后按下面顺序到达摩洞:sw,se,n,s,w,e,w,e,
e,s,w,n,nw,n，拿到旧竹片(Bamboo), 可以读到30级，之后身上带有bamboo按上面
顺序走竹林，每走一次增加dodge值为自己的先天悟性，可以到101级。另外在钟楼
或鼓楼跳楼更快，要求有效dodge大于125，注意精气不要小于零，否则会假死。",
            "易筋经攻防篇" : "\n ask 打铁僧(右边竹林open door) about 铁手掌，然后look hand，如果
描述为:易筋经攻防篇 这是一块铁手掌，上面凹凹凸凸刻满了人形搏击的场面。
就是真的，否则就扔到别处重新要，知道要到真的。study hand 可以到 parry 30
级，之后要在跟人打架的时候边打边study hand，可以读到101级。",
            "易筋经修行篇" : "\n在大雄宝殿ketou，只要有毅力，便会磕出薄绢(Silk)来，不过要小心磕
头不要超过50下，否则会晕，可以离开一下再磕。读silk可以读 force到30级，然
后身上带有silk再磕头，可以到101级。",
            "易筋经拳法篇" : "\n finger、hand、claw、strike和cuff：在少林的西碑林，look tower，看到四句
诗，念第二句 (say 上报四重恩，下济三途苦)，然后 do 4 pull stone up，do 3 
push stone down,佛塔忽然发出轧轧的声音，向一侧缓缓移开，向下露出一个黑洞
洞的入口。下面有石板(Stone)，可以读这些功夫到30级，具体读哪一个都有可能，
30级以后要在里面study table，或直接读table，可到101级。",
            "藏经阁" : "藏经阁有好多少林秘籍，不过想得到不太容易，我是不敢去那。",
            "达摩心经" : "找少林方丈去要，能读禅宗心法到150级。",
            "洗髓经" : "找达摩老祖去要。要见达摩，先去方丈那问一下，然后就可以到达摩洞下面去见祖师了。",
            "古墓" : "\n  古墓派创立之初，玩之人颇多，不过高手出的却不多，大多是拿玉蜂浆的大米。
古墓初学比较容易，问问题，听故事，不出墓即可学武。虽说14不许出墓，但只要想
出可以杀出去，反正死了什么也不降，也可在外边存盘。功夫学到一定程度可以向杨
过和小龙女要君子剑、淑女剑。古墓的玉蜂浆可以涨精力，寒玉床用来练内力非常快，
杨女附近天罗地网网麻雀涨纤云步法非常之快。
古墓有玉女心经可读，还有天下奇书九阴真经。",
            "玉女心经" : "找陆无双去要，如果经验过了10000，可以读到50级。",
            "九阴真经" : "\n  终南山的一条小溪中有九阴真经，ask 杨女 about 九阴真经,她会告诉你，得找
到鞭法秘笈，而鞭法秘笈在李莫愁手上，问了她才可以拿到。拿了秘笈给杨女，然
后到小溪处，swim river，n，n，e，n，n，w，然后enter xuanwo。不过游泳是消
耗体力的。读九阴前100级需要literate，100级以后需要钻研，并且需要梵文100，
daoxue-xinfa 100，literate 100，钻研的最高等级为(先天悟性+10)*5。如果你非
常牛的话，可以钻研到很高的级别，而且不一定非得是古墓弟子。九阴神功的移魂
大法很是厉害，赶紧去学吧，还犹豫什么。",
            "日月神教" : "\n 日月神教其实还是很厉害的，但不知道玩的人并不多，是不是害怕受那
一刀之苦？也可以拜任我行啊，他的吸星大法很厉害的。不过要拜任我行
先得到梅庄中去把他救出来。话又说回来了，梅庄也不是那么好进的，黑
木令你拿不到吧，就算四宝，也是困难重重啊。算了吧，还是在教内转转
吧，说不定可以在柴房等地方search到一些宝物呢。", 
            "吸星大法" : "吸星大法是任我行老先生研究出来的一种内功。你可以到梅庄的地牢里去看看，
不过任老先生是不愿意别人偷学的，如果你能打败他，或许也未可知。", 
            "梅庄" : "\n 梅庄是东方不败关押任我行的地方，不许随便进出。外人如果找到四宝，或许有缘
一去。携带四宝，到门口敲门，分别敲4253下，就进去了。见到管家丁坚，看看
是不是有一幅画，问问丁坚剑术，然后给四位庄主他们喜欢的东西，跟他们比比
武，也许有机会去地牢里看看。到黄庄主的屋子后面搜索一下，也许有秘籍。", 
            "四宝" : "去华山村玉泉院李铁嘴那问问吧，他比我更清楚。不过广陵散太难弄到了。", 
            "广陵散" : "广陵散在竹林任盈盈手上，要拿广陵散，必须把令狐冲带到她面前。他们最
喜欢曲洋长老的笑傲江湖之曲了。", 
            "笑傲江湖之曲" : "笑傲江湖之曲在曲洋身上，听说曲长老在魔教柴房中快被渴死了，你去早了也许
能见上一面。",
            "华山" : "\n  华山的独孤九剑名扬天下，至今风清扬的弟子屈指可数。要想见风前辈一面真是
比登天还难。风清洋隐居在思过崖的山洞中。只有令狐冲知道风太师叔在什么地方。
华山剑法的天外飞龙能够一招致敌，为封不平不传之秘，如果你去向他学艺，也许
有缘学会。华山的紫霞秘籍和华山剑谱以及游龙剑至今不知落到了何处。
自古华山一条路，从 从千尺幢到百尺峡最难走，不过走得多了，也许对轻功有好处。",
            "思过崖" : "思过崖在华山练武场的northwest方向，令狐冲在那里整天面壁，
岳灵珊最清楚不过了。",
            "令狐冲" : "令狐冲整天在思过崖面壁，小师妹岳灵珊经常去看他。",
            "紫霞秘籍" : "在陆大有身上，能够读紫霞神功到100级。劳德诺早就对他虎视耽眈了。",
            "华山剑谱" : "在华山村王小二身上可读基本剑法到101级。小流氓知道王小二在哪，王小二最爱偷别人的鸡了。",
            "游龙剑" : "在冯铁匠手上。如果到岳不群书房拿到纸片，可以找李铁嘴伪造一封信，就可以找冯铁匠取剑了。",
            "桃花岛" : "\n  拜桃花岛有被开除的危险，仔细看看help。桃花岛这一派分归云庄和桃花岛两部分。
去桃花岛当然要坐船了，在泉州东边。岛上有一些特效丹药，找人问问吧。黄岛主女儿
黄蓉身上还有软猥甲和叫化鸡，看看能不能要来。归云庄也有许多好东西，池塘可以洗
澡，还有金轮铠甲和七星剑。黑风山上的白骨架可以用来练功，不过黑风双煞可不是好
惹的。桃花岛内功书和兰花扶穴手秘诀好象也在归云庄。", 
            "黄蓉" : "黄蓉住在清啸亭里，程英知道，傻姑也知道蓉姐姐在哪里。", 
            "桃花岛内功书" : "好象在归云庄的书房，仔细找找吧。可读force到31级。", 
            "金轮锴甲" : "在归云庄树林深处的隐者身上。你得拿着庄主的书信，进得树林，给他书信和虎皮。
树林里老虎可多了，还是别去了吧。",  
            "书信" : "你怎么这么笨啊，书信当然在书房了。", 
            "七星剑" : "七星剑在一个宝库里，去那要经过一个迷宫，迷宫入口有神灵把守，你如果给他手印，
就可以进去了。不过据说迷宫很难走，去的人十之八九都没有出来。", 
            "手印" : "好象在砍柴人手上，陆庄主正在找偷手印的人呢。", 
            "池塘" : "在归云庄的桃花林里，阿香一直想把总管的烟斗还给他，正发愁没人去呢。你如果帮了她
的忙，也许能去池塘洗澡了。不过洗澡后变美变丑，那得看你的福缘如何了。", 
            "兰花扶穴手秘诀" : "在归云庄的假山洞里，能读到101级。", 
            "全真" : "全真王重阳在首次华山论剑时夺得第一，武功自然了得，除了一阳指，同归剑法也是
厉害之极。男子拜全真时需要发誓，必须忠于全真才行。全真老者那里有奇药，还有蜂王蜜。浴室洗澡极爽。
全真的道德经能读daoxue-xinfa，是钻研九阴真经必须的。老顽童周伯通现在整天养蜂为乐，如果有缘，也许
能向他学会左右互搏。", 
            "周伯通" : "周伯通现在在全真的小树林里，养蜂为乐。", 
            "峨嵋" : "当小尼姑有什么好玩的。不过峨嵋后山的人参不错，能长5点内力，你可以去找找看。", 
            "星宿" : "星宿老怪丁春秋的化功大法和星宿毒掌非常厉害，而且见了正派之人便杀。李秋水自然
更不用说了。星宿的天山器法也不错。", 
            "天山器法" : "在摘星子身上，能读基本暗器到101级。", 
            "明教" : "明教的乾坤大挪移非常厉害，大腾挪步法是迄今为止唯一有perform的身法。", 
              "明教" : "去明教需要过沙漠。过沙漠时按n,w,w,w的顺序重复三次，大概就能过去了。
明教的乾坤大挪移非常厉害，大腾挪步法是迄今为止唯一有perform的身法。",
            "灵鹫宫" : "灵鹫宫是新开的门派，我可不清楚。不过听说那里有天龙八部。", 
            "天龙八部" : "天龙八部是一部奇书，能读刀法和剑法到180级。至于怎么拿，问问在线高手，
或到北大BBS的MUD版精华区看看吧。", 
            "襄阳" : "在扬州的杂货贩杨永福那里买一本襄阳导游图，襄阳的大部分秘密就都清楚了。", 
            "泉州": "泉州向阳老宅里面据说有辟邪剑法的秘籍。陈小二卖好多高级营养品。山洞里还有玄铁剑。", 
            "玄铁剑" : "为独孤求败所埋，在泉州的一个山洞里，他的丑雕在他死后一直守在那。去山洞需要
过河，得问问渔夫才行。如果给他抓到了鱼，他会给你一个水靠，穿上他就可以游过去了。", 
            "辟邪剑法" : "辟邪剑法乃福威镖局总镖头林震南的曾祖远图公所创，去问问他吧。问清楚后到天山
买卖提处买个火折，到泉州向阳老宅，下到井里，用火折照亮路后钻进去，press 林镖头告诉你的暗号，
爬上箱子，跳到梁上，就快拿到了。", 
            "钓鱼岛" : "钓鱼岛自古以来就是我国的领土，可是常有倭寇出入，你去了那儿一定把倭寇消灭光阿。
不过去钓鱼岛不太容易，得找个船家问问能不能出海。海上的路不好辨认，有个罗盘就好了。岛上钓鱼
可以涨内功，还有其它一些好东西。灌木丛里的一个山洞里还藏有一件护体软甲。", 
            "罗盘" : "如果你能帮泉州的船家找回他女儿的嫁妆(珍珠项链)，他也许会给你一个罗盘。珍珠项链
被浪人头目抢去了。", 
            "钓鱼" : "得在钓鱼岛的大礁石上钓鱼。要钓鱼当然要有鱼杆了，你必须从树林中的一棵树上砍树枝，
作为鱼杆，而砍树枝需要砍柴刀。", 
            "砍柴刀" : "在钓鱼岛的军营里找找看吧。", 
            "护体软甲" : "护体软甲在钓鱼岛灌木丛的一个山洞中。到灯塔顶上四处望(wang)一下，就会发现
灌木丛。砍灌木需要砍柴刀。如果救出军营中渔夫的女儿，他就会给你一把钥匙。要救人得需要女儿妆，
在山洞里也许能找到。",
              "平西王府" : "在去天龙寺的途中有一条向北的路，便是通往平西王府。你如果支持吴三桂自立
为王，就容易进出王府了。往里走见到吴三桂，问问他射月弓的情况，也许能到他的秘室看看。
秘室里有好多宝贝，象金丝甲，鱼肠刺，洋枪什么的。不过秘室有非常厉害的武师看守。即使
杀了所有武师，如果内力不行，也很难出得来，如果身上带有百合花也许好点。", 
              "射月弓" : "在平西王府的萍水逢身上，问问她吧。", 
              "百合花" : "听说平西王府的花农很是精通花道。", 
              "阿凡提" : "阿凡提被关在巴依客厅里，如果你帮他找回小毛驴，他会给你出个谜语，如果猜出来
了，他会给你80点经验和一两黄金。", 
              "谜语" : "阿凡提最爱猜谜语了。",
              "小毛驴" : "小毛驴被阿凡提丢在天山沙漠的绿洲上了。你可以从天山脚下出发sw，nw，sw，se，ne，
就到绿洲了。你知道走沙漠是非常需要水的。",
              "飞沙走石十三势" : "问问田伯光这个采花大盗，也许可以得到，能读blade到101级。",
              "鬼刀王五" : "王五在醉仙楼二楼，如果你揭露他这个鬼刀的老底，他会杀你的，不过他身上可有钱。",
              "天山雪莲" : "在天山山涧的采药人身上。得有匹马才能过得去。归云庄的黑鬃马或者天山的
伊犁马都可以。阿拉木罕最爱马了，你问问她，也许会得到一匹。",
                  "经验" : "经验对于每个人来说都是非常重要的。长经验的主要方法是做任务和战斗。做任务
有两种，一是做本门派的任务，既长经验又长潜能和师门忠诚度。另一种任务叫做task，长经验和潜能
非常快，不过风险比较大。战斗当然就是打架了，打经验和战斗力跟自己接近的NPC，就能长经验和潜能，
而且打得越多，长得越快，只要气足够长。关于战斗的技巧应该多向老玩家请教。少林的木人，黑风山的
白骨架以及帮主，盟主，使者都是很好的练功对象。
  除此之外，刚一出生时可以到中央广场的开站礼品树上摘果子吃，长1000点经验，还有内力和精力。
跟阿凡提猜谜语可以得经验，过少林罗汉阵可以得经验。就连找海公公做个手术都可以得到点经验。
不过有些门派不收经验太高的，这点需要注意。",
                  "道德" : "杀了比自己经验高的人，便会得到一定的道德。道德有正有负，这跟一个人的人品
有关。大体上人越厉害，道德也越高。如果想得正道德，就去杀那些恶人吧。如果想改变道德属性，
可以先去少林的达摩洞面壁，道德就会变为零。还有能长道德的物品，如宋青书的剑，黑木崖地图等。",
                  "宋青书的剑" : "武当首侠宋远桥的不孝之子宋青书因杀了其师叔莫声谷，逃到了峨嵋，
躲在万年庵中，如果夺下他的佩剑，把佩剑交给送远桥，可以涨道德5000。",
                  "黑木崖地图" : "日月神教的农夫是华山派的奸细，ask about 华山派，他就会原形闭露，
杀了他可以得到黑木崖地图，交与岳不群可以涨道德5000和得到一把碧水剑。",
"读书" : "北大侠客行能读的书籍很多，比如太极十三势，道德经，棒法秘籍，六脉神剑剑谱，
北冥神功图谱，凌波微步图谱，无量残局，无量玉壁，易筋经，达摩心经，洗髓经，少林武籍，
玉女心经，九阴真经，鞭法秘笈，紫霞秘籍，华山剑谱，桃花岛内功书，兰花扶穴手秘诀，天
山器法，乾坤大挪移，圣火令，吸星大法，射雕英雄传，天龙八部，辟邪剑法，飞沙走石十三
势，鹰爪功秘诀，开山掌法精要，葵花宝典，说文解字，马屁宝典，梵文，楚氏内功秘籍等等。
如果能上得侠客岛，能读的东西太多了。",
            "射雕英雄传" : "在郭靖手上，可读force和parry到180级。郭靖在襄阳，你去襄阳看看好了。",
            "少林武籍" : "在少林的藏经阁里有许多少林武籍，几乎能读所有的少林武功。",
            "鹰爪功秘诀" : "在梅庄黄仲公的内室，能读基本爪法到150级呢。",
            "开山掌法精要" : "在梅庄黄仲公的内室，能读基本掌法到150级呢",
            "圣火令" : "在明教教主张无忌手上，可读圣火神功到101级。",
            "葵花宝典" : "为东方不败的镇教之宝，听说能读葵花神功和辟邪剑法，谁也没见过。",
            "鞭法秘笈" : "鞭法秘笈在李莫愁手里，去问她要吧。",
            "杀手帮" : "当杀手可不是闹着玩的，可要想清楚了。如果你真的想干，就去问问梁柳鹤吧。如果
你经验超过100万，他会推荐你去找帮主楚云飞。首先得在效忠楼发誓，然后再经过几位堂主的考验，
就能见到楚云飞了。如果能把楚云飞杀了，可以得到面具，好玩得很。如果你精力充沛，还可以试着
找找楚氏内功秘籍。",
            "楚氏内功秘籍" : "在杀手帮后山的金刀护法手里。听说他跟阿萍关系不一般，你可以去阿平那
打探一番。去那种地方是需要大量金钱和精力的。",
            "侠客岛" : "侠客岛的功夫世人都很羡慕。如果拿到了侠客岛的赏善罚恶令，就可以在南海之滨
wave 黄衣大汉，问他侠客岛和如何去侠客岛。岛上的路很是复杂，到了以后可以向高手请教如何走。",
             "说文解字" : "在朱熹那有卖，能读literate到101级。",
             "马屁宝典" : "在朱熹那有卖，能读flatter到101级。",
             "梵文" : "在明教附件的老者处有卖，能读fanwen到100级。",
             "无量残局" : "在无量山中，能读literate到151级。",
              "赚钱" : (: ask :),
             "一灯大师" : (: ask_me :),
       ]) );

        setup();
       add_money("gold", 5);
        carry_object("/clone/armor/jinzhuang")->wear();
        carry_object("/clone/armor/manshoes")->wear();
        carry_object("/d/shaolin/obj/changjian")->wield();
} 

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("give_quest", "job");
        add_action("do_look","look");

}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(10) ) {
                case 0:
                        write( "满不懂笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，有什么不知道的，可以问(ask)我。\n");
                        break;
                case 1:
                        write( "满不懂笑眯眯地说道：这位" + RANK_D->query_respect(ob)
                                + "，要是想给我帮点忙，请打job。\n");
                        break;
        }
	return;

}
int give_quest()
{
        mapping quest ;
        object me,ob;
        int j, combatexp, timep,factor,num;
        int tag = 0;
        string *levels = ({
                        "1",
                        "2",
                        "3",
        });
        me = this_player();
        combatexp = (int) (me->query("combat_exp"));
if(base_name(environment(this_object())) != "/d/city/idleroom")
{
message_vision("满不懂对$N怒道：“你他妈的把老子给搬到什么地方来了？还不把我给搬回去。”\n",me);
command("slapfy " + me->query("id"));
return 1;
}
        if(me->is_busy())
        {
message_vision("满不懂对$N哼了一声道：“等你忙完了再说吧。”\n",me);
        return 1;
        }
        if(combatexp<10000)
        {
message_vision("满不懂对$N哼了一声道：“辣块妈妈，东西还没长齐想干嘛？”\n",me);
             return 1;
        }
		//去掉经验限制，改为经验高奖励低
/*	if(combatexp>5000000)
        {
message_vision("满不懂对$N哼了一声道：“你武功太高了，已经没有适合给你的任务了。”\n",me);
             return 1;
        }*/
// Let's see if this player still carries an un-expired task
        if((quest =  me->query("wquest")))
        {
             if( ((int) me->query("wjob/task_time")) >  time() )
             {
message_vision("满不懂对$N笑道：说你不行吧，还不服气？\n", me);
message_vision("满不懂瞟了$N一眼说道：你要是没本事，就拿点儿钱买就得了。\n",me);
                   return 1;
             }
             else
             {
message_vision("满不懂对着$N叹了一口气：没关系去拿别的也成。\n", me);
message_vision("满不懂瞟了$N一眼说道：你要是没本事，就拿点儿钱买就得了。\n",me);
		return 1;
             }
        }
/*
        for(j= sizeof(levels) - 1 ; j>=0; j--)
        {
             if( atoi(levels[j])  <= combatexp )
             {
                   num=j;
                   factor=10;
                   break;
             }
        }
        if (num>0)
        {
             if (random(50)>45)
             {
                   num=num-1;
             }
        } 
        else
        {
             if ((num<sizeof(levels)-1)&&(random(100)>95))
             {
                   num=num+1;
                   factor=15;
             }
        }
        tag=levels[num];
        quest = QUESTW_D(tag)->query_quest();
        timep = quest["time"];

 //       while (quest["quest_type"] == "杀")
 //       {
 //       quest = QUEST_D(tag)->query_quest();
 //       timep = quest["time"];
 //       }
*/
        if(combatexp<100000)
        {
        	tag = 1;
        	factor = 20;
        }
        else if(combatexp<1000000)
        {
        	tag = 2;
        	factor = 35;
        }
        else //if(combatexp<5000000)        
        {
        	tag = 3;
        	factor = 25;
        }
        quest = QUESTW_D(tag)->query_quest();
        timep = quest["time"];
        	
        time_period(timep, me);
        if(quest["quest_type"]=="杀")
             tell_object(me,"先替我把『"+quest["quest"]+HIW"』抓回来，我想看看他长得啥模样。\n" NOR);
        else
             tell_object(me,"找到『"+quest["quest"]+HIW"』给我，我会好好谢你。\n" NOR);
//        quest["exp_bonus"]=quest["exp_bonus"];
//        quest["pot_bonus"]=quest["pot_bonus"];
//        quest["repute"]=quest["score"];

        me->set("wquest", quest);
/*        
                   if (ob = present("xin", this_player()))
                   {
                   destruct(ob);     
                   }
*/                   
        me->set("wjob/task_time", (int) time()+(int) quest["time"]);
        me->set("wjob/quest_factor",factor);
		me->add("wjob/questnumber",1);
        return 1;
}

int time_period(int timep, object me)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        tell_object(me,HIW "满不懂吩咐道：如果你在" + time + "内");
        return 1;
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

int ask_me()
{
          object me;
          me = this_player();
          command("hehe "+me->query("id"));
           message("vision",
     HIY "一灯大师的任务事关机密，巫师不让说的。你还是去杨永福老板那里买本旅游指南好好琢磨琢磨吧！\n"
   NOR, environment(), this_object() );
  return 1;
}
int accept_object(object who, object ob)
{
        int bonus, exp, pot, score,factor,questnumber;
        string test;
        mapping quest;

        if (ob->query("money_id"))
        {
             if(!who->query("wquest"))
             {
                   message_vision("满不懂笑道：那我可就不客气了。\n",who);
                   return 1;
             }
             else
             if ( ob->value() < 2000)
             {
message_vision("满不懂一双尖针般的眼睛直盯着$N：这点钱可不够我们的开销！\n", who);
                   return 1;
             }
             else
             {
message_vision("满不懂笑道：那好，咱们买卖不成仁义在。想要好处再找我吧！\n",who);
                   who->set("wquest",0);
				   who->set("wjob/questnumber",0);
                   who->start_busy(1);
                   return 1;
             }
        }

        if(!(quest =  who->query("wquest")))
        {
             tell_object(who,"满不懂说道：这不是我想要的。\n");
             return 0;
        }

        if( ob->query("name") != quest["quest"])
        {
             tell_object(who,"满不懂说道：这是什么东西？我叫你办的事你就这样糊弄我？！\n");
             return 0;
        }

        if ((int) who->query("wjob/task_time") < time() )
        {
             tell_object(who,"满不懂说道：真是废物！你没有在指定的时间内回来！现在我已经用不着了。\n");
			 who->set("wjob/questnumber");
//             destruct(ob);
             return 0;
        }
        if (userp(ob))
        {
             tell_object(who,"满不懂说道：这好像不是“物品”吧？\n");
             return 0;
        } 
        else
        {
             tell_object(who,"满不懂赞许地点头说道：不错！差使办得还不错！\n");
             exp = quest["exp_bonus"]/2 + random(quest["exp_bonus"]);
             pot = quest["pot_bonus"]/4 + random(quest["pot_bonus"]/2);
             score = 10 + random(90);
             factor=who->query("wjob/quest_factor");
//             destruct(ob);

             if (factor)
             {
                  exp=exp*factor/10;
                  pot=pot*factor/10;
//                    score=score*factor/10;
             }
			 questnumber=who->query("wjob/questnumber");
			 if (questnumber > 10)
				 questnumber=5;
			 if (questnumber < 1)
				 questnumber=1;
			 exp=exp*questnumber/3;
			 pot=pot*questnumber/3;
//                           score=score*questnumber/3;
			 if (exp > 1000)
			 {
			 	exp = exp * 3/4;
			 	pot = pot * 3/4;
			 	score = score * 3/4;
			 }	
			 if (exp>5000000)
			 {
				 exp = exp /2;
				 pot = pot /2;
				 score = score /2;
			 }
			 if (exp > 10000000)
			 {
                                  exp = exp * 2/3;
                                  pot = pot * 2/3;
                                  score = score * 2/3;
			 }
             bonus = (int) who->query("combat_exp");
             bonus += exp;
             who->set("combat_exp", bonus);
             bonus = (int) who->query("potential");
             bonus = bonus - (int) who->query("learned_points");
             bonus = bonus + pot;
//              if( bonus > 10000) bonus = 10000;
             bonus += (int) who->query("learned_points");
             who->set("potential", bonus );
             bonus = (int) who->query("repute");
             bonus += score;
             who->set("repute", bonus);
             tell_object(who,HIW"你被奖励了：" + chinese_number(exp)
               + "点实战经验，"+ chinese_number(pot) + "点潜能，"
                + chinese_number(score)+"点江湖声望。\n"NOR);
             who->set("wquest", 0 );
             who->start_busy(2);
             tell_object(who,HIW"恭喜你完成一个差使！\n"NOR);
             call_out("destroying", 1, this_object(), ob);
            
             return 1;
        }
        return 1;
}

 int ask()
{
        object me;
        me = this_player();
        if (!me->query_temp("help/money")) 
   {
                say("满不懂对你说道： 钱可是好东西。 刚开始可以去配药赚钱，等功夫高了，可以杀NPC赚钱，
大部分NPC身上都有钱或物品。醉仙楼的仙老板肯定有，鬼刀王五钱更多。 听说杀手帮的柳随风
抢来了无数的黄金。物品大多数都可以卖钱，如果你有宝物，象软猥甲，护体软甲之类的，你可
就发了。跟阿凡提猜谜语可以得到经验和黄金。襄阳的土匪窝里有的是财宝。如果你手气特别好
的话，可以去赌场碰碰运气。
  侠客行里的大部分老玩家都挺热心的，可以向他们要。
  看看我身上还有钱么？\n");              me->set_temp("help/money",1);
           command("give "+me->query("id")+" 1 gold");
              return 1;           
}
       else
          {   
    command("chat* papaya "+me->query("id"));
              command("say 你不是刚刚问过我么，怎么这么快就忘了？\n");
       return 1;
          }
}

int do_look(string target)
{
        object me;
        me = this_player();
        if (target=="man budong" || target=="budong" ) 
   {
                   message("vision",
   HIY "满不懂说道：看什么，还是去玩侠客行吧！\n"
       "满不懂对" + me->name() + "说：需要帮忙么？\n"
   NOR, environment(), this_object() );
         command("admire "+me->query("id"));
           }
}       
