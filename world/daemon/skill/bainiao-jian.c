//���񽣷�
//lestat modi for dtxy 2001

inherit SKILL;
#include <ansi.h>

string* skill_head =({
        "$Nһ��",
        "ֻ��$N��������Ծ��,һ��",
        "$Nʹ��",
        "$NƮȻ������һʽ",
        "$N��������Ծ��,�������ּ�ת��һ��",
        "$N����������һ��",
});

string* skill_tail =({
        "������$w��������,�ó�һ���׹�ֱ��$n��$l",
        "��$w����һ������,������������,ֱȡ$n��$l",
        "���������ּ�ת,�ε�$nͷ��Ŀѣ",
        "������$w��ò����س�����$n��Χ.",
        "��������ˮ������$nȫ��",
        "������$w���������֮��һ������Ⱥ�ۡ�",
});

mapping *action = ({
   ([  "action": "$Nһ��"+HIC"������չ�᡹"NOR",����$w��������,�ó�һ���׹�ֱ��$n��$l",
     "dodge":     -20,
     "damage":     40,
     "damage_type":   "����"
   ]),
([ "action":"ֻ��$N��������Ծ��,һ��"+HIM"��ӥ�����ա�"NOR",������ˮ,һйǧ��,����$nȫ��",
     "dodge":     -30,
     "damage":     40,
     "damage_type":   "����"
   ]),
   ([   "action":
"$NƮȻ����,����$w΢΢���,ɲ�Ǽ������Ž�,�ִ�$wȫ��Ÿ���λ,����һ��"+HIG"��������졹"NOR"",
     "dodge":     -40,
     "damage": 35,
     "damage_type":   "����"
   ]),
   ([ "action":
"$N��ָ�ᵯ����,$w����һ������,������������,ֱȡ$n��$l,ȴ��һ��"+HIY"���ۼ�������"NOR"",
     "dodge":     -20,
     "damage": 45,
     "damage_type":   "����"
   ]),
  ([  "action":      
 "$Nһ��"+HIB"�������ƶˡ�"NOR",���⻮������ԲȦ,�������,�������",
     "dodge":     -30,
     "damage": 40,
     "damage_type":   "����"
   ]),
  ([   "action": 
"$N����$w������ҵػ���һ����,ƽƽ����$n��$l,���ǰ��񽣷�֮"+HIW"��������⡹"NOR"",
     "dodge":     -10,
     "damage":     50,
     "damage_type":   "����"
   ]),
  ([ "action": 
"$Nһʽ"+RED"���ž���Ѫ��"NOR",����$w��ת,��Ϊһ��Ѫ��,��ò����س�����$n��Χ",
     "dodge":     -30,
     "damage":     30,
     "damage_type":   "����"
   ]),
   ([ "action": 
"$N��������Ծ��,�������ּ�ת,�ε�$nͷ��Ŀѣ,����һ��"+HIR"�����ﱨ����"NOR"",
     "dodge":     -40,
     "damage":     35,
     "damage_type":   "����"
   ]),
   ([ "action": "$Nһ����Х,���ΰεض���,����һ��"+HIB"����Ӱ������"NOR",����ֱ��$nͷ��",
      "dodge": -20,
      "damage": 50,
      "damage_type": "����"
]),
 ([ "action":
 "$N����$wһ��,����ɢ��ʮ�����ɫϼ��,��ס��$nȫ��,����һ��"+HIG"����ȸ������"NOR"",
     "dodge": -10,
     "damage": 35,
    "damage_type": "����"
]),
([ "action": "$Nһ��"+HIC"������ѧ�ࡹ"NOR",����$w��һ�����벻���ķ�λֱ��$n������",
    "dodge": -40,
    "damage": 45,
    "damage_type": "����"
]),
(["action":
 "$N����$wһ��,���طֳ�һ����Ӱ,��������ͬʱ����$n���,����"+HIM"��ԧ��Ϸˮ��"NOR"",
  "dodge": -30,
  "damage": 50,
  "damage_type": "����"
]),
});

int valid_learn(object me)
{
   object ob;

   if( (int)me->query("max_force") < 50 )
    return notify_fail("�����������,û�а취�����񽣷�.\n");

   if( (string)me->query_skill_mapped("force")!= "ningxie-force")
     return notify_fail("���񽣷�������ϱ�����Ѫ��������.\n");

   if( !(ob = me->query_temp("weapon"))
   ||   (string)ob->query("skill_type") != "sword" )
     return notify_fail("���������һ�ѽ�������������\n");

   return 1;
}

int valid_enable(string usage)
{
   return usage=="sword" || usage=="parry"|| usage=="throwing";
}

mapping query_action(object me, object weapon)
{
     mapping* m_actions;
     m_actions=me->query("skill_bainiao-jian");
     if(me->query("skill_bainiao-jian")==0 )
     return action[random(sizeof(action))];
     if( random(4) == 1 )
     return m_actions[random(sizeof(m_actions))];
     else
     return action[random(sizeof(action))];
}

int practice_skill(object me)
{
   if( (int)me->query("kee") < 30
   ||   (int)me->query("force") < 3 )
    return notify_fail("���������������,û�а취��ϰ���񽣷�.\n");
   me->receive_damage("kee", 30);
   me->add("force", -3);
  write("�㰴����ѧ����һ����񽣷�.\n");
   return 1;
}

string perform_action_file(string action)
{
  return CLASS_D("yaomo/xueshan") + "/bainiao-jian/" + action;
}


void skill_improved(object me)
{
   int m_skill=me->query_skill("bainiao-jian",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"��԰��񽣷�����������ˣ���İ��񽣷�������һ���µľ��磡\n"NOR);
     if(me->query("zichuang/times")>7){
        tell_object(me,HIW"Ȼ����Ĺ����Ѿ��������壬�����ٴ��������ˡ�\n"NOR);
        return;
     }
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"Ȼ��������о�Ȼ������һ��ʧ��У�\n"NOR);
        return;
     }
     if((random(me->query("int")/2)+(int)me->query_skill("literate")/50)<10){
       tell_object(me,HIW"Ȼ�������������һ�����ĸо����·���һ˿��Ҫ�Ķ���û
��ץס��\n"NOR);
       return;
     }
     tell_object(me,HIW"��ͻȻ�������飬�԰����������һ���µ��÷���\n"NOR
);
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

   m_actions=me->query("skill_bainiao-jian");
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
//   if(!arg||arg==" ")arg="���񽣷���ɱ��"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIR"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_bainiao-jian",m_actions);
   me->add("zichuang/times",1);
}
 

