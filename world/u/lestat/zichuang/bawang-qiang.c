// bawang-qiang.c ������ǹ����
//lestat modi for dtxy 2001

inherit SKILL;
#include <ansi.h>
string* skill_head =({
        "$N���㾫��ʹ��һ��",
        "$N����һ����һʽ",
        "$N�������ߣ����Ǻ���һ��ת����æ��ʹ��һ��",
        "$Nһ���粽��ʹһ��",
		"$Nһ��ǹ��,ʹ��һ��",
});
string* skill_tail =({
        "������$w��������$n���ţ���ɤ��ǰ�ġ�",
        "������$wһͦ����$n$l��",
        "������$w�������ٴ���$n��$l��",
        "������$w��ɣ�������㺮�⡣",
        "������$w����һ�����������¶��ϼ���$n$l",
});

mapping *action = ({
        ([      "action":
"$Nʹһ��"+HIW"��ӭ����������"NOR"������$w��������$n���ţ���ɤ��ǰ��",
                "damage":               50,
                "dodge":                5,
                "parry":                -10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N���㾫�񣬶���$w��һ��"+HIG"������Ѱ�ߡ�"NOR"����$n$l",
                "damage":               40,
                "dodge":                15,
                "parry":                -10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nһ���粽��ʹһ��"+HIC"����ɽ��ˮ��"NOR"������$w�������ٴ���$n��$l",
                "damage":               45,
                "dodge":                20,
                "parry":                -10,
                "damage_type":  "����"
        ]),
         ([      "action":
"$Nһ��ǹ�ѣ�ž����һ������"+HIM"�����ǹ����"NOR"���������ң�����ʵʵ����$nȫ��Ҫ��",
                "damage":               45,
                "dodge":                -10,
                "parry":                -5,
                "damage_type":  "����"
        ]),
         ([      "action":
"ֻ��$Nһ��б�磬ʹ��"+HIR"���ٻ������ơ�"NOR"������$w����һ�����������¶��ϼ���$n$l",
                "damage":               55,
                "dodge":                20,
                "parry":                0,
                "damage_type":  "����"
        ]),
        ([      "action":
"ֻ��$N����һ��������$w�����벻���ĽǶȴ���$n��$l��\n��һ��"+HIB"�����߳�����"NOR"�������磬�����ޱ�",
                "damage":               35,
                "dodge":                5,
                "parry":                -25,
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nʹ��"+MAG"������Ͷ���ơ�"NOR"������б�ɣ��Ӳ���ͻ��һǹ������$n$l",
                "damage":               40,
                "dodge":                15,
                "parry":                0,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N�������ߣ����Ǻ���һ��ת����æ��ʹ��һ��"+RED"������ǹ��"NOR"��$wһͦ����$n$l",
                "damage":               50,
                "dodge":                10,
                "parry":                -20,
                "damage_type":  "����"
        ]),
});

int valid_learn(object me)
{
        object ob;
     	if(me->query("family/family_name") != "������")
		return notify_fail("����ǹ���˽���������֮�ܣ�\n");
        if( (int)me->query("max_force") < 100 )
                return
         notify_fail("�������������û�а취������ǹ����\n");
        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "spear" )
                return notify_fail("���������һ��ǹ������ǹ����\n");

        return 1;
}

int valid_enable(string usage)
{
        return (usage=="spear") || (usage=="parry");
}
mapping query_action(object me, object weapon)
{
 int i;
 mapping* m_actions;
 i=me->query_action("BWQ_perform");
 if( ! me->query_temp("BWQ_perform"))
      {
     if(me->query("skill_bawang-qiang")==0) return action[random(4)];
     if(random(2))return action[random(4)];
     m_actions=me->query("skill_bawang-qiang");
     return m_actions[random(sizeof(m_actions))];
      }
    else 
   {
  return action[4];
  }
   return action[random(sizeof(action))];
}


int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon = me->query_temp("weapon"))
        ||      (string)weapon->query("skill_type") != "spear" )
                return
notify_fail("���������һ����ǹ���������Ƶ�������������ǹ����\n");

        if( (int)me->query("kee") < 30 
        ||    (int)me->query("force") < 5  )
                return
notify_fail("�����������������ǹ������������Ϣ��Ϣ�ɡ�\n");
        me->receive_damage("kee", 20);
        me->add("force", -5);
        write(RED"ʮ��ɱһ�ˣ�ǧ�ﲻ���С�\n"NOR);
        return 1;
}

string perform_action_file(string func)
{
return CLASS_D("fighter") + "/bawang-qiang/" + func;
}
void skill_improved(object me)
{
   int m_skill=me->query_skill("bawang-qiang",1);


   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"��԰���ǹ������������ˣ���İ���ǹ��������һ���µľ��磡\n"NOR);
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
     tell_object(me,HIW"��ͻȻ�������飬�԰���ǹ���������һ���µ��÷���\n"NOR);
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

   m_actions=me->query("skill_bawang-qiang");
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
//   if(!arg||arg==" ")arg="����ǹ�ش���ɱ��"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+MAG"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_bawang-qiang",m_actions);
   me->add("zichuang/times",1);
}

