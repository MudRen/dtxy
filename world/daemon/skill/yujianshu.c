
//lestat modi for dtxy 2001

inherit SKILL;
#include <ansi.h>
string* skill_head =({
        "$N�������ˣ�ʹ��һ��",
        "$N�����������У�ʹ��һ��",
        "$N�Ĵ����ߣ�һ��",
        "$N��̬���У�һ��",
        "$N�й�ֱ����ͻȻһ��",
        "$N˫��һ�٣���ֱԾ��һ��",
});

string* skill_tail =({
        "������$w��ͣ�ز�����",
        "������$w��׼$n��$l���һն",
        "�����ֽ�$w��׼$n$lһ����ȥ",
        "������$w����ػ���$n��$l",
        "������$wȥ��Ʈ��������ֻ����$n�ۻ�����",
        "������$w�����㺮�⣬ָ��$nǰ��Ѩ��",
});

mapping *action = ({
		([	"name":			"��������",
		"action":
"$N˫��һ�٣���ֱԾ������$w��ͣ�ز����ţ�\n"
"����ס$nȫ������"+HIC"���������硹"NOR"��Ȼ���޿ײ���",
		"dodge":		-5,
		"parry":		-10,
		"damage":		 50,
		"damage_type":		"����"
	]),
	([	"name":			"�������",
		"action":
"$N����$w�����㺮�⣬ָ��$nǰ��Ѩ����$n��ר����־�ضԸ��Ž��У�\n"
"����$N������������$n��$l������"+HIM"��������硹"NOR"������ã�ʵ���ѷ�",
		"dodge":		-5,
		"parry":		15,
		"damage":		40,
		"damage_type":		"����"
	]),
	([	"name":			"��������",
		"action":
"$N��$n�������ߣ�һ��"+HIY"[��������]"NOR",����$wȥ��Ʈ��������ֻ����$n�ۻ����ҡ�\n"
"�ô�������$N������������һ��$w����$n��$l����",
		"dodge":		-15,
		"parry":		10,
		"damage":		35,
		"damage_type":		"����"
	]),
	([	"name":			"�����п�",
		"action":
"$N��������$w��������㺮�⣬��ס$n���ظ���ֻ��$n��������\n"
"����"+HIR"�������пա�"NOR"ֱ��ϸ�����ܣ�$nʵ�ڲ�֪$w��Ҫָ���Լ����Ϻδ�",
		"dodge":		25,
		"parry":		-10,
		"damage":		35,
		"damage_type":		"����"
	]),
	([	"name":			"������Ӱ",
		"action":
"$N����$w�й�ֱ�������ٴ���$n��ǰ�ġ�\n"
"����"+HIB"��������Ӱ��"NOR"���˶�Ŀһ�¡�$nֻ������һ����$w�Ѵ̵���$l",
		"dodge":		-15,
		"parry":		15,
		"damage":		35,
		"damage_type":		"����"
	]),
	([	"name":			"��������",
		"action":
"$N����$w��$n�����ּ��̣�������$nҪ�м�ʱ��\n"
"$wȴͻȻת����$n�����㣡����"+HIG"���������ڡ�"NOR"ȷʵ���Ī��",
		"dodge":		10,
		"parry":		-15,
		"damage":		45,
		"damage_type":		"����"
	]),
});

mapping *action_xjh = ({        
([      "action":
HIR"����������죬�����У�\n"NOR"\t$N�趯$w��������磬��������",
		"force":               60,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),
([      "action":
HIG"ϸ��ƽɳ����С���磡\n"NOR"\t$Nǣ������������������",
		"force":               70,
                "damage":               70,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIB"����Ļ��ƾ���˼���\n"NOR"\t$N����������羲ֹ��������ΪһĻ���磬ȴ�ֱ仯����",
		"force":               80,
                "damage":               80,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIY"ĺ�����̻�ϣ�\n"NOR"\t$N��$w����һ�ӣ����绯Ϊ˿˿�����ɢ��ɢ�����",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
([      "action":
HIM"�����У�\n"NOR"\t$Nʹ��������������һʽ���Ѿۼ���һ�����Ϣ�籬�Ѱ�ը��",
		"force":               100,
                "damage":               100,
                "dodge":                -80,
                "parry":                -80,
                "damage_type":  "����"
        ]),  
});

mapping *action_nnj = ({        
([      "action":
HIG"��ͥ��ݣ������\n"NOR"\t$N�ḧ$w��ͻȻ�佣��һ��ֱϮ$n��$l",
		"force":               30,
                "damage":               40,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "����"
        ]),
([      "action":
HIC"������������꣬���ұ���һҶ��\n"NOR"\t$N��ʽ�Ƶ�������ȴƮ������",
		"force":               30,
                "damage":               40,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIC"�»�δ�£����ⲻ����������ˮ��\n"NOR"\t$N�����������羵��ƽ���������޾��粨",
		"force":               50,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIW"�¹����գ��ηνԱ�ѩ��\n"NOR"\t$N��ʽ�����������Ի���$n����ͷһ����һ�����������Ѵ�����$n$l",
		"force":               60,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIW"���·ֻԣ����ӹ�Ӱ��\n"NOR"\t$Nʹ������ū�������һʽ���������Ľ���ͻȻ��ţ�$n�����������˵Ľ�����",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
});

mapping *action_yjn = ({        
([      "action":
HIG"���Ϻã�\n"NOR"\t$Nһ����̾��ͻȻ�佣��һ��ֱϮ$n��$l",
		"force":               40,
                "damage":               40,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "����"
        ]),
([      "action":
HIC"�羰�����ϣ�\n"NOR"\t$N��ʽ����������ȴƮ������",
		"force":               40,
                "damage":               40,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIR"�ճ�������ʤ��\n"NOR"\t$N����ͻȻ��ʢ�������ճ���",
		"force":               50,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIB"������ˮ��������\n"NOR"\t$N��ʽ�ٱ䣬��ˮ����",
		"force":               60,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIW"�ܲ��佭�ϣ�\n"NOR"\t$Nʹ�����佭�ϡ����һʽ����ʽ�����޾���$nӦ�Ӳ�Ͼ",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
});

mapping *action_sny = ({        
([      "action":
HIB"�������̣����������\n"NOR"\t$Nһ����̾��ͻȻ�佣��һ��ֱϮ$n��$l",
		"force":               40,
                "damage":               40,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "����"
        ]),
([      "action":
HIB"�����������۴߷���\n"NOR"\t$N�����ƶϻ������ᵯ����Ѿ���",
		"force":               40,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIG"�������꣬��ӳ����ǧ�\n"NOR"\t$N��Ȼ��������ʽ����Ƶ�",
		"force":               60,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIR"���۳���ˣ����˱���������\n"NOR"\t$N�沨������������������",
		"force":               60,
                "damage":               70,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
WHT"��¥�峪�����ң����������̣�\n"NOR"\t$Nʹ���������Ρ����һʽ��ֱ�����ã�����Ϊһ��",
		"force":               80,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
});

mapping *action_mjh = ({        
([      "action":
HIB"ƥ��������ҡ���Σ�\n"NOR"\t$Nһ����̾��ͻȻ�佣��һ��ֱϮ$n��$l",
		"force":               30,
                "damage":               60,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "����"
        ]),
([      "action":
HIB"��Ц�ң�������;��\n"NOR"\t$N�ᵯ��棬��$n���벻���ĽǶȳ���",
		"force":               30,
                "damage":               80,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIY"ŭ����ڣ�ƾ������\n"NOR"\t$N˫�ֳֽ���������ɱ",
		"force":               50,
                "damage":               80,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIC"���쳤Х��׳�����ң�\n"NOR"\t$N��ʽ�󿪴��أ���������",
		"force":               60,
                "damage":               100,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIR"��ʮ��������������ǧ��·�ƺ��£�\n"NOR"\t$Nʹ���������졷���һʽ��ֱ�����ã�ȫ���̳�һ��",
		"force":               80,
                "damage":               120,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
});

mapping *action_cxs = ({        
([      "action":
HIB"һҶ�����ᷫ���ݲ������ϰ���\n"NOR"\t$Nһ����̾��ͻȻ�佣��һ��ֱϮ$n��$l",
		"force":               40,
                "damage":               50,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "����"
        ]),
([      "action":
HIB"�³�ĺ�ǣ�������Թ��\n"NOR"\t$N�ᵯ��棬��$n���벻���ĽǶȳ���",
		"force":               40,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIY"ˮãã��ƽɳ�㣬����ɢ��\n"NOR"\t$N�����ƶϻ�������Ȼ��̳�һ��",
		"force":               80,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIC"���ңɽС����üǳ��\n"NOR"\t$NԶԶ�ݿ�����Ȼ����ӳ�һ������",
		"force":               80,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIM"��������Ϣ������Զ��\n"NOR"\t$Nʹ��������˼�����һʽ��������Ȼ����ʽ�޼���Ѱ",
		"force":               100,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
});

mapping *action_yjm = ({        
([      "action":
HIB"������űߣ���į��������\n"NOR"\t$Nһ����̾��ͻȻ�佣��һ��ֱϮ$n��$l",
		"force":               40,
                "damage":               50,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "����"
        ]),
([      "action":
HIB"���ǻƻ���Գ��������꣡\n"NOR"\t$N�ᵯ��棬��$n���벻���ĽǶȳ���",
		"force":               40,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIB"�����������һ��Ⱥ���ʣ�\n"NOR"\t$N�����ƶϻ�������Ȼ��̳�һ��",
		"force":               80,
                "damage":               50,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
YEL"���������������\n"NOR"\t$NԶԶ�ݿ�����Ȼ����ӳ�һ������",
		"force":               80,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIY"ֻ������ʣ�\n"NOR"\t$Nʹ����һ��÷�����һʽ��������������ʽ�޼���Ѱ",
		"force":               100,
                "damage":               80,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
});

mapping *action_tsx = ({        
([      "action":
HIG"һ���´ʾ�һ����\n"NOR"\t$N�������������˶�Ŀһ��",
		"force":               50,
                "damage":               50,
                "dodge":                -50,
                "parry":                -50,
                "damage_type":  "����"
        ]),
([      "action":
HIB"���������Բ�ɣ�\n"NOR"\t$N�ᵯ��棬����������κ�",
		"force":               50,
                "damage":               60,
                "dodge":                -50,
                "parry":                -60,
                "damage_type":  "����"
        ]),           
([      "action":
HIB"�����峪����ǰ��\n"NOR"\t$N��������峪ǰ��",
		"force":               80,
                "damage":               60,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
YEL"�ƺ��������ϼ��\n"NOR"\t$N���Ϻ�ϼһ�����������",
		"force":               80,
                "damage":               80,
                "dodge":                -60,
                "parry":                -60,
                "damage_type":  "����"
        ]),  
([      "action":
HIY"ʹ�ǹ�������죡\n"NOR"\t$Nʹ����̤ɯ�С����һʽ����ʽ������ֱ�ƾ���",
		"force":               100,
                "damage":               100,
                "dodge":                -70,
                "parry":                -70,
                "damage_type":  "����"
        ]),  
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("���������Ϊ�����������ѧ��Ҳû�á�\n");
	if (!(ob = me->query_temp("weapon"))
	   || (string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ����������ϰ������\n");
	return 1;
}

int practice_skill(object me)
{
	int dod=(int)me->query_skill("dodge");
	int swo=(int)me->query_skill("yujianshu");

	if (dod<swo/2)
		return notify_fail("����������Ͻ���������ȥ�ܿ��ܻ��˵��Լ���\n");
	if ((int)me->query("kee") < 30)
		return notify_fail("������Ƿ�ѣ�ǿ���������к����档\n");
	if ((int)me->query("force") < 5)
		return notify_fail("���������㣬ǿ�����������߻���ħ��Σ�ա�\n");
	me->receive_damage("kee", 30);
	me->add("force", -5);
	message_vision("$NĬĬ������һ�����Ȼ������һ����������\n", me);
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
     tell_object(me,HIW"�������������������ˣ����������������һ���µľ��磡\n"NOR);
   if(me->query("zichuang/times")>7){
        tell_object(me,HIW"Ȼ����Ĺ����Ѿ��������壬�����ٴ��������ˡ�\n"NOR);
        return;
     }
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"Ȼ��������о�Ȼ������һ��ʧ��У�\n"NOR);
        return;
     }
     if((random(me->query("int")/2)+(int)me->query_skill("literate")/50)<10){
       tell_object(me,HIW"Ȼ�������������һ�����ĸо����·���һ˿��Ҫ�Ķ���û��ץס��\n"NOR);
       return;
     }
     tell_object(me,HIW"��ͻȻ�������飬���������������һ���µ��÷���\n"NOR);
     tell_object(me,"��Ϊ����ȡһ�����֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
   }
   return;
}

void name_skill(object me, string arg)
{
	string *banned_name = ({
                "��", "��", "��", "��", "��", "��", "��", "��",
                "ү", "��", "��ʦ", "����", "����",
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
   m_act+=(["damage_type":"����"]);
if (!arg || arg=="") 
     {
          tell_object(me,"��Ϊ�������ʽȡһ�����֣�");
          input_to( (: call_other, __FILE__, "name_skill", me:));
          return;
     }
     else while(i--) 
     {
                if( arg[i]<=' ' ) 
                {
                        tell_object(me,"��ʽ���ֲ���ʹ�ÿ�����Ԫ���������趨һ�����֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if(strsrch(arg, "��") >= 0) 
                {
                        tell_object(me,"��ʽ���ֲ����пո��������趨һ�����֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) ) 
                {
                        tell_object(me,"�����á����ġ�Ϊ�������ʽȡ���֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
     }
     if( member_array(arg, banned_name)!=-1 ) 
     {
     tell_object(me,"�Բ����������ֻ���������˵����š��������趨һ�����֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
     if( (strlen(arg) < 8) || (strlen(arg) > 16 ) ) 
     {
     tell_object(me,"�Բ�����ʽ���ֱ����� �� �� �� �������֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
//   if(!arg||arg==" ")arg="����������"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIW"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_yujianshu",m_actions);
   me->add("zichuang/times",1);
}
 

