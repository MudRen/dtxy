//�����β�����dragonfight.c
// cglaem...12/19/96.
//meipai skill(only dragon related NPCs can use it)
// tomcat �޸�
inherit SKILL;
#include <ansi.h>

string* skill_head =({
        "$N�߼�������˫���뷢��ʩ��һ��",
        "$N˫���������򣬽�������$n����һ��",
        "$N˫����ʩ����$nֱ�Ƴ�һ��",
        "$N����������ʹ��һ��",
        "$N��һ����������һ�죬һ��",
        "$N����ǰ�������ƴ�������״�����ʹһ��",
});

string* skill_tail =({
        "������һ��һ�����������£��͵�����$nб�Ƴ�ȥ",
        "��Ю��һ�ɾ�������$n���Ʒ�����������ͣ�������ٱ����������",
        "������ǰ̽������ٿ�ش����Ƶ��´��˹�ȥ������$n",
        "������Ծ�ڰ�գ����Ƹ��ַ�������֮ǰ����$nһ��",
        "�����ֹ��ã������󹳣�ʹ$n��������",
        "��Ծ���գ��Ӹ��»�$n���������",
});

mapping *action = ({
        ([      "action":
"$N����Ծ��һ��"+HIR"���������졹"NOR"��˫������ɽ����֮�ƻ���$n��$l",
                "dodge":                -40,
                "parry":                -40,
                "force":                180,
                "damage_type":          "����",
                "weapon" :              "˫��",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
        ]),
        ([      "action":
"$N���˷�����ͻȻ������ǰ����ָ�繳��һ��"+HIW"��Ǳ�����á�"NOR"����׼$n��$lһ��ץ�˹�ȥ",
                "dodge":                -60,
                "parry":                -40,
                "force":                250,
                "damage_type":          "ץ��",
                "weapon":               "������ָ",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
        ]),
        ([      "action":
"ֻ��$Nһ����˫��������һ��ɨ��$n����һ��"+HIB"��������β��"NOR"�����Ƿ���ʤ��",
                "dodge":                -50,
                "parry":                -40,
                "force":                250,
                "damage_type":          "����",
                "weapon":               "˫��",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
        ]),
        ([      "action":
"$N����������ʹ��һ��"+HIY"����ս��Ұ��"NOR"��Х���к�����ϣ���$nֱײ����",
                "dodge":                -60,
                "parry":                -40,
                "force":                200,
                "damage_type":          "ײ��",
                "weapon":               "ȫ��",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
        ]),
            ([  "action":
"ֻ��$Nһ������ڰ�գ�һ��"+HIC"�������ĺ���"NOR"����δ��������ȫ��������$n",
                "dodge":                -40,
                "parry":                -20,
                "force":                250,
                "damage_type":          "����",
                "weapon":               "����",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
        ]),
            ([  "action":
"$N����һ������$n�������һȭ������"+HIG"������������"NOR"�������ף������ޱ�",
                "dodge":                -10,
                "parry":                -50,
                "force":                180,
                "damage_type":          "����",
                "weapon":               "ȭͷ",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
        ]),
        ([  "action":
"$N����΢�����ұ����䣬���ƻ��˸�ԲȦ������һ����������ȥ������һ��"+HIB"�������лڡ�"NOR,
                "dodge":                -80,
                "parry":                -80,
                "force":                500,
                "damage_type":          "����",
                "weapon":               "ȭͷ",
                "parry_msg":    "ֻ�������ϡ�һ������$N���ָ�",
        ]),
});

int valid_learn(object me)
{
        if( (int)me->query_skill("dragonforce",1) < (int)me->query_skill("dragonfight",1)/2)
                return notify_fail("��������ķ���������տ���޷������������β�����\n");


        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail("�����β���������֡�\n");
        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed";
}


int practice_skill(object me)
{
        if( (int)me->query_skill("dragonforce",1) < (int)me->query_skill("dragonfight",1)/2)
                return notify_fail("��������ķ���������տ���޷������������β�����\n");

        if( (int)me->query("sen") < 50)
                return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");

        if( (int)me->query("kee") < 50 )
                return notify_fail("����������������Ϣһ�������ɡ�\n");

        if( (int)me->query("force") < 20 )
                return notify_fail("������������ˡ�\n");

        me->receive_damage("kee", 30);
        me->add("force", -20);

        return 1;
}

mapping query_action(object me, object weapon)
{
	int i;
	mapping* m_actions;
	m_actions=me->query("skill_dragonfight");
	if( !me->query_temp("HTH_perform")) 
	{
		if(me->query("skill_dragonfight")==0)
			return action[random(6)];
		if(random(4)) return action[random(6)];
		return m_actions[random(sizeof(m_actions))];
	}
	else
	{ 
		return action[6];
	}
  	return action[random(sizeof(action))];
}


string perform_action_file(string func)
{
        return CLASS_D("dragon") + "/dragonfight/" + func;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/2) > victim->query_str()/10) {
                victim->receive_wound("kee", damage_bonus / 3 );
                switch(random(3)) {
                        case 0: return HIB"��������������һ�����죬�����ǹ����������\n"NOR;
                        case 1: return HIB"$N����һ�£�$n��$l������������һ�����죡\n"NOR;
                        case 2: return HIB"ֻ����$n��$l��������һ�� ...\n"NOR;
                }
        }
}
void skill_improved(object me)
{
   int m_skill=me->query_skill("dragonfight",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"������β�������������ˣ�������β���������һ���µľ��磡\n"NOR);
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
     tell_object(me,HIW"��ͻȻ�������飬�����β����������һ���µ��÷���\n"NOR);
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

   m_actions=me->query("skill_dragonfight");
   if(!pointerp(m_actions))m_actions=({});

   //content=me->query("str")+me->query_skill("unarmed",1)/5;
   //m_act+=(["damage":content]);
   content=-me->query("spi");
   m_act+=(["dodge" :content]);
   content=-me->query("cps");
   m_act+=(["parry" :content]);
   content=me->query("con")+me->query_skill("force",1);
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
//   if(!arg||arg==" ")arg="���β�������"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIC"��"+arg+"��"NOR+skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_dragonfight",m_actions);
   me->add("zichuang/times",1);
}


