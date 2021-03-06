
//lestat modi for dtxy 2001

inherit SKILL;
#include <ansi.h>
string* skill_head =({
        "$N身形稍退，使出一招",
        "$N于朦朦胧胧中，使出一招",
        "$N四处游走，一招",
        "$N神态悠闲，一招",
        "$N中宫直进，突然一招",
        "$N双脚一顿，笔直跃起，一招",
});

string* skill_tail =({
        "，手中$w不停地颤抖着",
        "，手中$w对准$n的$l凌空一斩",
        "，反手将$w对准$n$l一剑刺去",
        "，手中$w轻妙地划向$n的$l",
        "，手中$w去势飘忽不定，只看得$n眼花缭乱",
        "，手中$w带起点点寒光，指向$n前胸穴道",
});

mapping *action = ({
		([	"name":			"御剑生风",
		"action":
"$N双脚一顿，笔直跃起，手中$w不停地颤抖着，\n"
"笼罩住$n全身。这势"+HIC"「御剑生风」"NOR"果然是无孔不入",
		"dodge":		-5,
		"parry":		-10,
		"damage":		 50,
		"damage_type":		"刺伤"
	]),
	([	"name":			"御剑如虹",
		"action":
"$N手中$w带起点点寒光，指向$n前胸穴道。$n正专心致志地对付着剑招，\n"
"不料$N左手运力拍向$n的$l。这势"+HIM"「御剑如虹」"NOR"亦真亦幻，实是难防",
		"dodge":		-5,
		"parry":		15,
		"damage":		40,
		"damage_type":		"震伤"
	]),
	([	"name":			"御剑成龙",
		"action":
"$N在$n四周游走，一招"+HIY"[御剑成龙]"NOR",手中$w去势飘忽不定，只看得$n眼花缭乱。\n"
"趁此良机，$N于朦朦胧胧中一抖$w，向$n的$l疾挑",
		"dodge":		-15,
		"parry":		10,
		"damage":		35,
		"damage_type":		"刺伤"
	]),
	([	"name":			"御剑行空",
		"action":
"$N仗起手中$w，带出点点寒光，罩住$n的胸腹，只等$n的破绽。\n"
"这招"+HIR"「御剑行空」"NOR"直如细雨般紧密，$n实在不知$w将要指向自己身上何处",
		"dodge":		25,
		"parry":		-10,
		"damage":		35,
		"damage_type":		"刺伤"
	]),
	([	"name":			"御剑无影",
		"action":
"$N手中$w中宫直进，疾速刺向$n的前心。\n"
"这招"+HIB"「御剑无影」"NOR"令人耳目一新。$n只觉浑身一紧，$w已刺到了$l",
		"dodge":		-15,
		"parry":		15,
		"damage":		35,
		"damage_type":		"刺伤"
	]),
	([	"name":			"御剑飞腾",
		"action":
"$N手中$w向$n的右手疾刺，但正当$n要招架时，\n"
"$w却突然转向了$n的左足！这招"+HIG"「御剑飞腾」"NOR"确实神鬼莫测",
		"dodge":		10,
		"parry":		-15,
		"damage":		45,
		"damage_type":		"刺伤"
	]),
});

mapping *action_xjh = ({        
([      "action":
HIR"罗襦绣袂香红，画堂中！\n"NOR"\t$N舞动$w，剑势如虹，晃如破天",
		"force":               60,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIG"细草平沙番马，小屏风！\n"NOR"\t$N牵引剑气，化成清风而扶",
		"force":               70,
                "damage":               70,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIB"卷罗幕，凭汝阁，思无穷！\n"NOR"\t$N剑气有如清风静止而立，化为一幕屏风，却又变化无穷",
		"force":               80,
                "damage":               80,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIY"暮雨轻烟魂断！\n"NOR"\t$N将$w轻轻一挥，屏风化为丝丝轻雨而散，散后而聚",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIM"隔断栊！\n"NOR"\t$N使出《相见欢》最后一式，把聚集在一起的气息如爆裂般炸开",
		"force":               100,
                "damage":               100,
                "dodge":                -80,
                "parry":                -80,
                "damage_type":  "刺伤"
        ]),  
});

mapping *action_nnj = ({        
([      "action":
HIG"洞庭青草，近中秋！\n"NOR"\t$N轻抚$w，突然间剑光一闪直袭$n的$l",
		"force":               30,
                "damage":               40,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIC"玉鉴琼田三万顷，著我扁舟一叶！\n"NOR"\t$N剑式浩荡，剑气却飘忽不定",
		"force":               30,
                "damage":               40,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIC"月华未吐，波光不动，新凉如水！\n"NOR"\t$N剑气内敛，如镜面平湖，暗含无尽风波",
		"force":               50,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIW"孤光自照，肝肺皆冰雪！\n"NOR"\t$N剑式回旋，招招自护，$n的心头一紧，一道锐利剑气已刺上了$n$l",
		"force":               60,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIW"素月分辉，明河共影！\n"NOR"\t$N使出《念奴娇》最后一式，将内敛的剑气突然外放，$n被笼罩在迫人的剑气中",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
});

mapping *action_yjn = ({        
([      "action":
HIG"江南好！\n"NOR"\t$N一声轻叹，突然间剑光一闪直袭$n的$l",
		"force":               40,
                "damage":               40,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIC"风景旧曾谙！\n"NOR"\t$N剑式反复，剑气却飘忽不定",
		"force":               40,
                "damage":               40,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIR"日出江花红胜火！\n"NOR"\t$N剑气突然大盛，如旭日初升",
		"force":               50,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIB"春来江水绿如蓝！\n"NOR"\t$N剑式再变，如水东流",
		"force":               60,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIW"能不忆江南！\n"NOR"\t$N使出《忆江南》最后一式，剑式绵绵无尽，$n应接不暇",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
});

mapping *action_sny = ({        
([      "action":
HIB"伫立长堤，淡荡晚风起！\n"NOR"\t$N一声轻叹，突然间剑光一闪直袭$n的$l",
		"force":               40,
                "damage":               40,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIB"留恋处，兰舟催发！\n"NOR"\t$N剑意似断还连，轻弹青锋难决断",
		"force":               40,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIG"塞柳万株，掩映箭波千里！\n"NOR"\t$N断然出剑，招式连绵浩荡",
		"force":               60,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIR"走舟车向此，人人奔名竞利！\n"NOR"\t$N随波逐流，似是无力控制",
		"force":               60,
                "damage":               70,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
WHT"玉楼清唱倚朱弦，余韵入疏烟！\n"NOR"\t$N使出《少年游》最后一式，直进中堂，化万剑为一剑",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
});

mapping *action_mjh = ({        
([      "action":
HIB"匹马驱驱，摇征辔！\n"NOR"\t$N一声轻叹，突然间剑光一闪直袭$n的$l",
		"force":               30,
                "damage":               60,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIB"似笑我，独自向长途！\n"NOR"\t$N轻弹青锋，自$n意想不到的角度出剑",
		"force":               30,
                "damage":               80,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIY"怒发冲冠，凭阑处！\n"NOR"\t$N双手持剑，大力劈杀",
		"force":               50,
                "damage":               80,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "劈伤"
        ]),  
([      "action":
HIC"仰天长啸，壮怀激烈！\n"NOR"\t$N招式大开大阖，气势猛烈",
		"force":               60,
                "damage":               100,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIR"三十功名尘与土，八千里路云和月！\n"NOR"\t$N使出《满江红》最后一式，直进中堂，全力刺出一剑",
		"force":               80,
                "damage":               120,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
});

mapping *action_cxs = ({        
([      "action":
HIB"一叶扁舟轻帆卷。暂泊楚江南岸！\n"NOR"\t$N一声轻叹，突然间剑光一闪直袭$n的$l",
		"force":               40,
                "damage":               50,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIB"孤城暮角，引胡笳怨！\n"NOR"\t$N轻弹青锋，自$n意想不到的角度出剑",
		"force":               40,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIY"水茫茫，平沙雁，旋惊散！\n"NOR"\t$N剑意似断还连，猛然间刺出一剑",
		"force":               80,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIC"天际遥山小，黛眉浅！\n"NOR"\t$N远远遁开，骤然返身挥出一道剑气",
		"force":               80,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIM"佳人无消息，断云远！\n"NOR"\t$N使出《长相思》最后一式，神情黯然，招式无迹可寻",
		"force":               100,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
});

mapping *action_yjm = ({        
([      "action":
HIB"驿外断桥边，寂寞开无主！\n"NOR"\t$N一声轻叹，突然间剑光一闪直袭$n的$l",
		"force":               40,
                "damage":               50,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIB"已是黄昏独自愁，更著风和雨！\n"NOR"\t$N轻弹青锋，自$n意想不到的角度出剑",
		"force":               40,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIB"无意苦争春，一任群芳妒！\n"NOR"\t$N剑意似断还连，猛然间刺出一剑",
		"force":               80,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
YEL"零落成泥碾作尘！\n"NOR"\t$N远远遁开，骤然返身挥出一道剑气",
		"force":               80,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIY"只有香如故！\n"NOR"\t$N使出《一剪梅》最后一式，暗香袅袅，招式无迹可寻",
		"force":               100,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
});

mapping *action_tsx = ({        
([      "action":
HIG"一曲新词酒一杯！\n"NOR"\t$N剑如游龙，令人耳目一新",
		"force":               50,
                "damage":               50,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "刺伤"
        ]),
([      "action":
HIB"几回疏雨滴圆荷！\n"NOR"\t$N轻弹青锋，剑鸣如疏雨滴荷",
		"force":               50,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),           
([      "action":
HIB"不辞清唱玉尊前！\n"NOR"\t$N如举玉尊，清唱前行",
		"force":               80,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
YEL"酒红初上脸边霞！\n"NOR"\t$N脸上红霞一闪，步如醉酒",
		"force":               80,
                "damage":               80,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "刺伤"
        ]),  
([      "action":
HIY"使星归觐九重天！\n"NOR"\t$N使出《踏莎行》最后一式，剑式如龙，直破九天",
		"force":               100,
                "damage":               100,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "刺伤"
        ]),  
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("你的内力修为不够深，御剑术学了也没用。\n");
	if (!(ob = me->query_temp("weapon"))
	   || (string)ob->query("skill_type") != "sword" )
		return notify_fail("你必须先找一柄剑才能练习剑法。\n");
	return 1;
}

int practice_skill(object me)
{
	int dod=(int)me->query_skill("dodge");
	int swo=(int)me->query_skill("yujianshu");

	if (dod<swo/2)
		return notify_fail("你的身法跟不上剑法，练下去很可能会伤到自己。\n");
	if ((int)me->query("kee") < 30)
		return notify_fail("你体质欠佳，强练御剑术有害无益。\n");
	if ((int)me->query("force") < 5)
		return notify_fail("你内力不足，强练御剑术有走火入魔的危险。\n");
	me->receive_damage("kee", 30);
	me->add("force", -5);
	message_vision("$N默默回忆了一会儿，然后练了一遍御剑术。\n", me);
	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword"||usage=="parry";
}
mapping query_action(object me, object weapon)
{
     mapping* m_actions;
     int p = me->query_temp("sword_type");
     int i;
     m_actions=me->query("skill_yujianshu");
     i = me->query_temp("pfm_xjh");
     if(p)
     {
     	switch(p)
     	{
     		case 1:
     		{	
     			return action_nnj[i];
     			break;
     		}
     		case 2:
     		{	
     			return action_yjn[i];
     			break;
     		}
     		case 3:
     		{	
     			return action_sny[i];
     			break;
     		}
     		case 4:
     		{	
     			return action_mjh[i];
     			break;
     		}
     		case 5:
     		{	
     			return action_cxs[i];
     			break;
     		}
     		case 6:
     		{	
     			return action_yjm[i];
     			break;
     		}
     		case 7:
     		{	
     			return action_tsx[i];
     			break;
     		}
     		case 8:
     		{	
     			return action_xjh[i];
     			break;
     		}
     		default:
     		{
     			return action[random(sizeof(action))];
     			break;	
     		}	
     	}
     }
     else
     {
	     if(me->query("skill_yujianshu")==0 )
	     return action[random(sizeof(action))];
	     if( random(4) == 1 )
	     return m_actions[random(sizeof(m_actions))];
	     else 
	    return action[random(sizeof(action))];
      }

}

string perform_action_file(string func)
{
	return CLASS_D("shushan") + "/yujianshu/"+func;
}
void skill_improved(object me)
{
   int m_skill=me->query_skill("yujianshu",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"你对御剑术的领悟加深了，你的御剑术进入了一个新的境界！\n"NOR);
   if(me->query("zichuang/times")>7){
        tell_object(me,HIW"然而你的功夫已经练至顶峰，不能再创出新招了。\n"NOR);
        return;
     }
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"然而你的心中居然产生了一种失落感！\n"NOR);
        return;
     }
     if((random(me->query("int")/2)+(int)me->query_skill("literate")/50)<10){
       tell_object(me,HIW"然而你的心中升起一种惆怅的感觉，仿佛有一丝重要的东西没有抓住。\n"NOR);
       return;
     }
     tell_object(me,HIW"你突然福至心灵，对御剑术领悟出了一招新的用法！\n"NOR);
     tell_object(me,"请为这招取一个名字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
   }
   return;
}

void name_skill(object me, string arg)
{
	string *banned_name = ({
                "你", "你", "我", "他", "她", "它", "爸", "妈",
                "爷", "奶", "巫师", "天神", "神仙",
        });
   mapping* m_actions;
   mapping m_act=([]);
   int content, i=strlen(arg);
   string msg;

   m_actions=me->query("skill_yujianshu");
 if(!pointerp(m_actions))m_actions=({});

   content=me->query("str")+2*me->query_skill("unarmed",1)/10;
   m_act+=(["damage":content]);
   content=-me->query("spi");
   m_act+=(["dodge" :content]);
   content=-me->query("cps");
   m_act+=(["parry" :content]);
   content=me->query("con")+2*me->query_skill("force",1)/10;
   m_act+=(["force" :content]);
   m_act+=(["damage_type":"刺伤"]);
if (!arg || arg=="") 
     {
          tell_object(me,"请为你的新招式取一个名字：");
          input_to( (: call_other, __FILE__, "name_skill", me:));
          return;
     }
     else while(i--) 
     {
                if( arg[i]<=' ' ) 
                {
                        tell_object(me,"招式名字不能使用控制字元，请重新设定一个名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if(strsrch(arg, "　") >= 0) 
                {
                        tell_object(me,"招式名字不能有空格，请重新设定一个名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) ) 
                {
                        tell_object(me,"请您用「中文」为你的新招式取名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
     }
     if( member_array(arg, banned_name)!=-1 ) 
     {
     tell_object(me,"对不起，这种名字会造成其他人的困扰。请重新设定一个名字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
     if( (strlen(arg) < 8) || (strlen(arg) > 16 ) ) 
     {
     tell_object(me,"对不起，招式名字必须是 ４ 到 ８ 个中文字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
//   if(!arg||arg==" ")arg="御剑术绝技"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIW"「"+arg+"」"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_yujianshu",m_actions);
   me->add("zichuang/times",1);
}
 

